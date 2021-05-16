#ifndef _System_WorldLogic_h_
#define _System_WorldLogic_h_

NAMESPACE_TOPSIDE_BEGIN
	
class WorldLogicSystem : public System<WorldLogicSystem>
{
	void Visit(RuntimeVisitor& vis) override {}
	
public:
    SYS_CTOR(WorldLogicSystem)

protected:
    void Update(double dt) override
    {
        EntityComponentVisitor<Transform> visitor(GetMachine());
		visitor.Skip(Pool::BIT_TRANSFORM);
        for (;visitor; visitor++)
        {
            EntityRef entity = *visitor;
            Transform* transform = visitor.Get<Transform>();
			
            if (transform->position[1] < -1000.0f)
            {
                entity->Destroy();
            }
        }
    }
};

NAMESPACE_TOPSIDE_END

#endif
