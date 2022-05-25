#include "WinLib.h"


NAMESPACE_PARALLEL_BEGIN


// Constructor for DeviceResources.
GfxDevResources::DeviceResources()
{
    CreateDeviceIndependentResources();
}

// Configures resources that don't depend on the Direct3D device.
void GfxDevResources::CreateDeviceIndependentResources()
{
    // Initialize Direct2D resources.
    D2D1_FACTORY_OPTIONS options{};

#if defined(_DEBUG)
    // If the project is in a debug build, enable Direct2D debugging via SDK Layers.
    options.debugLevel = D2D1_DEBUG_LEVEL_INFORMATION;
#endif

    // Initialize the Direct2D Factory.
    Holo::CheckResult(
        D2D1CreateFactory(
            D2D1_FACTORY_TYPE_SINGLE_THREADED,
            __uuidof(ID2D1Factory2),
            &options,
            &m_d2dFactory
        ));

    // Initialize the DirectWrite Factory.
    Holo::CheckResult(
        DWriteCreateFactory(
            DWRITE_FACTORY_TYPE_SHARED,
            __uuidof(IDWriteFactory2),
            &m_dwriteFactory
        ));

    // Initialize the Windows Imaging Component (WIC) Factory.
    Holo::CheckResult(
        CoCreateInstance(
            CLSID_WICImagingFactory2,
            nullptr,
            CLSCTX_INPROC_SERVER,
            IID_PPV_ARGS(&m_wicFactory)
        ));
}

void GfxDevResources::SetHolographicSpace(HolographicSpace holospace)
{
    // Cache the holographic space. Used to re-initalize during device-lost scenarios.
    m_holospace = holospace;

    InitializeUsingHolographicSpace();
}

void GfxDevResources::InitializeUsingHolographicSpace()
{
    // The holographic space might need to determine which adapter supports
    // holograms, in which case it will specify a non-zero PrimaryAdapterId.
    LUID id =
    {
        m_holospace.PrimaryAdapterId().LowPart,
        m_holospace.PrimaryAdapterId().HighPart
    };

    // When a primary adapter ID is given to the app, the app should find
    // the corresponding DXGI adapter and use it to create Direct3D devices
    // and device contexts. Otherwise, there is no restriction on the DXGI
    // adapter the app can use.
    if ((id.HighPart != 0) || (id.LowPart != 0))
    {
        UINT createFlags = 0;
#ifdef DEBUG
        if (DX::SdkLayersAvailable())
        {
            createFlags |= DXGI_CREATE_FACTORY_DEBUG;
        }
#endif
        // Create the DXGI factory.
        ComPtr<IDXGIFactory1> dxgiFactory;
        Holo::CheckResult(
            CreateDXGIFactory2(
                createFlags,
                IID_PPV_ARGS(&dxgiFactory)
            ));
        ComPtr<IDXGIFactory4> dxgiFactory4;
        Holo::CheckResult(dxgiFactory.As(&dxgiFactory4));

        // Retrieve the adapter specified by the holographic space.
        Holo::CheckResult(
            dxgiFactory4->EnumAdapterByLuid(
                id,
                IID_PPV_ARGS(&m_dxgiAdapter)
            ));
    }
    else
    {
        m_dxgiAdapter.Reset();
    }

    CreateDeviceResources();

    m_holospace.SetDirect3D11Device(m_d3dInteropDevice);
}

