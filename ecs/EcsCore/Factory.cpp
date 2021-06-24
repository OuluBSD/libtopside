#include "EcsCore.h"

NAMESPACE_ECS_BEGIN



void Factory::Dump() {
	const auto& fns = CompDataMap();
	
	LOG("Factory::Dump:");
	LOG("\tcomponents (" << fns.GetCount() << "):");
	for(int i = 0; i < fns.GetCount(); i++) {
		const auto& d = fns[i];
		LOG("\t\t" << i << ": " << d.name << "(" << d.side.ToString() << ")");
		IfaceData& src = SourceDataMap().Get(d.src);
		LOG("\t\t\tsrc:  " << d.src.ToString());
		IfaceData& sink = SinkDataMap().Get(d.sink);
		LOG("\t\t\tsink: " << d.sink.ToString());
	}
}

void Factory::RefreshLinks(CompData& d) {
	auto& m = Factory::CompDataMap();
	if (!d.searched_sink_links) {
		for (const auto& comp_data : m.GetValues()) {
			if (d.src == comp_data.sink) {
				Link& l = d.sink_links.Add();
				l.dst_comp = comp_data.cls;
				l.iface = d.src;
				ASSERT(l.dst_comp.IsValid() && l.iface.IsValid());
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
	
	
	if (src.IsAddComponent()) {
		for (const ExtData& e : d.ext.GetValues()) {
			a.Post() = src;
			a.Post().SetAs_AddExtension(comp, e.cls);
			if (e.action_fn(d.side, a)) {
				MemSwap(acts.Add(), a);
				a.Pre() = src;
			}
		}
	}
	
	for (const Link& link : d.sink_links) {
		EcsTypeCls side = link.dst_comp;
		ASSERT(side.IsValid());
		const CompData& side_cd = m.Get(side);
		
		ASSERT(src.GetComponent() != link.dst_comp);
		
		a.Post() = src;
		a.Post().SetAs_AddComponent(link.dst_comp, link.iface);
		if (side_cd.action_fn(side_cd.cls, a)) {
			MemSwap(acts.Add(), a);
			a.Pre() = src;
		}
	}
	
}




NAMESPACE_ECS_END
