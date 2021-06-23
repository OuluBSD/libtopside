#include "EcsCore.h"
#if 0


NAMESPACE_ECS_BEGIN


ConnectorBase::ConnectorBase() {
	DBG_CONSTRUCT
}

ConnectorBase::~ConnectorBase() {
	DBG_DESTRUCT
}

PoolRef ConnectorBase::GetPool() {
	return GetParent()->AsRefT();
}

String ConnectorBase::ToString() const {
	return GetDynamicName();
}


NAMESPACE_ECS_END
#endif
