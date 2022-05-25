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
        Shared<GfxDevResources> dev_resources,
        Shared<Pbr::Resources> pbr_res,
        NativeShaderResourceViewRef skybox_tex);

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
    Shared<EntityStore>				entity_store;
    Shared<HolographicScene>		holo_scene;
    One<SkyboxRenderer>				skybox_rend;
    ArrayMap<float, TextRenderer>	text_rend;
    One<QuadRenderer>				quad_rend;
    Shared<Pbr::Resources>			pbr_res;
    NativeEventToken				camera_added_event;
    NativeEventToken				camera_removed_event;
    Shared<GfxDevResources>			dev_res;
	
    TextRenderer* GetTextRendererForFontSize(float font_size);
	
    bool RenderAtCameraPose(
        GfxCamResources *cam_resources,
        const SpatialCoordinateSystem& coord_system,
        HoloFramePred& prediction,
        const HoloCamRendParams& rend_params,
        const HoloCamPose& cam_pose);
	
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
