#include "LocalHMD.h"


NAMESPACE_HMD_BEGIN


// Running automatic updates at 1000 Hz
#define AUTOMATIC_UPDATE_SLEEP (1.0 / 1000.0)

Context* CreateContext(void)
{
	Context* ctx = (Context*)calloc(1, sizeof(Context));
	if(!ctx){
		LOGE("could not allocate RAM for context");
		return NULL;
	}

	InitMonotonic(ctx);

#if 0

#if DRIVER_OCULUS_RIFT
	ctx->drivers[ctx->num_drivers++] = lhmd_create_oculus_rift_drv(ctx);
#endif

#if DRIVER_OCULUS_RIFT_S
	ctx->drivers[ctx->num_drivers++] = lhmd_create_oculus_rift_s_drv(ctx);
#endif

#if DRIVER_DEEPOON
	ctx->drivers[ctx->num_drivers++] = lhmd_create_deepoon_drv(ctx);
#endif

#if DRIVER_HTC_VIVE
	ctx->drivers[ctx->num_drivers++] = lhmd_create_htc_vive_drv(ctx);
#endif

#if DRIVER_NOLO
	ctx->drivers[ctx->num_drivers++] = lhmd_create_nolo_drv(ctx);
#endif

#if DRIVER_XGVR
	ctx->drivers[ctx->num_drivers++] = lhmd_create_xgvr_drv(ctx);
#endif

#if DRIVER_VRTEK
	ctx->drivers[ctx->num_drivers++] = lhmd_create_vrtek_drv(ctx);
#endif

#if DRIVER_EXTERNAL
	ctx->drivers[ctx->num_drivers++] = lhmd_create_external_drv(ctx);
#endif

#endif

#if DRIVER_WMR
	ctx->drivers[ctx->num_drivers++] = CreateWmrDriver(ctx);
#endif

#if DRIVER_PSVR
	ctx->drivers[ctx->num_drivers++] = CreatePsvrDriver(ctx);
#endif

#if DRIVER_ANDROID
	ctx->drivers[ctx->num_drivers++] = CreateAndroidDriver(ctx);
#endif

	// add dummy driver last to make it the lowest priority
	ctx->drivers[ctx->num_drivers++] = CreateDummyDriver(ctx);

	ctx->update_request_quit = false;

	return ctx;
}

void DestroyContext(Context* ctx)
{
	ctx->update_request_quit = true;

	for(int i = 0; i < ctx->num_active_devices; i++){
		ctx->active_devices[i]->Close(ctx->active_devices[i]);
	}

	for(int i = 0; i < ctx->num_drivers; i++){
		ctx->drivers[i]->Destroy(ctx->drivers[i]);
	}

	if(ctx->update_thread){
		DestroyThread(ctx->update_thread);
		DestroyMutex(ctx->update_mutex);
	}

	free(ctx);
}

void UpdateContext(Context* ctx)
{
	for(int i = 0; i < ctx->num_active_devices; i++){
		Device* dev = ctx->active_devices[i];
		if(!dev->settings.automatic_update && dev->Update)
			dev->Update(dev);

		EnterMutex(ctx->update_mutex);
		dev->GetFloat(dev, HMD_POSITION_VECTOR, (float*)&dev->position);
		dev->GetFloat(dev, HMD_ROTATION_QUAT, (float*)&dev->rotation);
		LeaveMutex(ctx->update_mutex);
	}
}

const char* GetContextError(Context* ctx)
{
	return ctx->error_msg;
}

int ProbeContext(Context* ctx)
{
	memset(&ctx->list, 0, sizeof(DeviceList));
	for(int i = 0; i < ctx->num_drivers; i++){
		ctx->drivers[i]->GetDeviceList(ctx->drivers[i], &ctx->list);
	}

	return ctx->list.num_devices;
}

