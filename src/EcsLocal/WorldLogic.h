#ifndef _System_WorldLogic_h_
#define _System_WorldLogic_h_

NAMESPACE_ECS_BEGIN
	
class WorldLogicSystem : public System<WorldLogicSystem>
{
	
	
public:
	SYS_RTTI(WorldLogicSystem)
    ECS_SYS_CTOR(WorldLogicSystem)
	ECS_SYS_DEF_VISIT
	
protected:
    void Update(double dt) override
    {
        EntityComponentVisitor<Transform> visitor(GetEngine());
		visitor.Skip(Pool::BIT_TRANSFORM);
        for (;visitor; visitor++)
        {
            EntityRef entity = *visitor;
            TransformRef transform = visitor.Get<Transform>();
			
            if (transform->position[1] < -1000.0f)
            {
                entity->Destroy();
            }
        }
    }
};

NAMESPACE_ECS_END

#endif
