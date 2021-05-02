#ifndef _Multimedia_Capture_V4L2_h_
#define _Multimedia_Capture_V4L2_h_


NAMESPACE_OULU_BEGIN


class CaptureDevice_V4L2 : public MediaInputStream {
	
protected:
	friend class V4L2_DeviceManager;
	
	static const int buf_size = 5000000;
	V4l2Capture* vid_cap = 0;
	
};



NAMESPACE_OULU_END


#endif
