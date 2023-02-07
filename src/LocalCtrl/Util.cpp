#include "LocalCtrl.h"

NAMESPACE_TOPSIDE_BEGIN


void EventLoopIteration(double dt, bool* quit) {
	#if IS_UPP_CORE
	Ctrl::EventLoopOnce();
	#else
	Ctrl::ProcessEvents(dt, quit);
	#endif
}


NAMESPACE_TOPSIDE_END
