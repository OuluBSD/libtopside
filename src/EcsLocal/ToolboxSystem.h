#ifndef _EcsLocal_ToolboxSystem_h_
#define _EcsLocal_ToolboxSystem_h_


NAMESPACE_ECS_BEGIN


class ToolSystemBase;
class PlayerHandComponent;

using PlayerHandComponentRef = RefT_Entity<PlayerHandComponent>;



class CustomToolComponent :
	public Component<CustomToolComponent> {
	
public:
	RTTI_COMP0(CustomToolComponent)
	COPY_PANIC(CustomToolComponent)
	COMP_DEF_VISIT
	
	virtual bool LoadModel(ModelComponent&) = 0;
	
};

using CustomToolComponentRef = Ref<CustomToolComponent>;



class ToolComponent : public Component<ToolComponent> {
	
public:
	RTTI_COMP0(ToolComponent)
	COPY_PANIC(ToolComponent)
	COMP_DEF_VISIT_(vis & active_tool & active_hand; vis && tools;)
	
	void Initialize() override;
	void Uninitialize() override;
	bool Arg(String key, Object value) override;
	
	void SwitchNext();
	void SwitchOff();
	void AddTool(CustomToolComponentRef cb);
	void RemoveTool(CustomToolComponentRef cb);
	void RefreshModel();
	
	String title;
	String description;
	TypeId tool_type { AsVoidTypeId() };
	
	CustomToolComponentRef active_tool;
	Array<CustomToolComponentRef> tools;
	PlayerHandComponentRef active_hand;
	
};

using ToolComponentRef = Ref<ToolComponent>;


class ToolboxSystemBase :
	public System<ToolboxSystemBase>,
	public InteractionListener
{
	
public:
	ECS_SYS_DEF_VISIT_(vis && tools && selectors && selector_objects)
	
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
	
	
protected:
	void SwitchToolType(EntityRef entity, const TypeId& new_type);
	void OnControllerPressed(const CtrlEvent& e) override;
	
};

using ToolboxSystemBaseRef = Ref<ToolboxSystemBase>;


NAMESPACE_ECS_END

#endif
