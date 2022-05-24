#include "IfaceLib.h"

NAMESPACE_PLAN_BEGIN



PKG(VR, Vr, V) {
	IfaceLib::Add(this);
	
	COLOR(28, 85, 150)
	MAINFLAG(Screen)
	MAINFLAG(Vr)
	DEPENDENCY(ParallelLib)
	DEPENDENCY(Geometry)
	
	PKG_IFACE {
		NATIVE_CLASS(MotionController)
		NATIVE_CLASS(MotionControllerSystem)
		//UTIL_CLASS()
		
	}
	
	NAMESPACE {
		CLASS(MotionController) {
			NATIVE_INHERIT(MotionController, ctrl)
			
			METHOD2V(SendContinuousBuzzForDuration, NativeMotionController& this, float)
		}
		CLASS(MotionControllerSystem) {
			NATIVE_INHERIT(MotionControllerSystem, sys)
			
		}
		CLASS(AppView) {
			
		}
		CLASS(CameraResources) {
			
		}
		CLASS(ControllerModelCache) {
			
		}
		CLASS(DeviceResources) {
			
		}
		CLASS(HolographicRenderer) {
			
		}
		CLASS(HolographicScene) {
			
		}
		CLASS(SpatialInteractionSystem) {
			
		}
		CLASS(Renderer) {
			
		}
	}
	
	
	VENDOR(Fake) {
		VENDOR_ENABLED_FLAG(OGL)
		
		
		
	}
	
	VENDOR(Holo) {
		VENDOR_ENABLED_FLAG(UWP)
		
		
		
	}
	
	VENDOR(Ovr) {
		VENDOR_ENABLED_FLAG2(OGL, OVR)
		
		
		
	}
	
	VENDOR(Hmd) {
		VENDOR_ENABLED_FLAG2(OGL, OHMD)
		
		
		
	}
	
}


NAMESPACE_PLAN_END
