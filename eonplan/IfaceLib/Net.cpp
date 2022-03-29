#include "IfaceLib.h"

NAMESPACE_PLAN_BEGIN



PKG(Internet, Net, N) {
	IfaceLib::Add(this);
	
	COLOR(56, 170, 0)
	DEPENDENCY(ParallelLib)
	
	PKG_IFACE {
		NATIVE_CLASS(Socket)
		//UTIL_CLASS()
		
		
	}
	
	NAMESPACE {
		CLASS(Socket) {
			NATIVE_INHERIT(Socket, sock)
			
			METHOD1R(CreateSocket, bool, NativeSocket& this)
			METHOD1V(ClearSocket, NativeSocket& this)
		}
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
