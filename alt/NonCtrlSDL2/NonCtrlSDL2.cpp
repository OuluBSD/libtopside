#include "NonCtrlSDL2.h"
#include <SerialLib/SerialLib.h>
#include <AtomSDL2/AtomSDL2.h>
//#include <Physics/Physics.h>

NAMESPACE_TOPSIDE_BEGIN


bool SingleMachine::Open(bool ecs) {
	using namespace Serial;
	
	const AppFlags& flags = GetAppFlags();
	Machine& mach = GetActiveMachine();
	
	
	RegistrySystemRef reg	= mach.Add<RegistrySystem>();
	LoopStoreRef ents		= mach.Add<LoopStore>();
    
    mach.Add<AtomStore>();
    mach.Add<AtomSystem>();
    mach.Add<ScriptLoader>();
    mach.Add<PacketTracker>();
    
    
    if (ecs)
		mach.Add<EntitySystem>();
	
    /*mach.Add<HolographicScene>();
    mach.Add<EasingSystem>();
    mach.Add<MotionControllerSystem>();
    mach.Add<WorldLogicSystem>();*/
	   
    //if (flags.HaveOdePhysics())
	//	mach.Add<OdeSystem>();
	
    
    #ifdef flagOPENVR
    mach.Add<OpenVR>();
    #endif
    
    reg->SetAppName("SDL2 ECS machine");
    
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
