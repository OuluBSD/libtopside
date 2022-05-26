#ifndef _IHolograph_Dx_h_
#define _IHolograph_Dx_h_


#define WIN32_LEAN_AND_MEAN

#include <memory>
#include <future>
#include <tuple>
#include <mutex>
#include <algorithm>
#include <robuffer.h>

#include <array>
#include <optional>
#include <future>
#include <map>
#include <unordered_set>
#include <mutex>
#include <vector>
#include <tuple>
#include <sstream>
#include <numeric>

#define _USE_MATH_DEFINES
#include <cmath>

#include <stdint.h>

#include <d2d1_2.h>
#include <d3d11_4.h>
#include <DirectXColors.h>
#include <dwrite_2.h>
#include <wincodec.h>
#include <WindowsNumerics.h>
#include <Windows.Graphics.Directx.Direct3D11.Interop.h>

#include <wrl\client.h>
#include <ppl.h>


#pragma comment(lib, "windowsapp")
#pragma comment(lib, "ole32")
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>

#include <winrt/Windows.ApplicationModel.Activation.h>
#include <winrt/Windows.ApplicationModel.Core.h>
#include <winrt/Windows.Devices.h>
#include <winrt/Windows.Devices.haptics.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.Gaming.Input.h>
#include <winrt/Windows.Graphics.Display.h>
#include <winrt/Windows.Graphics.Holographic.h>
#include <winrt/Windows.Perception.People.h>
#include <winrt/Windows.Perception.Spatial.h>
#include <winrt/Windows.Storage.h>
#include <winrt/Windows.Storage.Streams.h>
#include <winrt/Windows.Storage.AccessCache.h>
#include <winrt/Windows.Storage.FileProperties.h>
#include <winrt/Windows.Storage.Pickers.h>
#include <winrt/Windows.UI.Core.h>
#include <winrt/Windows.UI.Input.Spatial.h>

#include <winrt/Windows.ApplicationModel.Activation.h>
#include <winrt/Windows.ApplicationModel.Core.h>
#include <winrt/Windows.Gaming.Input.h>
#include <winrt/Windows.Graphics.Display.h>
#include <winrt/Windows.Graphics.Holographic.h>
#include <winrt/Windows.Perception.People.h>
#include <winrt/Windows.Perception.Spatial.h>
#include <winrt/Windows.Storage.h>
#include <winrt/Windows.Storage.Streams.h>
#include <winrt/Windows.UI.Core.h>


NAMESPACE_PARALLEL_BEGIN


using namespace DirectX;
using namespace Microsoft::WRL;
using namespace winrt::Windows::Foundation::Numerics;
using namespace winrt::Windows::Graphics::DirectX::Direct3D11;
using namespace winrt::Windows::Graphics::Holographic;
using namespace winrt::Windows::Perception::Spatial;

using namespace std::placeholders;
using namespace DirectX;
using namespace Microsoft::WRL;
using namespace winrt::Windows::Storage::Streams;
using namespace winrt::Windows::UI::Input::Spatial;

using namespace D2D1;
using namespace Microsoft::WRL;
using namespace winrt::Windows::Graphics::DirectX::Direct3D11;
using namespace winrt::Windows::Graphics::Display;
using namespace winrt::Windows::Graphics::Holographic;

using namespace Neso;
using namespace winrt::Windows::Foundation::Numerics;
using namespace winrt::Windows::Graphics::Holographic;
using namespace winrt::Windows::Perception;
using namespace winrt::Windows::Perception::Spatial;
using namespace DirectX;

using namespace concurrency;
using namespace std::placeholders;
using namespace winrt::Windows::ApplicationModel;
using namespace winrt::Windows::ApplicationModel::Activation;
using namespace winrt::Windows::ApplicationModel::Core;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Graphics::Holographic;
using namespace winrt::Windows::UI::Core;

using namespace winrt::Windows::Foundation::Numerics;
using namespace winrt::Windows::Perception::Spatial;
using namespace winrt::Windows::Graphics::Holographic;
using namespace winrt::Windows::UI::Input::Spatial;

using namespace concurrency;
using namespace DirectX;
using namespace std::placeholders;
using namespace winrt::Windows::Foundation::Numerics;
using namespace winrt::Windows::Gaming::Input;
using namespace winrt::Windows::Graphics::Holographic;
using namespace winrt::Windows::Perception::Spatial;
using namespace winrt::Windows::UI::Input::Spatial;

