#ifndef _IGraphics_Types_h_
#define _IGraphics_Types_h_

NAMESPACE_TOPSIDE_BEGIN

namespace GVar {

typedef enum : uint32 {
	COLOR0_EXT		= 1 << 0
} RenderTarget;

}

NAMESPACE_TOPSIDE_END



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


#define GFX_CLS(x, g) struct g##x;
#define GFX_RSYS(x) GFX_CLS_LIST(x)
GFX_RENDSYS_LIST
#undef GFX_RSYS
#undef GFX_CLS





template <class Backend>
struct CpuGfxT {
	using SoftRend			= SoftRendT<Backend>;
	using SoftCompiler		= SoftCompilerT<Backend>;
	using SoftShader		= SoftShaderT<Backend>;
	using SoftProgram		= SoftProgramT<Backend>;
	using SoftFramebuffer	= SoftFramebufferT<Backend>;
	using SoftPipeline		= SoftPipelineT<Backend>;
	// using SoftVertexArray	= SoftVertexArrayT<Backend>;
	
	struct Thread {
		SoftRend rend;
		SoftCompiler comp;
		SoftShader* shdr = 0;
		SoftProgram* prog = 0;
		SoftFramebuffer* fb = 0;
		SoftFramebuffer* ctx_default_fb = 0;
		SoftPipeline* pipe = 0;
		SoftVertexArray* vao = 0;
		
		struct Tex {
			const SoftFramebuffer* r = 0;
			SoftFramebuffer* rw = 0;
			
			const SoftFramebuffer* GetReadTexture() const {return r ? r : rw;}
		};
		Tex texture[CHANNEL_COUNT];
		int active_texture = -1;
		
		Tex& T() {
			ASSERT(active_texture >= 0 && active_texture < CHANNEL_COUNT);
			return texture[active_texture];
		}
	};
	
	static Thread& Local();
	static SoftRend& Rend();
	
	using NativeTexture = uint32;
	using NativeShader = SoftShader;
	using NativeColorBuffer = SoftFramebuffer;
	using NativeDepthBuffer = SoftFramebuffer;
	using NativeFrameBuffer = SoftFramebuffer;
	// using SystemFrameBuffer = SDL_Texture*;
	using NativeVertexArray = SoftVertexArray;
	using NativeVertexBuffer = SoftVertexBuffer;
	using NativeElementBuffer = SoftElementBuffer;
	using NativeProgram = SoftProgram;
	using NativePipeline = SoftPipeline;
	using ValFormat = Parallel::VideoFormat;
	
	static const GVar::GfxType Type = GVar::SW;
	
	static void BindProgramPipeline(NativePipeline& pipeline);
	static void UseProgram(NativeProgram& prog);
	static void UnbindProgramPipeline();
	static const char* GetShaderTemplate(GVar::ShaderType t);
	static void HotfixShaderCode(String& s);
	static void DrawBuffers(GVar::RenderTarget tgt);
	static void ActiveTexture(int ch);
	static bool CreateShader(GVar::ShaderType t, NativeShader& new_shdr);
	static void ShaderSource(NativeShader& s, String code);
	static bool CompileShader(NativeShader& s);
	static String GetLastErrorS(NativeShader& s);
	static String GetLastErrorP(NativeProgram& s);
	static bool CreateProgram(NativeProgram& prog);
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
	static void TexParameteri(GVar::TextureType type, GVar::Filter filter, GVar::Wrap repeat);
	static bool GenTexture(NativeFrameBuffer& fb);
	static void GenVertexArray(NativeVertexArray& vao);
	static void GenVertexBuffer(NativeVertexBuffer& vbo);
	static void GenElementBuffer(NativeElementBuffer& ebo);
	static void BindVertexArray(NativeVertexArray& vao);
	static void BindVertexBuffer(NativeVertexBuffer& vbo);
	static void BindElementBuffer(NativeElementBuffer& ebo);
	static void VertexBufferData(const Vector<Vertex>& vtx);
	static void ElementBufferData(const Vector<uint32>& el);
	static void SetupVertexStructure() {}
	static void UnbindVertexArray();
	static void UnbindVertexBuffer();
	static void UnbindElementBuffer();
	static void ActivateVertexStructure() {}
	static void DeactivateVertexStructure() {}
	static void DrawVertexElements(int element_limit);
	static void TexImage2D(Texture& tex);
	static void DeleteVertexArray(NativeVertexArray& vao);
	static void DeleteVertexBuffer(NativeVertexBuffer& vbo);
	static void DeleteElementBuffer(NativeElementBuffer& ebo);
	static void DeleteTexture(NativeColorBuffer& b);
	
