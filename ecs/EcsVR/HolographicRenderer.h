#pragma once


NAMESPACE_ECS_BEGIN


class HolographicScene;
class TextRenderer;
class QuadRenderer;
class SkyboxRenderer;



// HolographicRenderer
// A stereoscopic 3D rendering system, manages rendering everything in the scene
// through DirectX 11 and Windows::Perception APIs
template <class Holo>
class HolographicRendererT :
	public System<HolographicRendererT<Holo>>,
	public Holo::GfxDeviceNotify
{
public:
	using Resources = Pbr::ResourcesT<Holo>;
	using HoloSpace = typename Holo::HoloSpace;
	using HoloFramePred = typename Holo::HoloFramePred;
	using HoloCamRendParams = typename Holo::HoloCamRendParams;
	using HoloCamPose = typename Holo::HoloCamPose;
	using HoloSpaceCameraAddedEventArgs = typename Holo::HoloSpaceCameraAddedEventArgs;
	using HoloSpaceCameraRemovedEventArgs = typename Holo::HoloSpaceCameraRemovedEventArgs;
	using SpatialCoordinateSystem = typename Holo::SpatialCoordinateSystem;
	using GfxDevResources = typename Holo::GfxDevResources;
	using GfxCamResources = typename Holo::GfxCamResources;
	using NativeEventToken = typename Holo::NativeEventToken;
	using NativeShaderResourceViewRef = typename Holo::NativeShaderResourceViewRef;
	
    HolographicRendererT(
        Ecs::Engine& core,
        Shared<GfxDevResources> dev_resources,
        Shared<Resources> pbr_res,
        NativeShaderResourceViewRef skybox_tex);

    ~HolographicRendererT();

    Shared<Resources> GetPbrResources();
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
    Shared<Ecs::EntityStore>		entity_store;
    Shared<HolographicScene>		holo_scene;
    One<SkyboxRenderer>				skybox_rend;
    ArrayMap<float, TextRenderer>	text_rend;
    One<QuadRenderer>				quad_rend;
    Shared<Resources>				pbr_res;
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


NAMESPACE_ECS_END
