#ifndef _EcsPhysics_TPrefab_h_
#define _EcsPhysics_TPrefab_h_

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
		
		Fys::SetGeomModelPlane(this->geom, this->GetSystem()->GetSpace().GetNative());
		
		this->is_override_phys_geom = true;
		this->override_geom = Identity<mat4>();
		
		TODO
		ModelBuilder mb;
		mb	.AddPlane(vec3(-50, 0, -50), vec2(100, 100))
			/*.SetMaterial(DefaultMaterial())*/
			;
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
		
		Ref<System> w = GetActiveMachine().Get<System>();
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


NAMESPACE_ECS_END

#endif
