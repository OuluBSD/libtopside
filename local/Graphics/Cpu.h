#ifndef _Graphics_Cpu_h_
#define _Graphics_Cpu_h_

NAMESPACE_TOPSIDE_BEGIN


#define GFX_CLS(x, g) struct g##x : x##T<g##Gfx> {RTTI_DECL1(g##x, Base)};
GFX_CLS_LIST(SdlCpu)
#undef GFX_CLS


// default frame TODO should be conditional
using CpuStateDraw = SdlCpuStateDraw;
using CpuDataState = SdlCpuDataState;
using CpuFramebuffer = SdlCpuFramebuffer;


#if 0
struct CpuVertexShaderArgs {
};

struct CpuFragmentShaderArgs {
	
};


using SdlCpuVertexShaderArgs = CpuVertexShaderArgs;
using SdlCpuFragmentShaderArgs = CpuFragmentShaderArgs;


struct CpuFramebufferState;
struct CpuDataObject;

struct CpuStateDraw : StateDrawT<CpuGfx> {RTTI_DECL1(CpuStateDraw, Base)};
struct SdlCpuFramebuffer : FramebufferT<SdlCpuGfx> {RTTI_DECL1(SdlCpuFramebuffer, Base)};


struct SdlCpuRenderer : public RendererT<SdlCpuGfx> {
	RTTI_DECL1(SdlCpuRenderer, Base)
};


/*class SdlCpuDrawFramebuffer : public DrawFramebufferT<SdlCpuGfx> {
public:
	RTTI_DECL1(SdlCpuDrawFramebuffer, Base)
	
};*/

struct CpuDataObject : DataObjectT<CpuGfx> {
	RTTI_DECL1(CpuDataObject, Base)
	
    CpuDataObject() {}
    ~CpuDataObject() {FreeCpu();}
    void FreeCpu() {TODO}
    void Paint() override {TODO}
    void MakeTexture(int tex_id, int w, int h, int pitch, int stride, const Vector<byte>& data) override {TODO}
    
};

struct CpuDataState : DataStateT<CpuGfx> {RTTI_DECL1(CpuDataState, Base)};

struct CpuInputState : InputStateT<CpuGfx> {
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

struct CpuCompiler : CompilerT<CpuGfx> {
	RTTI_DECL1(CpuCompiler, Base)
	
	CpuCompiler();
	bool CompileShader(String code, ShaderVar::Type type, GLuint& shader_out);
	bool Compile(CpuFramebufferState& fb_state, CpuShaderState& shd_state, ShaderVar::Type type, String code, String library);
	
};

struct CpuLinker : LinkerT<CpuGfx> {
	RTTI_DECL1(CpuLinker, Base)
	
	bool Link(CpuFramebufferState& fb_state);
	
};

struct CpuRuntimeState : RuntimeStateT<CpuGfx> {RTTI_DECL1(CpuRuntimeState, Base)};
struct CpuContextState : ContextStateT<CpuGfx> {RTTI_DECL1(CpuContextState, Base)};

struct CpuBuffer : BufferT<CpuGfx> {
	RTTI_DECL1(CpuBuffer, Base)
	
	
};




#endif

NAMESPACE_TOPSIDE_END

#endif