	static void Uniform1i(int idx, int f);
	static void Uniform1f(int idx, float f);
	static void Uniform2f(int idx, float f0, float f1);
	static void Uniform3f(int idx, float f0, float f1, float f2);
	static void Uniform4f(int idx, float f0, float f1, float f2, float f3);
	static void UniformMatrix4fv(int idx, const mat4& mat);
	
	
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
	
	
	static void BindFramebufferEXT(NativeFrameBuffer& fb);
	static void BindTextureRO(GVar::TextureType type, const NativeFrameBuffer& tex);
	static void BindTextureRW(GVar::TextureType type, NativeFrameBuffer& tex);
	static void UnbindTexture(GVar::TextureType type);
	static void GenerateMipmap(GVar::TextureType type);
	static void BindFramebufferDefault();
	static void RenderScreenRect();
	static void SetContextDefaultFramebuffer(NativeFrameBuffer& fb);
	static void BeginRender();
	static void EndRender();
	
	// static Serial::VideoFormat& GetFormat(Parallel::Format& fmt);
	
};

#ifdef flagOGL
struct OglGfx {
	using NativeTexture = GLuint;
	using NativeShader = GLuint;
	using NativeColorBuffer = GLuint;
	using NativeDepthBuffer = GLuint;
	using NativeFrameBuffer = GLuint;
	using NativeBuffer = GLuint;
	using SystemFrameBuffer = NativeFrameBuffer;
	using NativeVertexArray = GLuint;
	using NativeVertexBuffer = GLuint;
	using NativeElementBuffer = GLuint;
	using NativeProgram = GLuint;
	using NativePipeline = GLuint;
	using ValFormat = Serial::FboFormat;
	
	static const GVar::GfxType Type = GVar::OGL;
	
	static void BindProgramPipeline(NativePipeline& pipeline);
	static void UseProgram(NativeProgram& prog);
	//static void EnterFramebuffer(NativeFrameBuffer& fb);
	static void BindFramebufferEXT(NativeFrameBuffer& fb);
	static void UnbindProgramPipeline();
	static void BindFramebufferDefault();
	static void DrawBuffers(GVar::RenderTarget tgt);
	//static void SetRender_Color();
	static void RenderScreenRect();
	static const char* GetShaderTemplate(GVar::ShaderType t);
	static void HotfixShaderCode(String& s);
	static void ActiveTexture(int ch);
	static void BindTextureRO(GVar::TextureType type, const NativeFrameBuffer& tex);
	static void BindTextureRW(GVar::TextureType type, NativeFrameBuffer& tex);
	static void UnbindTexture(GVar::TextureType type);
	static void GenerateMipmap(GVar::TextureType type);
	static bool CreateShader(GVar::ShaderType t, NativeShader& new_shdr);
	static void ShaderSource(NativeShader& s, String code);
	static bool CompileShader(NativeShader& s);
	static String GetLastErrorS(NativeShader& s);
	static String GetLastErrorP(NativeProgram& s);
	static bool CreateProgram(NativeProgram& prog);
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
	static void TexParameteri(GVar::TextureType type, GVar::Filter filter, GVar::Wrap repeat);
	static bool GenTexture(NativeFrameBuffer& fb);
	static void GenVertexArray(NativeVertexArray& vao);
	static void GenVertexBuffer(NativeVertexBuffer& vbo);
	static void GenElementBuffer(NativeElementBuffer& ebo);
	static void BindVertexArray(NativeVertexArray& vao);
	static void BindVertexBuffer(NativeVertexBuffer& vbo);
	static void BindElementBuffer(NativeElementBuffer& ebo);
	static void DeleteVertexArray(NativeVertexArray& vao);
	static void DeleteVertexBuffer(NativeVertexBuffer& vbo);
	static void DeleteElementBuffer(NativeElementBuffer& ebo);
	static void VertexBufferData(const Vector<Vertex>& vtx);
	static void ElementBufferData(const Vector<uint32>& el);
	static void SetupVertexStructure();
	static void UnbindVertexArray();
	static void UnbindVertexBuffer();
	static void UnbindElementBuffer();
	static void ActivateVertexStructure();
	static void DeactivateVertexStructure();
	static void DrawVertexElements(int element_limit);
	static void TexImage2D(Texture& tex);
	static void DeleteTexture(NativeColorBuffer& b);
	
	static void Uniform1i(int idx, int i) {glUniform1i(idx, i);}
	static void Uniform1f(int idx, float f) {glUniform1f(idx, f);}
	static void Uniform2f(int idx, float f0, float f1) {glUniform2f(idx, f0, f1);}
	static void Uniform3f(int idx, float f0, float f1, float f2) {glUniform3f(idx, f0, f1, f2);}
	static void Uniform4f(int idx, float f0, float f1, float f2, float f3) {glUniform4f(idx, f0, f1, f2, f3);}
	static void UniformMatrix4fv(int idx, const mat4& mat);
	
	
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
	static void SetContextDefaultFramebuffer(NativeFrameBuffer& fb) {/* done by opengl*/}
	static void BeginRender() {}
	static void EndRender() {}
	
