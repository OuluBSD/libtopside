// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 2022.4.8 19:22:44

#ifndef _IAudio_Vendors_h_
#define _IAudio_Vendors_h_

#if (defined flagLINUX) || (defined flagFREEBSD) || (defined flagWIN32)
	#if defined flagBUILTIN_PORTAUDIO | (defined flagWIN32 & defined flagMSC)
		#include <ports/portaudio/portaudio.h>
		#include <ports/portaudio/pa_types.h>
	#else
		#include <portaudio.h>
	#endif
#endif

NAMESPACE_PARALLEL_BEGIN

#define AUD_CLS_LIST(x) \
	AUD_CLS(SinkDevice, x) \
	AUD_CLS(SourceDevice, x) \



#define AUD_VNDR_LIST \
	AUD_VNDR(AudPortaudio) \



#define AUD_CLS(x, v) struct v##x;
#define AUD_VNDR(x) AUD_CLS_LIST(x)
AUD_VNDR_LIST
#undef AUD_VNDR
#undef AUD_CLS



#if (defined flagLINUX) || (defined flagFREEBSD) || (defined flagWIN32)
struct AudPortaudio {
	using NativeSinkDevice = PaStream*;
	using NativeSourceDevice = PaStream*;
	
	struct Thread {
		
	};
	static Thread& Local() {thread_local static Thread t; return t;}
	
	#include "IfaceFuncs.inl"
	
};
#endif



NAMESPACE_PARALLEL_END


#endif

