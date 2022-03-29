#include "IfaceLib.h"

NAMESPACE_PLAN_BEGIN



PKG(Math, Math, m) {
	IfaceLib::Add(this);
	
	COLOR(14, 37, 142)
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
