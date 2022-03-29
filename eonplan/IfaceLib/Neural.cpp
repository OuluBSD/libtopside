#include "IfaceLib.h"

NAMESPACE_PLAN_BEGIN



PKG(Neural, Nrl, N) {
	IfaceLib::Add(this);
	
	COLOR(226, 85, 0)
	DEPENDENCY(ParallelLib)
	
	NAMESPACE {
		CLASS(Network) {
			
		}
	}
	
	PKG_IFACE {
		NATIVE_CLASS(Network)
		//UTIL_CLASS()
		
		FUNCTION1R(CreateNetwork, bool, NativeNetwork&)
		FUNCTION1V(ClearNetwork, NativeNetwork&)
		
	}
	
}


NAMESPACE_PLAN_END
