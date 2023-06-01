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
	#define COMP(t, k, v) ComponentFactory::Register<t>(k);
	#include "Types.inl"
	#undef COMP
	
	
	DesktopFactory::Register<GuiTesterApp>("guitester");
	
	
}

NAMESPACE_UPP_END