int GetString(StringDescription type, const char ** out)
{
	switch(type){
	case HMD_GLSL_DISTORTION_VERT_SRC:
		*out = distortion_vert;
		return HMD_S_OK;
	case HMD_GLSL_DISTORTION_FRAG_SRC:
		*out = distortion_frag;
		return HMD_S_OK;
	case HMD_GLSL_330_DISTORTION_VERT_SRC:
		*out = distortion_vert_330;
		return HMD_S_OK;
	case HMD_GLSL_330_DISTORTION_FRAG_SRC:
		*out = distortion_frag_330;
		return HMD_S_OK;
	case HMD_GLSL_ES_DISTORTION_VERT_SRC:
		*out = distortion_vert_es;
		return HMD_S_OK;
	case HMD_GLSL_ES_DISTORTION_FRAG_SRC:
		*out = distortion_frag_es;
		return HMD_S_OK;
	default:
		return HMD_S_UNSUPPORTED;
	}
}

const char* GetListString(Context* ctx, int index, StringValue type)
{
	if(index >= ctx->list.num_devices)
		return NULL;

	switch(type){
	case HMD_VENDOR:
		return ctx->list.devices[index].vendor;
	case HMD_PRODUCT:
		return ctx->list.devices[index].product;
	case HMD_PATH:
		return ctx->list.devices[index].path;
	default:
		return NULL;
	}
}

int GetListInt(Context* ctx, int index, IntValue type, int* out)
{
	if(index >= ctx->list.num_devices)
		return HMD_S_INVALID_PARAMETER;

	switch(type){
	case HMD_DEVICE_CLASS:
		*out = ctx->list.devices[index].device_class;
		return HMD_S_OK;

	case HMD_DEVICE_FLAGS:
		*out = ctx->list.devices[index].device_flags;
		return HMD_S_OK;

	default:
		return HMD_S_INVALID_PARAMETER;
	}
}

static unsigned int lhmd_update_thread(void* arg)
{
	Context* ctx = (Context*)arg;

	while(!ctx->update_request_quit)
	{
		EnterMutex(ctx->update_mutex);

		for(int i = 0; i < ctx->num_active_devices; i++){
			if(ctx->active_devices[i]->settings.automatic_update && ctx->active_devices[i]->Update)
				ctx->active_devices[i]->Update(ctx->active_devices[i]);
		}

		LeaveMutex(ctx->update_mutex);

		SleepSeconds(AUTOMATIC_UPDATE_SLEEP);
	}

	return 0;
}

static void lhmd_set_up_update_thread(Context* ctx)
{
	if(!ctx->update_thread){
		ctx->update_mutex = CreateMutex(ctx);
		ctx->update_thread = CreateThread(ctx, lhmd_update_thread, ctx);
	}
}

Device* OpenListDeviceSettings(Context* ctx, int index, DeviceSettings* settings)
{
	EnterMutex(ctx->update_mutex);

	if(index >= 0 && index < ctx->list.num_devices){

		DeviceDescription* desc = &ctx->list.devices[index];
		Driver* driver = (Driver*)desc->driver_ptr;
		Device* device = driver->OpenDevice(driver, desc);

		if (device == NULL) {
			lhmd_set_error(ctx, "Could not open device with index: %d, check device permissions?", index);
			LeaveMutex(ctx->update_mutex);
			return NULL;
		}

		device->rotation_correction[3] = 1;

		device->settings = *settings;

		device->ctx = ctx;
		device->active_device_idx = ctx->num_active_devices;
		ctx->active_devices[ctx->num_active_devices++] = device;

		LeaveMutex(ctx->update_mutex);

		if(device->settings.automatic_update)
			lhmd_set_up_update_thread(ctx);

		return device;
	}

	LeaveMutex(ctx->update_mutex);

	lhmd_set_error(ctx, "no device with index: %d", index);
	return NULL;
}

Device* OpenListDevice(Context* ctx, int index)
{
	DeviceSettings settings;

	settings.automatic_update = true;

	return OpenListDeviceSettings(ctx, index, &settings);
}

int CloseDevice(Device* device)
{
	EnterMutex(device->ctx->update_mutex);

	Context* ctx = device->ctx;
	int idx = device->active_device_idx;

	memmove(ctx->active_devices + idx, ctx->active_devices + idx + 1,
		sizeof(Device*) * (ctx->num_active_devices - idx - 1));

	device->Close(device);

	ctx->num_active_devices--;

	for(int i = idx; i < ctx->num_active_devices; i++)
		ctx->active_devices[i]->active_device_idx--;

	LeaveMutex(ctx->update_mutex);

	return HMD_S_OK;
}

