#ifndef _LocalHMD_LocalHMD_h_
#define _LocalHMD_LocalHMD_h_

// openhmd commit: dfac0203376552c5274976c42f0757b31310c483

#include <string.h>
#include <wchar.h>
#ifdef flagFREEBSD
	#include <hidapi/hidapi_libusb.h>
#elif defined flagLINUX
	#include <hidapi/hidapi.h>
#endif
#include <assert.h>
#include <limits.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

#ifdef flagPOSIX
	#include <time.h>
	#include <sys/time.h>
	#include <pthread.h>
	#ifdef __CYGWIN__
		#define CLOCK_MONOTONIC (clockid_t)4
	#endif
	#ifndef _POSIX_C_SOURCE
		#define _POSIX_C_SOURCE 199309L
	#endif
#endif

#ifdef __ANDROID__
	#include <android/sensor.h>
	#include <poll.h>
	#include <pthread.h>
	#include <sched.h>
	#include <android/configuration.h>
	#include <android/looper.h>
	#include <android/native_activity.h>
#endif


#include <Geometry/Geometry.h>


#define NAMESPACE_HMD_BEGIN		namespace TS { namespace HMD {
#define NAMESPACE_HMD_END		}}


#include "Public.h"
#include "Internal.h"
#include "Log.h"
#include "Math.h"
#include "Fusion.h"
#include "Platform.h"
#include "Utils.h"
#include "Shaders.h"
#include "Wmr.h"
#include "Android.h"
#include "Psvr.h"
#include "ConfigKey.h"
#include "Miniz.h"
#include "NxJson.h"
#include "System.h"
#include "Daemon.h"


#endif
