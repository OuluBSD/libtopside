#include "IfaceLib.h"

NAMESPACE_PLAN_BEGIN



PKG(StreamServer, Svr, R) {
	IfaceLib::Add(this);
	
	COLOR(28, 0, 42)
	DEPENDENCY(ParallelLib)
	
	NAMESPACE {
		CLASS(StreamServer) {
			
		}
	}
	
	PKG_IFACE {
		NATIVE_CLASS(StreamServer)
		//UTIL_CLASS()
		
		FUNCTION1R(CreateServerInstance, bool, NativeStreamServer&)
		FUNCTION1V(ClearServerInstance, NativeStreamServer&)
		
		FUNCTION2V(SetPort, NativeStreamServer&, int port)
		FUNCTION1R(Open, bool, NativeStreamServer&)
		FUNCTION1R(Close, bool, NativeStreamServer&)
		
	}
	
	
	
	
}


NAMESPACE_PLAN_END
