#include "EcsCtrl.h"


NAMESPACE_OULU_BEGIN


InterfaceCtrlFactoryMap& GetInterfaceCtrlFactoryMap() {static InterfaceCtrlFactoryMap map; return map;}

void RegisterInterfaceCtrlFactory(TypeId iface, InterfaceCtrlFactory fac) {
	GetInterfaceCtrlFactoryMap().GetAdd(iface) = fac;
}

InterfaceCtrl* NewInterfaceCtrl(TypeId iface) {
	auto& map = GetInterfaceCtrlFactoryMap();
	InterfaceCtrlFactory fn = 0;
	int i = map.Find(iface);
	if (i >= 0)
		fn = map[i];
	return fn ? fn() : 0;
}



NAMESPACE_OULU_END
