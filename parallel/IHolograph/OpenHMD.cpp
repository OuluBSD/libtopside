#include "IHolograph.h"

#if (defined flagLINUX) || (defined flagFREEBSD)


NAMESPACE_PARALLEL_BEGIN

bool HoloOpenHMD::SinkDevice_Initialize(NativeSinkDevice& dev, AtomBase& a, const Script::WorldState& ws) {
	TODO
}

bool HoloOpenHMD::SinkDevice_PostInitialize(NativeSinkDevice& dev, AtomBase& a) {
	TODO
}

bool HoloOpenHMD::SinkDevice_Start(NativeSinkDevice& dev, AtomBase& a) {
	TODO
}

void HoloOpenHMD::SinkDevice_Stop(NativeSinkDevice& dev, AtomBase& a) {
	TODO
}

void HoloOpenHMD::SinkDevice_Uninitialize(NativeSinkDevice& dev, AtomBase& a) {
	TODO
}

bool HoloOpenHMD::SinkDevice_Send(NativeSinkDevice& dev, AtomBase& a, RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) {
	TODO
}

bool HoloOpenHMD::SinkDevice_Recv(NativeSinkDevice& dev, AtomBase& a, int sink_ch, const Packet& in) {
	TODO
}

void HoloOpenHMD::SinkDevice_Finalize(NativeSinkDevice& dev, AtomBase& a, RealtimeSourceConfig& cfg) {
	TODO
}

bool HoloOpenHMD::SinkDevice_NegotiateSinkFormat(NativeSinkDevice& dev, AtomBase& a, Serial::Link& link, int sink_ch, const Format& new_fmt) {
	TODO
}





NAMESPACE_PARALLEL_END
#endif

