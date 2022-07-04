#ifndef __LocalVR_HOLOLENS_IMU_H__
#define __LocalVR_HOLOLENS_IMU_H__


NAMESPACE_HMD_BEGIN


/*#include <glib.h>
#include <glib-object.h>

#include "device.h"*/

#define OUVRT_TYPE_HOLOLENS_IMU (ouvrt_hololens_imu_get_type())
G_DECLARE_FINAL_TYPE(OuvrtHoloLensIMU, ouvrt_hololens_imu, \
		     OUVRT, HOLOLENS_IMU, OuvrtDevice)

OuvrtDevice *hololens_imu_new(const char *devnode);


NAMESPACE_HMD_END


#endif
