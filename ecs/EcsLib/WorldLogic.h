#ifndef _System_WorldLogic_h_
#define _System_WorldLogic_h_

NAMESPACE_OULU_BEGIN
	
// AppLogicSystem
// Simple system to destroy objects that get too far away from the user
class WorldLogicSystem : public System<WorldLogicSystem>
{
public:
    using System::System;

protected:
    void Update(double /*dt*/) override
    {
        EntityComponentVisitor<Transform> visitor(machine);
		visitor.Skip(Pool::BIT_TRANSFORM);
        for (;visitor; visitor++)
        {
            EntityRef entity = *visitor;
            Transform* transform = visitor.Get<Transform>();

            // Destroy any objects that fall too far away (Baseballs and Bullets)
            if (transform->position[1] < -1000.0f)
            {
                entity->Destroy();
            }
        }
    }
};

NAMESPACE_OULU_END

#endif
