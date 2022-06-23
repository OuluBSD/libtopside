#include "LocalHMD.h"


NAMESPACE_HMD_BEGIN


typedef struct {
	Device base;
	int id;
} DummyPrivateData;

static void Dummy_UpdateDevice(Device* device)
{
	
}

static int GetFloat(Device* device, FloatValue type, float* out)
{
	DummyPrivateData* priv = (DummyPrivateData*)device;

	switch(type){
	case HMD_ROTATION_QUAT:
		out[0] = out[1] = out[2] = 0;
		out[3] = 1.0f;
		break;

	case HMD_POSITION_VECTOR:
		if(priv->id == 0){
			// HMD
			out[0] = out[1] = out[2] = 0;
		}
		else if(priv->id == 1)
		{
			// Left Controller
			out[0] = -.5f;
			out[1] = out[2] = 0;
		}
		else
		{
			// Right Controller
			out[0] = .5f;
			out[1] = out[2] = 0;
		}
		break;

	case HMD_DISTORTION_K:
		// TODO this should be set to the equivalent of no distortion
		memset(out, 0, sizeof(float) * 6);
		break;
	
	case HMD_CONTROLS_STATE:
		out[0] = .1f;
		out[1] = 1.0f;
		break;

	default:
		lhmd_set_error(priv->base.ctx, "invalid type given to GetFloat (%ud)", type);
		return HMD_S_INVALID_PARAMETER;
		break;
	}

	return HMD_S_OK;
}

int Dummy_CloseDevice(Device* device)
{
	LOGD("closing dummy device");
	free(device);
	return 0;
}

static Device* OpenDevice(Driver* driver, DeviceDescription* desc)
{
	DummyPrivateData* priv = (DummyPrivateData*)AllocateFn(driver->ctx, "", sizeof(DummyPrivateData));
	if(!priv)
		return NULL;
	
	priv->id = desc->id;
	
	// Set default device properties
	SetDefaultDeviceProperties(&priv->base.properties);

	// Set device properties (imitates the rift values)
	priv->base.properties.hsize = 0.149760f;
	priv->base.properties.vsize = 0.093600f;
	priv->base.properties.hres = 1280;
	priv->base.properties.vres = 800;
	priv->base.properties.lens_sep = 0.063500f;
	priv->base.properties.lens_vpos = 0.046800f;
	priv->base.properties.fov = DEG_TO_RAD(125.5144f);
	priv->base.properties.ratio = (1280.0f / 800.0f) / 2.0f;
	
	// Some buttons and axes
	priv->base.properties.control_count = 2;
	priv->base.properties.controls_hints[0] = HMD_BUTTON_A;
	priv->base.properties.controls_hints[1] = HMD_MENU;
	priv->base.properties.controls_types[0] = HMD_ANALOG;
	priv->base.properties.controls_types[1] = HMD_DIGITAL;

	// calculate projection eye projection matrices from the device properties
	CalculateDefaultProjectionMatrices(&priv->base.properties);

	// set up device callbacks
	priv->base.Update = Dummy_UpdateDevice;
	priv->base.Close = Dummy_CloseDevice;
	priv->base.GetFloat = GetFloat;
	
	return (Device*)priv;
}

static void GetDeviceList(Driver* driver, DeviceList* list)
{
	int id = 0;
	DeviceDescription* desc;

	// HMD

	desc = &list->devices[list->num_devices++];

	strcpy(desc->driver, "OpenHMD Null Driver");
	strcpy(desc->vendor, "OpenHMD");
	strcpy(desc->product, "HMD Null Device");

	strcpy(desc->path, "(none)");

	desc->driver_ptr = driver;

	desc->device_flags = HMD_DEVICE_FLAGS_NULL_DEVICE | HMD_DEVICE_FLAGS_ROTATIONAL_TRACKING;
	desc->device_class = HMD_DEVICE_CLASS_HMD;

	desc->id = id++;

	// Left Controller
	
	desc = &list->devices[list->num_devices++];

	strcpy(desc->driver, "OpenHMD Null Driver");
	strcpy(desc->vendor, "OpenHMD");
	strcpy(desc->product, "Left Controller Null Device");

	strcpy(desc->path, "(none)");

	desc->driver_ptr = driver;

	desc->device_flags = HMD_DEVICE_FLAGS_NULL_DEVICE |
		HMD_DEVICE_FLAGS_POSITIONAL_TRACKING |
		HMD_DEVICE_FLAGS_ROTATIONAL_TRACKING |
		HMD_DEVICE_FLAGS_LEFT_CONTROLLER;

	desc->device_class = HMD_DEVICE_CLASS_CONTROLLER;

	desc->id = id++;
	
	// Right Controller
	
	desc = &list->devices[list->num_devices++];

	strcpy(desc->driver, "OpenHMD Null Driver");
	strcpy(desc->vendor, "OpenHMD");
	strcpy(desc->product, "Right Controller Null Device");

	strcpy(desc->path, "(none)");

	desc->driver_ptr = driver;

	desc->device_flags = HMD_DEVICE_FLAGS_NULL_DEVICE |
		HMD_DEVICE_FLAGS_POSITIONAL_TRACKING |
		HMD_DEVICE_FLAGS_ROTATIONAL_TRACKING |
		HMD_DEVICE_FLAGS_RIGHT_CONTROLLER;

	desc->device_class = HMD_DEVICE_CLASS_CONTROLLER;

	desc->id = id++;
}

static void DestroyDriver(Driver* drv)
{
	LOGD("shutting down dummy driver");
	free(drv);
}

Driver* CreateDummyDriver(Context* ctx)
{
	Driver* drv = (Driver*)AllocateFn(ctx, "", sizeof(Driver));
	if(!drv)
		return NULL;

	drv->GetDeviceList = GetDeviceList;
	drv->OpenDevice = OpenDevice;
	drv->GetDeviceList = GetDeviceList;
	drv->OpenDevice = OpenDevice;
	drv->Destroy = DestroyDriver;

	return drv;
}


NAMESPACE_HMD_END

