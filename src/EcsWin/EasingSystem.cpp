#if 0
#include "EcsWin.h"


using namespace winrt::Windows::Foundation::Numerics;

void EasingSystem::Update(double dt)
{
    for (auto& componentSet : m_engine.Get<EntityStore>()->GetComponents<Transform, Easing>())
    {
        auto transform = std::get<Transform*>(componentSet);
        auto easing = std::get<Easing*>(componentSet);

        transform->position = lerp(transform->position, easing->TargetPosition, easing->PositionEasingFactor);
        transform->orientation = slerp(transform->orientation, easing->TargetOrientation, easing->OrientationEasingFactor);
    }
}
#endif
