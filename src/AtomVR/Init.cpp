#include "AtomVR.h"

// This file is generated. Do not modify this file.

INITBLOCK_(AtomVR) {
	using namespace TS::Parallel;
	using namespace TS::Serial;
	using namespace TS;
	#if (defined flagFREEBSD && defined flagOPENHMD) || (defined flagLINUX && defined flagOPENHMD)
	Factory::RegisterAtom<OpenHMDPipe>();
	#endif
	#if defined flagLOCALHMD
	Factory::RegisterAtom<LocalHMDPipe>();
	#endif
	#if (defined flagFREEBSD) || (defined flagLINUX)
	Factory::RegisterAtom<RemoteVRServerPipe>();
	#endif
	#if (defined flagFREEBSD && defined flagHACK) || (defined flagLINUX && defined flagHACK)
	Factory::RegisterAtom<BluetoothHoloPipe>();
	#endif
}