static int GetDeviceFloat_unp(Device* device, FloatValue type, float* out)
{
	switch(type){
	case HMD_LEFT_EYE_GL_MODELVIEW_MATRIX: {
			quat rot = device->rotation;
			oquat_mult_me(&rot, &device->rotation_correction);
			mat4 central_view, eye_shift, result;
			omat4_init_look_at(&central_view, &rot, &device->position);
			omat4_init_Translate(&eye_shift, +(device->properties.ipd / 2.0f), 0.0f, 0.0f);
			omat4_mult(&eye_shift, &central_view, &result);
			omat4_transpose(&result, (mat4*)out);
			return HMD_S_OK;
		}
	case HMD_RIGHT_EYE_GL_MODELVIEW_MATRIX: {
			quat rot = device->rotation;
			oquat_mult_me(&rot, &device->rotation_correction);
			mat4 central_view, eye_shift, result;
			omat4_init_look_at(&central_view, &rot, &device->position);
			omat4_init_Translate(&eye_shift, -(device->properties.ipd / 2.0f), 0.0f, 0.0f);
			omat4_mult(&eye_shift, &central_view, &result);
			omat4_transpose(&result, (mat4*)out);
			return HMD_S_OK;
		}
	case HMD_LEFT_EYE_GL_PROJECTION_MATRIX:
		omat4_transpose(&device->properties.proj_left, (mat4*)out);
		return HMD_S_OK;
	case HMD_RIGHT_EYE_GL_PROJECTION_MATRIX:
		omat4_transpose(&device->properties.proj_right, (mat4*)out);
		return HMD_S_OK;

	case HMD_SCREEN_HORIZONTAL_SIZE:
		*out = device->properties.hsize;
		return HMD_S_OK;
	case HMD_SCREEN_VERTICAL_SIZE:
		*out = device->properties.vsize;
		return HMD_S_OK;

	case HMD_LENS_HORIZONTAL_SEPARATION:
		*out = device->properties.lens_sep;
		return HMD_S_OK;
	case HMD_LENS_VERTICAL_POSITION:
		*out = device->properties.lens_vpos;
		return HMD_S_OK;

	case HMD_RIGHT_EYE_FOV:
	case HMD_LEFT_EYE_FOV:
		*out = device->properties.fov;
		return HMD_S_OK;
	case HMD_RIGHT_EYE_ASPECT_RATIO:
	case HMD_LEFT_EYE_ASPECT_RATIO:
		*out = device->properties.ratio;
		return HMD_S_OK;

	case HMD_EYE_IPD:
		*out = device->properties.ipd;
		return HMD_S_OK;

	case HMD_PROJECTION_ZFAR:
		*out = device->properties.zfar;
		return HMD_S_OK;
	case HMD_PROJECTION_ZNEAR:
		*out = device->properties.znear;
		return HMD_S_OK;

	case HMD_ROTATION_QUAT:
	{
		*(quat*)out = device->rotation;

		oquat_mult_me((quat*)out, &device->rotation_correction);
		return HMD_S_OK;
	}
	case HMD_POSITION_VECTOR:
	{
		*(vec3*)out = device->position;
		for(int i = 0; i < 3; i++)
			out[i] += device->position_correction.data[i];
		
		return HMD_S_OK;
	}
	case HMD_UNIVERSAL_DISTORTION_K: {
		for (int i = 0; i < 4; i++) {
			out[i] = device->properties.universal_distortion_k[i];
		}
		return HMD_S_OK;
	}
	case HMD_UNIVERSAL_ABERRATION_K: {
		for (int i = 0; i < 3; i++) {
			out[i] = device->properties.universal_aberration_k[i];
		}
		return HMD_S_OK;
	}
	default:
		return device->GetFloat(device, type, out);
	}
}

int GetDeviceFloat(Device* device, FloatValue type, float* out)
{
	EnterMutex(device->ctx->update_mutex);
	int ret = GetDeviceFloat_unp(device, type, out);
	LeaveMutex(device->ctx->update_mutex);

	return ret;
}

