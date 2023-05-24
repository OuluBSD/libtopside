#ifndef _EcsLocal_ThrowingSystem_h_
#define _EcsLocal_ThrowingSystem_h_

NAMESPACE_ECS_BEGIN


class ThrowingComponent :
	public CustomToolComponent {
	
public:
	RTTI_COMP1(ThrowingComponent, CustomToolComponent)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<CustomToolComponent>(this); vis & ball_object;}
	
	
	void Etherize(Ether& e) override;
	void Initialize() override;
	void Uninitialize() override;
	void SetEnabled(bool enable) override;
	void Destroy() override;
	bool LoadModel(ModelComponent&) override;
	
	EntityRef ball_object;
	
	float distance_from_pointer = 0.05f;
	float scale = 0.25f;
};

using ThrowingComponentRef = Ref<ThrowingComponent>;


// ThrowingInteractionSystem
// This ToolSystem manages the Throwing tool which allows you to throw baseballs in 3D scene
class ThrowingInteractionSystemBase :
	public ToolSystemBaseT<ThrowingInteractionSystemBase, ThrowingComponent>
{
	Array<ThrowingComponentRef> comps;
	
public:
	using ToolSys = ToolSystemBaseT<ThrowingInteractionSystemBase, ThrowingComponent>;
	ECS_SYS_CTOR(ThrowingInteractionSystemBase);
	RTTI_DECL1(ThrowingInteractionSystemBase, ToolSys)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<ToolSys>(this);}
	
	using Parent = Engine;
	float ball_holding_distance;
	static constexpr const char* POOL_NAME = "throwing";
	
	void Attach(ThrowingComponentRef c);
	void Detach(ThrowingComponentRef c);
	PoolRef GetPool() const {return GetEngine().Get<EntityStore>()->GetRoot()->GetAddPool(POOL_NAME);}
	
	
protected:
	// System
	bool Initialize() override;
	void Uninitialize() override;
	void Update(double dt) override;
	void OnControllerPressed(const CtrlEvent& e) override;
	void OnControllerUpdated(const CtrlEvent& e) override;
	void OnControllerReleased(const CtrlEvent& e) override;
	
	// IInteractionModeSystem
	String GetInstructions() const override;
	String GetDisplayName() const override;
	EntityRef CreateToolSelector() const override;
	void Register() override;
	void Unregister() override;
	void Activate(EntityRef entity) override;
	void Deactivate(EntityRef entity) override;
	
};


NAMESPACE_ECS_END

#endif
