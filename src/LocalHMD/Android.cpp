#include "LocalHMD.h"


NAMESPACE_HMD_BEGIN


#ifdef flagANDROID

typedef struct {
	Device base;
	Fusion sensor_fusion;

	//Android specific
	#ifdef __ANDROID__
    ASensorManager* sensor_mgr;
    const ASensor* accel_sensor;
    const ASensor* gyro_sensor;
    ASensorEventQueue* sensor_event_queue;
	AAssetManager* asset_mgr;
	short firstRun;
    #endif
} AndroidPrivateData;

//Forward decelerations
static void SetAndroidProperties(Device* device, DeviceProperties* props);
static void InitFusionAndroid(Fusion* me);
static void UpdateFusionAndroid(Fusion* me, float dt, const vec3* accel);


//Static variable for timeDelta;
static float timestamp;

//Android callback for the sensor event queue
static int AndroidSensorCallback(int fd, int events, void* data)
{
    AndroidPrivateData* priv = (AndroidPrivateData*)data;

    if (priv->accel_sensor != NULL)
    {
        ASensorEvent event;
        vec3 gyro;
        vec3 accel;
        vec3 mag;
        float lastevent_timestamp;
        while (ASensorEventQueue_getEvents(priv->sensor_event_queue, &event, 1) > 0)
        {
            if (event.type == ASENSOR_TYPE_ACCELEROMETER)
            {
                accel.x = event.acceleration.y;
                accel.y = -event.acceleration.x;
                accel.z = event.acceleration.z;
            }
            if (event.type == ASENSOR_TYPE_GYROSCOPE)
            {
                gyro.x = -event.data[1];
                gyro.y = event.data[0];
                gyro.z = event.data[2];
            }
            ///TODO: Implement mag when available
            mag.x = 0.0f;
            mag.y = 0.0f;
            mag.z = 0.0f;

            lastevent_timestamp = event.timestamp;
        }
            //apply data to the fusion
            float dT = 0.0f;
            if (timestamp != 0)
                dT= (lastevent_timestamp - timestamp) * (1.0f / 1000000000.0f);

            //Check if accelerometer only fallback is required
            if (!priv->gyro_sensor)
                UpdateFusionAndroid(&priv->sensor_fusion, dT, &accel);
            else
                UpdateFusion(&priv->sensor_fusion, dT, &gyro, &accel, &mag); //default

            timestamp = lastevent_timestamp;
    }
    return 1;
}

static void Android_UpdateDevice(Device* device)
{
    AndroidPrivateData* priv = (AndroidPrivateData*)device;

    ALooper* looper = ALooper_prepare(ALOOPER_PREPARE_ALLOW_NON_CALLBACKS);

    //We need this since during init the android_app state is not set yet
    if (priv->firstRun == 1)
    {
        priv->sensor_event_queue = ASensorManager_createEventQueue(priv->sensor_mgr,
                                    looper, ALOOPER_POLL_CALLBACK, AndroidSensorCallback, (void*)priv);

        // Start sensors in case this was not done already.
        if (priv->accel_sensor != NULL)
        {
            ASensorEventQueue_enableSensor(priv->sensor_event_queue, priv->accel_sensor);
            // We'd like to get 60 events per second (in us).
            ASensorEventQueue_setEventRate(priv->sensor_event_queue, priv->accel_sensor, (1000L/60)*1000);
        }
        if (priv->gyro_sensor != NULL)
        {
            ASensorEventQueue_enableSensor(priv->sensor_event_queue, priv->gyro_sensor);
            // We'd like to get 60 events per second (in us).
            ASensorEventQueue_setEventRate(priv->sensor_event_queue, priv->gyro_sensor, (1000L/60)*1000);
        }
        priv->firstRun = 0;
    }

    ALooper_pollAll(0, NULL, NULL, NULL);
}

static int Android_GetFloat(Device* device, FloatValue type, float* out)
{
	AndroidPrivateData* priv = (AndroidPrivateData*)device;

	switch(type){
                case HMD_ROTATION_QUAT: {
                    if (!priv->gyro_sensor)
                        *(quat*)out = priv->sensor_fusion.orient;
                    else {
                        // 90° rotation to restore the standard frame
                        quat rotated = {-M_SQRT2 / 2, 0, 0, M_SQRT2 / 2};
                        oquat_mult_me(&rotated, &priv->sensor_fusion.orient);
                        *(quat*)out = rotated;
                    }
                    break;
                }

		case HMD_POSITION_VECTOR:
			out[0] = out[1] = out[2] = 0;
			break;

		case HMD_DISTORTION_K:
			// TODO this should be set to the equivalent of no distortion
			memset(out, 0, sizeof(float) * 6);
			break;

		default:
			lhmd_set_error(priv->base.ctx, "invalid type given to GetFloat (%d)", type);
			return -1;
			break;
	}

	return 0;
}

static int Android_SetData(Device* device, DataValue type, void* in)
{
	AndroidPrivateData* priv = (AndroidPrivateData*)device;

	switch(type){
		case HMD_DRIVER_PROPERTIES: {
            SetAndroidProperties(device, (DeviceProperties*)in);
            break;
		}

		default:
			lhmd_set_error(priv->base.ctx, "invalid type given to SetData (%i)", type);
			return -1;
			break;
		}

		return 0;
}

static void Android_CloseDevice(Device* device)
{
	LOGD("closing Android device");
	free(device);
}

