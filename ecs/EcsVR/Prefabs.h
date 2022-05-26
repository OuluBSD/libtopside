#ifndef _System_Prefabs_h_
#define _System_Prefabs_h_

#if 1

NAMESPACE_ECS_BEGIN

namespace Knownmodel_names 
{
constexpr auto UnitSphere = "UnitSphere_LowPoly";
constexpr auto UnitCube = "UnitCube";
constexpr auto UnitQuad = "UnitQuad";
constexpr auto Baseball = "Baseball";
constexpr auto PaintBrush = "PaintBrush";
constexpr auto Gun = "Gun";
}

struct FloorPrefab : EntityPrefab<Transform, PbrRenderable>
{
	using Component = EntityPrefab<Transform, PbrRenderable>::Components;
	
    static Components Make(Entity& e)
    {
        auto components = EntityPrefab::Make(e);

        components.Get<Transform>().size = { 10.0f, 0.00001f, 10.0f };
        //components.Get<PbrRenderable>().ResetModel(Knownmodel_names::UnitCube);
        //components.Get<PbrRenderable>().color = Rgba(0.15f, 0.15f, 0.15f, 1.0f);
        TODO

        return components;
    }
};



struct Baseball : EntityPrefab<Transform, PbrRenderable, RigidBody>
{
    static Components Make(Entity& e)
    {
        auto components = EntityPrefab::Make(e);

        components.Get<RigidBody>().acceleration = e.GetEngine().Get<PhysicsSystem>()->gravity;
        components.Get<PbrRenderable>().ResetModel(Knownmodel_names::Baseball);

        return components;
    }
};

struct Bullet : EntityPrefab<Transform, PbrRenderable, RigidBody>
{
    static Components Make(Entity& e)
    {
        auto components = EntityPrefab::Make(e);

        components.Get<RigidBody>().acceleration = e.GetEngine().Get<PhysicsSystem>()->gravity;
        components.Get<PbrRenderable>().ResetModel(Knownmodel_names::UnitSphere);
        components.Get<PbrRenderable>().color = vec4(0, 0, 1, 1);
        components.Get<Transform>().size = vec3(0.025f);

        return components;
    }
};

struct PaintBrush : EntityPrefab<Transform, PbrRenderable, MotionControllerComponent>
{
    static Components Make(Entity& e)
    {
        auto components = EntityPrefab::Make(e);

        components.Get<PbrRenderable>().ResetModel(Knownmodel_names::PaintBrush);

        return components;
    }
};

struct Gun : EntityPrefab<Transform, PbrRenderable, MotionControllerComponent>
{
    static Components Make(Entity& e)
    {
        auto components = EntityPrefab::Make(e);

        components.Get<PbrRenderable>().ResetModel(Knownmodel_names::Gun);

        return components;
    }
};

struct PaintStroke : EntityPrefab<Transform, PbrRenderable, PaintStrokeComponent>
{
    static Components Make(Entity& e)
    {
        auto components = EntityPrefab::Make(e);

		TODO
        //components.Get<PbrRenderable>().model.Create();

        return components;
    }
};

struct StaticSphere : EntityPrefab<Transform, ModelComponent>
{
    static Components Make(Entity& e)
    {
        auto components = EntityPrefab::Make(e);

        //components.Get<PbrRenderable>().ResetModel(Knownmodel_names::UnitSphere);
        //components.Get<PbrRenderable>().color = Rgba(0.5, 0.5, 0.5, 1.0);
        TODO

        return components;
    }
};

struct StaticCube : EntityPrefab<Transform, ModelComponent>
{
    static Components Make(Entity& e)
    {
        auto components = EntityPrefab::Make(e);

        //components.Get<PbrRenderable>().ResetModel(Knownmodel_names::UnitCube);
        //components.Get<PbrRenderable>().color = Rgba(0.5, 0.5, 0.5, 1.0);
		TODO
		
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
