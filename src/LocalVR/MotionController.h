#ifndef __LocalVR_MOTION_CONTROLLER_H__
#define __LocalVR_MOTION_CONTROLLER_H__


NAMESPACE_HMD_BEGIN


#define OUVRT_TYPE_MOTION_CONTROLLER (ouvrt_motion_controller_get_type())
G_DECLARE_FINAL_TYPE(OuvrtMotionController, ouvrt_motion_controller, \
		     OUVRT, MOTION_CONTROLLER, OuvrtDevice)

OuvrtDevice *motion_controller_new(const char *devnode);


NAMESPACE_HMD_END


#endif
