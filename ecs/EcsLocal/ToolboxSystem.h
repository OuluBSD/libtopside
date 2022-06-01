#ifndef _EcsLocal_ToolboxSystem_h_
#define _EcsLocal_ToolboxSystem_h_


NAMESPACE_ECS_BEGIN


class ToolSystemBase;

class ToolComponent : public Component<ToolComponent> {
	
public:
	RTTI_COMP0(ToolComponent)
	COPY_PANIC(ToolComponent)
	COMP_DEF_VISIT
	
	
	String title;
	String description;
	TypeId tool_type { AsVoidTypeId() };
	
};


class ToolboxSystemBase :
	public System<ToolboxSystemBase>
{
	LinkedList<EntityRef> entities;
	
public:
	void Visit(RuntimeVisitor& vis) override {TODO}
	RTTI_DECL1(ToolboxSystemBase, System<ToolboxSystemBase>)
	ECS_SYS_CTOR(ToolboxSystemBase);
	
	using Parent = Engine;
	
	
	void AddToolSystem(ToolSystemBaseRef system);
	void RemoveToolSystem(ToolSystemBaseRef system);
	
protected:
	// System
	void Start() override;
	void Update(double dt) override;
	void Stop() override;
	bool Initialize() override;
	void Uninitialize() override;
	
private:
	TypeMap<ToolSystemBaseRef> selectors;
	TypeMap<EntityRef> selector_objects;
	
	bool show_toolbox{ false };
	
	enum ControllerHand {
		Left, Right, Count
	};
	
	static String ControllerHandToString(ControllerHand hand);
	
	struct ControllerContext {
		EntityRef ctrl;
		EntityRef dbg_txt;
		ControllerHand hand;
	};
	
	void SwitchToolType(EntityRef entity, const TypeId& new_type);
	
	
	EntityRef instruction_text;
	FixedArray<ControllerContext, ControllerHand::Count> ctrls;
	
	
};


NAMESPACE_ECS_END

#endif
