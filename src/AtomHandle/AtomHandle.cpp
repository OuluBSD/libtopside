#include "AtomHandle.h"

NAMESPACE_UPP_BEGIN


INITBLOCK_(AtomHandle) {
	using namespace TS::Parallel;
	using namespace TS::Serial;
	using namespace TS;
	
	#ifdef flagSCREEN
	Factory::RegisterAtom<HandleProgVideo>();
	#endif
	
}


NAMESPACE_UPP_END
