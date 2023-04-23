#include "IHal.h"

#if defined flagUWP && defined flagDX12

#ifndef WINAPI_FAMILY
	#define WINAPI_FAMILY WINAPI_FAMILY_APP
#endif

#include <winapifamily.h>
#include <Objbase.h>

#include <Guiddef.h>
#include <wrl.h>
#include <wrl/client.h>
#include <d3d11.h>
#include <d3d11_3.h>
#include <d3d11_4.h>
#include <DirectXMath.h>
#include <DirectXColors.h>

#include <stdint.h>

#include <d2d1_2.h>
#include <d3d11_4.h>
#include <DirectXColors.h>
#include <dwrite_2.h>
#include <wincodec.h>
#include <WindowsNumerics.h>
#include <Windows.Graphics.Directx.Direct3D11.Interop.h>

#include <wrl\client.h>

#if WINAPI_FAMILY != WINAPI_FAMILY_APP
	#error Wrong WINAPI_FAMILY
#endif

#ifndef __WRL_NO_DEFAULT_LIB__
	#error Not defined: __WRL_NO_DEFAULT_LIB__
#endif


#include <ppl.h>
#include <winrt\Windows.ApplicationModel.Activation.h>
#include <winrt\Windows.ApplicationModel.Core.h>
#include <winrt\Windows.Devices.h>
#include <winrt\Windows.Devices.haptics.h>
#include <winrt\Windows.Foundation.h>
#include <winrt\Windows.Foundation.Collections.h>
#include <winrt\Windows.Gaming.Input.h>
#include <winrt\Windows.Graphics.Display.h>
#include <winrt\Windows.Graphics.Holographic.h>
#include <winrt\Windows.Perception.People.h>
#include <winrt\Windows.Perception.Spatial.h>
#include <winrt\Windows.Storage.h>
#include <winrt\Windows.Storage.Streams.h>
#include <winrt\Windows.UI.Core.h>
#include <winrt\Windows.UI.Input.Spatial.h>



NAMESPACE_PARALLEL_BEGIN


using namespace D2D1;
using namespace Microsoft::WRL;
using namespace winrt::Windows::Graphics::DirectX::Direct3D11;
using namespace winrt::Windows::Graphics::Display;
using namespace winrt::Windows::Graphics::Holographic;



struct HalHolo::NativeContextBase {
	inline static NativeContextBase* latest = 0;
	
    // Direct2D factories.
    Microsoft::WRL::ComPtr<ID2D1Factory2>                   m_d2dFactory;
    Microsoft::WRL::ComPtr<IDWriteFactory2>                 m_dwriteFactory;
    Microsoft::WRL::ComPtr<IWICImagingFactory2>             m_wicFactory;

    // The holographic space provides a preferred DXGI adapter ID.
    winrt::Windows::Graphics::Holographic::HolographicSpace m_holographicSpace = nullptr;

	
};



struct HalHolo::NativeD12VideoSinkDevice {
	
    // Direct3D objects.
    Microsoft::WRL::ComPtr<ID3D11Device4>                   m_d3dDevice;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext3>            m_d3dContext;
    Microsoft::WRL::ComPtr<IDXGIAdapter3>                   m_dxgiAdapter;

    // Direct3D interop objects.
    winrt::Windows::Graphics::DirectX::Direct3D11::IDirect3DDevice m_d3dInteropDevice;

    // Properties of the Direct3D device currently in use.
    D3D_FEATURE_LEVEL                                       m_d3dFeatureLevel = D3D_FEATURE_LEVEL_10_0;

    // Whether or not the current Direct3D device supports the optional feature
    // for setting the render target array index from the vertex shader stage.
    bool                                                    m_supportsVprt = false;

};



struct HalHolo::NativeEventsBase {
	
};







