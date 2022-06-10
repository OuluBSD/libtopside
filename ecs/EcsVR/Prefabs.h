#ifndef _System_Prefabs_h_
#define _System_Prefabs_h_

#if 1

NAMESPACE_ECS_BEGIN



struct FloorPrefab : EntityPrefab<Transform, ModelComponent>
{
	using Component = EntityPrefab<Transform, ModelComponent>::Components;
	
    static Components Make(Entity& e)
    {
        auto components = EntityPrefab::Make(e);

        components.Get<TransformRef>()->size = { 10.0f, 0.00001f, 10.0f };
        components.Get<ModelComponentRef>()->SetPrefabModel(KnownModelNames::UnitCube);
        components.Get<ModelComponentRef>()->color = vec4(0.15f, 0.15f, 0.15f, 1.0f);

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
