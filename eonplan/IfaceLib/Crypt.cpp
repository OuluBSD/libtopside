#include "IfaceLib.h"

NAMESPACE_PLAN_BEGIN



PKG(Crypt, Cry, C) {
	IfaceLib::Add(this);
	
	COLOR(54, 57, 42)
	DEPENDENCY(ParallelLib)
	
	PKG_IFACE {
		NATIVE_CLASS(Crypt)
		//UTIL_CLASS()
		
		
	}
	
	NAMESPACE {
		CLASS(Crypt) {
			NATIVE_INHERIT(Crypt, dev)
			
			METHOD1R(CreateNativeCrypt, bool, NativeCrypt& this)
			METHOD1V(ClearNativeCrypt, NativeCrypt& this)
			
			METHOD3V(Encrypt, NativeCrypt&, const Vector<byte>& in, Vector<byte>& out)
			METHOD3V(Decrypt, NativeCrypt&, const Vector<byte>& in, Vector<byte>& out)
			
		}
	}
	
	
	
	
}


NAMESPACE_PLAN_END
