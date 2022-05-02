#ifndef _IGraphics_Types_h_
#define _IGraphics_Types_h_


NAMESPACE_PARALLEL_BEGIN

/*namespace Serial {
class Format;
class FboFormat;
class VideoFormat;
}*/

#define GFX_CLS_LIST(g) \
	GFX_CLS(VertexShaderArgs, g) \
	GFX_CLS(FragmentShaderArgs, g) \
	/*GFX_CLS(BinderIface, g)*/ \
	GFX_CLS(DataObject, g) \
	/*GFX_CLS(DataState, g)*/ \
	/*GFX_CLS(InputState, g)*/ \
	/*GFX_CLS(Framebuffer, g)*/ \
	GFX_CLS(Compiler, g) \
	GFX_CLS(Linker, g) \
	/*GFX_CLS(ShaderState, g)*/ \
	/*GFX_CLS(Shader, g)*/ \
	GFX_CLS(ShaderPipeline, g) \
	/*GFX_CLS(RuntimeState, g)*/ \
	/*GFX_CLS(FramebufferStateExt, g)*/ \
	/*GFX_CLS(ContextState, g)*/ \
	GFX_CLS(Renderer, g) \
	GFX_CLS(StateDraw, g) \
	GFX_CLS(Buffer, g) \


#define GFX_RENDSYS_LIST \
	GFX_RSYS(SdlCpu) \
	GFX_RSYS(SdlOgl) \
	GFX_RSYS(X11Ogl) \
	GFX_RSYS(X11Sw) \


#define GFX_CLS(x, g) template <class Gfx> struct x##T;
GFX_CLS_LIST(_)
#undef GFX_CLS

#define GFX_RSYS(x) struct x##Gfx;
GFX_RENDSYS_LIST
#undef GFX_RSYS

/*#define GFX_CLS(x, g) struct g##x;
#define GFX_RSYS(x) GFX_CLS_LIST(x)
GFX_RENDSYS_LIST
#undef GFX_RSYS
#undef GFX_CLS*/





struct GfxFramebuffer;
struct GfxBuffer;
template <class Gfx> struct FramebufferT;


template <class Gfx>
struct CpuGfxT {
	using SoftRend			= SoftRendT<Gfx>;
	using SoftCompiler		= SoftCompilerT<Gfx>;
	using SoftShader		= SoftShaderT<Gfx>;
	using SoftProgram		= SoftProgramT<Gfx>;
	using SoftFramebuffer	= SoftFramebufferT<Gfx>;
	using SoftPipeline		= SoftPipelineT<Gfx>;
	// using SoftVertexArray	= SoftVertexArrayT<Gfx>;
	using NativeColorBufferRef		= ByteImage*;
	using NativeColorBufferConstRef	= ConstByteImage*;
	using NativeDepthBufferRef		= DepthImage*;
	using NativeDepthBufferConstRef	= ConstDepthImage*;
	
	using FramebufferBase	= GfxFramebuffer;
	
	
	struct Thread {
		SoftRend rend;
		SoftCompiler comp;
		SoftShader* shdr = 0;
		SoftProgram* prog = 0;
		SoftFramebuffer* fb = 0;
		SoftFramebuffer* ctx_default_fb = 0;
		DepthImage* depth = 0;
		SoftPipeline* pipe = 0;
		SoftVertexArray* vao = 0;
		
		struct Tex {
			NativeColorBufferConstRef r = 0;
			NativeColorBufferRef rw = 0;
			
			NativeColorBufferConstRef GetReadTexture() const {return r ? r : rw;}
		};
		Tex texture[CHANNEL_COUNT];
		int active_texture = -1;
		
		Tex& T() {
			ASSERT(active_texture >= 0 && active_texture < CHANNEL_COUNT);
			return texture[active_texture];
		}
	};
	
