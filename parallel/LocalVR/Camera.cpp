#include "LocalVR.h"


NAMESPACE_HMD_BEGIN



G_DEFINE_TYPE(OuvrtCamera, ouvrt_camera, OUVRT_TYPE_DEVICE)

static void ouvrt_camera_class_init(G_GNUC_UNUSED OuvrtCameraClass *klass)
{
}

/*
 * Initializes common fields of the camera structure.
 *
 * Returns 0 on success, negative values on error.
 */
static void ouvrt_camera_init(OuvrtCamera *camera)
{
	camera->dev.type = DEVICE_TYPE_CAMERA;
}


NAMESPACE_HMD_END

