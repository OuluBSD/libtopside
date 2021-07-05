#include "EcsCore.h"

NAMESPACE_ECS_BEGIN



void Factory::Dump() {
	const auto& fns = CompDataMap();
	
	LOG("Factory::Dump:");
	LOG("\tcomponents (" << fns.GetCount() << "):");
	for(int i = 0; i < fns.GetCount(); i++) {
		const auto& d = fns[i];
		LOG("\t\t" << i << ": " << d.name << "(" << d.cls.ToString() << ")");
		/*IfaceData& src = SourceDataMap().Get(d.cls.src);
		LOG("\t\t\tsrc:  " << d.src.ToString());
		IfaceData& sink = SinkDataMap().Get(d.cls.sink);
		LOG("\t\t\tsink: " << d.sink.ToString());*/
	}
}

void Factory::RefreshLinks(CompData& d) {
	auto& m = Factory::CompDataMap();
	if (!d.searched_sink_links) {
		bool dump = false;
		/*if (d.cls.src.dev == DevCls::ACCEL && d.cls.src.val == ValCls::MIDI) {
			LOG(d.cls.ToString());
			dump = true;
		}*/
		for (const auto& comp_data : m.GetValues()) {
			if (d.cls.src == comp_data.cls.sink) {
				Link& l = d.sink_links.Add();
				l.dst_comp = comp_data.cls;
				l.iface = d.cls.src;
				ASSERT(l.dst_comp.IsValid() && l.iface.IsValid());
				if (dump) {LOG("\t" << comp_data.cls.ToString());}
			}
		}
		if (dump) {
			LOG("");
		}
		d.searched_sink_links = true;
	}
}

const Vector<Factory::Link>& Factory::GetSinkComponents(TypeCompCls src_comp) {
	auto& m = Factory::CompDataMap();
	CompData& d = m.Get(src_comp);
	RefreshLinks(d);
	return d.sink_links;
}

void Factory::GetComponentActions(const Eon::WorldState& src, Vector<Eon::Action>& acts) {
	auto& m = CompDataMap();
	
	TypeCompCls comp = src.GetComponent();
	CompData& d = m.Get(comp);
	RefreshLinks(d);
	
	Eon::Action a;
	a.Pre() = src;
	
	if (src.IsAddComponent()) {
		for (const ExtData& e : d.ext.GetValues()) {
			a.Post() = src;
			a.Post().SetAs_AddExtension(comp, e.cls);
			a.Post().SetSideCls(e.side_vd);
			if (e.action_fn(comp, a)) {
				MemSwap(acts.Add(), a);
				a.Pre() = src;
			}
		}
	}
	
	for (const Link& link : d.sink_links) {
		TypeCompCls dst = link.dst_comp;
		ASSERT(dst.IsValid());
		const CompData& dst_cd = m.Get(dst);
		
		/*if (dst.sub == SubCompCls::CONVERTER && dst.side.vd == VD(ACCEL,AUDIO)) {
			LOG(dst.ToString());
		}*/
		if (comp.sub != SubCompCls::CUSTOMER &&
			dst.sub != SubCompCls::CONVERTER &&
			dst.side.vd.val != comp.side.vd.val &&
			dst.sink.val != ValCls::RECEIPT)
			continue;
		//ASSERT(src.GetComponent() != link.dst_comp);
		
		a.Post() = src;
		a.Post().SetAs_AddComponent(dst);
		if (dst_cd.action_fn(dst_cd.cls, a)) {
			MemSwap(acts.Add(), a);
			a.Pre() = src;
		}
	}
	
}




NAMESPACE_ECS_END
