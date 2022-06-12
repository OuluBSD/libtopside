#ifndef _IHolograph_Ogl_h_
#define _IHolograph_Ogl_h_

#if 0

NAMESPACE_PARALLEL_BEGIN


struct OglHolo {
	struct VoidBase {};
	
	template <class T> using AppViewBase = VoidBase;
	template <class T> using AppViewSourceBase = VoidBase;
	
	using HolographicCamera = int;
	using HolographicCameraRenderingParameters = int;
	using HolographicCameraPose = int;
	using HolographicFrame = int;
	using HolographicSpace = int;
	using HolographicFramePrediction = int;
	using GfxInteropDevice = int;
	using SpatialSource = int;
	using SpatialInteractionSourceHandedness = int;
	using SpatialInteractionController = int;
	using TimeSpan = int;
	using SpatialCoordinateSystem = int;
	using GfxCoreWindow = int;
	using KeyEventArgs = int;
	using IFrameworkView = int;
	using IFrameworkViewSource = int;
	using CoreApplicationView = int;
	using LaunchActivatedEventArgs = int;
	using IActivatedEventArgs = int;
	using IInspectable = int;
	using SuspendingEventArgs = int;
	using VisibilityChangedEventArgs = int;
	using PointerEventArgs = int;
	using HolographicStereoTransform = int;
	using Deferral = int;
	using PerceptionTimestamp = int;
	using SpatialStageFrameOfReference = int;
	using SpatialStationaryFrameOfReference = int;
	using ISpatialInteractionManager = int;
	using SpatialInteractionManager = int;
	using GfxLibInterfaceAccess = int;
	
	using GfxDevResources = int;
	using GfxCamResources = int;
	using GfxDeviceNotify = int;
	
	using NativeGfxDeviceRef = int;
	using NativeGfxDeviceContextRef = int;
	using NativeGfxLibRef = int;
	using Native2DLibRef = int;
	using NativeHwLibRef = int;
	using NativeVrCamLibRef = int;
	using NativeShaderResourceViewRef = int;
	using NativeRenderTargetViewRef = int;
	using NativeDepthStencilViewRef = int;
	using NativeTexture2DRef = int;
	using NativeInputLayoutRef = int;
	using NativeBufferRef = int;
	using NativeVertexShaderRef = int;
	using NativeGeometryShaderRef = int;
	using NativePixelShaderRef = int;
	using NativeSamplerStateRef = int;
	using NativeDepthStencilStateRef = int;
	using NativeRenderTargetRef = int;
	using NativeSolidColorBrushRef = int;
	using NativeWriteTextFormatRef = int;
	using NativeGfxLibSurfaceRef = int;
	
	using NativeInspectableRef = int;
	
	using NativeEventToken = int;
	using NativeString = int;
	
	using FeatureLevel = int;
	
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
#endif
