#ifndef _LocalHMD_Public_h_
#define _LocalHMD_Public_h_


NAMESPACE_HMD_BEGIN


#ifdef _WIN32
	#ifdef DLL_EXPORT
		#define HMD_APIENTRY __cdecl
		#define HMD_APIENTRYDLL __declspec( dllexport )
	#else
		#ifdef HMD_STATIC
			#define HMD_APIENTRY __cdecl
			#define HMD_APIENTRYDLL
		#else
			#define HMD_APIENTRY __cdecl
			#define HMD_APIENTRYDLL __declspec( dllimport )
		#endif
	#endif
#else
	#define HMD_APIENTRY
	#define HMD_APIENTRYDLL __attribute__((visibility("default")))
#endif

// Maximum length of a string, including termination, in OpenHMD.
#define HMD_STR_SIZE 256

#undef Status

// Return status codes, used for all functions that can return an error.
typedef enum {
	HMD_S_OK = 0,
	HMD_S_UNKNOWN_ERROR = -1,
	HMD_S_INVALID_PARAMETER = -2,
	HMD_S_UNSUPPORTED = -3,
	HMD_S_INVALID_OPERATION = -4,
	
	// HMD_S_USER_RESERVED and below can be used for user purposes, such as errors within ohmd wrappers, etc.
	HMD_S_USER_RESERVED = -16384,
} Status;

// A collection of string value information types, used for getting information with GetListString().
typedef enum {
	HMD_VENDOR    = 0,
	HMD_PRODUCT   = 1,
	HMD_PATH      = 2,
} StringValue;

// A collection of string descriptions, used for getting strings with GetString().
typedef enum {
	HMD_GLSL_DISTORTION_VERT_SRC = 0,
	HMD_GLSL_DISTORTION_FRAG_SRC = 1,
	HMD_GLSL_330_DISTORTION_VERT_SRC = 2,
	HMD_GLSL_330_DISTORTION_FRAG_SRC = 3,
	HMD_GLSL_ES_DISTORTION_VERT_SRC = 4,
	HMD_GLSL_ES_DISTORTION_FRAG_SRC = 5,
} StringDescription;

// Standard controls. Note that this is not an index into the control state.
// Use HMD_CONTROL_TYPES to determine what function a control serves at a given index.
typedef enum {
	HMD_GENERIC        = 0,
	HMD_TRIGGER        = 1,
	HMD_TRIGGER_CLICK  = 2,
	HMD_SQUEEZE        = 3,
	HMD_MENU           = 4,
	HMD_HOME           = 5,
	HMD_ANALOG_X       = 6,
	HMD_ANALOG_Y       = 7,
	HMD_ANALOG_PRESS   = 8,
	HMD_BUTTON_A       = 9,
	HMD_BUTTON_B       = 10,
	HMD_BUTTON_X       = 11,
	HMD_BUTTON_Y       = 12,
	HMD_VOLUME_PLUS    = 13,
	HMD_VOLUME_MINUS   = 14,
	HMD_MIC_MUTE       = 15,
} ControlHint;

// Control type. Indicates whether controls are digital or analog.
typedef enum {
	HMD_DIGITAL = 0,
	HMD_ANALOG = 1
} ControlType;

