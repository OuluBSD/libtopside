#ifndef _EcsLocal_PhysicsSystem_h_
#define _EcsLocal_PhysicsSystem_h_


NAMESPACE_ECS_BEGIN


class PhysicsBody;


class PhysicsSystem : public System<PhysicsSystem>
{
	Vector<PhysicsBody*> bodies;
	double time = 0;
	double last_dt = 0;
	bool debug_log = false;
	
	
	float area_length = 100.0f;
	bool remove_outside_area = false;
	
	
	void TestPlayerLookFn(PhysicsBody& b, Point mouse_diff);
	void TestPlayerMoveFn(PhysicsBody& b, vec3 rel_dir, float step);
	
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
	
	int test_fn;
	bool is_bound = false;
	
	Ref<Transform> trans;
	Ref<PlayerBodyComponent> player;
	
public:
	RTTI_COMP0(PhysicsBody)
	COMP_DEF_VISIT_(vis & trans & player)
	
	void Etherize(Ether& e) override;
	void Initialize() override;
	void Uninitialize() override;
	bool Arg(String key, Object value) override;
	
    void operator=(const PhysicsBody& r);
    
	bool BindDefault();
	void UnbindDefault();
	
};

using PhysicsBodyRef = Ref<PhysicsBody>;



NAMESPACE_ECS_END


#endif
