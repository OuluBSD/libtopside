#include "IfaceLib.h"

NAMESPACE_PLAN_BEGIN



PKG(StaticServer, Svt, T) {
	IfaceLib::Add(this);
	
	COLOR(28, 42, 0)
	DEPENDENCY(Local)
	
	NAMESPACE {
		CLASS(ServerInstance) {
			
		}
	}
	
	PKG_IFACE {
		NATIVE_CLASS(ServerInstance)
		//UTIL_CLASS()
		
		FUNCTION1R(CreateServerInstance, bool, NativeServerInstance&)
		FUNCTION1V(ClearServerInstance, NativeServerInstance&)
		
		FUNCTION2V(SetRootPath, NativeServerInstance&, String path)
		FUNCTION2V(SetPort, NativeServerInstance&, int port)
		FUNCTION1R(Open, bool, NativeServerInstance&)
		FUNCTION1R(Close, bool, NativeServerInstance&)
		
	}
	
	
	
	
}


NAMESPACE_PLAN_END
