#include "EcsVR.h"


NAMESPACE_ECS_BEGIN


/*
HolographicRenderingSystem::HolographicRenderingSystemT(
    Engine& core,
    Shared<GfxDevResources> dev_resources,
    Shared<Pbr::Resources> pbr_res,
    NativeShaderResourceViewRef skybox_tex) :
    System<HolographicRenderingSystem>(core),
    dev_res(std::move(dev_resources)),
    pbr_res(std::move(pbr_res))
{
    quad_rend = std::make_unique<QuadRenderer>(dev_res);
    skybox_rend = std::make_unique<SkyboxRenderer>(dev_res, skybox_tex);
}*/


#if 0

HolographicRenderingSystem::~HolographicRenderingSystem() = default;



Shared<Pbr::Resources> HolographicRenderingSystem::GetPbrResources()
{
    fail_fast_if(pbr_res == nullptr);
    return pbr_res;
}


Shared<typename Holo::GfxDevResources> HolographicRenderingSystem::GetDeviceResources()
{
    fail_fast_if(dev_res == nullptr);
    return dev_res;
}

#endif

void HolographicRenderingSystem::OnDeviceLost()
{
	TODO
	/*
    pbr_res->ReleaseDeviceDependentResources();
    for (auto& renderer_pair : text_rend)
    {
        renderer_pair.second->ReleaseDeviceDependentResources();
    }
    quad_rend->ReleaseDeviceDependentResources();
    skybox_rend->ReleaseDeviceDependentResources();
    */
}


void HolographicRenderingSystem::OnDeviceRestored()
{
	TODO
	/*
    pbr_res->CreateDeviceDependentResources(dev_res->GetD3DDevice());
    for (auto& renderer_pair : text_rend)
    {
        renderer_pair.second->CreateDeviceDependentResources();
    }
    quad_rend->CreateDeviceDependentResources();
    skybox_rend->CreateDeviceDependentResources();
    */
}

bool HolographicRenderingSystem::Initialize()
{
	if (!HolographicScopeBinder::Initialize())
		return false;
	
	TODO
	#if 0
	s->dev_res.RegisterDeviceNotify(this);
    s->pbr_res.SetLight(vec4{ 0.0f, 0.707f, -0.707f }, Colors::White);
    
    Engine& e = GetEngine();
    
    pbr_model_cache = e.Get<PbrModelCache>();
    #endif
    
	return true;
}


void HolographicRenderingSystem::Uninitialize()
{
	if (!s) return;
	
	s->dev_res.RegisterDeviceNotify(nullptr);
}


void HolographicRenderingSystem::Start()
{
	Engine& e = GetEngine();
    entity_store = e.Get<EntityStore>();
    holo_scene = e.Get<HolographicScene>();

    BindEventHandlers(s->holospace);
}


void HolographicRenderingSystem::Stop()
{
	TODO
	/*
    ReleaseEventHandlers(holo_scene->HolographicSpace());

    holo_scene = 0;
    entity_store = 0;
    */
}


void HolographicRenderingSystem::Update(double dt)
{
	//if (state.IsEmpty()) {
	if (!state) {
		Serial::Machine& mach = Serial::GetActiveMachine();
		SpaceStoreRef ents = mach.Get<SpaceStore>();
		
		#ifdef flagVR
		#ifdef flagOGL
		RefT_Atom<X11OglHoloFboProg> x11_holo_ogl_fbo = ents->GetRoot()->FindDeep<X11OglHoloFboProg>();
		if (!state && x11_holo_ogl_fbo) {
			state = &x11_holo_ogl_fbo->data.accel_state;
		}
		#endif
		#endif
		//GfxDataState& ds = FboAtomT<X11SwGfx>::data.accel_state
		if (!state) TODO
			
			
		TODO // s->bind state
	}
	
	
	
    auto& holographic_frame = s->current_frame;

    s->dev_res.EnsureCameraResources(holographic_frame, holographic_frame.GetCurrentPrediction());

    const bool should_present = s->dev_res.UseHolographicCameraResources(
        [this](ArrayMap<uint32, CameraResources>& camera_resource_map, bool& ret)
    {
        auto& holographic_frame = s->current_frame;
        
        // Up-to-date frame predictions enhance the effectiveness of image stablization and
        // allow more accurate positioning of holograms.
        holo_scene->UpdateCurrentPrediction();

        const HolographicFramePrediction& prediction = holographic_frame.GetCurrentPrediction();
        SpatialCoordinateSystem& coord_system = holo_scene->GetWorldCoordinateSystem();

        bool at_least_one_camera_rendered = false;
        for (const HolographicCameraPose& cam_pose : prediction.GetCameraPoses())
        {
            // This represents the device-based resources for a HolographicCamera.
            int i = camera_resource_map.Find(cam_pose.GetHolographicCamera().GetId());
            CameraResources* cam_resources = i >= 0 ? &camera_resource_map[i] : 0;

            if (RenderAtCameraPose(cam_resources, coord_system, prediction, holographic_frame.GetRenderingParameters(cam_pose), cam_pose))
            {
                at_least_one_camera_rendered = true;
            }
        }

        ret = at_least_one_camera_rendered;
    });

    if (should_present)
    {
        s->dev_res.Present(holographic_frame);
    }
}

