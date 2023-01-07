#include "SerialLib.h"

NAMESPACE_TOPSIDE_BEGIN


bool SingleMachine::Open(void(*arg_fn)()) {
	using namespace Parallel;
	using namespace Serial;
	
	const AppFlags& flags = GetAppFlags();
	Machine& mach = GetActiveMachine();
	
	RegistrySystemRef reg = mach.Add<RegistrySystem>();
	
	mach.Add<AtomStore>();
	mach.Add<LinkStore>();
	mach.Add<SpaceStore>();
	mach.Add<LoopStore>();
	
    mach.Add<AtomSystem>();
	mach.Add<LinkSystem>();
	
    mach.Add<ScriptLoader>();
    mach.Add<GuboSystem>();
    mach.Add<WindowSystem>();
    
	
    reg->SetAppName("Non-screen machine");
    
    if (arg_fn)
        arg_fn();
    
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
