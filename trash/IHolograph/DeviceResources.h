#pragma once

#if 0

NAMESPACE_PARALLEL_BEGIN


// Provides an interface for an application that owns DeviceResources to be notified of the device being lost or created.
struct DeviceNotify : RTTIBase
{
	RTTI_DECL0(DeviceNotify)
	
    virtual void OnDeviceLost()     = 0;
    virtual void OnDeviceRestored() = 0;
};

// Creates and manages a graphics device and immediate context, Direct2D device and context (for debug), and the holographic swap chain.
class DeviceResources
{
	/*using CameraResources = CameraResources;
	using HolographicCamera = typename Holo::HolographicCamera;
	using HolographicFrame = typename Holo::HolographicFrame;
	using HolographicFramePrediction = typename Holo::HolographicFramePrediction;
	using HolographicSpace = typename Holo::HolographicSpace;
	using GfxDevice = typename Holo::GfxDevice;
	using NativeGfxDeviceRef = typename Holo::NativeGfxDeviceRef;
	using NativeGfxDeviceContextRef = typename Holo::NativeGfxDeviceContextRef;
	using NativeGfxLibRef = typename Holo::NativeGfxLibRef;
	using Native2DLibRef = typename Holo::Native2DLibRef;
	using NativeHwLibRef = typename Holo::NativeHwLibRef;
	using NativeVrCamLibRef = typename Holo::NativeVrCamLibRef;
	using FeatureLevel = typename Holo::FeatureLevel;
	*/
	
public:
    DeviceResources();

    // Public methods related to graphics devices.
    void HandleDeviceLost();
    void RegisterDeviceNotify(DeviceNotify* dev_notify);
    void Trim();
    void Present(HolographicFrame& frame);

    // Public methods related to holographic devices.
    void SetHolographicSpace(HolographicSpace space);
    void EnsureCameraResources(
        HolographicFrame& frame,
        const HolographicFramePrediction& prediction);

    void AddHolographicCamera(HolographicCamera& camera);
    void RemoveHolographicCamera(HolographicCamera& camera);

    // Holographic accessors.
    template<typename LCallback>
    bool						UseHolographicCameraResources(LCallback const& callback);

    const GfxDevice&			GetD3DInteropDevice()           const { return gfx_interop_dev; }

    // D3D accessors.
    NativeGfxDeviceRef          GetD3DDevice()                  const { return gfx_dev; }
    NativeGfxDeviceContextRef   GetD3DDeviceContext()           const { return gfx_ctx_dev; }
    FeatureLevel				GetDeviceFeatureLevel()         const { return gfx_feature_level; }
    bool						GetDeviceSupportsVprt()         const { return supports_vprt; }

    // DXGI acessors.
    NativeGfxLibRef				GetDXGIAdapter()                const { return gfxlib_adapter; }

    // D2D accessors.
    Native2DLibRef				GetD2DFactory()                 const { return gfx_2d_factory; }
    NativeHwLibRef				GetDWriteFactory()              const { return gfx_hw_factory; }
    NativeVrCamLibRef			GetWicImagingFactory()          const { return vr_camlib; }

private:
    // Private methods related to the graphics device, and resources based on that device.
    void CreateDeviceIndependentResources();
    void InitializeUsingHolographicSpace();
    void CreateDeviceResources();

    // graphics objects.
    NativeGfxDeviceRef						gfx_dev;
    NativeGfxDeviceContextRef				gfx_ctx_dev;
    NativeGfxLibRef							gfxlib_adapter;

    // graphics interop objects.
    GfxDevice								gfx_interop_dev;

    // Direct2D factories.
    Native2DLibRef							gfx_2d_factory;
    NativeHwLibRef							gfx_hw_factory;
    NativeVrCamLibRef						vr_camlib;

    // The holographic space provides a preferred DXGI adapter ID.
    HolographicSpace						holospace;

    // Properties of the graphics device currently in use.
    FeatureLevel							gfx_feature_level;

    // The IDeviceNotify can be held directly as it owns the DeviceResources.
    DeviceNotify*							dev_notify = 0;

    // Whether or not the current graphics device supports the optional feature
    // for setting the render target array index from the vertex shader stage.
    bool									supports_vprt = false;

    // Back buffer resources, etc. for attached holographic cameras.
    ArrayMap<uint32, CameraResources>		cam_resources;
    Mutex									cam_resources_lock;
    
};



// Device-based resources for holographic cameras are stored in a std::map. Access this list by providing a
// callback to this function, and the std::map will be guarded from add and remove
// events until the callback returns. The callback is processed immediately and must
// not contain any nested calls to UseHolographicCameraResources.
// The callback takes a parameter of type ArrayMap<uint32, std::unique_ptr<GfxCamResources>>&
// through which the list of cameras will be accessed.
template<typename LCallback>
bool DeviceResources::UseHolographicCameraResources(LCallback const& callback)
{
	Mutex::Lock guard(cam_resources_lock);
	bool ret = false;
    callback(cam_resources, ret);
    return ret;
}




/*using SharedDeviceResources = Shared<GfxDevResources>;
using HolographicSpace = HolographicSpace;*/

/*
void LoadDefaultResources(DeviceResources& dr, HolographicSpace& hs, String diff, String spec, String skybox, String lut);
*/

NAMESPACE_PARALLEL_END

#endif
