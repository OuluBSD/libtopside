#include "IfaceLib.h"

NAMESPACE_PLAN_BEGIN



PKG(Camera, Cam, W) {
	IfaceLib::Add(this);
	
	COLOR(54, 157, 442)
	DEPENDENCY(ParallelLib)
	DEPENDENCY(IMedia)
	HAVE_IS_READY
	
	PKG_IFACE {
		//NATIVE_CLASS(Camera)
		//UTIL_CLASS()
		
	}
	
	NAMESPACE {
		CLASS(Camera) {
			NATIVE_INHERIT(Camera, dev)
			
			//METHOD1R(CreateWebcam, bool, NativeWebcam& this)
			//METHOD1V(ClearWebcam, NativeWebcam& this)
			
			
		}
	}
	
	VENDOR(V4L2OpenCV) {
		VENDOR_ENABLED_FLAG(OPENCV)
		VENDOR_ENABLED_FLAG(LINUX)
		//ENDOR_CLASS(Camera, void*)
		
		v->AddStruct("NativeCamera")
			.Add("fmts",			"Array<VideoSourceFormatT<V4L2Media>>")
			.Add("path",			"String")
			.Add("last_p",			"Packet")
			.Add("sw_frame",		"Image")
			.Add("open_pix_fmt",	"uint32")
			.Add("open_frame_sz",	"Size")
			.Add("cur_time",		"TimeStop")
			.Add("flag",			"RunningFlag")
			.Add("time_step",		"double")
			.Add("prev_frame_i",	"int")
			.Add("values",			"Vector<byte>")
			.Add("fmt",				"Format")
			.Add("filepath",		"String")
			.Add("sz",				"Size3")
			.Add("stride",			"int")
			.Add("vflip",			"bool")
			.Add("devmgr",			"V4L2_DeviceManager")
			.Add("cap",				"OpenCVCaptureDevice*")
		;
	}
	
	
	
	
}


NAMESPACE_PLAN_END
