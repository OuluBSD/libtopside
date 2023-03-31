#include "IHolograph.h"

#if (defined flagLINUX) || (defined flagFREEBSD)


NAMESPACE_PARALLEL_BEGIN

struct HoloDevUsb::NativeSinkDevice {
	
};




bool HoloDevUsb::SinkDevice_Create(NativeSinkDevice*& dev) {
	dev = new NativeSinkDevice;
	return true;
}

void HoloDevUsb::SinkDevice_Destroy(NativeSinkDevice*& dev) {
	delete dev;
}

void HoloDevUsb::SinkDevice_Visit(NativeSinkDevice&, AtomBase&, RuntimeVisitor& vis) {
	
}

bool HoloDevUsb::SinkDevice_Initialize(NativeSinkDevice& dev, AtomBase& a, const Script::WorldState& ws) {
	TODO
}

bool HoloDevUsb::SinkDevice_PostInitialize(NativeSinkDevice& dev, AtomBase& a) {
	TODO
}

bool HoloDevUsb::SinkDevice_Start(NativeSinkDevice& dev, AtomBase& a) {
	TODO
}

void HoloDevUsb::SinkDevice_Stop(NativeSinkDevice& dev, AtomBase& a) {
	TODO
}

void HoloDevUsb::SinkDevice_Uninitialize(NativeSinkDevice& dev, AtomBase& a) {
	TODO
}

bool HoloDevUsb::SinkDevice_Send(NativeSinkDevice& dev, AtomBase& a, RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) {
	TODO
}

bool HoloDevUsb::SinkDevice_Recv(NativeSinkDevice& dev, AtomBase& a, int sink_ch, const Packet& in) {
	TODO
}

void HoloDevUsb::SinkDevice_Finalize(NativeSinkDevice& dev, AtomBase& a, RealtimeSourceConfig& cfg) {
	TODO
}

bool HoloDevUsb::SinkDevice_IsReady(NativeSinkDevice& dev, AtomBase& a, PacketIO& io) {
	TODO
}





NAMESPACE_PARALLEL_END
#endif

