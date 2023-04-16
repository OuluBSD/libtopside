#pragma once


NAMESPACE_WIN_BEGIN


class ToolSystemBase;

struct ToolComponent : Component<ToolComponent>
{
    std::wstring title;
    std::wstring description;
    detail::type_id toolType{ typeid(nullptr_t) };
};

////////////////////////////////////////////////////////////////////////////////
// ToolboxSystem
// This system manages the ToolSystems and manages the two Entities that represent the left and right Motion Controllers
class ToolboxSystem : 
    public System<ToolboxSystem>,
    public ISpatialInteractionListener
{
public:
    using System::System;

    void AddToolSystem(std::shared_ptr<ToolSystemBase> system);
    void RemoveToolSystem(const std::shared_ptr<ToolSystemBase>& system);

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


NAMESPACE_WIN_END
