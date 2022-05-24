// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!

#ifndef _IMidiHw_Vendors_h_
#define _IMidiHw_Vendors_h_

NAMESPACE_PARALLEL_BEGIN

#define MID_CLS_LIST(x) \
	MID_CLS(Source, x) \



#define MID_VNDR_LIST \
	MID_VNDR(MidPortmidi) \



#define MID_CLS(x, v) struct v##x;
#define MID_VNDR(x) MID_CLS_LIST(x)
MID_VNDR_LIST
#undef MID_VNDR
#undef MID_CLS



#if defined flagPORTMIDI
struct MidPortmidi {
	
	struct NativeSource {
		const PmDeviceInfo* info;
		PmQueue* in_queue;
		int id;
		PmStream* midi_in;
	};
	
	struct Thread {
		
	};
	static Thread& Local() {thread_local static Thread t; return t;}
	
	#include "IfaceFuncs.inl"
	
};
#endif



NAMESPACE_PARALLEL_END


#endif

