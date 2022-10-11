#include "ParallelCore.h"


NAMESPACE_PARALLEL_BEGIN




void Factory::Dump() {
	const auto& fns = AtomDataMap();
	
	LOG("Factory::Dump:");
	LOG("\tatoms (" << fns.GetCount() << "):");
	for(int i = 0; i < fns.GetCount(); i++) {
		const auto& d = fns[i];
		LOG("\t\t" << i << ": " << d.name << "(" << d.cls.ToString() << ")");
	}
}




NAMESPACE_PARALLEL_END
