#include "IfaceLib.h"

NAMESPACE_PLAN_BEGIN



PKG(Optimizer, Opt, o) {
	IfaceLib::Add(this);
	
	COLOR(14, 37, 142)
	DEPENDENCY(Local)
	
	NAMESPACE {
		CLASS(Solver) {
			
		}
	}
	
	PKG_IFACE {
		NATIVE_CLASS(Solver)
		//UTIL_CLASS()
		
		FUNCTION1R(CreateSolver, bool, NativeSolver&)
		FUNCTION1V(ClearSolver, NativeSolver&)
		
	}
	
}


NAMESPACE_PLAN_END
