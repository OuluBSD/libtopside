// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!

#ifndef _IVolumetric_Vendors_h_
#define _IVolumetric_Vendors_h_

NAMESPACE_PARALLEL_BEGIN

#define VOL_CLS_LIST(x) \
	VOL_CLS(StaticSource, x) \



#define VOL_VNDR_LIST \
	VOL_VNDR(VolRawByte) \



#define VOL_CLS(x, v) struct v##x;
#define VOL_VNDR(x) VOL_CLS_LIST(x)
VOL_VNDR_LIST
#undef VOL_VNDR
#undef VOL_CLS



#if (defined flagLINUX) || (defined flagFREEBSD)
struct VolRawByte {
	
	struct NativeStaticSource {
		Vector<byte> values;
		Format fmt;
		String filepath;
		Size3 sz;
		int stride;
		bool vflip;
	};
	
	struct Thread {
		
	};
	static Thread& Local() {thread_local static Thread t; return t;}
	
	#include "IfaceFuncs.inl"
	
};
#endif



NAMESPACE_PARALLEL_END


#endif