	// not here: using NativeTexture = uint32;
	using NativeShaderRef = SoftShader*;
	using NativeFrameBufferRef = SoftFramebuffer*;
	using NativeFrameBufferConstRef = const SoftFramebuffer*;
	using NativeVertexArray = SoftVertexArray;
	using NativeVertexBuffer = SoftVertexBuffer;
	using NativeElementBuffer = SoftElementBuffer;
	using NativeProgram = SoftProgram;
	using NativePipeline = SoftPipeline;
	using ValFormat = Parallel::VideoFormat;
	
	static const GVar::GfxType Type = GVar::SW;
	
	#include "TypeFuncList.inl"
	
	static Serial::VideoFormat& GetFormat(Parallel::Format& fmt) {return fmt.vid;}
	
	static Thread& Local();
	static SoftRend& Rend();
	
	static NativeColorBufferConstRef GetLocalTexture(int ch);
	
	static const bool is_builtin_shader = true;
	
};

#ifdef flagOGL

struct OglFramebufferBase;
struct OglBufferBase;
	
template <class Gfx>
struct OglGfxT {
	static const bool is_builtin_shader = false;
	
	using NativeTexture = GLuint;
	using NativeShaderRef = GLuint;
	using NativeColorBufferRef = GLuint;
	using NativeColorBufferConstRef = GLuint;
	using NativeDepthBufferRef = GLuint;
	using NativeDepthBufferConstRef = GLuint;
	using NativeFrameBufferRef = GLuint;
	using NativeFrameBufferConstRef = GLuint;
	using NativeBuffer = GLuint;
	using SystemFrameBufferRef = NativeFrameBufferRef;
	using NativeVertexArray = GLuint;
	using NativeVertexBuffer = GLuint;
	using NativeElementBuffer = GLuint;
	using NativeProgram = GLuint;
	using NativePipeline = GLuint;
	using ValFormat = Serial::FboFormat;
	
	using FramebufferBase = OglFramebufferBase;
	using BufferBase = OglBufferBase;
	
	static const GVar::GfxType Type = GVar::OGL;
	
	#include "TypeFuncList.inl"
	
	static Serial::FboFormat& GetFormat(Parallel::Format& fmt);
	
};
#endif


#ifdef flagPOSIX
struct X11Gfx {
	using NativeDisplay			= ::Display*;
	using NativeWindow			= ::Window;
	using NativeRenderer		= void*;
	using NativeRendererInfo	= void*;
	
	static Size GetWindowSize(NativeWindow& win);
	static bool CreateWindowAndRenderer(Size screen_sz, dword flags, NativeWindow& win, NativeRenderer& rend);
	static void SetTitle(NativeDisplay& display, NativeWindow& win, String title);
	static void SetWindowFullscreen(NativeWindow& win, bool b=true);
	static void DestroyRenderer(NativeRenderer& rend);
	static void DestroyWindow(NativeWindow& win);
	static void MaximizeWindow(NativeWindow& win);
	static void RestoreWindow(NativeWindow& win);
	static void SetWindowPosition(NativeWindow& win, Point pt);
	static void SetWindowSize(NativeWindow& win, Size sz);
	
	
};

struct X11SwGfx : CpuGfxT<X11SwGfx>, X11Gfx {
	using SystemFrameBufferRef = SoftFramebuffer*;
	using NativeGLContext = void*;
	using BufferBase = GfxBuffer;
	
	using NativeTexture = SystemFrameBufferRef;
	using NativeSurface = NativeColorBufferRef;
	//using NativeColorBufferRef = void*;
	using SoftShaderLibrary = SoftShaderLibraryT<X11SwGfx>;
	
	#define GFX_CLS(x, g) using x = x##T<g##Gfx>;
	//#define GFX_CLS(x, g) using x = g##x;
	GFX_CLS_LIST(X11Sw)
	#undef GFX_CLS
	
	
	static void DeleteContext(NativeGLContext& ctx);
	static void ActivateNextFrame(NativeDisplay& d, NativeWindow& w, NativeRenderer& r, NativeColorBufferRef color_buf);
	
	static bool LockTextureToSurface(NativeTexture& tex, Rect r, NativeSurface& surf);
	static void UnlockTextureToSurface(NativeTexture& tex);
	static void QueryTexture(NativeTexture& tex, uint32& fmt, int& access, int& w, int& h);
	
