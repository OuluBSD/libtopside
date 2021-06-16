#include "EcsLocal.h"

NAMESPACE_TOPSIDE_BEGIN


void EasingSystem::Update(double dt)
{
	EntityComponentVisitor<Transform, Easing> visitor(GetMachine());
	visitor.Skip(Pool::BIT_TRANSFORM);
	for (; visitor; visitor++) {
        auto transform = visitor.Get<Transform>();
        auto easing = visitor.Get<Easing>();

        transform->position = lerp(transform->position, easing->target_position, easing->position_easing_factor);
        transform->orientation = slerp(transform->orientation, easing->target_orientation, easing->orientation_easing_factor);
    }
}
	

NAMESPACE_TOPSIDE_END
