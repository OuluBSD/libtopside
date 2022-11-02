#ifndef __LocalVR_HOLOLENS_CAMERA_H__
#define __LocalVR_HOLOLENS_CAMERA_H__


NAMESPACE_HMD_BEGIN


G_BEGIN_DECLS

#define OUVRT_TYPE_HOLOLENS_CAMERA (ouvrt_hololens_camera_get_type())
G_DECLARE_FINAL_TYPE(OuvrtHoloLensCamera, ouvrt_hololens_camera, \
		     OUVRT, HOLOLENS_CAMERA, OuvrtCameraV4L2)

OuvrtDevice *hololens_camera_new(const char *devnode);

G_END_DECLS


NAMESPACE_HMD_END


#endif
