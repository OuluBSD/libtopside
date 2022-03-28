#include "AtomNonScreen.h"
#include <SerialPlanner/SerialPlanner.h>

NAMESPACE_TOPSIDE_BEGIN


bool SingleMachine::Open(void(*arg_fn)()) {
	using namespace Parallel;
	using namespace Serial;
	
	const AppFlags& flags = GetAppFlags();
	Machine& mach = GetActiveMachine();
	
	RegistrySystemRef reg = mach.Add<RegistrySystem>();
    mach.Add<AtomSystem>();
	mach.Add<LinkSystem>();
	
	mach.Add<AtomStore>();
	mach.Add<LinkStore>();
	
	mach.Add<SpaceStore>();
	mach.Add<LoopStore>();
	
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
