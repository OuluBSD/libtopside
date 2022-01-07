#include "IfaceLib.h"

NAMESPACE_PLAN_BEGIN



PKG(Crypt, Cry, C) {
	IfaceLib::Add(this);
	
	COLOR(54, 57, 42)
	DEPENDENCY(Local)
	
	NAMESPACE {
		CLASS(Crypt) {
			
		}
	}
	
	PKG_IFACE {
		NATIVE_CLASS(Crypt)
		//UTIL_CLASS()
		
		FUNCTION1R(CreateNativeCrypt, bool, NativeCrypt&)
		FUNCTION1V(ClearNativeCrypt, NativeCrypt&)
		
		FUNCTION3V(Encrypt, NativeCrypt&, const Vector<byte>& in, Vector<byte>& out)
		FUNCTION3V(Decrypt, NativeCrypt&, const Vector<byte>& in, Vector<byte>& out)
		
	}
	
	
	
	
}


NAMESPACE_PLAN_END
