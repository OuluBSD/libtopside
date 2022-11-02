#ifndef __LocalVR_CAMERA_H__
#define __LocalVR_CAMERA_H__


NAMESPACE_HMD_BEGIN


struct debug_stream;

#define OUVRT_TYPE_CAMERA		(ouvrt_camera_get_type())
#define OUVRT_CAMERA(obj)		(G_TYPE_CHECK_INSTANCE_CAST((obj), \
					 OUVRT_TYPE_CAMERA, OuvrtCamera))
#define OUVRT_IS_CAMERA(obj)		(G_TYPE_CHECK_INSTANCE_TYPE((obj), \
					 OUVRT_TYPE_CAMERA))
#define OUVRT_CAMERA_CLASS(klass)	(G_TYPE_CHECK_CLASS_CAST((klass), \
					 OUVRT_TYPE_CAMERA, OuvrtCameraClass))
#define OUVRT_IS_CAMERA_CLASS(klass)	(G_TYPE_CHECK_CLASS_TYPE((klass), \
					 OUVRT_TYPE_CAMERA))
#define OUVRT_CAMERA_GET_CLASS(obj)	(G_TYPE_INSTANCE_GET_CLASS((obj), \
					 OUVRT_TYPE_CAMERA, OuvrtCameraClass))

typedef struct _OuvrtCamera			OuvrtCamera;
typedef struct _OuvrtCameraClass	OuvrtCameraClass;

struct _OuvrtCamera {
	OuvrtDevice dev;
	OuvrtTracker *tracker;

	int width;
	int height;
	int framerate;
	mat3 camera_matrix;
	double dist_coeffs[5];
	int sizeimage;
	int sequence;
	struct debug_stream *debug;
};

struct _OuvrtCameraClass {
	OuvrtDeviceClass parent_class;
	int (*process_frame)(OuvrtCamera *camera, void *frame);
};

GType ouvrt_camera_get_type(void);


NAMESPACE_HMD_END


#endif
