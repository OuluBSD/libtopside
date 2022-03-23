// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 23.3.23 18:44:22

#ifndef _IMidi_Vendors_h_
#define _IMidi_Vendors_h_

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



struct MidPortmidi {
	using NativeSinkDevice = uint32;
	using NativeSourceDevice = uint32;
	using NativeEvent = uint32;
	typedef void (*DataCallbackFn)(void*, char* data, int size);
	
	struct Thread {
		
	};
	static Thread& Local() {thread_local static Thread t; return t;}
	
	#include "IfaceFuncs.inl"
	
};



NAMESPACE_TOPSIDE_END


#endif

