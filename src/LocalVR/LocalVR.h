#ifndef _LocalVR_LocalVR_h_
#define _LocalVR_LocalVR_h_

// ouvrt commit: 446354fae08f9851658e92d31fe422d21fd3c47f

#include <stdbool.h>
#include <glib.h>
#include <glib-object.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <linux/videodev2.h>
#include <linux/hidraw.h>
#include <poll.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <time.h>
#include <sys/fcntl.h>
#include <asm/byteorder.h>
#include <libusb.h>
#include <math.h>
#include <float.h>

#include <LocalHMD/LocalHMD.h>

#define flagDEBUG_SERVER 1

#include "Buttons.h"
#include "BlobWatch.h"
#include "Maths.h"
#include "Imu.h"
#include "TrackingModel.h"
#include "Leds.h"
#include "Debug.h"
#include "Flicker.h"
#include "Tracker.h"
#include "Device.h"
#include "Camera.h"
#include "CameraV4l2.h"
#include "HololensCamera.h"
#include "HololensHidReports.h"
#include "HololensImu.h"
#include "UsbDevice.h"
#include "HololensCamera2.h"
#include "UsbIds.h"
#include "HidRaw.h"
#include "OpenCV.h"
#include "MotionController.h"
#include "Daemon.h"
#include "Telemetry.h"
#include "Lighthouse.h"

#endif
