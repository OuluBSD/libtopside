#pragma once


NAMESPACE_PARALLEL_BEGIN


template <class Holo>
class DeviceResourcesT;


// Manages DirectX device resources that are specific to a holographic camera, such as the
// back buffer, ViewProjection constant buffer, and viewport.
template <class Holo>
class CameraResourcesT
{
public:
	using HoloCam = typename Holo::HoloCam;
	using GfxDevResources = typename Holo::GfxDevResources;
	using HoloCamRendParams = typename Holo::HoloCamRendParams;
	using HoloCamPose = typename Holo::HoloCamPose;
	using SpatialCoordinateSystem = typename Holo::SpatialCoordinateSystem;
	using HoloStereoTransform = typename Holo::HoloStereoTransform;
	using NativeRenderTargetViewRef = typename Holo::NativeRenderTargetViewRef;
	using NativeDepthStencilViewRef = typename Holo::NativeDepthStencilViewRef;
	using NativeTexture2DRef = typename Holo::NativeTexture2DRef;
	
	
    CameraResourcesT(const HoloCam& holocam);

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
    ViewportParams				GetViewport()                       const { return gfx_viewport; }
    LightSampleFD				GetBackBufferDXGIFormat()           const { return gfxlib_fmt; }

    // Render target properties.
    Size GetRenderTargetSize() const { return gfx_rend_tgt_size; }
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
    LightSampleFD							gfxlib_fmt;
    Size									gfx_rend_tgt_size;
    ViewportParams							gfx_viewport;

    // Indicates whether the camera supports stereoscopic rendering.
    bool									is_stereo = false;

    // Pointer to the holographic camera these resources are for.
    HoloCam									holocam = 0;
    
};


NAMESPACE_PARALLEL_END
