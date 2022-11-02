#include "Local.h"

NAMESPACE_TOPSIDE_BEGIN

void ErrorSourceBuffered::DumpMessages() {
	for(const ProcMsg& pm : messages) {
		LOG(pm.ToString());
	}
}



NAMESPACE_TOPSIDE_END
