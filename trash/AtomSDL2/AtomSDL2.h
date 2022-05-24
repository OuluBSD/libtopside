#ifndef _OOSDL2_System_h_
#define _OOSDL2_System_h_

#include <SerialLib/SerialLib.h>
#include <OOSDL2/OOSDL2.h>


#define HAVE_MANUAL_SDL_CLASSES 1


#define OBJ_CREATE \
	SDL2ContextBaseRef ev_ctx = GetLoop()->template FindNearestAtomCast<SDL2ContextBase>(1); \
	/*ASSERT(ev_ctx);*/ \
	if (!ev_ctx) {RTLOG("error: could not find SDL2Context"); return false;} \
	obj.Create(ev_ctx->GetOOSDL2(), this); \
	ev_ctx->Add(AsRefT());



#include "Base.h"
#include "Context.h"
#include "Timer.h"
#include "AudioIn.h"
#include "AudioOut.h"
#include "ScreenT.h"
//#include "CpuScreen.h"
//#include "OglScreen.h"
#include "Events.h"
#include "Joystick.h"
#include "GameController.h"
#include "Sensor.h"
#include "Image.h"
#include "Font.h"


NAMESPACE_SERIAL_BEGIN




NAMESPACE_SERIAL_END

#endif
