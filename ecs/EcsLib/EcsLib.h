#ifndef _EcsLib_EcsLib_h_
#define _EcsLib_EcsLib_h_

#include <EcsCore/EcsCore.h>

#if defined UPP_VERSION || (defined flagSTDEXC)
	#include <Esc/Esc.h>
#endif

#ifdef flagVR
	#include <IHolograph/IHolograph.h>
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
#include "Model.h"
#include "RenderingSystem.h"
#include "EventSystem.h"
#include "Prefab.h"
#include "EonLoader.h"
#include "WorldLogic.h"

#ifdef GUIPLATFORM_INCLUDE_AFTER_ECSLIB
	#include GUIPLATFORM_INCLUDE_AFTER_ECSLIB
#endif

#endif



/*#if defined flagGUI && defined flagGUI
	#include <SDL2GUI3D/System.h>
#endif*/


