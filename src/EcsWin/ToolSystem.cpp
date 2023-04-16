#include "EcsWin.h"


NAMESPACE_WIN_BEGIN


ComponentMap ToolSelectorPrefab::Make(ComponentStore& store)
{
    auto components = EntityPrefab::Make(e);

    components.Get<RigidBody>()->angularVelocity = { 0.0f, -3.0f, 0.0f }; // Spin in place
    components.Get<RigidBody>()->dampingFactor = 1.0f;
    components.Get<Easing>()->PositionEasingFactor = 0.1f;

    return components;
}


NAMESPACE_WIN_END
