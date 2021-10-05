#ifndef _Physics_Physics_h_
#define _Physics_Physics_h_

#ifndef flagODE
	#error Physics package requires ODE build flag
#endif

#include <ode/ode.h>

#include <EcsLocal/EcsLocal.h>


#include "OdeSystem.h"
#include "OdePrefab.h"


#endif
