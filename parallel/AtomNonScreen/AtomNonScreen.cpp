#include "AtomNonScreen.h"
#include <SerialPlanner/SerialPlanner.h>

NAMESPACE_TOPSIDE_BEGIN


bool SingleMachine::Open(void(*arg_fn)()) {
	using namespace Parallel;
	using namespace Serial;
	
	const AppFlags& flags = GetAppFlags();
	Machine& mach = GetActiveMachine();
	
	RegistrySystemRef reg = mach.Add<RegistrySystem>();
	mach.Add<AtomStore>();
    mach.Add<AtomSystem>();
	mach.Add<SpaceStore>();
	mach.Add<LinkStore>();
	mach.Add<LinkSystem>();
	mach.Add<LoopStore>();
	mach.Add<LoopSystem>();
    mach.Add<ScriptLoader>();
    
    reg->SetAppName("Non-screen machine");
    
    if (!mach.Start())
		return false;
    
	return true;
}

void SingleMachine::Close() {
	using namespace Parallel;
	
	Machine& mach = GetActiveMachine();
	mach.Stop();
}


NAMESPACE_TOPSIDE_END
