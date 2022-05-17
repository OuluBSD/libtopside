#include "EcsVirtualGui.h"

NAMESPACE_ECS_BEGIN





//EcsVirtualGui_MachineData	__sdl2data;
VirtualGui*				__current_VirtualGui;



VirtualGui::VirtualGui(VirtualGuiSystem* sys) : sys(sys) {
	__current_VirtualGui = this;
	//data = &__sdl2data;
	title = "Unnamed";
	
}

VirtualGui::~VirtualGui() {
	/*if (is_open)
		Close();*/
}

void VirtualGui::Clear() {
	
}

void VirtualGui::RecvAudio(byte* stream, int len) {
	TODO
	//if (aout)
	//	aout->SinkCallback(stream, len);
}

VirtualGui* VirtualGui::Current() {
	return __current_VirtualGui;
}

/*bool VirtualGui::InitMachine() {
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

bool VirtualGui::DeinitMachine() {
	GetMachine().SetNotRunning();
	
	return true;
}*/

bool VirtualGui::Open() {
	ASSERT(!VirtualGui3DPtr);
	VirtualGui3DPtr = this;
	
	//AddDefaultComponents();
	
	Engine& eng = sys->GetEngine();
	Serial::EntitySystem& esys = eng.GetEntitySystem();
	Machine& mach = esys.GetMachine();
	
	rend = eng.Get<Ecs::RenderingSystem>();
	if (!rend) {
		LOG("VirtualGui::Open: error: could not find RenderingSystem");
		return false;
	}
	
	title = "VirtualGui";
	screen_sz = Size(1280,720);
	
	/*if (0)
		;
	#ifdef flagSDL2
	else if (rend->sdl_sw_buf) {
		buf = rend->sdl_sw_buf;
	}
	#ifdef flagOGL
	else if (rend->sdl_ogl_buf) {
		buf = rend->sdl_ogl_buf;
	}
	#endif
	#endif
	else {
		LOG("VirtualGui::Open: error: no rendering buffers set");
		return false;
	}
	
	TODO*/
	
	/*aout = FindComponent<OOSDL2::AudioOutput>();
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
	*/
	
	
	return true;
}

void VirtualGui::Close() {
	//OOSDL2::Bundle::Close();
}


bool VirtualGui::Poll(UPP::CtrlEvent& e) {
	TODO
	//return ev ? ev->Poll(e) : false;
}
Size VirtualGui::GetSize() {
	return screen_sz;
	//return scr ? scr->GetSize() : Size(0,0);
}

void VirtualGui::SetTitle(String title) {
	this->title = title;
	//desired_title = title; if (scr) scr->SetTitle(title);
}

SystemDraw& VirtualGui::BeginDraw() {
	TODO
	//return scr ? scr->BeginDraw() : empty_draw;
}

void VirtualGui::CommitDraw() {
	TODO
	//if (scr) scr->CommitDraw();
}

uint32 VirtualGui::GetTickCount() {
	TODO
	//return ev ? ev->GetTickCount() : 0;
}

void VirtualGui::WaitEvent(int ms) {
	TODO
	//if (ev) ev->WaitEvent(ms);
}

bool VirtualGui::IsWaitingEvent() {
	TODO
	//return ev ? ev->IsWaitingEvent() : false;
}

void VirtualGui::WakeUpGuiThread() {
	TODO
	//if (ev) ev->WakeUpEventThread();
}




NAMESPACE_ECS_END
