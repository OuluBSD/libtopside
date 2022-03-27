#include "ParallelCore.h"


NAMESPACE_PARALLEL_BEGIN




void Factory::Dump() {
	const auto& fns = AtomDataMap();
	
	LOG("Factory::Dump:");
	LOG("\tatoms (" << fns.GetCount() << "):");
	for(int i = 0; i < fns.GetCount(); i++) {
		const auto& d = fns[i];
		LOG("\t\t" << i << ": " << d.name << "(" << d.cls.ToString() << ")");
		/*IfaceData& src = IfaceLinkDataMap().Get(d.cls.src);
		LOG("\t\t\tsrc:  " << d.src.ToString());
		IfaceData& sink = SinkDataMap().Get(d.cls.sink);
		LOG("\t\t\tsink: " << d.sink.ToString());*/
	}
}

void Factory::RefreshLinks(AtomData& d) {
	auto& m = Factory::AtomDataMap();
	if (!d.searched_sink_links) {
		bool dump = false;
		/*if (d.cls.src.dev == DevCls::OGL && d.cls.src.val == ValCls::MIDI) {
			LOG(d.cls.ToString());
			dump = true;
		}*/
		for (const auto& atom_data : m.GetValues()) {
			ValDevCls common_vd = d.cls.iface.src.GetCommon(atom_data.cls.iface.sink);
			if (common_vd.IsValid()) {
				Link& l = d.sink_links.Add();
				l.dst_atom = atom_data.cls;
				l.iface = d.cls.iface.src;
				l.common_vd = common_vd;
				ASSERT(l.dst_atom.IsValid() && l.iface.IsValid());
				if (dump) {LOG("\t" << atom_data.cls.ToString());}
			}
		}
		if (dump) {
			LOG("");
		}
		d.searched_sink_links = true;
	}
}

const Vector<Factory::Link>& Factory::GetSinkAtoms(AtomTypeCls src_atom) {
	auto& m = Factory::AtomDataMap();
	AtomData& d = m.Get(src_atom);
	RefreshLinks(d);
	return d.sink_links;
}

LinkTypeCls Factory::GetAtomLinkType(AtomTypeCls atom) {
	auto& m = Factory::AtomDataMap();
	int i = AtomDataMap().Find(atom);
	ASSERT(i >= 0);
	if (i < 0)
		return LinkTypeCls();
	return AtomDataMap()[i].link_type();
}



NAMESPACE_PARALLEL_END
