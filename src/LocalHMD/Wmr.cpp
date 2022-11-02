#include "LocalHMD.h"


NAMESPACE_HMD_BEGIN


#define FEATURE_BUFFER_SIZE 497

#define TICK_LEN (1.0f / 10000000.0f) // 1000 Hz ticks



typedef struct {
	Device base;

	::hid_device* hmd_imu;
	Fusion sensor_fusion;
	vec3 raw_accel, raw_gyro;
	uint32 last_ticks;
	uint8 last_seq;
	HololensSensorsPacket sensor;

} WmrPrivateData;

static void vec3_from_hololens_gyro(int16 smp[3][32], int i, vec3* out_vec)
{
	out_vec->data[0] = (float)(smp[1][8*i+0] +
			     smp[1][8*i+1] +
			     smp[1][8*i+2] +
			     smp[1][8*i+3] +
			     smp[1][8*i+4] +
			     smp[1][8*i+5] +
			     smp[1][8*i+6] +
			     smp[1][8*i+7]) * 0.001f * -0.125f;
	out_vec->data[1] = (float)(smp[0][8*i+0] +
			     smp[0][8*i+1] +
			     smp[0][8*i+2] +
			     smp[0][8*i+3] +
			     smp[0][8*i+4] +
			     smp[0][8*i+5] +
			     smp[0][8*i+6] +
			     smp[0][8*i+7]) * 0.001f * -0.125f;
	out_vec->data[2] = (float)(smp[2][8*i+0] +
			     smp[2][8*i+1] +
			     smp[2][8*i+2] +
			     smp[2][8*i+3] +
			     smp[2][8*i+4] +
			     smp[2][8*i+5] +
			     smp[2][8*i+6] +
			     smp[2][8*i+7]) * 0.001f * -0.125f;
}

static void vec3_from_hololens_accel(int32 smp[3][4], int i, vec3* out_vec)
{
	out_vec->data[0] = (float)smp[1][i] * 0.001f * -1.0f;
	out_vec->data[1] = (float)smp[0][i] * 0.001f * -1.0f;
	out_vec->data[2] = (float)smp[2][i] * 0.001f * -1.0f;
}

static void HandleTrackerSensorMsg(WmrPrivateData* priv, unsigned char* buffer, int size)
{
	uint64 last_sample_tick = priv->sensor.gyro_timestamp[3];

	if(!HololensSensorsDecodePacket(&priv->sensor, buffer, size)){
		LOGE("couldn't decode tracker sensor message");
	}

	HololensSensorsPacket* s = &priv->sensor;


	vec3 mag = {{0.0f, 0.0f, 0.0f}};

	for(int i = 0; i < 4; i++){
		uint64 tick_delta = 1000;
		if(last_sample_tick > 0) //startup correction
			tick_delta = s->gyro_timestamp[i] - last_sample_tick;

		float dt = tick_delta * TICK_LEN;

		vec3_from_hololens_gyro(s->gyro, i, &priv->raw_gyro);
		vec3_from_hololens_accel(s->accel, i, &priv->raw_accel);

		UpdateFusion(&priv->sensor_fusion, dt, &priv->raw_gyro, &priv->raw_accel, &mag);

		last_sample_tick = s->gyro_timestamp[i];
	}
}

static void Wmr_UpdateDevice(Device* device)
{
	WmrPrivateData* priv = (WmrPrivateData*)device;

	unsigned char buffer[FEATURE_BUFFER_SIZE];

	while(true){
		int size = hid_read(priv->hmd_imu, buffer, FEATURE_BUFFER_SIZE);
		if(size < 0){
			LOGE("error reading from device");
			return;
		} else if(size == 0) {
			return; // No more messages, return.
		}

		// currently the only message type the hardware supports (I think)
		if(buffer[0] == HOLOLENS_IRQ_SENSORS){
			HandleTrackerSensorMsg(priv, buffer, size);
		}else if(buffer[0] != HOLOLENS_IRQ_DEBUG){
			LOGE("unknown message type: %u", buffer[0]);
		}
	}
}

static int GetFloat(Device* device, FloatValue type, float* out)
{
	WmrPrivateData* priv = (WmrPrivateData*)device;

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

	default:
		lhmd_set_error(priv->base.ctx, "invalid type given to hmd GetFloat (%ud)", type);
		return -1;
		break;
	}

	return 0;
}

int Wmr_CloseDevice(Device* device)
{
	WmrPrivateData* priv = (WmrPrivateData*)device;

	LOGD("closing Microsoft HoloLens Sensors device");

	hid_close(priv->hmd_imu);

	free(device);

	return 0;
}

