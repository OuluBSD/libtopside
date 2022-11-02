#ifndef _plugin_portmidi_pm_upp_h_
#define _plugin_portmidi_pm_upp_h_

#ifdef flagFREEBSD
	#include "portmidi.h"
	#include "hostapi/freebsd/pmsndio.h"
#endif

#ifdef flagLINUX
	#include "portmidi.h"
	#include "hostapi/linux/pmlinux.h"
	#include "hostapi/linux/pmlinuxalsa.h"
#endif

#ifdef flagWIN32
	#include "hostapi/win/pmwinmm.h"
#endif

#endif
