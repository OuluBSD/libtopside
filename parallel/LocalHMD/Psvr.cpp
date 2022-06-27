#include "LocalHMD.h"


NAMESPACE_HMD_BEGIN


#define FEATURE_BUFFER_SIZE 256

#define TICK_LEN (1.0f / 1000000.0f) // 1 MHz ticks

#define SONY_ID                  0x054c
#define PSVR_HMD                 0x09af


typedef struct {
	Device base;

	hid_device* hmd_handle;
	hid_device* hmd_control;
	Fusion sensor_fusion;
	vec3 raw_accel, raw_gyro;
	uint8 last_seq;
	uint8 buttons;
	PsvrSensorPacket sensor;

} PsvrPrivateData;

static void AccelFromPsvrVec(const int16* smp, vec3* out_vec)
{
	out_vec->data[0] = (float)smp[1] *  (9.81 / 16384);
	out_vec->data[1] = (float)smp[0] *  (9.81 / 16384);
	out_vec->data[2] = (float)smp[2] * -(9.81 / 16384);
}

static void GyroFromPsvrVec(const int16* smp, vec3* out_vec)
{
	out_vec->data[0] = (float)smp[1] * 0.00105f;
	out_vec->data[1] = (float)smp[0] * 0.00105f;
	out_vec->data[2] = (float)smp[2] * 0.00105f * -1.0f;
}


static uint32 CalculateDeltaAndHandleRollover(uint32 next, uint32 last)
{
	uint32 tick_delta = next - last;

	// The 24-bit tick counter has rolled over,
	// adjust the "negative" value to be positive.
	if (tick_delta > 0xffffff) {
		tick_delta += 0x1000000;
	}

	return tick_delta;
}

static void HandleTrackerSensorMsg(PsvrPrivateData* priv, unsigned char* buffer, int size)
{
	uint32 last_sample_tick = priv->sensor.samples[1].tick;

	if(!PsvrDecodeSensorPacket(&priv->sensor, buffer, size)){
		LOGE("couldn't decode tracker sensor message");
	}

	PsvrSensorPacket* s = &priv->sensor;

	uint32 tick_delta = 500;

	// Startup correction, ignore last_sample_tick if zero.
	if (last_sample_tick > 0) {
		tick_delta = CalculateDeltaAndHandleRollover(
			s->samples[0].tick, last_sample_tick);

		// The PSVR device can buffer sensor data from previous
		// sessions which we can get at the start of new sessions.
		// @todo Maybe just skip the first 10 sensor packets?
		// @todo Maybe reset sensor fusion?
		if (tick_delta < 475 || tick_delta > 525) {
			LOGD("tick_delta = %u", tick_delta);
			tick_delta = 500;
		}
	}

	vec3 mag = {{0.0f, 0.0f, 0.0f}};

	for (int i = 0; i < 2; i++) {
		float dt = tick_delta * TICK_LEN;
		AccelFromPsvrVec(s->samples[i].accel, &priv->raw_accel);
		GyroFromPsvrVec(s->samples[i].gyro, &priv->raw_gyro);

		UpdateFusion(&priv->sensor_fusion, dt, &priv->raw_gyro, &priv->raw_accel, &mag);

		if (i == 0) {
			tick_delta = CalculateDeltaAndHandleRollover(
				s->samples[1].tick, s->samples[0].tick);
		}
	}

	priv->buttons = s->buttons;
}

static void Teardown(PsvrPrivateData* priv)
{
	if (priv->hmd_handle != NULL) {
		hid_close(priv->hmd_handle);
		priv->hmd_handle = NULL;
	}

	if (priv->hmd_control != NULL) {
		hid_close(priv->hmd_control);
		priv->hmd_control = NULL;
	}
}

static void Psvr_UpdateDevice(Device* device)
{
	PsvrPrivateData* priv = (PsvrPrivateData*)device;

	int size = 0;
	unsigned char buffer[FEATURE_BUFFER_SIZE];

	while(true){
		int size = hid_read(priv->hmd_handle, buffer, FEATURE_BUFFER_SIZE);
		if(size < 0){
			LOGE("error reading from device");
			return;
		} else if(size == 0) {
			return; // No more messages, return.
		}

		HandleTrackerSensorMsg(priv, buffer, size);
	}

	if(size < 0){
		LOGE("error reading from device");
	}
}

