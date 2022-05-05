#include "IfaceLib.h"

NAMESPACE_PLAN_BEGIN



PKG(Volumetric, Vol, V) {
	IfaceLib::Add(this);
	
	COLOR(28, 85, 0)
	DEPENDENCY(ParallelLib)
	HAVE_IS_READY
	
	PKG_IFACE {
		//NATIVE_CLASS(StaticSource)
		//UTIL_CLASS()
		
	}
	
	NAMESPACE {
		CLASS(StaticSource) {
			NATIVE_INHERIT(StaticSource, dev)
			
		}
	}
	
	VENDOR(RawByte) {
		VENDOR_ENABLED_FLAG(LINUX)
		VENDOR_ENABLED_FLAG(FREEBSD)
		VENDOR_CLASS(StaticSource, void*)
		
		v->AddStruct("NativeStaticSource")
			.Add("values",		"Vector<byte>")
			.Add("fmt",			"Format")
			.Add("filepath",	"String")
			.Add("sz",			"Size3")
			.Add("stride",		"int")
			.Add("vflip",		"bool")
		;
	}
	
	
	
}


NAMESPACE_PLAN_END
