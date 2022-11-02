#ifndef _System_PhysicsPrefab_h_
#define _System_PhysicsPrefab_h_

#if 0
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
		override_geom = Identity<mat4>();
		
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


NAMESPACE_ECS_END

#endif
#endif
#endif
