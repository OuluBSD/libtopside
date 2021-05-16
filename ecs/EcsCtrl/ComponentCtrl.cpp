#include "EcsCtrl.h"


NAMESPACE_TOPSIDE_BEGIN


ComponentCtrlFactoryMap& GetComponentCtrlFactoryMap() {static ComponentCtrlFactoryMap map; return map;}

void RegisterComponentCtrlFactory(TypeId comp, ComponentCtrlFactory fac) {
	GetComponentCtrlFactoryMap().GetAdd(comp) = fac;
}

ComponentCtrl* NewComponentCtrl(TypeId comp) {
	auto& map = GetComponentCtrlFactoryMap();
	ComponentCtrlFactory fn = 0;
	int i = map.Find(comp);
	if (i >= 0)
		fn = map[i];
	return fn ? fn() : 0;
}


NAMESPACE_TOPSIDE_END
