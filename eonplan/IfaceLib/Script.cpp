#include "IfaceLib.h"

NAMESPACE_PLAN_BEGIN



PKG(Script, Scr, S) {
	IfaceLib::Add(this);
	
	COLOR(56, 127, 255)
	DEPENDENCY(Local)
	
	NAMESPACE {
		CLASS(Runner) {
			
		}
		CLASS(Thread) {
			
		}
	}
	
	PKG_IFACE {
		NATIVE_CLASS(Runner)
		NATIVE_CLASS(Thread)
		//UTIL_CLASS()
		
		FUNCTION1R(CreateRunner, bool, NativeRunner&)
		FUNCTION1V(ClearRunner, NativeRunner&)
		
		FUNCTION2R(CreateThread, bool, NativeRunner&, NativeThread&)
		FUNCTION1V(ClearThread, NativeThread&)
		
		FUNCTION4R(Run, bool, NativeThread&, String filepath, String script, const StringMap* args);
		FUNCTION1V(Stop, NativeThread&)
		FUNCTION1R(IsRunning, bool, NativeThread&)
		
	}
	
	
	VENDOR(Esc) {
		
	}
	
	VENDOR(Python) {
		
	}
	
	VENDOR(Duktape) {
		
	}
	
	
}


NAMESPACE_PLAN_END
