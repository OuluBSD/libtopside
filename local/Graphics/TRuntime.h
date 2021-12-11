#ifndef _Graphics_TRuntime_h_
#define _Graphics_TRuntime_h_

NAMESPACE_TOPSIDE_BEGIN


template <class Gfx>
struct CompilerT : GfxCompiler {
	RTTI_DECL1(CompilerT, GfxCompiler)
	using Base = CompilerT<Gfx>;
	using NativeShader = typename Gfx::NativeShader;
	using ContextState = typename Gfx::ContextState;
	using RuntimeState = typename Gfx::RuntimeState;
	using Framebuffer = typename Gfx::Framebuffer;
	using ShaderState = typename Gfx::ShaderState;
	
	bool CompileShader(String code, ShaderVar::Type type, NativeShader& shader_out) {
		GLenum shader_type;
		if (type == ShaderVar::PROG_FRAGMENT) {
			shader_type = GL_FRAGMENT_SHADER;
		}
		else if (type == ShaderVar::PROG_VERTEX) {
			shader_type = GL_VERTEX_SHADER;
		}
		else {
			CHKLOGRET0(0, "TODO: other programs than fragment shader");
		}
		
		shader_out = glCreateShader(shader_type);
		GLint status = GL_FALSE;
		GLint loglen = 0;
		CHKLOGRET0(shader_out > 0, "Compiler::CompileShader: error: glCreateShader failed unexpectedly");
		
		const GLchar* src = code.Begin();
		int len = code.GetCount();
		glShaderSource(shader_out, 1, &src, &len);
		glCompileShader(shader_out);
		
		glGetShaderiv(shader_out, GL_COMPILE_STATUS, &status);
		if (status != GL_TRUE) {
			glGetShaderiv(shader_out, GL_INFO_LOG_LENGTH, &loglen);
			Vector<GLchar> msg;
			msg.SetCount(loglen);
			glGetShaderInfoLog(shader_out, loglen, NULL, msg.Begin());
			String err(msg.Begin());
			SetError(err);
			CHKLOGRET0(0, "Compiler::CompileShader: error: shader failed to compile: " + err);
		}
		
		return true;
	}
	
	bool Compile(	const ContextState& ctx,
					RuntimeState& rt,
					Framebuffer& fb,
					ShaderState& shdr,
					ShaderVar::Type type) {
		bool succ = true;
		String code = Gfx::GetShaderTemplate();
		String user_code = shdr.code;
		String library = shdr.library;
		
		Gfx::HotfixShaderCode(library);
		Gfx::HotfixShaderCode(user_code);
		
		String sampler0 = "sampler2D";
		String sampler1 = "sampler2D";
		String sampler2 = "sampler2D";
		String sampler3 = "sampler2D";
		
		bool is_fragment = type == ShaderVar::PROG_FRAGMENT;
		bool is_vertex = type == ShaderVar::PROG_VERTEX;
		code.Replace("${IS_FRAGMENT_SHADER}", IntStr(is_fragment));
		code.Replace("${IS_VERTEX_SHADER}", IntStr(is_vertex));
		code.Replace("${IS_AUDIO}", IntStr(fb.is_audio));
		code.Replace("${USER_CODE}", user_code);
		code.Replace("${USER_LIBRARY}", library);
		code.Replace("${SAMPLER0}", sampler0);
		code.Replace("${SAMPLER1}", sampler1);
		code.Replace("${SAMPLER2}", sampler2);
		code.Replace("${SAMPLER3}", sampler3);
		
		LOG(code);
		
		{
			EnableGfxAccelDebugMessages(1);
			
			succ = CompileShader(code, type, shdr.shader);
			
			rt.is_searched_vars = false;
			
			EnableGfxAccelDebugMessages(0);
		}
		
		if (!succ) {
			LOG(GetLineNumStr(code));
		}
		return succ;
	}

	
};

template <class Gfx>
struct LinkerT : GfxLinker {
	RTTI_DECL1(LinkerT, GfxLinker)
	using Base = LinkerT<Gfx>;
	using RuntimeState = typename Gfx::RuntimeState;
	using ShaderState = typename Gfx::ShaderState;
	
	bool log = false;
	
	
	
	bool Link(RuntimeState& rt) {
		CHKLOGRET0(rt.prog == 0, "Linker::Link: error: trying to overwrite compiled program");
		
		rt.prog = glCreateProgram();
		CHKLOGRET0(rt.prog > 0, "Linker::Link: error: opengl error")
		
		glProgramParameteri(rt.prog, GL_PROGRAM_SEPARABLE, GL_TRUE);
		
		uint8 complied_count = 0;
		EnableGfxAccelDebugMessages(1);
		for(int i = 0; i < ShaderVar::PROG_COUNT; i++) {
			ShaderState& shd_state = rt.shaders[i];
			if (shd_state.shader == 0)
				continue;
			complied_count++;
			
			glAttachShader(rt.prog, shd_state.shader);
			glDeleteShader(shd_state.shader);
			shd_state.shader = 0;
		}
		EnableGfxAccelDebugMessages(0);
		CHKLOGRET0(complied_count, "Linker::Link: error: no compiled shaders found");
		
		glLinkProgram(rt.prog);
		
		GLint status = GL_FALSE;
		GLint loglen, n_uniforms;
		glGetProgramiv(rt.prog, GL_LINK_STATUS, &status);
		if (status != GL_TRUE) {
			glGetProgramiv(rt.prog, GL_INFO_LOG_LENGTH, &loglen);
			Vector<GLchar> msg;
			msg.SetCount(loglen);
			glGetProgramInfoLog(rt.prog, loglen, NULL, msg.Begin());
			if (loglen) {
				String s;
				s.Set(msg.Begin(), loglen);
				SetError(s);
			}
			else
				SetError("linking failed with unknown error");
			return false;
		}
		
		// diagnostics
		if (log) {
			glGetProgramiv(rt.prog, GL_ACTIVE_UNIFORMS, &n_uniforms);
			LOG("\t\t" << (int)n_uniforms << " uniforms:");
			
			GLchar name[80];
			GLsizei namelen;
			for (int i = 0; i < n_uniforms; i++) {
				GLint size;
				GLenum type;
				
				glGetActiveUniform(rt.prog, i, 79, &namelen, &size, &type, name);
				name[namelen] = '\0';
				LOG("\t\t\t" << i << ": " << String(name) << " (type: " << HexStr(type) << ", size: " << (int)size << ")");
			}
		}
		
		return true;
	}
	
