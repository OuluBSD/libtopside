#include "IfaceLib.h"

NAMESPACE_PLAN_BEGIN



PKG(VirtualMachine, Vm, X) {
	IfaceLib::Add(this);
	
	COLOR(56, 170, 0)
	DEPENDENCY(ParallelLib)
	
	NAMESPACE {
		CLASS(VirtualMachine) {
			
		}
		CLASS(Thread) {
			
		}
	}
	
	PKG_IFACE {
		NATIVE_CLASS(VirtualMachine)
		NATIVE_CLASS(Thread)
		//UTIL_CLASS()
		
		FUNCTION1R(CreateVirtualMachine, bool, NativeVirtualMachine&)
		FUNCTION1V(ClearVirtualMachine, NativeVirtualMachine&)
		
		FUNCTION2R(CreateThread, bool, NativeVirtualMachine&, NativeThread&)
		FUNCTION1V(ClearThread, NativeThread&)
		
		FUNCTION4R(Run, bool, NativeThread&, String filepath, String script, const StringMap* args);
		FUNCTION1V(Stop, NativeThread&)
		FUNCTION1R(IsRunning, bool, NativeThread&)
		
	}
	
	
	VENDOR(Tos) {
		
	}
	
	
	
}


NAMESPACE_PLAN_END
