#include "IfaceLib.h"

NAMESPACE_PLAN_BEGIN



PKG(Finance, Fin, F) {
	IfaceLib::Add(this);
	
	COLOR(226, 85, 123)
	DEPENDENCY(ParallelLib)
	
	NAMESPACE {
		CLASS(System) {
			
		}
	}
	
	PKG_IFACE {
		NATIVE_CLASS(System)
		//UTIL_CLASS()
		
		FUNCTION1R(CreateSystem, bool, NativeSystem&)
		FUNCTION1V(ClearSystem, NativeSystem&)
		
	}
	
}


NAMESPACE_PLAN_END
