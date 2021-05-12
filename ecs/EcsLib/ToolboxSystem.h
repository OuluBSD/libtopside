#pragma once


NAMESPACE_OULU_BEGIN

class ToolSystemBase;

struct ToolComponent : Component<ToolComponent>
{
    String title;
    String description;
    TypeId tool_type{ typeid(nullptr_t) };
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
    using Parent = Machine;

    void AddToolSystem(ToolSystemBaseRef system);
    void RemoveToolSystem(const ToolSystemBaseRef& system);

protected:
    // System
    void Start() override;
    void Update(double dt) override;
    void Stop() override;

    // ISpatialInteractionListener
    void OnSourcePressed(const SpatialInteractionSourceEventArgs& args) override;

private:
    TypeMap<ToolSystemBaseRef> m_selectors;
    TypeMap<EntityRef> m_selectorObjects;

    bool m_showToolbox{ false };

    enum ControllerHand {
        Left, Right, Count
    };

    static String ControllerHandToString(ControllerHand hand);
    static SpatialInteractionSourceHandedness ControllerHandToHandedness(ControllerHand hand);

    struct ControllerContext {
        EntityRef Controller;
        EntityRef DebugText;
        ControllerHand Hand;
    };

    void SwitchToolType(EntityRef entity, const TypeId& newType);

    EntityRef FindController(const SpatialInteractionSource& source);

    FixedArray<ControllerContext, ControllerHand::Count> m_controllers;

    EntityRef instruction_text;
    
    
};

NAMESPACE_OULU_END
