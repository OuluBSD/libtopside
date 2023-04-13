#pragma once


NAMESPACE_ECS_BEGIN



constexpr auto UnitSphere = "UnitSphere_LowPoly";
constexpr auto UnitCube = "UnitCube";
constexpr auto Baseball = "Baseball";
constexpr auto PaintBrush = "PaintBrush";
constexpr auto Gun = "Gun";

	
struct FloorPrefab : EntityPrefab<Transform, PbrRenderable>
{
    static ComponentMap Make(ComponentStore& store)
    {
        auto components = EntityPrefab::Make(store);

        components.Get<Transform>()->scale = { 10.0f, 0.00001f, 10.0f };
        components.Get<PbrRenderable>()->ResetModel(DemoRoom::KnownModelNames::UnitCube);
        components.Get<PbrRenderable>()->Color = DirectX::XMVECTORF32{ 0.15f, 0.15f, 0.15f, 1.0f };

        return components;
    }
};

struct Baseball : EntityPrefab<Transform, PbrRenderable, RigidBody>
{
    static ComponentMap Make(ComponentStore& store)
    {
        auto components = EntityPrefab::Make(store);

        components.Get<RigidBody>()->acceleration = PhysicsSystem::EarthGravity;
        components.Get<PbrRenderable>()->ResetModel(DemoRoom::KnownModelNames::Baseball);

        return components;
    }
};

struct Bullet : EntityPrefab<Transform, PbrRenderable, RigidBody>
{
    static ComponentMap Make(ComponentStore& store)
    {
        auto components = EntityPrefab::Make(store);

        components.Get<RigidBody>()->acceleration = PhysicsSystem::EarthGravity;
        components.Get<PbrRenderable>()->ResetModel(DemoRoom::KnownModelNames::UnitSphere);
        components.Get<PbrRenderable>()->Color = DirectX::Colors::Blue;
        components.Get<Transform>()->scale = winrt::Windows::Foundation::Numerics::float3{ 0.025f };

        return components;
    }
};

struct PaintBrush : EntityPrefab<Transform, PbrRenderable, DemoRoom::MotionControllerComponent>
{
    static ComponentMap Make(ComponentStore& store)
    {
        auto components = EntityPrefab::Make(store);

        components.Get<PbrRenderable>()->ResetModel(DemoRoom::KnownModelNames::PaintBrush);

        return components;
    }
};

struct Gun : EntityPrefab<Transform, PbrRenderable, DemoRoom::MotionControllerComponent>
{
    static ComponentMap Make(ComponentStore& store)
    {
        auto components = EntityPrefab::Make(store);

        components.Get<PbrRenderable>()->ResetModel(DemoRoom::KnownModelNames::Gun);

        return components;
    }
};

struct PaintStroke : EntityPrefab<Transform, PbrRenderable, DemoRoom::PaintStrokeComponent>
{
    static ComponentMap Make(ComponentStore& store)
    {
        auto components = EntityPrefab::Make(store);

        components.Get<PbrRenderable>()->Model = std::make_shared<Pbr::Model>();

        return components;
    }
};

struct StaticSphere : EntityPrefab<Transform, PbrRenderable>
{
    static ComponentMap Make(ComponentStore& store)
    {
        auto components = EntityPrefab::Make(store);

        components.Get<PbrRenderable>()->ResetModel(DemoRoom::KnownModelNames::UnitSphere);
        components.Get<PbrRenderable>()->Color = DirectX::Colors::Gray;

        return components;
    }
};

struct StaticCube : EntityPrefab<Transform, PbrRenderable>
{
    static ComponentMap Make(ComponentStore& store)
    {
        auto components = EntityPrefab::Make(store);

        components.Get<PbrRenderable>()->ResetModel(DemoRoom::KnownModelNames::UnitCube);
        components.Get<PbrRenderable>()->Color = DirectX::Colors::Gray;

        return components;
    }
};


NAMESPACE_ECS_END