	static int GetBytesPerPixel(NativeSurface& surf);
	static int GetPitch(NativeSurface& surf);
	static byte* GetData(NativeSurface& surf);
	
};

#ifdef flagOGL
struct X11OglGfx : OglGfxT<X11OglGfx>, X11Gfx {
	#define GFX_CLS(x, g) using x = x##T<g##Gfx>;
	//#define GFX_CLS(x, g) using x = g##x;
	GFX_CLS_LIST(X11Ogl)
	#undef GFX_CLS
	
	using NativeGLContext = ::GLXContext;
	using SoftShaderLibrary = DummySoftShaderLibraryT<X11OglGfx>;
	
	static void DeleteContext(NativeGLContext& ctx);
	static void ActivateNextFrame(NativeDisplay& d, NativeWindow& w, NativeRenderer& r, NativeColorBufferRef color_buf);
	
};
#endif
#endif


#ifdef flagSDL2
struct SdlGfx {
	using NativeDisplay			= void*;
	using NativeWindow			= SDL_Window*;
	using NativeRenderer		= SDL_Renderer*;
	using NativeRendererInfo	= SDL_RendererInfo;
	using NativeGLContext		= SDL_GLContext;
	
	static Size GetWindowSize(NativeWindow& win);
	static bool CreateWindowAndRenderer(Size screen_sz, dword flags, NativeWindow& win, NativeRenderer& rend);
	static void SetTitle(NativeDisplay& display, NativeWindow& win, String title);
	static void SetWindowFullscreen(NativeWindow& win, bool b=true);
	static void DestroyRenderer(NativeRenderer& rend);
	static void DestroyWindow(NativeWindow& win);
	static void DeleteContext(NativeGLContext& ctx);
	static void MaximizeWindow(NativeWindow& win);
	static void RestoreWindow(NativeWindow& win);
	static void SetWindowPosition(NativeWindow& win, Point pt);
	static void SetWindowSize(NativeWindow& win, Size sz);
	
	
	
};

/*
struct SdlCpuGfx : CpuGfxT<SdlCpuGfx>, SdlGfx {
	using NativeFrameBuffer = SDL_Texture*;
	using NativeColorBufferRef = SDL_Texture*;
	using NativeDepthBufferRef = SDL_Texture*;
	
	struct Thread {
		NativeFrameBuffer fb = 0;
		NativeFrameBuffer ctx_default_fb = 0;
	};
	
	static Thread& Local();
	
	#define GFX_CLS(x, g) using x = g##x;
	GFX_CLS_LIST(SdlCpu)
	#undef GFX_CLS
	
	NativeFrameBuffer fb;
	
	static void BindFramebufferEXT(NativeFrameBuffer& fb);
	static void BindTexture(GVar::TextureType type, const NativeFrameBuffer& tex);
	static void BindFramebufferDefault();
	static void RenderScreenRect();
	static void SetContextDefaultFramebuffer(NativeFrameBuffer& fb) {Local().ctx_default_fb = fb;}
	
};
*/

struct SdlCpuGfx : CpuGfxT<SdlCpuGfx>, SdlGfx {
	using SystemFrameBufferRef = SDL_Texture*;
	
	using NativeTexture = SDL_Texture*;
	using NativeSurface = SDL_Surface*;
	//using NativeColorBufferRef = SDL_Texture*;
	using SoftShaderLibrary = SoftShaderLibraryT<SdlCpuGfx>;
	
	#define GFX_CLS(x, g) using x = x##T<g##Gfx>;
	//#define GFX_CLS(x, g) using x = g##x;
	GFX_CLS_LIST(SdlCpu)
	#undef GFX_CLS
	
	static void ActivateNextFrame(NativeDisplay& d, NativeWindow& w, NativeRenderer& r, NativeColorBufferRef color_buf);
	
	static int GetBytesPerPixel(NativeSurface& surf);
	static int GetPitch(NativeSurface& surf);
	static byte* GetData(NativeSurface& surf);
	
