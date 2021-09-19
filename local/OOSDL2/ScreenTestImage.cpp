#include "OOSDL2.h"

#ifdef flagGUI

NAMESPACE_SDL2_BEGIN

const char* def_shader = R"SH4D3R(
#define M_PI	3.1415926535897932384626433832795

void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
    vec3 res = iResolution;
    float t = float(iFrame) / 60.0;
    bool mode = mod(t, 6.0) > 3.0;
    t = t * 504;
    //t = t * 0.2;
    vec3 shift = vec3(
        sin(t),
        sin(t + M_PI/3.0),
        sin(t + M_PI*2.0/3.0));
    if (mode)
        fragColor = vec4(
            fragCoord.x / res.x + shift.x,
            fragCoord.y / res.y + shift.y,
            1.0 - fragCoord.y / res.y + shift.z, 0);
    else
        fragColor = vec4(fragCoord.y/res.y + shift.x, (shift.y + 1.0) * 0.5, fragCoord.x/res.x, 0);
}
)SH4D3R";

bool Screen::TestImageInitialize() {
	if (is_opengl)
		return Ogl_Initialize();
	
	return false;
}

void Screen::TestImageRender() {
	if (is_opengl)
		Ogl_Render();
}

bool Screen::Ogl_Initialize() {
	gltest.glsl = def_shader;

	if (!Ogl_CompilePrograms())
		return false;
	
	if (!Ogl_LinkStages())
		return false;
	
	Ogl_RefreshPipeline();
	
	gltest.is_vars_searched = false;
	
	return true;
}

void Screen::Ogl_RefreshPipeline() {
	Ogl_CreatePipeline();
}

void Screen::Ogl_Render() {
	RTLOG("Screen::Ogl_Render");
	ASSERT(gltest.prog > 0);
	ASSERT(gltest.stage > 0);
	if (gltest.prog < 0)
		return;
	
    glBindProgramPipeline(gltest.stage);
	glUseProgram(gltest.prog);
	
	if (!gltest.is_vars_searched) {
		gltest.is_vars_searched = true;
		Ogl_FindVariables();
	}
	
	Ogl_SetVars();
	
	glClear(GL_COLOR_BUFFER_BIT);
	glRectf(-1.0, -1.0, 1.0, 1.0);
	
	glBindProgramPipeline(0);
	
	gltest.frames++;
}

void Screen::Ogl_FindVariables() {
	for(int i = 0; i < VAR_COUNT; i++) {
		const char* var_name = VarNames()[i];
		GLint idx = glGetUniformLocation(gltest.prog, var_name);
		gltest.var_idx[i] = idx;
	}
}

void Screen::Ogl_ClearPipeline() {
	if (gltest.stage > 0) {
		glDeleteProgramPipelines(1, &gltest.stage);
		gltest.stage = 0;
	}
}

void Screen::Ogl_CreatePipeline() {
	Ogl_ClearPipeline();
	
	glGenProgramPipelines(1, &gltest.stage);
	
	if (gltest.prog >= 0) {
		glUseProgramStages(gltest.stage, GL_FRAGMENT_SHADER_BIT, gltest.prog);
	}
}

void Screen::Ogl_ClearTex() {
	if (gltest.color_buf > 0) {
		glDeleteTextures(1, &gltest.color_buf);
		gltest.color_buf = 0;
	}
}

void Screen::Ogl_ClearProg() {
	if (gltest.prog >= 0) {
		glDeleteProgram(gltest.prog);
		gltest.prog = -1;
	}
}

