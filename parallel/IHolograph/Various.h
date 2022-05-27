#ifndef _IHolograph_Various_h_
#define _IHolograph_Various_h_


NAMESPACE_PARALLEL_BEGIN


struct VirtualRoomAnchor : RTTIBase {
	RTTI_DECL0(VirtualRoomAnchor)
	
	#ifdef flagDX11
	SpatialStageFrameOfReference dx11;
	#endif
	
	
	VirtualRoomAnchor();
	void Clear();
	
	
	Callback WhenChanged;
	static Callback WhenActiveChanged;
	
};


VirtualRoomAnchor* GetActiveVirtualRoomAnchor();



struct SpatialDynamicAnchor {
	SpatialDynamicAnchor* parent;
	vec3 position;
	
	
	SpatialDynamicAnchor();
	void Clear();
	SpatialDynamicAnchor GetRelative(const vec3& position);
	
	
};

SpatialDynamicAnchor& GetActiveSpatialDynamicAnchor();


struct CameraAddedEventArgs {
	
};

struct CameraRemovedEventArgs {
	
};

typedef enum {
	Unspecified,
	Left,
	Right
} SpatialSourceHandedness;

struct SpatialStaticAnchor {
	
	
	
};

struct SpatialSource {
	// note: dx11 identical
	
	
};

struct SpatialSourceLocation {
	// note: dx11 identical
	
};

struct SpatialCoordinateSystem {
	// note: dx11 identical
	
};

struct HoloFramePred {
	// note: dx11 identical
	
};

struct HoloSpace {
	// note: dx11 identical
	
	
	
	Callback2<const HoloSpace&, const CameraAddedEventArgs&> WhenCameraAdded;
	Callback2<const HoloSpace&, const CameraRemovedEventArgs&> WhenCameraRemoved;
	
};



NAMESPACE_PARALLEL_END


#endif
