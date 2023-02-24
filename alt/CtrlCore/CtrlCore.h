#ifndef _CtrlCoreAlt_CtrlCore_h_
#define _CtrlCoreAlt_CtrlCore_h_

#include "Defs.h"

NAMESPACE_UPP



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

#include "MKeys.h"




bool GetMouseLeft();
bool GetMouseRight();
bool GetMouseMiddle();


END_UPP_NAMESPACE


#include "Util.h"
#include "Ctrl.h"
#include "TopWindow.h"
#include "Images.h"


NAMESPACE_UPP

#ifdef GUIPLATFORM_INCLUDE_AFTER
	#include GUIPLATFORM_INCLUDE_AFTER
#endif

END_UPP_NAMESPACE

#endif
