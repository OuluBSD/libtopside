#include "WinLib.h"


NAMESPACE_PARALLEL_BEGIN


////////////////////////////////////////////////////////////////////////////////
// Holographic Renderer
////////////////////////////////////////////////////////////////////////////////
HolographicRenderer::HolographicRenderer(
    Engine& core,
    Shared<GfxDevResources> deviceResources,
    Shared<Pbr::Resources> pbr_res,
    NativeShaderResourceViewRef skyboxTexture) :
    System(core),
    dev_res(std::move(deviceResources)),
    pbr_res(std::move(pbr_res))
{
    m_quadRenderer = std::make_unique<QuadRenderer>(dev_res);
    m_skyboxRenderer = std::make_unique<SkyboxRenderer>(dev_res, skyboxTexture);
}

HolographicRenderer::~HolographicRenderer() = default;

Shared<Pbr::Resources> HolographicRenderer::GetPbrResources()
{
    fail_fast_if(pbr_res == nullptr);
    return pbr_res;
}

Shared<GfxDevResources> HolographicRenderer::GetDeviceResources()
{
    fail_fast_if(dev_res == nullptr);
    return dev_res;
}

void HolographicRenderer::OnDeviceLost()
{
    pbr_res->ReleaseDeviceDependentResources();
    for (auto& rendererPair : m_textRenderers)
    {
        rendererPair.second->ReleaseDeviceDependentResources();
    }
    m_quadRenderer->ReleaseDeviceDependentResources();
    m_skyboxRenderer->ReleaseDeviceDependentResources();
}

void HolographicRenderer::OnDeviceRestored()
{
    pbr_res->CreateDeviceDependentResources(dev_res->GetD3DDevice());
    for (auto& rendererPair : m_textRenderers)
    {
        rendererPair.second->CreateDeviceDependentResources();
    }
    m_quadRenderer->CreateDeviceDependentResources();
    m_skyboxRenderer->CreateDeviceDependentResources();
}

void HolographicRenderer::Initialize()
{
    dev_res->RegisterDeviceNotify(this);
    pbr_res->SetLight(vec4{ 0.0f, 0.7071067811865475f, -0.7071067811865475f }, Colors::White);
}

void HolographicRenderer::Uninitialize()
{
    dev_res->RegisterDeviceNotify(nullptr);
}

void HolographicRenderer::Start()
{
    m_entityStore = machine.Get<EntityStore>();
    m_holoScene = machine.Get<HolographicScene>();

    BindEventHandlers(m_holoScene->HolographicSpace());
}

void HolographicRenderer::Stop()
{
    ReleaseEventHandlers(m_holoScene->HolographicSpace());

    m_holoScene = nullptr;
    m_entityStore = nullptr;
}

void HolographicRenderer::Update(double)
{
    auto holographicFrame = m_holoScene->CurrentFrame();

    dev_res->EnsureCameraResources(holographicFrame, holographicFrame.CurrentPrediction());

    const bool shouldPresent = dev_res->UseHolographicCameraResources<bool>(
        [this, holographicFrame](std::map<UINT32, std::unique_ptr<GfxCamResources>>& cameraResourceMap)
    {
        // Up-to-date frame predictions enhance the effectiveness of image stablization and
        // allow more accurate positioning of holograms.
        m_holoScene->UpdateCurrentPrediction();

        HolographicFramePrediction prediction = holographicFrame.CurrentPrediction();
        SpatialCoordinateSystem coordinateSystem = m_holoScene->WorldCoordinateSystem();

        bool atLeastOneCameraRendered = false;
        for (HolographicCameraPose const& cameraPose : prediction.CameraPoses())
        {
            // This represents the device-based resources for a HolographicCamera.
            GfxCamResources* pCameraResources = cameraResourceMap[cameraPose.HolographicCamera().Id()].get();

            if (RenderAtCameraPose(pCameraResources, coordinateSystem, prediction, holographicFrame.GetRenderingParameters(cameraPose), cameraPose))
            {
                atLeastOneCameraRendered = true;
            }
        }

        return atLeastOneCameraRendered;
    });

    if (shouldPresent)
    {
        dev_res->Present(holographicFrame);
    }
}

TextRenderer* HolographicRenderer::GetTextRendererForFontSize(float fontSize)
{
    auto it = m_textRenderers.find(fontSize);
    if (it == m_textRenderers.end())
    {
        auto textRenderer = std::make_unique<TextRenderer>(dev_res, 1024u, 1024u, fontSize);
        it = m_textRenderers.insert(it, { fontSize, std::move(textRenderer) });
    }

    return it->second.get();
}

