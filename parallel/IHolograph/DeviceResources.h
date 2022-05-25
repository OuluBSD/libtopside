#pragma once


NAMESPACE_PARALLEL_BEGIN


namespace DX {


// Provides an interface for an application that owns DeviceResources to be notified of the device being lost or created.
struct IDeviceNotify
{
    virtual void OnDeviceLost()     = 0;
    virtual void OnDeviceRestored() = 0;
};

// Creates and manages a Direct3D device and immediate context, Direct2D device and context (for debug), and the holographic swap chain.
template <class Holo>
class DeviceResources
{
	using HoloCam = typename Holo::HoloCam;
	using HoloFrame = typename Holo::HoloFrame;
	using HoloFramePred = typename Holo::HoloFramePred;
	
	
public:
    DeviceResources();

    // Public methods related to Direct3D devices.
    void HandleDeviceLost();
    void RegisterDeviceNotify(IDeviceNotify* dev_notify);
    void Trim();
    void Present(HoloFrame frame);

    // Public methods related to holographic devices.
    void SetHolographicSpace(HoloSpace space);
    void EnsureCameraResources(
        HoloFrame frame,
        HoloFramePred prediction);

    void AddHolographicCamera(HoloCam camera);
    void RemoveHolographicCamera(HoloCam camera);

    // Holographic accessors.
    template<typename RetType, typename LCallback>
    RetType						UseHolographicCameraResources(LCallback const& callback);

    GfxDevice					GetD3DInteropDevice()           const { return gfx_interop_dev;    }

    // D3D accessors.
    NativeGfxDeviceRef          GetD3DDevice()                  const { return gfx_dev.Get();     }
    NativeGfxDeviceContextRef   GetD3DDeviceContext()           const { return gfx_ctx_dev.Get();    }
    D3D_FEATURE_LEVEL			GetDeviceFeatureLevel()         const { return gfx_feature_level;     }
    bool						GetDeviceSupportsVprt()         const { return supports_vprt;        }

    // DXGI acessors.
    NativeGfxLibRef				GetDXGIAdapter()                const { return gfxlib_adapter.Get();   }

    // D2D accessors.
    Native2DLibRef				GetD2DFactory()                 const { return gfx_2d_factory.Get();    }
    NativeHwLibRef				GetDWriteFactory()              const { return gfx_hw_factory.Get(); }
    NativeVrCamLibRef			GetWicImagingFactory()          const { return vr_camlib.Get();    }

private:
    // Private methods related to the Direct3D device, and resources based on that device.
    void CreateDeviceIndependentResources();
    void InitializeUsingHolographicSpace();
    void CreateDeviceResources();

    // Direct3D objects.
    NativeGfxDeviceRef						gfx_dev;
    NativeGfxDeviceContextRef				gfx_ctx_dev;
    NativeGfxLibRef							gfxlib_adapter;

    // Direct3D interop objects.
    GfxDevice								gfx_interop_dev;

    // Direct2D factories.
    Native2DLibRef							gfx_2d_factory;
    NativeHwLibRef							gfx_hw_factory;
    NativeVrCamLibRef						vr_camlib;

    // The holographic space provides a preferred DXGI adapter ID.
    HoloSpace								holospace = 0;

    // Properties of the Direct3D device currently in use.
    D3D_FEATURE_LEVEL						gfx_feature_level = D3D_FEATURE_LEVEL_10_0;

    // The IDeviceNotify can be held directly as it owns the DeviceResources.
    IDeviceNotify*							dev_notify = 0;

    // Whether or not the current Direct3D device supports the optional feature
    // for setting the render target array index from the vertex shader stage.
    bool									supports_vprt = false;

    // Back buffer resources, etc. for attached holographic cameras.
    VectorMap<uint32, One<CameraResources>>	cam_resources;
    Mutex									cam_resources_lock;
    
};


}

// Device-based resources for holographic cameras are stored in a std::map. Access this list by providing a
// callback to this function, and the std::map will be guarded from add and remove
// events until the callback returns. The callback is processed immediately and must
// not contain any nested calls to UseHolographicCameraResources.
// The callback takes a parameter of type ArrayMap<uint32, std::unique_ptr<GfxCamResources>>&
// through which the list of cameras will be accessed.
template<typename RetType, typename LCallback>
RetType GfxDevResources::UseHolographicCameraResources(LCallback const& callback)
{
	TODO
    /*Mutex::Lock guard(cam_resources_lock);
    return callback(cam_resources);*/
}






/*using SharedDeviceResources = Shared<GfxDevResources>;
using HolographicSpace = HoloSpace;*/

void LoadDefaultResources(DeviceResources& dr, HolographicSpace& hs, String diff, String spec, String skybox, String lut);


NAMESPACE_PARALLEL_END
