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
#include "EntityStore.h"
#include "Component.h"
#include "Connector.h"
#include "ComponentStore.h"
#include "EonParser.h"
#include "EonPlanner.h"
#include "Factory.h"
#include "Entity.h"
#include "Pool.h"
#include "EntityVisitor.h"
#include "Overlap.h"
#include "Action.h"
#include "ActionSystem.h"
#include "ConnManual.h"
#include "ConnAny.h"
#include "ConnPoolComps.h"
#include "ConnPoolComps.inl"
#include "ConnDevComps.h"
#include "ConnDevComps.inl"
#include "AudioSystem.h"
#include "VideoSystem.h"

#endif
