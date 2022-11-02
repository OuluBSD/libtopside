#ifndef _Physics_Physics_h_
#define _Physics_Physics_h_


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

#include "OdeSystem.h"
#include "OdePrefab.h"


#endif
