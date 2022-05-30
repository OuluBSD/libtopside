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
	HAL_CLS(CenterFboSinkDevice, x) \
	HAL_CLS(OglVideoSinkDevice, x) \
	HAL_CLS(ContextBase, x) \
	HAL_CLS(EventsBase, x) \



#define HAL_VNDR_LIST \
	HAL_VNDR(HalSdl) \



#define HAL_CLS(x, v) struct v##x;
#define HAL_VNDR(x) HAL_CLS_LIST(x)
HAL_VNDR_LIST
#undef HAL_VNDR
#undef HAL_CLS



#if defined flagSDL2
struct HalSdl {
	using NativeAudioSinkDevice = SDL_AudioDeviceID;
	using NativeContextBase = void*;
	
	struct NativeVideoSink {
		void* display;
		SDL_Window* win;
		SDL_Renderer* rend;
		FramebufferT<SdlCpuGfx> fb;
		One<ImageDraw> id;
		Size sz;
		ProgImage pi;
	};
	
	struct NativeSw3dVideoSink {
		void* display;
		SDL_Window* win;
		SDL_Renderer* rend;
		SDL_Texture* fb;
		GfxAccelAtom<SdlSwGfx> accel;
	};
	
	#if defined flagOGL
	struct NativeOglVideoSink {
		void* display;
		::SDL_Window* win;
		::SDL_Renderer* rend;
		uint32 fb;
		GfxAccelAtom<SdlOglGfx> accel;
		::SDL_RendererInfo rend_info;
		::SDL_GLContext gl_ctx;
	};
	#endif
	
	struct NativeEventsBase {
		int time;
		dword seq;
		UPP::CtrlEvent ev;
		Size sz;
		bool ev_sendable;
		bool is_lalt;
		bool is_ralt;
		bool is_lshift;
		bool is_rshift;
		bool is_lctrl;
		bool is_rctrl;
		Point prev_mouse_pt;
	};
	
	struct Thread {
		
	};
	static Thread& Local() {thread_local static Thread t; return t;}
	
	#include "IfaceFuncs.inl"
	
};
#endif



NAMESPACE_PARALLEL_END


#endif

