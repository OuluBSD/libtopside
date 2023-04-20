#pragma once


NAMESPACE_ECS_BEGIN

using ::TS::Ecs::Transform;

	
struct FloorPrefab : EntityPrefab<Transform, PbrRenderable>
{
    static Components Make(Entity& e)
    {
        auto components = EntityPrefab::Make(e);

        components.Get<TransformRef>()->size = { 10.0f, 0.00001f, 10.0f };
        components.Get<PbrRenderableRef>()->ResetModel(KnownModelNames::UnitCube);
        components.Get<PbrRenderableRef>()->Color = DirectX::XMVECTORF32{ 0.15f, 0.15f, 0.15f, 1.0f };

        return components;
    }
};

#if 0

struct Baseball : EntityPrefab<Transform, PbrRenderable, RigidBody>
{
    static Components Make(Entity& e)
    {
        auto components = EntityPrefab::Make(e);

        components.Get<RigidBodyRef>()->acceleration = EarthGravity;
        components.Get<PbrRenderableRef>()->ResetModel(KnownModelNames::Baseball);

        return components;
    }
};

struct Bullet : EntityPrefab<Transform, PbrRenderable, RigidBody>
{
    static Components Make(Entity& e)
    {
        auto components = EntityPrefab::Make(e);

        components.Get<RigidBodyRef>()->acceleration = EarthGravity;
        components.Get<PbrRenderableRef>()->ResetModel(KnownModelNames::UnitSphere);
        components.Get<PbrRenderableRef>()->Color = DirectX::Colors::Blue;
        components.Get<TransformRef>()->size = vec3(0.025f);

        return components;
    }
};

struct PaintBrush : EntityPrefab<Transform, PbrRenderable, MotionControllerComponent>
{
    static Components Make(Entity& e)
    {
        auto components = EntityPrefab::Make(e);

        components.Get<PbrRenderableRef>()->ResetModel(KnownModelNames::PaintBrush);

        return components;
    }
};

struct Gun : EntityPrefab<Transform, PbrRenderable, MotionControllerComponent>
{
    static Components Make(Entity& e)
    {
        auto components = EntityPrefab::Make(e);

        components.Get<PbrRenderableRef>()->ResetModel(KnownModelNames::Gun);

        return components;
    }
};

struct PaintStroke : EntityPrefab<Transform, PbrRenderable, PaintStrokeComponent>
{
    static Components Make(Entity& e)
    {
        auto components = EntityPrefab::Make(e);

        components.Get<PbrRenderableRef>()->Model = std::make_shared<Pbr::Model>();

        return components;
    }
};

struct StaticSphere : EntityPrefab<Transform, PbrRenderable>
{
    static Components Make(Entity& e)
    {
        auto components = EntityPrefab::Make(e);

        components.Get<PbrRenderableRef>()->ResetModel(KnownModelNames::UnitSphere);
        components.Get<PbrRenderableRef>()->Color = DirectX::Colors::Gray;

        return components;
    }
};

struct StaticCube : EntityPrefab<Transform, PbrRenderable>
{
    static Components Make(Entity& e)
    {
        auto components = EntityPrefab::Make(e);

        components.Get<PbrRenderableRef>()->ResetModel(KnownModelNames::UnitCube);
        components.Get<PbrRenderableRef>()->Color = DirectX::Colors::Gray;

        return components;
    }
};

#endif

NAMESPACE_ECS_END
