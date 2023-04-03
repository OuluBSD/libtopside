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

        components.Get<ModelComponentRef>()->MakeCylinder(vec3(0,0,0), 0.2f, 1.0f);

        return components;
    }
};

struct PaintStroke : EntityPrefab<Transform, ModelComponent, PaintStrokeComponent>
{
    static Components Make(Entity& e)
    {
        auto components = EntityPrefab::Make(e);

        components.Get<ModelComponentRef>()->Create();

        return components;
    }
};

struct Bullet : EntityPrefab<Transform, ModelComponent, RigidBody, PhysicsBody>
{
    static Components Make(Entity& e)
    {
        auto components = EntityPrefab::Make(e);

        components.Get<RigidBodyRef>()->acceleration = e.GetEngine().Get<PhysicsSystem>()->gravity;
        components.Get<ModelComponentRef>()->MakeBall(vec3(0,0,0), 0.2f);
        components.Get<ModelComponentRef>()->color = vec4(0, 0, 1, 1);
        components.Get<TransformRef>()->size = vec3(0.025f);

        return components;
    }
};

struct Baseball : EntityPrefab<Transform, ModelComponent, RigidBody, PhysicsBody>
{
    static Components Make(Entity& e)
    {
        auto components = EntityPrefab::Make(e);

        components.Get<RigidBodyRef>()->acceleration = e.GetEngine().Get<PhysicsSystem>()->gravity;
        components.Get<ModelComponentRef>()->SetPrefabModel(KnownModelNames::Baseball);

        return components;
    }
};


NAMESPACE_ECS_END

#endif
