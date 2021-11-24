#ifndef _EcsLib_EcsLib_h_
#define _EcsLib_EcsLib_h_

#include <EcsCore/EcsCore.h>

#if defined UPP_VERSION || (defined flagSTDEXC)
	#include <Esc/Esc.h>
#endif

#ifdef flagVR
	#if defined flagUWP
		#include <WinLib/WinLib.h>
	#elif defined flagSTEAM
		#include <SteamLib/SteamLib.h>
	#else
		#include <FreeLib/FreeLib.h>
	#endif
#endif

#if !defined LIBTOPSIDE && defined flagGUI
	// No WindowSystem
#elif defined(flagGUI)
	#define HAVE_WINDOWSYSTEM 1
#endif

#define BIG_NUMBER 100000000

#include "Defs.h"
#include "CommonComponents.h"
#include "Camera.h"
#include "RegistrySystem.h"
#include "RenderingSystem.h"
#include "EventSystem.h"

#ifdef GUIPLATFORM_INCLUDE_AFTER_ECSLIB
	#include GUIPLATFORM_INCLUDE_AFTER_ECSLIB
#endif

#endif

/*#if defined flagGUI && defined flagGUI
	#include <SDL2GUI3D/System.h>
#endif*/


