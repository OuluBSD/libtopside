#ifndef _EcsLocal_PhysicsSystem_h_
#define _EcsLocal_PhysicsSystem_h_


NAMESPACE_ECS_BEGIN


class PhysicsBody;


class PhysicsSystem : public System<PhysicsSystem>
{
	Vector<PhysicsBody*> bodies;
	double time = 0;
	bool debug_log = false;
	
protected:
    void Update(double dt) override;
	bool Arg(String key, Object value) override;
    
    void RunTestFn(PhysicsBody& b);
public:
    vec3	gravity;
    
    PhysicsSystem(Engine& e);

    
    void Attach(PhysicsBody& b);
    void Detach(PhysicsBody& b);
    
};


class PhysicsBody : public Component<PhysicsBody> {
	
public:
	friend class PhysicsSystem;
	
	enum {
		TESTFN_NULL,
		TESTFN_FIXED,
		TESTFN_CIRCLE,
	};
	
	int test_fn = 0;
	Ref<Transform> trans;
	
public:
	RTTI_COMP0(PhysicsBody)
	COMP_DEF_VISIT_(vis & trans)
	
	void Initialize() override;
	bool Arg(String key, Object value) override;
	
    void operator=(const PhysicsBody& r) {
        
    }
    
	
};



NAMESPACE_ECS_END


#endif
