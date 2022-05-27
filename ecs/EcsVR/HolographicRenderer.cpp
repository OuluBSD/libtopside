#include "EcsVR.h"


NAMESPACE_ECS_BEGIN


/*
HolographicRenderer::HolographicRendererT(
    Engine& core,
    Shared<GfxDevResources> dev_resources,
    Shared<Pbr::Resources> pbr_res,
    NativeShaderResourceViewRef skybox_tex) :
    System<HolographicRenderer>(core),
    dev_res(std::move(dev_resources)),
    pbr_res(std::move(pbr_res))
{
    quad_rend = std::make_unique<QuadRenderer>(dev_res);
    skybox_rend = std::make_unique<SkyboxRenderer>(dev_res, skybox_tex);
}*/


#if 0

HolographicRenderer::~HolographicRenderer() = default;


Shared<Pbr::Resources> HolographicRenderer::GetPbrResources()
{
    fail_fast_if(pbr_res == nullptr);
    return pbr_res;
}


Shared<typename Holo::GfxDevResources> HolographicRenderer::GetDeviceResources()
{
    fail_fast_if(dev_res == nullptr);
    return dev_res;
}


void HolographicRenderer::OnDeviceLost()
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


void HolographicRenderer::OnDeviceRestored()
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

#endif

bool HolographicRenderer::Initialize()
{
	LOG("HolographicRenderer::Initialize: TODO attach atom");
    //dev_res->RegisterDeviceNotify(this);
    //pbr_res->SetLight(vec4{ 0.0f, 0.707f, -0.707f }, Colors::White);
    return true;
}


void HolographicRenderer::Uninitialize()
{
	TODO
	/*
    dev_res->RegisterDeviceNotify(nullptr);
    */
}


void HolographicRenderer::Start()
{
	Engine& e = GetEngine();
    entity_store = e.Get<EntityStore>();
    holo_scene = e.Get<HolographicScene>();

    BindEventHandlers(holo_scene->GetHolographicSpace());
}


void HolographicRenderer::Stop()
{
	TODO
	/*
    ReleaseEventHandlers(holo_scene->HolographicSpace());

    holo_scene = 0;
    entity_store = 0;
    */
}


void HolographicRenderer::Update(double)
{
	TODO
	/*
    auto holographic_frame = holo_scene->CurrentFrame();

    dev_res->EnsureCameraResources(holographic_frame, holographic_frame.CurrentPrediction());

    const bool shouldPresent = dev_res->UseHolographicCameraResources<bool>(
        [this, holographic_frame](ArrayMap<uint32, GfxCamResources>& camera_resource_map)
    {
        // Up-to-date frame predictions enhance the effectiveness of image stablization and
        // allow more accurate positioning of holograms.
        holo_scene->UpdateCurrentPrediction();

        HolographicFramePrediction prediction = holographic_frame.CurrentPrediction();
        SpatialCoordinateSystem coord_system = holo_scene->WorldCoordinateSystem();

        bool at_least_one_camera_rendered = false;
        for (const HolographicCameraPose& cam_pose : prediction.CameraPoses())
        {
            // This represents the device-based resources for a HolographicCamera.
            GfxCamResources* cam_resources = camera_resource_map[cam_pose.HolographicCamera().Id()].get();

            if (RenderAtCameraPose(cam_resources, coord_system, prediction, holographic_frame.GetRenderingParameters(cam_pose), cam_pose))
            {
                at_least_one_camera_rendered = true;
            }
        }

        return at_least_one_camera_rendered;
    });

    if (shouldPresent)
    {
        dev_res->Present(holographic_frame);
    }
    */
}

#if 0

TextRenderer* HolographicRenderer::GetTextRendererForFontSize(float font_size)
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


bool HolographicRenderer::RenderAtCameraPose(
    GfxCamResources *cam_resources,
    const SpatialCoordinateSystem& coord_system,
    HoloFramePred& prediction,
    const HoloCamRendParams& rend_params,
    const HoloCamPose& cam_pose)
{
	TODO
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

    // The view and projection matrices for each holographic camera will change
    // every frame. This function will return false when positional tracking is lost.
    HolographicStereoTransform coord_system_to_view;
    HolographicStereoTransform view_to_projection;
    bool cameraActive = cam_resources->GetViewProjectionTransform(dev_res, cam_pose, coord_system, &coord_system_to_view, &view_to_projection);

    // Only render world-locked content when positional tracking is active.
    if (cameraActive) {
        ////////////////////////////////////////////////////////////////////////////////
        // Pbr Rendering
        pbr_res->SetViewProjection(
            XMLoadFloat4x4(&coord_system_to_view.Left),
            XMLoadFloat4x4(&coord_system_to_view.Right),
            XMLoadFloat4x4(&view_to_projection.Left),
            XMLoadFloat4x4(&view_to_projection.Right));

        pbr_res->Bind(dev_res->GetD3DDeviceContext());

        for (auto[transform, pbr] : entity_store->GetComponents<Transform, PbrRenderable>())
        {
            if (pbr->Model)
            {
                mat4 transform_matrix = transform->GetMatrix();

                if (pbr->Offset)
                {
                    transform_matrix = *pbr->Offset * transform_matrix;
                }

                pbr->Model->GetNode(Pbr::RootNodeIndex).SetTransform(XMLoadFloat4x4(&transform_matrix));
                pbr->Model->Render(*pbr_res, dev_res->GetD3DDeviceContext());
            }
        }

        ////////////////////////////////////////////////////////////////////////////////
        // Text Rendering
        quad_rend->SetViewProjection(
            coord_system_to_view.left,
            view_to_projection.left,
            coord_system_to_view.right,
            view_to_projection.right);

        quad_rend->Bind();

        float prev_font_size = std::numeric_limits<float>::quiet_NaN();
        TextRenderer* text_rend = nullptr;

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

        quad_rend->Unbind();

        ////////////////////////////////////////////////////////////////////////////////
        // Skybox Rendering
        mat4 camera_to_coord_sys = mat4::identity();
        if (auto location = SpatialLocator::GetDefault().TryLocateAtTimestamp(prediction.Timestamp(), coord_system))
        {
            camera_to_coord_sys = make_mat4_translation(location.Position());
        }

        skybox_rend->SetViewProjection(
            camera_to_coord_sys * coord_system_to_view.Left,  view_to_projection.Left,
            camera_to_coord_sys * coord_system_to_view.Right, view_to_projection.Right);

        skybox_rend->Bind();
        skybox_rend->Render();
        skybox_rend->Unbind();

        cam_resources->CommitDirect3D11DepthBuffer(rend_params);
    }

    return true;*/
}

#endif

void HolographicRenderer::BindEventHandlers(HoloSpace& holospace) {
	holospace.WhenCameraAdded.Add(THISBACK(OnCameraAdded));
    holospace.WhenCameraRemoved.Add(THISBACK(OnCameraRemoved));
}

#if 0

void HolographicRenderer::ReleaseEventHandlers(
    const HoloSpace& holospace)
{
    fail_fast_if(holospace == nullptr);

    holospace.CameraRemoved(camera_removed_event);
    holospace.CameraAdded(camera_added_event);
}

#endif

// Asynchronously creates resources for new holographic cameras.

void HolographicRenderer::OnCameraAdded(
    const HoloSpace& sender,
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


void HolographicRenderer::OnCameraRemoved(
    const HoloSpace& sender,
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
