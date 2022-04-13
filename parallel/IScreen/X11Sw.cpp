#include "IScreen.h"

#if (defined flagLINUX) || (defined flagFREEBSD)
NAMESPACE_PARALLEL_BEGIN

bool ScrX11Sw::SinkDevice_Initialize(NativeSinkDevice& dev, AtomBase& a, const Script::WorldState& ws) {
	TODO
}

bool ScrX11Sw::SinkDevice_PostInitialize(NativeSinkDevice& dev, AtomBase& a) {
	TODO
}

bool ScrX11Sw::SinkDevice_Start(NativeSinkDevice& dev, AtomBase& a) {
	TODO
}

void ScrX11Sw::SinkDevice_Stop(NativeSinkDevice& dev, AtomBase& a) {
	TODO
}

void ScrX11Sw::SinkDevice_Uninitialize(NativeSinkDevice& dev, AtomBase& a) {
	TODO
}

bool ScrX11Sw::SinkDevice_ProcessPacket(NativeSinkDevice& dev, AtomBase& a, PacketValue& in, PacketValue& out) {
	TODO
}

bool ScrX11Sw::SinkDevice_Recv(NativeSinkDevice& dev, AtomBase& a, int sink_ch, const Packet& in) {
	TODO
}

void ScrX11Sw::SinkDevice_Finalize(NativeSinkDevice& dev, AtomBase& a, RealtimeSourceConfig& cfg) {
	TODO
}





NAMESPACE_PARALLEL_END
#endif

