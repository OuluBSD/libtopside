#include "EcsLib.h"

NAMESPACE_OULU_BEGIN


void EasingSystem::Update(double dt)
{
	EntityComponentVisitor<Transform, Easing> visitor(machine);
	visitor.Skip(EntityPool::BIT_TRANSFORM);
	for (; visitor; visitor++) {
        auto transform = visitor.Get<Transform>();
        auto easing = visitor.Get<Easing>();

        transform->position = lerp(transform->position, easing->TargetPosition, easing->PositionEasingFactor);
        transform->orientation = slerp(transform->orientation, easing->TargetOrientation, easing->OrientationEasingFactor);
    }
}
	

NAMESPACE_OULU_END
