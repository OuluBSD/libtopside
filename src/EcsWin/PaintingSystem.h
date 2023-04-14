#pragma once


NAMESPACE_ECS_BEGIN


static constexpr float PaintTipThickness = 0.008f;


struct PaintComponent : Component<PaintComponent>
{
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
    std::vector<SharedEntity> colorPickerObjects;
    std::vector<SharedEntity> strokes;

    SharedEntity touchpadIndicator;
    SharedEntity strokeInProgress;
    SharedEntity paintBrush;
    SharedEntity beam;

    State currentState{ State::Idle };

    float touchpadX{ 0.0f };
    float touchpadY{ 0.0f };

    float thumbstickX{ 0.0f };
    float thumbstickY{ 0.0f };

    bool waitForTouchpadRelease{ false };

    winrt::Windows::UI::Input::Spatial::SpatialInteractionSourceLocation previousManipulationLocation{ nullptr };

    std::optional<DirectX::XMMATRIX> brushTipOffsetFromHoldingPose;
};

////////////////////////////////////////////////////////////////////////////////
// PaintingInteractionSystem
// This ToolSystem manages the PaintBrush tool which allows you to draw 3D strokes in the scene

class PaintingInteractionSystem : public ToolSystem<PaintingInteractionSystem, PaintComponent>
{
public:
    using ToolSystem::ToolSystem;

protected:
    // System
    void Start() override;
    void Update(double dt) override;
    void Stop() override;

    // ToolSystemBase
    std::wstring_view GetInstructions() const override;
    std::wstring_view GetDisplayName() const override;
    SharedEntity CreateToolSelector() const override;

    void Register(std::vector<SharedEntity> entities) override;
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

    std::vector<std::vector<SharedEntity>> m_persistentStrokes;
};


NAMESPACE_ECS_END
