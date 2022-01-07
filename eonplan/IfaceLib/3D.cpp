#include "IfaceLib.h"

NAMESPACE_PLAN_BEGIN



PKG(Three, Thr, H) {
	IfaceLib::Add(this);
	
	COLOR(54, 157, 242)
	DEPENDENCY(Local)
	
	NAMESPACE {
		CLASS(Model) {
			
		}
	}
	
	PKG_IFACE {
		NATIVE_CLASS(Model)
		//UTIL_CLASS()
		
		FUNCTION1R(CreateModel, bool, NativeModel&)
		FUNCTION1V(ClearModel, NativeModel&)
		
	}
	
}


NAMESPACE_PLAN_END
