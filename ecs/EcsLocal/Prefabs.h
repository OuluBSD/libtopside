#ifndef _EcsLocal_Prefabs_h_
#define _EcsLocal_Prefabs_h_

NAMESPACE_ECS_BEGIN



struct StaticSkybox : EntityPrefab<Transform, Renderable, ModelComponent>
{
    static Components Make(Entity& e)
    {
        auto components = EntityPrefab::Make(e);
        
        float huge_distance = 10e5;
        ModelBuilder b;
        b.AddBox(vec3(0,0,0), vec3(huge_distance, huge_distance, huge_distance), true);
        
        ModelMesh* m = b.Detach();
        m->ReverseFaces();
        components.Get<Ref<ModelComponent>>()->Attach(m);
        
        return components;
    }
};

struct StaticSphere : EntityPrefab<Transform, ModelComponent>
{
    static Components Make(Entity& e)
    {
        auto components = EntityPrefab::Make(e);

        components.Get<ModelComponentRef>()->SetPrefabModel(KnownModelNames::UnitSphere);
        components.Get<ModelComponentRef>()->color = vec4(0.5, 0.5, 0.5, 1.0);

        return components;
    }
};

struct StaticCube : EntityPrefab<Transform, ModelComponent>
{
    static Components Make(Entity& e)
    {
        auto components = EntityPrefab::Make(e);

        components.Get<ModelComponentRef>()->SetPrefabModel(KnownModelNames::UnitCube);
        components.Get<ModelComponentRef>()->color = vec4(0.5, 0.5, 0.5, 1.0);
		
        return components;
    }
};



NAMESPACE_ECS_END

#endif
