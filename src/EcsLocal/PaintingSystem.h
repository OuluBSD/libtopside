#pragma once

#if 1


NAMESPACE_ECS_BEGIN


class PaintComponent :
	public CustomToolComponent {
	
public:
	RTTI_COMP1(PaintComponent, CustomToolComponent)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<CustomToolComponent>(this);}
	
	
	
	typedef enum : byte  {
		Idle,
		Painting,
		Manipulating,
		ColorSelection
	} State;
	
	void Etherize(Ether& e) override;
	void Initialize() override;
	void Uninitialize() override;
	void SetEnabled(bool enable) override;
	void Destroy() override;
	bool LoadModel(ModelComponent&) override;
	
	
	EntityRef touchpad_indicator;
	EntityRef stroke_in_progress;
	EntityRef paint_brush;
	EntityRef beam;
	LinkedList<EntityRef> clr_pick_objects;
	LinkedList<EntityRef> strokes;
	HandSourceLocation* prev_manip_loc = 0;
	
	vec4 selected_color = Colors::White;
	byte cur_state { State::Idle };
	
	float touchpad_x = 0.0f;
	float touchpad_y = 0.0f;
	
	float thumbstick_x = 0.0f;
	float thumbstick_y = 0.0f;
	
	bool wait_touchpad_release = false;
	
	mat4 brush_tip_offset_from_holding_pose;
	bool has_brush_tip_offset = false;
	
};



class PaintingInteractionSystemBase :
	public ToolSystemBaseT<PaintingInteractionSystemBase, PaintComponent>
{
public:
	using ToolSys = ToolSystemBaseT<PaintingInteractionSystemBase, PaintComponent>;
	RTTI_DECL1(PaintingInteractionSystemBase, ToolSys)
	ECS_SYS_CTOR(PaintingInteractionSystemBase);
	
	void Visit(RuntimeVisitor& vis) override {
		vis.VisitThis<ToolSys>(this);
		for (auto& v : persistent_strokes)
			for (auto& r : v)
				vis & r;
	}
	
	
	
	using Parent = Engine;
	
	static constexpr float paint_tip_thickness = 0.008f;
	static constexpr const char* POOL_NAME = "painting";
	
	PoolRef GetPool() const {return GetEngine().Get<EntityStore>()->GetRoot()->GetAddPool(POOL_NAME);}
	
	void Attach(PaintComponentRef c);
	void Detach(PaintComponentRef c);
	
protected:
	// System
	bool Initialize() override;
	void Start() override;
	void Update(double dt) override;
	void Stop() override;
	void Uninitialize() override;
	bool Arg(String key, Object value) override;
	
	// ToolSystemBase
	String GetInstructions() const override;
	String GetDisplayName() const override;
	EntityRef CreateToolSelector() const override;
	
	void Register() override;
	void Unregister() override;
	void Activate(EntityRef entity) override;
	void Deactivate(EntityRef entity) override;
	
	// ISpatialInteractionListener
	void OnControllerPressed(const CtrlEvent& e) override;
	void OnControllerUpdated(const CtrlEvent& e) override;
	void OnControllerReleased(const CtrlEvent& e) override;
	
private:
	vec4 SelectColor(double x, double y);
	void ClearStrokes();
	
	SimpleFixedArray<vec4, 10> colors = {
		Colors::Red,
		Colors::Chocolate,
		Colors::Yellow,
		Colors::Lime,
		Colors::Cyan,
		Colors::Blue,
		Colors::MediumPurple,
		Colors::White,
		Colors::DimGray,
		Colors::Black
	};
	
	ToolboxSystemBaseRef tb;
	Array<PaintComponentRef> comps;
	LinkedList<LinkedList<EntityRef>> persistent_strokes;
	bool dbg_model = false;
	
	
};


NAMESPACE_ECS_END

#endif
