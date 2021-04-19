#include <EcsLib/EcsLib.h>
#include "After.h"

NAMESPACE_UPP





//SDL2GUI3DAlt_MachineData	__sdl2data;
SDL2GUI3DAlt*				__current_SDL2GUI3DAlt;



SDL2GUI3DAlt::SDL2GUI3DAlt(void* sys) : sys(sys) {
	__current_SDL2GUI3DAlt = this;
	//data = &__sdl2data;
	desired_title = "Unnamed";
	
}

SDL2GUI3DAlt::~SDL2GUI3DAlt() {
	/*if (is_open)
		Close();*/
}

void SDL2GUI3DAlt::RecvAudio(Uint8* stream, int len) {
	if (aout)
		aout->Put(stream, len);
}

SDL2GUI3DAlt* SDL2GUI3DAlt::Current() {
	return __current_SDL2GUI3DAlt;
}

/*bool SDL2GUI3DAlt::InitMachine() {
	Machine& mach = GetMachine();
	
	try {
	    mach.Add<RegistrySystem>();
	    mach.Add<EventSystem>();
	    mach.Add<RenderingSystem>();
	    mach.Add<WindowSystem>();
	    #ifdef flagOPENVR
	    mach.Add<OpenVR>();
	    #endif
	    
	    EntityStore& ents = *mach.Add<EntityStore>();
	    mach.Add<ComponentStore>();
	    mach.Add<HolographicScene>();
	    mach.Add<EasingSystem>();
	    mach.Add<AudioSystem>();
	    mach.Add<ControllerSystem>();
	    mach.Add<MotionControllerSystem>();
	    mach.Add<WorldLogicSystem>();
	    
	    bool physics = false;
	    if (physics)
			mach.Add<PhysicsSystem>();
	
	    mach.Start();
	    
		ents.Create<CameraPrefab>();
	}
	catch (Exc e) {
		LOG("InitMachine error: " << e);
		return false;
	}
	
	return true;
}

bool SDL2GUI3DAlt::DeinitMachine() {
	GetMachine().SetNotRunning();
	
	return true;
}*/

bool SDL2GUI3DAlt::Open() {
	ASSERT(!VirtualGui3DAltPtr);
	VirtualGui3DAltPtr = this;
	
	/*AddDefaultComponents();
	aout = FindComponent<OOSDL2::AudioOutput>();
	scr = FindComponent<OOSDL2::Screen>();
	ev = FindComponent<OOSDL2::Events>();
	
	if (scr) {
		scr->Sizeable();
		//scr->Maximize();
		//scr->Fullscreen();
		scr->SetTitle(desired_title);
	}
	
	if (!OOSDL2::Bundle::Open())
		return false;
	
	
	return true;*/
	
	return true;
}

void SDL2GUI3DAlt::Close() {
	//OOSDL2::Bundle::Close();
}







END_UPP_NAMESPACE
