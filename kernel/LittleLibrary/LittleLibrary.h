#ifndef _LittleLibrary_LittleLibrary_h_
#define _LittleLibrary_LittleLibrary_h_

#include <LittleCommon/LittleCommon.h>

#if EMUGUI
	#include <EmuCtrl/EmuCtrl.h>
#elif EMU
	#include <Emu/Emu.h>
#else
	#include <x86/Kernel.h>
#endif





#include "Callback.h"
#include "icxxabi.h"

#include "Common.h"
#include "Interrupts.h"



#endif
