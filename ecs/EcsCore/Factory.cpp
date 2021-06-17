#include "EcsCore.h"

NAMESPACE_TOPSIDE_BEGIN



void EcsFactory::Dump() {
	const auto& fns = CompDataMap();
	
	LOG("EcsFactory::Dump:");
	LOG("\tcomponents (" << fns.GetCount() << "):");
	for(int i = 0; i < fns.GetCount(); i++) {
		const auto& d = fns[i];
		LOG("\t\t" << i << ": " << d.name);
		IfaceData& src = SourceDataMap().Get(d.src);
		LOG("\t\t\tsrc:  " << src.name);
		IfaceData& sink = SinkDataMap().Get(d.sink);
		LOG("\t\t\tsink: " << sink.name);
	}
}

const Vector<EcsFactory::Link>& EcsFactory::GetSinkComponents(TypeCls src_comp) {
	auto& m = EcsFactory::CompDataMap();
	CompData& d = m.Get(src_comp);
	if (!d.searched_sink_links) {
		for (const auto& comp_data : m.GetValues()) {
			if (d.src_sink == comp_data.sink) {
				Link& l = d.sink_links.Add();
				l.dst_comp = comp_data.cls;
				l.iface_src = d.src;
				l.iface_sink = d.src_sink;
			}
		}
		d.searched_sink_links = true;
	}
	
	return d.sink_links;
}

void EcsFactory::GetComponentActions(const Eon::WorldState& src, const Vector<Link>& sink_links, Vector<Eon::Action>& acts) {
	auto& m = CompDataMap();
	
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