// A collection of float value information types, used for getting and setting information with
// GetDeviceFloat() and SetDeviceFloat().
typedef enum {
	// float[4] (get): Absolute rotation of the device, in space, as a quaternion (x, y, z, w).
	HMD_ROTATION_QUAT                    =  1,
	
	// float[16] (get): A "ready to use" OpenGL style 4x4 matrix with a modelview matrix for the
	// left eye of the HMD.
	HMD_LEFT_EYE_GL_MODELVIEW_MATRIX     =  2,
	// float[16] (get): A "ready to use" OpenGL style 4x4 matrix with a modelview matrix for the
	// right eye of the HMD.
	HMD_RIGHT_EYE_GL_MODELVIEW_MATRIX    =  3,
	
	// float[16] (get): A "ready to use" OpenGL style 4x4 matrix with a projection matrix for the
	// left eye of the HMD.
	HMD_LEFT_EYE_GL_PROJECTION_MATRIX    =  4,
	// float[16] (get): A "ready to use" OpenGL style 4x4 matrix with a projection matrix for the
	// right eye of the HMD.
	HMD_RIGHT_EYE_GL_PROJECTION_MATRIX   =  5,
	
	// float[3] (get): A 3-D vector representing the absolute position of the device, in space.
	HMD_POSITION_VECTOR                  =  6,
	
	// float[1] (get): Physical width of the device screen in metres.
	HMD_SCREEN_HORIZONTAL_SIZE           =  7,
	// float[1] (get): Physical height of the device screen in metres.
	HMD_SCREEN_VERTICAL_SIZE             =  8,
	
	// float[1] (get): Physical separation of the device lenses in metres.
	HMD_LENS_HORIZONTAL_SEPARATION       =  9,
	// float[1] (get): Physical vertical position of the lenses in metres.
	HMD_LENS_VERTICAL_POSITION           = 10,
	
	// float[1] (get): Physical field of view for the left eye in degrees.
	HMD_LEFT_EYE_FOV                     = 11,
	// float[1] (get): Physical display aspect ratio for the left eye screen.
	HMD_LEFT_EYE_ASPECT_RATIO            = 12,
	// float[1] (get): Physical field of view for the left right in degrees.
	HMD_RIGHT_EYE_FOV                    = 13,
	// float[1] (get): Physical display aspect ratio for the right eye screen.
	HMD_RIGHT_EYE_ASPECT_RATIO           = 14,
	
	// float[1] (get, set): Physical interpupillary distance of the user in metres.
	HMD_EYE_IPD                          = 15,
	
	// float[1] (get, set): Z-far value for the projection matrix calculations (i.e. drawing distance).
	HMD_PROJECTION_ZFAR                  = 16,
	// float[1] (get, set): Z-near value for the projection matrix calculations (i.e. close clipping distance).
	HMD_PROJECTION_ZNEAR                 = 17,
	
	// float[6] (get): Device specific distortion value.
	HMD_DISTORTION_K                     = 18,
	
	/**
	 * float[10] (set): Perform sensor fusion on values from external sensors.
	 *
	 * Values are: dt (time since last update in seconds) X, Y, Z gyro, X, Y, Z accelerometer and X, Y, Z magnetometer.
	 **/
	HMD_EXTERNAL_SENSOR_FUSION           = 19,
	
	// float[4] (get): Universal shader distortion coefficients (PanoTools model <a,b,c,d>.
	HMD_UNIVERSAL_DISTORTION_K           = 20,
	
	// float[3] (get): Universal shader aberration coefficients (post warp scaling <r,g,b>.
	HMD_UNIVERSAL_ABERRATION_K           = 21,
	
	// float[HMD_CONTROL_COUNT] (get): Get the state of the device's controls.
	HMD_CONTROLS_STATE                = 22,
	
} FloatValue;

// A collection of int value information types used for getting information with GetDeviceInt().
typedef enum {
	// int[1] (get, lhmd_geti()): Physical horizontal resolution of the device screen.
	HMD_SCREEN_HORIZONTAL_RESOLUTION     =  0,
	// int[1] (get, lhmd_geti()): Physical vertical resolution of the device screen.
	HMD_SCREEN_VERTICAL_RESOLUTION       =  1,
	
	// int[1] (get, lhmd_geti()/GetListInt()): Gets the class of the device. See: DeviceClass.
	HMD_DEVICE_CLASS                     =  2,
	// int[1] (get, lhmd_geti()/GetListInt()): Gets the flags of the device. See: DeviceFlags.
	HMD_DEVICE_FLAGS                     =  3,
	
	// int[1] (get, lhmd_geti()): Get the number of analog and digital controls of the device.
	HMD_CONTROL_COUNT                    =  4,
	
	// int[HMD_CONTROL_COUNT] (get, lhmd_geti()): Get what function controls serve.
	HMD_CONTROLS_HINTS                   =  5,
	
	// int[HMD_CONTROL_COUNT] (get, lhmd_geti()): Get whether controls are digital or analog.
	HMD_CONTROLS_TYPES                   =  6,
} IntValue;

// A collection of data information types used for setting information with lhmd_SetData().
typedef enum {
	// void* (set): Set void* data for use in the internal drivers.
	HMD_DRIVER_DATA		= 0,
	/**
	 * DeviceProperties* (set):
	 * Set the device properties based on the DeviceProperties struct for use in the internal drivers.
	 *
	 * This can be used to fill in information about the device internally, such as Android, or for setting profiles.
	 **/
	HMD_DRIVER_PROPERTIES	= 1,
} DataValue;

typedef enum {
	// int[1] (set, default: 1): Set this to 0 to prevent OpenHMD from creating background threads to do automatic device ticking.
	// Call lhmd_update(); must be called frequently, at least 10 times per second, if the background threads are disabled.
	HMD_IDS_AUTOMATIC_UPDATE = 0,
} IntSettings;

