#ifndef _System_OdeSystem_h_
#define _System_OdeSystem_h_

#ifdef flagODE


NAMESPACE_ECS_BEGIN

class OdeSystem;

NAMESPACE_ECS_END


NAMESPACE_TOPSIDE_BEGIN


class OdeSpace;

class OdeNode : RTTIBase {
	
protected:
	OdeNode* owner = NULL;
	Vector<OdeNode*> nodes;
	
public:
	RTTI_DECL0(OdeNode)
	
	OdeNode() {}
	virtual ~OdeNode() {}
	
	virtual void Attach(OdeNode& node) {
		node.owner = this;
		nodes.Add(&node);
		node.OnAttach();
	}
	
	virtual void Detach(OdeNode& node) {
		for(int i = 0; i < nodes.GetCount(); i++) {
			if (nodes[i] == &node) {
				node.OnDetach();
				node.owner = NULL;
				nodes.Remove(i);
				break;
			}
		}
	}
	
	virtual void OnAttach() {}
	virtual void OnDetach() {}
	virtual String ToString() {return "OdeNode";}
	
	Ecs::OdeSystem* GetWorld();
	OdeSpace* GetSpace();
	dWorldID GetWorldId();
	dSpaceID GetWorldSpaceId();
};

class OdeObject : public OdeNode {
	
public:
	ModelLoader loader;
	CpuDataObject* cpu_obj = 0;
	OglDataObject* ogl_obj = 0;
	
	GfxDataObject* fb_obj = 0;
	bool model_err = false;
	
	dGeomID geom = 0;
	dBodyID body = 0;
	dMass mass;
	dQuaternion orient = {0,1,0,0};									// Orientation of body is represented as quaternions
	
	bool is_override_phys_geom = false;
	mat4 override_geom;
	mat4 model_geom = identity<mat4>();
	
public:
	RTTI_DECL1(OdeObject, OdeNode)
	typedef OdeObject CLASSNAME;
	OdeObject();
	virtual ~OdeObject();
	
	virtual void LoadModel(GfxDataState& s);
	
	void OnAttach() override {body = dBodyCreate(GetWorldId());} // Create ID for physics body
	void OnDetach() override {DetachContent();}
	virtual void Refresh();
	
	void AttachContent();
	void DetachContent();
	void SetPosition(double x, double y, double z) {dBodySetPosition(body, x, y, z);}
	void SetGeomPosition(double x, double y, double z) {dGeomSetPosition(geom, x, y, z);}
	void SetGeomRotationIdentity(){dMatrix3 R; dRSetIdentity(R); dGeomSetRotation(geom, R);}
	void RotateFromAxisAndAngle(double ax, double ay, double az, double angle) {dMatrix3 R; dRFromAxisAndAngle(R, ax, ay, az, angle); dBodySetRotation(body, R);}
	const dReal* GetBodyPosition() {return dBodyGetPosition(body);}
	void LoadModel(CpuDataState& state);
	void LoadModel(OglDataState& state);
	
	Callback GetRefreshCallback() {return THISBACK(Refresh);}
};

class OdeJoint : public OdeNode {
	
protected:
	dJointID joint;
	dJointFeedback feedback;
	int stress = 0;
	
public:
	RTTI_DECL1(OdeJoint, OdeNode)
	OdeJoint() {
		
	}
	
	void OnAttach() override {
		joint = dJointCreateHinge2(GetWorldId(), 0);	// Create ID for physics joint
		dJointSetFeedback(joint, &feedback);
	}
	
	void AttachHinge(OdeObject& owner, OdeObject& face) {
		dJointAttach(joint, owner.body, face.body);
		const dReal *a = dBodyGetPosition(face.body);
		dJointSetHinge2Anchor(joint, a[0], a[1], a[2]);
		dVector3 xunit = { 1, 0, 0 }, yunit = { 0, 1, 0 }, zunit = { 0, 0, 1 };
		dJointSetHinge2Axis1(joint, yunit[0], yunit[1], yunit[2]);
		dJointSetHinge2Axis2(joint, xunit[0], xunit[1], xunit[2]);
	}
	
	void SetHingeSuspension(double erp, double cfm) {
		dJointSetHinge2Param(joint, dParamSuspensionERP, erp);
		dJointSetHinge2Param(joint, dParamSuspensionCFM, cfm);
	}
	void SetHingeLock() {SetHingeRange(0, 0);}
	void SetHingeRange(double lo, double hi) {dJointSetHinge2Param(joint, dParamLoStop, lo); dJointSetHinge2Param(joint, dParamHiStop, hi);}
	void SetHingeRange1(double lo, double hi) {dJointSetHinge2Param(joint, dParamLoStop1, lo); dJointSetHinge2Param(joint, dParamHiStop1, hi);}
	void SetHingeRange2(double lo, double hi) {dJointSetHinge2Param(joint, dParamLoStop2, lo); dJointSetHinge2Param(joint, dParamHiStop2, hi);}
	void SetHingeRange3(double lo, double hi) {dJointSetHinge2Param(joint, dParamLoStop3, lo); dJointSetHinge2Param(joint, dParamHiStop3, hi);}
	void SetVelocity(double d) {dJointSetHinge2Param(joint, dParamVel, d);}
	void SetVelocity1(double d) {dJointSetHinge2Param(joint, dParamVel1, d);}
	void SetVelocity2(double d) {dJointSetHinge2Param(joint, dParamVel2, d);}
	void SetVelocity3(double d) {dJointSetHinge2Param(joint, dParamVel3, d);}
	void SetMaxForce(double d) {dJointSetHinge2Param(joint, dParamFMax, d);}
	void SetMaxForce1(double d) {dJointSetHinge2Param(joint, dParamFMax1, d);}
	void SetMaxForce2(double d) {dJointSetHinge2Param(joint, dParamFMax2, d);}
	void SetMaxForce3(double d) {dJointSetHinge2Param(joint, dParamFMax3, d);}
	void SetFudgeFactor(double d) {dJointSetHinge2Param(joint, dParamFudgeFactor, d);}
	void SetAnchor(double x, double y, double z) {dJointSetHingeAnchor(joint, x, y, z);}
	void SetAxis(double x, double y, double z) {dJointSetHingeAxis(joint, x, y, z);}
	
