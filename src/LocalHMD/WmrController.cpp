#include "LocalHMD.h"


NAMESPACE_HMD_BEGIN


#define FEATURE_BUFFER_SIZE	45

#define TICK_LEN		1e-7 // 0.1 µs ticks


typedef struct {
	Device base;
	uint32 device_flags; // DeviceFlags

	hid_device* controller_imu;
	Fusion sensor_fusion;
	vec3 raw_accel, raw_gyro;
	uint32 last_ticks;
	uint8 last_seq;
	MotionControllerPacket sensor;
} ControllerPrivateData;

static void vec3f_from_controller_gyro(int32_t in_vec[3], vec3& out_vec)
{
	out_vec[0] = (float)in_vec[0] * 1e-5; // FIXME, this is just a crude guess
	out_vec[1] = (float)in_vec[2] * 1e-5;
	out_vec[2] = (float)in_vec[1] * -1e-5;
}

static void vec3f_from_controller_accel(int32_t in_vec[3], vec3& out_vec)
{
	out_vec[0] = (float)in_vec[0] * (9.80665 * 2e-6); // 2 µg per LSB
	out_vec[1] = (float)in_vec[2] * (9.80665 * 2e-6);
	out_vec[2] = (float)in_vec[1] * (-9.80665 * 2e-6);
}

static void HandleControllerSensorMsg(ControllerPrivateData* priv, unsigned char* buffer, int size)
{
	uint32_t last_sample_tick = priv->sensor.timestamp;

	if(!MotionControllerDecodePacket(&priv->sensor, buffer, size)){
		LOGE("couldn't decode tracker sensor message");
	}

	MotionControllerPacket* s = &priv->sensor;


	vec3 mag = {{0.0f, 0.0f, 0.0f}};

	uint64_t tick_delta = 1000;
	if(last_sample_tick > 0) //startup correction
		tick_delta = s->timestamp - last_sample_tick;

	float dt = tick_delta * TICK_LEN;

	vec3f_from_controller_gyro(s->gyro, priv->raw_gyro);
	vec3f_from_controller_accel(s->accel, priv->raw_accel);

	UpdateFusion(&priv->sensor_fusion, dt, &priv->raw_gyro, &priv->raw_accel, &mag);

	//last_sample_tick = s->timestamp;
}

static void UpdateDevice_WmrCtrl(Device* device)
{
	ControllerPrivateData* priv = (ControllerPrivateData*)device;

	int size = 0;
	unsigned char buffer[FEATURE_BUFFER_SIZE];

	while(true){
		int size = hid_read(priv->controller_imu, buffer, FEATURE_BUFFER_SIZE);
		if(size < 0){
			LOGE("error reading from device");
			return;
		} else if(size == 0) {
			return; // No more messages, return.
		}

		// currently the only message type the hardware supports (I think)
		if(buffer[0] == CONTROLLER_IRQ_SENSORS){
			HandleControllerSensorMsg(priv, buffer, size);
		}else if(buffer[0] != HOLOLENS_IRQ_DEBUG){
			LOGE("unknown message type: %u", buffer[0]);
		}
	}

	if(size < 0){
		LOGE("error reading from device");
	}
}

static int GetFloat(Device* device, FloatValue type, float* out)
{
	ControllerPrivateData* priv = (ControllerPrivateData*)device;

	switch(type){
	case HMD_ROTATION_QUAT:
		*(quat*)out = priv->sensor_fusion.orient;
		break;

	case HMD_POSITION_VECTOR:
		if (priv->device_flags & HMD_DEVICE_FLAGS_LEFT_CONTROLLER)
			out[0] = -0.5f;
		else
			out[0] = 0.5f;
		out[1] = out[2] = 0;
		break;

	case HMD_DISTORTION_K:
		// TODO this should be set to the equivalent of no distortion
		memset(out, 0, sizeof(float) * 6);
		break;

	case HMD_CONTROLS_STATE:
		out[0] = !!(priv->sensor.buttons & MOTION_CONTROLLER_BUTTON_STICK);
		out[1] = !!(priv->sensor.buttons & MOTION_CONTROLLER_BUTTON_WINDOWS);
		out[2] = !!(priv->sensor.buttons & MOTION_CONTROLLER_BUTTON_MENU);
		out[3] = !!(priv->sensor.buttons & MOTION_CONTROLLER_BUTTON_GRIP);
		out[4] = !!(priv->sensor.buttons & MOTION_CONTROLLER_BUTTON_PAD_PRESS);
		out[5] = !!(priv->sensor.buttons & MOTION_CONTROLLER_BUTTON_PAD_TOUCH);
		out[6] = priv->sensor.stick[0] * (2.0 / 4095.0) - 1.0;
		out[7] = priv->sensor.stick[1] * (-2.0 / 4095.0) + 1.0;
		out[8] = (float)priv->sensor.trigger / 255.0;
		if (priv->sensor.touchpad[0] == 255)
			out[9] = 0.0;
		else
			out[9] = priv->sensor.touchpad[0] * (2.0 / 100.0) - 1.0;
		if (priv->sensor.touchpad[1] == 255)
			out[10] = 0.0;
		else
			out[10] = priv->sensor.touchpad[1] * (-2.0 / 100.0) + 1.0;
		break;

	default:
		lhmd_set_error(priv->base.ctx, "invalid type given to controller getf (%ud)", type);
		return -1;
		break;
	}

	return 0;
}

