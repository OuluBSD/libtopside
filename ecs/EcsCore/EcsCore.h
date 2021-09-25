#ifndef _EcsCore_EcsCore_h_
#define _EcsCore_EcsCore_h_


#include <Graphics/Graphics.h>
#include <Geometry/Geometry.h>
#include <TemplatesCore/TemplatesCore.h>
#include <Agent/Agent.h>

#if HAVE_SDL2
	#include <OOSDL2/OOSDL2.h>
#endif


#include "Defs.h"
#include "EntityStore.h"
#include "Component.h"
#include "EonParser.h"
#include "EonPlanner.h"
#include "Factory.h"
#include "Entity.h"
#include "ComponentStore.h"
#include "Pool.h"
#include "EntityVisitor.h"
#include "Customer.h"


#endif
