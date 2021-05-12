#pragma once


static constexpr float paint_tip_thickness = 0.008f;


NAMESPACE_OULU_BEGIN

	
class PaintComponent :
	public Component<PaintComponent>
{
	VIS_COMP_0_0
	
public:
	COPY_PANIC(PaintComponent)
	void Visit(RuntimeVisitor& vis) override {}
	
	
    enum class State
    {
        Idle,
        Painting,
        Manipulating,
        ColorSelection
    };

    void SetEnabled(bool enable) override;
    void Destroy() override;

    vec4 selected_color = Colors::White;
    LinkedList<EntityRef> clr_pick_objects;
    LinkedList<EntityRef> strokes;

    EntityRef touchpad_indicator;
    EntityRef stroke_in_progress;
    EntityRef paint_brush;
    EntityRef beam;

    State cur_state { State::Idle };

    float touchpad_x = 0.0f;
    float touchpad_y = 0.0f;

    float thumbstick_x = 0.0f;
    float thumbstick_y = 0.0f;

    bool wait_touchpad_release = false;

    SpatialInteractionSourceLocation prev_manip_loc;

    Optional<mat4> brush_tip_offset_from_holding_pose;
    
};



class PaintingInteractionSystem :
	public ToolSystem<PaintingInteractionSystem, PaintComponent>
{
public:
    using ToolSystem::ToolSystem;

protected:
    // System
    void Start() override;
    void Update(double dt) override;
    void Stop() override;

    // ToolSystemBase
    String GetInstructions() const override;
    String GetDisplayName() const override;
    EntityRef CreateToolSelector() const override;

    void Register(const LinkedList<EntityRef>& entities) override;
    void Activate(EntityRef entity) override;
    void Deactivate(EntityRef entity) override;

    // ISpatialInteractionListener
    void OnSourcePressed(const SpatialInteractionSourceEventArgs& args) override;
    void OnSourceUpdated(const SpatialInteractionSourceEventArgs& args) override;
    void OnSourceReleased(const SpatialInteractionSourceEventArgs& args) override;

private:
    vec4 SelectColor(double x, double y);

    FixedArray<vec4, 10> colors =
    {
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

    LinkedList<LinkedList<EntityRef>> persistent_strokes;
};


NAMESPACE_OULU_END

