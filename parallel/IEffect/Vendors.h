// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!

#ifndef _IEffect_Vendors_h_
#define _IEffect_Vendors_h_

#if 1
	#include <AudioCore/AudioCore.h>
#endif

NAMESPACE_PARALLEL_BEGIN

#define FX_CLS_LIST(x) \
	FX_CLS(Effect, x) \



#define FX_VNDR_LIST \
	FX_VNDR(FxAudioCore) \



#define FX_CLS(x, v) struct v##x;
#define FX_VNDR(x) FX_CLS_LIST(x)
FX_VNDR_LIST
#undef FX_VNDR
#undef FX_CLS



#if 1
struct FxAudioCore {
	
	struct NativeEffect {
		One<Audio::Effect> effect;
		int channel_count;
		int sample_rate;
		Packet last_audio_in;
	};
	
	struct Thread {
		
	};
	static Thread& Local() {thread_local static Thread t; return t;}
	
	#include "IfaceFuncs.inl"
	
};
#endif



NAMESPACE_PARALLEL_END


#endif

