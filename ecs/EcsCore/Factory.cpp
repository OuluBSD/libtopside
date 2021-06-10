#include "EcsCore.h"

NAMESPACE_TOPSIDE_BEGIN



void EcsFactory::Dump() {
	const auto& fns = CompDataMap();
	
	LOG("EcsFactory::Dump:");
	LOG("\tcomponents (" << fns.GetCount() << "):");
	for(int i = 0; i < fns.GetCount(); i++) {
		const auto& d = fns[i];
		LOG("\t\t" << i << ": " << d.name);
		for(int j = 0; j < d.srcs.GetCount(); j++) {
			TypeCls src = d.srcs[j];
			IfaceData& d = IfaceDataMap().Get(src);
			LOG("\t\t\tsrc " << j << ": " << d.name);
		}
		for(int j = 0; j < d.sinks.GetCount(); j++) {
			TypeCls src = d.sinks[j];
			IfaceData& d = IfaceDataMap().Get(src);
			LOG("\t\t\tsink " << j << ": " << d.name);
		}
	}
}

const Vector<TypeCls>& EcsFactory::GetSinkComponents(TypeCls src_comp) {
	auto& m = EcsFactory::CompDataMap();
	CompData& d = m.Get(src_comp);
	if (!d.searched_sink_comps) {
		for (TypeCls src_sink : d.src_sinks) {
			for (const auto& comp_data : m.GetValues()) {
				for (TypeCls comp_sink : comp_data.sinks) {
					if (src_sink == comp_sink) {
						d.sink_comps.Add(comp_data.cls);
						break;
					}
				}
			}
		}
		
		d.searched_sink_comps = true;
	}
	
	return d.sink_comps;
}

void EcsFactory::GetComponentActions(const Eon::WorldState& src, TypeCls sink_comp, Vector<Eon::Action>& acts) {
	TODO
}




NAMESPACE_TOPSIDE_END
