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
    void RegisterDeviceNotify(IDeviceNotify* deviceNotify);
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

    GfxDevice					GetD3DInteropDevice()           const { return m_d3dInteropDevice;    }

    // D3D accessors.
    NativeGfxDeviceRef          GetD3DDevice()                  const { return m_d3dDevice.Get();     }
    NativeGfxDeviceContextRef   GetD3DDeviceContext()           const { return m_d3dContext.Get();    }
    D3D_FEATURE_LEVEL			GetDeviceFeatureLevel()         const { return m_d3dFeatureLevel;     }
    bool						GetDeviceSupportsVprt()         const { return m_supportsVprt;        }

    // DXGI acessors.
    NativeGfxLibRef				GetDXGIAdapter()                const { return m_dxgiAdapter.Get();   }

    // D2D accessors.
    Native2DLibRef				GetD2DFactory()                 const { return m_d2dFactory.Get();    }
    NativeHwLibRef				GetDWriteFactory()              const { return m_dwriteFactory.Get(); }
    NativeVrCamLibRef			GetWicImagingFactory()          const { return m_wicFactory.Get();    }

private:
    // Private methods related to the Direct3D device, and resources based on that device.
    void CreateDeviceIndependentResources();
    void InitializeUsingHolographicSpace();
    void CreateDeviceResources();

    // Direct3D objects.
    NativeGfxDeviceRef						m_d3dDevice;
    NativeGfxDeviceContextRef				m_d3dContext;
    NativeGfxLibRef							m_dxgiAdapter;

    // Direct3D interop objects.
    GfxDevice								m_d3dInteropDevice;

    // Direct2D factories.
    Native2DLibRef							m_d2dFactory;
    NativeHwLibRef							m_dwriteFactory;
    NativeVrCamLibRef						m_wicFactory;

    // The holographic space provides a preferred DXGI adapter ID.
    HoloSpace								m_holospace = nullptr;

    // Properties of the Direct3D device currently in use.
    D3D_FEATURE_LEVEL						m_d3dFeatureLevel = D3D_FEATURE_LEVEL_10_0;

    // The IDeviceNotify can be held directly as it owns the DeviceResources.
    IDeviceNotify*							m_deviceNotify = nullptr;

    // Whether or not the current Direct3D device supports the optional feature
    // for setting the render target array index from the vertex shader stage.
    bool									m_supportsVprt = false;

    // Back buffer resources, etc. for attached holographic cameras.
    VectorMap<uint32, One<CameraResources>>	m_cameraResources;
    Mutex									m_cameraResourcesLock;
    
};


}

// Device-based resources for holographic cameras are stored in a std::map. Access this list by providing a
// callback to this function, and the std::map will be guarded from add and remove
// events until the callback returns. The callback is processed immediately and must
// not contain any nested calls to UseHolographicCameraResources.
// The callback takes a parameter of type std::map<UINT32, std::unique_ptr<GfxCamResources>>&
// through which the list of cameras will be accessed.
template<typename RetType, typename LCallback>
RetType GfxDevResources::UseHolographicCameraResources(LCallback const& callback)
{
	TODO
    /*Mutex::Lock guard(m_cameraResourcesLock);
    return callback(m_cameraResources);*/
}






/*using SharedDeviceResources = Shared<GfxDevResources>;
using HolographicSpace = HoloSpace;*/

void LoadDefaultResources(DeviceResources& dr, HolographicSpace& hs, String diff, String spec, String skybox, String lut);


NAMESPACE_PARALLEL_END