void Screen::Ogl_CreateTex(Size sz) {
	OOSDL2::EnableOpenGLDebugMessages(1);
	
	{
		// color buffer
		glGenTextures(1, &gltest.color_buf);
		glBindTexture(GL_TEXTURE_2D, gltest.color_buf);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, sz.cx, sz.cy, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
		Ogl_TexFlags(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	
	OOSDL2::EnableOpenGLDebugMessages(0);
}

bool Screen::Ogl_CompilePrograms() {
	return Ogl_CompileFragmentShader();
}

bool Screen::Ogl_CompileFragmentShader() {
	if (gltest.glsl.GetCount() == 0)
		return false;
	
	String code;
	
	code =		"#version 430\n"
				"#define GL_ES\n"
	
				"uniform vec3    iResolution; \n"
				"uniform int     iFrame;\n"
				;
	
	code += gltest.glsl;
	
	code +=		"\nvoid main (void) {\n"
				"	vec4 color = vec4 (0.0, 0.0, 0.0, 1.0);\n"
				"	mainImage (color, gl_FragCoord.xy);\n"
				"	gl_FragColor = color;\n"
				"}\n\n";
	
	LOG(code);
	
	if (!Ogl_CompileProgram(code)) {
		LOG(GetLineNumStr(code));
		Close();
		return false;
	}
	
	return true;
}

bool Screen::Ogl_CompileProgram(String shader_source) {
	OOSDL2::EnableOpenGLDebugMessages(1);
	
	GLint frag = Ogl_CompileShader(shader_source);
	if (frag < 0)
		return false;
		
	gltest.prog = glCreateProgram();
	glProgramParameteri(gltest.prog, GL_PROGRAM_SEPARABLE, GL_TRUE);
	
	glAttachShader(gltest.prog, frag);
	glDeleteShader(frag);
	frag = 0;
	
	OOSDL2::EnableOpenGLDebugMessages(0);
	
	return true;
}

GLint Screen::Ogl_CompileShader(String shader_source) {
	GLenum shader_type = GL_FRAGMENT_SHADER;
	GLuint shader = glCreateShader(shader_type);
	GLint status = GL_FALSE;
	GLint loglen;
	GLchar *error_message;
	if (shader == 0) {
		RTLOG("Screen::Ogl_CompileShader: glCreateShader failed unexpectedly");
		return -1;
	}
	
	const GLchar* src = shader_source.Begin();
	int len = shader_source.GetCount();
	glShaderSource(shader, 1, &src, &len);
	glCompileShader(shader);
	
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status != GL_TRUE) {
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &loglen);
		Vector<GLchar> msg;
		msg.SetCount(loglen);
		glGetShaderInfoLog(shader, loglen, NULL, msg.Begin());
		RTLOG("Screen::Ogl_CompileShader: shader failed to compile: " + String(msg.Begin()));
		return -1;
	}
	
	return shader;
}

bool Screen::Ogl_LinkStages() {
	if (gltest.prog >= 0) {
		if (!Ogl_LinkProgram()) {
			Close();
			return false;
		}
	}
	
	return true;
}

bool Screen::Ogl_LinkProgram() {
	GLint status = GL_FALSE;
	GLint loglen, n_uniforms;
	
	if (gltest.prog < 0)
		return false;
	
	glLinkProgram(gltest.prog);
	
	glGetProgramiv(gltest.prog, GL_LINK_STATUS, &status);
	if (status != GL_TRUE) {
		glGetProgramiv(gltest.prog, GL_INFO_LOG_LENGTH, &loglen);
		Vector<GLchar> msg;
		msg.SetCount(loglen);
		glGetProgramInfoLog(gltest.prog, loglen, NULL, msg.Begin());
		if (loglen) {
			String s;
			s.Set(msg.Begin(), loglen);
			RTLOG("Screen::Ogl_LinkProgram: error: " << s);
		}
		else{
			RTLOG("Screen::Ogl_LinkProgram: error: linking failed (unknown error)");
		}
		return false;
	}
	
	// diagnostics
	glGetProgramiv(gltest.prog, GL_ACTIVE_UNIFORMS, &n_uniforms);
	RTLOG("Screen::Ogl_LinkProgram: " << (int)n_uniforms << " uniforms:");
	
	GLchar name[80];
	GLsizei namelen;
	for (int i = 0; i < n_uniforms; i++) {
		GLint size;
		GLenum type;
		
		glGetActiveUniform(gltest.prog, i, 79, &namelen, &size, &type, name);
		name[namelen] = '\0';
		RTLOG("Screen::Ogl_LinkProgram: " << i << ": " << String(name) << " (type: " << HexStr(type) << ", size: " << (int)size << ")");
	}
	
	return true;
}

void Screen::Ogl_TexFlags(int type) {
	glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_CLAMP);
}

void Screen::Ogl_SetVars() {
	for(int i = 0; i < VAR_COUNT; i++)
		if (gltest.var_idx[i] >= 0)
			Ogl_SetVar(i);
}

void Screen::Ogl_SetVar(int var) {
	int uindex = gltest.var_idx[var];
	ASSERT(uindex >= 0);
	if (uindex < 0)
		return;
	
	if (var == VAR_RESOLUTION) {
		glUniform3f(uindex, (float)screen_sz.cx, (float)screen_sz.cy, 1.0f);
	}
	else if (var == VAR_FRAMES) {
		RTLOG("iFrame = " << gltest.frames);
		glUniform1i(uindex, gltest.frames);
	}
	
}

NAMESPACE_SDL2_END

#endif
