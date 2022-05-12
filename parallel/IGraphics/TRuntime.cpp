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
				const ContextState& ctx,
				RuntimeState& rt,
				Framebuffer& fb,
				ShaderState& shdr,
				GVar::ShaderType type) {
	bool succ = true;
	String code = Gfx::GetShaderTemplate(type);
	String user_code = shdr.code;
	String library = shdr.library;
	
	Gfx::HotfixShaderCode(library);
	Gfx::HotfixShaderCode(user_code);
	
	String sampler0 = rt.inputs[0].GetSamplerString();
	String sampler1 = rt.inputs[1].GetSamplerString();
	String sampler2 = rt.inputs[2].GetSamplerString();
	String sampler3 = rt.inputs[3].GetSamplerString();
	
	bool is_fragment = type == GVar::FRAGMENT_SHADER;
	bool is_vertex = type == GVar::VERTEX_SHADER;
	code.Replace("${IS_FRAGMENT_SHADER}", IntStr(is_fragment));
	code.Replace("${IS_VERTEX_SHADER}", IntStr(is_vertex));
	code.Replace("${IS_AUDIO}", IntStr(fb.is_audio));
	code.Replace("${USER_CODE}", user_code);
	code.Replace("${USER_LIBRARY}", library);
	code.Replace("${SAMPLER0}", sampler0);
	code.Replace("${SAMPLER1}", sampler1);
	code.Replace("${SAMPLER2}", sampler2);
	code.Replace("${SAMPLER3}", sampler3);
	
	LOG(GetLineNumStr(code));
	
	{
		EnableGfxAccelDebugMessages(1);
		
		succ = CompileShader(code, type, shdr.shader);
		
		rt.is_searched_vars = false;
		
		EnableGfxAccelDebugMessages(0);
	}
	
	/*if (!succ) {
		LOG(GetLineNumStr(code));
	}*/
	return succ;
}


template <class Gfx>
bool LinkerT<Gfx>::Link(RuntimeState& rt) {
	CHKLOGRET0(rt.prog == 0, "Linker::Link: error: trying to overwrite compiled program");
	
	Gfx::CreateProgram(rt.prog);
	CHKLOGRET0(rt.prog, "Linker::Link: error: opengl error")
	
	Gfx::ProgramParameteri(rt.prog, GVar::PROGRAM_SEPARABLE, true);
	
	uint8 complied_count = 0;
	EnableGfxAccelDebugMessages(1);
	for(int i = 0; i < GVar::SHADERTYPE_COUNT; i++) {
		ShaderState& shd_state = rt.shaders[i];
		if (!shd_state.shader)
			continue;
		complied_count++;
		
		Gfx::AttachShader(rt.prog, shd_state.shader);
		Gfx::DeleteShader(shd_state.shader);
		shd_state.shader = Null;
	}
	EnableGfxAccelDebugMessages(0);
	CHKLOGRET0(complied_count, "Linker::Link: error: no compiled shaders found");
	
	bool succ = Gfx::LinkProgram(rt.prog);
	
	if (!succ) {
		String err = Gfx::GetLastErrorP(rt.prog);
		SetError(err);
		return false;
	}
	
	// diagnostics
	if (log) {
		int n_uniforms = 0;
		Gfx::GetProgramiv(rt.prog, GVar::ACTIVE_UNIFORMS, n_uniforms);
		LOG("\t\t" << (int)n_uniforms << " uniforms:");
		
		
		for (int i = 0; i < n_uniforms; i++) {
			int size = 0, type = 0;
			String name = Gfx::GetActiveUniform(rt.prog, i, &size, &type);
			LOG("\t\t\t" << i << ": " << String(name) << " (type: " << HexStr(type) << ", size: " << (int)size << ")");
		}
	}
	
	return true;
}


GFX3D_EXCPLICIT_INITIALIZE_CLASS(CompilerT)
GFX3D_EXCPLICIT_INITIALIZE_CLASS(LinkerT)
GFX3D_EXCPLICIT_INITIALIZE_CLASS(ShaderStateT)
//GFX3D_EXCPLICIT_INITIALIZE_CLASS(ShaderT)
GFX3D_EXCPLICIT_INITIALIZE_CLASS(ShaderPipelineT)
GFX3D_EXCPLICIT_INITIALIZE_CLASS(RuntimeStateT)
//GFX3D_EXCPLICIT_INITIALIZE_CLASS(FramebufferStateExtT)


NAMESPACE_PARALLEL_END
