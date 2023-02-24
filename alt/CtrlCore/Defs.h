#ifndef _CtrlCore_Defs_h_
#define _CtrlCore_Defs_h_


#include <Draw/Draw.h>
#include <Local/Local.h>



#ifndef GUIPLATFORM_INCLUDE
	#ifdef flagVIRTUALGUI
		#define VIRTUALGUI 1
	#endif

	#if VIRTUALGUI
		#define GUIPLATFORM_KEYCODES_INCLUDE <VirtualGui/Keys.h>
		#define GUIPLATFORM_INCLUDE          <VirtualGui/VirtualGui.h>
	#else
		#error Only Virtual Gui backend is supported
	#endif
#endif

#define GUI_APP_MAIN_HOOK

#include GUIPLATFORM_INCLUDE




#endif
