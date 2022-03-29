#include "IfaceLib.h"

NAMESPACE_PLAN_BEGIN



PKG(Webcam, Cam, W) {
	IfaceLib::Add(this);
	
	COLOR(54, 157, 442)
	DEPENDENCY(ParallelLib)
	
	PKG_IFACE {
		NATIVE_CLASS(Webcam)
		//UTIL_CLASS()
		
	}
	
	NAMESPACE {
		CLASS(Webcam) {
			NATIVE_INHERIT(Webcam, dev)
			
			METHOD1R(CreateWebcam, bool, NativeWebcam& this)
			METHOD1V(ClearWebcam, NativeWebcam& this)
		}
	}
	
	
	
	
}


NAMESPACE_PLAN_END