bool HolographicRenderer::RenderAtCameraPose(
    GfxCamResources *pCameraResources,
    const SpatialCoordinateSystem& coordinateSystem,
    HoloFramePred& prediction,
    const HoloCamRendParams& renderingParameters,
    const HoloCamPose& cameraPose)
{
    // Get the device context.
    const auto context = dev_res->GetD3DDeviceContext();
    const auto depthStencilView = pCameraResources->GetDepthStencilView();

    // Set render targets to the current holographic camera.
    const NativeRenderTargetViewRef targets[1] = { pCameraResources->GetBackBufferRenderTargetView() };
    context->OMSetRenderTargets(1, targets, depthStencilView);

    // TODO don't need to do this if we have a skybox
    // Clear the back buffer and depth stencil view.
    context->ClearRenderTargetView(targets[0], Colors::Transparent);
    context->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

    // The view and projection matrices for each holographic camera will change
    // every frame. This function will return false when positional tracking is lost.
    HolographicStereoTransform coordinateSystemToView;
    HolographicStereoTransform viewToProjection;
    bool cameraActive = pCameraResources->GetViewProjectionTransform(dev_res, cameraPose, coordinateSystem, &coordinateSystemToView, &viewToProjection);

    // Only render world-locked content when positional tracking is active.
    if (cameraActive)
    {
        ////////////////////////////////////////////////////////////////////////////////
        // Pbr Rendering
        pbr_res->SetViewProjection(
            XMLoadFloat4x4(&coordinateSystemToView.Left),
            XMLoadFloat4x4(&coordinateSystemToView.Right),
            XMLoadFloat4x4(&viewToProjection.Left),
            XMLoadFloat4x4(&viewToProjection.Right));

        pbr_res->Bind(dev_res->GetD3DDeviceContext());

        for (auto[transform, pbr] : m_entityStore->GetComponents<Transform, PbrRenderable>())
        {
            if (pbr->Model)
            {
                float4x4 transformMtx = transform->GetMatrix();

                if (pbr->Offset)
                {
                    transformMtx = *pbr->Offset * transformMtx;
                }

                pbr->Model->GetNode(Pbr::RootNodeIndex).SetTransform(XMLoadFloat4x4(&transformMtx));
                pbr->Model->Render(*pbr_res, dev_res->GetD3DDeviceContext());
            }
        }

        ////////////////////////////////////////////////////////////////////////////////
        // Text Rendering
        m_quadRenderer->SetViewProjection(
            coordinateSystemToView.Left,
            viewToProjection.Left,
            coordinateSystemToView.Right,
            viewToProjection.Right);

        m_quadRenderer->Bind();

        float prevFontSize = std::numeric_limits<float>::quiet_NaN();
        TextRenderer* textRenderer = nullptr;

        for (auto[transform, textRenderable] : m_entityStore->GetComponents<Transform, TextRenderable>())
        {
            if (prevFontSize != textRenderable->font_size)
            {
                prevFontSize = textRenderable->font_size;
                textRenderer = GetTextRendererForFontSize(prevFontSize);
            }

            textRenderer->RenderTextOffscreen(textRenderable->Text);
            m_quadRenderer->Render(transform->GetMatrix(), textRenderer->GetTexture());
        }

        m_quadRenderer->Unbind();

        ////////////////////////////////////////////////////////////////////////////////
        // Skybox Rendering
        float4x4 cameraToCoordinateSystem = float4x4::identity();
        if (auto location = SpatialLocator::GetDefault().TryLocateAtTimestamp(prediction.Timestamp(), coordinateSystem))
        {
            cameraToCoordinateSystem = make_float4x4_translation(location.Position());
        }

        m_skyboxRenderer->SetViewProjection(
            cameraToCoordinateSystem * coordinateSystemToView.Left,  viewToProjection.Left,
            cameraToCoordinateSystem * coordinateSystemToView.Right, viewToProjection.Right);

        m_skyboxRenderer->Bind();
        m_skyboxRenderer->Render();
        m_skyboxRenderer->Unbind();

        pCameraResources->CommitDirect3D11DepthBuffer(renderingParameters);
    }

    return true;
}

void HolographicRenderer::BindEventHandlers(
    const HoloSpace& holospace)
{
    fail_fast_if(holospace == nullptr);

    m_cameraAddedToken = holospace.CameraAdded(
        std::bind(&HolographicRenderer::OnCameraAdded, this, std::placeholders::_1, std::placeholders::_2));

    m_cameraRemovedToken = holospace.CameraRemoved(
        std::bind(&HolographicRenderer::OnCameraRemoved, this, std::placeholders::_1, std::placeholders::_2));
}

void HolographicRenderer::ReleaseEventHandlers(
    const HoloSpace& holospace)
{
    fail_fast_if(holospace == nullptr);

    holospace.CameraRemoved(m_cameraRemovedToken);
    holospace.CameraAdded(m_cameraAddedToken);
}

// Asynchronously creates resources for new holographic cameras.
void HolographicRenderer::OnCameraAdded(
    const HoloSpace& sender,
    HoloSpaceCameraAddedEventArgs const& args)
{
    Deferral deferral = args.GetDeferral();
    HolographicCamera holographicCamera = args.Camera();
    concurrency::create_task([this, deferral, holographicCamera]()
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
        dev_res->AddHolographicCamera(holographicCamera);

        // Holographic frame predictions will not include any information about this camera until
        // the deferral is completed.
        deferral.Complete();
    });
}

// Synchronously releases resources for holographic cameras that are no longer
// attached to the system.

void HolographicRenderer::OnCameraRemoved(
    const HoloSpace& sender,
    HoloSpaceCameraRemovedEventArgs const& args)
{
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
}


NAMESPACE_PARALLEL_END
