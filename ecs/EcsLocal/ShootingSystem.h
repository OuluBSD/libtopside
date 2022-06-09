#ifndef _EcsLocal_ShootingSystem_h_
#define _EcsLocal_ShootingSystem_h_

NAMESPACE_ECS_BEGIN


class ShootingComponent :
	public Component<ShootingComponent> {
	
public:
	RTTI_COMP0(ShootingComponent)
	COPY_PANIC(ShootingComponent)
	COMP_DEF_VISIT //_(vis & gun)
	
	
	
	void Initialize() override;
	void Uninitialize() override;
	//void SetEnabled(bool enable) override;
	//void Destroy() override;
	
	//EntityRef gun;
	
	float bullet_speed = 10.0f;
	mat4 barrel_to_ctrl;
};

using ShootingComponentRef = Ref<ShootingComponent>;


// ShootingInteractionSystem
// This ToolSystem manages the Gun tool which allows you to shoot balls in the 3D scene

class ShootingInteractionSystemBase :
	public ToolSystemBaseT<ShootingInteractionSystemBase, ShootingComponent>,
	public InteractionListener
{
	Array<ShootingComponentRef> comps;
	
public:
	using ToolSys = ToolSystemBaseT<ShootingInteractionSystemBase, ShootingComponent>;
	ECS_SYS_CTOR(ShootingInteractionSystemBase);
	RTTI_DECL2(ShootingInteractionSystemBase, ToolSys, InteractionListener)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<ToolSys>(this);}
	
	using Parent = Engine;
	
	static constexpr const char* POOL_NAME = "shooting";
	
	void Attach(ShootingComponentRef c);
	void Detach(ShootingComponentRef c);
	PoolRef GetPool() const {return GetEngine().Get<EntityStore>()->GetRoot()->GetAddPool(POOL_NAME);}
	
protected:
	// ToolSystemBase
	bool Initialize() override;
	void Uninitialize() override;
	String GetInstructions() const override;
	String GetDisplayName() const override;
	EntityRef CreateToolSelector() const override;
	void OnControllerPressed(const CtrlEvent& e) override;
	void OnControllerUpdated(const CtrlEvent& e) override;
	void OnControllerReleased(const CtrlEvent& e) override;
	
	void Register() override;
	void Unregister() override;
	void Activate(EntityRef entity) override;
	void Deactivate(EntityRef entity) override;
	
};


NAMESPACE_ECS_END

#endif
