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
			IfaceData& d = SourceDataMap().Get(src);
			LOG("\t\t\tsrc " << j << ": " << d.name);
		}
		for(int j = 0; j < d.sinks.GetCount(); j++) {
			TypeCls src = d.sinks[j];
			IfaceData& d = SinkDataMap().Get(src);
			LOG("\t\t\tsink " << j << ": " << d.name);
		}
	}
}

const Vector<EcsFactory::Link>& EcsFactory::GetSinkComponents(TypeCls src_comp) {
	auto& m = EcsFactory::CompDataMap();
	CompData& d = m.Get(src_comp);
	if (!d.searched_sink_links) {
		auto src_iter = d.srcs.Begin();
		for (TypeCls src_sink : d.src_sinks) {
			for (const auto& comp_data : m.GetValues()) {
				for (TypeCls comp_sink : comp_data.sinks) {
					if (src_sink == comp_sink) {
						Link& l = d.sink_links.Add();
						l.dst_comp = comp_data.cls;
						l.iface_src = *src_iter;
						l.iface_sink = src_sink;
						break;
					}
				}
			}
			++src_iter;
		}
		
		d.searched_sink_links = true;
	}
	
	return d.sink_links;
}

void EcsFactory::GetComponentActions(const Eon::WorldState& src, const Vector<Link>& sink_links, Vector<Eon::Action>& acts) {
	auto& m = CompDataMap();
	//CompData& src_cd = m.Get(src.GetComponent());
	
	Eon::Action a;
	a.Pre() = src;
	
	for (const auto& link : sink_links) {
		TypeCls sink = link.dst_comp;
		
		CompData& sink_cd = m.Get(sink);
		
		a.Post() = src; 
		a.Post().SetTypes(link.dst_comp, link.iface_src, link.iface_sink);
		
		if (sink_cd.action_fn(a)) {
			MemSwap(acts.Add(), a);
			a.Pre() = src;
		}
	}
}




NAMESPACE_TOPSIDE_END
