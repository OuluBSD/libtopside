#ifndef _EcsLib_EcsLib_h_
#define _EcsLib_EcsLib_h_

#include <Core/Core.h>
#include <EcsCore/EcsCore.h>

#if defined UPP_VERSION || (defined flagSTDEXC)
	#include <Esc/Esc.h>
#endif

#ifdef flagVR
	#include <IHolograph/IHolograph.h>
#endif

#if !defined flagGUI
	#error GUI not defined
#endif

#if !defined LIBTOPSIDE
	#error LIBTOPSIDE not defined
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
#include "Gui.h"
#include "Absolute2D.h"
#include "Geom2DComponent.h"

#ifdef GUIPLATFORM_INCLUDE_AFTER_ECSLIB
	#include GUIPLATFORM_INCLUDE_AFTER_ECSLIB
#else
	#error GUIPLATFORM_INCLUDE_AFTER_ECSLIB not defined
#endif

#endif

