#include "SerialLib.h"

NAMESPACE_TOPSIDE_BEGIN


bool SingleMachine::Open(void(*arg_fn)()) {
	using namespace Parallel;
	using namespace Serial;
	
	SetCoutLog();
	
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
    
    mach.Add<ModelCache>();
    
	#ifdef flagGUI
    mach.Add<Gu::GuboSystem>();
    #endif
    
    #if IS_TS_CORE && defined flagGUI
    mach.Add<Gu::SurfaceSystem>();
    #endif
    
    #if IS_UPP_CORE && defined flagGUI
    mach.Add<WindowSystem>();
    #endif
    
	
    reg->SetAppName("Non-screen machine");
    
    if (arg_fn)
        arg_fn();
    
    if (!mach.Start()) {
		#ifdef flagDEBUG
        LOG("SingleMachine::Open: error: machine failed to start");
        #endif
		return false;
    }
	
	return true;
}

void SingleMachine::Close() {
	using namespace Parallel;
	
	Machine& mach = GetActiveMachine();
	mach.Stop();
}


NAMESPACE_TOPSIDE_END
