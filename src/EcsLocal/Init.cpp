#include "EcsLocal.h"

NAMESPACE_UPP_BEGIN

INITBLOCK_(EcsLocal) {
	using namespace Serial;
	using namespace Ecs;
	
	
	// System
	Engine::Register<EasingSystem>("easing");
	Engine::Register<WorldLogicSystem>("world.logic");
	Engine::Register<PhysicsSystem>("physics");
	Engine::Register<PaintStrokeSystemBase>("paintstroke");
	Engine::Register<ToolboxSystemBase>("toolbox");
	Engine::Register<PaintingInteractionSystemBase>("painting");
	Engine::Register<ShootingInteractionSystemBase>("shooting");
	Engine::Register<ThrowingInteractionSystemBase>("throwing");
	Engine::Register<PlayerBodySystem>("player");
	Engine::Register<InteractionSystem>("interaction");
	Engine::Register<Ecs::DesktopSuiteSystem>("desktop");
	
	
	// Component
	ComponentFactory::Register<RigidBody>("body");
	//ComponentFactory::Register<StaticVolumeComponent>("");
	ComponentFactory::Register<TextRenderable>("text");
	ComponentFactory::Register<Easing>("easing");
	ComponentFactory::Register<PhysicsBody>("physics");
	ComponentFactory::Register<ToolComponent>("tool");
	ComponentFactory::Register<PaintComponent>("paint");
	ComponentFactory::Register<ShootingComponent>("shoot");
	ComponentFactory::Register<ThrowingComponent>("throw");
	ComponentFactory::Register<PlayerHandComponent>("player.hand");
	ComponentFactory::Register<PlayerHeadComponent>("player.head");
	ComponentFactory::Register<PlayerBodyComponent>("player.body");
#ifdef flagGUI
	ComponentFactory::Register<DefaultGuiAppComponent>("");
#endif
	
	
	
	DesktopFactory::Register<GuiTesterApp>("guitester");
	
	
	
}

NAMESPACE_UPP_END