static hid_device* OpenDevice_idx(int manufacturer, int product, int iface, int iface_tot, int device_index)
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

static int config_command_sync(hid_device* hmd_imu, unsigned char type,
			       unsigned char* buf, int len)
{
	unsigned char cmd[64] = { 0x02, type };

	hid_write(hmd_imu, cmd, sizeof(cmd));
	do {
		int size = hid_read(hmd_imu, buf, len);
		if (size == -1)
			return -1;
		if (buf[0] == HOLOLENS_IRQ_CONTROL)
			return size;
	} while (buf[0] == HOLOLENS_IRQ_SENSORS || buf[0] == HOLOLENS_IRQ_DEBUG);

	return -1;
}

int read_config_part(WmrPrivateData *priv, unsigned char type,
		     unsigned char *data, int len)
{
	unsigned char buf[33];
	int offset = 0;
	int size;

	size = config_command_sync(priv->hmd_imu, 0x0b, buf, sizeof(buf));

	if (size != 33 || buf[0] != 0x02) {
		LOGE("Failed to issue command 0b: %02x %02x %02x\n",
		       buf[0], buf[1], buf[2]);
		return -1;
	}
	size = config_command_sync(priv->hmd_imu, type, buf, sizeof(buf));
	if (size != 33 || buf[0] != 0x02) {
		LOGE("Failed to issue command %02x: %02x %02x %02x\n", type,
		       buf[0], buf[1], buf[2]);
		return -1;
	}
	for (;;) {
		size = config_command_sync(priv->hmd_imu, 0x08, buf, sizeof(buf));
		if (size != 33 || (buf[1] != 0x01 && buf[1] != 0x02)) {
			LOGE("Failed to issue command 08: %02x %02x %02x\n",
			       buf[0], buf[1], buf[2]);
			return -1;
		}
		if (buf[1] != 0x01)
			break;
		if (buf[2] > len || offset + buf[2] > len) {
			LOGE("Getting more information then requested\n");
			return -1;
		}
		memcpy(data + offset, buf + 3, buf[2]);
		offset += buf[2];
	}

	return offset;
}

void decrypt_config(unsigned char* config)
{
	WmrConfigHeader* hdr = (WmrConfigHeader*)config;
	for (int i = 0; i < hdr->json_size - sizeof(uint16); i++)
	{
		config[hdr->json_start + sizeof(uint16) + i] ^= wmr_config_key[i % sizeof(wmr_config_key)];
	}
}

unsigned char *read_config(WmrPrivateData *priv)
{
	unsigned char meta[84];
	unsigned char *data;
	int size, data_size;

	size = read_config_part(priv, 0x06, meta, sizeof(meta));

	if (size == -1)
		return NULL;

	// No idea what the other 64 bytes of metadata are, but the first two
	// seem to be little endian size of the data store.
	
	data_size = meta[0] | (meta[1] << 8);
	data = (unsigned char*)calloc(1, data_size);
	if (!data)
                return NULL;

	size = read_config_part(priv, 0x04, data, data_size);
	if (size == -1) {
		free(data);
		return NULL;
	}

	decrypt_config(data);

	LOGI("Read %d-byte config data\n", data_size);

	return data;
}


void process_nxjson_obj(const nx_json* node, const nx_json* (*list)[32], const char* match)
{
	if (!node)
		return;

	if (node->key) {
		if (strcmp(match,node->key) == 0)
		{
			//LOGE("Found key %s\n", node->key);
			for (int i = 0; i < 32; i++)
			{
				if (!list[0][i]) {
					list[0][i] = node;
					break;
				}
			}
		}
	}
	
	process_nxjson_obj(node->next, list, match);
	process_nxjson_obj(node->child, list, match);
}

void resetList(const nx_json* (*list)[32])
{
	memset(list, 0, sizeof(*list));
}

