#ifndef _Graphics_Types_h_
#define _Graphics_Types_h_

NAMESPACE_TOPSIDE_BEGIN


#define GFX_CLS_LIST(g) \
	GFX_CLS(VertexShaderArgs, g) \
	GFX_CLS(FragmentShaderArgs, g) \
	GFX_CLS(BinderIface, g) \
	GFX_CLS(DataObject, g) \
	GFX_CLS(DataState, g) \
	GFX_CLS(InputState, g) \
	GFX_CLS(Framebuffer, g) \
	GFX_CLS(Compiler, g) \
	GFX_CLS(Linker, g) \
	GFX_CLS(ShaderState, g) \
	GFX_CLS(Shader, g) \
	GFX_CLS(ShaderPipeline, g) \
	GFX_CLS(RuntimeState, g) \
	GFX_CLS(FramebufferStateExt, g) \
	GFX_CLS(ContextState, g) \
	GFX_CLS(Renderer, g) \
	GFX_CLS(StateDraw, g) \
	GFX_CLS(Buffer, g) \


#define GFX_RENDSYS_LIST \
	GFX_RSYS(SdlCpu) \
	GFX_RSYS(SdlOgl) \


#define GFX_CLS(x, g) struct g##x;
#define GFX_RSYS(x) GFX_CLS_LIST(x)
GFX_RENDSYS_LIST
#undef GFX_RSYS
#undef GFX_CLS


struct OglRendererBase {
	static void ClearBuffers();
	static void LeaveFramebuffer();
	static void SetSmoothShading(bool b=true);
	static void SetDepthTest(bool b=true);
	static void SetDepthOrderLess(bool b=true);
	static void SetClearValue(RGBA clr, byte depth);
	static void SetFastPerspectiveCorrection(bool b=true);
	static void SetTriangleBacksideCulling(bool b=true);
	static void SetTriangleFrontsideCCW(bool b=true);
	static void SetViewport(Size sz);
	//static void ActivateNextFrame();
	
};

template <class T>
struct GfxBaseMethod {
	static void ClearBuffers(T& o) {o.ClearBuffers();}
	static void LeaveFramebuffer(T& o) {o.LeaveFramebuffer();}
	static void SetSmoothShading(T& o, bool b=true) {o.SetSmoothShading(b);}
	static void SetDepthTest(T& o, bool b=true) {o.SetDepthTest(b);}
	static void SetDepthOrderLess(T& o, bool b=true) {o.SetDepthOrderLess(b);}
	static void SetClearValue(T& o, RGBA clr, byte depth) {o.SetClearValue(clr, depth);}
	static void SetFastPerspectiveCorrection(T& o, bool b=true) {o.SetFastPerspectiveCorrection(b);}
	static void SetTriangleBacksideCulling(T& o, bool b=true) {o.SetTriangleBacksideCulling(b);}
	static void SetTriangleFrontsideCCW(T& o, bool b=true) {o.SetTriangleFrontsideCCW(b);}
	static void SetViewport(T& o, Size sz) {o.SetViewport(sz);}
	//static void ActivateNextFrame(W& w, T& o) {o.ActivateNextFrame();}
	
};

template <class T, class Parent>
struct GfxBaseStatic : Parent {
	static void ClearBuffers(T&) {Parent::ClearBuffers();}
	static void LeaveFramebuffer(T&) {Parent::LeaveFramebuffer();}
	static void SetSmoothShading(T&, bool b=true) {Parent::SetSmoothShading(b);}
	static void SetDepthTest(T&, bool b=true) {Parent::SetDepthTest(b);}
	static void SetDepthOrderLess(T&, bool b=true) {Parent::SetDepthOrderLess(b);}
	static void SetClearValue(T&, RGBA clr, byte depth) {Parent::SetClearValue(clr, depth);}
	static void SetFastPerspectiveCorrection(T&, bool b=true) {Parent::SetFastPerspectiveCorrection(b);}
	static void SetTriangleBacksideCulling(T&, bool b=true) {Parent::SetTriangleBacksideCulling(b);}
	static void SetTriangleFrontsideCCW(T&, bool b=true) {Parent::SetTriangleFrontsideCCW(b);}
	static void SetViewport(T&, Size sz) {Parent::SetViewport(sz);}
	//static void ActivateNextFrame(R&, T&) {Parent::ActivateNextFrame();}
	
};


struct CpuGfx {
	using NativeTexture = uint32;
	using NativeShader = uint32;
	using NativeColorBuffer = uint32;
	using NativeDepthBuffer = uint32;
	using NativeVertexArray = uint32;
	using NativeVertexBuffer = uint32;
	using NativeElementBuffer = uint32;
	using NativeProgram = uint32;
	using NativePipeline = uint32;
	
	static const ShaderVar::GfxType type = ShaderVar::SW;
	
};

struct OglGfx {
	using NativeTexture = GLuint;
	using NativeShader = GLuint;
	using NativeColorBuffer = GLuint;
	using NativeDepthBuffer = GLuint;
	using NativeFrameBuffer = GLuint;
	using NativeVertexArray = GLuint;
	using NativeVertexBuffer = GLuint;
	using NativeElementBuffer = GLuint;
	using NativeProgram = GLuint;
	using NativePipeline = GLuint;
	
	static const ShaderVar::GfxType type = ShaderVar::OGL;
	
};


struct SdlGfx : GfxBaseStatic<SDL_Renderer, OglRendererBase> {
	using NativeWindow = SDL_Window;
	using NativeRenderer = SDL_Renderer;
	
	static void ActivateNextFrame(NativeWindow& w, NativeRenderer& r);
};

struct SdlCpuGfx : CpuGfx, SdlGfx {
	using NativeFrameBuffer = SDL_Texture*;
	
	#define GFX_CLS(x, g) using x = g##x;
	GFX_CLS_LIST(SdlCpu)
	#undef GFX_CLS
	
};

struct SdlOglGfx : OglGfx, SdlGfx {
	#define GFX_CLS(x, g) using x = g##x;
	GFX_CLS_LIST(SdlOgl)
	#undef GFX_CLS
	
};




NAMESPACE_TOPSIDE_END

#endif
