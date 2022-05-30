#ifndef _IHolograph_Various_h_
#define _IHolograph_Various_h_


NAMESPACE_PARALLEL_BEGIN




struct NativeRenderTargetView{};
struct NativeDepthStencilView{};
struct NativeGfxDevice{};
struct NativeGfxDeviceContext{};
struct NativeGfxLib{};
struct Native2DLib{};
struct NativeHwLib{};
struct NativeVrCamLib{};
struct NativeShaderResourceView{};
struct NativeTexture2D{};
struct NativeInputLayout{};
struct NativeBuffer{};
struct NativeVertexShader{};
struct NativeGeometryShader{};
struct NativePixelShader{};
struct NativeSamplerState{};
struct NativeDepthStencilState{};
struct NativeRenderTarget{};
struct NativeSolidColorBrush{};
struct NativeWriteTextFormat{};
struct NativeGfxLibSurface{};

using NativeRenderTargetViewRef = NativeRenderTargetView*;
using NativeDepthStencilViewRef = NativeDepthStencilView*;
using NativeGfxDeviceRef = NativeGfxDevice*;
using NativeGfxDeviceContextRef = NativeGfxDeviceContext*;
using NativeGfxLibRef = NativeGfxLib*;
using Native2DLibRef = Native2DLib*;
using NativeHwLibRef = NativeHwLib*;
using NativeVrCamLibRef = NativeVrCamLib*;
using NativeShaderResourceViewRef = NativeShaderResourceView*;
using NativeTexture2DRef = NativeTexture2D*;
using NativeInputLayoutRef = NativeInputLayout*;
using NativeBufferRef = NativeBuffer*;
using NativeVertexShaderRef = NativeVertexShader*;
using NativeGeometryShaderRef = NativeGeometryShader*;
using NativePixelShaderRef = NativePixelShader*;
using NativeSamplerStateRef = NativeSamplerState*;
using NativeDepthStencilStateRef = NativeDepthStencilState*;
using NativeRenderTargetRef = NativeRenderTarget*;
using NativeSolidColorBrushRef = NativeSolidColorBrush*;
using NativeWriteTextFormatRef = NativeWriteTextFormat*;
using NativeGfxLibSurfaceRef = NativeGfxLibSurface*;

using FeatureLevel = int;

struct GfxDevice{};
struct GfxDevResources{};

struct LaunchActivatedEventArgs{};
struct VisibilityChangedEventArgs{};
struct GfxCoreWindowEventArgs{};
struct KeyEventArgs{};
struct GfxCoreWindow{};
struct CoreApplicationView{};
struct ActivatedEventArgs{};
struct Inspectable{};
struct SuspendingEventArgs{};
struct PointerEventArgs{};
struct NativeEventToken{};
struct FrameworkView{};







typedef enum {
	Unspecified,
	Left,
	Right
} SpatialInteractionSourceHandedness;

typedef enum {
	HolographicSpaceCreateNextFrame,
	HolographicFrameUpdatePrediction,
	
} PredictionUpdateReason;

typedef enum {
	High,
	Approximate,
} SpatialInteractionSourcePositionAccuracy;

#undef Success
typedef enum {
	Success,
	DeviceRemoved
} HolographicFramePresentResult;




struct SpatialCoordinateSystem {
	// note: dx11 identical
	
};

struct SpatialStageFrameOfReference : RTTIBase {
	RTTI_DECL0(SpatialStageFrameOfReference)
	
	SpatialCoordinateSystem* sys = 0;
	
	
	SpatialStageFrameOfReference();
	void Clear();
	
	SpatialCoordinateSystem& GetCoordinateSystem() const;
	
	Callback WhenChanged;
	static Callback WhenActiveChanged;
	
};


SpatialStageFrameOfReference* GetActiveSpatialStageFrameOfReference();




struct SpatialSourceEventArgs {
	
};

struct SpatialInteractionSourceEventArgs : SpatialSourceEventArgs {
	
};

struct SpatialSource {
	uint32 id = 0;
	
	
	uint32 GetId() const {return id;}
	
};

struct SpatialPointerInteractionSourcePose {
	//bool is_set = false;
	vec3 forward_direction;
	quat orientation;
	vec3 position;
	SpatialInteractionSourcePositionAccuracy position_accuracy;
	vec3 up_direction;
	
	vec3 GetPosition() const {return position;}
	vec3 GetForwardDirection() const {return forward_direction;}
	quat GetOrientation() const {return orientation;}
	//operator bool() const {return is_set;}
};

struct SpatialLocation {
	vec3 position;
	bool is_valid = false;
	
	
	virtual vec3 GetPosition() const {return position;}
	
	operator bool() const {return is_valid;}
	
};

struct SpatialSourceLocation : SpatialLocation {
	vec3 velocity;
	vec3 angular_velocity;
	quat orientation;
	SpatialPointerInteractionSourcePose* pose = 0;
	
