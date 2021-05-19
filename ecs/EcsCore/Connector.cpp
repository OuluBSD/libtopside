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


NAMESPACE_TOPSIDE_END
