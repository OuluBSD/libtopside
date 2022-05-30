#pragma once


NAMESPACE_ECS_BEGIN


class HolographicScene;
class TextRenderer;
//class QuadRenderer;
//class SkyboxRenderer;
class PbrModelCache;

using HolographicSceneRef = Ref<HolographicScene, RefParent1<Engine>>;
using PbrModelCacheRef = Ref<PbrModelCache, RefParent1<Engine>>;


// HolographicRenderingSystem
// A stereoscopic 3D rendering system, manages rendering everything in the scene
// through DirectX 11 and Windows::Perception APIs
class HolographicRenderingSystem :
	public System<HolographicRenderingSystem>,
	public HolographicScopeBinder,
	public DeviceNotify
{
public:
	/*using Resources = Pbr::ResourcesT<Holo>;
	using HolographicSpace = typename Holo::HolographicSpace;
	using HolographicFramePrediction = typename Holo::HolographicFramePrediction;
	using HolographicCameraRenderingParameters = typename Holo::HolographicCameraRenderingParameters;
	using HolographicCameraPose = typename Holo::HolographicCameraPose;
	using HolographicSpaceCameraAddedEventArgs = typename Holo::HolographicSpaceCameraAddedEventArgs;
	using HolographicSpaceCameraRemovedEventArgs = typename Holo::HolographicSpaceCameraRemovedEventArgs;
	using SpatialCoordinateSystem = typename Holo::SpatialCoordinateSystem;
	using GfxDevResources = typename Holo::GfxDevResources;
	using GfxCamResources = typename Holo::GfxCamResources;
	using NativeEventToken = typename Holo::NativeEventToken;
	using NativeShaderResourceViewRef = typename Holo::NativeShaderResourceViewRef;*/
	
	ECS_SYS_CTOR(HolographicRenderingSystem)
	
    /*HolographicRenderingSystemT(
        Ecs::Engine& core,
        Shared<GfxDevResources> dev_resources,
        Shared<Resources> pbr_res,
        NativeShaderResourceViewRef skybox_tex);

    ~HolographicRenderingSystemT();

    Shared<Resources> GetPbrResources();
    Shared<GfxDevResources> GetDeviceResources();
*/
    void OnDeviceLost() override;
    void OnDeviceRestored() override;

protected:
    bool Initialize() override;
    void Start() override;
    void Update(double) override;
    void Stop() override;
    void Uninitialize() override;

    void BindEventHandlers(HolographicSpace& holospace);
    //void ReleaseEventHandlers(const HolographicSpace& holospace);

private:
    Ref<EntityStore>			entity_store;
    PbrModelCacheRef			pbr_model_cache;
    HolographicSceneRef			holo_scene;
    
    One<QuadRenderer>			quad_rend;
    One<SkyboxRenderer>			skybox_rend;
	GfxDataState*				state = 0;
    
    /*DeviceResources*			dev_res = 0;
    Pbr::Resources*				pbr_res = 0;*/
    
    /*
    ArrayMap<float, TextRenderer>	text_rend;
    NativeEventToken			camera_added_event;
    NativeEventToken			camera_removed_event;
	
    TextRenderer* GetTextRendererForFontSize(float font_size);
	*/
    bool RenderAtCameraPose(
        CameraResources *cam_resources,
        const SpatialCoordinateSystem& coord_system,
        const HolographicFramePrediction& prediction,
        const HolographicCameraRenderingParameters& rend_params,
        const HolographicCameraPose& cam_pose);
	
	
    // Asynchronously creates resources for new holographic cameras.
    void OnCameraAdded(
        const HolographicSpace& sender,
        const CameraAddedEventArgs& args);
	
    // Synchronously releases resources for holographic cameras that are no longer
    // attached to the system.
    void OnCameraRemoved(
        const HolographicSpace& sender,
        const CameraRemovedEventArgs& args);
    
    
};

using HolographicRenderingSystemRef = Ref<HolographicRenderingSystem>;


NAMESPACE_ECS_END