using namespace Neso;
using namespace DemoRoom;

using namespace Neso;
using namespace DemoRoom;
using namespace DirectX;
using namespace winrt::Windows::Foundation::Numerics;
using namespace winrt::Windows::Perception::Spatial;
using namespace winrt::Windows::UI::Input::Spatial;
using namespace std::literals::chrono_literals;

using namespace Neso;
using namespace DirectX;
using namespace winrt::Windows::Foundation::Numerics;

using namespace Neso;
using namespace DemoRoom;
using namespace winrt::Windows::Foundation::Numerics;
using namespace winrt::Windows::Perception::Spatial;
using namespace winrt::Windows::UI::Input::Spatial;
using namespace std::chrono_literals;

using namespace Neso;
using namespace DemoRoom;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Foundation::Numerics;
using namespace winrt::Windows::Perception::Spatial;
using namespace winrt::Windows::UI::Input::Spatial;

using namespace Neso;
using namespace DemoRoom;
using namespace winrt::Windows::Foundation::Numerics;
using namespace winrt::Windows::Perception::Spatial;
using namespace winrt::Windows::UI::Input::Spatial;



struct Dx11Holo {
	using namespace Microsoft::WRL;
	using namespace Neso;
	using namespace Concurrency;
	using namespace DirectX;
	using namespace winrt::Windows::Graphics::Holographic;
	using namespace winrt::Windows::Perception;
	using namespace winrt::Windows::Perception::Spatial;
	using namespace winrt::Windows::Foundation::Numerics;
	using namespace winrt::Windows::UI::Input::Spatial;
    using namespace winrt::Windows::Devices::Haptics;
    using namespace winrt::Windows::Foundation::Collections;
    using namespace winrt::Windows::UI::Input::Spatial;
	
	template <class T> using AppViewBase = winrt::implements<T, IFrameworkView>;
	template <class T> using AppViewSourceBase = winrt::implements<T, IFrameworkViewSource>;
	
	using HoloCam = winrt::Windows::Graphics::Holographic::HolographicCamera;
	using HoloCamRendParams = winrt::Windows::Graphics::Holographic:: HolographicCameraRenderingParameters;
	using HoloCamPose = winrt::Windows::Graphics::Holographic:: HolographicCameraPose;
	using HoloFrame = winrt::Windows::Graphics::Holographic::HolographicFrame;
	using HoloSpace = winrt::Windows::Graphics::Holographic:: HolographicSpace;
	using HoloFramePred = winrt::Windows::Graphics::Holographic:: HolographicFramePrediction;
	using GfxInteropDevice = winrt::Windows::Graphics::DirectX::Direct3D11::IDirect3DDevice;
	using SpatialSource = winrt::Windows::UI::Input::Spatial:: SpatialInteractionSource;
	using SpatialSourceHandedness = winrt::Windows::UI::Input::Spatial:: SpatialSourceHandedness;
	using SpatialInteractionController = winrt::Windows::UI::Input::Spatial:: SpatialInteractionController;
	using TimeSpan = winrt::Windows::Foundation:: TimeSpan;
	using SpatialCoordinateSystem = winrt::Windows::Perception::Spatial:: SpatialCoordinateSystem;
	using CoreWindow = winrt::Windows::UI::Core:: CoreWindow;
	using KeyEventArgs = winrt::Windows::UI::Core:: KeyEventArgs;
	using IFrameworkView = winrt::Windows::ApplicationModel::Core:: IFrameworkView;
	using IFrameworkViewSource = winrt::Windows::ApplicationModel::Core:: IFrameworkViewSource;
	using CoreApplicationView = winrt::Windows::ApplicationModel::Core:: CoreApplicationView;
	using LaunchActivatedEventArgs = winrt::Windows::ApplicationModel::Activation::LaunchActivatedEventArgs;
	using IActivatedEventArgs = winrt::Windows::ApplicationModel::Activation::IActivatedEventArgs;
	using IInspectable = winrt::Windows::Foundation:: IInspectable;
	using SuspendingEventArgs = winrt::Windows::ApplicationModel:: SuspendingEventArgs;
	using VisibilityChangedEventArgs = winrt::Windows::UI::Core:: VisibilityChangedEventArgs;
	using PointerEventArgs = winrt::Windows::UI::Core:: PointerEventArgs;
	using HoloStereoTransform = winrt::Windows::Graphics::Holographic:: HolographicStereoTransform;
	using Deferral = winrt::Windows::Foundation:: Deferral;
	using PerceptionTimestamp = winrt::Windows::Perception:: PerceptionTimestamp;
	using SpatialStageFrameOfReference = winrt::Windows::Perception::Spatial::SpatialStageFrameOfReference;
	using SpatialStationaryFrameOfReference = winrt::Windows::Perception::Spatial::SpatialStationaryFrameOfReference;
	using ISpatialInteractionManager = winrt::Windows::UI::Input::Spatial:: ISpatialInteractionManager;
	using SpatialInteractionManager = winrt::Windows::UI::Input::Spatial:: SpatialInteractionManager;
	using GfxLibInterfaceAccess = winrt::Windows::Graphics::DirectX::Direct3D11::IDirect3DDxgiInterfaceAccess;
	
