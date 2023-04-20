#if 0
#pragma once


NAMESPACE_ECS_BEGIN


class ToolSystemBase;

struct ToolComponent : Component<ToolComponent>
{
    std::wstring title;
    std::wstring description;
    detail::type_id toolType{ typeid(nullptr_t) };
    
    COPY_PANIC(ToolComponent)
    
};

////////////////////////////////////////////////////////////////////////////////
// ToolboxSystem
// This system manages the ToolSystems and manages the two Entities that represent the left and right Motion Controllers
class ToolboxSystem : 
    public System<ToolboxSystem>,
    public ISpatialInteractionListener
{
public:
	using Base = System<ToolboxSystem>;
    using System::System;
    RTTI_DECL2(ToolboxSystem, Base, ISpatialInteractionListener)

    void AddToolSystem(ToolSystemBase& system);
    void RemoveToolSystem(ToolSystemBase& system);

protected:
    // System
    void Start() override;
    void Update(double dt) override;
    void Stop() override;

    // ISpatialInteractionListener
    void OnSourcePressed(
        const winrt::Windows::UI::Input::Spatial::SpatialInteractionSourceEventArgs& args) override;

private:
    detail::type_map<std::shared_ptr<ToolSystemBase>> m_selectors;
    detail::type_map<EntityRef> m_selectorObjects;

    bool m_showToolbox{ false };

    enum ControllerHand {
        Left, Right, Count
    };

    static std::wstring_view ControllerHandToString(ControllerHand hand);
    static winrt::Windows::UI::Input::Spatial::SpatialInteractionSourceHandedness ControllerHandToHandedness(ControllerHand hand);

    struct ControllerContext {
        EntityRef Controller;
        EntityRef DebugText;
        ControllerHand Hand;
    };

    void SwitchToolType(Entity& entity, const detail::type_id& newType);

    EntityRef FindController(const winrt::Windows::UI::Input::Spatial::SpatialInteractionSource& source);

    std::array<ControllerContext, ControllerHand::Count> m_controllers;

    EntityRef m_instructionalText;
    
    
};


NAMESPACE_ECS_END
#endif
