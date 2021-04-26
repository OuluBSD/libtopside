#ifndef _EcsCore_EcsCore_h_
#define _EcsCore_EcsCore_h_

#ifdef flagGUI
	#include <Graphics/GL.h>
	#include <OuluCtrl/OuluCtrl.h>
#else
	#include <Geometry/Geometry.h>
	#include <Oulu/Oulu.h>
	#include <VirtualSound/VirtualSound.h>
#endif

#include <Agent/Agent.h>

#ifdef flagMSC
	#define CXX2A_STATIC_ASSERT(x, y) static_assert(x, y)
#else
	#define CXX2A_STATIC_ASSERT(x, y)
#endif


#include "TransformUtil.h"

#include "Common.h"
#include "Machine.h"
#include "Exchange.h"
#include "ExchangeSystem.h"
#include "State.h"
#include "Interface.h"
#include "Component.h"
#include "TypeTraits.h"
#include "ComponentStore.h"
#include "Entity.h"
#include "EntityStore.h"
#include "Overlap.h"
#include "StateSystem.h"
#include "Action.h"
#include "ActionSystem.h"

#include "Listener.h"
#include "Controller.h"




#endif
