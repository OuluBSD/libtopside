#ifndef _LittleLibrary_LittleLibrary_h_
#define _LittleLibrary_LittleLibrary_h_

#ifdef flagEMU
	#define EMU		1
	#define REALHW	0
	#define PACKED
#else
	#define EMU		0
	#define REALHW	1
	#define PACKED	__attribute__((packed))
#endif


#if EMU
	#ifdef flagGUI
		#include <CtrlLib/CtrlLib.h>
	#else
		#include <Core/Core.h>
	#endif
	using namespace Upp;
#endif





#include "Callback.h"
#include "Memory.h"
#include "FixedArray.h"
#include "icxxabi.h"

#include "Common.h"
#include "Interrupts.h"
#include "FileSystem.h"



#endif