	using GfxDevResources = DX:: DeviceResources;
	using GfxCamResources = DX:: CameraResources;
	using GfxDeviceNotify = DX:: IDeviceNotify;
	
	using NativeGfxDeviceRef = ComPtr<ID3D11Device4>;
	using NativeGfxDeviceContextRef = ComPtr<ID3D11DeviceContext3>;
	using NativeGfxLibRef = ComPtr<IDXGIAdapter3>;
	using Native2DLibRef = ComPtr<ID2D1Factory2>;
	using NativeHwLibRef = ComPtr<IDWriteFactory2>;
	using NativeVrCamLibRef = ComPtr<IWICImagingFactory2>;
	using NativeShaderResourceViewRef = ComPtr<ID3D11ShaderResourceView>;
	using NativeRenderTargetViewRef = ComPtr<ID3D11RenderTargetView>;
	using NativeDepthStencilViewRef = ComPtr<ID3D11DepthStencilView>;
	using NativeTexture2DRef = ComPtr<ID3D11Texture2D>;
	using NativeInputLayoutRef = ComPtr<ID3D11InputLayout>;
	using NativeBufferRef = ComPtr<ID3D11Buffer>;
	using NativeVertexShaderRef = ComPtr<ID3D11VertexShader>;
	using NativeGeometryShaderRef = ComPtr<ID3D11GeometryShader>;
	using NativePixelShaderRef = ComPtr<ID3D11PixelShader>;
	using NativeSamplerStateRef = ComPtr<ID3D11SamplerState>;
	using NativeDepthStencilStateRef = ComPtr<ID3D11DepthStencilState>;
	using NativeRenderTargetRef = ComPtr<ID2D1RenderTarget>;
	using NativeSolidColorBrushRef = ComPtr<ID2D1SolidColorBrush>;
	using NativeWriteTextFormatRef = ComPtr<IDWriteTextFormat>;
	using NativeGfxLibSurfaceRef = ComPtr<IDXGISurface>;
	
	using NativeInspectableRef = ComPtr<::IInspectable>;
	
	using NativeEventToken = winrt:: event_token;
	using NativeString = winrt::hstring;
	
	using FeatureLevel = D3D_FEATURE_LEVEL;
	
	// mat4 == mat4;
	
	void CheckResult(uint32 hr); // winrt:: check_hresult
	void ResumeBackground(); // co_await winrt::resume_background();
	
	static void Initialize(); // winrt::init_apartment();
	static uint16 BuzzContinuous(); // winrt::Windows::Devices::Haptics::KnownSimpleHapticsControllerWaveforms::BuzzContinuous();
	static void ThrowLastError(); // winrt::throw_last_error
	static void ThrowIfFailed(bool b); // Holo::ThrowIfFailed
	static FeatureLevel GetDefaultFeatureLevel(); // D3D_FEATURE_LEVEL_10_0
	static void SendContinuousBuzzForDuration(const SpatialSource& source, const TimeSpan& play_duration, float intensity = 1.0f);
	
	/* TODO
	// The main function bootstraps into the IFrameworkView.
	int __stdcall wWinMain(HINSTANCE, HINSTANCE, PWSTR, int)
	{
	    winrt::init_apartment();
	    CoreApplication::Run(AppViewSource());
	    return 0;
	}
	*/
	
};


NAMESPACE_PARALLEL_END


#endif
