// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 2022.3.31 23:44:55

#ifndef _IHal_Vendors_h_
#define _IHal_Vendors_h_

NAMESPACE_PARALLEL_BEGIN

#define HAL_CLS_LIST(x) \
	HAL_CLS(AudioSinkDevice, x) \
	HAL_CLS(ContextBase, x) \



#define HAL_VNDR_LIST \
	HAL_VNDR(HalSdl2) \



#define HAL_CLS(x, v) struct v##x;
#define HAL_VNDR(x) HAL_CLS_LIST(x)
HAL_VNDR_LIST
#undef HAL_VNDR
#undef HAL_CLS



#if defined flagSDL2
struct HalSdl2 {
	using NativeAudioSinkDevice = void*;
	using NativeContextBase = void*;
	
	struct Thread {
		
	};
	static Thread& Local() {thread_local static Thread t; return t;}
	
	#include "IfaceFuncs.inl"
	
};
#endif



NAMESPACE_PARALLEL_END


#endif

