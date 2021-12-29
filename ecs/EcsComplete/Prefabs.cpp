#include "EcsComplete.h"

NAMESPACE_ECS_BEGIN


void DefaultEcsInitializer() {
	Engine& eng = GetActiveEngine();
	eng.GetAdd<RenderingSystem>();
	eng.GetAdd<EntityStore>();
	eng.GetAdd<ComponentStore>();
	#ifdef flagODE
	eng.GetAdd<OdeSystem>();
	#else
	eng.GetAdd<TosSystem>();
	#endif
	eng.GetAdd<EventSystem>();
	
	Serial::Machine& mach = Serial::GetActiveMachine();
	//eng.GetAdd<PhysicsSystem>();
	
	DefaultSerialInitializerInternalEon();
}


void DefaultEcsStartup() {
	/*Engine& eng = GetActiveEngine();
	EntityStoreRef ents = eng.Get<EntityStore>();
	RenderingSystemRef rend = eng.Get<RenderingSystem>();
	PoolRef models = ents->GetRoot()->GetAddPool("models");
	PoolRef cameras = ents->GetRoot()->GetAddPool("cameras");
	EntityRef gnd = models->Create<StaticGroundPlanePrefab>();
	EntityRef car = models->Create<BuggyCarPrefab>();
	EntityRef cam = cameras->Create<CameraPrefab>();
	
	Ref<ChaseCam> chaser = cam->Add<ChaseCam>();
	chaser->SetTarget(car->Get<Transform>());
	rend->AddViewable(cam->Get<Viewable>());*/
}


NAMESPACE_ECS_END
