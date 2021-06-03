#include "AccelCore.h"

NAMESPACE_TOPSIDE_BEGIN



void Pool::AddConnectEverythingWithAccel() {
	#define IFACE(x) \
		Add<ConnectAllInterfaces<x##Spec>>(); \
		Add<ConnectAllInterfaces<Accel##x##Spec>>();
	IFACE_LIST
	#undef IFACE
}

void Pool::ConnectEverythingWithAccel() {
	#define IFACE(x) \
		Find<ConnectAllInterfaces<x##Spec>>()->Update(0); \
		Find<ConnectAllInterfaces<Accel##x##Spec>>()->Update(0);
	IFACE_LIST
	#undef IFACE
}



NAMESPACE_TOPSIDE_END
