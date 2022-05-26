#include "IHolograph.h"


NAMESPACE_PARALLEL_BEGIN


// Constructor for DeviceResources.
template <class Holo>
DeviceResourcesT::DeviceResources()
{
	gfx_feature_level = Holo::GetDefaultFeatureLevel();
    CreateDeviceIndependentResources();
}

// Configures resources that don't depend on the Direct3D device.
template <class Holo>
void DeviceResourcesT::CreateDeviceIndependentResources()
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
            &gfx_2d_factory
        ));

    // Initialize the DirectWrite Factory.
    Holo::CheckResult(
        DWriteCreateFactory(
            DWRITE_FACTORY_TYPE_SHARED,
            __uuidof(IDWriteFactory2),
            &gfx_hw_factory
        ));

    // Initialize the Windows Imaging Component (WIC) Factory.
    Holo::CheckResult(
        CoCreateInstance(
            CLSID_WICImagingFactory2,
            nullptr,
            CLSCTX_INPROC_SERVER,
            IID_PPV_ARGS(&vr_camlib)
        ));
}

template <class Holo>
void DeviceResourcesT::SetHolographicSpace(HolographicSpace holospace)
{
    // Cache the holographic space. Used to re-initalize during device-lost scenarios.
    holospace = holospace;

    InitializeUsingHolographicSpace();
}

template <class Holo>
void DeviceResourcesT::InitializeUsingHolographicSpace()
{
    // The holographic space might need to determine which adapter supports
    // holograms, in which case it will specify a non-zero PrimaryAdapterId.
    LUID id =
    {
        holospace.PrimaryAdapterId().LowPart,
        holospace.PrimaryAdapterId().HighPart
    };

    // When a primary adapter ID is given to the app, the app should find
    // the corresponding DXGI adapter and use it to create Direct3D devices
    // and device contexts. Otherwise, there is no restriction on the DXGI
    // adapter the app can use.
    if ((id.HighPart != 0) || (id.LowPart != 0))
    {
        uint32 create_flags = 0;
#ifdef DEBUG
        if (DX::SdkLayersAvailable())
        {
            create_flags |= DXGI_CREATE_FACTORY_DEBUG;
        }
#endif
        // Create the DXGI factory.
        ComPtr<IDXGIFactory1> gfxlib_factory;
        Holo::CheckResult(
            CreateDXGIFactory2(
                create_flags,
                IID_PPV_ARGS(&gfxlib_factory)
            ));
        ComPtr<IDXGIFactory4> gfxlib_factory4;
        Holo::CheckResult(gfxlib_factory.As(&gfxlib_factory4));

        // Retrieve the adapter specified by the holographic space.
        Holo::CheckResult(
            gfxlib_factory4->EnumAdapterByLuid(
                id,
                IID_PPV_ARGS(&gfxlib_adapter)
            ));
    }
    else
    {
        gfxlib_adapter.Reset();
    }

    CreateDeviceResources();

    holospace.SetDirect3D11Device(gfx_interop_dev);
}

