#include "Graphics.h"


NAMESPACE_TOPSIDE_BEGIN

OglCompiler::OglCompiler() {
	
}



const char* shader_tmpl = R"SH4D3R(
#version 430
#define GL_ES

#if ${IS_FRAGMENT_SHADER}
uniform ${SAMPLER0} iChannel0;
uniform ${SAMPLER1} iChannel1;
uniform ${SAMPLER2} iChannel2;
uniform ${SAMPLER3} iChannel3;
#elif ${IS_VERTEX_SHADER}
layout (location = 0) in vec3 iPos;
layout (location = 1) in vec3 iNormal;
layout (location = 2) in vec2 iTexCoords;

in int gl_VertexID;
in int gl_InstanceID;

out vec2 TexCoords;
out gl_PerVertex
{
  vec4 gl_Position;
  float gl_PointSize;
  float gl_ClipDistance[];
};

#endif

uniform float     iAudioSeconds;
uniform mat4      iView;
uniform mat4      iProjection;
uniform mat4      iScale;
uniform mat4      iTransform;
uniform mat4      iModel;

uniform vec3      iResolution;           // viewport resolution (in pixels)
uniform float     iTime;                 // shader playback time (in seconds)
uniform float     iTimeDelta;            // duration since the previous frame (in seconds)
uniform int       iFrame;                // frames since the shader (re)started
uniform vec2      iOffset;
uniform vec4      iMouse;                // mouse pixel coords. xy: current (if MLB down), zw: click
uniform vec4      iDate;                 // (year, month, day, time in secs)
uniform float     iFrameRate;
uniform float     iSampleRate;           // sound sample rate (i.e., 44100)
uniform float     iChannelTime[4];       // channel playback time (in seconds)
uniform vec3      iChannelResolution[4]; // channel resolution (in pixels)
uniform float     iBlockOffset;          // total consumed samples (mostly for audio, for video it's same as iFrame)

${USER_LIBRARY}
${USER_CODE}

#if ${IS_FRAGMENT_SHADER}
#if ${IS_AUDIO}
void main (void) {
	float t = iAudioSeconds + gl_FragCoord.x / iSampleRate;
	vec2 value = mainSound (t);
	gl_FragColor = vec4(value, 0.0, 1.0);
}
#else
void main (void) {
	vec4 color = vec4 (0.0, 0.0, 0.0, 1.0);
	mainImage (color, gl_FragCoord.xy);
	gl_FragColor = color;
}
#endif
#elif ${IS_VERTEX_SHADER}
void main (void) {
	mainVertex();
}
#endif
)SH4D3R";


bool OglCompiler::Compile(OglFramebufferState& fb_state, OglShaderState& shd_state, ShaderVar::Type type, String user_code, String library) {
	bool succ = true;
	String code = shader_tmpl;
	
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
	code.Replace("${IS_AUDIO}", IntStr(fb_state.is_audio));
	code.Replace("${USER_CODE}", user_code);
	code.Replace("${USER_LIBRARY}", library);
	code.Replace("${SAMPLER0}", sampler0);
	code.Replace("${SAMPLER1}", sampler1);
	code.Replace("${SAMPLER2}", sampler2);
	code.Replace("${SAMPLER3}", sampler3);
	
	LOG(code);
	
	{
		EnableGfxAccelDebugMessages(1);
		
		succ = CompileShader(code, type, shd_state.shader);
		
		fb_state.is_searched_vars = false;
		
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
		err = String(msg.Begin());
		CHKLOGRET0(0, "OglCompiler::CompileShader: error: shader failed to compile: " + err);
	}
	
	return true;
}







bool OglLinker::Link(OglFramebufferState& fb_state) {
	CHKLOGRET0(fb_state.prog < 0, "OglLinker::Link: error: trying to overwrite compiled program");
	
	fb_state.prog = glCreateProgram();
	CHKLOGRET0(fb_state.prog >= 0, "OglLinker::Link: error: opengl error")
	
	glProgramParameteri(fb_state.prog, GL_PROGRAM_SEPARABLE, GL_TRUE);
	
	uint8 complied_count = 0;
	EnableGfxAccelDebugMessages(1);
	for(int i = 0; i < ShaderVar::PROG_COUNT; i++) {
		OglShaderState& shd_state = fb_state.shaders[i];
		if (shd_state.shader < 0)
			continue;
		complied_count++;
		
		glAttachShader(fb_state.prog, shd_state.shader);
		glDeleteShader(shd_state.shader);
		shd_state.shader = 0;
	}
	EnableGfxAccelDebugMessages(0);
	CHKLOGRET0(complied_count, "OglLinker::Link: error: no compiled shaders found");
	
	glLinkProgram(fb_state.prog);
	
	GLint status = GL_FALSE;
	GLint loglen, n_uniforms;
	glGetProgramiv(fb_state.prog, GL_LINK_STATUS, &status);
	if (status != GL_TRUE) {
		glGetProgramiv(fb_state.prog, GL_INFO_LOG_LENGTH, &loglen);
		Vector<GLchar> msg;
		msg.SetCount(loglen);
		glGetProgramInfoLog(fb_state.prog, loglen, NULL, msg.Begin());
		if (loglen) {
			String s;
			s.Set(msg.Begin(), loglen);
			err = s;
		}
		else
			err ="linking failed with unknown error";
		return false;
	}
	
	// diagnostics
	if (log) {
		glGetProgramiv(fb_state.prog, GL_ACTIVE_UNIFORMS, &n_uniforms);
		LOG("\t\t" << (int)n_uniforms << " uniforms:");
		
		GLchar name[80];
		GLsizei namelen;
		for (int i = 0; i < n_uniforms; i++) {
			GLint size;
			GLenum type;
			
			glGetActiveUniform(fb_state.prog, i, 79, &namelen, &size, &type, name);
			name[namelen] = '\0';
			LOG("\t\t\t" << i << ": " << String(name) << " (type: " << HexStr(type) << ", size: " << (int)size << ")");
		}
	}
	
	return true;
}


NAMESPACE_TOPSIDE_END
