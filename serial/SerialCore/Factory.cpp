#include "SerialCore.h"

NAMESPACE_SERIAL_BEGIN




void Factory::Dump() {
	const auto& fns = AtomDataMap();
	
	LOG("Factory::Dump:");
	LOG("\tatoms (" << fns.GetCount() << "):");
	for(int i = 0; i < fns.GetCount(); i++) {
		const auto& d = fns[i];
		LOG("\t\t" << i << ": " << d.name << "(" << d.cls.ToString() << ")");
		/*IfaceData& src = SourceDataMap().Get(d.cls.src);
		LOG("\t\t\tsrc:  " << d.src.ToString());
		IfaceData& sink = SinkDataMap().Get(d.cls.sink);
		LOG("\t\t\tsink: " << d.sink.ToString());*/
	}
}

void Factory::RefreshLinks(AtomData& d) {
	auto& m = Factory::AtomDataMap();
	if (!d.searched_sink_links) {
		bool dump = false;
		/*if (d.cls.src.dev == DevCls::ACCEL && d.cls.src.val == ValCls::MIDI) {
			LOG(d.cls.ToString());
			dump = true;
		}*/
		for (const auto& atom_data : m.GetValues()) {
			if (d.cls.iface.src == atom_data.cls.iface.sink) {
				Link& l = d.sink_links.Add();
				l.dst_atom = atom_data.cls;
				l.iface = d.cls.iface.src;
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



NAMESPACE_SERIAL_END
