#include "EcsDebug.h"

NAMESPACE_ECS_BEGIN



bool DebugSideInputExt::Initialize(const Eon::WorldState& ws) {return true;}
void DebugSideInputExt::Uninitialize() {}
void DebugSideInputExt::Forward(FwdScope& fwd) {}
void DebugSideInputExt::StorePacket(Packet& p) {}
bool DebugSideInputExt::MakeSide(const TypeExtCls& from_type, const Eon::WorldState& from, const TypeExtCls& to_type, const Eon::WorldState& to) {
	ValDevCls f = from.GetSideCls();
	ValDevCls t = to.GetSideCls();
	if (f.val != t.val)
		return false;
	return true;
}

bool DebugSideOutputExt::Initialize(const Eon::WorldState& ws) {return true;}
void DebugSideOutputExt::Uninitialize() {}
void DebugSideOutputExt::Forward(FwdScope& fwd) {}
void DebugSideOutputExt::StorePacket(Packet& p) {}
bool DebugSideOutputExt::MakeSide(const TypeExtCls& from_type, const Eon::WorldState& from, const TypeExtCls& to_type, const Eon::WorldState& to) {
	ValDevCls f = from.GetSideCls();
	ValDevCls t = to.GetSideCls();
	if (f.val != t.val)
		return false;
	return true;
}



NAMESPACE_ECS_END