// Device classes.
typedef enum {
	// HMD device.
	HMD_DEVICE_CLASS_HMD        = 0,
	// Controller device.
	HMD_DEVICE_CLASS_CONTROLLER = 1,
	// Generic tracker device.
	HMD_DEVICE_CLASS_GENERIC_TRACKER = 2,
} DeviceClass;

// Device flags.
typedef enum {
	// Device is a null (dummy) device.
	HMD_DEVICE_FLAGS_NULL_DEVICE         = 1,
	HMD_DEVICE_FLAGS_POSITIONAL_TRACKING = 2,
	HMD_DEVICE_FLAGS_ROTATIONAL_TRACKING = 4,
	HMD_DEVICE_FLAGS_LEFT_CONTROLLER     = 8,
	HMD_DEVICE_FLAGS_RIGHT_CONTROLLER    = 16,
} DeviceFlags;

// An opaque pointer to a context structure.
struct Context;

// An opaque pointer to a structure representing a device, such as an HMD.
struct Device;

// An opaque pointer to a structure representing arguments for a device.
struct DeviceSettings;


struct Thread;
struct Mutex;

/**
 * Create an OpenHMD context.
 *
 * @return a pointer to an allocated Context on success or NULL if it fails.
 **/
Context* CreateContext();

/**
 * Destroy an OpenHMD context.
 *
 * DestroyContext de-initializes and de-allocates an OpenHMD context allocated with CreateContext.
 * All devices associated with the context are automatically closed.
 *
 * @param ctx The context to destroy.
 **/
void DestroyContext(Context* ctx);

/**
 * Get the last error as a human readable string.
 *
 * If a function taking a context as an argument (Context "methods") returns non-successfully,
 * a human readable error message describing what went wrong can be retrieved with this function.
 *
 * @param ctx The context to retrieve the error message from.
 * @return a pointer to the error message.
 **/
const char* GetContextError(Context* ctx);

/**
 * Update a context.
 *
 * Update the values for the devices handled by a context.
 *
 * If background threads are disabled, this performs tasks like pumping events from the device. The exact details
 * are up to the driver but try to call it quite frequently.
 * Once per frame in a "game loop" should be sufficient.
 * If OpenHMD is handled in a background thread in your program, calling UpdateContext and then sleeping for 10-20 ms
 * is recommended.
 *
 * @param ctx The context that needs updating.
 **/
void UpdateContext(Context* ctx);

/**
 * Probe for devices.
 *
 * Probes for and enumerates supported devices attached to the system.
 *
 * @param ctx A context with no currently open devices.
 * @return the number of devices found on the system.
 **/
int ProbeContext(Context* ctx);

/**
 * Get string from openhmd.
 *
 * Gets a string from OpenHMD. This is where non-device specific strings reside.
 * This is where the distortion shader sources can be retrieved.
 *
 * @param type The name of the string to fetch. One of HMD_GLSL_DISTORTION_FRAG_SRC, and HMD_GLSL_DISTORTION_FRAG_SRC.
 * @param out The location to return a const char*
 * @return 0 on success, <0 on failure.
 **/
int GetString(StringDescription type, const char** out);

/**
 * Get device description from enumeration list index.
 *
 * Gets a human readable device description string from a zero indexed enumeration index
 * between 0 and (max - 1), where max is the number ProbeContext returned
 * (i.e. if ProbeContext returns 3, valid indices are 0, 1 and 2).
 * The function can return three types of data. The vendor name, the product name and
 * a driver specific path where the device is attached.
 *
 * ProbeContext must be called before calling GetListString.
 *
 * @param ctx A (probed) context.
 * @param index An index, between 0 and the value returned from ProbeContext.
 * @param type The type of data to fetch. One of HMD_VENDOR, HMD_PRODUCT and HMD_PATH.
 * @return a string with a human readable device name.
 **/
const char* GetListString(Context* ctx, int index, StringValue type);


/**
 * Get integer value from enumeration list index.
 *
 *
 *
 * ProbeContext must be called before calling GetListString.
 *
 * @param ctx A (probed) context.
 * @param index An index, between 0 and the value returned from ProbeContext.
 * @param type What type of value to retrieve, IntValue section for more information.
 * @return 0 on success, <0 on failure.
 **/
int GetListInt(Context* ctx, int index, IntValue type, int* out);

