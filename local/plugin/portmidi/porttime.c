/* porttime.c -- portable API for millisecond timer */

/* There is no machine-independent implementation code to put here */

#ifdef flagPOSIX
	#include "ptlinux.c"
#endif

#ifdef flagWIN32
	#include "ptwinmm.c"
#endif
