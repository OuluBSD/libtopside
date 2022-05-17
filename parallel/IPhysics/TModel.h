#ifndef _IPhysics_TModel_h_
#define _IPhysics_TModel_h_

NAMESPACE_PARALLEL_BEGIN


template <class Fys>
class ScalarObject : public Fys::Object {
	using Object = typename Fys::Object;
	using Float = typename Fys::Float;
	
protected:
	vec3 sides;
	
public:
	RTTI_DECL1(ScalarObject, Object)
	ScalarObject() {
		for (int k = 0; k < 3; k++) sides[k] = 1.0;
	}
	void SetRandomSize() {
		for (int k = 0; k < 3; k++) sides[k] = Randomf() * 0.5 + 0.1;
	}
	
	String ToString() override {return "ScalarObject";}
};

template <class Fys>
struct Sphere : public ScalarObject<Fys> {
	using ScalarObject = ScalarObject<Fys>;
	using Object = typename Fys::Object;
	
	double radius = 0.102;
	double wmass  = 0.1;
	
	RTTI_DECL1(Sphere, ScalarObject)
	
	void OnAttach() override {
		Object::OnAttach();
		
		// Set orientation from axis (1i+0j+0k) and it's (angle 90 degrees)
		this->SetOrientation(1, 0, 0, M_PI*0.5);
		
		// Set mass function for physics body as sphere
		Fys::SetMassFunctionSphere(this->mass, this->sides[0], radius);
		
		// Set mass for the mass function
		Fys::SetMass(this->mass, wmass);
		
		// Set 3D geometry for the object as sphere
		Fys::SetGeomModelSphere(this->geom, radius);
		
		ModelBuilder mb;
		mb	.AddSphere(vec3(0., 0., 0.), radius)
			.SetMaterial(DefaultMaterial());
		this->loader = mb;
		
		this->AttachContent();
	}
	
	String ToString() override {return "Sphere";}
};



#if 0


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

#endif


NAMESPACE_PARALLEL_END

#endif
