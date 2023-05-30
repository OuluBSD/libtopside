#include "enet.h"

NAMESPACE_TOPSIDE_BEGIN


INITBLOCK_(enet) {
	DaemonBase::Register<EnetServiceServer>("EnetServer");
	DaemonBase::Register<EnetServiceClient>("EnetClient");
}


NAMESPACE_TOPSIDE_END
