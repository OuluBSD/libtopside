#pragma once

#if 0

NAMESPACE_PARALLEL_BEGIN


class DeviceResources;


// Manages DirectX device resources that are specific to a holographic camera, such as the
// back buffer, ViewProjection constant buffer, and viewport.
class CameraResources
{
public:
	/*using HolographicCamera = typename Holo::HolographicCamera;
	using GfxDevResources = typename Holo::GfxDevResources;
	using HolographicCameraRenderingParameters = typename Holo::HolographicCameraRenderingParameters;
	using HolographicCameraPose = typename Holo::HolographicCameraPose;
	using SpatialCoordinateSystem = typename Holo::SpatialCoordinateSystem;
	using HolographicStereoTransform = typename Holo::HolographicStereoTransform;
	using NativeRenderTargetViewRef = typename Holo::NativeRenderTargetViewRef;
	using NativeDepthStencilViewRef = typename Holo::NativeDepthStencilViewRef;
	using NativeTexture2DRef = typename Holo::NativeTexture2DRef;*/
	
	
    CameraResources();
	
	void SetCamera( HolographicCamera& holocam);
	
    void CreateResourcesForBackBuffer(
        const DeviceResources* dev_resources,
        const HolographicCameraRenderingParameters& cam_params
        );
    void ReleaseResourcesForBackBuffer(
        const DeviceResources* dev_resources
        );

    bool GetViewProjectionTransform(
        DeviceResources& dev_resources,
        const HolographicCameraPose& cam_pose,
        const SpatialCoordinateSystem& coord_system,
        HolographicStereoTransform* view_transform,
        HolographicStereoTransform* proj_transform);

    void Commitgraphics11DepthBuffer(
        const HolographicCameraRenderingParameters& rend_params) const;

    // graphics device resources.
    NativeRenderTargetViewRef	GetBackBufferRenderTargetView()     const { return gfx_rend_tgt_view; }
    NativeDepthStencilViewRef	GetDepthStencilView()               const { return gfx_depth_stencil_view; }
    NativeTexture2DRef			GetBackBufferTexture2D()            const { return gfx_back_buffer; }
    ViewportParams				GetViewport()                       const { return gfx_viewport; }
    LightSampleFD				GetBackBufferDXGIFormat()           const { return gfxlib_fmt; }

    // Render target properties.
    Size GetRenderTargetSize() const { return gfx_rend_tgt_size; }
    bool IsRenderingStereoscopic() const { return is_stereo; }

    // The holographic camera these resources are for.
    const HolographicCamera& GetHolographicCamera() const { return *holocam; }

private:
    // graphics rendering objects. Required for 3D.
    NativeRenderTargetViewRef				gfx_rend_tgt_view;
    NativeDepthStencilViewRef				gfx_depth_stencil_view;
    NativeTexture2DRef						gfx_depth_stencil;
    NativeTexture2DRef						gfx_back_buffer;

    // graphics rendering properties.
    LightSampleFD							gfxlib_fmt;
    Size									gfx_rend_tgt_size;
    ViewportParams							gfx_viewport;

    // Indicates whether the camera supports stereoscopic rendering.
    bool									is_stereo = false;

    // Pointer to the holographic camera these resources are for.
    HolographicCamera*						holocam = 0;
    
};


NAMESPACE_PARALLEL_END

#endif
