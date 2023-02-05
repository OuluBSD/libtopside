#include "LocalCtrl.h"

NAMESPACE_TOPSIDE_BEGIN


void EventLoopIteration(double dt, bool* quit) {
	#ifdef UPP_VERSION
	TODO
	#else
	Ctrl::ProcessEvents(dt, quit);
	#endif
}


NAMESPACE_TOPSIDE_END
