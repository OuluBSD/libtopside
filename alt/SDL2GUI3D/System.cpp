#include "System.h"
#include <FusionCore/FusionCore.h>

NAMESPACE_TOPSIDE_BEGIN




bool SDL2GUI3DSystem::Initialize() {
	return gui.Open();
}

void SDL2GUI3DSystem::Start() {
	
}

void SDL2GUI3DSystem::Update(double dt) {
	
}

void SDL2GUI3DSystem::Stop() {
	
}

void SDL2GUI3DSystem::Uninitialize() {
	gui.Close();
}


NAMESPACE_TOPSIDE_END

NAMESPACE_UPP

bool Open_SDL2GUI3D_ECS(bool gui) {
	using namespace Topside;
	Machine& mach = Topside::GetMachine();
	
	RegistrySystem& reg = *mach.Add<RegistrySystem>();
	EntityStore& ents = *mach.Add<EntityStore>();
    mach.Add<ComponentStore>();
    //mach.Add<ConnectorSystem>();
    TODO
    
    mach.Add<SDL2System>();
    mach.Add<SDL2GUI3DSystem>();
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
    //app->Find<Connector>()->ConnectAll();
    TODO
    
	return true;
}

void Close_SDL2GUI3D_ECS() {
	using namespace Topside;
	Machine& mach = Topside::GetMachine();
	
	mach.Stop();
}


END_UPP_NAMESPACE
