#ifndef _System_WorldLogic_h_
#define _System_WorldLogic_h_

NAMESPACE_ECS_BEGIN
	
class WorldLogicSystem : public System<WorldLogicSystem>
{
	
	
public:
	SYS_RTTI(WorldLogicSystem)
    ECS_SYS_CTOR(WorldLogicSystem)
	ECS_SYS_DEF_VISIT
	
	void Attach(Transform* t);
	void Detach(Transform* t);
	
protected:
	void Update(double dt) override;
	void UpdateByVisit(double dt);
	void UpdateByList(double dt);
	void UpdateTransform(Transform& t, double dt);
	
	Vector<Transform*> list;
	
};

NAMESPACE_ECS_END

#endif