#if defined(_DEBUG)
// Check for SDK Layer support.
inline bool SdkLayersAvailable()
{
    HRESULT hr = D3D11CreateDevice(
        nullptr,
        D3D_DRIVER_TYPE_NULL,       // There is no need to create a real hardware device.
        0,
        D3D11_CREATE_DEVICE_DEBUG,  // Check for the SDK layers.
        nullptr,                    // Any feature level will do.
        0,
        D3D11_SDK_VERSION,          // Always set this to D3D11_SDK_VERSION for Windows Store apps.
        nullptr,                    // No need to keep the D3D device reference.
        nullptr,                    // No need to know the feature level.
        nullptr                     // No need to keep the D3D device context reference.
        );

    return SUCCEEDED(hr);
}
#endif









bool HalHolo::ContextBase_Create(NativeContextBase*& dev) {
	if (NativeContextBase::latest)
		return false;
	
	dev = new NativeContextBase;
	
	NativeContextBase::latest = dev;
	
	return true;
}

void HalHolo::ContextBase_Destroy(NativeContextBase*& dev) {
	ASSERT(NativeContextBase::latest == dev);
	NativeContextBase::latest = 0;
	
	delete dev;
}

bool HalHolo::ContextBase_Initialize(NativeContextBase& dev, AtomBase& a, const Script::WorldState& ws) {
	// Initialize Direct2D resources.
    D2D1_FACTORY_OPTIONS options{};

#if defined(_DEBUG)
    // If the project is in a debug build, enable Direct2D debugging via SDK Layers.
    options.debugLevel = D2D1_DEBUG_LEVEL_INFORMATION;
#endif
	
	try {
	    // Initialize the Direct2D Factory.
	    winrt::check_hresult(
	        D2D1CreateFactory(
	            D2D1_FACTORY_TYPE_SINGLE_THREADED,
	            __uuidof(ID2D1Factory2),
	            &options,
	            &dev.m_d2dFactory
	        ));
	
	    // Initialize the DirectWrite Factory.
	    winrt::check_hresult(
	        DWriteCreateFactory(
	            DWRITE_FACTORY_TYPE_SHARED,
	            __uuidof(IDWriteFactory2),
	            &dev.m_dwriteFactory
	        ));
	
	    // Initialize the Windows Imaging Component (WIC) Factory.
	    winrt::check_hresult(
	        CoCreateInstance(
	            CLSID_WICImagingFactory2,
	            nullptr,
	            CLSCTX_INPROC_SERVER,
	            IID_PPV_ARGS(&dev.m_wicFactory)
	        ));
	}
	catch (winrt::hresult_error e) {
		LOG("HalHolo::ContextBase_Initialize: error: " << WString(e.message().c_str()).ToString());
		return false;
	}
    
    return true;
}

bool HalHolo::ContextBase_PostInitialize(NativeContextBase& dev, AtomBase& a) {
	
    return true;
}

bool HalHolo::ContextBase_Start(NativeContextBase& dev, AtomBase& a) {
	ASSERT(dev.m_holographicSpace);
	if (!dev.m_holographicSpace)
		return false;
	
    return true;
}

void HalHolo::ContextBase_Stop(NativeContextBase& dev, AtomBase& a) {
	TODO
}

void HalHolo::ContextBase_Uninitialize(NativeContextBase& dev, AtomBase& a) {
	TODO
}

bool HalHolo::ContextBase_Send(NativeContextBase& dev, AtomBase& a, RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) {
	TODO
}

void HalHolo::ContextBase_Visit(NativeContextBase& dev, AtomBase& a, RuntimeVisitor& vis) {
	TODO
}

bool HalHolo::ContextBase_Recv(NativeContextBase& dev, AtomBase& a, int src, const Packet& p) {
	TODO
}

void HalHolo::ContextBase_Finalize(NativeContextBase& dev, AtomBase& a, RealtimeSourceConfig& cfg) {
	TODO
}

void HalHolo::ContextBase_Update(NativeContextBase& dev, AtomBase& a, double dt) {
	TODO
}

bool HalHolo::ContextBase_IsReady(NativeContextBase& dev, AtomBase& a, PacketIO& io) {
	TODO
}

