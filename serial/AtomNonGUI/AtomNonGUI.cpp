#include "AtomNonGUI.h"

NAMESPACE_SERIAL_BEGIN


bool SingleMachine::Open(bool gui) {
	const AppFlags& flags = GetAppFlags();
	Machine& mach = GetActiveMachine();
	
	RegistrySystemRef reg = mach.Add<RegistrySystem>();
	LoopStoreRef loops = mach.Add<LoopStore>();
    mach.Add<AtomStore>();
    mach.Add<AtomSystem>();
    
    reg->SetAppName("SDL2 ECS machine");
    
    if (!mach.Start())
		return false;
    
	return true;
}

void SingleMachine::Close() {
	Machine& mach = GetActiveMachine();
	mach.Stop();
}


NAMESPACE_SERIAL_END