	static Serial::FboFormat& GetFormat(Parallel::Format& fmt);
	
};
#endif


#ifdef flagPOSIX
struct X11Gfx {
	using NativeDisplay			= ::Display*;
	using NativeWindow			= ::Window;
	using NativeRenderer		= void*;
	using NativeRendererInfo	= void*;
	using NativeGLContext		= ::GLXContext;
	
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

#ifdef flagOGL
struct X11OglGfx : OglGfx, X11Gfx {
	#define GFX_CLS(x, g) using x = g##x;
	GFX_CLS_LIST(X11Ogl)
	#undef GFX_CLS
	
	static void ActivateNextFrame(NativeWindow& w, NativeRenderer& r, NativeFrameBuffer& color_buf);
	
};
#endif
#endif


#ifdef flagSDL2
struct SdlGfx {
	using NativeWindow			= SDL_Window;
	using NativeRenderer		= SDL_Renderer;
	using NativeRendererInfo	= SDL_RendererInfo;
	using NativeGLContext		= SDL_GLContext;
	
	static Size GetWindowSize(NativeWindow& win);
	static bool CreateWindowAndRenderer(Size screen_sz, dword flags, NativeWindow& win, NativeRenderer& rend);
	static void SetTitle(NativeDisplay& display, NativeWindow& win, String title);
	static void SetWindowFullscreen(NativeWindow& win, bool b=true);
	static void DestroyRenderer(NativeRenderer& rend);
	static void DestroyWindow(NativeWindow& win);
	static void DeleteContext(GLContext& ctx);
	static void MaximizeWindow(NativeWindow& win);
	static void RestoreWindow(NativeWindow& win);
	static void SetWindowPosition(NativeWindow& win, Point pt);
	static void SetWindowSize(NativeWindow& win, Size sz);
	
};

/*struct SdlCpuGfx : CpuGfx, SdlGfx {
	using NativeFrameBuffer = SDL_Texture*;
	using NativeColorBuffer = SDL_Texture*;
	using NativeDepthBuffer = SDL_Texture*;
	
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
	
};*/

struct SdlCpuGfx : CpuGfx, SdlGfx {
	#define GFX_CLS(x, g) using x = g##x;
	GFX_CLS_LIST(SdlCpu)
	#undef GFX_CLS
	
	static void ActivateNextFrame(NativeWindow& w, NativeRenderer& r, NativeFrameBuffer& color_buf);
	
};

#ifdef flagOGL
struct SdlOglGfx : OglGfx, SdlGfx {
	#define GFX_CLS(x, g) using x = g##x;
	GFX_CLS_LIST(SdlOgl)
	#undef GFX_CLS
	
	static void ActivateNextFrame(NativeWindow& w, NativeRenderer& r, NativeFrameBuffer& color_buf);
	
};
#define SDLOGL_GFXTYPE GFXTYPE(SdlOglGfx)
#define SDLOGL_EXCPLICIT_INITIALIZE_CLASS(x) template struct x <SdlOglGfx>;

#else
	#define SDLOGL_GFXTYPE
	#define SDLOGL_EXCPLICIT_INITIALIZE_CLASS(x)
#endif

#define SDL_GFXTYPE \
	SDLOGL_GFXTYPE \
	GFXTYPE(SdlCpuGfx)

#define SDL_EXCPLICIT_INITIALIZE_CLASS(x) \
	SDLOGL_EXCPLICIT_INITIALIZE_CLASS(x) \
	template struct x <SdlCpuGfx>;

#else

#define SDL_GFXTYPE
#define SDL_EXCPLICIT_INITIALIZE_CLASS(x)

#endif

#ifdef flagPOSIX
	#define POSIX_GFXTYPE \
		GFXTYPE(X11OglGfx)
	#define POSIX_EXCPLICIT_INITIALIZE_CLASS(x) \
		template struct x <X11OglGfx>;
#else
	#define POSIX_GFXTYPE
	#define POSIX_EXCPLICIT_INITIALIZE_CLASS(x)
#endif


#define GFXTYPE_LIST \
	 \
	SDL_GFXTYPE \
	POSIX_GFXTYPE \


#define GFX_EXCPLICIT_INITIALIZE_CLASS(x) \
	 \
	SDL_EXCPLICIT_INITIALIZE_CLASS(x) \
	POSIX_EXCPLICIT_INITIALIZE_CLASS(x) \


NAMESPACE_PARALLEL_END

#endif
