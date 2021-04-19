#ifndef _EcsLib_EcsLib_h_
#define _EcsLib_EcsLib_h_

#include <EcsCore/EcsCore.h>

#ifdef flagALTCORE
	#include <EscAlt/Esc.h>
#else
	#include <Esc/Esc.h>
#endif


#if !defined(flagALTCORE) && defined(flagGUI) && !defined(flagVIRTUALGUI3D)
	// No WindowSystem
#elif defined(flagGUI)
	#define HAVE_WINDOWSYSTEM 1
#endif

#define BIG_NUMBER 100000000


#include "Defs.h"
#include "Viewport.h"
#include "Shader.h"
#include "Camera.h"
#include "Model.h"
#include "CommonComponents.h"
#include "EasingSystem.h"
#include "WorldLogic.h"
#include "MotionController.h"
#include "HolographicScene.h"
#include "AudioSystem.h"
#include "MoCtrl.h"
#include "RegistrySystem.h"

#include "BasicShaders.h"
#include "OctreeShaders.h"
#include "PathTracerShaders.h"

#include "Prefabs.h"

#ifdef GUIPLATFORM_INCLUDE_AFTER_ECSLIB
	#include GUIPLATFORM_INCLUDE_AFTER_ECSLIB
#endif

#include "EventSystem.h"
#include "RenderingSystem.h"
#include "WindowSystem.h"

#endif

#ifdef flagSDL2
	#include <OOSDL2/System.h>
#endif

#include <Multimedia/System.h>

#ifdef flagSDL2GUI3DALT
#include <SDL2GUI3DAlt/System.h>
#endif


