#include "EcsDebug.h"

NAMESPACE_ECS_BEGIN


bool DebugConverterExt::Initialize(const Eon::WorldState& ws) {return true;}
void DebugConverterExt::Uninitialize() {}
void DebugConverterExt::Forward(FwdScope& fwd) {}
void DebugConverterExt::StorePacket(Packet& p) {}
bool DebugConverterExt::MakeSide(const TypeExtCls& from_type, const Eon::WorldState& from, const TypeExtCls& to_type, const Eon::WorldState& to) {
	return true;
}



NAMESPACE_ECS_END
