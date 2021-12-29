#ifndef _Physics_TSystem_h_
#define _Physics_TSystem_h_

NAMESPACE_ECS_BEGIN


template <class Fys>
struct SystemT :
	SpaceT<Fys>,
	System<SystemT<Fys>>
{
	using Base = SystemT<Fys>;
	using Node = NodeT<Fys>;
	using Space = SpaceT<Fys>;
	using EcsSystem = System<SystemT<Fys>>;
	using NativeWorld = typename Fys::NativeWorld;
	using NativeSpace = typename Fys::NativeSpace;
	using NativeJointGroup = typename Fys::NativeJointGroup;
	using NativeThreading = typename Fys::NativeThreading;
	using NativeThreadPool = typename Fys::NativeThreadPool;
	using NativeGeom = typename Fys::NativeGeom;
	using NativeContact = typename Fys::NativeContact;
	using FysSystem = typename Fys::System;
	
protected:
	NativeWorld world;
	NativeJointGroup contactgroup;
	NativeThreading threading;
	NativeThreadPool pool;
	
	
public:
	RTTI_DECL2(SystemT, Space, EcsSystem)
	using Parent = Engine;
	
	static vec3 EarthGravity() {return vec3(0, -9.81, 0);}
	
	typedef SystemT<Fys> CLASSNAME;
	SystemT(Engine& e) {
		world = Null;
		contactgroup = Null;
		threading = Null;
		pool = Null;
		
		this->SetParent(e);
		Fys::InitializeLibrary();
		Fys::CreateWorld(world);
		
		this->SetRoot();
		this->OnAttach();
		
		Fys::CreateJointGroup(contactgroup);
		
		SetGravity(EarthGravity());
		SetIterationCount(64);
		
		Fys::CreateThreading(threading);
		Fys::CreateThreadPool(pool);
		Fys::AttachThreadPool(threading, pool);
		Fys::AttachThreading(world, threading);
	}
	
	~SystemT() {
		Fys::DetachThreading(threading);
		Fys::ClearThreadPool(pool);
		Fys::DetachThreading(world);
		Fys::ClearThreading(threading);
		
		Fys::DetachJointGroup(contactgroup);
		Fys::ClearJointGroup(contactgroup);
		Fys::ClearSpace(this->space);
		Fys::ClearWorld(world);
		Fys::UninitializeLibrary();
	}
	
	void Visit(RuntimeVisitor& vis) override {VIS_THIS(Space)}
	
    bool Initialize() override {
		SetGravity(vec3(0, -0.5, 0));
		return true;
	}
    void Start() override {}
    void Update(double dt) override {
		Collide();
		StepWorld(dt);
		RemoveContactJoints();
	}
    void Stop() override {}
    void Uninitialize() override {}
    
	void SetGravity(const vec3& v) {Fys::SetGravity(world, v);}
	void SetCFM(float f) {Fys::SetWorldCFM(world, f);}
	void SetConstraintForceMixing(float f) {Fys::SetWorldCFM(world, f);}
	void SetContactMaxCorrectingVel(float f) {Fys::SetMaxCorrectingVelocity(world, f);}
	void SetContactSurfaceLayer(float f) {Fys::SetContactSurfaceLayer(world, f);}
	void SetAutoDisableFlag(bool b) {Fys::SetAutoDisable(world, b);}
	void SetIterationCount(int i) {Fys::SetStepIterations(world, i);}
	void SetAutoDisableAverageSamplesCount(int i) {Fys::SetAutoDisableSamples(world, i);}
	
	const NativeWorld& GetWorld() const {ASSERT(world); return world;}
	const NativeJointGroup& GetJointGroup() const {ASSERT(contactgroup); return contactgroup;}
	NativeWorld& GetWorld() {ASSERT(world); return world;}
	NativeJointGroup& GetJointGroup() {ASSERT(contactgroup); return contactgroup;}
	
	void Collide() {ASSERT(this->space); Fys::Collide(this->space, this, &SystemT::StaticNearCallback);}
	void StepWorld(double seconds) {Fys::Step(world, seconds);}
	void RemoveContactJoints() {Fys::DetachJointGroup(contactgroup);}
	
	virtual void NearCallback(void *, NativeGeom& o1, NativeGeom& o2);
	static void StaticNearCallback(void *data, NativeGeom& o1, NativeGeom& o2) {((SystemT*)data)->NearCallback(NULL, o1, o2);}
	
	String ToString() const override {return Fys::Id() + "System";}
	
	static void AddEngineSystem();
	
};


NAMESPACE_ECS_END

#endif