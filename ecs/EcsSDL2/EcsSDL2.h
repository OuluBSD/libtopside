#ifndef _OOSDL2_System_h_
#define _OOSDL2_System_h_

#include <EcsLib/EcsLib.h>
#include <OOSDL2/OOSDL2.h>



#define OBJ_CREATE \
	auto ev_ctx = GetEntity()->Find<SDL2ContextComponent>(); \
	/*ASSERT(ev_ctx);*/ \
	if (ev_ctx) { \
		obj.Create(ev_ctx->GetOOSDL2()); \
	}



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


NAMESPACE_TOPSIDE_BEGIN



#if defined flagGUI

PREFAB_BEGIN(SDL2StandaloneWindow)
	SDL2TimerComponent,
	SDL2EventsComponent,
	//SDL2AudioInputComponent,
	SDL2AudioOutputComponent,
	SDL2ScreenComponent,
	SDL2JoystickComponent,
	SDL2GameControllerComponent,
	SDL2SensorComponent,
	SDL2ImageComponent,
	SDL2FontComponent,
	SDL2ContextComponent
PREFAB_END

#endif

PREFAB_BEGIN(SDL2StandaloneConsole)
	SDL2TimerComponent,
	SDL2EventsComponent,
	//SDL2AudioInputComponent,
	SDL2AudioOutputComponent,
	// Never: SDL2ScreenComponent,
	SDL2JoystickComponent,
	SDL2GameControllerComponent,
	SDL2SensorComponent,
	SDL2ImageComponent,
	SDL2FontComponent,
	SDL2ContextComponent
PREFAB_END



PREFAB_BEGIN(StandaloneLineIn)
	SDL2AudioInputComponent,
	SDL2ContextComponent
PREFAB_END



NAMESPACE_TOPSIDE_END

#endif