	void EnableLog() {log = true;}
	void DisableLog() {log = false;}
	
};


template <class Gfx>
struct ShaderStateT : GfxShaderState {
	RTTI_DECL1(ShaderStateT, GfxShaderState)
	using Base = ShaderStateT<Gfx>;
	using NativeShader = typename Gfx::NativeShader;
	
	
	NativeShader shader;
	
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
	using Framebuffer = typename Gfx::Framebuffer;
	using DataState = typename Gfx::DataState;
	using DataObject = typename Gfx::DataObject;
	using VertexShaderArgs = typename Gfx::VertexShaderArgs;
	using FragmentShaderArgs = typename Gfx::FragmentShaderArgs;
	using DataStateBase = DataStateT<Gfx>;
	RTTI_DECL1(ShaderT, GfxShader)
	
    DataStateBase* state = 0;
    
    
	void SetState(DataStateBase& d) {state = &d;}
    bool CheckCompileErrors(GLuint shader, String type);
	void BasicMeshRefresh(ModelMesh& model, Mesh& mesh);
    
	GfxDataObject* CreateObject() override {return state ? &state->CreateObject() : 0;}

	virtual void Process(VertexShaderArgs& args) {Panic("not implemented");}
	virtual void Process(FragmentShaderArgs& args) {Panic("not implemented");}
	
	
	
	
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

template <class Gfx>
struct ShaderPipelineT :
	GfxShaderPipeline
{
	RTTI_DECL1(ShaderPipelineT, GfxShaderPipeline)
	using Base = ShaderPipelineT<Gfx>;
	using DataState = typename Gfx::DataState;
	
	
	
	
	void LoadState(DataState& state) {TODO}
	
};

template <class Gfx>
struct RuntimeStateT : GfxRuntimeState {
	RTTI_DECL1(RuntimeStateT, GfxRuntimeState)
	using Base = RuntimeStateT<Gfx>;
	using NatProgram  = typename Gfx::NativeProgram;
	using NatPipeline = typename Gfx::NativePipeline;
	using NatShader = typename Gfx::NativeShader;
	using ShaderState = typename Gfx::ShaderState;
	using InputState = typename Gfx::InputState;
	
	
	NatProgram	prog;
	NatPipeline	pipeline;
	NatShader	shader;
	bool		is_searched_vars = 0;
	int			var_idx[ShaderVar::VAR_COUNT];
	bool		is_time_used = 0;
	
	ShaderState	shaders[ShaderVar::PROG_COUNT];
	InputState	inputs[ShaderVar::INPUT_COUNT];
	
	Vector<String> user_vars;
	
	
	
	RuntimeStateT() {
		prog = Null;
		pipeline = Null;
		shader = Null;
		memset(&var_idx, 0, sizeof(var_idx));
	}
	
	void SetCode(ShaderVar::Type t, const String& s) {shaders[t].code = s;}
	
};

template <class Gfx>
struct FramebufferStateExtT : ErrorReporter {
	RTTI_DECL1(FramebufferStateExtT, ErrorReporter)
	using Base = FramebufferStateExtT<Gfx>;
	using Framebuffer = typename Gfx::Framebuffer;
	using Shader = typename Gfx::Shader;
	
	Framebuffer* state = 0;
	Shader* stages[ShaderVar::PROG_COUNT];
	
	
	FramebufferStateExtT() {Clear();}
	void SetVertex(Shader& s) {stages[ShaderVar::PROG_VERTEX] = &s;}
	void SetFragment(Shader& s) {stages[ShaderVar::PROG_FRAGMENT] = &s;}
	
	
	void Clear() {
		//FramebufferState::Clear();
		state = 0;
		for(int i = 0; i < ShaderVar::PROG_COUNT; i++)
			stages[i] = 0;
	}
	
	void LoadState(FramebufferT<Gfx>& state) {
		Clear();
		
		this->state = &state;
		AppendState(state);
	}
	
	void AppendState(FramebufferT<Gfx>& state) {
		for(int i = 0; i < ShaderVar::PROG_COUNT; i++) {
			if (state.stages[i])
				stages[i] = CastPtr<ShaderT<Gfx>>(state.stages[i]);
		}
	}

};



NAMESPACE_TOPSIDE_END

#endif
