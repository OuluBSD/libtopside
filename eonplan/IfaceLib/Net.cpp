#include "IfaceLib.h"

NAMESPACE_PLAN_BEGIN



PKG(Internet, Net, N) {
	IfaceLib::Add(this);
	
	COLOR(56, 170, 0)
	DEPENDENCY(Local)
	
	NAMESPACE {
		CLASS(Socket) {
			
		}
	}
	
	PKG_IFACE {
		NATIVE_CLASS(Socket)
		//UTIL_CLASS()
		
		FUNCTION1R(CreateSocket, bool, NativeSocket&)
		FUNCTION1V(ClearSocket, NativeVirtualMachine&)
		
	}
	
	
	VENDOR(Posix) {
		
	}
	
	VENDOR(Win32) {
		
	}
	
	VENDOR(Enet) {
		
	}
	
	VENDOR(NullSerial) {
		
	}
	
	
	
}


NAMESPACE_PLAN_END
