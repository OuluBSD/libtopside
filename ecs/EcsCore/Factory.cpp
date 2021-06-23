#include "EcsCore.h"

NAMESPACE_ECS_BEGIN



void Factory::Dump() {
	const auto& fns = CompDataMap();
	
	LOG("Factory::Dump:");
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

void Factory::RefreshLinks(CompData& d) {
	ASSERT(d.src_sink);
	auto& m = Factory::CompDataMap();
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

const Vector<Factory::Link>& Factory::GetSinkComponents(EcsTypeCls src_comp) {
	auto& m = Factory::CompDataMap();
	CompData& d = m.Get(src_comp);
	RefreshLinks(d);
	return d.sink_links;
}

void Factory::GetComponentActions(const Eon::WorldState& src, Vector<Eon::Action>& acts) {
	auto& m = CompDataMap();
	
	EcsTypeCls comp = src.GetComponent();
	CompData& d = m.Get(comp);
	RefreshLinks(d);
	
	Eon::Action a;
	a.Pre() = src;
	
	TODO
	/*if (src.IsAddComponent()) {
		for (const ExtData& e : d.ext.GetValues()) {
			a.Post() = src;
			a.Post().SetAs_AddExtension(comp, e.cls);
			if (e.action_fn(vd, a)) {
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
		if (sink_cd.action_fn(vd, a)) {
			MemSwap(acts.Add(), a);
			a.Pre() = src;
		}
	}*/
	
}




NAMESPACE_ECS_END