static int CloseDevice_WmrCtrl(Device* device)
{
	ControllerPrivateData* priv = (ControllerPrivateData*)device;

	LOGD("closing Microsoft Motion Controller device");

	hid_close(priv->controller_imu);

	free(device);

	return 0;
}

static hid_device* OpenDeviceIdx(int manufacturer, int product, int iface, int iface_tot, int device_index)
{
	struct hid_device_info* devs = hid_enumerate(manufacturer, product);
	struct hid_device_info* cur_dev = devs;

	int idx = 0;
	int iface_cur = 0;
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
		
		#if 0
		WString ps(cur_dev->product_string);
		String pss = ps.ToString();
		LOG(i << ": " << HexStr(cur_dev) << ": " << HexStr(cur_dev->vendor_id) << ":" << HexStr(cur_dev->product_id) << ": " << path << ", " << pss);
		#endif
		
		LOGI("%04x:%04x %s\n", manufacturer, product, cur_dev->path);

		if(idx == device_index && iface == iface_cur){
			ret = hid_open_path(cur_dev->path);
			LOGI("opening\n");
			if (ret)
				break;
		}

		cur_dev = cur_dev->next;

		iface_cur++;

		if(iface_cur >= iface_tot){
			idx++;
			iface_cur = 0;
		}
	}

	hid_free_enumeration(devs);

	return ret;
}

Device* OpenMotionControllerDevice(Driver* driver, DeviceDescription* desc)
{
	ControllerPrivateData* priv = (ControllerPrivateData*)lhmd_alloc(driver->ctx, sizeof(ControllerPrivateData));

	if(!priv)
		return NULL;

	priv->base.ctx = driver->ctx;
	priv->device_flags = desc->device_flags;

	int idx = atoi(desc->path);

	// Open the controller device
	priv->controller_imu = OpenDeviceIdx(MICROSOFT_VID, MOTION_CONTROLLER_PID, 0, 1, idx);

	if(!priv->controller_imu) {
		priv->controller_imu = OpenDeviceIdx(MICROSOFT_VID, MOTION_CONTROLLER_PID_SAMSUNG, 0, 1, idx);
		if(!priv->controller_imu)
			goto cleanup;
	}
	// TODO read_config

	if(hid_set_nonblocking(priv->controller_imu, 1) == -1){
		lhmd_set_error(driver->ctx, "failed to set non-blocking on device");
		goto cleanup;
	}

	// turn the IMU on
	hid_write(priv->controller_imu, MotionControllerImuOn, sizeof(MotionControllerImuOn));

	// turn the LEDs bright
	hid_write(priv->controller_imu, MotionControllerLedsBright,
		  sizeof(MotionControllerLedsBright));

	// Set default device properties
	SetDefaultDeviceProperties(&priv->base.properties);

	// Set device properties
	priv->base.properties.control_count = 11;
	priv->base.properties.controls_hints[0] = HMD_ANALOG_PRESS; // thumbstick press
	priv->base.properties.controls_hints[1] = HMD_HOME; // windows button
	priv->base.properties.controls_hints[2] = HMD_MENU;
	priv->base.properties.controls_hints[3] = HMD_SQUEEZE; // grip button
	priv->base.properties.controls_hints[4] = HMD_ANALOG_PRESS; // touchpad press
	priv->base.properties.controls_hints[5] = HMD_GENERIC; // touchpad touch
	priv->base.properties.controls_hints[6] = HMD_ANALOG_X; // thumbstick x
	priv->base.properties.controls_hints[7] = HMD_ANALOG_Y; // thumbstick y
	priv->base.properties.controls_hints[8] = HMD_TRIGGER;
	priv->base.properties.controls_hints[9] = HMD_ANALOG_X; // thumbpad x
	priv->base.properties.controls_hints[10] = HMD_ANALOG_Y; // thumbpad y
	priv->base.properties.controls_types[0] = HMD_DIGITAL;
	priv->base.properties.controls_types[1] = HMD_DIGITAL;
	priv->base.properties.controls_types[2] = HMD_DIGITAL;
	priv->base.properties.controls_types[3] = HMD_DIGITAL;
	priv->base.properties.controls_types[4] = HMD_DIGITAL;
	priv->base.properties.controls_types[5] = HMD_DIGITAL;
	priv->base.properties.controls_types[6] = HMD_ANALOG;
	priv->base.properties.controls_types[7] = HMD_ANALOG;
	priv->base.properties.controls_types[8] = HMD_ANALOG;
	priv->base.properties.controls_types[9] = HMD_ANALOG;
	priv->base.properties.controls_types[10] = HMD_ANALOG;

	// set up device callbacks
	priv->base.Update = UpdateDevice_WmrCtrl;
	priv->base.Close = CloseDevice_WmrCtrl;
	priv->base.GetFloat = GetFloat;

	InitFusion(&priv->sensor_fusion);

	return (Device*)priv;

cleanup:
	if(priv)
		free(priv);

	return NULL;
}


NAMESPACE_HMD_END
