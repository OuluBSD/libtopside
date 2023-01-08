#include "AtomHandle.h"

// This file is generated. Do not modify this file.

INITBLOCK_(AtomHandle) {
	using namespace TS::Parallel;
	using namespace TS::Serial;
	using namespace TS;
	#if defined flagSCREEN
	Factory::RegisterAtom<HandleProgEvents>();
	#endif
	#if defined flagSCREEN
	Factory::RegisterAtom<PipeProgVideo>();
	#endif
	#if defined flagSCREEN
	Factory::RegisterAtom<HandleProgVideo>();
	#endif
}

