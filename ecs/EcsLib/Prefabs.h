#ifndef _System_Prefabs_h_
#define _System_Prefabs_h_


NAMESPACE_OULU_BEGIN

namespace KnownModelNames 
{
constexpr auto UnitSphere = "UnitSphere_LowPoly";
constexpr auto UnitCube = "UnitCube";
constexpr auto UnitQuad = "UnitQuad";
constexpr auto Baseball = "Baseball";
constexpr auto PaintBrush = "PaintBrush";
constexpr auto Gun = "Gun";
}

struct FloorPrefab : EntityPrefab<Transform, ModelComponent>
{
    static ComponentMap Make(ComponentStore& store)
    {
        auto components = EntityPrefab::Make(store);

        components.Get<Transform>()->size = { 10.0f, 0.00001f, 10.0f };
        //components.Get<Model>()->ResetModel(KnownModelNames::UnitCube);
        //components.Get<Model>()->color = Rgba(0.15f, 0.15f, 0.15f, 1.0f);
        TODO

        return components;
    }
};


/*
struct Baseball : EntityPrefab<Transform, Model, RigidBody>
{
    static ComponentMap Make(ComponentStore& store)
    {
        auto components = EntityPrefab::Make(store);

        components.Get<RigidBody>()->acceleration = PhysicsSystem::EarthGravity;
        components.Get<Model>()->ResetModel(KnownModelNames::Baseball);

        return components;
    }
};

struct Bullet : EntityPrefab<Transform, Model, RigidBody>
{
    static ComponentMap Make(ComponentStore& store)
    {
        auto components = EntityPrefab::Make(store);

        components.Get<RigidBody>()->acceleration = PhysicsSystem::EarthGravity;
        components.Get<Model>()->ResetModel(KnownModelNames::UnitSphere);
        components.Get<Model>()->color = Rgba(0, 0, 1, 0);
        components.Get<Transform>()->size = vec3(0.025f);

        return components;
    }
};

struct PaintBrush : EntityPrefab<Transform, Model, MotionControllerComponent>
{
    static ComponentMap Make(ComponentStore& store)
    {
        auto components = EntityPrefab::Make(store);

        components.Get<Model>()->ResetModel(KnownModelNames::PaintBrush);

        return components;
    }
};

struct Gun : EntityPrefab<Transform, Model, MotionControllerComponent>
{
    static ComponentMap Make(ComponentStore& store)
    {
        auto components = EntityPrefab::Make(store);

        components.Get<Model>()->ResetModel(KnownModelNames::Gun);

        return components;
    }
};

struct PaintStroke : EntityPrefab<Transform, Model, PaintStrokeComponent>
{
    static ComponentMap Make(ComponentStore& store)
    {
        auto components = EntityPrefab::Make(store);

        components.Get<Model>()->model = MakeShared<Model>();

        return components;
    }
};*/

struct StaticSphere : EntityPrefab<Transform, ModelComponent>
{
    static ComponentMap Make(ComponentStore& store)
    {
        auto components = EntityPrefab::Make(store);

        //components.Get<Model>()->ResetModel(KnownModelNames::UnitSphere);
        //components.Get<Model>()->color = Rgba(0.5, 0.5, 0.5, 1.0);
        TODO

        return components;
    }
};

struct StaticCube : EntityPrefab<Transform, ModelComponent>
{
    static ComponentMap Make(ComponentStore& store)
    {
        auto components = EntityPrefab::Make(store);

        //components.Get<Model>()->ResetModel(KnownModelNames::UnitCube);
        //components.Get<Model>()->color = Rgba(0.5, 0.5, 0.5, 1.0);
		TODO
		
        return components;
    }
};

struct CameraPrefab : EntityPrefab<Transform, Viewport, Camerable, Connector>
{
    static ComponentMap Make(ComponentStore& store)
    {
        auto components = EntityPrefab::Make(store);
		
		components.Get<Transform>()->position[2] = 10.0;
		components.Get<Transform>()->position[1] = 3.0;
		
        return components;
    }
};

struct StaticModel : EntityPrefab<Transform, ModelComponent, Connector>
{
    static ComponentMap Make(ComponentStore& store)
    {
        auto components = EntityPrefab::Make(store);
		return components;
    }
};







NAMESPACE_OULU_END

#endif
