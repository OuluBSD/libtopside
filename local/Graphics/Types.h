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


/*struct OglRendererBase {
	
};




template <class T>
struct GfxBaseMethod {
	static void ClearBuffers(T& o) {o.ClearBuffers();}
	//static void LeaveFramebuffer(T& o) {o.LeaveFramebuffer();}
	//template <class Pipe, class Prog> static void EnterPipelineProgram(T& o, Pipe& pipeline, Prog& prog) {o.EnterPipelineProgram(pipeline, prog);}
	static void SetSmoothShading(T& o, bool b=true) {o.SetSmoothShading(b);}
	static void SetDepthTest(T& o, bool b=true) {o.SetDepthTest(b);}
	static void SetDepthOrderLess(T& o, bool b=true) {o.SetDepthOrderLess(b);}
	static void SetClearValue(T& o, RGBA clr, byte depth) {o.SetClearValue(clr, depth);}
	static void SetFastPerspectiveCorrection(T& o, bool b=true) {o.SetFastPerspectiveCorrection(b);}
	static void SetTriangleBacksideCulling(T& o, bool b=true) {o.SetTriangleBacksideCulling(b);}
	static void SetTriangleFrontsideCCW(T& o, bool b=true) {o.SetTriangleFrontsideCCW(b);}
	static void SetViewport(T& o, Size sz) {o.SetViewport(sz);}
	//static void ActivateNextFrame(W& w, T& o) {o.ActivateNextFrame();}
	static void SetDebugOutput(T& o, bool b=true) {o.SetDebugOutput(b);}
	
};

template <class T, class Parent>
struct GfxBaseStatic : Parent {
	static void ClearBuffers(T&) {Parent::ClearBuffers();}
	//static void LeaveFramebuffer(T&) {Parent::LeaveFramebuffer();}
	//template <class Pipe, class Prog> static void EnterPipelineProgram(T&, Pipe& pipeline, Prog& prog) {Parent::EnterPipelineProgram(pipeline, prog);}
	static void SetSmoothShading(T&, bool b=true) {Parent::SetSmoothShading(b);}
	static void SetDepthTest(T&, bool b=true) {Parent::SetDepthTest(b);}
	static void SetDepthOrderLess(T&, bool b=true) {Parent::SetDepthOrderLess(b);}
	static void SetClearValue(T&, RGBA clr, byte depth) {Parent::SetClearValue(clr, depth);}
	static void SetFastPerspectiveCorrection(T&, bool b=true) {Parent::SetFastPerspectiveCorrection(b);}
	static void SetTriangleBacksideCulling(T&, bool b=true) {Parent::SetTriangleBacksideCulling(b);}
	static void SetTriangleFrontsideCCW(T&, bool b=true) {Parent::SetTriangleFrontsideCCW(b);}
	static void SetViewport(T&, Size sz) {Parent::SetViewport(sz);}
	//static void ActivateNextFrame(R&, T&) {Parent::ActivateNextFrame();}
	static void SetDebugOutput(T&, bool b=true) {Parent::SetDebugOutput(b);}
	
};*/


namespace GVar {

typedef enum {
	DRAW_FRAMEBUFFER,
	READ_FRAMEBUFFER,
} FramebufferTarget;

typedef enum : uint32 {
	COLOR0_EXT		= 1 << 0
} RenderTarget;

typedef enum : uint32 {
	TEXTURE_INVALID,
	TEXTURE_3D,
	TEXTURE_CUBE_MAP,
	TEXTURE_2D,
} TextureType;

typedef enum : uint32 {
	PROGRAM_SEPARABLE,
} ParamType;

#define GVAR_PARAMTYPE_LIST \
	PARAM_TYPE(PROGRAM_SEPARABLE)
	
typedef enum : uint32 {
	ACTIVE_UNIFORMS,
} ProgParamType;

#define GVAR_PROGPARAMTYPE_LIST \
	PARAM_TYPE(ACTIVE_UNIFORMS)

typedef enum : uint32 {
	COLOR_BUFFER,
	DEPTH_BUFFER,
	STENCIL_BUFFER,
} BufferType;

#define GVAR_BUFFERTYPE_LIST \
	BUFFER_TYPE(COLOR_BUFFER) \
	BUFFER_TYPE(DEPTH_BUFFER) \
	BUFFER_TYPE(STENCIL_BUFFER)
}


