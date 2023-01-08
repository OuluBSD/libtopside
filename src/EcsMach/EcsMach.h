#ifndef _EcsMach_EcsMach_h_
#define _EcsMach_EcsMach_h_

#include <AtomMinimal/AtomMinimal.h>
#include <AtomHandle/AtomHandle.h>
#include <SerialLib/SerialLib.h>

#ifdef flagNO_ECS
	#error EcsMach is included while NO_ECS flag is defined.
#endif

#define NAMESPACE_ECS_NAME		Ecs
#define ECS						Ecs
#define NAMESPACE_ECS_BEGIN	namespace  TS { namespace  NAMESPACE_ECS_NAME {
#define NAMESPACE_ECS_END	}}

#include "Defs.h"
#include "Common.h"
#include "TypeTraits.h"
#include "Engine.h"

#endif