// Configures the Direct3D device, and stores handles to it and the device context.
template <class Holo>
void DeviceResourcesT::CreateDeviceResources()
{
    // This flag adds support for surfaces with a different color channel ordering
    // than the API default. It is required for compatibility with Direct2D.
    uint32 creation_flags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

#if defined(_DEBUG)
    if (DX::SdkLayersAvailable())
    {
        // If the project is in a debug build, enable debugging via SDK Layers with this flag.
        creation_flags |= D3D11_CREATE_DEVICE_DEBUG;
    }
#endif

    // This array defines the set of DirectX hardware feature levels this app will support.
    // Note the ordering should be preserved.
    // Note that HoloLens supports feature level 11.1. The HoloLens emulator is also capable
    // of running on graphics cards starting with feature level 10.0.
    D3D_FEATURE_LEVEL feature_levels[] =
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

    const D3D_DRIVER_TYPE driver_type = gfxlib_adapter == nullptr ? D3D_DRIVER_TYPE_HARDWARE : D3D_DRIVER_TYPE_UNKNOWN;
    const HRESULT hr = D3D11CreateDevice(
        gfxlib_adapter.Get(),       // Either nullptr, or the primary adapter determined by Windows Holographic.
        driver_type,                // Create a device using the hardware graphics driver.
        0,                          // Should be 0 unless the driver is D3D_DRIVER_TYPE_SOFTWARE.
        creation_flags,             // Set debug and Direct2D compatibility flags.
        feature_levels,             // List of feature levels this app can support.
        ARRAYSIZE(feature_levels),  // Size of the list above.
        D3D11_SDK_VERSION,          // Always set this to D3D11_SDK_VERSION for Windows Store apps.
        &device,                    // Returns the Direct3D device created.
        &gfx_feature_level,         // Returns feature level of device created.
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
                creation_flags,
                feature_levels,
                ARRAYSIZE(feature_levels),
                D3D11_SDK_VERSION,
                &device,
                &gfx_feature_level,
                &context
            ));
    }

    // Store pointers to the Direct3D device and immediate context.
    Holo::CheckResult(device.As(&gfx_dev));
    Holo::CheckResult(context.As(&gfx_ctx_dev));

    // Acquire the DXGI interface for the Direct3D device.
    ComPtr<IDXGIDevice3> gfxlib_dev;
    Holo::CheckResult(gfx_dev.As(&gfxlib_dev));

    // Wrap the native device using a WinRT interop object.
    NativeInspectableRef object;
    TODO /*Holo::CheckResult(CreateDirect3D11DeviceFromDXGIDevice(
        gfxlib_dev.Get(),
        winrt::put_abi(object)));*/
    gfx_interop_dev = object.as<IDirect3DDevice>();

    // Cache the DXGI adapter.
    // This is for the case of no preferred DXGI adapter, or fallback to WARP.
    ComPtr<IDXGIAdapter> gfxlib_adapter;
    Holo::CheckResult(gfxlib_dev->GetAdapter(&gfxlib_adapter));
    Holo::CheckResult(gfxlib_adapter.As(&gfxlib_adapter));

    // Check for device support for the optional feature that allows setting the render target array index from the vertex shader stage.
    D3D11_FEATURE_DATA_D3D11_OPTIONS3 options;
    gfx_dev->CheckFeatureSupport(D3D11_FEATURE_D3D11_OPTIONS3, &options, sizeof(options));
    if (options.VPAndRTArrayIndexFromAnyShaderFeedingRasterizer) {
        supports_vprt = true;
    }
}

// Validates the back buffer for each HolographicCamera and recreates
// resources for back buffers that have changed.
// Locks the set of holographic camera resources until the function exits.
template <class Holo>
void DeviceResourcesT::EnsureCameraResources(
    HolographicFrame frame,
    HolographicFramePrediction prediction)
{
    UseHolographicCameraResources<void>([this, frame, prediction](ArrayMap<uint32, CameraResources>& camera_resource_map)
    {
        for (HolographicCameraPose const& cam_pose : prediction.CameraPoses())
        {
            HolographicCameraRenderingParameters rend_params = frame.GetRenderingParameters(cam_pose);
            CameraResources* cam_resources = camera_resource_map[cam_pose.HolographicCamera().Id()].get();

            cam_resources->CreateResourcesForBackBuffer(this, rend_params);
        }
    });
}

// Prepares to allocate resources and adds resource views for a camera.
// Locks the set of holographic camera resources until the function exits.
template <class Holo>
void DeviceResourcesT::AddHolographicCamera(HolographicCamera camera)
{
    UseHolographicCameraResources<void>([this, camera](ArrayMap<uint32, CameraResources>& camera_resource_map)
    {
        camera_resource_map[camera.Id()] = std::make_unique<CameraResources>(camera);
    });
}

// Deallocates resources for a camera and removes the camera from the set.
// Locks the set of holographic camera resources until the function exits.
template <class Holo>
void DeviceResourcesT::RemoveHolographicCamera(HolographicCamera camera)
{
    UseHolographicCameraResources<void>([this, camera](ArrayMap<uint32, CameraResources>& camera_resource_map)
    {
        CameraResources* cam_resources = camera_resource_map[camera.Id()].get();

        if (cam_resources != nullptr)
        {
            cam_resources->ReleaseResourcesForBackBuffer(this);
            camera_resource_map.erase(camera.Id());
        }
    });
}

