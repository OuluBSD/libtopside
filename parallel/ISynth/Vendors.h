// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!

#ifndef _ISynth_Vendors_h_
#define _ISynth_Vendors_h_

NAMESPACE_PARALLEL_BEGIN

#define SYN_CLS_LIST(x) \
	SYN_CLS(Instrument, x) \



#define SYN_VNDR_LIST \
	SYN_VNDR(SynFluidsynth) \



#define SYN_CLS(x, v) struct v##x;
#define SYN_VNDR(x) SYN_CLS_LIST(x)
SYN_VNDR_LIST
#undef SYN_VNDR
#undef SYN_CLS



#if defined flagFLUIDSYNTH
struct SynFluidsynth {
	
	struct NativeInstrument {
		fluid_settings_t* settings;
		fluid_synth_t* synth;
		fluid_audio_driver_t* adriver;
		int sfont_id;
		bool sf_loaded;
	};
	
	struct Thread {
		
	};
	static Thread& Local() {thread_local static Thread t; return t;}
	
	#include "IfaceFuncs.inl"
	
};
#endif



NAMESPACE_PARALLEL_END


#endif

