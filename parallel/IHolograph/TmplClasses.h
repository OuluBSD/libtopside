// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!

#ifndef _IHolograph_TmplClasses_h_
#define _IHolograph_TmplClasses_h_

NAMESPACE_PARALLEL_BEGIN

template <class Holo> struct HolographSinkDeviceT;



template <class Holo>
struct HolographSinkDeviceT : HoloSinkDevice {
	using CLASSNAME = HolographSinkDeviceT<Holo>;
	RTTI_DECL1(CLASSNAME, HoloSinkDevice)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<HoloSinkDevice>(this);}
	
	typename Holo::NativeSinkDevice dev;
	
	
	bool Initialize(const Script::WorldState& ws) override {
		if (!Holo::SinkDevice_Initialize(dev, *this, ws))
			return false;
		return true;
	}

	bool PostInitialize() override {
		if (!Holo::SinkDevice_PostInitialize(dev, *this))
			return false;
		return true;
	}

	bool Start() override {
		return Holo::SinkDevice_Start(dev, *this);
	}

	void Stop() override {
		Holo::SinkDevice_Stop(dev, *this);
	}

	void Uninitialize() override {
		Holo::SinkDevice_Uninitialize(dev, *this);
	}

	bool Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) override {
		if (!Holo::SinkDevice_Send(dev, *this, cfg, out, src_ch))
			return false;
		return true;
	}

	bool Recv(int sink_ch, const Packet& in) override {
		return Holo::SinkDevice_Recv(dev, *this, sink_ch, in);
	}

	void Finalize(RealtimeSourceConfig& cfg) override {
		return Holo::SinkDevice_Finalize(dev, *this, cfg);
	}

	bool IsReady(PacketIO& io) override {
		return Holo::SinkDevice_IsReady(dev, *this, io);
	}

	
};

#if (defined flagOPENHMD && defined flagLINUX) || (defined flagOPENHMD && defined flagFREEBSD)
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

#if (defined flagLINUX) || (defined flagFREEBSD)
using DevBluetoothSinkDevice = HolographSinkDeviceT<HoloDevBluetooth>;
#endif


NAMESPACE_PARALLEL_END

#endif

