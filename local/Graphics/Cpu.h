#ifndef _Graphics_Cpu_h_
#define _Graphics_Cpu_h_

NAMESPACE_TOPSIDE_BEGIN



struct CpuFramebufferState;
struct CpuDataObject;



struct CpuVertexShaderArgs {
	CpuFramebufferState& state;
	CpuDataObject& obj;
	const vec3& pos;
	const vec3& normal;
	const vec2& tex_coords;
	vec4& pos_out;
	vec2& tex_coord_out;
};

struct CpuFragmentShaderArgs {
	
};







struct CpuStateDraw : StateDrawT<CpuGfx> {RTTI_DECL1(CpuStateDraw, Base)};
struct CpuFramebuffer : FramebufferT<CpuGfx> {RTTI_DECL1(CpuFramebuffer, Base)};


struct SdlCpuRenderer : public RendererT<SdlCpuGfx> {
	RTTI_DECL1(SdlCpuRenderer, Base)
};


class SdlCpuDrawFramebuffer : public DrawFramebufferT<SdlCpuGfx> {
public:
	RTTI_DECL1(SdlCpuDrawFramebuffer, Base)
	
};

struct CpuDataObject : DataObjectT<CpuGfx> {
	RTTI_DECL1(CpuDataObject, Base)
	
    CpuDataObject() {}
    ~CpuDataObject() {FreeCpu();}
    void FreeCpu() {TODO}
    void Paint() override {TODO}
    void MakeTexture(int tex_id, int w, int h, int pitch, int stride, const Vector<byte>& data) override {TODO}
    
};

struct CpuDataState : DataStateT<CpuGfx> {RTTI_DECL1(CpuDataState, Base)};

struct CpuInputState : FramebufferInputStateT<CpuGfx> {
	RTTI_DECL1(CpuInputState, Base)
	
};

struct CpuShaderState : ShaderStateT<CpuGfx> {
	RTTI_DECL1(CpuShaderState, Base)
	
};

struct CpuShader : ShaderT<CpuGfx>
{
	RTTI_DECL1(CpuShader, Base)
	
	CpuShader() {}
	
};

struct CpuShaderPipeline : ShaderPipelineT<CpuGfx>
{
	RTTI_DECL1(CpuShaderPipeline, Base)
	
};

struct CpuCompiler : GfxCompilerT<CpuGfx> {
	RTTI_DECL1(CpuCompiler, Base)
	
	CpuCompiler();
	bool CompileShader(String code, ShaderVar::Type type, GLuint& shader_out);
	bool Compile(CpuFramebufferState& fb_state, CpuShaderState& shd_state, ShaderVar::Type type, String code, String library);
	
	static void HotfixWebGLSL(String& s);
};

struct CpuLinker : GfxLinkerT<CpuGfx> {
	RTTI_DECL1(CpuLinker, Base)
	
	bool Link(CpuFramebufferState& fb_state);
	
};

struct CpuRuntimeState : RuntimeStateT<CpuGfx> {RTTI_DECL1(CpuRuntimeState, Base)};
struct CpuContextState : ContextStateT<CpuGfx> {RTTI_DECL1(CpuContextState, Base)};

struct CpuBuffer : BufferT<CpuGfx> {
	RTTI_DECL1(CpuBuffer, Base)
	
	
};





NAMESPACE_TOPSIDE_END

#endif