static Device* OpenHmdDevice(Driver* driver, DeviceDescription* desc)
{
	WmrPrivateData* priv = (WmrPrivateData*)lhmd_alloc(driver->ctx, sizeof(WmrPrivateData));
	unsigned char *config;
	bool samsung = false;

	if(!priv)
		return NULL;

	priv->base.ctx = driver->ctx;

	int idx = atoi(desc->path);

	// Open the HMD device
	priv->hmd_imu = OpenDevice_idx(MICROSOFT_VID, HOLOLENS_SENSORS_PID, 0, 1, idx);

	if(!priv->hmd_imu)
		goto cleanup;

	//Bunch of temp variables to set to the display configs
	int resolution_h, resolution_v;

	config = read_config(priv);
	if (config) {
		WmrConfigHeader* hdr = (WmrConfigHeader*)config;
		LOGI("Model name: %.64s\n", hdr->name);
		if (strncmp(hdr->name,
			    "Samsung Windows Mixed Reality 800ZAA", 64) == 0) {
			samsung = true;
		}

		char *json_data = (char*)config + hdr->json_start + sizeof(uint16);
		const nx_json* json = nx_json_parse(json_data, 0);

		if (json->type != NX_JSON_NULL)
		{
			//list to save found nodes with matching name
			const nx_json* returnlist[32] = {0};
			resetList(&returnlist); process_nxjson_obj(json, &returnlist, "DisplayHeight");
			LOGE("Found display height %lli\n", returnlist[0]->int_value); //taking the first element since it does not matter if you take display 0 or 1
			resolution_v = returnlist[0]->int_value;
			resetList(&returnlist); process_nxjson_obj(json, &returnlist, "DisplayWidth");
			LOGE("Found display width %lli\n", returnlist[0]->int_value); //taking the first element since it does not matter if you take display 0 or 1
			resolution_h = returnlist[0]->int_value;
			
			//Left in for debugging until we confirmed most variables working
			/*
			for (int i = 0; i < 32; i++)
			{
				if (returnlist[i] != 0)
				{
					if (returnlist[i]->type == NX_JSON_STRING)
						printf("Found %s\n", returnlist[i]->text_value);
					if (returnlist[i]->type == NX_JSON_INTEGER)
						printf("Found %lli\n", returnlist[i]->int_value);
					if (returnlist[i]->type == NX_JSON_DOUBLE)
						printf("Found %f\n", returnlist[i]->dbl_value);
					if (returnlist[i]->type == NX_JSON_ARRAY)
						printf("Found array, TODO\n");
				}
			}*/

		}
		else {
			LOGE("Could not parse json\n");
		}

		//TODO: use new config data

		nx_json_free(json);

		free(config);
	}
	else {
		LOGE("Could not read config from the firmware\n");
	}

	if(hid_set_nonblocking(priv->hmd_imu, 1) == -1){
		lhmd_set_error(driver->ctx, "failed to set non-blocking on device");
		goto cleanup;
	}

	// turn the IMU on
	hid_write(priv->hmd_imu, HololensSensorsImuOn, sizeof(HololensSensorsImuOn));

	// Set default device properties
	SetDefaultDeviceProperties(&priv->base.properties);

	// Set device properties
	if (samsung) {
		// Samsung Odyssey has two 3.5" 1440x1600 OLED displays.
		priv->base.properties.hsize = 0.118942f;
		priv->base.properties.vsize = 0.066079f;
		priv->base.properties.hres = resolution_h;
		priv->base.properties.vres = resolution_v;
		priv->base.properties.lens_sep = 0.063f; // FIXME
		priv->base.properties.lens_vpos = 0.03304f; // FIXME
		priv->base.properties.fov = DEG_TO_RAD(110.0f);
		priv->base.properties.ratio = 0.9f;
	} else {
		// Most Windows Mixed Reality Headsets have two 2.89" 1440x1440 LCDs
		priv->base.properties.hsize = 0.103812f;
		priv->base.properties.vsize = 0.051905f;
		priv->base.properties.hres = resolution_h;
		priv->base.properties.vres = resolution_v;
		priv->base.properties.lens_sep = 0.063f; // FIXME
		priv->base.properties.lens_vpos = 0.025953f; // FIXME
		priv->base.properties.fov = DEG_TO_RAD(95.0f);
		priv->base.properties.ratio = 1.0f;
	}

	// calculate projection eye projection matrices from the device properties
	CalculateDefaultProjectionMatrices(&priv->base.properties);

	// set up device callbacks
	priv->base.Update = Wmr_UpdateDevice;
	priv->base.Close = Wmr_CloseDevice;
	priv->base.GetFloat = GetFloat;

	InitFusion(&priv->sensor_fusion);

	return (Device*)priv;

cleanup:
	if(priv)
		free(priv);

	return NULL;
}

static Device* OpenDevice(Driver* driver, DeviceDescription* desc)
{
	if (desc->device_flags & (HMD_DEVICE_FLAGS_LEFT_CONTROLLER |
				  HMD_DEVICE_FLAGS_RIGHT_CONTROLLER))
		return OpenMotionControllerDevice(driver, desc);
	else
		return OpenHmdDevice(driver, desc);
}