/**
 * Open a device.
 *
 * Opens a device from a zero indexed enumeration index between 0 and (max - 1)
 * where max is the number ProbeContext returned (i.e. if ProbeContext returns 3,
 * valid indices are 0, 1 and 2).
 *
 * ProbeContext must be called before calling OpenListDevice.
 *
 * @param ctx A (probed) context.
 * @param index An index, between 0 and the value returned from ProbeContext.
 * @return a pointer to an Device, which represents a hardware device, such as an HMD.
 **/
Device* OpenListDevice(Context* ctx, int index);

/**
 * Open a device with additional settings provided.
 *
 * Opens a device from a zero indexed enumeration index between 0 and (max - 1)
 * where max is the number ProbeContext returned (i.e. if ProbeContext returns 3,
 * valid indices are 0, 1 and 2).
 *
 * ProbeContext must be called before calling OpenListDevice.
 *
 * @param ctx A (probed) context.
 * @param index An index, between 0 and the value returned from ProbeContext.
 * @param settings A pointer to a device settings struct.
 * @return a pointer to an Device, which represents a hardware device, such as an HMD.
 **/
Device* OpenListDeviceSettings(Context* ctx, int index, DeviceSettings* settings);

/**
 * Specify int settings in a device settings struct.
 *
 * @param settings The device settings struct to set values to.
 * @param key The specefic setting you wish to set.
 * @param value A pointer to an int or int array (containing the expected number of elements) with the value(s) you wish to set.
 **/
Status SetDeviceSettingsInt(DeviceSettings* settings, IntSettings key, const int* val);

/**
 * Create a device settings instance.
 *
 * @param ctx A pointer to a valid Context.
 * @return a pointer to an allocated Context on success or NULL if it fails.
 **/
DeviceSettings* CreateDeviceSettings(Context* ctx);

/**
 * Destroy a device settings instance.
 *
 * @param ctx The device settings instance to destroy.
 **/
void DestroyDeviceSettings(DeviceSettings* settings);

/**
 * Close a device.
 *
 * Closes a device opened by OpenListDevice. Note that DestroyContext automatically closes any open devices
 * associated with the context being destroyed.
 *
 * @param device The open device.
 * @return 0 on success, <0 on failure.
 **/
int CloseDevice(Device* device);

/**
 * Get a floating point value from a device.
 *
 *
 * @param device An open device to retrieve the value from.
 * @param type What type of value to retrieve, see FloatValue section for more information.
 * @param[out] out A pointer to a float, or float array where the retrieved value should be written.
 * @return 0 on success, <0 on failure.
 **/
int GetDeviceFloat(Device* device, FloatValue type, float* out);

/**
 * Set a floating point value for a device.
 *
 * @param device An open device to set the value in.
 * @param type What type of value to set, see FloatValue section for more information.
 * @param in A pointer to a float, or float array where the new value is stored.
 * @return 0 on success, <0 on failure.
 **/
int SetDeviceFloat(Device* device, FloatValue type, const float* in);

/**
 * Get an integer value from a device.
 *
 * @param device An open device to retrieve the value from.
 * @param type What type of value to retrieve, IntValue section for more information.
 * @param[out] out A pointer to an integer, or integer array where the retrieved value should be written.
 * @return 0 on success, <0 on failure.
 **/
int GetDeviceInt(Device* device, IntValue type, int* out);

/**
 * Set an integer value for a device.
 *
 * @param device An open device to set the value in.
 * @param type What type of value to set, see FloatValue section for more information.
 * @param in A pointer to a int, or int array where the new value is stored.
 * @return 0 on success, <0 on failure.
 **/
int SetDeviceInt(Device* device, IntValue type, const int* in);

/**
 * Set an void* data value for a device.
 *
 * @param device An open device to set the value in.
 * @param type What type of value to set, see FloatValue section for more information.
 * @param in A pointer to the void* casted object.
 * @return 0 on success, <0 on failure.
 **/
int SetDeviceData(Device* device, DataValue type, const void* in);

/**
 * Get the library version.
 *
 * @param major Major version.
 * @param minor Minor version.
 * @param patch Patch version.
 **/
void GetVersion(int* out_major, int* out_minor, int* out_patch);

/**
 * Check that the library is compatible with the required version.
 *
 * @param major Required major version.
 * @param minor Required minor version.
 * @param patch Required patch version.
 * @return OMHD_S_OK if the version is compatible or HMD_S_UNSUPPORTED if it's not.
 **/
Status RequireVersion(int major, int minor, int patch);

/**
 * Sleep for the given amount of seconds.
 *
 * @param time Time to sleep in seconds.
 **/
void SleepSeconds(double time);


NAMESPACE_HMD_END


#endif
