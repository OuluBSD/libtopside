#ifndef __LocalVR_HOLOLENS_CAMERA2_H__
#define __LocalVR_HOLOLENS_CAMERA2_H__


NAMESPACE_HMD_BEGIN


G_BEGIN_DECLS

#define OUVRT_TYPE_HOLOLENS_CAMERA2 (ouvrt_hololens_camera2_get_type())
G_DECLARE_FINAL_TYPE(OuvrtHoloLensCamera2, ouvrt_hololens_camera2, OUVRT, \
		     HOLOLENS_CAMERA2, OuvrtUSBDevice)

OuvrtDevice *hololens_camera2_new(const char *devnode);

G_END_DECLS


NAMESPACE_HMD_END


#endif
