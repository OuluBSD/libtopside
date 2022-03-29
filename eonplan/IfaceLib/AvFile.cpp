#include "IfaceLib.h"

NAMESPACE_PLAN_BEGIN



PKG(AvFile, AV, a) {
	IfaceLib::Add(this);
	
	COLOR(214, 57, 42)
	DEPENDENCY(ParallelLib)
	
	PKG_IFACE {
		NATIVE_CLASS(AVFile)
		NATIVE_CLASS(Process)
		//UTIL_CLASS()
		
	}
	
	NAMESPACE {
		CLASS(AVFile) {
			NATIVE_INHERIT(AVFile, file)
			
			METHOD1R(CreateAVFile, bool, NativeAVFile& this)
			METHOD1V(ClearAVFile, NativeAVFile& this)
		}
	}
	
}


NAMESPACE_PLAN_END
