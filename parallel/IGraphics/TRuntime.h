#ifndef _IGraphics_TRuntime_h_
#define _IGraphics_TRuntime_h_

NAMESPACE_PARALLEL_BEGIN


template <class Gfx> struct ContextStateT;
template <class Gfx> struct RuntimeStateT;

template <class Gfx>
struct CompilerT : GfxCompiler {
	RTTI_DECL1(CompilerT, GfxCompiler)
	using Base = CompilerT<Gfx>;
	using NativeShaderRef = typename Gfx::NativeShaderRef;
	using RuntimeState = RuntimeStateT<Gfx>;
	using Framebuffer = FramebufferT<Gfx>;
	using ShaderState = ShaderStateT<Gfx>;
	using ContextState = ContextStateT<Gfx>;
	
	bool CompileShader(String code, GVar::ShaderType type, NativeShaderRef& shader_out);
	bool Compile(	const ContextState& ctx,
					RuntimeState& rt,
					Framebuffer& fb,
					ShaderState& shdr,
					GVar::ShaderType type);

	
};

template <class Gfx>
struct LinkerT : GfxLinker {
	RTTI_DECL1(LinkerT, GfxLinker)
	using Base = LinkerT<Gfx>;
	using RuntimeState = RuntimeStateT<Gfx>;
	using ShaderState = ShaderStateT<Gfx>;
	
	bool log = false;
	
	
	
	bool Link(RuntimeState& rt);
	
	void EnableLog() {log = true;}
	void DisableLog() {log = false;}
	
};


template <class Gfx>
struct ShaderStateT : GfxShaderState {
	RTTI_DECL1(ShaderStateT, GfxShaderState)
	using Base = ShaderStateT<Gfx>;
	using NativeShaderRef = typename Gfx::NativeShaderRef;
	
	
	NativeShaderRef shader;
	
	ShaderStateT() {
		shader = Null;
	}
	
};


template <class Gfx>
struct ShaderT :
	GfxShader,
	ErrorReporter
{
	using Base = ShaderT<Gfx>;
	using DataState = DataStateT<Gfx>;
	using DataObject = typename Gfx::DataObject;
	using VertexShaderArgs = typename Gfx::VertexShaderArgs;
	using FragmentShaderArgs = typename Gfx::FragmentShaderArgs;
	using DataStateBase = DataStateT<Gfx>;
	using Framebuffer = FramebufferT<Gfx>;
	RTTI_DECL1(ShaderT, GfxShader)
	
    DataStateBase* state = 0;
    
    
	void SetState(DataStateBase& d) {state = &d;}
    bool CheckCompileErrors(GLuint shader, String type);
	void BasicMeshRefresh(ModelMesh& model, Mesh& mesh);
    
	GfxDataObject* CreateObject() override {return state ? &state->CreateObject() : 0;}

	
	
	
	
	#if 0
	bool Load(String vertex_path, String fragment_path, String geometry_path = "") override;
	void SetLoaded(bool b=true) {is_loaded = true;}
	bool IsLoaded() const override {return is_loaded;}
	void Refresh(ModelMesh& model) override;
    void Refresh(ModelMesh& model, Mesh& mesh) override;
	void Use() override;
	
	
	void SetBool(const String &name, bool value) const override;
	void SetInt(const String &name, int value) const override;
	void SetFloat(const String &name, float value) const override;
	void SetVec2(const String &name, const vec2 &value) const override;
	void SetVec3(const String &name, const vec3 &value) const override;
	void SetVec4(const String &name, const vec4 &value) const override;
	void SetMat2(const String &name, const mat2 &mat) const override;
	void SetMat3(const String &name, const mat3 &mat) const override;
	void SetMat4(const String &name, const mat4 &mat) const override;
	void SetVec2(const String &name, float x, float y) const override;
	void SetVec3(const String &name, float x, float y, float z) const override;
	void SetVec4(const String &name, float x, float y, float z, float w) const override;
	#endif
	
};
#endif


template <class Gfx>
struct ShaderPipelineT :
	GfxShaderPipeline
{
	RTTI_DECL1(ShaderPipelineT, GfxShaderPipeline)
	using Base = ShaderPipelineT<Gfx>;
	using DataState = DataStateT<Gfx>;
	
	
	
	
	void LoadState(DataState& state) {TODO}
	
};

template <class Gfx>
struct RuntimeStateT : GfxRuntimeState {
	RTTI_DECL1(RuntimeStateT, GfxRuntimeState)
	using Base = RuntimeStateT<Gfx>;
	using NativeProgram  = typename Gfx::NativeProgram;
	using NativePipeline = typename Gfx::NativePipeline;
	using ShaderState = ShaderStateT<Gfx>;
	using InputState  = InputStateT<Gfx>;
	
	
	NativeProgram	prog;
	NativePipeline	pipeline;
	//NativeShaderRef	shader;
	bool		is_searched_vars = 0;
	int			var_idx[GVar::VAR_COUNT];
	bool		is_time_used = 0;
	
	ShaderState	shaders[GVar::SHADERTYPE_COUNT];
	InputState	inputs[GVar::INPUT_COUNT];
	
	Vector<String> user_vars;
	
	
	
	RuntimeStateT() {
		prog = Null;
		pipeline = Null;
		//shader = Null;
		memset(&var_idx, 0, sizeof(var_idx));
	}
	
	void SetCode(GVar::ShaderType t, const String& s) {shaders[t].code = s;}
	
};

#if 0
template <class Gfx>
struct FramebufferStateExtT : ErrorReporter {
	RTTI_DECL1(FramebufferStateExtT, ErrorReporter)
	using Base = FramebufferStateExtT<Gfx>;
	using Framebuffer = typename Gfx::Framebuffer;
	//using Shader = typename Gfx::Shader;
	
	Framebuffer* state = 0;
	//Shader* stages[GVar::SHADERTYPE_COUNT];
	
	
	FramebufferStateExtT() {Clear();}
	//void SetVertex(Shader& s) {stages[GVar::VERTEX_SHADER] = &s;}
	//void SetFragment(Shader& s) {stages[GVar::FRAGMENT_SHADER] = &s;}
	
	
	void Clear() {
		//FramebufferState::Clear();
		state = 0;
		for(int i = 0; i < GVar::SHADERTYPE_COUNT; i++)
			stages[i] = 0;
	}
	
	/*void LoadState(FramebufferT<Gfx>& state) {
		Clear();
		
		this->state = CastPtr<Framebuffer>(&state);
		ASSERT(state);
		AppendState(state);
	}
	
	void AppendState(FramebufferT<Gfx>& state) {
		for(int i = 0; i < GVar::SHADERTYPE_COUNT; i++) {
			if (state.stages[i])
				stages[i] = CastPtr<ShaderT<Gfx>>(state.stages[i]);
		}
	}*/

};

#endif

NAMESPACE_PARALLEL_END

