#ifndef _EcsLocal_ToolboxSystem_h_
#define _EcsLocal_ToolboxSystem_h_


NAMESPACE_ECS_BEGIN


class ToolSystemBase;
class PlayerHandComponent;

using PlayerHandComponentRef = RefT_Entity<PlayerHandComponent>;


class ToolComponent : public Component<ToolComponent> {
	
public:
	RTTI_COMP0(ToolComponent)
	COPY_PANIC(ToolComponent)
	COMP_DEF_VISIT
	
	void Initialize() override;
	void Uninitialize() override;
	bool Arg(String key, Object value) override;
	
	void SwitchNext();
	void SwitchOff();
	void AddTool(ComponentBaseRef cb);
	void RemoveTool(ComponentBaseRef cb);
	
	String title;
	String description;
	TypeId tool_type { AsVoidTypeId() };
	
	ComponentBaseRef active_tool;
	Array<ComponentBaseRef> tools;
	PlayerHandComponentRef active_hand;
	
};

using ToolComponentRef = Ref<ToolComponent>;



class ToolboxSystemBase :
	public System<ToolboxSystemBase>,
	public InteractionListener
{
	//LinkedList<EntityRef> entities;
	
public:
	//SYS_DEF_VISIT_(vis & instruction_text; vis | ctrls; vis && entities;)
	SYS_DEF_VISIT_(vis && tools && selectors && selector_objects)
	
	RTTI_DECL2(ToolboxSystemBase, System<ToolboxSystemBase>, InteractionListener)
	ECS_SYS_CTOR(ToolboxSystemBase);
	
	using Parent = Engine;
	
	
	void AddToolSystem(ToolSystemBaseRef system);
	void RemoveToolSystem(ToolSystemBaseRef system);
	
	void Attach(ToolComponentRef tool);
	void Detach(ToolComponentRef tool);
	
	const Array<ToolComponentRef>& GetTools() const {return tools;}
	
protected:
	// System
	void Start() override;
	void Update(double dt) override;
	void Stop() override;
	bool Initialize() override;
	void Uninitialize() override;
	bool Arg(String key, Object value) override;
	
private:
	Array<ToolComponentRef> tools;
	TypeMap<ToolSystemBaseRef> selectors;
	TypeMap<EntityRef> selector_objects;
	
	bool test_tool_changer{ false };
	bool show_toolbox{ false };
	int active_tool_idx = -1;
	
	/*enum ControllerHand {
		Left, Right, Count
	};*/
	
	//static String ControllerHandToString(ControllerHand hand);
	
	/*struct ControllerContext : RTTIBase {
		RTTI_DECL0(ControllerContext)
		
		EntityRef ctrl;
		EntityRef dbg_txt;
		ControllerHand hand;
		
		void Visit(RuntimeVisitor& vis) {(vis & ctrl) & dbg_txt;}
		void Clear() {ctrl.Clear(); dbg_txt.Clear();}
		operator bool() const {return !ctrl.IsEmpty() || !dbg_txt.IsEmpty();}
	};*/
	
protected:
	void SwitchToolType(EntityRef entity, const TypeId& new_type);
	void OnControllerPressed(const CtrlEvent& e) override;
	
	/*
	EntityRef instruction_text;
	FixedArray<ControllerContext, ControllerHand::Count> ctrls;*/
	
};

using ToolboxSystemBaseRef = Ref<ToolboxSystemBase>;


NAMESPACE_ECS_END

#endif
