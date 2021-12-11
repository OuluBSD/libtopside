#include "Graphics.h"


NAMESPACE_TOPSIDE_BEGIN

#if 0

OglCompiler::OglCompiler() {
	
}






bool OglCompiler::Compile(const OglContextState& ctx, OglRuntimeState& rt, OglFramebuffer& fb, OglShaderState& shdr, ShaderVar::Type type) {
	bool succ = true;
	String code = shader_tmpl;
	String user_code = shdr.code;
	String library = shdr.library;
	
	HotfixWebGLSL(library);
	HotfixWebGLSL(user_code);
	
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

void OglCompiler::HotfixWebGLSL(String& s) {
	s.Replace("precision float;", "");
	if (s.Find("vec4 char(") >= 0)
		s.Replace("char(", "_char(");
}

bool OglCompiler::CompileShader(String code, ShaderVar::Type type, GLuint& shader_out) {
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
	CHKLOGRET0(shader_out > 0, "OglCompiler::CompileShader: error: glCreateShader failed unexpectedly");
	
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
		CHKLOGRET0(0, "OglCompiler::CompileShader: error: shader failed to compile: " + err);
	}
	
	return true;
}







bool OglLinker::Link(OglRuntimeState& rt) {
	CHKLOGRET0(rt.prog == 0, "OglLinker::Link: error: trying to overwrite compiled program");
	
	rt.prog = glCreateProgram();
	CHKLOGRET0(rt.prog > 0, "OglLinker::Link: error: opengl error")
	
	glProgramParameteri(rt.prog, GL_PROGRAM_SEPARABLE, GL_TRUE);
	
	uint8 complied_count = 0;
	EnableGfxAccelDebugMessages(1);
	for(int i = 0; i < ShaderVar::PROG_COUNT; i++) {
		OglShaderState& shd_state = rt.shaders[i];
		if (shd_state.shader == 0)
			continue;
		complied_count++;
		
		glAttachShader(rt.prog, shd_state.shader);
		glDeleteShader(shd_state.shader);
		shd_state.shader = 0;
	}
	EnableGfxAccelDebugMessages(0);
	CHKLOGRET0(complied_count, "OglLinker::Link: error: no compiled shaders found");
	
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

#endif

NAMESPACE_TOPSIDE_END

