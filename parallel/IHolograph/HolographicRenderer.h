#pragma once


NAMESPACE_PBR_BEGIN
struct Resources;
NAMESPACE_PBR_END


NAMESPACE_PARALLEL_BEGIN


class HolographicScene;
class TextRenderer;
class QuadRenderer;
class SkyboxRenderer;



// HolographicRenderer
// A stereoscopic 3D rendering system, manages rendering everything in the scene
// through DirectX 11 and Windows::Perception APIs
class HolographicRenderer :
	public System<HolographicRenderer>,
	public GfxDeviceNotify
{
public:
    HolographicRenderer(
        Engine& core,
        Shared<GfxDevResources> deviceResources,
        Shared<Pbr::Resources> pbr_res,
        NativeShaderResourceViewRef skyboxTexture);

    ~HolographicRenderer();

    Shared<Pbr::Resources> GetPbrResources();
    Shared<GfxDevResources> GetDeviceResources();

    void OnDeviceLost() override;
    void OnDeviceRestored() override;

protected:
    void Initialize() override;
    void Start() override;
    void Update(double) override;
    void Stop() override;
    void Uninitialize() override;

    void BindEventHandlers(const HoloSpace& holospace);
    void ReleaseEventHandlers(const HoloSpace& holospace);

private:
    Shared<EntityStore> m_entityStore;
    Shared<HolographicScene> m_holoScene;

    One<SkyboxRenderer> m_skyboxRenderer;

    ArrayMap<float, TextRenderer> m_textRenderers;
    One<QuadRenderer> m_quadRenderer;

    Shared<Pbr::Resources> pbr_res;

    NativeEventToken m_cameraAddedToken{};
    NativeEventToken m_cameraRemovedToken{};

    Shared<GfxDevResources> dev_res;

    TextRenderer* GetTextRendererForFontSize(float fontSize);

    bool RenderAtCameraPose(
        GfxCamResources *pCameraResources,
        const SpatialCoordinateSystem& coordinateSystem,
        HoloFramePred& prediction,
        const HoloCamRendParams& renderingParameters,
        const HoloCamPose& cameraPose);

    // Asynchronously creates resources for new holographic cameras.
    void OnCameraAdded(
        const HoloSpace& sender,
        const HoloSpaceCameraAddedEventArgs& args);

    // Synchronously releases resources for holographic cameras that are no longer
    // attached to the system.
    void OnCameraRemoved(
        const HoloSpace& sender,
        const HoloSpaceCameraRemovedEventArgs& args);
    
    
};


NAMESPACE_PARALLEL_END
