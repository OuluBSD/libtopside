#include "IfaceLib.h"

NAMESPACE_PLAN_BEGIN



PKG(Hal, Hal, H) {
	IfaceLib::Add(this);
	COLOR(198, 127, 200)
	DEPENDENCY(ParallelLib)
	DEPENDENCY(IGraphics)
	HAVE_RECV_FINALIZE
	HAVE_UPDATE
	HAVE_IS_READY
	
	PKG_IFACE {
		NATIVE_CLASS(AudioSinkDevice)
		//NATIVE_CLASS(Window)
		//NATIVE_CLASS(Renderer)
		//NATIVE_CLASS(AudioSourceDevice)
		NATIVE_CLASS(ContextBase)
		//NATIVE_CLASS(EventsBase)
		//UTIL_CLASS()
		
	}
	
	NAMESPACE {
		CLASS(AudioSinkDevice) {
			NATIVE_INHERIT(AudioSinkDevice, dev)
			
		}
		/*
		CLASS(AudioSourceDevice) {
			NATIVE_INHERIT(AudioSourceDevice, dev)
			
		}*/
		/*CLASS(Window) {
			NATIVE_INHERIT(Window, win)
			
		}
		
		CLASS(Renderer) {
			NATIVE_INHERIT(Renderer, rend)
			
		}*/
		
		CLASS(CenterVideoSinkDevice) {
			NATIVE_INHERIT(VideoSink, dev)
			
			//NATIVE_FIELD(NativeWindow*, win)
			//NATIVE_FIELD(NativeRenderer*, rend)
			
		}
		
		CLASS(CenterFboSinkDevice) {
			NATIVE_INHERIT(Sw3dVideoSink, dev)
			
			//NATIVE_FIELD(NativeWindow*, win)
			//NATIVE_FIELD(NativeRenderer*, rend)
			
		}
		
		CLASS(OglVideoSinkDevice) {
			NATIVE_INHERIT(OglVideoSink, dev)
			NATIVE_ENABLED_FLAG(OGL)
			
			//NATIVE_FIELD(NativeWindow*, win)
			//NATIVE_FIELD(NativeRenderer*, rend)
			
		}
		
		CLASS(ContextBase) {
			NATIVE_INHERIT(ContextBase, ctx)
			HAVE_VIRTUAL_CONTEXT
			
		}
		
		CLASS(EventsBase) {
			NATIVE_INHERIT(EventsBase, ctx)
			
		}
	}
	
	VENDOR(Sdl) {
		VENDOR_ENABLED_FLAG(SDL2)
		
		LIBRARY("", SDL2)
		LIBRARY("", SDL2_ttf)
		LIBRARY("", SDL2_image)
		VENDOR_INCLUDE("", SDL2/SDL.h)
		VENDOR_INCLUDE("", SDL2/SDL_ttf.h)
		VENDOR_INCLUDE("", SDL2/SDL_image.h)
		VENDOR_HEADER_REQUIRES_INCLUDES
		
		VENDOR_CLASS(AudioSinkDevice, SDL_AudioDeviceID)
		//VENDOR_CLASS(Window, SDL_Window*)
		//VENDOR_CLASS(Renderer, SDL_Renderer*)
		
		v->AddStruct("NativeVideoSink")
			.Add("display",		"void*")
			.Add("win",			"SDL_Window*")
			.Add("rend",		"SDL_Renderer*")
			.Add("fb",			"FramebufferT<SdlCpuGfx>")
			.Add("id",			"One<ImageDraw>")
			//.Add("render_src",	"int")
			.Add("sz",			"Size")
			.Add("pi",			"ProgImage")
			;
		
		v->AddStruct("NativeSw3dVideoSink")
			.Add("display",		"void*")
			.Add("win",			"SDL_Window*")
			.Add("rend",		"SDL_Renderer*")
			.Add("fb",			"SDL_Texture*")
			.Add("accel",		"GfxAccelAtom<SdlSwGfx>")
			;
		
		v->AddStruct("NativeOglVideoSink")
			.Add("display",		"void*")
			.Add("win",			"::SDL_Window*")
			.Add("rend",		"::SDL_Renderer*")
			.Add("fb",			"uint32")
			.Add("accel",		"GfxAccelAtom<SdlOglGfx>")
			.Add("rend_info",	"::SDL_RendererInfo")
			.Add("gl_ctx",		"::SDL_GLContext")
			.RequireFlag("OGL");
			;
		
		v->AddStruct("NativeEventsBase")
			.Add("time",			"int")
			.Add("seq",				"dword")
			.Add("ev",				"UPP::CtrlEvent")
			.Add("sz",				"Size")
			.Add("ev_sendable",		"bool")
			.Add("is_lalt",			"bool")
			.Add("is_ralt",			"bool")
			.Add("is_lshift",		"bool")
			.Add("is_rshift",		"bool")
			.Add("is_lctrl",		"bool")
			.Add("is_rctrl",		"bool")
			.Add("prev_mouse_pt",	"Point")
			;
		
		// POSIX: GLEW GL GLU
		// Win32: Opengl32 glu32 glew32s
		
		/*
		#if defined flagWIN32 && defined flagMSC
			#include <SDL.h>
			#include <SDL_ttf.h>
			#include <SDL_image.h>
			#include <SDL_syswm.h>
			#ifdef flagSCREEN
				#include <SDL_opengl.h>
			#endif
		#else
			#include <SDL2/SDL.h>
			#include <SDL2/SDL_ttf.h>
			#include <SDL2/SDL_image.h>
			#ifdef flagSCREEN
				#include <SDL2/SDL_opengl.h>
			#endif
		#endif
		*/
		
	}
	
	
	
}


NAMESPACE_PLAN_END
