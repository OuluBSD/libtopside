#pragma once


NAMESPACE_OULU_BEGIN

class ToolSystemBase;

class ToolComponent : public Component<ToolComponent>
{
	VIS_COMP_0_0
	
public:
	COPY_PANIC(ToolComponent)
	void Visit(RuntimeVisitor& vis) override {}
	
    String title;
    String description;
    TypeId tool_type { typeid(void) };
    
};

////////////////////////////////////////////////////////////////////////////////
// ToolboxSystem
// This system manages the ToolSystems and manages the two Entities that represent the left and right Motion Controllers
class ToolboxSystem :
    public System<ToolboxSystem>,
    public ISpatialInteractionListener
{
	LinkedList<EntityRef> entities;
	
public:
    using System::System;
    using Parent = Machine;

	
    void AddToolSystem(ToolSystemBaseRef system);
    void RemoveToolSystem(ToolSystemBaseRef system);

protected:
    // System
    void Start() override;
    void Update(double dt) override;
    void Stop() override;
    void Uninitialize() override;

    // ISpatialInteractionListener
    void OnSourcePressed(const SpatialInteractionSourceEventArgs& args) override;

private:
    TypeMap<ToolSystemBaseRef> selectors;
    TypeMap<EntityRef> selector_objects;

    bool show_toolbox{ false };

    enum ControllerHand {
        Left, Right, Count
    };

    static String ControllerHandToString(ControllerHand hand);
    static SpatialInteractionSourceHandedness ControllerHandToHandedness(ControllerHand hand);

    struct ControllerContext {
        EntityRef ctrl;
        EntityRef dbg_txt;
        ControllerHand hand;
    };

    void SwitchToolType(EntityRef entity, const TypeId& new_type);

    EntityRef FindController(const SpatialInteractionSource& source);

    FixedArray<ControllerContext, ControllerHand::Count> ctrls;

    EntityRef instruction_text;
    
    
};

NAMESPACE_OULU_END
