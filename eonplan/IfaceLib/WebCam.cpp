#include "IfaceLib.h"

NAMESPACE_PLAN_BEGIN



PKG(Webcam, Cam, W) {
	IfaceLib::Add(this);
	
	COLOR(54, 157, 442)
	DEPENDENCY(Local)
	
	NAMESPACE {
		CLASS(Webcam) {
			
		}
	}
	
	PKG_IFACE {
		NATIVE_CLASS(Webcam)
		//UTIL_CLASS()
		
		FUNCTION1R(CreateWebcam, bool, NativeWebcam&)
		FUNCTION1V(ClearWebcam, NativeWebcam&)
		
	}
	
	
	
	
}


NAMESPACE_PLAN_END