#if 0

TextRenderer* HolographicRenderingSystem::GetTextRendererForFontSize(float font_size)
{
	TODO
    /*auto it = text_rend.find(font_size);
    if (it == text_rend.end())
    {
        auto text_rend = std::make_unique<TextRenderer>(dev_res, 1024u, 1024u, font_size);
        it = text_rend.insert(it, { font_size, std::move(text_rend) });
    }

    return it->second.get();*/
}

#endif

bool HolographicRenderingSystem::RenderAtCameraPose(
    CameraResources *cam_resources,
    const SpatialCoordinateSystem& coord_system,
    const HolographicFramePrediction& prediction,
    const HolographicCameraRenderingParameters& rend_params,
    const HolographicCameraPose& cam_pose)
{
	TODO
	#if 0
	/*
    // Get the device context.
    const auto context = dev_res->GetD3DDeviceContext();
    const auto depth_stencil_view = cam_resources->GetDepthStencilView();

    // Set render targets to the current holographic camera.
    const NativeRenderTargetViewRef targets[1] = { cam_resources->GetBackBufferRenderTargetView() };
    context->OMSetRenderTargets(1, targets, depth_stencil_view);

    // TODO don't need to do this if we have a skybox
    // Clear the back buffer and depth stencil view.
    context->ClearRenderTargetView(targets[0], Colors::Transparent);
    context->ClearDepthStencilView(depth_stencil_view, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	*/

    // The view and projection matrices for each holographic camera will change
    // every frame. This function will return false when positional tracking is lost.
    HolographicStereoTransform coord_system_to_view;
    HolographicStereoTransform view_to_projection;
    bool camera_active = cam_resources->GetViewProjectionTransform(s->dev_res, cam_pose, coord_system, &coord_system_to_view, &view_to_projection);

    // Only render world-locked content when positional tracking is active.
    if (camera_active) {
        ////////////////////////////////////////////////////////////////////////////////
        // Pbr Rendering
        s->pbr_res.SetViewProjection(
            coord_system_to_view.left,
            coord_system_to_view.right,
            view_to_projection.left,
            view_to_projection.right);

        //pbr_res->Bind(dev_res->GetD3DDeviceContext());
		const Vector<PbrRenderable*>& comps = pbr_model_cache->GetComponents();
        for (PbrRenderable* pbr : comps)
        {
            if (pbr->model)
            {
                TransformRef transform = pbr->GetEntity()->Get<Transform>();
                mat4 transform_matrix = transform->GetMatrix();
                
                if (pbr->offset)
                {
                    transform_matrix = *pbr->offset * transform_matrix;
                }

                pbr->model->GetNode(/*root_parent_node_index*/-1).SetTransform(transform_matrix);
                pbr->model->Render(s->pbr_res/*, dev_res.GetD3DDeviceContext()*/);
            }
        }
        
        
        // Text Rendering
        quad_rend->SetViewProjection(
            coord_system_to_view.left,
            view_to_projection.left,
            coord_system_to_view.right,
            view_to_projection.right);

        quad_rend->Bind();

        float prev_font_size = std::numeric_limits<float>::quiet_NaN();
        TextRenderer* text_rend = nullptr;

		TODO
		/*
        for (auto[transform, text_renderable] : entity_store->GetComponents<Transform, TextRenderable>())
        {
            if (prev_font_size != text_renderable->font_size)
            {
                prev_font_size = text_renderable->font_size;
                text_rend = GetTextRendererForFontSize(prev_font_size);
            }

            text_rend->RenderTextOffscreen(text_renderable->Text);
            quad_rend->Render(transform->GetMatrix(), text_rend->GetTexture());
        }
        */

        quad_rend->Unbind();

        ////////////////////////////////////////////////////////////////////////////////
        // Skybox Rendering
        mat4 camera_to_coord_sys = identity<mat4>();
        if (auto location = GetActiveSpatialLocator().TryLocateAtTimestamp(prediction.GetTimestamp(), coord_system))
        {
            camera_to_coord_sys = make_mat4_translation(location.GetPosition());
        }

        skybox_rend->SetViewProjection(
            camera_to_coord_sys * coord_system_to_view.left,  view_to_projection.left,
            camera_to_coord_sys * coord_system_to_view.right, view_to_projection.right);

        skybox_rend->Bind();
        skybox_rend->Render();
        skybox_rend->Unbind();

        TODO //cam_resources->CommitDirect3D11DepthBuffer(rend_params);
    }

    return true;
    #endif
}