	static bool LockTextureToSurface(SoftFramebuffer* tex, Rect r, NativeSurface& surf);
	static void QueryTexture(SoftFramebuffer* tex, uint32& fmt, int& access, int& w, int& h);
	static void UnlockTextureToSurface(SoftFramebuffer* tex);
	
	static bool LockTextureToSurface(NativeTexture& tex, Rect r, NativeSurface& surf);
	static void QueryTexture(NativeTexture& tex, uint32& fmt, int& access, int& w, int& h);
	static void UnlockTextureToSurface(NativeTexture& tex);
	
};

#ifdef flagOGL
struct SdlOglGfx : OglGfxT<SdlOglGfx>, SdlGfx {
	using NativeSurface = void*;
	using SoftShaderLibrary = DummySoftShaderLibraryT<SdlOglGfx>;
	
	#define GFX_CLS(x, g) using x = x##T<g##Gfx>;
	//#define GFX_CLS(x, g) using x = g##x;
	GFX_CLS_LIST(SdlOgl)
	#undef GFX_CLS
	
	static void ActivateNextFrame(NativeDisplay& d, NativeWindow& w, NativeRenderer& r, NativeColorBufferRef color_buf);
	
	static bool LockTextureToSurface(NativeTexture& tex, Rect r, NativeSurface& surf);
	static void QueryTexture(NativeTexture& tex, uint32& fmt, int& access, int& w, int& h);
	
};

	#define SDLOGL_GFXTYPE GFXTYPE(SdlOgl)
	#define SDLOGL_EXCPLICIT_INITIALIZE_CLASS(x) template struct x <SdlOglGfx>;
#else
	#define SDLOGL_GFXTYPE
	#define SDLOGL_EXCPLICIT_INITIALIZE_CLASS(x)
#endif

#define SDL_GFXTYPE \
	SDLOGL_GFXTYPE \
	GFXTYPE(SdlCpu)

#define SDLSW_EXCPLICIT_INITIALIZE_CLASS(x) \
	template struct x <SdlCpuGfx>;

#define SDL_EXCPLICIT_INITIALIZE_CLASS(x) \
	SDLOGL_EXCPLICIT_INITIALIZE_CLASS(x) \
	SDLSW_EXCPLICIT_INITIALIZE_CLASS(x) \
	

#else

#define SDL_GFXTYPE
#define SDLOGL_EXCPLICIT_INITIALIZE_CLASS(x)
#define SDL_EXCPLICIT_INITIALIZE_CLASS(x)
#define SDLSW_EXCPLICIT_INITIALIZE_CLASS(x)

#endif

#if defined flagPOSIX
	#define X11SW_GFXTYPE GFXTYPE(X11Sw)
	#define X11SW_EXCPLICIT_INITIALIZE_CLASS(x) template struct x <X11SwGfx>;
#else
	#define X11SW_GFXTYPE
	#define X11SW_EXCPLICIT_INITIALIZE_CLASS(x)
#endif

#if defined flagPOSIX && defined flagOGL
	#define X11OGL_GFXTYPE GFXTYPE(X11Ogl)
	#define X11OGL_EXCPLICIT_INITIALIZE_CLASS(x) template struct x <X11OglGfx>;
#else
	#define X11OGL_GFXTYPE
	#define X11OGL_EXCPLICIT_INITIALIZE_CLASS(x)
#endif


#define GFXTYPE_LIST \
	 \
	SDL_GFXTYPE \
	X11OGL_GFXTYPE \
	X11SW_GFXTYPE \


#define GFX_EXCPLICIT_INITIALIZE_CLASS(x) \
	 \
	SDL_EXCPLICIT_INITIALIZE_CLASS(x) \
	X11OGL_EXCPLICIT_INITIALIZE_CLASS(x) \
	X11SW_EXCPLICIT_INITIALIZE_CLASS(x) \


#define SOFTREND_EXCPLICIT_INITIALIZE_CLASS(x) \
	 \
	SDLSW_EXCPLICIT_INITIALIZE_CLASS(x) \
	X11SW_EXCPLICIT_INITIALIZE_CLASS(x) \


NAMESPACE_PARALLEL_END

#endif
