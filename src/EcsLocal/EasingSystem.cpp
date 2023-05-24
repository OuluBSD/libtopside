#include "EcsLocal.h"


NAMESPACE_ECS_BEGIN





void Easing::Etherize(Ether& e) {
	e % target_position
	  % target_orientation
	  % position_easing_factor
	  % orientation_easing_factor;
}

void Easing::Initialize() {
	Ref<EasingSystem> sys = GetEngine().TryGet<EasingSystem>();
	if (sys)
		sys->Attach(this);
}

void Easing::Uninitialize() {
	Ref<EasingSystem> sys = GetEngine().TryGet<EasingSystem>();
	if (sys)
		sys->Detach(this);
}






void EasingSystem::Update(double dt)
{
	for (Easing* easing : comps) {
		Ref<Transform> transform = easing->GetEntity()->Find<Transform>();
		if (!transform)
			continue;
        
        TODO
    }
}

void EasingSystem::Attach(Easing* e) {
	VectorFindAdd(comps, e);
}

void EasingSystem::Detach(Easing* e) {
	VectorRemoveKey(comps, e);
}

 

NAMESPACE_ECS_END

