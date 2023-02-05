#ifndef _IGraphics_TPipeline_h_
#define _IGraphics_TPipeline_h_

NAMESPACE_PARALLEL_BEGIN


template <class Gfx> struct ContextStateT;
template <class Gfx> struct ProgramStateT;
template <class Gfx> struct PipelineStateT;
template <class Gfx> struct ProgramStateT;
template <class Gfx> struct ShaderStateT;
template <class Gfx> struct DataStateT;
template <class Gfx> struct InputStateT;
template <class Gfx> struct ModelStateT;

template <class Gfx>
struct CompilerT : GfxCompiler {
	RTTI_DECL1(CompilerT, GfxCompiler)
	using Base = CompilerT<Gfx>;
	using NativeShaderRef = typename Gfx::NativeShaderRef;
	using PipelineState = PipelineStateT<Gfx>;
	using ProgramState = ProgramStateT<Gfx>;
	using Framebuffer = FramebufferT<Gfx>;
	using ShaderState = ShaderStateT<Gfx>;
	using ContextState = ContextStateT<Gfx>;
	
	bool CompileShader(String code, GVar::ShaderType type, NativeShaderRef& shader_out);
	bool Compile(	const GfxCompilerArgs& args,
					ProgramState& ps,
					ShaderState& shdr,
					GVar::ShaderType type);

	
};

template <class Gfx>
struct LinkerT : GfxLinker {
	RTTI_DECL1(LinkerT, GfxLinker)
	using Base = LinkerT<Gfx>;
	using PipelineState = PipelineStateT<Gfx>;
	using ShaderState = ShaderStateT<Gfx>;
	using ProgramState = ProgramStateT<Gfx>;
	
	bool log = false;
	
	
	
	bool Link(ProgramState& ps);
	
	void EnableLog() {log = true;}
	void DisableLog() {log = false;}
	
};


template <class Gfx>
struct ShaderStateT : GfxShaderState {
	RTTI_DECL1(ShaderStateT, GfxShaderState)
	using Base = ShaderStateT<Gfx>;
	using NativeShaderRef = typename Gfx::NativeShaderRef;
	
	
	NativeShaderRef native;
	
	ShaderStateT() {
		native = NULL;
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
	void BasicMeshRefresh(Model& model, Mesh& mesh);
    
	GfxDataObject* CreateObject() override {return state ? &state->CreateObject() : 0;}

	
};



template <class Gfx>
struct ProgramStateT : GfxProgramState {
	RTTI_DECL1(ProgramStateT, GfxProgramState)
	using Base = ProgramStateT<Gfx>;
	using NativeProgram = typename Gfx::NativeProgram;
	using NativePipeline = typename Gfx::NativePipeline;
	using ShaderState = ShaderStateT<Gfx>;
	using InputState = InputStateT<Gfx>;
	using PipelineState = PipelineStateT<Gfx>;
	using DataState = DataStateT<Gfx>;
	using ModelState = ModelStateT<Gfx>;
	using DataObject = DataObjectT<Gfx>;
	using ContextState = ContextStateT<Gfx>;
	using BufferStage = BufferStageT<Gfx>;
	using Compiler = CompilerT<Gfx>;
	using Linker = LinkerT<Gfx>;
	using NativeColorBufferConstRef = typename Gfx::NativeColorBufferConstRef;
	
	PipelineState*		owner = 0;
	String				name;
	NativeProgram		native;
	bool				is_searched_vars = 0;
	int					var_idx[GVar::VAR_COUNT];
	bool				is_time_used = 0;
	ShaderState			shaders[GVar::SHADERTYPE_COUNT];
	InputState			inputs[GVar::INPUT_COUNT];
	bool				ready = false;
	bool				failed = false;
	
	Vector<String>		user_vars;
	
	
	ProgramStateT() {
		native = Null;
		memset(&var_idx, 0, sizeof(var_idx));
	}
	
	void SetCode(GVar::ShaderType t, const String& s) {shaders[t].code = s;}
	
	
	bool LoadShader(GVar::ShaderType shader_type, String str, bool is_path, bool is_content, String library_path);
	bool LoadShaderFile(GVar::ShaderType shader_type, String shader_path, String library_path);
	bool LoadShaderContent(GVar::ShaderType shader_type, String content);
	bool LoadBuiltinShader(GVar::ShaderType shader_type, String id);
	bool LoadInputLink(int in_id, const InternalPacketData& v);
	bool Compile(const GfxCompilerArgs& args);
	bool SetupLoopback(int loopback_stage_i, BufferStage& s);
	void RefreshProgramStages();
	void FindVariables();
	void RealizeCompilation(const GfxCompilerArgs& args);
	
	typedef enum {
		VIEW_TARGET_MONO,
		VIEW_TARGET_STEREO_LEFT,
		VIEW_TARGET_STEREO_RIGHT,
	} ViewTarget;
	
	void SetVars(ContextState&, ModelState&, const DataObject& o, ViewTarget vtgt);
	void SetVar(ContextState&, ModelState&, int var, const DataObject& o, ViewTarget vtgt);
	void SetVars(ContextState& ctx, EnvStateRef& env, const RealtimeSourceConfig& cfg);
	void SetVar(ContextState& ctx, EnvStateRef& env, int var, const RealtimeSourceConfig& cfg);
	void SetInputVolume(int in_id);
	void SetInputCubemap(int in_id);
	
	int BuiltinShader();
	template <int> int BuiltinShaderT();
	template <int> bool LoadBuiltinShaderT(GVar::ShaderType shader_type, String id);
	
	NativeColorBufferConstRef GetInputTex(int input_i) const;
	GVar::TextureMode GetTexType(int input_i) const;
	
	
};

template <class Gfx>
struct PipelineStateT : GfxPipelineState {
	RTTI_DECL1(PipelineStateT, GfxPipelineState)
	using Base = PipelineStateT<Gfx>;
	using NativeProgram  = typename Gfx::NativeProgram;
	using NativePipeline = typename Gfx::NativePipeline;
	using ShaderState = ShaderStateT<Gfx>;
	using InputState  = InputStateT<Gfx>;
	using ProgramState  = ProgramStateT<Gfx>;
	using DataState  = DataStateT<Gfx>;
	
	
	DataState* owner = 0;
	String name;
	
	NativePipeline native;
	ArrayMap<int, ProgramState> programs;
	
	
	
	PipelineStateT() {
		native = Null;
	}
	ProgramState& GetAddProgram(String name);
	ProgramState* FindProgram(String name);
	void Realize();
	void Clear();
	void Create();
	
};




NAMESPACE_PARALLEL_END

#endif
