// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!

#ifndef _IHolograph_IHolograph_h_
#define _IHolograph_IHolograph_h_

#include <ParallelLib/ParallelLib.h>
#include <IMedia/IMedia.h>
#include <LocalHMD/LocalHMD.h>

NAMESPACE_PARALLEL_BEGIN

#define HOLO_CLS_LIST(x) \
	HOLO_CLS(SinkDevice, x) \

#define HOLO_VNDR_LIST \
	HOLO_VNDR(HoloOpenHMD) \
	HOLO_VNDR(HoloLocalHMD) \
	HOLO_VNDR(HoloRemoteVRServer) \
	HOLO_VNDR(HoloDevUsb) \
	HOLO_VNDR(HoloDevBluetooth) \
	HOLO_VNDR(HoloOpenVR) \

#define HOLO_CLS(x, v) struct v##x;
#define HOLO_VNDR(x) HOLO_CLS_LIST(x)
HOLO_VNDR_LIST
#undef HOLO_VNDR
#undef HOLO_CLS

#if (defined flagLINUX && defined flagOPENHMD) || (defined flagFREEBSD && defined flagOPENHMD)
struct HoloOpenHMD {
	struct NativeSinkDevice;
	
	struct Thread {
		
	};
	
	static Thread& Local() {thread_local static Thread t; return t;}
	
	#include "IfaceFuncs.inl"
	
};
#endif
#if defined flagLOCALHMD
struct HoloLocalHMD {
	struct NativeSinkDevice;
	
	struct Thread {
		
	};
	
	static Thread& Local() {thread_local static Thread t; return t;}
	
	#include "IfaceFuncs.inl"
	
};
#endif
#if (defined flagLINUX) || (defined flagFREEBSD)
struct HoloRemoteVRServer {
	struct NativeSinkDevice;
	
	struct Thread {
		
	};
	
	static Thread& Local() {thread_local static Thread t; return t;}
	
	#include "IfaceFuncs.inl"
	
};
#endif
#if (defined flagLINUX) || (defined flagFREEBSD)
struct HoloDevUsb {
	struct NativeSinkDevice;
	
	struct Thread {
		
	};
	
	static Thread& Local() {thread_local static Thread t; return t;}
	
	#include "IfaceFuncs.inl"
	
};
#endif
#if (defined flagLINUX && defined flagHACK) || (defined flagFREEBSD && defined flagHACK)
struct HoloDevBluetooth {
	struct NativeSinkDevice;
	
	struct Thread {
		
	};
	
	static Thread& Local() {thread_local static Thread t; return t;}
	
	#include "IfaceFuncs.inl"
	
};
#endif
#if (defined flagWIN32 && defined flagOPENVR)
struct HoloOpenVR {
	struct NativeSinkDevice;
	
	struct Thread {
		
	};
	
	static Thread& Local() {thread_local static Thread t; return t;}
	
	#include "IfaceFuncs.inl"
	
};
#endif

struct HoloSinkDevice : public Atom {
	RTTI_DECL1(HoloSinkDevice, Atom)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<Atom>(this);}
	
	virtual ~HoloSinkDevice() {}
};


template <class Holo> struct HolographSinkDeviceT : HoloSinkDevice {
	using CLASSNAME = HolographSinkDeviceT<Holo>;
	RTTI_DECL1(CLASSNAME, HoloSinkDevice)
	void Visit(RuntimeVisitor& vis) override {
		if (dev) Holo::SinkDevice_Visit(*dev, *this, vis);
		vis.VisitThis<HoloSinkDevice>(this);
	}
	typename Holo::NativeSinkDevice* dev = 0;
	bool Initialize(const Script::WorldState& ws) override {
		if (!Holo::SinkDevice_Create(dev))
			return false;
		if (!Holo::SinkDevice_Initialize(*dev, *this, ws))
			return false;
		return true;
	}
	bool PostInitialize() override {
		if (!Holo::SinkDevice_PostInitialize(*dev, *this))
			return false;
		return true;
	}
	bool Start() override {
		return Holo::SinkDevice_Start(*dev, *this);
	}
	void Stop() override {
		Holo::SinkDevice_Stop(*dev, *this);
	}
	void Uninitialize() override {
		ASSERT(this->GetDependencyCount() == 0);
		Holo::SinkDevice_Uninitialize(*dev, *this);
		Holo::SinkDevice_Destroy(dev);
	}
	bool Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) override {
		if (!Holo::SinkDevice_Send(*dev, *this, cfg, out, src_ch))
			return false;
		return true;
	}
	bool Recv(int sink_ch, const Packet& in) override {
		return Holo::SinkDevice_Recv(*dev, *this, sink_ch, in);
	}
	void Finalize(RealtimeSourceConfig& cfg) override {
		return Holo::SinkDevice_Finalize(*dev, *this, cfg);
	}
	bool IsReady(PacketIO& io) override {
		return Holo::SinkDevice_IsReady(*dev, *this, io);
	}
};

#if (defined flagLINUX && defined flagOPENHMD) || (defined flagFREEBSD && defined flagOPENHMD)
using OpenHMDSinkDevice = HolographSinkDeviceT<HoloOpenHMD>;
#endif
#if defined flagLOCALHMD
using LocalHMDSinkDevice = HolographSinkDeviceT<HoloLocalHMD>;
#endif
#if (defined flagLINUX) || (defined flagFREEBSD)
using RemoteVRServerSinkDevice = HolographSinkDeviceT<HoloRemoteVRServer>;
#endif
#if (defined flagLINUX) || (defined flagFREEBSD)
using DevUsbSinkDevice = HolographSinkDeviceT<HoloDevUsb>;
#endif
#if (defined flagLINUX && defined flagHACK) || (defined flagFREEBSD && defined flagHACK)
using DevBluetoothSinkDevice = HolographSinkDeviceT<HoloDevBluetooth>;
#endif
#if (defined flagWIN32 && defined flagOPENVR)
using OpenVRSinkDevice = HolographSinkDeviceT<HoloOpenVR>;
#endif

NAMESPACE_PARALLEL_END

#endif
