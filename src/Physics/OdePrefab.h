#ifndef _System_PhysicsPrefab_h_
#define _System_PhysicsPrefab_h_

#ifdef flagODE

NAMESPACE_ECS_BEGIN



struct StaticGroundPlane : public OdeObject, public Component<StaticGroundPlane> {
	RTTI_DECL2(StaticGroundPlane, OdeObject, Component<StaticGroundPlane>)
	
	typedef StaticGroundPlane CLASSNAME;
	
	using Parent = Entity;
	
	void operator=(const StaticGroundPlane& ) {Panic("Not implemented");}
	COMP_DEF_VISIT
	
	void OnAttach() override {
		OdeObject::OnAttach();
		
		geom = dCreatePlane(GetSpace()->GetSpaceId(), 0, 1, 0, 0);
		
		is_override_phys_geom = true;
		override_geom = identity<mat4>();
		
		ModelBuilder mb;
		mb	.AddPlane(vec3(-50, 0, -50), vec2(100, 100))
			.SetMaterial(DefaultMaterial());
		loader = mb.AsModel();
	}
	
	String ToString() override {return "StaticGroundPlane";}
};

using StaticGroundPlaneRef = Ref<StaticGroundPlane>;

struct StaticGroundPlanePrefab :
	EntityPrefab<Transform, Renderable, StaticGroundPlane>
{
    static Components Make(Entity& e)
    {
        auto components = EntityPrefab::Make(e);
		auto ground = components.Get<StaticGroundPlaneRef>();
		
		components.Get<TransformRef>()->position[1] = -5.0;
		components.Get<RenderableRef>()->cb.Add(ground->GetRefreshCallback());
		
		OdeSystemRef w = e.GetEngine().Get<OdeSystem>();
		OdeSystem& ow = CastRef<OdeSystem>(*w);
		StaticGroundPlaneRef plane = components.Get<StaticGroundPlaneRef>();
		ASSERT(plane);
		ow.OdeNode::Attach(*plane);
		
        return components;
    }
};

struct StaticBox : public OdeObject {
	double width = 1.0, height = 1.0, length = 1.0;
	
	RTTI_DECL1(StaticBox, OdeObject)
	StaticBox& Set(double w, double h, double l) {width=w; height=h; length=l; return *this;}
	StaticBox& SetRotationX(double angle) {dMatrix3 R; dRFromAxisAndAngle(R, 1, 0, 0, angle); dGeomSetRotation(geom, R); return *this;}
	StaticBox& SetRotationY(double angle) {dMatrix3 R; dRFromAxisAndAngle(R, 0, 1, 0, angle); dGeomSetRotation(geom, R); return *this;}
	StaticBox& SetRotationZ(double angle) {dMatrix3 R; dRFromAxisAndAngle(R, 0, 0, 1, angle); dGeomSetRotation(geom, R); return *this;}
	StaticBox& SetPosition(double x, double y, double z) {dGeomSetPosition(geom, x, y, z); return *this;}
	
	void OnAttach() override;
	
	String ToString() override {return "StaticBox";}
};



class OdeScalarObject : public OdeObject {
	
protected:
	dReal sides[3];
	
public:
	RTTI_DECL1(OdeScalarObject, OdeObject)
	OdeScalarObject() {
		for (int k = 0; k < 3; k++) sides[k] = 1.0;
	}
	void SetRandomSize() {
		for (int k = 0; k < 3; k++) sides[k] = dRandReal() * 0.5 + 0.1;
	}
	
	String ToString() override {return "OdeScalarObject";}
};

struct OdeSphere : public OdeScalarObject {
	double radius = 0.102;
	double wmass  = 0.1;
	
	RTTI_DECL1(OdeSphere, OdeScalarObject)
	
	OdeSphere& Reset(double x, double y, double z) {
		dQuaternion q;
		dQSetIdentity(q);
		dBodySetPosition(body, x, y, z);
		dBodySetQuaternion(body, q);
		dBodySetLinearVel(body, 0,0,0);
		dBodySetAngularVel(body, 0,0,0);
		return *this;
	}
	
	void OnAttach() override {
		OdeObject::OnAttach();
		
		dQFromAxisAndAngle(orient, 1, 0, 0, M_PI*0.5);	// Set orientation from axis (1i+0j+0k) and it's (angle 90 degrees)
		dMassSetSphere(&mass, sides[0], radius);		// Set mass function for physics body as sphere
		dMassAdjust(&mass, wmass);						// Set mass for the mass function
		geom = dCreateSphere(0, radius);				// Set 3D geometry for the object as sphere
		
		ModelBuilder mb;
		mb	.AddSphere(vec3(0., 0., 0.), radius)
			.SetMaterial(DefaultMaterial());
		loader = mb;
		
		AttachContent();
	}
	
	String ToString() override {return "Sphere";}
};


NAMESPACE_ECS_END

#endif
#endif
