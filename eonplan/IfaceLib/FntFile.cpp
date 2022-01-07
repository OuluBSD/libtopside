#include "IfaceLib.h"

NAMESPACE_PLAN_BEGIN



PKG(Font, Fnt, F) {
	IfaceLib::Add(this);
	
	COLOR(54, 54, 54)
	DEPENDENCY(Local)
	
	NAMESPACE {
		CLASS(Font) {
			
		}
	}
	
	PKG_IFACE {
		NATIVE_CLASS(Font)
		//UTIL_CLASS()
		
		FUNCTION1R(CreateFont, bool, NativeFont&)
		FUNCTION1V(ClearFont, NativeFont&)
		
	}
	
	
	
	
}


NAMESPACE_PLAN_END
