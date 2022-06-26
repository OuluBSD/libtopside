#include "EcsLocal.h"


NAMESPACE_ECS_BEGIN

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
        //transform->data.position = lerp(transform->position, easing->target_position, easing->position_easing_factor);
        //transform->data.orientation = slerp(transform->orientation, easing->target_orientation, easing->orientation_easing_factor);
    }
}

void EasingSystem::Attach(Easing* e) {
	VectorFindAdd(comps, e);
}

void EasingSystem::Detach(Easing* e) {
	VectorRemoveKey(comps, e);
}

 

NAMESPACE_ECS_END

