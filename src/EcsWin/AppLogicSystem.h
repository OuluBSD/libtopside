#if 0
#pragma once


namespace DemoRoom
{

////////////////////////////////////////////////////////////////////////////////
// AppLogicSystem
// Simple system to destroy objects that get too far away from the user
class AppLogicSystem : public Neso::System<AppLogicSystem>
{
public:
    using System::System;

protected:
    void Update(double /*dt*/) override
    {
        for (auto &componentSet : m_engine.Get<Neso::EntityStore>()->GetComponentsWithEntity<Neso::Transform>())
        {
            auto[entity, transform] = componentSet;

            // Destroy any objects that fall too far away (Baseballs and Bullets)
            if (transform->position.y < -10.0f)
            {
                entity->Destroy();
            }
        }
    }
};

}
#endif
