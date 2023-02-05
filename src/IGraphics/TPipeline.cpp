#include "IGraphics.h"

NAMESPACE_PARALLEL_BEGIN


template <class Gfx>
bool CompilerT<Gfx>::CompileShader(String code, GVar::ShaderType type, NativeShaderRef& shader_out) {
	bool succ = Gfx::CreateShader(type, shader_out);
	CHKLOGRET0(succ, "Compiler::CompileShader: error: Gfx::CreateShader failed unexpectedly");
	
	Gfx::ShaderSource(shader_out, code);
	succ = Gfx::CompileShader(shader_out);
	
	if (!succ) {
		String err = Gfx::GetLastErrorS(shader_out);
		SetError(err);
		CHKLOGRET0(0, "Compiler::CompileShader: error: shader failed to compile: " + err);
	}
	
	return true;
}


template <class Gfx>
bool CompilerT<Gfx>::Compile(
				const GfxCompilerArgs& args,
				ProgramState& ps,
				ShaderState& shdr,
				GVar::ShaderType type) {
	bool succ = true;
	String code = Gfx::GetShaderTemplate(type);
	String user_code = shdr.code;
	String library = shdr.library;
	
	Gfx::HotfixShaderCode(library);
	Gfx::HotfixShaderCode(user_code);
	
	String sampler0 = ps.inputs[0].GetSamplerString();
	String sampler1 = ps.inputs[1].GetSamplerString();
	String sampler2 = ps.inputs[2].GetSamplerString();
	String sampler3 = ps.inputs[3].GetSamplerString();
	
	bool is_fragment = type == GVar::FRAGMENT_SHADER;
	bool is_vertex = type == GVar::VERTEX_SHADER;
	code.Replace("${IS_FRAGMENT_SHADER}", IntStr(is_fragment));
	code.Replace("${IS_VERTEX_SHADER}", IntStr(is_vertex));
	code.Replace("${IS_AUDIO}", IntStr(args.is_audio));
	code.Replace("${IS_AFFINE}", IntStr(args.is_affine));
	code.Replace("${USER_CODE}", user_code);
	code.Replace("${USER_LIBRARY}", library);
	code.Replace("${SAMPLER0}", sampler0);
	code.Replace("${SAMPLER1}", sampler1);
	code.Replace("${SAMPLER2}", sampler2);
	code.Replace("${SAMPLER3}", sampler3);
	
	LOG(GetLineNumStr(code));
	
	{
		EnableGfxAccelDebugMessages(1);
		
		succ = CompileShader(code, type, shdr.native);
		
		ps.is_searched_vars = false;
		
		EnableGfxAccelDebugMessages(0);
	}
	
	return succ;
}


template <class Gfx>
bool LinkerT<Gfx>::Link(ProgramState& ps) {
	CHKLOGRET0(!ps.native, "Linker::Link: error: trying to overwrite compiled program");
	
	Gfx::CreateProgram(ps.native);
	CHKLOGRET0(ps.native, "Linker::Link: error: opengl error")
	
	Gfx::ProgramParameteri(ps.native, GVar::PROGRAM_SEPARABLE, true);
	
	uint8 complied_count = 0;
	EnableGfxAccelDebugMessages(1);
	for(int i = 0; i < GVar::SHADERTYPE_COUNT; i++) {
		ShaderState& shd_state = ps.shaders[i];
		if (!shd_state.native)
			continue;
		complied_count++;
		
		Gfx::AttachShader(ps.native, shd_state.native);
		Gfx::DeleteShader(shd_state.native);
		shd_state.native = NULL;
	}
	EnableGfxAccelDebugMessages(0);
	CHKLOGRET0(complied_count, "Linker::Link: error: no compiled shaders found");
	
	bool succ = Gfx::LinkProgram(ps.native);
	
	if (!succ) {
		String err = Gfx::GetLastErrorP(ps.native);
		SetError(err);
		return false;
	}
	
	// diagnostics
	if (log) {
		int n_uniforms = 0;
		Gfx::GetProgramiv(ps.native, GVar::ACTIVE_UNIFORMS, n_uniforms);
		LOG("\t\t" << (int)n_uniforms << " uniforms:");
		
		
		for (int i = 0; i < n_uniforms; i++) {
			int size = 0, type = 0;
			String name = Gfx::GetActiveUniform(ps.native, i, &size, &type);
			LOG("\t\t\t" << i << ": " << String(name) << " (type: " << HexStr(type) << ", size: " << (int)size << ")");
		}
	}
	
	return true;
}





















template <class Gfx>
ProgramStateT<Gfx>& PipelineStateT<Gfx>::GetAddProgram(String name) {
	int id = owner->dictionary.FindAdd(name);
	int i = programs.Find(id);
	if (i >= 0)
		return programs[i];
	ProgramStateT<Gfx>& ps = programs.Add(id);
	ps.owner = this;
	ps.name = name;
	ps.id = id;
	return ps;
}

template <class Gfx>
ProgramStateT<Gfx>* PipelineStateT<Gfx>::FindProgram(String name) {
	int id = owner->dictionary.Find(name);
	if (id < 0)
		return 0;
	int i = programs.Find(id);
	if (i < 0)
		return 0;
	return &programs[i];
}

template <class Gfx>
void PipelineStateT<Gfx>::Realize() {
	if (!native)
		Create();
	
	for (ProgramState& prog : programs.GetValues())
		prog.RefreshProgramStages();
}

template <class Gfx>
void PipelineStateT<Gfx>::Clear() {
	if (native) {
		Gfx::DeleteProgramPipeline(native);
	}
}

template <class Gfx>
void PipelineStateT<Gfx>::Create() {
	Clear();
	
	Gfx::GenProgramPipeline(native);
	
	for (ProgramState& prog : programs.GetValues())
		prog.RefreshProgramStages();
}


GFX3D_EXCPLICIT_INITIALIZE_CLASS(CompilerT)
GFX3D_EXCPLICIT_INITIALIZE_CLASS(LinkerT)
GFX3D_EXCPLICIT_INITIALIZE_CLASS(ShaderStateT)
GFX3D_EXCPLICIT_INITIALIZE_CLASS(PipelineStateT)


NAMESPACE_PARALLEL_END
