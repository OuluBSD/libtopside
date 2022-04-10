// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!

#ifndef _IHal_Vendors_h_
#define _IHal_Vendors_h_

#if defined flagSDL2
	#include <SDL2/SDL.h>
	#include <SDL2/SDL_ttf.h>
	#include <SDL2/SDL_image.h>
#endif

NAMESPACE_PARALLEL_BEGIN

#define HAL_CLS_LIST(x) \
	HAL_CLS(AudioSinkDevice, x) \
	HAL_CLS(CenterVideoSinkDevice, x) \
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
	using NativeAudioSinkDevice = SDL_AudioDeviceID;
	using NativeContextBase = void*;
	
	struct NativeVideoSink {
		SDL_Window* win;
		SDL_Renderer* rend;
		FramebufferT<SdlCpuGfx> fb;
	};

	
	struct Thread {
		
	};
	static Thread& Local() {thread_local static Thread t; return t;}
	
	#include "IfaceFuncs.inl"
	
};
#endif



NAMESPACE_PARALLEL_END


#endif

