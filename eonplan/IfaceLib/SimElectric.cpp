#include "IfaceLib.h"

// e.g. https://modelica.org, SPICE, etc.

NAMESPACE_PLAN_BEGIN



PKG(ElectricSimulator, Esim, E) {
	IfaceLib::Add(this);
	
	COLOR(226, 125, 223)
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
