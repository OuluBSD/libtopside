#ifndef _EcsCore_EcsCore_h_
#define _EcsCore_EcsCore_h_


#include <Graphics/GL.h>
#ifdef flagGUI
	#include <LocalCtrl/LocalCtrl.h>
#endif
#include <Geometry/Geometry.h>
#include <Local/Local.h>

#include <Agent/Agent.h>

#ifdef flagMSC
	#define CXX2A_STATIC_ASSERT(x, y) static_assert(x, y)
#else
	#define CXX2A_STATIC_ASSERT(x, y)
#endif


#include "TransformUtil.h"

/*#include "Common.h"
#include "Machine.h"
#include "EntityStore.h"
#include "ExchangeSystem.h"
#include "Connector.h"
#include "TypeTraits.h"
#include "Templates.h"
#include "Interface.h"
#include "Component.h"
#include "Entity.h"
#include "Pool.h"
#include "Templates.inl"
#include "ComponentStore.h"
#include "EntityVisitor.h"
#include "Overlap.h"
#include "Action.h"
#include "ActionSystem.h"
#include "ConnPoolComps.h"
#include "AudioSystem.h"
#include "VideoSystem.h"*/

/*#include "Common.h"
#include "Machine.h"
#include "ExchangeSystem.h"
#include "Interface.h"
#include "Component.h"
#include "Connector.h"
#include "TypeTraits.h"
#include "Templates.h"
#include "ComponentStore.h"
#include "Entity.h"
#include "Pool.h"
#include "EntityVisitor.h"
#include "EntityStore.h"
#include "Overlap.h"
#include "Action.h"
#include "ActionSystem.h"
#include "ConnPoolComps.h"
#include "AudioSystem.h"
#include "VideoSystem.h"*/

#include "Common.h"
#include "Machine.h"

#include "EntityStore.h"

#include "Templates.h"

#include "Interface.h"

#include "Component.h"
#include "Connector.h"
#include "TypeTraits.h"
#include "ComponentStore.h"
#include "Entity.h"
#include "Pool.h"
#include "EntityVisitor.h"
#include "Overlap.h"
#include "Action.h"
#include "ActionSystem.h"
#include "ConnPoolComps.h"
#include "AudioSystem.h"
#include "VideoSystem.h"

#endif
