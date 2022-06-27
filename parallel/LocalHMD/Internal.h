#ifndef _LocalHMD_Internal_h_
#define _LocalHMD_Internal_h_


NAMESPACE_HMD_BEGIN

#define DRIVER_WMR 1
#define DRIVER_PSVR 1

#ifdef flagANDROID
#define DRIVER_ANDROID 1
#endif


#define HMD_MAX_DEVICES 16

#define HMD_MAX(_a, _b) ((_a) > (_b) ? (_a) : (_b))
#define HMD_MIN(_a, _b) ((_a) < (_b) ? (_a) : (_b))

#define HMD_STRINGIFY(_what) #_what

#define HMD_VERSION_MAJOR 0
#define HMD_VERSION_MINOR 3
#define HMD_VERSION_PATCH 0

struct Context;

typedef struct Driver Driver;

typedef struct {
	char driver[HMD_STR_SIZE];
	char vendor[HMD_STR_SIZE];
	char product[HMD_STR_SIZE];
	char path[HMD_STR_SIZE];
	int revision;
	int id;
	uint32 device_flags; // DeviceFlags
	DeviceClass device_class;
	Driver* driver_ptr;
} DeviceDescription;

typedef struct {
	int num_devices;
	DeviceDescription devices[HMD_MAX_DEVICES];
} DeviceList;

struct Driver {
	void (*GetDeviceList)(Driver* driver, DeviceList* list);
	Device*(*OpenDevice)(Driver* driver, DeviceDescription* desc);
	void (*Destroy)(Driver* driver);
	Context* ctx;
};

typedef struct {
	int hres;
	int vres;
	int control_count;
	int controls_hints[64];
	int controls_types[64];
	
	float hsize;
	float vsize;
	
	float lens_sep;
	float lens_vpos;
	
	float fov;
	float ratio;
	
	float ipd;
	float zfar;
	float znear;
	
	int accel_only; //bool-like for setting acceleration only fallback (android driver)
	
	mat4 proj_left; // adjusted projection matrix for left screen
	mat4 proj_right; // adjusted projection matrix for right screen
	float universal_distortion_k[4]; //PanoTools lens distiorion model [a,b,c,d]
	float universal_aberration_k[3]; //post-warp per channel scaling [r,g,b]
} DeviceProperties;

struct DeviceSettings {
	bool automatic_update;
};

struct Device {
	DeviceProperties properties;
	
	quat rotation_correction;
	vec3 position_correction;
	
	int (*GetFloat)(Device* device, FloatValue type, float* out);
	int (*SetFloat)(Device* device, FloatValue type, const float* in);
	int (*SetInt)(Device* device, IntValue type, const int* in);
	int (*SetData)(Device* device, DataValue type, const void* in);
	
	void (*Update)(Device* device);
	int (*Close)(Device* device);
	
	Context* ctx;
	
	DeviceSettings settings;
	
	int active_device_idx; // index into Device->active_devices[]
	
	quat rotation;
	vec3 position;
};


struct Context {
	Driver* drivers[16];
	int num_drivers;
	
	DeviceList list;
	
	Device* active_devices[256];
	int num_active_devices;
	
	Thread* update_thread;
	Mutex* update_mutex;
	
	bool update_request_quit;
	
	uint64 monotonic_ticks_per_sec;
	
	char error_msg[HMD_STR_SIZE];
};

// helper functions
void InitMonotonic(Context* ctx);
uint64 GetMonotonic(Context* ctx);
uint64 GetMonotonicPerSec(Context* ctx);
uint64 ConvertMonotonic(uint64 ticks, uint64 srcTicksPerSecond, uint64 dstTicksPerSecond);
void SetDefaultDeviceProperties(DeviceProperties* props);
void CalculateDefaultProjectionMatrices(DeviceProperties* props);
void SetUniversalDistortionK(DeviceProperties* props, float a, float b, float c, float d);
void SetUniversalAberrationK(DeviceProperties* props, float r, float g, float b);

// drivers
Driver* CreateDummyDriver(Context* ctx);
Driver* CreateWmrDriver(Context* ctx);
Driver* CreatePsvrDriver(Context* ctx);
Driver* CreateAndroidDriver(Context* ctx);


NAMESPACE_HMD_END


#endif