static Device* OpenDevice(Driver* driver, DeviceDescription* desc)
{
	AndroidPrivateData* priv = lhmd_alloc(driver->ctx, sizeof(AndroidPrivateData));
	if(!priv)
		return NULL;

	// Set default device properties
	SetDefaultDeviceProperties(&priv->base.properties);

	// Set device properties
	//TODO: Get information from android about device
	//TODO: Use profile string to set default for a particular device (Durovis, VR One etc)
	priv->base.properties.hsize = 0.149760f;
	priv->base.properties.vsize = 0.093600f;
	priv->base.properties.hres = 1280;
	priv->base.properties.vres = 800;
	priv->base.properties.lens_sep = 0.063500f;
	priv->base.properties.lens_vpos = 0.046800f;
	priv->base.properties.fov = DEG_TO_RAD(125.5144f);
	priv->base.properties.ratio = (1280.0f / 800.0f) / 2.0f;

	// calculate projection eye projection matrices from the device properties
	CalculateDefaultProjectionMatrices(&priv->base.properties);

	// set up device callbacks
	priv->base.update = Android_UpdateDevice;
	priv->base.close = Android_CloseDevice;
	priv->base.GetFloat = Android_GetFloat;
	priv->base.SetData = Android_SetData;

    //init Android sensors
    priv->sensor_mgr = ASensorManager_getInstance();
    priv->accel_sensor = ASensorManager_getDefaultSensor(priv->sensor_mgr,
            ASENSOR_TYPE_ACCELEROMETER);
    priv->gyro_sensor = ASensorManager_getDefaultSensor(priv->sensor_mgr,
            ASENSOR_TYPE_GYROSCOPE);

    priv->firstRun = 1; //need this since ASensorManager_createEventQueue requires a set android_app*

    //Check if accelerometer only fallback is required
    if (!priv->gyro_sensor)
        InitFusionAndroid(&priv->sensor_fusion);
    else {
        InitFusion(&priv->sensor_fusion); //Default when all sensors are available
        priv->sensor_fusion.flags = 0; // Disable the gravity
    }

	return (Device*)priv;
}

static void GetDeviceList(Driver* driver, DeviceList* list)
{
	DeviceDescription* desc = &list->devices[list->num_devices++];

	strcpy(desc->driver, "OpenHMD Generic Android Driver");
	strcpy(desc->vendor, "OpenHMD");
	strcpy(desc->product, "Android Device");

	strcpy(desc->path, "(none)");

	desc->device_class = HMD_DEVICE_CLASS_HMD;
	desc->device_flags = HMD_DEVICE_FLAGS_ROTATIONAL_TRACKING;

	desc->driver_ptr = driver;
}

static void DestroyDriver(Driver* drv)
{
	LOGD("shutting down Android driver");
	free(drv);
}

Driver* CreateAndroidDriver(Context* ctx)
{
	Driver* drv = lhmd_alloc(ctx, sizeof(Driver));
	if(!drv)
		return NULL;

	drv->GetDeviceList = GetDeviceList;
	drv->OpenDevice = OpenDevice;
	drv->destroy = DestroyDriver;
	drv->ctx = ctx;

	return drv;
}

// Android specific functions
static void UpdateFusionAndroid(Fusion* me, float dt, const vec3* accel)
{
	//avg raw accel data to smooth jitter, and normalise
	AddFilterQueue(&me->accel_fq, accel);
	vec3 accel_mean;
	GetMeanFilterQueue(&me->accel_fq, &accel_mean);
	vec3 acc_n = accel_mean;
	ovec3_normalize_me(&acc_n);


	//reference vectors for axis-angle
	vec3 xyzv[3] = {
		{1,0,0},
		{0,1,0},
		{0,0,1}
	};
	quat roll, pitch;

	//pitch is rot around x, based on gravity in z and y axes
	oquat_init_axis(&pitch, xyzv+0, atan2f(-acc_n.z, -acc_n.y));

	//roll is rot around z, based on gravity in x and y axes
	//note we need to invert the values when the device is upside down (y < 0) for proper results
	oquat_init_axis(&roll, xyzv+2, acc_n.y < 0 ? atan2f(-acc_n.x, -acc_n.y) : atan2f(acc_n.x, acc_n.y));



	quat or = {0,0,0,1};
	//order of applying is yaw-pitch-roll
	//yaw is not possible using only accel
	oquat_mult_me(&or, &pitch);
	oquat_mult_me(&or, &roll);

	me->orient = or;
}

//shorter buffers for frame smoothing
static void InitFusionAndroid(Fusion* me)
{
	memset(me, 0, sizeof(fusion));
	me->orient[3] = 1.0f;

	InitFilterQueue(&me->mag_fq, 10);
	InitFilterQueue(&me->accel_fq, 10);
	InitFilterQueue(&me->ang_vel_fq, 10);

	me->flags = FF_USE_GRAVITY;
	me->grav_gain = 0.05f;
}

static void SetAndroidProperties(Device* device, DeviceProperties* props)
{
    AndroidPrivateData* priv = (AndroidPrivateData*)device;

	priv->base.properties.hsize = props->hsize;
	priv->base.properties.vsize = props->vsize;
	priv->base.properties.hres = props->hres;
	priv->base.properties.vres = props->vres;
	priv->base.properties.lens_sep = props->lens_sep;
	priv->base.properties.lens_vpos = props->lens_vpos;
	priv->base.properties.fov = DEG_TO_RAD(props->fov);
	priv->base.properties.ratio = props->ratio;
}

static void SetAndroidProfile(Driver* driver, AndroidHmdProfile profile)
{
    switch(profile){
        case DROID_DUROVIS_OPEN_DIVE: break;
        case DROID_DUROVIS_DIVE_5: break;
        case DROID_DUROVIS_DIVE_7: break;
        case DROID_CARL_ZEISS_VRONE: break;
        case DROID_GOOGLE_CARDBOARD: break;
        case DROID_NONE:
        default: break;
    }
}

#endif


NAMESPACE_HMD_END

