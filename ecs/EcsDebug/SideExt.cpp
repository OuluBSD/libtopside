#include "EcsDebug.h"

NAMESPACE_ECS_BEGIN



bool DebugAudioSideInputExt::Initialize(const Eon::WorldState& ws) {return true;}
void DebugAudioSideInputExt::Uninitialize() {}
void DebugAudioSideInputExt::Forward(FwdScope& fwd) {}
void DebugAudioSideInputExt::StorePacket(Packet& p) {}
bool DebugAudioSideInputExt::MakeSide(const TypeExtCls& from_type, const Eon::WorldState& from, const TypeExtCls& to_type, const Eon::WorldState& to) {
	return true;
}

bool DebugAudioSideOutputExt::Initialize(const Eon::WorldState& ws) {return true;}
void DebugAudioSideOutputExt::Uninitialize() {}
void DebugAudioSideOutputExt::Forward(FwdScope& fwd) {}
void DebugAudioSideOutputExt::StorePacket(Packet& p) {}
bool DebugAudioSideOutputExt::MakeSide(const TypeExtCls& from_type, const Eon::WorldState& from, const TypeExtCls& to_type, const Eon::WorldState& to) {
	return true;
}



NAMESPACE_ECS_END
