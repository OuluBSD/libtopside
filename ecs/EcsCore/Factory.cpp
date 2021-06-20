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

void EcsFactory::RefreshLinks(CompData& d) {
	ASSERT(d.src_sink);
	auto& m = EcsFactory::CompDataMap();
	if (!d.searched_sink_links) {
		for (const auto& comp_data : m.GetValues()) {
			if (d.src_sink == comp_data.sink) {
				Link& l = d.sink_links.Add();
				l.dst_comp = comp_data.cls;
				l.iface_src = d.src;
				l.iface_sink = d.src_sink;
				ASSERT(l.dst_comp && l.iface_src && l.iface_sink);
			}
		}
		d.searched_sink_links = true;
	}
}

const Vector<EcsFactory::Link>& EcsFactory::GetSinkComponents(TypeCls src_comp) {
	auto& m = EcsFactory::CompDataMap();
	CompData& d = m.Get(src_comp);
	RefreshLinks(d);
	return d.sink_links;
}

void EcsFactory::GetComponentActions(const Eon::WorldState& src, Vector<Eon::Action>& acts) {
	auto& m = CompDataMap();
	
	TypeCls comp = src.GetComponent();
	CompData& d = m.Get(comp);
	RefreshLinks(d);
	
	Eon::Action a;
	a.Pre() = src;
	
	if (src.IsAddComponent()) {
		for (const ExtData& e : d.ext.GetValues()) {
			a.Post() = src;
			a.Post().SetAs_AddExtension(comp, e.cls);
			if (e.action_fn(a)) {
				MemSwap(acts.Add(), a);
				a.Pre() = src;
			}
		}
	}
	
	for (const Link& link : d.sink_links) {
		TypeCls sink = link.dst_comp;
		ASSERT(sink != 0);
		const CompData& sink_cd = m.Get(sink);
		
		a.Post() = src;
		a.Post().SetAs_AddComponent(link.dst_comp, link.iface_src, link.iface_sink);
		if (sink_cd.action_fn(a)) {
			MemSwap(acts.Add(), a);
			a.Pre() = src;
		}
	}
	
}




NAMESPACE_TOPSIDE_END