// Configures the Direct3D device, and stores handles to it and the device context.
void GfxDevResources::CreateDeviceResources()
{
    // This flag adds support for surfaces with a different color channel ordering
    // than the API default. It is required for compatibility with Direct2D.
    UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

#if defined(_DEBUG)
    if (DX::SdkLayersAvailable())
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

    const D3D_DRIVER_TYPE driverType = m_dxgiAdapter == nullptr ? D3D_DRIVER_TYPE_HARDWARE : D3D_DRIVER_TYPE_UNKNOWN;
    const HRESULT hr = D3D11CreateDevice(
        m_dxgiAdapter.Get(),        // Either nullptr, or the primary adapter determined by Windows Holographic.
        driverType,                 // Create a device using the hardware graphics driver.
        0,                          // Should be 0 unless the driver is D3D_DRIVER_TYPE_SOFTWARE.
        creationFlags,              // Set debug and Direct2D compatibility flags.
        featureLevels,              // List of feature levels this app can support.
        ARRAYSIZE(featureLevels),   // Size of the list above.
        D3D11_SDK_VERSION,          // Always set this to D3D11_SDK_VERSION for Windows Store apps.
        &device,                    // Returns the Direct3D device created.
        &m_d3dFeatureLevel,         // Returns feature level of device created.
        &context                    // Returns the device immediate context.
    );

    if (FAILED(hr))
    {
        // If the initialization fails, fall back to the WARP device.
        // For more information on WARP, see:
        // http://go.microsoft.com/fwlink/?LinkId=286690
        Holo::CheckResult(
            D3D11CreateDevice(
                nullptr,              // Use the default DXGI adapter for WARP.
                D3D_DRIVER_TYPE_WARP, // Create a WARP device instead of a hardware device.
                0,
                creationFlags,
                featureLevels,
                ARRAYSIZE(featureLevels),
                D3D11_SDK_VERSION,
                &device,
                &m_d3dFeatureLevel,
                &context
            ));
    }

    // Store pointers to the Direct3D device and immediate context.
    Holo::CheckResult(device.As(&m_d3dDevice));
    Holo::CheckResult(context.As(&m_d3dContext));

    // Acquire the DXGI interface for the Direct3D device.
    ComPtr<IDXGIDevice3> dxgiDevice;
    Holo::CheckResult(m_d3dDevice.As(&dxgiDevice));

    // Wrap the native device using a WinRT interop object.
    NativeInspectableRef object;
    TODO /*Holo::CheckResult(CreateDirect3D11DeviceFromDXGIDevice(
        dxgiDevice.Get(),
        winrt::put_abi(object)));*/
    m_d3dInteropDevice = object.as<IDirect3DDevice>();

    // Cache the DXGI adapter.
    // This is for the case of no preferred DXGI adapter, or fallback to WARP.
    ComPtr<IDXGIAdapter> dxgiAdapter;
    Holo::CheckResult(dxgiDevice->GetAdapter(&dxgiAdapter));
    Holo::CheckResult(dxgiAdapter.As(&m_dxgiAdapter));

    // Check for device support for the optional feature that allows setting the render target array index from the vertex shader stage.
    D3D11_FEATURE_DATA_D3D11_OPTIONS3 options;
    m_d3dDevice->CheckFeatureSupport(D3D11_FEATURE_D3D11_OPTIONS3, &options, sizeof(options));
    if (options.VPAndRTArrayIndexFromAnyShaderFeedingRasterizer)
    {
        m_supportsVprt = true;
    }
}

// Validates the back buffer for each HolographicCamera and recreates
// resources for back buffers that have changed.
// Locks the set of holographic camera resources until the function exits.
void GfxDevResources::EnsureCameraResources(
    HolographicFrame frame,
    HolographicFramePrediction prediction)
{
    UseHolographicCameraResources<void>([this, frame, prediction](std::map<UINT32, std::unique_ptr<CameraResources>>& cameraResourceMap)
    {
        for (HolographicCameraPose const& cameraPose : prediction.CameraPoses())
        {
            HolographicCameraRenderingParameters renderingParameters = frame.GetRenderingParameters(cameraPose);
            CameraResources* pCameraResources = cameraResourceMap[cameraPose.HolographicCamera().Id()].get();

            pCameraResources->CreateResourcesForBackBuffer(this, renderingParameters);
        }
    });
}

// Prepares to allocate resources and adds resource views for a camera.
// Locks the set of holographic camera resources until the function exits.
void GfxDevResources::AddHolographicCamera(HolographicCamera camera)
{
    UseHolographicCameraResources<void>([this, camera](std::map<UINT32, std::unique_ptr<CameraResources>>& cameraResourceMap)
    {
        cameraResourceMap[camera.Id()] = std::make_unique<CameraResources>(camera);
    });
}

// Deallocates resources for a camera and removes the camera from the set.
// Locks the set of holographic camera resources until the function exits.
void GfxDevResources::RemoveHolographicCamera(HolographicCamera camera)
{
    UseHolographicCameraResources<void>([this, camera](std::map<UINT32, std::unique_ptr<CameraResources>>& cameraResourceMap)
    {
        CameraResources* pCameraResources = cameraResourceMap[camera.Id()].get();

        if (pCameraResources != nullptr)
        {
            pCameraResources->ReleaseResourcesForBackBuffer(this);
            cameraResourceMap.erase(camera.Id());
        }
    });
}

