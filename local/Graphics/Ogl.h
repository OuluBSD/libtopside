#ifndef _Graphics_Ogl_h_
#define _Graphics_Ogl_h_

NAMESPACE_TOPSIDE_BEGIN


int GetOglChCode(int channels, bool is_float=false);


struct OglFramebufferState;
struct OglFramebufferObject;



struct OglVertexShaderArgs {
	OglFramebufferState& state;
	OglFramebufferObject& obj;
	const vec3& pos;
	const vec3& normal;
	const vec2& tex_coords;
	vec4& pos_out;
	vec2& tex_coord_out;
};

struct OglFragmentShaderArgs {
	
};



class OglFramebuffer : public FramebufferT<OglGfx> {
	
public:
	bool locked = false;
	
public:
	typedef OglFramebuffer CLASSNAME;
	OglFramebuffer();
	~OglFramebuffer() {Clear();}
	
	bool Create(int w, int h, int channels=3) override;
	void Enter() override {ASSERT(!locked); locked = true;}
	void Leave() override {ASSERT(locked);  locked = false;}
	byte* GetIterator(int x, int y) override {Panic("Not usable: OglFramebuffer::GetIterator"); return 0;}
	void DrawFill(const byte* mem, int sz) override {TODO}
	
	void Bind();
	void Clear();
	void Render();
};


class SdlOglRenderer : public RendererT<SdlOglGfx> {
	
public:
	void PreFrame() override;
	void PostFrame() override;
	
};


class SdlOglDrawFramebuffer : public DrawFramebufferT<SdlOglGfx> {
public:
	RTTI_DECL1(SdlOglDrawFramebuffer, Base)
	
};

struct OglFramebufferObject : FramebufferObjectT<OglGfx> {
	RTTI_DECL1(OglFramebufferObject, Base)
	
    OglFramebufferObject() {}
    ~OglFramebufferObject() {FreeOgl();}
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

struct OglFramebufferState : FramebufferStateT<OglGfx> {
	RTTI_DECL1(OglFramebufferState, Base)
	
	GLint GetGlType() const;
	GLint GetGlFormat() const;
	int GetGlSize() const;
	int GetGlSampleSize() const;
	
};

struct OglShader : ShaderT<OglGfx>
{
	RTTI_DECL1(OglShader, Base)
	
	OglShader() {}
	OglShader(OglFramebufferState& s) {state = &s;}
	
};

struct OglShaderPipeline : ShaderPipelineT<OglGfx>
{
	RTTI_DECL1(OglShaderPipeline, Base)
	
};

struct OglCompiler : GCompilerT<OglGfx> {
	RTTI_DECL1(OglCompiler, Base)
	
	OglCompiler();
	bool CompileShader(String code, ShaderVar::Type type, GLuint& shader_out);
	bool Compile(OglFramebufferState& fb_state, OglShaderState& shd_state, ShaderVar::Type type, String code, String library);
	
	static void HotfixWebGLSL(String& s);
};

struct OglLinker : GLinkerT<OglGfx> {
	RTTI_DECL1(OglLinker, Base)
	
	bool Link(OglFramebufferState& fb_state);
	
};

struct OglBuffer : BufferT<OglGfx> {
	RTTI_DECL1(OglBuffer, Base)
	
	
};


NAMESPACE_TOPSIDE_END

#endif
