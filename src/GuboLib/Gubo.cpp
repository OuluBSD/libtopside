#include "GuboLib.h"

NAMESPACE_TOPSIDE_BEGIN


void TopGubo::CreateGeom3DComponent() {
	using namespace Ecs;
	using namespace Parallel;
	
	
	Machine& mach = GetActiveMachine();
	Gu::GuboSystemRef wins = mach.Get<Gu::GuboSystem>();
	Gu::GuboManager& mgr = wins->GetActiveScope();
	mgr.AddInterface(*this);
	
}


NAMESPACE_TOPSIDE_END
