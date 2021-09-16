#ifndef _OOSDL2_System_h_
#define _OOSDL2_System_h_

#include <SerialLib/SerialLib.h>
#include <OOSDL2/OOSDL2.h>


#define HAVE_MANUAL_SDL_CLASSES 1


#define OBJ_CREATE \
	SDL2ContextBaseRef ev_ctx = GetLoop()->FindNearestAtomCast<SDL2ContextBase>(1); \
	/*ASSERT(ev_ctx);*/ \
	if (!ev_ctx) {RTLOG("error: could not find SDL2Context"); return false;} \
	obj.Create(ev_ctx->GetOOSDL2(), this); \
	ev_ctx->Add(AsRefT());



#include "Base.h"
#include "Timer.h"
#include "AudioIn.h"
#include "AudioOut.h"
#include "Screen.h"
#include "Events.h"
#include "Joystick.h"
#include "GameController.h"
#include "Sensor.h"
#include "Image.h"
#include "Font.h"
#include "Context.h"
#include "System.h"


NAMESPACE_SERIAL_BEGIN



#if 0

#if defined flagGUI

PREFAB_BEGIN(SDL2StandaloneWindow)
	SDL2TimerAtom,
	SDL2EventsAtom,
	//SDL2AudioInputAtom,
	SDL2AudioOutputAtom,
	//SDL2DummyAudioOutputAtom,
	SDL2ScreenAtom,
	SDL2JoystickAtom,
	SDL2GameControllerAtom,
	SDL2SensorAtom,
	SDL2ImageAtom,
	SDL2FontAtom
PREFAB_END

#endif

PREFAB_BEGIN(SDL2StandaloneConsole)
	SDL2TimerAtom,
	SDL2EventsAtom,
	//SDL2AudioInputAtom,
	SDL2AudioOutputAtom,
	// Never: SDL2ScreenAtom,
	SDL2JoystickAtom,
	SDL2GameControllerAtom,
	SDL2SensorAtom,
	SDL2ImageAtom,
	SDL2FontAtom
PREFAB_END



PREFAB_BEGIN(StandaloneLineIn)
	SDL2AudioInputAtom
PREFAB_END

#endif


NAMESPACE_SERIAL_END

#endif