static int SetDeviceFloat_unp(Device* device, FloatValue type, const float* in)
{
	switch(type){
	case HMD_EYE_IPD:
		device->properties.ipd = *in;
		return HMD_S_OK;
	case HMD_PROJECTION_ZFAR:
		device->properties.zfar = *in;
		return HMD_S_OK;
	case HMD_PROJECTION_ZNEAR:
		device->properties.znear = *in;
		return HMD_S_OK;
	case HMD_ROTATION_QUAT:
		{
			// adjust rotation correction
			quat q;
			int ret = device->GetFloat(device, HMD_ROTATION_QUAT, (float*)&q);

			if(ret != 0){
				return ret;
			}

			oquat_diff(&q, (quat*)in, &device->rotation_correction);
			return HMD_S_OK;
		}
	case HMD_POSITION_VECTOR:
		{
			// adjust position correction
			vec3 v;
			int ret = device->GetFloat(device, HMD_POSITION_VECTOR, (float*)&v);

			if(ret != 0){
				return ret;
			}

			for(int i = 0; i < 3; i++)
				device->position_correction.data[i] = in[i] - v.data[i];

			return HMD_S_OK;
		}
	case HMD_EXTERNAL_SENSOR_FUSION:
		{
			if(device->SetFloat == NULL)
				return HMD_S_UNSUPPORTED;

			return device->SetFloat(device, type, in);
		}
	default:
		return HMD_S_INVALID_PARAMETER;
	}
}

int SetDeviceFloat(Device* device, FloatValue type, const float* in)
{
	EnterMutex(device->ctx->update_mutex);
	int ret = SetDeviceFloat_unp(device, type, in);
	LeaveMutex(device->ctx->update_mutex);

	return ret;
}

int GetDeviceInt(Device* device, IntValue type, int* out)
{
	ASSERT(device);
	switch(type){
		case HMD_SCREEN_HORIZONTAL_RESOLUTION:
			*out = device->properties.hres;
			return HMD_S_OK;

		case HMD_SCREEN_VERTICAL_RESOLUTION:
			*out = device->properties.vres;
			return HMD_S_OK;
		
		case HMD_CONTROL_COUNT:
			*out = device->properties.control_count;
			return HMD_S_OK;

		case HMD_CONTROLS_TYPES:
			memcpy(out, device->properties.controls_types, device->properties.control_count * sizeof(int));
			return HMD_S_OK;
		
		case HMD_CONTROLS_HINTS:
			memcpy(out, device->properties.controls_hints, device->properties.control_count * sizeof(int));
			return HMD_S_OK;

		default:
				return HMD_S_INVALID_PARAMETER;
	}
}

int SetDeviceInt(Device* device, IntValue type, const int* in)
{
	switch(type){
	default:
		return HMD_S_INVALID_PARAMETER;
	}
}


static int SetDeviceData_unp(Device* device, DataValue type, const void* in)
{
    switch(type){
    case HMD_DRIVER_DATA:
			device->SetData(device, HMD_DRIVER_DATA, in);
			return HMD_S_OK;

    case HMD_DRIVER_PROPERTIES:
			device->SetData(device, HMD_DRIVER_PROPERTIES, in);
			return HMD_S_OK;

    default:
      return HMD_S_INVALID_PARAMETER;
    }
}

int SetDeviceData(Device* device, DataValue type, const void* in)
{
	EnterMutex(device->ctx->update_mutex);
	int ret = SetDeviceData_unp(device, type, in);
	LeaveMutex(device->ctx->update_mutex);

	return ret;
}

Status SetDeviceSettingsInt(DeviceSettings* settings, IntSettings key, const int* val)
{
	switch(key){
	case HMD_IDS_AUTOMATIC_UPDATE:
		settings->automatic_update = val[0] == 0 ? false : true;
		return HMD_S_OK;

	default:
		return HMD_S_INVALID_PARAMETER;
	}
}

DeviceSettings* CreateDeviceSettings(Context* ctx)
{
	return (DeviceSettings*)lhmd_alloc(ctx, sizeof(DeviceSettings));
}

