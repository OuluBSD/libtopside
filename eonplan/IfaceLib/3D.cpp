#include "IfaceLib.h"

NAMESPACE_PLAN_BEGIN



PKG(Three, Thr, H) {
	IfaceLib::Add(this);
	
	COLOR(54, 157, 242)
	DEPENDENCY(ParallelLib)
	
	PKG_IFACE {
		NATIVE_CLASS(Model)
		//UTIL_CLASS()
		
	}
	
	NAMESPACE {
		CLASS(Model) {
			NATIVE_INHERIT(Model, model)
			
			METHOD1R(CreateModel, bool, NativeModel& this)
			METHOD1V(ClearModel, NativeModel& this)
		}
	}
	
}


NAMESPACE_PLAN_END
