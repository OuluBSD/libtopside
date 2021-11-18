#include <EcsLocal/EcsLocal.h>
#include "After.h"

NAMESPACE_UPP





//SDL2GUI3D_MachineData	__sdl2data;
SDL2GUI3D*				__current_SDL2GUI3D;



SDL2GUI3D::SDL2GUI3D(void* sys) : sys(sys) {
	__current_SDL2GUI3D = this;
	//data = &__sdl2data;
	desired_title = "Unnamed";
	
}

SDL2GUI3D::~SDL2GUI3D() {
	/*if (is_open)
		Close();*/
}

void SDL2GUI3D::RecvAudio(Uint8* stream, int len) {
	TODO
	//if (aout)
	//	aout->SinkCallback(stream, len);
}

SDL2GUI3D* SDL2GUI3D::Current() {
	return __current_SDL2GUI3D;
}

/*bool SDL2GUI3D::InitMachine() {
	Machine& mach = GetMachine();
	
	try {
	    mach.Add<RegistrySystem>();
	    mach.Add<HumanSystem>();
	    mach.Add<DisplaySystem>();
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

bool SDL2GUI3D::DeinitMachine() {
	GetMachine().SetNotRunning();
	
	return true;
}*/

bool SDL2GUI3D::Open() {
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

void SDL2GUI3D::Close() {
	//OOSDL2::Bundle::Close();
}







END_UPP_NAMESPACE
