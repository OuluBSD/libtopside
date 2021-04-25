#include "EcsLib.h"

NAMESPACE_OULU_BEGIN

Ref<Transform> Camerable::GetTransform() {
	Entity& ent = GetEntity();
	return ent.Find<Transform>();
}

NAMESPACE_OULU_END
