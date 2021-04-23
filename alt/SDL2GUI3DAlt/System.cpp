#include "System.h"
#include <FusionCore/FusionCore.h>

NAMESPACE_OULU_BEGIN


SDL2GUI3DAltSystem::SDL2GUI3DAltSystem(Machine& m) : System<SDL2GUI3DAltSystem>(m), gui(this) {
	
}

bool SDL2GUI3DAltSystem::Initialize() {
	return gui.Open();
}

void SDL2GUI3DAltSystem::Start() {
	
}

void SDL2GUI3DAltSystem::Update(float dt) {
	
}

void SDL2GUI3DAltSystem::Stop() {
	
}

void SDL2GUI3DAltSystem::Uninitialize() {
	gui.Close();
}


NAMESPACE_OULU_END

NAMESPACE_UPP

bool Open_SDL2GUI3DAlt_ECS(bool gui) {
	using namespace Oulu;
	Machine& mach = Oulu::GetMachine();
	
	RegistrySystem& reg = *mach.Add<RegistrySystem>();
	EntityStore& ents = *mach.Add<EntityStore>();
    mach.Add<ComponentStore>();
    mach.Add<ConnectorSystem>();
    
    mach.Add<SDL2System>();
    mach.Add<SDL2GUI3DAltSystem>();
    mach.Add<EventSystem>();
    mach.Add<RenderingSystem>();
    mach.Add<AudioSystem>();
    mach.Add<FusionSystem>();
    
    if (gui)
		mach.Add<WindowSystem>();
	
    /*mach.Add<HolographicScene>();
    mach.Add<EasingSystem>();
    mach.Add<AudioSystem>();
    mach.Add<ControllerSystem>();
    mach.Add<MotionControllerSystem>();
    mach.Add<WorldLogicSystem>();
	   
    bool physics = false;
    if (physics)
		mach.Add<PhysicsSystem>();*/
	
    
    #ifdef flagOPENVR
    mach.Add<OpenVR>();
    #endif
    
    reg.SetAppName("SDL2 ECS machine");
    
    if (!mach.Start())
		return false;
    
    EntityRef app = ents.Create<StandaloneWindow>();
    app->Find<Connector>()->ConnectAll();
    
	return true;
}

void Close_SDL2GUI3DAlt_ECS() {
	using namespace Oulu;
	Machine& mach = Oulu::GetMachine();
	
	mach.Stop();
}


END_UPP_NAMESPACE
