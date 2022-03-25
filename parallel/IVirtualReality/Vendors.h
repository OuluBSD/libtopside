// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 25.3.25 19:11:33

#ifndef _IVirtualReality_Vendors_h_
#define _IVirtualReality_Vendors_h_

NAMESPACE_TOPSIDE_BEGIN

#define VR_CLS_LIST(x) \
	VR_CLS(MotionController, x) \
	VR_CLS(MotionControllerSystem, x) \
	VR_CLS(AppView, x) \
	VR_CLS(CameraResources, x) \
	VR_CLS(ControllerModelCache, x) \
	VR_CLS(DeviceResources, x) \
	VR_CLS(HolographicRenderer, x) \
	VR_CLS(HolographicScene, x) \
	VR_CLS(SpatialInteractionSystem, x) \
	VR_CLS(Renderer, x) \



#define VR_VNDR_LIST \
	VR_VNDR(VrHolo) \
	VR_VNDR(VrOvr) \
	VR_VNDR(VrHmd) \



#define VR_CLS(x, v) struct v##x;
#define VR_VNDR(x) VR_CLS_LIST(x)
VR_VNDR_LIST
#undef VR_VNDR
#undef VR_CLS



struct VrHolo {
	using NativeMotionController = uint32;
	using NativeMotionControllerSystem = uint32;
	typedef void (*DataCallbackFn)(void*, char* data, int size);
	
	struct Thread {
		
	};
	static Thread& Local() {thread_local static Thread t; return t;}
	
	#include "IfaceFuncs.inl"
	
};

struct VrOvr {
	using NativeMotionController = uint32;
	using NativeMotionControllerSystem = uint32;
	typedef void (*DataCallbackFn)(void*, char* data, int size);
	
	struct Thread {
		
	};
	static Thread& Local() {thread_local static Thread t; return t;}
	
	#include "IfaceFuncs.inl"
	
};

struct VrHmd {
	using NativeMotionController = uint32;
	using NativeMotionControllerSystem = uint32;
	typedef void (*DataCallbackFn)(void*, char* data, int size);
	
	struct Thread {
		
	};
	static Thread& Local() {thread_local static Thread t; return t;}
	
	#include "IfaceFuncs.inl"
	
};



NAMESPACE_TOPSIDE_END


#endif

