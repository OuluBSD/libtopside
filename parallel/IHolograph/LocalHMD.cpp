#include "IHolograph.h"

#if defined flagLOCALHMD
NAMESPACE_PARALLEL_BEGIN

bool HoloLocalHMD::SinkDevice_Initialize(NativeSinkDevice& dev, AtomBase& a, const Script::WorldState& ws) {
	TODO
}

bool HoloLocalHMD::SinkDevice_PostInitialize(NativeSinkDevice& dev, AtomBase& a) {
	TODO
}

bool HoloLocalHMD::SinkDevice_Start(NativeSinkDevice& dev, AtomBase& a) {
	TODO
}

void HoloLocalHMD::SinkDevice_Stop(NativeSinkDevice& dev, AtomBase& a) {
	TODO
}

void HoloLocalHMD::SinkDevice_Uninitialize(NativeSinkDevice& dev, AtomBase& a) {
	TODO
}

bool HoloLocalHMD::SinkDevice_Send(NativeSinkDevice& dev, AtomBase& a, RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) {
	TODO
}

bool HoloLocalHMD::SinkDevice_Recv(NativeSinkDevice& dev, AtomBase& a, int sink_ch, const Packet& in) {
	TODO
}

void HoloLocalHMD::SinkDevice_Finalize(NativeSinkDevice& dev, AtomBase& a, RealtimeSourceConfig& cfg) {
	TODO
}

bool HoloLocalHMD::SinkDevice_IsReady(NativeSinkDevice& dev, AtomBase& a, PacketIO& io) {
	TODO
}





NAMESPACE_PARALLEL_END
#endif

