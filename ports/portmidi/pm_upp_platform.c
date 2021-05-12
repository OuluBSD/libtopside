#include "pm_upp.h"

#ifdef flagFREEBSD
	#include "hostapi/freebsd/pmsndio.c"
#endif

#ifdef flagLINUX
	#include "hostapi/linux/finddefault.c"
	#include "hostapi/linux/pmlinux.c"
	#include "hostapi/linux/pmlinuxalsa.c"
#endif

#ifdef flagWIN32
	#include "hostapi/win/pmwin.c"
	#include "hostapi/win/pmwinmm.c"
#endif
