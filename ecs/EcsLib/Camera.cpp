#include "EcsLib.h"

NAMESPACE_OULU_BEGIN

Transform* Camerable::GetTransform() {
	Entity& ent = GetEntity();
	return ent.Find<Transform>();
}

NAMESPACE_OULU_END
