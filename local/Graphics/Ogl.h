#ifndef _Graphics_Ogl_h_
#define _Graphics_Ogl_h_

NAMESPACE_TOPSIDE_BEGIN


int GetOglChCode(int channels, bool is_float=false);


struct OglFramebufferState;
struct OglDataObject;



struct OglVertexShaderArgs {
	OglFramebufferState& state;
	OglDataObject& obj;
	const vec3& pos;
	const vec3& normal;
	const vec2& tex_coords;
	vec4& pos_out;
	vec2& tex_coord_out;
};

struct OglFragmentShaderArgs {
	
};







struct OglStateDraw : StateDrawT<OglGfx> {RTTI_DECL1(OglStateDraw, Base)};
struct OglFramebuffer : FramebufferT<OglGfx> {RTTI_DECL1(OglFramebuffer, Base)};


struct SdlOglRenderer : public RendererT<SdlOglGfx> {
	RTTI_DECL1(SdlOglRenderer, Base)
};


class SdlOglDrawFramebuffer : public DrawFramebufferT<SdlOglGfx> {
public:
	RTTI_DECL1(SdlOglDrawFramebuffer, Base)
	
};

struct OglDataObject : DataObjectT<OglGfx> {
	RTTI_DECL1(OglDataObject, Base)
	
    OglDataObject() {}
    ~OglDataObject() {FreeOgl();}
    void FreeOgl();
    void Paint() override;
    void MakeTexture(int tex_id, int w, int h, int pitch, int stride, const Vector<byte>& data) override;
    
};

struct OglInputState : FramebufferInputStateT<OglGfx> {
	RTTI_DECL1(OglInputState, Base)
	
};

struct OglShaderState : ShaderStateT<OglGfx> {
	RTTI_DECL1(OglShaderState, Base)
	
};

/*struct OglFramebufferState : FramebufferT<OglGfx> {
	RTTI_DECL1(OglFramebufferState, Base)
	
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
	//OglShader(OglFramebufferState& s) {state = &s;}
	
};

struct OglShaderPipeline : ShaderPipelineT<OglGfx>
{
	RTTI_DECL1(OglShaderPipeline, Base)
	
};

struct OglCompiler : GfxCompilerT<OglGfx> {
	RTTI_DECL1(OglCompiler, Base)
	
	OglCompiler();
	bool CompileShader(String code, ShaderVar::Type type, GLuint& shader_out);
	bool Compile(OglFramebufferState& fb_state, OglShaderState& shd_state, ShaderVar::Type type, String code, String library);
	
	static void HotfixWebGLSL(String& s);
};

struct OglLinker : GfxLinkerT<OglGfx> {
	RTTI_DECL1(OglLinker, Base)
	
	bool Link(OglFramebufferState& fb_state);
	
};

struct OglBuffer : BufferT<OglGfx> {
	RTTI_DECL1(OglBuffer, Base)
	
	
};


NAMESPACE_TOPSIDE_END

#endif