// Recreate all device resources and set them back to the current state.
// Locks the set of holographic camera resources until the function exits.
void GfxDevResources::HandleDeviceLost()
{
    if (m_deviceNotify != nullptr)
    {
        m_deviceNotify->OnDeviceLost();
    }

    UseHolographicCameraResources<void>([this](std::map<UINT32, std::unique_ptr<CameraResources>>& cameraResourceMap)
    {
        for (auto& pair : cameraResourceMap)
        {
            CameraResources* pCameraResources = pair.second.get();
            pCameraResources->ReleaseResourcesForBackBuffer(this);
        }
    });

    InitializeUsingHolographicSpace();

    if (m_deviceNotify != nullptr)
    {
        m_deviceNotify->OnDeviceRestored();
    }
}

// Register our DeviceNotify to be informed on device lost and creation.
void GfxDevResources::RegisterDeviceNotify(GfxDeviceNotify* deviceNotify)
{
    m_deviceNotify = deviceNotify;
}

// Call this method when the app suspends. It provides a hint to the driver that the app
// is entering an idle state and that temporary buffers can be reclaimed for use by other apps.
void GfxDevResources::Trim()
{
    m_d3dContext->ClearState();

    ComPtr<IDXGIDevice3> dxgiDevice;
    Holo::CheckResult(m_d3dDevice.As(&dxgiDevice));
    dxgiDevice->Trim();
}

// Present the contents of the swap chain to the screen.
// Locks the set of holographic camera resources until the function exits.
void GfxDevResources::Present(HolographicFrame frame)
{
    // By default, this API waits for the frame to finish before it returns.
    // Holographic apps should wait for the previous frame to finish before
    // starting work on a new frame. This allows for better results from
    // holographic frame predictions.
    HolographicFramePresentResult presentResult = frame.PresentUsingCurrentPrediction();

    // The PresentUsingCurrentPrediction API will detect when the graphics device
    // changes or becomes invalid. When this happens, it is considered a Direct3D
    // device lost scenario.
    if (presentResult == HolographicFramePresentResult::DeviceRemoved)
    {
        // The Direct3D device, context, and resources should be recreated.
        HandleDeviceLost();
    }
}









using SharedDeviceResources = Shared<GfxDevResources>;
using HolographicSpace = HoloSpace;


void LoadDefaultResources(DeviceResources& dev_res, HolographicSpace& hs, String diff, String spec, String skybox, String lut) {
	hs = std::make_shared<GfxDevResources>();
	
	dev_res.SetHolographicSpace(hs);
	
	const auto pbr_res = std::make_shared<Pbr::Resources>(dev_res.GetD3DDevice());

    NativeShaderResourceViewRef diffuseEnvironmentMap;
    NativeShaderResourceViewRef specularEnvironmentMap;
    NativeShaderResourceViewRef brdlutTexture;
    NativeShaderResourceViewRef skyboxTexture;

    auto resourceLoadingTask = std::async(std::launch::async, [&]
    {
        auto diffuseTextureFuture = DX::LoadDDSTextureAsync(dev_res.GetD3DDevice(), diff);
        auto specularTextureFuture = DX::LoadDDSTextureAsync(dev_res.GetD3DDevice(), spec);
        auto skyboxTextureFuture = DX::LoadDDSTextureAsync(dev_res.GetD3DDevice(), skybox);
        auto brdfLutFileDataFuture = DX::ReadDataAsync(lut);

        diffuseEnvironmentMap = diffuseTextureFuture.get();
        specularEnvironmentMap = specularTextureFuture.get();
        skyboxTexture = skyboxTextureFuture.get();
        std::vector<byte> brdfLutFileData = brdfLutFileDataFuture.get();

        // Read the BRDF Lookup Table used by the PBR system into a DirectX texture.
        brdlutTexture = Pbr::Texture::LoadImage(dev_res.GetD3DDevice(), brdfLutFileData.data(), static_cast<uint32_t>(brdfLutFileData.size()));
    });

    // Launch the loading tasks on another thread and wait for them to complete
    resourceLoadingTask.wait();

    pbr_res->SetBrdfLut(brdlutTexture.Get());
    pbr_res->SetEnvironmentMap(dev_res.GetD3DDeviceContext(), specularEnvironmentMap.Get(), diffuseEnvironmentMap.Get());
}


NAMESPACE_PARALLEL_END
