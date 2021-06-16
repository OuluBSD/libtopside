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
#include "ConnManual.h"
#include "ConnAny.h"


#endif
