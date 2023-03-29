#ifndef _Physics_TSystem_h_
#define _Physics_TSystem_h_

NAMESPACE_ECS_BEGIN


template <class Fys>
struct SystemT :
	SpaceT<Fys>,
	Ecs::System<SystemT<Fys>>
{
	using Base = SystemT<Fys>;
	using SP = Ecs::System<SystemT<Fys>>;
	using Node = NodeT<Fys>;
	using Space = SpaceT<Fys>;
	using EcsSystem = Ecs::System<SystemT<Fys>>;
	using NativeWorld = typename Fys::NativeWorld;
	using NativeSpace = typename Fys::NativeSpace;
	using NativeJointGroup = typename Fys::NativeJointGroup;
	using NativeThreading = typename Fys::NativeThreading;
	using NativeThreadPool = typename Fys::NativeThreadPool;
	using NativeGeom = typename Fys::NativeGeom;
	
protected:
	NativeWorld world = NULL;
	NativeJointGroup contactgroup = NULL;
	NativeThreading threading = NULL;
	NativeThreadPool pool = NULL;
	
	
public:
	RTTI_DECL2(Base, Space, EcsSystem)
	using Parent = Engine;
	
	static vec3 EarthGravity() {return vec3(0,-9.81,0);}
	
	ECS_SYS_CTOR_(SystemT) {
		Fys::InitializeLibrary();
		Fys::CreateWorld(world);
		
		this->SetRoot();
		this->OnAttach();
		
		Fys::CreateJointGroup(contactgroup);
		
		SetGravity(EarthGravity()[1]);
		SetIterationCount(64);
		
		Fys::CreateThreading(threading);
		Fys::CreateThreadPool(pool);
		Fys::AttachThreadPool(threading, pool);
		Fys::AttachThreading(world, threading);
	}
	 SYS_DEF_VISIT
	
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
	
    bool Initialize() override {
		SetGravity(-0.5);
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
    
	void SetGravity(float f) {Fys::SetGravity(world, f);}
	void SetCFM(float f) {Fys::SetWorldCFM(world, f);}
	void SetConstraintForceMixing(float f) {Fys::SetWorldCFM(world, f);}
	void SetContactMaxCorrectingVel(float f) {Fys::SetMaxCorrectingVelocity(world, f);}
	void SetContactSurfaceLayer(float f) {Fys::SetContactSurfaceLayer(world, f);}
	void SetAutoDisableFlag(bool b) {Fys::SetAutoDisable(world, b);}
	void SetIterationCount(int i) {Fys::SetStepIterations(world, i);}
	void SetAutoDisableAverageSamplesCount(int i) {Fys::SetAutoDisableSamples(world, i);}
	
	NativeWorld GetWorldId() const {ASSERT(world); return world;}
	NativeJointGroup GetJointGroupId() const {ASSERT(contactgroup); return contactgroup;}
	
	void Collide() {ASSERT(this->space); Fys::Collide(this->space, this, &StaticNearCallback);}
	void StepWorld(double seconds) {Fys::Step(this->world, seconds);}
	void RemoveContactJoints() {Fys::DetachJointGroup(contactgroup);}
	
	virtual void NearCallback(void *, NativeGeom o1, NativeGeom o2) {TODO}
	static void StaticNearCallback(void *data, NativeGeom o1, NativeGeom o2) {((SystemT*)data)->NearCallback(NULL, o1, o2);}
	
};


NAMESPACE_ECS_END

#endif