struct CpuGfx {
	using NativeTexture = uint32;
	using NativeShader = uint32;
	/*using NativeColorBuffer = uint32;
	using NativeDepthBuffer = uint32;
	using NativeFrameBuffer = uint32;*/
	using NativeVertexArray = uint32;
	using NativeVertexBuffer = uint32;
	using NativeElementBuffer = uint32;
	using NativeProgram = uint32;
	using NativePipeline = uint32;
	
	static const GVar::GfxType Type = GVar::SW;
	
	static void BindProgramPipeline(NativePipeline& pipeline);
	static void UseProgram(NativeProgram& prog);
	static void UnbindProgramPipeline();
	static const char* GetShaderTemplate();
	static void HotfixShaderCode(String& s);
	static void DrawBuffers(GVar::RenderTarget tgt);
	static void ActiveTexture(int ch);
	static bool CreateShader(GVar::ShaderType t, NativeShader& new_shdr);
	static void ShaderSource(NativeShader& s, String code);
	static bool CompileShader(NativeShader& s);
	static String GetLastErrorS(NativeShader& s);
	static String GetLastErrorP(NativeProgram& s);
	static void CreateProgram(NativeProgram& prog);
	static void ProgramParameteri(NativeProgram& prog, GVar::ParamType type, int i);
	static void AttachShader(NativeProgram& prog, NativeShader& shdr);
	static void DeleteShader(NativeShader& shdr);
	static bool LinkProgram(NativeProgram& prog);
	static void GetProgramiv(NativeProgram& prog, GVar::ProgParamType type, int& out);
	static String GetActiveUniform(NativeProgram& prog, int i, int* size_out=0, int* type_out=0);
	static void Clear(GVar::BufferType type);
	static void GenProgramPipeline(NativePipeline& pipe);
	static void UseProgramStages(NativePipeline& pipe, uint32 shader_type_bmask, NativeProgram& prog);
	static void DeleteProgramPipeline(NativePipeline& pipe);
	static void TexParameteri(int type, GVar::Filter filter, GVar::Wrap repeat);
	
	static void Uniform1i(int idx, int f);
	static void Uniform1f(int idx, float f);
	static void Uniform2f(int idx, float f0, float f1);
	static void Uniform3f(int idx, float f0, float f1, float f2);
	static void Uniform4f(int idx, float f0, float f1, float f2, float f3);
	
	
	static void ClearBuffers();
	static void SetSmoothShading(bool b=true);
	static void SetDepthTest(bool b=true);
	static void SetDepthOrderLess(bool b=true);
	static void SetClearValue(RGBA clr, byte depth);
	static void SetFastPerspectiveCorrection(bool b=true);
	static void SetTriangleBacksideCulling(bool b=true);
	static void SetTriangleFrontsideCCW(bool b=true);
	static void SetViewport(Size sz);
	//static void ActivateNextFrame();
	static void SetDebugOutput(bool b=true);
	
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
	
	static const GVar::GfxType Type = GVar::OGL;
	
