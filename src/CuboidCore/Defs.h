#ifndef _GuboCore_Defs_h_
#define _GuboCore_Defs_h_

#include <Draw/Draw.h>
#include <Local/Local.h>

#ifndef GUIPLATFORM_INCLUDE
	#error Build flags prevents GuboCore usage. Probably GUI flag is not set and GuboCore.h is included indirectly.
#else
	#include GUIPLATFORM_INCLUDE
#endif

#endif