void DestroyDeviceSettings(DeviceSettings* settings)
{
	free(settings);
}

void* AllocateFn(Context* ctx, const char* e_msg, size_t size)
{
	void* ret = calloc(1, size);
	if(!ret)
		lhmd_set_error(ctx, "%s", e_msg);
	return ret;
}

void SetDefaultDeviceProperties(DeviceProperties* props)
{
	props->ipd = 0.061f;
	props->znear = 0.1f;
	props->zfar = 1000.0f;
	SetUniversalDistortionK(props, 0, 0, 0, 1);
	SetUniversalAberrationK(props, 1.0, 1.0, 1.0);
}

void CalculateDefaultProjectionMatrices(DeviceProperties* props)
{
	mat4 proj_base; // base projection matrix

	// Calculate where the lens is on each screen,
	// and with the given value offset the projection matrix.
	float screen_center = props->hsize / 4.0f;
	float lens_shift = screen_center - props->lens_sep / 2.0f;
	// XXX: on CV1, props->hsize > props->lens_sep / 2.0,
	// I am not sure about the implications, but just taking the absolute
	// value of the offset seems to work.
	float proj_offset = fabs(4.0f * lens_shift / props->hsize);

	// Setup the base projection matrix. Each eye mostly have the
	// same projection matrix with the exception of the offset.
	omat4_init_perspective(&proj_base, props->fov, props->ratio, props->znear, props->zfar);

	// Setup the two adjusted projection matrices. Each is setup to deal
	// with the fact that the lens is not in the center of the screen.
	// These matrices only change of the hardware changes, so static.
	mat4 translate;

	omat4_init_Translate(&translate, proj_offset, 0, 0);
	omat4_mult(&translate, &proj_base, &props->proj_left);

	omat4_init_Translate(&translate, -proj_offset, 0, 0);
	omat4_mult(&translate, &proj_base, &props->proj_right);
}

void SetUniversalDistortionK(DeviceProperties* props, float a, float b, float c, float d)
{
	props->universal_distortion_k[0] = a;
	props->universal_distortion_k[1] = b;
	props->universal_distortion_k[2] = c;
	props->universal_distortion_k[3] = d;
}

void SetUniversalAberrationK(DeviceProperties* props, float r, float g, float b)
{
	props->universal_aberration_k[0] = r;
	props->universal_aberration_k[1] = g;
	props->universal_aberration_k[2] = b;
}

uint64 GetMonotonicPerSec(Context* ctx)
{
	return ctx->monotonic_ticks_per_sec;
}

// Grabbed from druntime, good thing it's BOOST v1.0 as well.

uint64 ConvertMonotonic(uint64 ticks, uint64 srcTicksPerSecond, uint64 dstTicksPerSecond)
{
	// This would be more straightforward with floating point arithmetic,
	// but we avoid it here in order to avoid the rounding errors that that
	// introduces. Also, by splitting out the units in this way, we're able
	// to deal with much larger values before running into problems with
	// integer overflow.
	return ticks / srcTicksPerSecond * dstTicksPerSecond +
		ticks % srcTicksPerSecond * dstTicksPerSecond / srcTicksPerSecond;
}

void GetVersion(int* out_major, int* out_minor, int* out_patch)
{
	*out_major = HMD_VERSION_MAJOR;
	*out_minor = HMD_VERSION_MINOR;
	*out_patch = HMD_VERSION_PATCH;
}

Status RequireVersion(int major, int minor, int patch)
{
	int curr_major, curr_minor, curr_patch;
	GetVersion(&curr_major, &curr_minor, &curr_patch);

	if(curr_major != major){
		// require same major version
		return HMD_S_UNSUPPORTED;
	}

	if(curr_minor == minor){
		// check patch version if the required minor version matches current
		if(curr_patch < patch){
			// fail is patch is too low
			return HMD_S_UNSUPPORTED;
		}
	}
	else if(curr_minor < minor)
	{
		// fail if minor is too low
		return HMD_S_UNSUPPORTED;
	}

	return HMD_S_OK;
}


NAMESPACE_HMD_END