	double GetAngle() {return dJointGetHinge2Angle1(joint);}
	
	
};

class OdeSpace : public OdeNode {
	
protected:
	dSpaceID space = NULL;
	bool is_owner = false;
	
public:
	RTTI_DECL1(OdeSpace, OdeNode)
	
	
	void OnAttach() override {
		if (is_owner) {
			space = dHashSpaceCreate(0);
		} else {
			space = dSimpleSpaceCreate(GetWorldSpaceId());
			dSpaceSetCleanup(space, 0);
		}
	}
	
	void SetPortal(bool b=true) {is_owner=b;}
	dSpaceID GetSpaceId() const {ASSERT(space); return space;}
	
};

NAMESPACE_TOPSIDE_END


NAMESPACE_ECS_BEGIN


class OdeSystem : public OdeSpace, public System<OdeSystem> {
	
protected:
	dWorldID world = NULL;
	dJointGroupID contactgroup = NULL;
	dThreadingImplementationID threading = NULL;
	dThreadingThreadPoolID pool = NULL;
	
	
public:
	RTTI_DECL2(OdeSystem, OdeSpace, System<OdeSystem>)
	using Parent = Engine;
	
	static vec3 EarthGravity;
	
	ECS_SYS_CTOR_(OdeSystem) {
		// create world
		dInitODE2(0);
		world = dWorldCreate();
		
		SetPortal();
		OnAttach();
		
		contactgroup = dJointGroupCreate(0);
		SetGravity(EarthGravity[1]);
		SetIterationCount(64);
		
		
		threading = dThreadingAllocateMultiThreadedImplementation();
		pool = dThreadingAllocateThreadPool(4, 0, dAllocateFlagBasicData, NULL);
		dThreadingThreadPoolServeMultiThreadedImplementation(pool, threading);
		dWorldSetStepThreadingImplementation(world, dThreadingImplementationGetFunctions(threading), threading);
		
		dAllocateODEDataForThread(dAllocateMaskAll);
	}
	SYS_DEF_VISIT
	
	~OdeSystem() {
		dThreadingImplementationShutdownProcessing(threading);
		dThreadingFreeThreadPool(pool);
		dWorldSetStepThreadingImplementation(world, NULL, NULL);
		dThreadingFreeImplementation(threading);
		
		dJointGroupEmpty(contactgroup);
		dJointGroupDestroy(contactgroup);
		dSpaceDestroy(space);
		dWorldDestroy(world);
		dCloseODE();
	}
	
    bool Initialize() override {
		SetGravity(-0.5);
		dAllocateODEDataForThread(dAllocateMaskAll);
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
    
	void SetGravity(double d) {dWorldSetGravity(world, 0, d, 0);}
	void SetCFM(double d) {dWorldSetCFM(world, d);}
	void SetContactMaxCorrectingVel(double d) {dWorldSetContactMaxCorrectingVel(world, d);}
	void SetContactSurfaceLayer(double d) {dWorldSetContactSurfaceLayer(world, d);}
	void SetAutoDisableFlag(bool b) {dWorldSetAutoDisableFlag(world, b);}
	void SetIterationCount(int i) {dWorldSetQuickStepNumIterations(world, i);}
	void SetAutoDisableAverageSamplesCount(int i) {dWorldSetAutoDisableAverageSamplesCount(world, i);}
	void SetConstraintForceMixing(double d) {dWorldSetCFM(world, d);}
	
	dWorldID GetWorldId() const {ASSERT(world); return world;}
	dJointGroupID GetJointGroupId() const {ASSERT(contactgroup); return contactgroup;}
	
	void Collide() {ASSERT(space != NULL); dSpaceCollide(space, this, &OdeSystem::StaticNearCallback);}
	void StepWorld(double seconds) {dWorldStep(world, seconds);}
	void RemoveContactJoints() {dJointGroupEmpty(contactgroup);}
	
	virtual void NearCallback(void *, dGeomID o1, dGeomID o2);
	static void StaticNearCallback(void *data, dGeomID o1, dGeomID o2) {((OdeSystem*)data)->NearCallback(NULL, o1, o2);}
	
};

using OdeSystemRef = Ref<OdeSystem>;



void AddEngineOdeSystem();



NAMESPACE_ECS_END





#endif
#endif
