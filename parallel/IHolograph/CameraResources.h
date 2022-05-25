#pragma once


NAMESPACE_PARALLEL_BEGIN


namespace DX {

	
class DeviceResources;


// Manages DirectX device resources that are specific to a holographic camera, such as the
// back buffer, ViewProjection constant buffer, and viewport.
class CameraResources
{
public:
    CameraResources(const HoloCam& holocam);

    void CreateResourcesForBackBuffer(
        const GfxDevResources* dev_resources,
        const HoloCamRendParams& cam_params
        );
    void ReleaseResourcesForBackBuffer(
        const GfxDevResources* dev_resources
        );

    bool GetViewProjectionTransform(
        Shared<GfxDevResources> dev_resources,
        const HoloCamPose& cam_pose,
        const SpatialCoordinateSystem& coord_system,
        HoloStereoTransform* view_transform,
        HoloStereoTransform* proj_transform);

    void CommitDirect3D11DepthBuffer(
        const HoloCamRendParams& rend_params) const;

    // Direct3D device resources.
    NativeRenderTargetViewRef	GetBackBufferRenderTargetView()     const { return gfx_rend_tgt_view.Get(); }
    NativeDepthStencilViewRef	GetDepthStencilView()               const { return gfx_depth_stencil_view.Get(); }
    NativeTexture2DRef			GetBackBufferTexture2D()            const { return gfx_back_buffer.Get(); }
    D3D11_VIEWPORT				GetViewport()                       const { return gfx_viewport; }
    DXGI_FORMAT					GetBackBufferDXGIFormat()           const { return gfxlib_fmt; }

    // Render target properties.
    vec2 GetRenderTargetSize() const& { return gfx_rend_tgt_size; }
    bool IsRenderingStereoscopic() const { return is_stereo; }

    // The holographic camera these resources are for.
    const HoloCam& GetHolographicCamera() const { return holocam; }

private:
    // Direct3D rendering objects. Required for 3D.
    NativeRenderTargetViewRef				gfx_rend_tgt_view;
    NativeDepthStencilViewRef				gfx_depth_stencil_view;
    NativeTexture2DRef						gfx_depth_stencil;
    NativeTexture2DRef						gfx_back_buffer;

    // Direct3D rendering properties.
    DXGI_FORMAT								gfxlib_fmt;
    Size									gfx_rend_tgt_size;
    D3D11_VIEWPORT							gfx_viewport;

    // Indicates whether the camera supports stereoscopic rendering.
    bool									is_stereo = false;

    // Pointer to the holographic camera these resources are for.
    HoloCam									holocam = 0;
    
};

}


NAMESPACE_PARALLEL_END
