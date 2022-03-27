#include "SerialMach.h"


NAMESPACE_SERIAL_BEGIN


void Factory::Dump() {
	const auto& fns = LinkDataMap();
	
	LOG("Factory::Dump:");
	LOG("\tlinks (" << fns.GetCount() << "):");
	for(int i = 0; i < fns.GetCount(); i++) {
		const auto& d = fns[i];
		LOG("\t\t" << i << ": " << d.name << "(" << d.cls.ToString() << ")");
		/*IfaceData& src = IfaceLinkDataMap().Get(d.cls.src);
		LOG("\t\t\tsrc:  " << d.src.ToString());
		IfaceData& sink = SinkDataMap().Get(d.cls.sink);
		LOG("\t\t\tsink: " << d.sink.ToString());*/
	}
}


NAMESPACE_SERIAL_END
