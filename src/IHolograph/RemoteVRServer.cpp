#include "IHolograph.h"

#if (defined flagLINUX) || (defined flagFREEBSD)

NAMESPACE_PARALLEL_BEGIN


struct HoloRemoteVRServer::NativeSinkDevice {
	SerialServiceClient svc;
	WmrFusionSystemReceiver recv;
};




bool HoloRemoteVRServer::SinkDevice_Create(NativeSinkDevice*& dev) {
	dev = new NativeSinkDevice;
	return true;
}

void HoloRemoteVRServer::SinkDevice_Destroy(NativeSinkDevice*& dev) {
	delete dev;
}

void HoloRemoteVRServer::SinkDevice_Visit(NativeSinkDevice&, AtomBase&, RuntimeVisitor& vis) {
	
}

bool HoloRemoteVRServer::SinkDevice_Initialize(NativeSinkDevice& dev, AtomBase& a, const Script::WorldState& ws) {
	String addr = ws.GetString(".addr", "127.0.0.1");
	int port = ws.GetInt(".port", 7776);
	
	if (!dev.svc.ConnectTcp(addr, port)) {
		LOG("HoloRemoteVRServer::SinkDevice_Initialize: error: could not connect " << addr << ":" << port);
		return false;
	}
	
	return true;
}

bool HoloRemoteVRServer::SinkDevice_PostInitialize(NativeSinkDevice& dev, AtomBase& a) {
	return true;
}

bool HoloRemoteVRServer::SinkDevice_Start(NativeSinkDevice& dev, AtomBase& a) {
	return true;
}

void HoloRemoteVRServer::SinkDevice_Stop(NativeSinkDevice& dev, AtomBase& a) {
	
}

void HoloRemoteVRServer::SinkDevice_Uninitialize(NativeSinkDevice& dev, AtomBase& a) {
	dev.svc.CloseTcp();
}

bool HoloRemoteVRServer::SinkDevice_Send(NativeSinkDevice& dev, AtomBase& a, RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) {
	ASSERT(dev.recv.ev_sendable);
	if (!dev.recv.ev_sendable)
		return false;
	
	Format fmt = out.GetFormat();
	RTLOG("HoloRemoteVRServer::SinkDevice_Send: " << fmt.ToString());
	
	if (fmt.IsEvent()) {
		UPP::CtrlEvent& dst = out.SetData<UPP::CtrlEvent>();
		dst = dev.recv.ev;
		out.seq = dev.recv.seq++;
	}
	
	return true;
}

bool HoloRemoteVRServer::SinkDevice_Recv(NativeSinkDevice& dev, AtomBase& a, int sink_ch, const Packet& in) {
	return true;
}

void HoloRemoteVRServer::SinkDevice_Finalize(NativeSinkDevice& dev, AtomBase& a, RealtimeSourceConfig& cfg) {
	
}

bool HoloRemoteVRServer::SinkDevice_IsReady(NativeSinkDevice& dev, AtomBase& a, PacketIO& io) {
	return dev.recv.UpdateFrom(dev.svc);
}





NAMESPACE_PARALLEL_END

#endif
