#include "EcsLib.h"

using namespace Neso;

NAMESPACE_OULU_BEGIN

ComponentMap ToolSelectorPrefab::Make(ComponentStore& store)
{
    auto components = EntityPrefab::Make(store);

    components.Get<RigidBody>()->angular_velocity = { 0.0f, -3.0f, 0.0f }; // Spin in place
    components.Get<RigidBody>()->damping_factor = 1.0f;
    components.Get<Easing>()->PositionEasingFactor = 0.1f;

    return components;
}

NAMESPACE_OULU_END