static void GetDeviceList(Driver* driver, DeviceList* list)
{
	//struct hid_device_info* devs = hid_enumerate(MICROSOFT_VID, 0);
	struct hid_device_info* devs = hid_enumerate(0, 0);
	struct hid_device_info* cur_dev = devs;
	
	/*
	#If you can't see bluetooth controllers, add these udev settings
	
	sudo echo 'KERNEL=="hidraw*", SUBSYSTEM=="hidraw", ATTRS{idVendor}=="045e", ATTRS{idProduct}=="0659", MODE="0666"' >  /etc/udev/rules.d/50-wmr-controller.rules
	sudo echo 'KERNEL=="hidraw*", SUBSYSTEM=="hidraw", ATTRS{idVendor}=="03F0", ATTRS{idProduct}=="0367", MODE="0666"' >>  /etc/udev/rules.d/50-wmr-controller.rules
	sudo echo 'KERNEL=="hidraw*", SUBSYSTEM=="hidraw", ATTRS{idVendor}=="0BDA", ATTRS{idProduct}=="485A", MODE="0666"' >>  /etc/udev/rules.d/50-wmr-controller.rules
	sudo echo 'KERNEL=="hidraw*", SUBSYSTEM=="hidraw", KERNELS=="0005:045E:065B.*", MODE="0666"' >> /etc/udev/rules.d/50-wmr-controller.rules
	sudo echo 'KERNEL=="hidraw*", SUBSYSTEM=="hidraw", KERNELS=="0005:045E:065D.*", MODE="0666"' >> /etc/udev/rules.d/50-wmr-controller.rules
	sudo udevadm control --reload-rules
	# disconnect and reconnect the controller.
	# ...maybe even reboot
	
	# if still doesn't work, edit "/etc/bluetooth/input.conf" and uncomment
	UserspaceHID=true
	
	# TODO improve documentation
	*/
	
	int id = 0, hmd_idx = 0, controller_idx = 0;
	int i = 0;
	Index<String> visited_paths;
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
		
		#ifdef flagDEBUG
		WString ps(cur_dev->product_string);
		String pss = ps.ToString();
		LOG(i << ": " << HexStr(cur_dev) << ": " << HexStr(cur_dev->vendor_id) << ":" << HexStr(cur_dev->product_id) << ": " << path << ", " << pss);
		#endif
		
		if (cur_dev->vendor_id != MICROSOFT_VID) {
			cur_dev = cur_dev->next;
			continue;
		}
		
		if (cur_dev->product_id == HOLOLENS_SENSORS_PID) {
			DeviceDescription* desc = &list->devices[list->num_devices++];

			#ifdef flagDEBUG
			LOG("\tFound OpenHMD Windows Mixed Reality Driver");
			#endif
			
			strcpy(desc->driver, "OpenHMD Windows Mixed Reality Driver");
			strcpy(desc->vendor, "Microsoft");
			strcpy(desc->product, "HoloLens Sensors");

			desc->revision = 0;

			snprintf(desc->path, HMD_STR_SIZE, "%d", hmd_idx);

			desc->driver_ptr = driver;
			desc->id = id++;

			desc->device_class = HMD_DEVICE_CLASS_HMD;
			desc->device_flags = HMD_DEVICE_FLAGS_ROTATIONAL_TRACKING;

			hmd_idx++;
		}
		else if (cur_dev->product_id == MOTION_CONTROLLER_PID || cur_dev->product_id == MOTION_CONTROLLER_PID_SAMSUNG) {
			DeviceDescription* desc = &list->devices[list->num_devices++];
			
			#ifdef flagDEBUG
			LOG("\tFound controller " << String(desc->product));
			#endif
			
			strcpy(desc->driver, "OpenHMD Windows Mixed Reality Driver");
			strcpy(desc->vendor, "Microsoft");
			// "Motion controller - Left" or "Motion controller - Right"
			snprintf(desc->product, HMD_STR_SIZE, "%S", cur_dev->product_string);

			desc->revision = 0;

			snprintf(desc->path, HMD_STR_SIZE, "%d", controller_idx);

			desc->driver_ptr = driver;
			desc->id = id++;

			desc->device_class = HMD_DEVICE_CLASS_CONTROLLER;
			desc->device_flags = HMD_DEVICE_FLAGS_ROTATIONAL_TRACKING;
			if (strcmp(desc->product, "Motion controller - Left") == 0)
				desc->device_flags |= HMD_DEVICE_FLAGS_LEFT_CONTROLLER;
			else
				desc->device_flags |= HMD_DEVICE_FLAGS_RIGHT_CONTROLLER;

			controller_idx++;
		}

		cur_dev = cur_dev->next;
		i++;
	}

	hid_free_enumeration(devs);
}

static void DestroyDriver(Driver* drv)
{
	LOGD("shutting down Windows Mixed Reality driver");
	free(drv);
}

Driver* CreateWmrDriver(Context* ctx)
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

