#ifndef _SoftRend_Backend_h_
#define _SoftRend_Backend_h_

NAMESPACE_TOPSIDE_BEGIN

#ifdef flagPOSIX

template <class Backend> class SoftPipelineT;
template <class Backend> class SoftRendT;
template <class Backend> class SoftProgramT;
template <class Backend> class SoftShaderT;
template <class Gfx> class DataObjectT;

struct X11Sw {
	using NativeTexture = uint32;
	using NativeSurface = void*;
	using NativeColorBuffer = void*;
	/*using ShaderPipeline = SoftPipelineT<X11Sw>;
	using NativeRenderer = SoftRendT<X11Sw>;
	using NativeDepthBuffer = SoftFramebufferT<X11Sw>;
	using NativeFrameBuffer = SoftFramebufferT<X11Sw>;
	using NativeProgram = SoftProgramT<X11Sw>;
	using NativePipeline = SoftPipelineT<X11Sw>;
	using NativeShader = SoftShaderT<X11Sw>;
	using DataObject = DataObjectT<X11Sw>;*/
	
	static bool LockTextureToSurface(NativeTexture& tex, Rect r, NativeSurface& surf);
	static void QueryTexture(NativeTexture& tex, uint32& fmt, int& access, int& w, int& h);
	
};
#define X11SW_BACKEND(x) BACKEND(x, X11Sw)
#define X11SW_BACKEND_EXCPLICIT_INIT(x) template struct x <X11Sw>;
#else
#define X11SW_BACKEND(x)
#define X11SW_BACKEND_EXCPLICIT_INIT(x)
#endif

#ifdef flagSDL2
struct Sdl {
	using NativeTexture = SDL_Texture*;
	using NativeSurface = SDL_Surface*;
	using NativeColorBuffer = SDL_Texture*;
	
	
	static bool LockTextureToSurface(NativeTexture& tex, Rect r, NativeSurface& surf);
	static void QueryTexture(NativeTexture& tex, uint32& fmt, int& access, int& w, int& h);
	
};
#define SDL2_BACKEND(x) BACKEND(x, Sdl)
#define SDL2_BACKEND_EXCPLICIT_INIT(x) template struct x <Sdl>;
#else
#define SDL2_BACKEND(x)
#define SDL2_BACKEND_EXCPLICIT_INIT(x)
#endif



#define SOFTREND_BACKEND_LIST(x) \
	SDL2_BACKEND(x) \
	X11SW_BACKEND(x) \


#define SOFTREND_EXCPLICIT_INITIALIZE_CLASS(x) \
	SDL2_BACKEND_EXCPLICIT_INIT(x) \
	X11SW_BACKEND_EXCPLICIT_INIT(x) \



NAMESPACE_TOPSIDE_END

#endif
