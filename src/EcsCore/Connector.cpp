#include "EcsCore.h"


NAMESPACE_TOPSIDE_BEGIN


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


NAMESPACE_TOPSIDE_END
