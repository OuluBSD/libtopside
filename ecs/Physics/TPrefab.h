#ifndef _Physics_TPrefab_h_
#define _Physics_TPrefab_h_

NAMESPACE_ECS_BEGIN


template <class Fys>
struct StaticGroundPlane : public Component<StaticGroundPlane<Fys>>, public Fys::Object {
	using Object = typename Fys::Object;
	using ComponentT = Component<StaticGroundPlane<Fys>>;
	RTTI_DECL2(StaticGroundPlane, Object, Component<StaticGroundPlane>)
	
	typedef StaticGroundPlane CLASSNAME;
	
	using Parent = Entity;
	
	void operator=(const StaticGroundPlane& ) {Panic("Not implemented");}
	COMP_DEF_VISIT
	
	void OnAttach() override {
		Object::OnAttach();
		
		Fys::SetGeomModelPlane(this->geom, this->GetSystem()->GetSpace());
		
		this->is_override_phys_geom = true;
		this->override_geom = identity<mat4>();
		
		ModelBuilder mb;
		mb	.AddPlane(vec3(-50, 0, -50), vec2(100, 100))
			.SetMaterial(DefaultMaterial());
		this->loader = mb.AsModel();
	}
	
	String ToString() const override {return "StaticGroundPlane";}
};

template <class Fys>
struct StaticGroundPlanePrefab :
	EntityPrefab<Transform, Renderable, StaticGroundPlane<Fys>>
{
	using GroundPlane = StaticGroundPlane<Fys>;
	using Prefab = EntityPrefab<Transform, Renderable, GroundPlane>;
	using Components = typename Prefab::Components;
	using System = typename Fys::System;
	
    static Components Make(Entity& e)
    {
        auto components = Prefab::Make(e);
		auto ground = components.template Get<Ref<GroundPlane>>();
		
		components.template Get<TransformRef>()->position[1] = -5.0;
		components.template Get<RenderableRef>()->cb.Add(ground->GetRefreshCallback());
		
		Ref<System> w = e.GetEngine().Get<System>();
		Ref<GroundPlane> plane = components.template Get<Ref<GroundPlane>>();
		ASSERT(plane);
		w->Attach(*plane);
		
        return components;
    }
};

template <class Fys>
struct StaticBox : public Fys::Object {
	using Object = typename Fys::Object;
	double width = 1.0, height = 1.0, length = 1.0;
	
	RTTI_DECL1(StaticBox, Object)
	StaticBox& Set(double w, double h, double l) {width=w; height=h; length=l; return *this;}
	
	void OnAttach() override;
	
	String ToString() override {return "StaticBox";}
};

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


NAMESPACE_ECS_END

#endif
