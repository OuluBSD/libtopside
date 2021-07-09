#include "EcsDebug.h"

NAMESPACE_ECS_BEGIN



bool DebugSideInputExt::Initialize(const Eon::WorldState& ws) {return true;}
void DebugSideInputExt::Uninitialize() {}
void DebugSideInputExt::Forward(FwdScope& fwd) {}
void DebugSideInputExt::StorePacket(Packet& p) {}
SideStatus DebugSideInputExt::MakeSide(const TypeExtCls& from_type, const Eon::WorldState& from, const TypeExtCls& to_type, const Eon::WorldState& to) {
	ValDevCls f = from.GetSideCls();
	ValDevCls t = to.GetSideCls();
	if (f.val != t.val)
		return SIDE_NOT_ACCEPTED;
	bool accept_multiple = to_type.IsMultiSideConnection();
	return accept_multiple ? SIDE_ACCEPTED_MULTI : SIDE_ACCEPTED;
}

bool DebugSideOutputExt::Initialize(const Eon::WorldState& ws) {return true;}
void DebugSideOutputExt::Uninitialize() {}
void DebugSideOutputExt::Forward(FwdScope& fwd) {}
void DebugSideOutputExt::StorePacket(Packet& p) {}
SideStatus DebugSideOutputExt::MakeSide(const TypeExtCls& from_type, const Eon::WorldState& from, const TypeExtCls& to_type, const Eon::WorldState& to) {
	ValDevCls f = from.GetSideCls();
	ValDevCls t = to.GetSideCls();
	if (f.val != t.val)
		return SIDE_NOT_ACCEPTED;
	bool accept_multiple = to_type.IsMultiSideConnection();
	return accept_multiple ? SIDE_ACCEPTED_MULTI : SIDE_ACCEPTED;
}



NAMESPACE_ECS_END
