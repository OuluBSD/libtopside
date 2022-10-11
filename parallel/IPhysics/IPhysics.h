#ifndef _IPhysics_IPhysics_h_
#define _IPhysics_IPhysics_h_


#ifdef flagODE
	#include <ode/ode.h>
#endif

#include <EcsLocal/EcsLocal.h>
#include <SoftPhys/SoftPhys.h>

#include "Enums.h"
#include "Types.h"
#include "FysClasses.h"

#include "TNode.h"
#include "TObject.h"
#include "TJoint.h"
#include "TSpace.h"
#include "TSystem.h"
#include "TModel.h"


NAMESPACE_PARALLEL_BEGIN


NAMESPACE_PARALLEL_END


#endif
