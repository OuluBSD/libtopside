#pragma once


NAMESPACE_WIN_BEGIN


static constexpr float PaintTipThickness = 0.008f;


struct PaintComponent : Component<PaintComponent>
{
	RTTI_DECL1(PaintComponent, Component<PaintComponent>)
	COPY_PANIC(PaintComponent)
	
    enum class State
    {
        Idle,
        Painting,
        Manipulating,
        ColorSelection
    };

    void SetEnabled(bool enable) override;
    void Destroy() override;

    DirectX::XMVECTORF32 selectedColor{ DirectX::Colors::White };
    Array<EntityRef> colorPickerObjects;
    Array<EntityRef> strokes;

    EntityRef touchpadIndicator;
    EntityRef strokeInProgress;
    EntityRef paintBrush;
    EntityRef beam;

    State currentState{ State::Idle };

    float touchpadX{ 0.0f };
    float touchpadY{ 0.0f };

    float thumbstickX{ 0.0f };
    float thumbstickY{ 0.0f };

    bool waitForTouchpadRelease{ false };

    winrt::Windows::UI::Input::Spatial::SpatialInteractionSourceLocation previousManipulationLocation{ nullptr };

    std::optional<mat4> brushTipOffsetFromHoldingPose;
    
};

using PaintComponentRef = Ref<PaintComponent>;


////////////////////////////////////////////////////////////////////////////////
// PaintingInteractionSystem
// This ToolSystem manages the PaintBrush tool which allows you to draw 3D strokes in the scene

class PaintingInteractionSystem :
	public ToolSystem<PaintingInteractionSystem, PaintComponent>
{
public:
	using Base = ToolSystem<PaintingInteractionSystem, PaintComponent>;
	RTTI_DECL1(PaintingInteractionSystem, Base)
	
    using ToolSystem::ToolSystem;

protected:
    // System
    void Start() override;
    void Update(double dt) override;
    void Stop() override;

    // ToolSystemBase
    std::wstring_view GetInstructions() const override;
    std::wstring_view GetDisplayName() const override;
    EntityRef CreateToolSelector() const override;

    void Register(Array<EntityRef>& entities) override;
    void Activate(Entity& entity) override;
    void Deactivate(Entity& entity) override;

    // ISpatialInteractionListener
    void OnSourcePressed(
        const winrt::Windows::UI::Input::Spatial::SpatialInteractionSourceEventArgs& args) override;

    void OnSourceUpdated(
        const winrt::Windows::UI::Input::Spatial::SpatialInteractionSourceEventArgs& args) override;

    void OnSourceReleased(
        const winrt::Windows::UI::Input::Spatial::SpatialInteractionSourceEventArgs& args) override;

private:
    DirectX::XMVECTORF32 SelectColor(double x, double y);

    std::array<DirectX::XMVECTORF32, 10> m_colors =
    {
        DirectX::Colors::Red,
        DirectX::Colors::Chocolate,
        DirectX::Colors::Yellow,
        DirectX::Colors::Lime,
        DirectX::Colors::Cyan,
        DirectX::Colors::Blue,
        DirectX::Colors::MediumPurple,
        DirectX::Colors::White,
        DirectX::Colors::DimGray,
        DirectX::Colors::Black
    };

    Array<Array<EntityRef>> m_persistentStrokes;
};


NAMESPACE_WIN_END
