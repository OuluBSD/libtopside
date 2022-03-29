#include "IEvent.h"

NAMESPACE_PARALLEL_BEGIN

bool EvX11::SourceDevice_Initialize(NativeSourceDevice& dev, AtomBase& a, const Script::WorldState& ws) {
	TODO
}

void EvX11::SourceDevice_Start(NativeSourceDevice& dev) {
	TODO
}

void EvX11::SourceDevice_Stop(NativeSourceDevice& dev) {
	TODO
}

void EvX11::SourceDevice_Uninitialize(NativeSourceDevice& dev) {
	TODO
}

bool EvX11::SourceDevice_ProcessPacket(NativeSourceDevice& dev, PacketValue& v) {
	TODO
}

bool EvX11::SourceDevice_Poll(NativeSourceDevice& o, UPP::CtrlEvent& e) {
	TODO
}

uint32 EvX11::SourceDevice_GetTickCount(NativeSourceDevice& o) {
	TODO
}

void EvX11::SourceDevice_WaitEvent(NativeSourceDevice& o, int ms) {
	TODO
}

bool EvX11::SourceDevice_IsWaitingEvent(NativeSourceDevice& o) {
	TODO
}





NAMESPACE_PARALLEL_END

