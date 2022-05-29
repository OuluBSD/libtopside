#pragma once

#if 1

NAMESPACE_ECS_BEGIN


class ThrowingComponent :
	public Component<ThrowingComponent> {
	
public:
	RTTI_COMP0(ThrowingComponent)
	COPY_PANIC(ThrowingComponent)
	COMP_DEF_VISIT
	
	
	
	void SetEnabled(bool enable) override;
	void Destroy() override;
	
	EntityRef ball_object;
	
	float distance_from_pointer = 0.05f;
	float scale = 0.25f;
};


// ThrowingInteractionSystem
// This ToolSystem manages the Throwing tool which allows you to throw baseballs in 3D scene
class ThrowingInteractionSystem : public ToolSystem<ThrowingInteractionSystem, ThrowingComponent> {
	
public:
	ECS_SYS_CTOR(ThrowingInteractionSystem);
	using ToolSys = ToolSystem<ThrowingInteractionSystem, ThrowingComponent>;
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<ToolSys>(this);}
	
	using Parent = Engine;
	static constexpr float ball_holding_distance = 0.075f;
	static constexpr const char* POOL_NAME = "throwing";
	
	PoolRef GetPool() const {return GetEngine().Get<EntityStore>()->GetRoot()->GetAddPool(POOL_NAME);}
	
	
protected:
	// System
	void Update(double dt) override;
	
	// IInteractionModeSystem
	String GetInstructions() const override;
	String GetDisplayName() const override;
	EntityRef CreateToolSelector() const override;
	
	// ISpatialInteractionListener
	//void OnSourcePressed(const SpatialInteractionSourceEventArgs& args) override;
	//void OnSourceReleased(const SpatialInteractionSourceEventArgs& args) override;
	
};


NAMESPACE_ECS_END

#endif
