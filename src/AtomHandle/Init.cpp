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
	Factory::RegisterAtom<CenterProgPipe>();
	#endif
	#if defined flagSCREEN
	Factory::RegisterAtom<OglProgPipe>();
	#endif
	#if defined flagSCREEN
	Factory::RegisterAtom<HandleProgVideo>();
	#endif
}

