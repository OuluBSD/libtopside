#pragma once


NAMESPACE_ECS_BEGIN


class HolographicScene;
class TextRenderer;
class QuadRenderer;
class SkyboxRenderer;

using HolographicSceneRef = Ref<HolographicScene, RefParent1<Engine>>;


// HolographicRenderer
// A stereoscopic 3D rendering system, manages rendering everything in the scene
// through DirectX 11 and Windows::Perception APIs
class HolographicRenderer :
	public System<HolographicRenderer>/*,
	public Holo::GfxDeviceNotify*/
{
public:
	/*using Resources = Pbr::ResourcesT<Holo>;
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
	using NativeShaderResourceViewRef = typename Holo::NativeShaderResourceViewRef;*/
	
	ECS_SYS_CTOR(HolographicRenderer)
	
    /*HolographicRendererT(
        Ecs::Engine& core,
        Shared<GfxDevResources> dev_resources,
        Shared<Resources> pbr_res,
        NativeShaderResourceViewRef skybox_tex);

    ~HolographicRendererT();

    Shared<Resources> GetPbrResources();
    Shared<GfxDevResources> GetDeviceResources();

    void OnDeviceLost() override;
    void OnDeviceRestored() override;*/

protected:
    bool Initialize() override;
    void Start() override;
    void Update(double) override;
    void Stop() override;
    void Uninitialize() override;

    void BindEventHandlers(HoloSpace& holospace);
    //void ReleaseEventHandlers(const HoloSpace& holospace);

private:
    Ref<EntityStore>				entity_store;
    HolographicSceneRef				holo_scene;
    //Ref<PbrResources>				pbr_res;
    /*
    One<SkyboxRenderer>				skybox_rend;
    ArrayMap<float, TextRenderer>	text_rend;
    One<QuadRenderer>				quad_rend;
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
	*/
	
    // Asynchronously creates resources for new holographic cameras.
    void OnCameraAdded(
        const HoloSpace& sender,
        const CameraAddedEventArgs& args);
	
    // Synchronously releases resources for holographic cameras that are no longer
    // attached to the system.
    void OnCameraRemoved(
        const HoloSpace& sender,
        const CameraRemovedEventArgs& args);
    
    
};


NAMESPACE_ECS_END
