#ifndef _CtrlCore_Defs_h_
#define _CtrlCore_Defs_h_


#include <Draw/Draw.h>
#include <Local/Local.h>

#ifndef GUIPLATFORM_INCLUDE
	#error Build flags prevents CtrlCore usage. Probably GUI flag is not set and CtrlCore.h is included indirectly.
#else
	#include GUIPLATFORM_INCLUDE
#endif



#endif
