#include "EcsComplete.h"

NAMESPACE_ECS_BEGIN


void DefaultEcsInitializer() {
	Engine& eng = GetActiveEngine();
	eng.GetAdd<ModelCache>();
	eng.GetAdd<EntityStore>();
	eng.GetAdd<ComponentStore>();
	#ifdef flagODE
	eng.GetAdd<OdeSystem>();
	#endif
	//eng.GetAdd<EventSystem>();
	
	Serial::Machine& mach = Serial::GetActiveMachine();
	
	DefaultSerialInitializerInternalEon();
}


void DefaultEcsStartup() {
	
}


NAMESPACE_ECS_END
