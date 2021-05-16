#pragma once


namespace Pbr {
struct Resources;
}

NAMESPACE_TOPSIDE_BEGIN


class HolographicScene;
class TextRenderer;
class QuadRenderer;
class SkyboxRenderer;

////////////////////////////////////////////////////////////////////////////////
// HolographicRenderer
// A stereoscopic 3D rendering system, manages rendering everything in the scene
// through DirectX 11 and Windows::Perception APIs
class HolographicRenderer :
	public System<HolographicRenderer>,
	public DX::IDeviceNotify
{
public:
    HolographicRenderer(
        Engine& core,
        Shared<DX::DeviceResources> deviceResources,
        Shared<Pbr::Resources> pbr_res,
        ID3D11ShaderResourceView* skyboxTexture);

    ~HolographicRenderer();

    Shared<Pbr::Resources> GetPbrResources();
    Shared<DX::DeviceResources> GetDeviceResources();

    void OnDeviceLost() override;
    void OnDeviceRestored() override;

protected:
    void Initialize() override;
    void Start() override;
    void Update(double) override;
    void Stop() override;
    void Uninitialize() override;

    void BindEventHandlers(
        const winrt::Windows::Graphics::Holographic::HolographicSpace& holospace);

    void ReleaseEventHandlers(
        const winrt::Windows::Graphics::Holographic::HolographicSpace& holospace);

private:
    Shared<EntityStore> m_entityStore{ nullptr };
    Shared<HolographicScene> m_holoScene{ nullptr };

    std::unique_ptr<SkyboxRenderer> m_skyboxRenderer{ nullptr };

    std::unordered_map<float, std::unique_ptr<TextRenderer>> m_textRenderers;
    std::unique_ptr<QuadRenderer> m_quadRenderer{ nullptr };

    Shared<Pbr::Resources> pbr_res{ nullptr };

    winrt::event_token m_cameraAddedToken{};
    winrt::event_token m_cameraRemovedToken{};

    Shared<DX::DeviceResources> dev_res{ nullptr };

    TextRenderer* GetTextRendererForFontSize(float fontSize);

    bool RenderAtCameraPose(
        DX::CameraResources *pCameraResources,
        winrt::Windows::Perception::Spatial::SpatialCoordinateSystem const& coordinateSystem,
        winrt::Windows::Graphics::Holographic::HolographicFramePrediction& prediction,
        winrt::Windows::Graphics::Holographic::HolographicCameraRenderingParameters const& renderingParameters,
        winrt::Windows::Graphics::Holographic::HolographicCameraPose const& cameraPose);

    // Asynchronously creates resources for new holographic cameras.
    void OnCameraAdded(
        winrt::Windows::Graphics::Holographic::HolographicSpace const& sender,
        winrt::Windows::Graphics::Holographic::HolographicSpaceCameraAddedEventArgs const& args);

    // Synchronously releases resources for holographic cameras that are no longer
    // attached to the system.
    void OnCameraRemoved(
        winrt::Windows::Graphics::Holographic::HolographicSpace const& sender,
        winrt::Windows::Graphics::Holographic::HolographicSpaceCameraRemovedEventArgs const& args);
};


NAMESPACE_TOPSIDE_END
