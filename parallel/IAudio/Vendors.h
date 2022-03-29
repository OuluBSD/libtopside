// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 29.3.29 19:55:44

#ifndef _IAudio_Vendors_h_
#define _IAudio_Vendors_h_

NAMESPACE_PARALLEL_BEGIN

#define AUD_CLS_LIST(x) \
	AUD_CLS(SinkDevice, x) \
	AUD_CLS(SourceDevice, x) \



#define AUD_VNDR_LIST \
	AUD_VNDR(AudSdl) \
	AUD_VNDR(AudPortaudio) \



#define AUD_CLS(x, v) struct v##x;
#define AUD_VNDR(x) AUD_CLS_LIST(x)
AUD_VNDR_LIST
#undef AUD_VNDR
#undef AUD_CLS



struct AudSdl {
	using NativeSinkDevice = uint32;
	using NativeSourceDevice = uint32;
	
	struct Thread {
		
	};
	static Thread& Local() {thread_local static Thread t; return t;}
	
	#include "IfaceFuncs.inl"
	
};

struct AudPortaudio {
	using NativeSinkDevice = uint32;
	using NativeSourceDevice = uint32;
	
	struct Thread {
		
	};
	static Thread& Local() {thread_local static Thread t; return t;}
	
	#include "IfaceFuncs.inl"
	
};



NAMESPACE_PARALLEL_END


#endif

