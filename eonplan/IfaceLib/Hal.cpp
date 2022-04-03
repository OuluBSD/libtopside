#include "IfaceLib.h"

NAMESPACE_PLAN_BEGIN



PKG(Hal, Hal, H) {
	IfaceLib::Add(this);
	COLOR(198, 127, 200)
	DEPENDENCY(ParallelLib)
	
	PKG_IFACE {
		NATIVE_CLASS(AudioSinkDevice)
		//NATIVE_CLASS(AudioSourceDevice)
		NATIVE_CLASS(ContextBase)
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
		
		CLASS(ContextBase) {
			NATIVE_INHERIT(ContextBase, ctx)
			HAVE_VIRTUAL_CONTEXT
			
		}
	}
	
	VENDOR(Sdl2) {
		VENDOR_ENABLED_FLAG(SDL2)
		
		LIBRARY("", SDL2)
		LIBRARY("", SDL2_ttf)
		LIBRARY("", SDL2_image)
		VENDOR_INCLUDE("", SDL2/SDL.h)
		VENDOR_INCLUDE("", SDL2/SDL_ttf.h)
		VENDOR_INCLUDE("", SDL2/SDL_image.h)
		VENDOR_HEADER_REQUIRES_INCLUDES
		
		VENDOR_CLASS(AudioSinkDevice, SDL_AudioDeviceID)
		
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
