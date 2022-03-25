// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 25.3.25 19:11:33

#ifndef _IAudio_Vendors_h_
#define _IAudio_Vendors_h_

NAMESPACE_TOPSIDE_BEGIN

#define AUD_CLS_LIST(x) \
	AUD_CLS(AudioSinkDevice, x) \
	AUD_CLS(AudioSourceDevice, x) \



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
	typedef void (*DataCallbackFn)(void*, char* data, int size);
	
	struct Thread {
		
	};
	static Thread& Local() {thread_local static Thread t; return t;}
	
	#include "IfaceFuncs.inl"
	
};

struct AudPortaudio {
	using NativeSinkDevice = uint32;
	using NativeSourceDevice = uint32;
	typedef void (*DataCallbackFn)(void*, char* data, int size);
	
	struct Thread {
		
	};
	static Thread& Local() {thread_local static Thread t; return t;}
	
	#include "IfaceFuncs.inl"
	
};



NAMESPACE_TOPSIDE_END


#endif

