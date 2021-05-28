#include "AccelCore.h"

NAMESPACE_TOPSIDE_BEGIN



void Pool::AddConnectEverythingWithAccel() {
	#define IFACE(x) \
		Add<ConnectAllInterfaces<x##Source>>(); \
		Add<ConnectAllInterfaces<Accel##x##Source>>();
	IFACE_LIST
	#undef IFACE
}

void Pool::ConnectEverythingWithAccel() {
	#define IFACE(x) \
		Find<ConnectAllInterfaces<x##Source>>()->Update(0); \
		Find<ConnectAllInterfaces<Accel##x##Source>>()->Update(0);
	IFACE_LIST
	#undef IFACE
}



NAMESPACE_TOPSIDE_END
