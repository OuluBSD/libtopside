#include "IfaceLib.h"

NAMESPACE_PLAN_BEGIN



PKG(OperatingSystem, Os, O) {
	IfaceLib::Add(this);
	
	COLOR(114, 37, 142)
	DEPENDENCY(ParallelLib)
	
	NAMESPACE {
		CLASS(MessageBus) {
			
		}
		CLASS(ProcessManager) {
			
		}
		CLASS(DesktopManager) {
			
		}
	}
	
	PKG_IFACE {
		NATIVE_CLASS(MessageBus)
		//UTIL_CLASS()
		
		FUNCTION1R(CreateMessageBus, bool, NativeMessageBus&)
		FUNCTION1V(ClearMessageBus, NativeMessageBus&)
		
	}
	
}


NAMESPACE_PLAN_END
