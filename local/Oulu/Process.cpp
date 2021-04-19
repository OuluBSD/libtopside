#include "Oulu.h"

NAMESPACE_OULU_BEGIN

void ErrorSourceBuffered::DumpMessages() {
	for(const ProcMsg& pm : messages) {
		LOG(pm.ToString());
	}
}



NAMESPACE_OULU_END