bool HalHolo::ContextBase_AttachContext(NativeContextBase& dev, AtomBase& a, AtomBase& other) {
	if (other.GetDependency()) {
		LOG("HalHolo::ContextBase_AttachContext: atom already has dependency");
		return false;
	}
	other.SetDependency(&a);
	return true;
}

void HalHolo::ContextBase_DetachContext(NativeContextBase& dev, AtomBase& a, AtomBase& other) {
	if (other.GetDependency() == &a)
		other.SetDependency(0);
}




void D12VideoSinkDevice_CreateDeviceResources(HalHolo::NativeD12VideoSinkDevice& dev);

bool HalHolo::D12VideoSinkDevice_Create(NativeD12VideoSinkDevice*& dev) {
	dev = new NativeD12VideoSinkDevice;
	return true;
}

void HalHolo::D12VideoSinkDevice_Destroy(NativeD12VideoSinkDevice*& dev) {
	delete dev;
}

bool HalHolo::D12VideoSinkDevice_Initialize(NativeD12VideoSinkDevice& dev, AtomBase& a, const Script::WorldState& ws) {
	if (!NativeContextBase::latest) {
		LOG("D12VideoSinkDevice_Initialize: error: no context");
		return false;
	}
	NativeContextBase& ctx = *NativeContextBase::latest;
	if (!ctx.m_holographicSpace) {
		LOG("HalHolo::D12VideoSinkDevice_Initialize: error: no holographic space in context");
		return false;
	}
	
	try {
		// The holographic space might need to determine which adapter supports
	    // holograms, in which case it will specify a non-zero PrimaryAdapterId.
	    LUID id =
	    {
	        ctx.m_holographicSpace.PrimaryAdapterId().LowPart,
	        ctx.m_holographicSpace.PrimaryAdapterId().HighPart
	    };
	
	    // When a primary adapter ID is given to the app, the app should find
	    // the corresponding DXGI adapter and use it to create Direct3D devices
	    // and device contexts. Otherwise, there is no restriction on the DXGI
	    // adapter the app can use.
	    if ((id.HighPart != 0) || (id.LowPart != 0))
	    {
	        UINT createFlags = 0;
	#ifdef DEBUG
	        if (SdkLayersAvailable())
	        {
	            createFlags |= DXGI_CREATE_FACTORY_DEBUG;
	        }
	#endif
	        // Create the DXGI factory.
	        ComPtr<IDXGIFactory1> dxgiFactory;
	        winrt::check_hresult(
	            CreateDXGIFactory2(
	                createFlags,
	                IID_PPV_ARGS(&dxgiFactory)
	            ));
	        ComPtr<IDXGIFactory4> dxgiFactory4;
	        winrt::check_hresult(dxgiFactory.As(&dxgiFactory4));
	
	        // Retrieve the adapter specified by the holographic space.
	        winrt::check_hresult(
	            dxgiFactory4->EnumAdapterByLuid(
	                id,
	                IID_PPV_ARGS(&dev.m_dxgiAdapter)
	            ));
	    }
	    else
	    {
	        dev.m_dxgiAdapter.Reset();
	    }
	
	    D12VideoSinkDevice_CreateDeviceResources(dev);
	
	    ctx.m_holographicSpace.SetDirect3D11Device(dev.m_d3dInteropDevice);
	}
	catch (winrt::hresult_error e) {
		LOG("HalHolo::D12VideoSinkDevice_Initialize: error: " << WString(e.message().c_str()).ToString());
		return false;
	}
	
	TODO
	
	return true;
}