// Recreate all device resources and set them back to the current state.
// Locks the set of holographic camera resources until the function exits.
template <class Holo>
void DeviceResourcesT::HandleDeviceLost()
{
    if (dev_notify != nullptr)
    {
        dev_notify->OnDeviceLost();
    }

    UseHolographicCameraResources<void>([this](ArrayMap<uint32, CameraResources>& camera_resource_map)
    {
        for (auto& pair : camera_resource_map)
        {
            CameraResources* cam_resources = pair.second.get();
            cam_resources->ReleaseResourcesForBackBuffer(this);
        }
    });

    InitializeUsingHolographicSpace();

    if (dev_notify != nullptr)
    {
        dev_notify->OnDeviceRestored();
    }
}

// Register our DeviceNotify to be informed on device lost and creation.
template <class Holo>
void DeviceResourcesT::RegisterDeviceNotify(GfxDeviceNotify* dev_notify)
{
    this->dev_notify = dev_notify;
}

// Call this method when the app suspends. It provides a hint to the driver that the app
// is entering an idle state and that temporary buffers can be reclaimed for use by other apps.
template <class Holo>
void DeviceResourcesT::Trim()
{
    gfx_ctx_dev->ClearState();

    ComPtr<IDXGIDevice3> gfxlib_dev;
    Holo::CheckResult(gfx_dev.As(&gfxlib_dev));
    gfxlib_dev->Trim();
}

// Present the contents of the swap chain to the screen.
// Locks the set of holographic camera resources until the function exits.
template <class Holo>
void DeviceResourcesT::Present(HolographicFrame frame)
{
    // By default, this API waits for the frame to finish before it returns.
    // Holographic apps should wait for the previous frame to finish before
    // starting work on a new frame. This allows for better results from
    // holographic frame predictions.
    HolographicFramePresentResult present_result = frame.PresentUsingCurrentPrediction();

    // The PresentUsingCurrentPrediction API will detect when the graphics device
    // changes or becomes invalid. When this happens, it is considered a Direct3D
    // device lost scenario.
    if (present_result == HolographicFramePresentResult::DeviceRemoved)
    {
        // The Direct3D device, context, and resources should be recreated.
        HandleDeviceLost();
    }
}









using SharedDeviceResources = Shared<GfxDevResources>;
using HolographicSpace = HoloSpace;


/*
template <class Holo>
void LoadDefaultResources(DeviceResources& dev_res, HolographicSpace& hs, String diff, String spec, String skybox, String lut) {
	hs = MakeShared<GfxDevResources>();
	
	dev_res.SetHolographicSpace(hs);
	
	const auto pbr_res = MakeShared<Pbr::Resources>(dev_res.GetD3DDevice());

    NativeShaderResourceViewRef diffuse_env_map;
    NativeShaderResourceViewRef specular_env_map;
    NativeShaderResourceViewRef brdf_lut_tex;
    NativeShaderResourceViewRef skybox_tex;

    auto resource_loading_task = std::async(std::launch::async, [&]
    {
        auto diffuse_texture_future = DX::LoadDDSTextureAsync(dev_res.GetD3DDevice(), diff);
        auto specular_texture_future = DX::LoadDDSTextureAsync(dev_res.GetD3DDevice(), spec);
        auto skybox_texture_future = DX::LoadDDSTextureAsync(dev_res.GetD3DDevice(), skybox);
        auto brdf_lut_file_data_future = DX::ReadDataAsync(lut);

        diffuse_env_map = diffuse_texture_future.get();
        specular_env_map = specular_texture_future.get();
        skybox_tex = skybox_texture_future.get();
        Vector<byte> brdf_lut_file_data = brdf_lut_file_data_future.get();

        // Read the BRDF Lookup Table used by the PBR system into a DirectX texture.
        brdf_lut_tex = Pbr::Texture::LoadImage(dev_res.GetD3DDevice(), brdf_lut_file_data.data(), static_cast<uint32>(brdf_lut_file_data.size()));
    });

    // Launch the loading tasks on another thread and wait for them to complete
    resource_loading_task.wait();

    pbr_res->SetBrdfLut(brdf_lut_tex.Get());
    pbr_res->SetEnvironmentMap(dev_res.GetD3DDeviceContext(), specular_env_map.Get(), diffuse_env_map.Get());
}
*/


NAMESPACE_PARALLEL_END
