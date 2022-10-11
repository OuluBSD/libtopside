#include "SerialMach.h"


NAMESPACE_SERIAL_BEGIN


void Factory::Dump() {
	const auto& fns = LinkDataMap();
	
	LOG("Factory::Dump:");
	LOG("\tlinks (" << fns.GetCount() << "):");
	for(int i = 0; i < fns.GetCount(); i++) {
		const auto& d = fns[i];
		LOG("\t\t" << i << ": " << d.name << "(" << d.cls.ToString() << ")");
	}
}


NAMESPACE_SERIAL_END