// Configures the Direct3D device, and stores handles to it and the device context.
void D12VideoSinkDevice_CreateDeviceResources(HalHolo::NativeD12VideoSinkDevice& dev)
{
    // This flag adds support for surfaces with a different color channel ordering
    // than the API default. It is required for compatibility with Direct2D.
    UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

#if defined(_DEBUG)
    if (SdkLayersAvailable())
    {
        // If the project is in a debug build, enable debugging via SDK Layers with this flag.
        creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
    }
#endif

    // This array defines the set of DirectX hardware feature levels this app will support.
    // Note the ordering should be preserved.
    // Note that HoloLens supports feature level 11.1. The HoloLens emulator is also capable
    // of running on graphics cards starting with feature level 10.0.
    D3D_FEATURE_LEVEL featureLevels[] =
    {
        D3D_FEATURE_LEVEL_12_1,
        D3D_FEATURE_LEVEL_12_0,
        D3D_FEATURE_LEVEL_11_1,
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0
    };

    // Create the Direct3D 11 API device object and a corresponding context.
    ComPtr<ID3D11Device> device;
    ComPtr<ID3D11DeviceContext> context;

    const D3D_DRIVER_TYPE driverType = dev.m_dxgiAdapter == nullptr ? D3D_DRIVER_TYPE_HARDWARE : D3D_DRIVER_TYPE_UNKNOWN;
    const HRESULT hr = D3D11CreateDevice(
        dev.m_dxgiAdapter.Get(),    // Either nullptr, or the primary adapter determined by Windows Holographic.
        driverType,                 // Create a device using the hardware graphics driver.
        0,                          // Should be 0 unless the driver is D3D_DRIVER_TYPE_SOFTWARE.
        creationFlags,              // Set debug and Direct2D compatibility flags.
        featureLevels,              // List of feature levels this app can support.
        ARRAYSIZE(featureLevels),   // Size of the list above.
        D3D11_SDK_VERSION,          // Always set this to D3D11_SDK_VERSION for Windows Store apps.
        &device,                    // Returns the Direct3D device created.
        &dev.m_d3dFeatureLevel,     // Returns feature level of device created.
        &context                    // Returns the device immediate context.
    );

    if (FAILED(hr))
    {
        // If the initialization fails, fall back to the WARP device.
        // For more information on WARP, see:
        // http://go.microsoft.com/fwlink/?LinkId=286690
        winrt::check_hresult(
            D3D11CreateDevice(
                nullptr,              // Use the default DXGI adapter for WARP.
                D3D_DRIVER_TYPE_WARP, // Create a WARP device instead of a hardware device.
                0,
                creationFlags,
                featureLevels,
                ARRAYSIZE(featureLevels),
                D3D11_SDK_VERSION,
                &device,
                &dev.m_d3dFeatureLevel,
                &context
            ));
    }

    // Store pointers to the Direct3D device and immediate context.
    winrt::check_hresult(device.As(&dev.m_d3dDevice));
    winrt::check_hresult(context.As(&dev.m_d3dContext));

    // Acquire the DXGI interface for the Direct3D device.
    ComPtr<IDXGIDevice3> dxgiDevice;
    winrt::check_hresult(dev.m_d3dDevice.As(&dxgiDevice));

    // Wrap the native device using a WinRT interop object.
    winrt::com_ptr<::IInspectable> object;
    winrt::check_hresult(CreateDirect3D11DeviceFromDXGIDevice(
        dxgiDevice.Get(),
        (IInspectable**)winrt::put_abi(object)));
    dev.m_d3dInteropDevice = object.as<IDirect3DDevice>();

    // Cache the DXGI adapter.
    // This is for the case of no preferred DXGI adapter, or fallback to WARP.
    ComPtr<IDXGIAdapter> dxgiAdapter;
    winrt::check_hresult(dxgiDevice->GetAdapter(&dxgiAdapter));
    winrt::check_hresult(dxgiAdapter.As(&dev.m_dxgiAdapter));

    // Check for device support for the optional feature that allows setting the render target array index from the vertex shader stage.
    D3D11_FEATURE_DATA_D3D11_OPTIONS3 options;
    dev.m_d3dDevice->CheckFeatureSupport(D3D11_FEATURE_D3D11_OPTIONS3, &options, sizeof(options));
    if (options.VPAndRTArrayIndexFromAnyShaderFeedingRasterizer) {
        dev.m_supportsVprt = true;
    }
}

bool HalHolo::D12VideoSinkDevice_PostInitialize(NativeD12VideoSinkDevice& dev, AtomBase& a) {
	TODO
}

