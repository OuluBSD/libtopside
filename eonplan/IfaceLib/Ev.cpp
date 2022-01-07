#include "IfaceLib.h"

NAMESPACE_PLAN_BEGIN



PKG(Events, Ev, E) {
	IfaceLib::Add(this);
	
	COLOR(85, 42, 0)
	DEPENDENCY(Local)
	
	NAMESPACE {
		CLASS(Events) {
			
		}
	}
	
	PKG_IFACE {
		NATIVE_CLASS(Context)
		NATIVE_CLASS(Events)
		//UTIL_CLASS()
		
		FUNCTION1R(Poll, bool, UPP::CtrlEvent& e)
		FUNCTION0R(GetTickCount, uint32)
		FUNCTION1V(WaitEvent, int ms)
		FUNCTION0R(IsWaitingEvent, bool)
		
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
