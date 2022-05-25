#include "WinLib.h"


NAMESPACE_PARALLEL_BEGIN


GfxCamResources::CameraResources(const HolographicCamera& camera) :
    holocam(camera),
    is_stereo(camera.IsStereo()),
    gfx_rend_tgt_size(camera.RenderTargetSize())
{
    gfx_viewport = CD3D11_VIEWPORT(
        0.f, 0.f,
        gfx_rend_tgt_size.cx,
        gfx_rend_tgt_size.cy
        );
};

// Updates resources associated with a holographic camera's swap chain.
// The app does not access the swap chain directly, but it does create
// resource views for the back buffer.
void GfxCamResources::CreateResourcesForBackBuffer(
    const GfxDevResources* dev_resources,
    const HolographicCameraRenderingParameters& cam_params
    )
{
    ID3D11Device* device = dev_resources->GetD3DDevice();

    // Get the WinRT object representing the holographic camera's back buffer.
    IDirect3DSurface surface = cam_params.Direct3D11BackBuffer();

    // Get the holographic camera's back buffer.
    // Holographic apps do not create a swap chain themselves; instead, buffers are
    // owned by the system. The Direct3D back buffer resources are provided to the
    // app using WinRT interop APIs.
    ComPtr<ID3D11Texture2D> cam_back_buf;
    Holo::CheckResult(surface.as<GfxLibInterfaceAccess>()->GetInterface(IID_PPV_ARGS(&cam_back_buf)));

    // Determine if the back buffer has changed. If so, ensure that the render target view
    // is for the current back buffer.
    if (gfx_back_buffer.Get() != cam_back_buf.Get())
    {
        // This can change every frame as the system moves to the next buffer in the
        // swap chain. This mode of operation will occur when certain rendering modes
        // are activated.
        gfx_back_buffer = cam_back_buf;

        // Create a render target view of the back buffer.
        // Creating this resource is inexpensive, and is better than keeping track of
        // the back buffers in order to pre-allocate render target views for each one.
        Holo::CheckResult(
            device->CreateRenderTargetView(
                gfx_back_buffer.Get(),
                nullptr,
                &gfx_rend_tgt_view
            ));

        // Get the DXGI format for the back buffer.
        // This information can be accessed by the app using CameraResources::GetBackBufferDXGIFormat().
        D3D11_TEXTURE2D_DESC backBufferDesc;
        gfx_back_buffer->GetDesc(&backBufferDesc);
        gfxlib_fmt = backBufferDesc.Format;

        // Check for render target size changes.
        vec2 current_size = holocam.RenderTargetSize();
        if (gfx_rend_tgt_size != current_size)
        {
            // Set render target size.
            gfx_rend_tgt_size = current_size;

            // A new depth stencil view is also needed.
            gfx_depth_stencil_view.Reset();
        }
    }

    // Refresh depth stencil resources, if needed.
    if (gfx_depth_stencil_view == nullptr)
    {
        // Create a depth stencil view for use with 3D rendering if needed.
        CD3D11_TEXTURE2D_DESC depth_stencil_desc(
            DXGI_FORMAT_R16_TYPELESS,
            static_cast<uint32>(gfx_rend_tgt_size.cx),
            static_cast<uint32>(gfx_rend_tgt_size.cy),
            is_stereo ? 2 : 1, // Create two textures when rendering in stereo.
            1, // Use a single mipmap level.
            D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE
        );

        Holo::CheckResult(
            device->CreateTexture2D(
                &depth_stencil_desc,
                nullptr,
                &gfx_depth_stencil
            ));

        CD3D11_DEPTH_STENCIL_VIEW_DESC depth_stencil_view_desc(
            is_stereo ? D3D11_DSV_DIMENSION_TEXTURE2DARRAY : D3D11_DSV_DIMENSION_TEXTURE2D,
            DXGI_FORMAT_D16_UNORM
        );
        Holo::CheckResult(
            device->CreateDepthStencilView(
                gfx_depth_stencil.Get(),
                &depth_stencil_view_desc,
                &gfx_depth_stencil_view
            ));
    }
}

// Releases resources associated with a back buffer.
void GfxCamResources::ReleaseResourcesForBackBuffer(const GfxDevResources* dev_resources)
{
    ID3D11DeviceContext* context = dev_resources->GetD3DDeviceContext();

    // Release camera-specific resources.
    gfx_back_buffer.Reset();
    gfx_depth_stencil.Reset();
    gfx_rend_tgt_view.Reset();
    gfx_depth_stencil_view.Reset();

    // Ensure system references to the back buffer are released by clearing the render
    // target from the graphics pipeline state, and then flushing the Direct3D context.
    NativeRenderTargetViewRef null_views[D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT] = 0;
    context->OMSetRenderTargets(ARRAYSIZE(null_views), null_views, nullptr);
    context->Flush();
}

// Gets the view/projection transforms for a holographic camera.
bool GfxCamResources::GetViewProjectionTransform(
    Shared<GfxDevResources> dev_resources,
    const HolographicCameraPose& cam_pose,
    const SpatialCoordinateSystem& coord_system,
    HolographicStereoTransform* view_transform,
    HolographicStereoTransform* proj_transform)
{
    // The system changes the viewport on a per-frame basis for system optimizations.
    auto viewport = cam_pose.Viewport();
    
    gfx_viewport = CD3D11_VIEWPORT(
        viewport.X,
        viewport.Y,
        viewport.Width,
        viewport.Height
    );

    // The projection transform for each frame is provided by the HolographicCameraPose.
    *proj_transform = cam_pose.ProjectionTransform();

    // Get a container object with the view and projection matrices for the given
    // pose in the given coordinate system.
    auto view_transform_container = cam_pose.TryGetViewTransform(coord_system);

    // If TryGetViewTransform returns a null pointer, that means the pose and coordinate
    // system cannot be understood relative to one another; content cannot be rendered
    // in this coordinate system for the duration of the current frame.
    // This usually means that positional tracking is not active for the current frame, in
    // which case it is possible to use a SpatialLocatorAttachedFrameOfReference to render
    // content that is not world-locked instead.
    bool view_transform_acquired = view_transform_container != nullptr;
    if (view_transform_acquired)
    {
        // Otherwise, the set of view transforms can be retrieved.
        *view_transform = view_transform_container.Value();

        dev_resources->GetD3DDeviceContext()->RSSetViewports(1, &gfx_viewport);

        return true;
    }

    return false;
}

void GfxCamResources::CommitDirect3D11DepthBuffer(const HolographicCameraRenderingParameters& rend_params) const
{
    // Direct3D interop APIs are used to provide the buffer to the WinRT API.
    ComPtr<IDXGIResource1> depth_stencil_resource;
    Holo::CheckResult(gfx_depth_stencil.As(&depth_stencil_resource));

    ComPtr<IDXGISurface2> depth_gfxlib_surface;
    Holo::CheckResult(depth_stencil_resource->CreateSubresourceSurface(0, &depth_gfxlib_surface));

    NativeInspectableRef inspectable_surface;
    TODO //Holo::CheckResult(CreateDirect3D11SurfaceFromDXGISurface(depth_gfxlib_surface.Get(), winrt::put_abi(inspectable_surface)));

    // Calling CommitDirect3D11DepthBuffer causes the system to queue Direct3D commands to
    // read the depth buffer. It will then use that information to stabilize the image as
    // the HolographicFrame is presented.
    rend_params.CommitDirect3D11DepthBuffer(inspectable_surface.as<IDirect3DSurface>());
    
}


NAMESPACE_PARALLEL_END
