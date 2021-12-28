#ifndef _Physics_Physics_h_
#define _Physics_Physics_h_


#ifdef flagODE
	#include <ode/ode.h>
#endif

#include <EcsLocal/EcsLocal.h>

#include "Enums.h"
#include "Types.h"
#include "FysClasses.h"

#include "TNode.h"
#include "TObject.h"
#include "TJoint.h"
#include "TSpace.h"
#include "TSystem.h"
#include "TPrefab.h"

//#include "OdeSystem.h"
//#include "OdePrefab.h"


NAMESPACE_TOPSIDE_BEGIN

#define FYS_CLS(x, f) struct f##x : x##T<f##Fys> {RTTI_DECL1(f##x,Base); void Visit(RuntimeVisitor& vis) override {VIS_THIS(Base)}};
#define FYS_SYS(x) FYS_CLS_LIST(x)
FYS_FYSSYS_LIST
#undef FYS_SYS
#undef FYS_CLS
namespace Ecs {
#define FYS_CLS(x, f) struct f##x : x##T<f##Fys> {RTTI_DECL1(f##x,Base); f##x(Engine& e) : Base(e){} void Visit(RuntimeVisitor& vis) override {VIS_THIS(Base)}};
#define FYS_SYS(x) FYS_ECS_CLS_LIST(x)
FYS_FYSSYS_LIST
#undef FYS_SYS
}
#undef FYS_CLS

NAMESPACE_TOPSIDE_END


#endif
