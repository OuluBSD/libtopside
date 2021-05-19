#include "EcsLib.h"

NAMESPACE_TOPSIDE_BEGIN

Ref<Transform> Camerable::GetTransform() {
	EntityRef ent = GetEntity();
	return ent->Find<Transform>();
}

NAMESPACE_TOPSIDE_END
