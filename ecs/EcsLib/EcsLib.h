#ifndef _EcsLib_EcsLib_h_
#define _EcsLib_EcsLib_h_

#include <TemplatesLib/TemplatesLib.h>

#if defined UPP_VERSION || (defined flagSTDEXC)
	#include <Esc/Esc.h>
#endif

#ifdef flagVR
	#if defined flagUWP
		#include <WinLib/WinLib.h>
	#elif defined flagSTEAM
		#include <SteamLib/SteamLib.h>
	#else
		#include <OpenLib/OpenLib.h>
	#endif
#endif

#if defined(UPP_VERSION) && defined(flagGUI)
	// No WindowSystem
#elif defined(flagGUI) && defined(flagCTRL)
	#define HAVE_WINDOWSYSTEM 1
#endif

#define BIG_NUMBER 100000000

#include "Defs.h"
#include "Component.h"
#include "Component.inl"
#include "RegistrySystem.h"
#include "Router.h"
#include "Eon.h"
#include "Customer.h"

#ifdef GUIPLATFORM_INCLUDE_AFTER_ECSLIB
	#include GUIPLATFORM_INCLUDE_AFTER_ECSLIB
#endif

#endif

#if HAVE_SDL2
	#include <EcsSDL2/EcsSDL2.h>
#endif

#if defined flagGUI && defined flagCTRL
	#include <SDL2GUI3D/System.h>
#endif


