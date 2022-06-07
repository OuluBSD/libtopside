#ifndef _EcsLocal_Prefabs_h_
#define _EcsLocal_Prefabs_h_

NAMESPACE_ECS_BEGIN


struct Gun : EntityPrefab<Transform, ModelComponent, ToolComponent>
{
    static Components Make(Entity& e)
    {
        auto components = EntityPrefab::Make(e);

        components.Get<ModelComponentRef>()->SetPrefabModel(KnownModelNames::Gun);

        return components;
    }
};

struct PaintBrush : EntityPrefab<Transform, ModelComponent, ToolComponent>
{
    static Components Make(Entity& e)
    {
        auto components = EntityPrefab::Make(e);

        components.Get<ModelComponentRef>()->SetPrefabModel(KnownModelNames::PaintBrush);

        return components;
    }
};

struct DummyToolModel : EntityPrefab<Transform, ModelComponent, ToolComponent>
{
    static Components Make(Entity& e)
    {
        auto components = EntityPrefab::Make(e);

        components.Get<ModelComponentRef>()->MakeCylinder(vec3(0,0,0), 0.2, 1.0);

        return components;
    }
};

struct PaintStroke : EntityPrefab<Transform, ModelComponent, PaintStrokeComponent>
{
    static Components Make(Entity& e)
    {
        auto components = EntityPrefab::Make(e);

        //components.Get<ModelComponentRef>()->model.Create();

        return components;
    }
};


NAMESPACE_ECS_END

#endif
