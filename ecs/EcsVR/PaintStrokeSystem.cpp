#include "EcsVR.h"

NAMESPACE_ECS_BEGIN

bool PaintStrokeSystemHolo::Initialize() {
	if (!PaintStrokeSystemBase::Initialize())
		return false;
	
	if (!HolographicScopeBinder::Initialize())
		return false;
	
	return true;
}

NAMESPACE_ECS_END