void HolographicRenderingSystem::BindEventHandlers(HolographicSpace& holospace) {
	holospace.WhenCameraAdded.Add(THISBACK(OnCameraAdded));
    holospace.WhenCameraRemoved.Add(THISBACK(OnCameraRemoved));
}

#if 0

void HolographicRenderingSystem::ReleaseEventHandlers(
    const HolographicSpace& holospace)
{
    fail_fast_if(holospace == nullptr);

    holospace.CameraRemoved(camera_removed_event);
    holospace.CameraAdded(camera_added_event);
}

#endif

// Asynchronously creates resources for new holographic cameras.

void HolographicRenderingSystem::OnCameraAdded(
    const HolographicSpace& sender,
    CameraAddedEventArgs const& args)
{
	TODO
	#if 0
    Deferral deferral = args.GetDeferral();
    HolographicCamera holocam = args.Camera();
    concurrency::create_task([this, deferral, holocam]()
    {
        //
        // TODO: Allocate resources for the new camera and load any content specific to
        //       that camera. Note that the render target size (in pixels) is a property
        //       of the HolographicCamera object, and can be used to create off-screen
        //       render targets that match the resolution of the HolographicCamera.
        //

        // Create device-based resources for the holographic camera and add it to the list of
        // cameras used for updates and rendering. Notes:
        //   * Since this function may be called at any time, the AddHolographicCamera function
        //     waits until it can get a lock on the set of holographic camera resources before
        //     adding the new camera. At 60 frames per second this wait should not take long.
        //   * A subsequent Update will take the back buffer from the RenderingParameters of this
        //     camera's CameraPose and use it to create the ID3D11RenderTargetView for this camera.
        //     Content can then be rendered for the HolographicCamera.
        dev_res->AddHolographicCamera(holocam);

        // Holographic frame predictions will not include any information about this camera until
        // the deferral is completed.
        deferral.Complete();
    });
    #endif
}

// Synchronously releases resources for holographic cameras that are no longer
// attached to the system.


void HolographicRenderingSystem::OnCameraRemoved(
    const HolographicSpace& sender,
    CameraRemovedEventArgs const& args)
{
	TODO
	/*
    concurrency::create_task([this]()
    {
        //
        // TODO: Asynchronously unload or deactivate content resources (not back buffer
        //       resources) that are specific only to the camera that was removed.
        //
    });

    // Before letting this callback return, ensure that all references to the back buffer
    // are released.
    // Since this function may be called at any time, the RemoveHolographicCamera function
    // waits until it can get a lock on the set of holographic camera resources before
    // deallocating resources for this camera. At 60 frames per second this wait should
    // not take long.
    dev_res->RemoveHolographicCamera(args.Camera());
    */
}


NAMESPACE_ECS_END
