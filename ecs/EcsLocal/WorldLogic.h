#ifndef _System_WorldLogic_h_
#define _System_WorldLogic_h_

NAMESPACE_TOPSIDE_BEGIN
	
class WorldLogicSystem : public System<WorldLogicSystem>
{
	
	
public:
	SYS_RTTI(WorldLogicSystem)
    SYS_CTOR(WorldLogicSystem)
	SYS_DEF_VISIT
	
protected:
    void Update(double dt) override
    {
        EntityComponentVisitor<Transform> visitor(GetMachine());
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

NAMESPACE_TOPSIDE_END

#endif