#include "IfaceLib.h"

NAMESPACE_PLAN_BEGIN



PKG(Cfr, Cfr, c) {
	IfaceLib::Add(this);
	
	COLOR(26, 185, 123)
	DEPENDENCY(Local)
	
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
