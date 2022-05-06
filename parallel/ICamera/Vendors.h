// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!

#ifndef _ICamera_Vendors_h_
#define _ICamera_Vendors_h_

NAMESPACE_PARALLEL_BEGIN

#define CAM_CLS_LIST(x) \
	CAM_CLS(Camera, x) \



#define CAM_VNDR_LIST \
	CAM_VNDR(CamV4L2OpenCV) \



#define CAM_CLS(x, v) struct v##x;
#define CAM_VNDR(x) CAM_CLS_LIST(x)
CAM_VNDR_LIST
#undef CAM_VNDR
#undef CAM_CLS



#if (defined flagOPENCV) || (defined flagLINUX)
struct CamV4L2OpenCV {
	
	struct NativeCamera {
		Array<VideoSourceFormatT<V4L2Media>> fmts;
		String path;
		Packet last_p;
		Image sw_frame;
		uint32 open_pix_fmt;
		Size open_frame_sz;
		TimeStop cur_time;
		RunningFlag flag;
		double time_step;
		int prev_frame_i;
		Vector<byte> values;
		Format fmt;
		String filepath;
		Size3 sz;
		int stride;
		bool vflip;
		V4L2_DeviceManager devmgr;
		OpenCVCaptureDevice* cap;
	};
	
	struct Thread {
		
	};
	static Thread& Local() {thread_local static Thread t; return t;}
	
	#include "IfaceFuncs.inl"
	
};
#endif



NAMESPACE_PARALLEL_END


#endif

