#include "IfaceLib.h"

NAMESPACE_PLAN_BEGIN



PKG(AvFile, AV, a) {
	IfaceLib::Add(this);
	
	COLOR(214, 57, 42)
	DEPENDENCY(Local)
	
	NAMESPACE {
		CLASS(AVFile) {
			
		}
	}
	
	PKG_IFACE {
		NATIVE_CLASS(AVFile)
		NATIVE_CLASS(Process)
		//UTIL_CLASS()
		
		FUNCTION1R(CreateAVFile, bool, NativeAVFile&)
		FUNCTION1V(ClearAVFile, NativeAVFile&)
		
	}
	
}


NAMESPACE_PLAN_END
