#include "IfaceLib.h"

NAMESPACE_PLAN_BEGIN



PKG(NetFile, Nef, n) {
	IfaceLib::Add(this);
	
	COLOR(214, 57, 42)
	DEPENDENCY(Local)
	
	NAMESPACE {
		CLASS(NetFile) {
			
		}
	}
	
	PKG_IFACE {
		NATIVE_CLASS(NetFile)
		NATIVE_CLASS(Process)
		//UTIL_CLASS()
		
		FUNCTION1R(CreateNetFile, bool, NativeNetFile&)
		FUNCTION1V(ClearNetFile, NativeNetFile&)
		
	}
	
}


NAMESPACE_PLAN_END