	virtual vec3 GetVelocity() const {return velocity;}
	virtual vec3 GetAngularVelocity() const {return angular_velocity;}
	virtual quat GetOrientation() const {return orientation;}
	
	virtual SpatialPointerInteractionSourcePose* GetSourcePointerPose() const {return pose;}
	
};

struct SpatialInteractionSourceLocation : SpatialSourceLocation {
	
	
};

struct SpatialInteractionSource : SpatialSource {
	SpatialInteractionSourceHandedness	handedness = Unspecified;
	SpatialInteractionSourceLocation	location;
	
	
	SpatialInteractionSourceHandedness GetHandedness() const {return handedness;}
	
};


typedef float TimeSpan;

struct PerceptionTimestamp {
	TimeSpan prediction_amount;
	TimeSpan system_relative_target_time;
	Time target_time;
	
};

struct SpatialInteractionSourceProperties {
	
	
	SpatialInteractionSourceLocation* TryGetLocation(const SpatialCoordinateSystem& coord_system);
	
	
};

struct SpatialInteractionSourceState {
	SpatialInteractionSource* src = 0;
	SpatialInteractionSourceProperties* props = 0;
	
	
	SpatialInteractionSource& GetSource() const {ASSERT(src); return *src;}
	SpatialInteractionSourceProperties& GetProperties() const {return *props;}
	
};

struct SpatialInteractionManager {
	Array<SpatialInteractionSourceState> detected_source_states;
	
	const Array<SpatialInteractionSourceState>& GetDetectedSourcesAtTimestamp(const PerceptionTimestamp& ts);
	
	
	
	static SpatialInteractionManager* GetForCurrentView();
	static void SetCurrentView(SpatialInteractionManager* mgr);
	
	using Cb = Callback2<const SpatialInteractionManager&, const SpatialSourceEventArgs&>;
	Cb WhenSourceDetected;
	Cb WhenSourcePressed;
	Cb WhenSourceUpdated;
	Cb WhenSourceReleased;
	Cb WhenSourceLost;
	
};

struct SpatialLocator {
	SpatialCoordinateSystem* sys = 0;
	SpatialLocator* parent = 0;
	vec3 position;
	
	
	SpatialLocator();
	void Clear();
	
	SpatialCoordinateSystem& GetCoordinateSystem() const;
	SpatialLocator GetRelative(const vec3& position);
	
	SpatialLocation TryLocateAtTimestamp(
		const PerceptionTimestamp& timestamp,
		const SpatialCoordinateSystem& coordinateSystem);
	
};

SpatialLocator& GetActiveSpatialLocator();


struct CameraAddedEventArgs {
	
};

struct CameraRemovedEventArgs {
	
};

struct SpatialStaticAnchor {
	
	
	
};

struct HolographicCameraRenderingParameters {
	
	
	
	HolographicFramePresentResult PresentUsingCurrentPrediction();
};

struct HolographicStereoTransform {
	mat4 left;
	mat4 right;
};

struct HolographicCamera {
	uint32 id = 0;
	bool is_stereo = false;
	Size size;
	
	uint32 GetId() const {return id;}
	bool IsStereo() const {return is_stereo;}
	Size GetRenderTargetSize() const {return size;}
	
};

struct HolographicCameraPose : Moveable<HolographicCameraPose> {
	double far_plane_distance;
	double near_plane_distance;
	HolographicCamera* camera = 0;
	HolographicStereoTransform projection_transform;
	Rect viewport;
	
	
	HolographicCamera& GetHolographicCamera() const {ASSERT(camera); return *camera;}
	Size GetRenderTargetSize() const {return viewport.GetSize();}
	
};

struct HolographicFramePrediction {
	Array<HolographicCameraPose> camera_poses;
	PerceptionTimestamp timestamp;
	
	
	void operator=(const HolographicFramePrediction& s);
	const PerceptionTimestamp& GetTimestamp() const {return timestamp;}
	const Array<HolographicCameraPose>& GetCameraPoses() const {return camera_poses;}
	
};

struct HolographicFrame {
	HolographicFramePrediction current;
	HolographicCameraRenderingParameters params;
	
	HolographicFrame();
	HolographicFrame(const HolographicFrame& f);
	void operator=(const HolographicFrame& s);
	const HolographicFramePrediction& GetCurrentPrediction() const;
	const HolographicCameraRenderingParameters& GetRenderingParameters(const HolographicCameraPose& cam_pose) const;
	HolographicFramePresentResult PresentUsingCurrentPrediction();
	void UpdateCurrentPrediction();
};

struct HolographicSpace {
	HolographicFrame frame;
	
	
	void CreateNextFrame();
	
	Callback2<const HolographicSpace&, const CameraAddedEventArgs&> WhenCameraAdded;
	Callback2<const HolographicSpace&, const CameraRemovedEventArgs&> WhenCameraRemoved;
	
};



NAMESPACE_PARALLEL_END


#endif
