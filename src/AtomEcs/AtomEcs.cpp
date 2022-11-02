#include "AtomEcs.h"

NAMESPACE_UPP_BEGIN


INITBLOCK_(AtomEcs) {
	using namespace TS::Parallel;
	using namespace TS::Serial;
	using namespace TS;
	
	#ifdef flagSCREEN
	Factory::RegisterAtom<EcsProgVideo>();
	#endif
	
}


NAMESPACE_UPP_END
