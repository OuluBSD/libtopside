#pragma once


NAMESPACE_PARALLEL_BEGIN
using namespace ::TS::Ecs::Win;
	
class HolographicScene;
class TextRenderer;
class QuadRenderer;
class SkyboxRenderer;


// HolographicRenderer
// A stereoscopic 3D rendering system, manages rendering everything in the scene
// through DirectX 11 and Windows::Perception APIs
class HolographicRenderer :
	public System<HolographicRenderer>,
	public IDeviceNotify
{
public:
	using System<HolographicRenderer>::System;
	using Base = System<HolographicRenderer>;
	RTTI_DECL2(HolographicRenderer, Base, IDeviceNotify)
	
    HolographicRenderer(
        Machine& core,
        std::shared_ptr<DeviceResources> deviceResources,
        std::shared_ptr<Pbr::Resources> pbrResources,
        ID3D11ShaderResourceView* skyboxTexture);

    ~HolographicRenderer();

    std::shared_ptr<Pbr::Resources> GetPbrResources();
    std::shared_ptr<DeviceResources> GetDeviceResources();

    void OnDeviceLost() override;
    void OnDeviceRestored() override;

protected:
    bool Initialize() override;
    void Start() override;
    void Update(double) override;
    void Stop() override;
    void Uninitialize() override;

    void BindEventHandlers(
        const winrt::Windows::Graphics::Holographic::HolographicSpace& holographicSpace);

    void ReleaseEventHandlers(
        const winrt::Windows::Graphics::Holographic::HolographicSpace& holographicSpace);

private:
    //Ecs::EntityStoreRef m_entityStore;
    
    Ref<HolographicScene> m_holoScene;

    std::unique_ptr<SkyboxRenderer> m_skyboxRenderer{ nullptr };

    std::unordered_map<float, std::unique_ptr<TextRenderer>> m_textRenderers;
    std::unique_ptr<QuadRenderer> m_quadRenderer{ nullptr };

    std::shared_ptr<Pbr::Resources> m_pbrResources{ nullptr };

    winrt::event_token m_cameraAddedToken{};
    winrt::event_token m_cameraRemovedToken{};

    std::shared_ptr<DeviceResources> m_deviceResources{ nullptr };

    TextRenderer* GetTextRendererForFontSize(float fontSize);

    bool RenderAtCameraPose(
        CameraResources *pCameraResources,
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


NAMESPACE_PARALLEL_END
