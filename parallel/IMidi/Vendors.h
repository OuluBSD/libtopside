// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!

#ifndef _IMidi_Vendors_h_
#define _IMidi_Vendors_h

NAMESPACE_TOPSIDE_BEGIN

#define MID_CLS_LIST(x) \
	MID_CLS(MidiSinkDevice, x) \
	MID_CLS(MidiSourceDevice, x) \



#define MID_VNDR_LIST \
	MID_VNDR(MidPortmidi) \



#define MID_CLS(x, v) struct v##x;
#define MID_VNDR(x) MID_CLS_LIST(x)
MID_VNDR_LIST
#undef MID_VNDR
#undef MID_CLS



VENDORSSZZ
struct MidPortmidi {
	struct Thread {
	};
	static Thread& Local() {thread_local static Thread t; return t;}
	
	#include "IfaceFuncs.inl"
	
};



NAMESPACE_TOPSIDE_END


#endif