static int GetFloat(Device* device, FloatValue type, float* out)
{
	PsvrPrivateData* priv = (PsvrPrivateData*)device;

	switch(type){
	case HMD_ROTATION_QUAT:
		*(quat*)out = priv->sensor_fusion.orient;
		break;

	case HMD_POSITION_VECTOR:
		out[0] = out[1] = out[2] = 0;
		break;

	case HMD_DISTORTION_K:
		// TODO this should be set to the equivalent of no distortion
		memset(out, 0, sizeof(float) * 6);
		break;

	case HMD_CONTROLS_STATE:
		out[0] = (priv->buttons & PSVR_BUTTON_VOLUME_PLUS) != 0;
		out[1] = (priv->buttons & PSVR_BUTTON_VOLUME_MINUS) != 0;
		out[2] = (priv->buttons & PSVR_BUTTON_MIC_MUTE) != 0;
		break;

	default:
		lhmd_set_error(priv->base.ctx, "invalid type given to GetFloat (%ud)", type);
		return -1;
		break;
	}

	return 0;
}

int Psvr_CloseDevice(Device* device)
{
	PsvrPrivateData* priv = (PsvrPrivateData*)device;

	// set cinematic mode for the hmd
	hid_write(priv->hmd_control, PsvrCinematicmodeOn, sizeof(PsvrCinematicmodeOn));

	LOGD("Closing Sony PSVR device.");

	Teardown(priv);

	free(device);

	return 0;
}

static hid_device* OpenDevice_idx(int manufacturer, int product, int iface, int device_index)
{
	struct hid_device_info* devs = hid_enumerate(manufacturer, product);
	struct hid_device_info* cur_dev = devs;

	int idx = 0;
	hid_device* ret = NULL;

	Index<String> visited_paths;
	int i = 0;
	while (cur_dev) {
		// Check visited paths because of weird problem, in which hidapi gives tens of
		// duplicate entries and invalid strings
		#if 1
		String path(cur_dev->path);
		if (visited_paths.Find(path) >= 0) {
			cur_dev = cur_dev->next;
			continue;
		}
		visited_paths.Add(path);
		#endif
		
		LOGI("%04x:%04x %s", manufacturer, product, cur_dev->path);

		if (cur_dev->interface_number == iface) {
			if(idx == device_index){
				LOGI("\topening '%s'", cur_dev->path);
				ret = hid_open_path(cur_dev->path);
				break;
			}

			idx++;
		}

		cur_dev = cur_dev->next;
	}

	hid_free_enumeration(devs);

	return ret;
}

