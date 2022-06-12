#include "EcsVR.h"

#if 0

NAMESPACE_ECS_BEGIN

bool HolographicScopeBinder::Initialize() {
	s = &GetGlobalHolographicScope(0);
	s->refs++;
	return true;
}

void HolographicScopeBinder::Uninitialize() {
	if (s) {
		s->refs--;
		s = 0;
	}
}

	

NAMESPACE_ECS_END
#endif
