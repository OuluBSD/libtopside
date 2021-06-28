#ifndef _Multimedia_Capture_V4L2_h_
#define _Multimedia_Capture_V4L2_h_

#if HAVE_V4L2_CAP

NAMESPACE_ECS_BEGIN


class CaptureDevice_V4L2 : public MediaStream {
	
protected:
	RTTI_DECL1(CaptureDevice_V4L2, MediaStream)
	
	friend class V4L2_DeviceManager;
	
	static const int buf_size = 5000000;
	V4l2Capture* vid_cap = 0;
	
};



NAMESPACE_ECS_END


#endif
#endif
