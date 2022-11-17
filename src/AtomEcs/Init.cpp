#include "AtomEcs.h"

// This file is generated. Do not modify this file.

INITBLOCK_(AtomEcs) {
	using namespace TS::Parallel;
	using namespace TS::Serial;
	using namespace TS;
	#if defined flagSCREEN
	Factory::RegisterAtom<EcsProgEvents>();
	#endif
	#if defined flagSCREEN
	Factory::RegisterAtom<PipeProgVideo>();
	#endif
	#if defined flagSCREEN
	Factory::RegisterAtom<EcsProgVideo>();
	#endif
}

