#include "IfaceLib.h"

NAMESPACE_PLAN_BEGIN



PKG(VirtualReality, Vr, V) {
	IfaceLib::Add(this);
	
	COLOR(28, 85, 150)
	MAINFLAG(Screen)
	MAINFLAG(Vr)
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
	
	
	VENDOR(Holo) {
		
		
		
	}
	
	VENDOR(Ovr) {
		
		
		
	}
	
	VENDOR(Hmd) {
		
		
		
	}
	
}


NAMESPACE_PLAN_END
