#ifndef _IGraphics_Ogl_h_
#define _IGraphics_Ogl_h_

NAMESPACE_TOPSIDE_BEGIN


#define GFX_CLS(x, g) struct g##x : x##T<g##Gfx> {RTTI_DECL1(g##x, Base)};

#ifdef flagSDL2
GFX_CLS_LIST(SdlOgl)
#endif

#undef GFX_CLS


// default frame TODO should be conditional
using OglStateDraw		= SdlOglStateDraw;
using OglDataState		= SdlOglDataState;
using OglShaderPipeline	= SdlOglShaderPipeline;
//using OglShader			= SdlOglShader;
using OglFramebuffer	= SdlOglFramebuffer;
using OglBuffer			= SdlOglBuffer;
//using OglBinderIface	= SdlOglBinderIface;
using OglDataObject		= SdlOglDataObject;


#ifdef flagSDL2
using OglBufferT		= BufferT<SdlOglGfx>;
#endif

int GetOglChCode(int channels, bool is_float=false);


#if 0
struct OglVertexShaderArgs {
	OglFramebuffer& state;
	OglDataObject& obj;
	const vec3& pos;
	const vec3& normal;
	const vec2& tex_coords;
	vec4& pos_out;
	vec2& tex_coord_out;
};

struct OglFragmentShaderArgs {
	
};

using OglCpuVertexShaderArgs = OglVertexShaderArgs;
using OglCpuFragmentShaderArgs = OglFragmentShaderArgs;






struct OglFramebuffer;
struct OglDataObject;

struct OglStateDraw : StateDrawT<OglGfx> {RTTI_DECL1(OglStateDraw, Base)};
struct OglFramebuffer : FramebufferT<OglGfx> {RTTI_DECL1(OglFramebuffer, Base)};


struct SdlOglRenderer : public RendererT<SdlOglGfx> {
	RTTI_DECL1(SdlOglRenderer, Base)
};


/*class SdlOglDrawFramebuffer : public DrawFramebufferT<SdlOglGfx> {
public:
	RTTI_DECL1(SdlOglDrawFramebuffer, Base)
	
};*/

struct OglDataObject : DataObjectT<OglGfx> {
	RTTI_DECL1(OglDataObject, Base)
	
    OglDataObject() {}
    ~OglDataObject() {FreeOgl();}
    void FreeOgl();
    void Paint() override;
    void MakeTexture(int tex_id, int w, int h, int pitch, int stride, const Vector<byte>& data) override {TODO}
    void Refresh(Mesh& m) override;
};

struct OglDataState : DataStateT<OglGfx> {RTTI_DECL1(OglDataState, Base)};

struct OglInputState : InputStateT<OglGfx> {
	RTTI_DECL1(OglInputState, Base)
	
};

struct OglShaderState : ShaderStateT<OglGfx> {
	RTTI_DECL1(OglShaderState, Base)
	
};

/*struct OglFramebuffer : FramebufferT<OglGfx> {
	RTTI_DECL1(OglFramebuffer, Base)
	
	GLint GetGlType() const;
	GLint GetGlFormat() const;
	int GetGlSize() const;
	int GetGlSampleSize() const;
	
};
*/
struct OglShader : ShaderT<OglGfx>
{
	RTTI_DECL1(OglShader, Base)
	
	OglShader() {}
	//OglShader(OglFramebuffer& s) {state = &s;}
	
};

struct OglShaderPipeline : ShaderPipelineT<OglGfx>
{
	RTTI_DECL1(OglShaderPipeline, Base)
	
};

struct OglCompiler : CompilerT<OglGfx> {
	RTTI_DECL1(OglCompiler, Base)
	
	OglCompiler();
	bool CompileShader(String code, GVar::ShaderType type, GLuint& shader_out);
	bool Compile(const OglContextState& ctx, OglRuntimeState& rt_state, OglFramebuffer& fb_state, OglShaderState& shd_state, GVar::ShaderType type);
	
	static void HotfixWebGLSL(String& s);
};

struct OglLinker : LinkerT<OglGfx> {
	RTTI_DECL1(OglLinker, Base)
	
	bool Link(OglRuntimeState& rt_state);
	
};

struct OglRuntimeState : RuntimeStateT<OglGfx> {RTTI_DECL1(OglRuntimeState, Base)};
struct OglContextState : ContextStateT<OglGfx> {RTTI_DECL1(OglContextState, Base)};

struct OglBuffer : BufferT<OglGfx> {
	RTTI_DECL1(OglBuffer, Base)
	
	
};

#endif

NAMESPACE_TOPSIDE_END

#endif
