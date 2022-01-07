#include "IfaceLib.h"

NAMESPACE_PLAN_BEGIN



PKG(VirtualReality, Vr, V) {
	IfaceLib::Add(this);
	
	COLOR(28, 85, 150)
	MAINFLAG(Screen)
	MAINFLAG(Vr)
	DEPENDENCY(Geometry)
	
	NAMESPACE {
		CLASS(MotionController) {
			
		}
		CLASS(MotionControllerSystem) {
			
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
	
	PKG_IFACE {
		NATIVE_CLASS(MotionController)
		NATIVE_CLASS(MotionControllerSystem)
		//UTIL_CLASS()
		
		FUNCTION1V(SendContinuousBuzzForDuration, float)
	}
	
	
	VENDOR(Holo) {
		
		
		
	}
	
	VENDOR(Ovr) {
		
		
		
	}
	
	VENDOR(Hmd) {
		
		
		
	}
	
}


NAMESPACE_PLAN_END
