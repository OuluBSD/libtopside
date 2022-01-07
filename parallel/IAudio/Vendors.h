// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!

#ifndef _IAudio_Vendors_h_
#define _IAudio_Vendors_h

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



VENDORSSZZ
struct AudSdl {
	struct Thread {
	};
	static Thread& Local() {thread_local static Thread t; return t;}
	
	#include "IfaceFuncs.inl"
	
};

struct AudPortaudio {
	struct Thread {
	};
	static Thread& Local() {thread_local static Thread t; return t;}
	
	#include "IfaceFuncs.inl"
	
};



NAMESPACE_TOPSIDE_END


#endif

