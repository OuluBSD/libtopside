#include "EcsComplete.h"

NAMESPACE_TOPSIDE_BEGIN


INITBLOCK_(EcsComplete) {
	DaemonBase::Register<EcsService>("Ecs");
}


NAMESPACE_TOPSIDE_END
