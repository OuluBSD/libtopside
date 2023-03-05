#ifndef _GuboCore_Defs_h_
#define _GuboCore_Defs_h_

#include <Draw/Draw.h>
#include <Local/Local.h>


/*
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

#include GUIPLATFORM_INCLUDE*/



#define LTIMING(x)



NAMESPACE_UPP_BEGIN


enum CtrlCoreFlags {
	K_DELTA        = 0x200000,
	K_CHAR_LIM     = 0x200000, // lower that this, key in Key is Unicode codepoint

	K_ALT          = 0x1000000,
	K_SHIFT        = 0x800000,
	K_CTRL         = 0x400000,
#ifdef PLATFORM_COCOA
	K_OPTION       = 0x2000000,
#endif

	K_KEYUP        = 0x4000000,

	K_MOUSEMIDDLE  = 0x2,
	K_MOUSERIGHT   = 0x4,
	K_MOUSELEFT    = 0x8,
	K_MOUSEDOUBLE  = 0x10,
	K_MOUSETRIPLE  = 0x20,

	K_SHIFT_CTRL = K_SHIFT|K_CTRL,


	K_PEN          = 0x80,

	IK_DBL_CLICK   = 0x40000001, // this is just to get the info that the entry is equal to dbl-click to the menu

	K_MOUSE_FORWARD = 0x40000002,
	K_MOUSE_BACKWARD = 0x40000003
};

//#include "MKeys.h"




#ifdef GUIPLATFORM_INCLUDE_AFTER
	#include GUIPLATFORM_INCLUDE_AFTER
#endif

NAMESPACE_UPP_END


#endif
