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

//#include "OdeSystem.h"
//#include "OdePrefab.h"


NAMESPACE_PARALLEL_BEGIN

/*
#define FYS_CLS(x, f) struct f##x : x##T<f##Fys> {RTTI_DECL1(f##x,Base); void Visit(RuntimeVisitor& vis) override {VIS_THIS(Base)}};
#define FYS_SYS(x) FYS_CLS_LIST(x)
	FYS_FYSSYS_LIST
#undef FYS_SYS
#undef FYS_CLS

#define FYS_CLS(x, f) struct f##x : x##T<f##Fys> {RTTI_DECL1(f##x,Base); f##x(Engine& e) : Base(e){} void Visit(RuntimeVisitor& vis) override {VIS_THIS(Base)}};
#define FYS_SYS(x) FYS_ECS_CLS_LIST(x)
		FYS_FYSSYS_LIST
#undef FYS_SYS
#undef FYS_CLS
*/

NAMESPACE_PARALLEL_END


#endif
