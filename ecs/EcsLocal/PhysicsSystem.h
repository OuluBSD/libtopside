#ifndef _EcsLocal_PhysicsSystem_h_
#define _EcsLocal_PhysicsSystem_h_


NAMESPACE_ECS_BEGIN


class PhysicsSystem : public System<PhysicsSystem>
{
	
protected:
    void Update(double dt) override;
    
    
public:
    vec3	gravity;
    
    PhysicsSystem(Engine& e);

    
};


NAMESPACE_ECS_END


#endif
