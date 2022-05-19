#ifndef _EcsLocal_PhysicsSystem_h_
#define _EcsLocal_PhysicsSystem_h_


NAMESPACE_ECS_BEGIN


class PhysicsSystem : public System<PhysicsSystem>
{
	bool debug_log = false;
	
protected:
    void Update(double dt) override;
	bool Arg(String key, Object value) override;
    
    
public:
    vec3	gravity;
    
    PhysicsSystem(Engine& e);

    
};


class PhysicsBody : public Component<PhysicsBody> {
	
public:
	RTTI_COMP0(PhysicsBody)
	COMP_DEF_VISIT
	
	bool Arg(String key, Object value) override;
	
    void operator=(const PhysicsBody& r) {
        
    }
    
	
};



NAMESPACE_ECS_END


#endif
