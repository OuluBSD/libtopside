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
    static Components Make(Entity& e)
    {
        auto components = EntityPrefab::Make(e);

        components.Get<Transform>().size = { 10.0f, 0.00001f, 10.0f };
        //components.Get<Model>().ResetModel(KnownModelNames::UnitCube);
        //components.Get<Model>().color = Rgba(0.15f, 0.15f, 0.15f, 1.0f);
        TODO

        return components;
    }
};


/*
struct Baseball : EntityPrefab<Transform, Model, RigidBody>
{
    static Components Make(Entity& e)
    {
        auto components = EntityPrefab::Make(e);

        components.Get<RigidBody>()->acceleration = PhysicsSystem::EarthGravity;
        components.Get<Model>()->ResetModel(KnownModelNames::Baseball);

        return components;
    }
};

struct Bullet : EntityPrefab<Transform, Model, RigidBody>
{
    static Components Make(Entity& e)
    {
        auto components = EntityPrefab::Make(e);

        components.Get<RigidBody>()->acceleration = PhysicsSystem::EarthGravity;
        components.Get<Model>()->ResetModel(KnownModelNames::UnitSphere);
        components.Get<Model>()->color = Rgba(0, 0, 1, 0);
        components.Get<Transform>().size = vec3(0.025f);

        return components;
    }
};

struct PaintBrush : EntityPrefab<Transform, Model, MotionControllerComponent>
{
    static Components Make(Entity& e)
    {
        auto components = EntityPrefab::Make(e);

        components.Get<Model>()->ResetModel(KnownModelNames::PaintBrush);

        return components;
    }
};

struct Gun : EntityPrefab<Transform, Model, MotionControllerComponent>
{
    static Components Make(Entity& e)
    {
        auto components = EntityPrefab::Make(e);

        components.Get<Model>()->ResetModel(KnownModelNames::Gun);

        return components;
    }
};

struct PaintStroke : EntityPrefab<Transform, Model, PaintStrokeComponent>
{
    static Components Make(Entity& e)
    {
        auto components = EntityPrefab::Make(e);

        components.Get<Model>()->model = MakeRef<Model>();

        return components;
    }
};*/

struct StaticSphere : EntityPrefab<Transform, ModelComponent>
{
    static Components Make(Entity& e)
    {
        auto components = EntityPrefab::Make(e);

        //components.Get<Model>()->ResetModel(KnownModelNames::UnitSphere);
        //components.Get<Model>()->color = Rgba(0.5, 0.5, 0.5, 1.0);
        TODO

        return components;
    }
};

struct StaticCube : EntityPrefab<Transform, ModelComponent>
{
    static Components Make(Entity& e)
    {
        auto components = EntityPrefab::Make(e);

        //components.Get<Model>()->ResetModel(KnownModelNames::UnitCube);
        //components.Get<Model>()->color = Rgba(0.5, 0.5, 0.5, 1.0);
		TODO
		
        return components;
    }
};

struct CameraPrefab : EntityPrefab<Transform, Viewport, Camerable>
{
    static Components Make(Entity& e)
    {
        auto components = EntityPrefab::Make(e);
		
		components.Get<Transform>().position[2] = 10.0;
		components.Get<Transform>().position[1] = 3.0;
		
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







NAMESPACE_OULU_END

#endif
