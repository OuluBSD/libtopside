#ifndef _System_Prefabs_h_
#define _System_Prefabs_h_

#if 1

NAMESPACE_ECS_BEGIN



struct FloorPrefab : EntityPrefab<Transform, PbrRenderable>
{
	using Component = EntityPrefab<Transform, PbrRenderable>::Components;
	
    static Components Make(Entity& e)
    {
        auto components = EntityPrefab::Make(e);

        components.Get<TransformRef>()->size = { 10.0f, 0.00001f, 10.0f };
        components.Get<PbrRenderableRef>()->ResetModel(KnownModelNames::UnitCube);
        components.Get<PbrRenderableRef>()->color = vec4(0.15f, 0.15f, 0.15f, 1.0f);

        return components;
    }
};

struct StaticModel : EntityPrefab<Transform, ModelComponent>
{
    static Components Make(Entity& e)
    {
        auto components = EntityPrefab::Make(e);
		return components;
    }
};







NAMESPACE_ECS_END

#endif
#endif
