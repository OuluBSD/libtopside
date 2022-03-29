#include "IfaceLib.h"

NAMESPACE_PLAN_BEGIN



PKG(Event, Ev, E) {
	IfaceLib::Add(this);
	
	COLOR(85, 42, 0)
	DEPENDENCY(ParallelLib)
	
	PKG_IFACE {
		NATIVE_CLASS(Context)
		NATIVE_CLASS(SourceDevice)
		//UTIL_CLASS()
		
	}
	
	NAMESPACE {
		CLASS(SourceDevice) {
			NATIVE_INHERIT(SourceDevice, dev)
			
			METHOD2R(Poll, bool, NativeSourceDevice& this, UPP::CtrlEvent& e)
			METHOD1R(GetTickCount, uint32, NativeSourceDevice& this)
			METHOD2V(WaitEvent, NativeSourceDevice& this, int ms)
			METHOD1R(IsWaitingEvent, bool, NativeSourceDevice& this)
		}
	}
	
	
	VENDOR(Sdl) {
		
	}
	
	VENDOR(Glfw) {
		
	}
	
	VENDOR(X11) {
		
	}
	
	VENDOR(Win32) {
		
	}
	
	
}


NAMESPACE_PLAN_END
