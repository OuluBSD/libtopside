#include "Internal.h"


NAMESPACE_TOPSIDE_BEGIN


bool SingleMachine::Open(void(*arg_fn)()) {
	using namespace Serial;
	
	const AppFlags& flags = GetAppFlags();
	Machine& mach = GetActiveMachine();
	
	RegistrySystemRef reg = mach.Add<RegistrySystem>();
	LoopStoreRef loops = mach.Add<LoopStore>();
	mach.Add<AtomStore>();
    mach.Add<AtomSystem>();
    mach.Add<ScriptLoader>();
    
    reg->SetAppName("Non-screen machine");
    
    if (!mach.Start())
		return false;
    
	return true;
}

void SingleMachine::Close() {
	using namespace Serial;
	
	Machine& mach = GetActiveMachine();
	mach.Stop();
}


NAMESPACE_TOPSIDE_END
