#ifndef _EcsLib_Prefab_h_
#define _EcsLib_Prefab_h_

NAMESPACE_ECS_BEGIN

namespace KnownModelNames 
{
	constexpr auto UnitSphere = "UnitSphere_LowPoly";
	constexpr auto UnitCube = "UnitCube";
	constexpr auto UnitQuad = "UnitQuad";
	constexpr auto Baseball = "Baseball";
	constexpr auto PaintBrush = "PaintBrush";
	constexpr auto Gun = "Gun";
	
	String GetPath(String name);
}


struct PaintBrush : EntityPrefab<Transform, ModelComponent/*, MotionControllerComponent*/>
{
    static Components Make(Entity& e)
    {
        auto components = EntityPrefab::Make(e);

        components.Get<ModelComponentRef>()->SetPrefabModel(KnownModelNames::PaintBrush);

        return components;
    }
};




NAMESPACE_ECS_END

#endif
