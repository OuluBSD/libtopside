#ifndef _EcsCore_EcsCore_h_
#define _EcsCore_EcsCore_h_


#include <Graphics/GL.h>
#include <Geometry/Geometry.h>
#include <TemplatesCore/TemplatesCore.h>
#include <Agent/Agent.h>

#if HAVE_SDL2
	#include <OOSDL2/OOSDL2.h>
#endif




#include "Defs.h"
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




#include "EntityStore.h"
#include "Component.h"
#include "Connector.h"
#include "ComponentStore.h"
#include "Entity.h"
#include "Pool.h"
#include "EntityVisitor.h"
#include "Overlap.h"
#include "Action.h"
#include "ActionSystem.h"
#include "ConnPoolComps.h"
#include "ConnPoolComps.inl"
#include "ConnDevComps.h"
#include "ConnDevComps.inl"
#include "AudioSystem.h"
#include "VideoSystem.h"

#endif
