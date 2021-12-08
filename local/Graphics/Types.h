#ifndef _Graphics_Types_h_
#define _Graphics_Types_h_

NAMESPACE_TOPSIDE_BEGIN


class CpuMemFramebuffer;
class CpuMemBuffer;

class OglDataState;
class OglDataObject;

class OglFramebuffer;
class OglFramebufferState;
class OglBuffer;
class OglShaderState;
class OglInputState;
class OglDataObject;
class OglVertexShaderArgs;
class OglFragmentShaderArgs;
class OglShader;
class OglShaderPipeline;
class OglCompiler;
class OglLinker;

class SdlCpuRenderer;
class SdlOglRenderer;

struct CpuGfx {
	using Framebuffer = CpuMemFramebuffer;
	using Buffer = CpuMemBuffer;
	
	using NativeFramebuffer = uint32;
	using NativeTexture = int32;
	using NativeShader = uint32;
	using NativeColorBuffer = uint32;
	using NativeDepthBuffer = uint32;
	using NativeFrameBuffer = uint32;
	using NativeProgram = uint32;
	using NativePipeline = uint32;
	
	static const ShaderVar::GfxType type = ShaderVar::SW;
	
};

struct OglGfx {
	// State
	using DataState = OglDataState;
	using DataObject = OglDataObject;
	// Framebuffer
	// Runtime
	// Context
	// Utils
	using Framebuffer = OglFramebuffer;
	using FramebufferState = OglFramebufferState;
	using Buffer = OglBuffer;
	using Shader = OglShader;
	using ShaderState = OglShaderState;
	using ShaderPipeline = OglShaderPipeline;
	using InputState = OglInputState;
	using BinderIface = BinderIfaceOgl;
	using VertexShaderArgs = OglVertexShaderArgs;
	using FragmentShaderArgs = OglFragmentShaderArgs;
	using Compiler = OglCompiler;
	using Linker = OglLinker;
	
	using NativeFramebuffer = GLuint;
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

struct SdlGfx : GfxBaseStatic<SDL_Renderer, OglRendererBase> {
	using NativeWindow = SDL_Window;
	using NativeRenderer = SDL_Renderer;
	
	static void ActivateNextFrame(NativeWindow& w, NativeRenderer& r);
};

struct SdlCpuGfx : CpuGfx, SdlGfx {
	using Renderer = SdlCpuRenderer;
	
};

struct SdlOglGfx : OglGfx, SdlGfx {
	using Renderer = SdlOglRenderer;
	
};


NAMESPACE_TOPSIDE_END

#endif