	static void BindProgramPipeline(NativePipeline& pipeline);
	static void UseProgram(NativeProgram& prog);
	//static void EnterFramebuffer(NativeFrameBuffer& fb);
	static void BindFramebufferEXT(NativeFrameBuffer& fb);
	static void UnbindProgramPipeline();
	static void UnbindFramebuffer();
	static void DrawBuffers(GVar::RenderTarget tgt);
	//static void SetRender_Color();
	static void RenderScreenRect();
	static const char* GetShaderTemplate();
	static void HotfixShaderCode(String& s);
	static void ActiveTexture(int ch);
	static void BindTexture(GVar::TextureType type, const NativeFrameBuffer& tex);
	static bool CreateShader(GVar::ShaderType t, NativeShader& new_shdr);
	static void ShaderSource(NativeShader& s, String code);
	static bool CompileShader(NativeShader& s);
	static String GetLastErrorS(NativeShader& s);
	static String GetLastErrorP(NativeProgram& s);
	static void CreateProgram(NativeProgram& prog);
	static void ProgramParameteri(NativeProgram& prog, GVar::ParamType type, int i);
	static void AttachShader(NativeProgram& prog, NativeShader& shdr);
	static void DeleteShader(NativeShader& shdr);
	static bool LinkProgram(NativeProgram& prog);
	static void GetProgramiv(NativeProgram& prog, GVar::ProgParamType type, int& out);
	static String GetActiveUniform(NativeProgram& prog, int i, int* size_out=0, int* type_out=0);
	static void Clear(GVar::BufferType type);
	static void GenProgramPipeline(NativePipeline& pipe);
	static void UseProgramStages(NativePipeline& pipe, uint32 shader_type_bmask, NativeProgram& prog);
	static void DeleteProgramPipeline(NativePipeline& pipe);
	static void TexParameteri(int type, GVar::Filter filter, GVar::Wrap repeat);
	
	static void Uniform1i(int idx, int i) {glUniform1i(idx, i);}
	static void Uniform1f(int idx, float f) {glUniform1f(idx, f);}
	static void Uniform2f(int idx, float f0, float f1) {glUniform2f(idx, f0, f1);}
	static void Uniform3f(int idx, float f0, float f1, float f2) {glUniform3f(idx, f0, f1, f2);}
	static void Uniform4f(int idx, float f0, float f1, float f2, float f3) {glUniform4f(idx, f0, f1, f2, f3);}
	
	
	static void ClearBuffers();
	static void SetSmoothShading(bool b=true);
	static void SetDepthTest(bool b=true);
	static void SetDepthOrderLess(bool b=true);
	static void SetClearValue(RGBA clr, byte depth);
	static void SetFastPerspectiveCorrection(bool b=true);
	static void SetTriangleBacksideCulling(bool b=true);
	static void SetTriangleFrontsideCCW(bool b=true);
	static void SetViewport(Size sz);
	//static void ActivateNextFrame();
	static void SetDebugOutput(bool b=true);
	
};



struct SdlGfx {
	using NativeWindow = SDL_Window;
	using NativeRenderer = SDL_Renderer;
	
	static void ActivateNextFrame(NativeWindow& w, NativeRenderer& r);
	static Size GetWindowSize(NativeWindow& win);
	
};

struct SdlCpuGfx : CpuGfx, SdlGfx {
	using NativeFrameBuffer = SDL_Texture*;
	using NativeColorBuffer = SDL_Texture*;
	using NativeDepthBuffer = SDL_Texture*;
	
	#define GFX_CLS(x, g) using x = g##x;
	GFX_CLS_LIST(SdlCpu)
	#undef GFX_CLS
	
	//static void EnterFramebuffer(NativeFrameBuffer& fb) {TODO}
	static void BindFramebufferEXT(NativeFrameBuffer& fb) {TODO}
	static void BindTexture(GVar::TextureType type, const NativeFrameBuffer& tex) {TODO}
	static void UnbindFramebuffer() {TODO}
	//static void SetRender_Color() {TODO}
	//static void Clear_Color() {TODO}
	static void RenderScreenRect() {TODO}
	
};

struct SdlOglGfx : OglGfx, SdlGfx {
	#define GFX_CLS(x, g) using x = g##x;
	GFX_CLS_LIST(SdlOgl)
	#undef GFX_CLS
	
};


#define GFXTYPE_LIST \
	GFXTYPE(SdlCpuGfx) \
	GFXTYPE(SdlOglgfx)

#define GFX_EXCPLICIT_INITIALIZE_CLASS(x) \
	template struct x <SdlCpuGfx>; \
	template struct x <SdlOglGfx>;


NAMESPACE_TOPSIDE_END

#endif
