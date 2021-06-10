#include "EcsCore.h"

NAMESPACE_TOPSIDE_BEGIN



void EcsFactory::Dump() {
	const auto& fns = NewCompFns();
	
	LOG("EcsFactory::Dump:");
	LOG("\tcomponents (" << fns.GetCount() << "):");
	for(int i = 0; i < fns.GetCount(); i++) {
		const auto& d = fns[i];
		LOG("\t\t" << i << ": " << d.name);
	}
}

int  EcsFactory::FindSinkComponents(TypeCls src_comp, Vector<TypeCls>& sink_comps) {
	TODO
}

void EcsFactory::GetComponentActions(TypeCls sink_comp, const Eon::WorldState& src, Vector<Eon::Action>& acts) {
	TODO
}




NAMESPACE_TOPSIDE_END
