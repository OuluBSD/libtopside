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



struct Baseball : EntityPrefab<Transform, PbrRenderable, RigidBody>
{
    static Components Make(Entity& e)
    {
        auto components = EntityPrefab::Make(e);

        components.Get<RigidBodyRef>()->acceleration = e.GetEngine().Get<PhysicsSystem>()->gravity;
        components.Get<PbrRenderableRef>()->ResetModel(KnownModelNames::Baseball);

        return components;
    }
};

struct Bullet : EntityPrefab<Transform, PbrRenderable, RigidBody>
{
    static Components Make(Entity& e)
    {
        auto components = EntityPrefab::Make(e);

        components.Get<RigidBodyRef>()->acceleration = e.GetEngine().Get<PhysicsSystem>()->gravity;
        components.Get<PbrRenderableRef>()->ResetModel(KnownModelNames::UnitSphere);
        components.Get<PbrRenderableRef>()->color = vec4(0, 0, 1, 1);
        components.Get<TransformRef>()->size = vec3(0.025f);

        return components;
    }
};

struct PaintStroke : EntityPrefab<Transform, PbrRenderable, PaintStrokeComponent>
{
    static Components Make(Entity& e)
    {
        auto components = EntityPrefab::Make(e);

        TODO //components.Get<PbrRenderableRef>()->model.Create();

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
