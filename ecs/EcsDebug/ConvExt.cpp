#include "EcsDebug.h"

NAMESPACE_ECS_BEGIN


bool DebugConverterExt::Initialize(const Eon::WorldState& ws) {
	return true;
}

void DebugConverterExt::Uninitialize() {
	
}

void DebugConverterExt::Forward(FwdScope& fwd) {
	
}

void DebugConverterExt::LoadPacket(int ch_i, const Packet& p) {
	
}

void DebugConverterExt::StorePacket(int sink_ch,  int src_ch, Packet& p) {
	TODO
}

SideStatus DebugConverterExt::MakeSide(const TypeExtCls& from_type, const Eon::WorldState& from, const TypeExtCls& to_type, const Eon::WorldState& to) {
	return SIDE_ACCEPTED;
}


NAMESPACE_ECS_END