static Device* OpenDevice(Driver* driver, DeviceDescription* desc)
{
	PsvrPrivateData* priv = (PsvrPrivateData*)lhmd_alloc(driver->ctx, sizeof(PsvrPrivateData));

	if(!priv)
		return NULL;

	priv->base.ctx = driver->ctx;

	int idx = atoi(desc->path);

	// Open the HMD device
	priv->hmd_handle = OpenDevice_idx(SONY_ID, PSVR_HMD, 4, idx);

	if(!priv->hmd_handle)
		goto cleanup;

	if(hid_set_nonblocking(priv->hmd_handle, 1) == -1){
		lhmd_set_error(driver->ctx, "failed to set non-blocking on device");
		goto cleanup;
	}

	// Open the HMD Control device
	priv->hmd_control = OpenDevice_idx(SONY_ID, PSVR_HMD, 5, idx);

	if(!priv->hmd_control)
		goto cleanup;

	if(hid_set_nonblocking(priv->hmd_control, 1) == -1){
		lhmd_set_error(driver->ctx, "failed to set non-blocking on device");
		goto cleanup;
	}

	// turn the display on
	if (hid_write(priv->hmd_control, PsvrPowerOn, sizeof(PsvrPowerOn)) == -1) {
		lhmd_set_error(driver->ctx, "failed to write to device (power on)");
		goto cleanup;
	}

	// set VR mode for the hmd
	if (hid_write(priv->hmd_control, PsvrVrmodeOn, sizeof(PsvrVrmodeOn)) == -1) {
		lhmd_set_error(driver->ctx, "failed to write to device (set VR mode)");
		goto cleanup;
	}

	// Set default device properties
	SetDefaultDeviceProperties(&priv->base.properties);

	// Set device properties TODO: Get from device
	priv->base.properties.hsize = 0.126; //from calculated specs
	priv->base.properties.vsize = 0.071; //from calculated specs
	priv->base.properties.hres = 1920;
	priv->base.properties.vres = 1080;

	// Measurements taken from
	// https://github.com/gusmanb/PSVRFramework/wiki/Optical-characteristics
	priv->base.properties.lens_sep = 0.0630999878f;
	priv->base.properties.lens_vpos = 0.0394899882f;

	priv->base.properties.fov = DEG_TO_RAD(103.57f); //TODO: Confirm exact measurements
	priv->base.properties.ratio = (1920.0f / 1080.0f) / 2.0f;

	priv->base.properties.control_count = 3;
	priv->base.properties.controls_hints[0] = HMD_VOLUME_PLUS;
	priv->base.properties.controls_hints[1] = HMD_VOLUME_MINUS;
	priv->base.properties.controls_hints[2] = HMD_MIC_MUTE;
	priv->base.properties.controls_types[0] = HMD_DIGITAL;
	priv->base.properties.controls_types[1] = HMD_DIGITAL;
	priv->base.properties.controls_types[2] = HMD_DIGITAL;

	// calculate projection eye projection matrices from the device properties
	CalculateDefaultProjectionMatrices(&priv->base.properties);

	// set up device callbacks
	priv->base.Update = Psvr_UpdateDevice;
	priv->base.Close = Psvr_CloseDevice;
	priv->base.GetFloat = GetFloat;

	InitFusion(&priv->sensor_fusion);

	return (Device*)priv;

cleanup:
	if (priv) {
		Teardown(priv);
		free(priv);
	}

	return NULL;
}

static void GetDeviceList(Driver* driver, DeviceList* list)
{
	struct hid_device_info* devs = hid_enumerate(SONY_ID, PSVR_HMD);
	struct hid_device_info* cur_dev = devs;

	int idx = 0;

	Index<String> visited_paths;
	int i = 0;
	while (cur_dev) {
		// Check visited paths because of weird problem, in which hidapi gives tens of
		// duplicate entries and invalid strings
		#if 1
		String path(cur_dev->path);
		if (visited_paths.Find(path) >= 0) {
			cur_dev = cur_dev->next;
			continue;
		}
		visited_paths.Add(path);
		#endif
		
		DeviceDescription* desc;

		// Warn if hidapi does not provide interface numbers
		if (cur_dev->interface_number == -1) {
			LOGE("hidapi does not provide PSVR interface numbers\n");
#ifdef __APPLE__
			LOGE("see https://github.com/signal11/hidapi/pull/380\n");
#endif
			break;
		}

		// Register one device for each IMU sensor interface
		if (cur_dev->interface_number == 4) {
			desc = &list->devices[list->num_devices++];

			strcpy(desc->driver, "OpenHMD Sony PSVR Driver");
			strcpy(desc->vendor, "Sony");
			strcpy(desc->product, "PSVR");

			desc->revision = 0;

			snprintf(desc->path, HMD_STR_SIZE, "%d", idx);

			desc->driver_ptr = driver;

			desc->device_class = HMD_DEVICE_CLASS_HMD;
			desc->device_flags = HMD_DEVICE_FLAGS_ROTATIONAL_TRACKING;

			idx++;
		}

		cur_dev = cur_dev->next;
	}

	hid_free_enumeration(devs);
}

static void DestroyDriver(Driver* drv)
{
	LOGD("shutting down Sony PSVR driver");
	free(drv);
}

Driver* CreatePsvrDriver(Context* ctx)
{
	Driver* drv = (Driver*)lhmd_alloc(ctx, sizeof(Driver));

	if(!drv)
		return NULL;

	drv->GetDeviceList = GetDeviceList;
	drv->OpenDevice = OpenDevice;
	drv->Destroy = DestroyDriver;
	drv->ctx = ctx;

	return drv;
}


NAMESPACE_HMD_END