bool HalHolo::D12VideoSinkDevice_Start(NativeD12VideoSinkDevice& dev, AtomBase& a) {
	TODO
}

void HalHolo::D12VideoSinkDevice_Stop(NativeD12VideoSinkDevice& dev, AtomBase& a) {
	TODO
}

void HalHolo::D12VideoSinkDevice_Uninitialize(NativeD12VideoSinkDevice& dev, AtomBase& a) {
	TODO
}

bool HalHolo::D12VideoSinkDevice_Send(NativeD12VideoSinkDevice& dev, AtomBase& a, RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) {
	TODO
}

void HalHolo::D12VideoSinkDevice_Visit(NativeD12VideoSinkDevice& dev, AtomBase& a, RuntimeVisitor& vis) {
	TODO
}

bool HalHolo::D12VideoSinkDevice_Recv(NativeD12VideoSinkDevice& dev, AtomBase& a, int src, const Packet& p) {
	TODO
}

void HalHolo::D12VideoSinkDevice_Finalize(NativeD12VideoSinkDevice& dev, AtomBase& a, RealtimeSourceConfig& cfg) {
	TODO
}

void HalHolo::D12VideoSinkDevice_Update(NativeD12VideoSinkDevice& dev, AtomBase& a, double dt) {
	TODO
}

bool HalHolo::D12VideoSinkDevice_IsReady(NativeD12VideoSinkDevice& dev, AtomBase& a, PacketIO& io) {
	TODO
}

bool HalHolo::D12VideoSinkDevice_AttachContext(NativeD12VideoSinkDevice& dev, AtomBase& a, AtomBase& other) {
	TODO
}

void HalHolo::D12VideoSinkDevice_DetachContext(NativeD12VideoSinkDevice& dev, AtomBase& a, AtomBase& other) {
	TODO
}




bool HalHolo::EventsBase_Create(NativeEventsBase*& dev) {
	dev = new NativeEventsBase;
	return true;
}

void HalHolo::EventsBase_Destroy(NativeEventsBase*& dev) {
	delete dev;
}

bool HalHolo::EventsBase_Initialize(NativeEventsBase& dev, AtomBase& a, const Script::WorldState& ws) {
	LOG("HalHolo::EventsBase_Initialize: TODO");
	return true;
}

bool HalHolo::EventsBase_PostInitialize(NativeEventsBase& dev, AtomBase& a) {
	return true;
}

bool HalHolo::EventsBase_Start(NativeEventsBase& dev, AtomBase& a) {
	return true;
}

void HalHolo::EventsBase_Stop(NativeEventsBase& dev, AtomBase& a) {
	TODO
}

void HalHolo::EventsBase_Uninitialize(NativeEventsBase& dev, AtomBase& a) {
	TODO
}

bool HalHolo::EventsBase_Send(NativeEventsBase& dev, AtomBase& a, RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) {
	TODO
}

void HalHolo::EventsBase_Visit(NativeEventsBase& dev, AtomBase& a, RuntimeVisitor& vis) {
	TODO
}

bool HalHolo::EventsBase_Recv(NativeEventsBase& dev, AtomBase& a, int src, const Packet& p) {
	TODO
}

void HalHolo::EventsBase_Finalize(NativeEventsBase& dev, AtomBase& a, RealtimeSourceConfig& cfg) {
	TODO
}

void HalHolo::EventsBase_Update(NativeEventsBase& dev, AtomBase& a, double dt) {
	TODO
}

bool HalHolo::EventsBase_IsReady(NativeEventsBase& dev, AtomBase& a, PacketIO& io) {
	TODO
}

bool HalHolo::EventsBase_AttachContext(NativeEventsBase& dev, AtomBase& a, AtomBase& other) {
	TODO
}

void HalHolo::EventsBase_DetachContext(NativeEventsBase& dev, AtomBase& a, AtomBase& other) {
	TODO
}



NAMESPACE_PARALLEL_END

#endif
