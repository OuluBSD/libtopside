// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!

#ifndef _IHolograph_Vendors_h_
#define _IHolograph_Vendors_h_

#if (defined flagOPENHMD && defined flagLINUX) || (defined flagOPENHMD && defined flagFREEBSD)
	#include <openhmd.h>
#endif

#if (defined flagLINUX) || (defined flagFREEBSD)
	#include <ports/hcidump/hcidump.h>
#endif

NAMESPACE_PARALLEL_BEGIN

#define HOLO_CLS_LIST(x) \
	HOLO_CLS(SinkDevice, x) \



#define HOLO_VNDR_LIST \
	HOLO_VNDR(HoloOpenHMD) \
	HOLO_VNDR(HoloDevUsb) \
	HOLO_VNDR(HoloDevBluetooth) \



#define HOLO_CLS(x, v) struct v##x;
#define HOLO_VNDR(x) HOLO_CLS_LIST(x)
HOLO_VNDR_LIST
#undef HOLO_VNDR
#undef HOLO_CLS



#if (defined flagOPENHMD && defined flagLINUX) || (defined flagOPENHMD && defined flagFREEBSD)
struct HoloOpenHMD {
	
	struct NativeSinkDevice {
		ohmd_context* ctx;
		ohmd_device_settings* settings;
		const char* fragment;
		const char* vertex;
		ohmd_device* hmd;
		ohmd_device* ctrl[2];
		Size screen_sz;
		CtrlEvent ev;
		CtrlEvent3D ev3d;
		bool ev_sendable;
		int seq;
		TimeStop ts;
		int control_count[2];
		int controls_fn[2][64];
		int controls_types[2][64];
	};
	
	struct Thread {
		
	};
	static Thread& Local() {thread_local static Thread t; return t;}
	
	#include "IfaceFuncs.inl"
	
};
#endif

#if (defined flagLINUX) || (defined flagFREEBSD)
struct HoloDevUsb {
	
	struct NativeSinkDevice {
	};
	
	struct Thread {
		
	};
	static Thread& Local() {thread_local static Thread t; return t;}
	
	#include "IfaceFuncs.inl"
	
};
#endif

#if (defined flagLINUX) || (defined flagFREEBSD)
struct HoloDevBluetooth {
	
	struct NativeSinkDevice {
		SimpleBluetoothConnection bt[2];
		Vector<byte> data[2];
		TcpSocket sock;
		int mode;
		int ctrl_idx[2];
	};
	
	struct Thread {
		
	};
	static Thread& Local() {thread_local static Thread t; return t;}
	
	#include "IfaceFuncs.inl"
	
};
#endif



NAMESPACE_PARALLEL_END


#endif

