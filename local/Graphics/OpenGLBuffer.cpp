#include "Graphics.h"

#ifdef flagGUI

NAMESPACE_TOPSIDE_BEGIN


int GetOglChCode(int channels, bool is_float) {
	if (!is_float) {
		switch (channels) {
			case 1: return GL_RED;
			case 2: return GL_RG;
			case 3: return GL_RGB;
			case 4: return GL_RGBA;
		}
	}
	else {
		switch (channels) {
			case 1: return GL_R32F;
			case 2: return GL_RG32F;
			case 3: return GL_RGB32F;
			case 4: return GL_RGBA32F;
		}
	}
	return 0;
}




bool OglBuffer::LoadFragmentShaderFile(String shader_path) {
	DLOG("OglBuffer::LoadFragmentShaderFile: " << shader_path);
	
	if (!FileExists(shader_path))
		shader_path = ShareDirFile(shader_path);
	
	if (!FileExists(shader_path)) {
		LOG("OglBuffer::LoadFragmentShaderFile: error: file does not exist: " << shader_path);
		return false;
	}
	
	String content = LoadFile(shader_path);
	if (content.IsEmpty()) {
		LOG("OglBuffer::LoadFragmentShaderFile: error: got empty shader file from: " << shader_path);
		return false;
	}
	
	DUMP(content);
	SetFragmentShaderSource(content);
	
	return true;
}

bool OglBuffer::InitializeTextureRGBA(Size sz, const Vector<byte>& data) {
	DLOG("OglBuffer::InitializeTextureRGBA: " << sz.ToString() << ", " << data.GetCount());
	
	UpdateTexBuffers();
	
	ReadTexture(sz, data);
	
	return true;
}

void OglBuffer::ReadTexture(Size sz, const Vector<byte>& data) {
	GLuint& color_buf = this->color_buf[0];
	ASSERT(color_buf > 0);
	ASSERT(sz == fb_size);
	glBindTexture (GL_TEXTURE_2D, color_buf);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F,
		sz.cx,
		sz.cy,
		0, GL_RGBA, GL_UNSIGNED_BYTE,
		data.Begin());
}

bool OglBuffer::Initialize() {
	DLOG("OglBuffer::Initialize: load new program");
	
	/*Object to_load;
	Swap(post_load, to_load);
	
	for(int i = 0; i < comps.GetCount(); i++) {
		FusionComponent& comp = *comps[i];
		if (comp.IsTypeTemporary()) {
			comp.Close();
			comp.GetECS().Destroy();
		}
	}
	
	Clear();
	FindComponents();
	DumpEntityComponents();
	
	Load(to_load);
	Reset();*/
	
	
	// If user connects buffers manually to sinks
	if (1) {
		
	}
	// Otherwise link sinks
	else {
		
	}
	
	
	
	if (!CompilePrograms())
		return false;
	
	if (!LinkStages())
		return false;
	
	
	/*
	//  Reload stage pointers
	RefreshStageQueue();
	
	
	
	DumpEntityComponents();
	
	is_open = true;
	for(Ref<FusionComponent>& comp : comps) {
		if (!comp->IsOpen() && !comp->Open()) {
			DLOG("OglBuffer::Initialize: error: a component did not open properly");
			is_open = false;
		}
	}
	
	if (!is_open) {
		DLOG("OglBuffer::Initialize: error: did not open properly");
		return false;
	}*/
	
	RefreshPipeline();
	
	initialized = true;
	
	return true;
}

void OglBuffer::RefreshPipeline() {
	DLOG("OglBuffer::RefreshPipeline begin");
	
	CreatePipeline();
	
	UpdateTexBuffers();
	
	if (!CheckInputTextures())
		return;
	
	Reset();
	
	DLOG("OglBuffer::RefreshPipeline end");
}

void OglBuffer::Reset() {
	time_total = 0;
}

const OglBuffer* OglBuffer::GetComponentById(int id) const {
	ASSERT(id >= 0);
	for (const OglBufferInput& s : in)
		if (s.id == id)
			return s.GetBuffer();
	return 0;
}

void OglBuffer::UpdateTexBuffers() {
	if (!is_win_fbo) {
		ASSERT(fb_channels > 0);
		ASSERT(fb_size.cx > 0 && fb_size.cy > 0);
		
		fb_sample_size			= fb_sampletype == SAMPLE_BYTE ? 1 : 4;
		fb_type					= fb_sampletype == SAMPLE_BYTE ? GL_UNSIGNED_BYTE : GL_FLOAT;
		fb_accel_sample_size	= fb_accel_sampletype == SAMPLE_BYTE ? 1 : 4;
		fb_accel_type			= fb_accel_sampletype == SAMPLE_BYTE ? GL_UNSIGNED_BYTE : GL_FLOAT;
		
		fb_size_bytes			= fb_size.cx * fb_size.cy * fb_sample_size;
		fb_accel_size_bytes		= fb_size.cx * fb_size.cy * fb_accel_sample_size;
		fb_fmt					= GetOglChCode(fb_channels, fb_type == GL_FLOAT);
		fb_accel_fmt			= GetOglChCode(fb_channels, fb_accel_type == GL_FLOAT);
		
		ASSERT(fb_size_bytes > 0);
		ASSERT(fb_accel_size_bytes > 0);
		ASSERT(fb_fmt >= 0);
		ASSERT(fb_accel_fmt >= 0);
		ASSERT(fb_type >= 0);
		ClearTex();
		
		CreateTex(
			true, true,
			OglBufferInput::FILTER_LINEAR,
			OglBufferInput::WRAP_CLAMP);
		
	}
}

int OglBuffer::NewWriteBuffer() {
	if (is_doublebuf)
		buf_i = (buf_i + 1) % 2;
	return buf_i;
}

void OglBuffer::ProcessStage(const RealtimeSourceConfig& cfg) {
	GLint& fg_prog = prog[OglBuffer::PROG_FRAGMENT];
	ASSERT(fg_prog >= 0);
	if (fg_prog < 0)
		return;
	
	RTLOG("OglBuffer::ProcessStage " << HexStr(this) << " time: " << cfg.time_total);
	
	time_total = cfg.time_total;
	//RTLOG("OglBuffer::ProcessStage: " << time_total);
	
	frames++;
	
	
	GLint prog = fg_prog;
	GLint uindex;
	
    glBindProgramPipeline(gl_stage);
	glUseProgram(prog);
	
	if (!is_searched_vars)
		FindVariables(prog);
	
	int bi = NewWriteBuffer();
	
	if (!is_win_fbo) {
		ASSERT(frame_buf[bi] > 0);
		const GLenum bufs[] = {GL_COLOR_ATTACHMENT0_EXT};
		
		// combine FBO
	    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, frame_buf[bi]);
	    
	    // set up render target
	    glDrawBuffers(sizeof bufs / sizeof bufs[0], bufs);
	}
	
	
	SetVars(prog, cfg);
	
	
	glClear(GL_COLOR_BUFFER_BIT);
	glRectf(-1.0, -1.0, 1.0, 1.0);
	
	
	
	EnableGfxAccelDebugMessages(1);
	
	ASSERT(is_win_fbo == (frame_buf[bi] == 0));
	if (frame_buf[bi] > 0) {
		// backup render target
	    //glDrawBuffer(GL_FRONT);
	    
	    // Some components (e.g. audio) needs to read the framebuffer
	    if (is_read_fb_output)
			UseRenderedFramebuffer();
		
	    // reset FBO
	    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
	}
	
	EnableGfxAccelDebugMessages(0);
	
	glBindProgramPipeline(0);
}

void OglBuffer::UseRenderedFramebuffer() {
	ASSERT(fb_size_bytes > 0);
	ASSERT(fb_size.cx > 0 && fb_size.cy > 0);
	ASSERT(fb_fmt >= 0);
	ASSERT(fb_type >= 0);
	
	fb_out.SetCount(fb_size_bytes);
	
	ASSERT(color_buf[buf_i] > 0);
	glReadBuffer(GL_COLOR_ATTACHMENT0_EXT);
	
	TODO // glReadPixels will crash mysteriously
	glReadPixels(0, 0, fb_size.cx, fb_size.cy, fb_fmt, fb_type, fb_out.Begin());
}

void OglBuffer::ClearPipeline() {
	if (gl_stage) {
		glDeleteProgramPipelines(1, &gl_stage);
		gl_stage = 0;
	}
}

void OglBuffer::CreatePipeline() {
	ClearPipeline();
	
	glGenProgramPipelines(1, &gl_stage);
	
	for(int j = 0; j < OglBuffer::PROG_COUNT; j++) {
		GLint& prog = this->prog[j];
		if (prog >= 0) {
			int bit = 1 << j;
			ASSERT(j != OglBuffer::PROG_VERTEX   || bit == GL_VERTEX_SHADER_BIT);
			ASSERT(j != OglBuffer::PROG_FRAGMENT || bit == GL_FRAGMENT_SHADER_BIT);
			glUseProgramStages(gl_stage, bit, prog);
		}
	}
}








void OglBuffer::FindVariables(GLint prog) {
	for(int i = 0; i < VAR_COUNT; i++) {
		const char* var_name = VarNames()[i];
		GLint idx = glGetUniformLocation(prog, var_name);
		var_idx[i] = idx;
	}
	is_searched_vars = true;
}

void OglBuffer::SetVars(GLint prog, const RealtimeSourceConfig& cfg) {
	for(int i = 0; i < VAR_COUNT; i++)
		if (var_idx[i] >= 0)
			SetVar(i, prog, cfg);
}

void OglBuffer::SetVar(int var, GLint prog, const RealtimeSourceConfig& cfg) {
	int uindex = var_idx[var];
	ASSERT(uindex >= 0);
	if (uindex < 0)
		return;
	
	if (var == VAR_MOUSE) {
		TODO
	}
	
	else if (var == VAR_AUDIOTIME) {
		glUniform1f(uindex, time_total);
	}
	
	else if (var == VAR_COMPAT_RESOLUTION) {
		ASSERT(fb_size.cx > 0 && fb_size.cy > 0);
		glUniform3f(uindex, fb_size.cx, fb_size.cy, 1.0);
	}
	
	else if (var == VAR_COMPAT_TIME) {
		//RTLOG("OglBuffer::SetVar: " << time_total);
		glUniform1f(uindex, time_total);
	}
	
	else if (var == VAR_COMPAT_TIMEDELTA) {
		ASSERT(frame_time != 0.0);
		glUniform1f(uindex, frame_time);
	}
	
	else if (var == VAR_COMPAT_FRAME) {
		ASSERT(frames >= 0);
		glUniform1i(uindex, frames);
	}
	
	else if (var == VAR_COMPAT_MOUSE) {
		glUniform4f(uindex,
			mouse_click.x,
			mouse_click.y,
			mouse_drag.x,
			mouse_drag.y);
	}
	
	else if (var == VAR_COMPAT_DATE) {
		double sec = ((int)time.hour * 60 + (int)time.minute) * 60 + (int)time.second;
		sec += 0.000001 * time_us;
		glUniform4f(uindex, time.year, time.month, time.day, sec);
	}
	
	else if (var == VAR_COMPAT_SAMPLERATE) {
		glUniform1f(uindex, sample_rate);
	}
	
	else if (var == VAR_COMPAT_OFFSET) {
		if (fb_size.cx > 0 && fb_size.cy > 0) {
			float x = fb_offset.x;
			float y = fb_size.cy - fb_size.cy - fb_offset.y; // -y_offset
			glUniform2f(uindex, x, y);
		} else {
			glUniform2f(uindex, 0.0, 0.0);
		}
	}
	
	else if (var >= VAR_COMPAT_CHANNEL0 && var <= VAR_COMPAT_CHANNEL3) {
		int ch = var - VAR_COMPAT_CHANNEL0;
		if (in.GetCount() >= ch+1) {
			int tex = GetInputTex(ch);
			ASSERT(tex != 0);
			glActiveTexture(GL_TEXTURE0 + ch);
			glBindTexture(GetTexType(ch), tex);
			glUniform1i(uindex, ch);
		}
	}
	
	else if (var == VAR_COMPAT_FRAMERATE) {
		ASSERT(fps > 0);
		glUniform1f(uindex, fps);
	}
	
	else if (var == VAR_COMPAT_CHANNELTIME) {
		double values[4];
		for(int j = 0; j < 4; j++) {
			if (j < in.GetCount()) {
				OglBufferInput& in = this->in[j];
				const OglBuffer* in_buf = in.GetBuffer();
				values[j] = in_buf->time_total;
			}
			else
				values[j] = time_total;
		}
		glUniform4f(uindex, values[0], values[1], values[2], values[3]);
	}
	
	else if (var >= VAR_COMPAT_CHANNELRESOLUTION0 && var <= VAR_COMPAT_CHANNELRESOLUTION3) {
		int ch = var - VAR_COMPAT_CHANNELRESOLUTION0;
		GLfloat values[3] = {0,0,0};
		if (ch < in.GetCount()) {
			OglBufferInput& in = this->in[ch];
			const OglBuffer* in_buf = in.GetBuffer();
			if (in.stream) {
				values[0] = in_buf->fb_size.cx;
				values[1] = in_buf->fb_size.cy;
				values[2] = in_buf->fb_depth;
			}
			/*else if (
				in.type == OglBufferInput::TEXTURE ||
				in.type == OglBufferInput::CUBEMAP ||
				in.type == OglBufferInput::VOLUME) {
				ASSERT(in.id >= 0);
				if (in.id >= 0 && ctx) {
					OglBuffer& comp = ctx->GetComponentById(in.id);
					values[0] = in.res.cx;
					values[1] = in.res.cy;
					values[2] = in.vol_depth;
				}
			}*/
		}
		glUniform3f(uindex, values[0], values[1], values[2]);
	}
	else {
		ASSERT_(false, "Invalid variable");
	}
}

void OglBuffer::ClearTex() {
	for(int bi = 0; bi < 2; bi++) {
		GLuint& color_buf = this->color_buf[bi];
		GLuint& depth_buf = this->depth_buf[bi];
		GLuint& frame_buf = this->frame_buf[bi];
		
		if (color_buf > 0) {
			glDeleteTextures(1, &color_buf);
			color_buf = 0;
		}
		if (depth_buf > 0) {
			glDeleteRenderbuffersEXT(1, &depth_buf);
			depth_buf = 0;
		}
		if (frame_buf > 0) {
			glDeleteFramebuffers(1, &frame_buf);
			frame_buf = 0;
		}
	}
}

void OglBuffer::ClearProg() {
	for(int i = 0; i < PROG_COUNT; i++) {
		auto& prog = this->prog[i];
		if (prog >= 0) {
			glDeleteProgram(prog);
			prog = -1;
		}
	}
}

void OglBuffer::CreateTex(bool create_depth, bool create_fbo, int filter, int repeat) {
	int buf_count = 1;
	if (is_doublebuf)
		buf_count++;
	
	Size sz = fb_size;
	int channels = fb_channels;
	
	EnableGfxAccelDebugMessages(1);
	
	for(int bi = 0; bi < buf_count; bi++) {
		GLuint& color_buf = this->color_buf[bi];
		GLuint& depth_buf = this->depth_buf[bi];
		GLuint& frame_buf = this->frame_buf[bi];
		ASSERT(color_buf == 0);
		
		ASSERT(fb_accel_fmt == GetOglChCode(4, true));
		ASSERT(fb_fmt == GetOglChCode(4, false));
		ASSERT(fb_type == GL_UNSIGNED_BYTE);
		
		// color buffer
		glGenTextures(1, &color_buf);
		glBindTexture(GL_TEXTURE_2D, color_buf);
		glTexImage2D(GL_TEXTURE_2D, 0, fb_accel_fmt, sz.cx, sz.cy, 0, fb_fmt, fb_type, 0);
		TexFlags(GL_TEXTURE_2D, filter, repeat);
		glBindTexture(GL_TEXTURE_2D, 0);
		
		// depth buffer
		if (create_depth) {
			glGenRenderbuffersEXT(1, &depth_buf);
			glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, depth_buf);
			glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT, sz.cx, sz.cy);
			glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, 0);
		}
		
		// FBO
		if (create_fbo) {
			glGenFramebuffersEXT(1, &frame_buf);
			glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, frame_buf);
			
			// combine FBO to color buffer
			glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, color_buf, 0);
			
			// combine FBO to depth buffer
			if (create_depth)
				glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, depth_buf);
			
			// reset FBO
			glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
		}
	}
	
	EnableGfxAccelDebugMessages(0);
}

GLint OglBuffer::GetInputTex(int input_i) const {
	const char* fn_name = "GetInputTex";
	//DLOG("OglBuffer::GetInputTex");
	if (input_i < 0 || input_i >= in.GetCount())
		return -1;
	
	const OglBufferInput& in = this->in[input_i];
	const OglBuffer* in_comp = GetComponentById(in.id);
	if (!in_comp)
		return -1;
	
	int tex = in_comp->GetOutputTexture(in_comp == this);
	ASSERT(tex > 0);
	
	return tex;
}

int OglBuffer::GetTexType(int input_i) const {
	const OglBufferInput& in = this->in[input_i];
	
	if (in.type == OglBufferInput::VOLUME)
		return GL_TEXTURE_3D;
	
	else if (in.type == OglBufferInput::CUBEMAP)
		return GL_TEXTURE_CUBE_MAP;
	
	else
		return GL_TEXTURE_2D;
}










bool OglBuffer::CompilePrograms() {
	const char* fn_name = "CompilePrograms";
	for(int i = 0; i < PROG_COUNT; i++) {
		if (i == PROG_FRAGMENT && !CompileFragmentShader())
			return false;
	}
	
	return true;
}

bool OglBuffer::CompileFragmentShader() {
	const char* fn_name = "CompilePrograms";
	
	ASSERT(prog[PROG_FRAGMENT] < 0);
	String& fg_glsl = code[PROG_FRAGMENT];
	if (fg_glsl.GetCount() == 0) {
		OnError(fn_name, "empty source code");
		return false;
	}
	
	DLOG("\tCompiling stage: " << id << ": " << name);
	
	String code;
	
	code =		"#version 430\n"
				"#define GL_ES\n"
	
				"uniform vec2      in_mouse;\n"
				"uniform float     in_audio_seconds;\n"
				
				"uniform vec3      iResolution;           // viewport resolution (in pixels)\n"
				"uniform float     iTime;                 // shader playback time (in seconds)\n"
				"uniform float     iTimeDelta;            // duration since the previous frame (in seconds)\n"
				"uniform int       iFrame;                // frames since the shader (re)started\n"
				"uniform vec2      iOffset;               \n"
				"uniform vec4      iMouse;                // mouse pixel coords. xy: current (if MLB down), zw: click\n"
				"uniform vec4      iDate;                 // (year, month, day, time in secs)\n"
				"uniform float     iFrameRate;\n"
				"uniform float     iSampleRate;           // sound sample rate (i.e., 44100)\n"
				"uniform float     iChannelTime[4];       // channel playback time (in seconds)\n"
				"uniform vec3      iChannelResolution[4]; // channel resolution (in pixels)\n"
				;
	
	for(int j = 0; j < 4; j++) {
		if (j < in.GetCount()) {
			OglBufferInput& in = this->in[j];
			if (in.type == OglBufferInput::CUBEMAP)
				code << "uniform samplerCube iChannel" << IntStr(j) << ";\n";
			else if (in.type == OglBufferInput::VOLUME)
				code << "uniform sampler3D iChannel" << IntStr(j) << ";\n";
			else
				code << "uniform sampler2D iChannel" << IntStr(j) << ";\n";
		}
		else
			code << "uniform sampler2D iChannel" << IntStr(j) << ";\n";
	}
	code << "\n";
	
	for(int j = 0; j < common_source.GetCount(); j++) {
		code += common_source[j] + "\n";
	}
	
	code += fg_glsl;
	
	if (is_shader_audio_main) {
		code +=		"\nvoid main (void) {\n"
					"	float t = in_audio_seconds + gl_FragCoord.x / iSampleRate;\n"
					"	vec2 value = mainSound (t);\n"
					"	gl_FragColor = vec4(value, 0.0, 1.0);\n"
					"}\n\n";
	}
	else {
		code +=		"\nvoid main (void) {\n"
					"	vec4 color = vec4 (0.0, 0.0, 0.0, 1.0);\n"
					"	mainImage (color, gl_FragCoord.xy);\n"
					"	gl_FragColor = color;\n"
					"}\n\n";
	}
	
	// Hotfixes
	code.Replace("precision float;", "");
	if (code.Find("vec4 char(") >= 0)
		code.Replace("char(", "_char(");
	
	//LOG(code);
	
	if (!CompileProgram(PROG_FRAGMENT, code)) {
		LOG(GetLineNumStr(code));
		return false;
	}
	
	return true;
}

bool OglBuffer::CompileProgram(int prog_i, String shader_source) {
	GLint frag, program;
	
	EnableGfxAccelDebugMessages(1);
	
	frag = CompileShader(prog_i, shader_source);
	if (frag < 0)
		return false;
		
	program = glCreateProgram();
	glProgramParameteri(program, GL_PROGRAM_SEPARABLE, GL_TRUE);
	
	glAttachShader(program, frag);
	glDeleteShader (frag);
	
	prog[prog_i] = program;
	
	is_searched_vars = false;
	
	EnableGfxAccelDebugMessages(0);
	
	return true;
}

GLint OglBuffer::CompileShader(int prog_i, String shader_source) {
	const char* fn_name = "CompileShader";
	
	GLenum shader_type;
	if (prog_i == PROG_FRAGMENT) {
		shader_type = GL_FRAGMENT_SHADER;
	}
	else {
		OnError(fn_name, "TODO: other programs than fragment shader");
		return -1;
	}
	
	GLuint shader = glCreateShader(shader_type);
	GLint status = GL_FALSE;
	GLint loglen;
	GLchar *error_message;
	if (shader == 0) {
		OnError(fn_name, "glCreateShader failed unexpectedly");
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
		OnError(fn_name, "shader failed to compile: " + String(msg.Begin()));
		return -1;
	}
	
	return shader;
}

bool OglBuffer::LinkStages() {
	const char* fn_name = "LinkStages";
	for(int j = 0; j < OglBuffer::PROG_COUNT; j++) {
		if (prog[j] >= 0) {
			LOG("\tLinking stage: " << name << ": program " << j);
			
			if (!LinkProgram(j))
				return false;
		}
	}
	
	return true;
}

bool OglBuffer::LinkProgram(int prog_i) {
	const char* fn_name = "LinkProgram";
	GLint program = prog[prog_i];
	GLint status = GL_FALSE;
	GLint loglen, n_uniforms;
	
	if (program < 0) {
		OnError(fn_name, "internal error: opengl program was expected to be valid");
		return false;
	}
	
	glLinkProgram(program);
	
	glGetProgramiv(program, GL_LINK_STATUS, &status);
	if (status != GL_TRUE) {
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &loglen);
		Vector<GLchar> msg;
		msg.SetCount(loglen);
		glGetProgramInfoLog(program, loglen, NULL, msg.Begin());
		if (loglen) {
			String s;
			s.Set(msg.Begin(), loglen);
			OnError(fn_name, s);
		}
		else
			OnError(fn_name, "linking failed with unknown error");
		return false;
	}
	
	// diagnostics
	glGetProgramiv(program, GL_ACTIVE_UNIFORMS, &n_uniforms);
	LOG("\t\t" << (int)n_uniforms << " uniforms:");
	
	GLchar name[80];
	GLsizei namelen;
	for (int i = 0; i < n_uniforms; i++) {
		GLint size;
		GLenum type;
		
		glGetActiveUniform(program, i, 79, &namelen, &size, &type, name);
		name[namelen] = '\0';
		LOG("\t\t\t" << i << ": " << String(name) << " (type: " << HexStr(type) << ", size: " << (int)size << ")");
	}
	
	return true;
}

bool OglBuffer::CheckInputTextures() {
	const char* fn_name = "CheckInputTextures";
	bool fail = false;
	for(int i = 0; i < PROG_COUNT; i++) {
		auto& prog = this->prog[i];
		if (prog >= 0) {
			for(int j = 0; j < CHANNEL_COUNT; j++) {
				GLint uindex = glGetUniformLocation(prog, "iChannel" + IntStr(j));
				if (uindex >= 0) {
					if (in.GetCount() > j) {
						int tex = GetInputTex(j);
						if (tex == 0) {
							OnError(fn_name,
								"no texture for stage " + IntStr(id) +
								", program " + IntStr(i) +
								", channel " + IntStr(j));
							fail = true;
						}
					}
				}
			}
		}
	}
	return !fail;
}

GLint OglBuffer::GetOutputTexture(bool reading_self) const {
	ASSERT(!reading_self || is_doublebuf);
	int buf_i = this->buf_i;
	if (reading_self)
		buf_i = (buf_i + 1) % 2;
	if (color_buf[buf_i] == 0) {DLOG("GetOutputTexture failed");}
	ASSERT(color_buf[buf_i] > 0);
	return color_buf[buf_i];
}

void OglBuffer::TexFlags(int type, int filter, int repeat) {
	if (filter == OglBufferInput::FILTER_NEAREST) {
		glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	}
	else if (filter == OglBufferInput::FILTER_LINEAR) {
		glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}
	else if (filter == OglBufferInput::FILTER_MIPMAP) {
		glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glGenerateMipmap(type);
	}
	
	if (repeat == OglBufferInput::WRAP_REPEAT) {
		glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);
		if (type == GL_TEXTURE_3D)
			glTexParameteri(type, GL_TEXTURE_WRAP_R, GL_REPEAT);
	}
	else if (repeat == OglBufferInput::WRAP_CLAMP) {
		glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_CLAMP);
		if (type == GL_TEXTURE_3D)
			glTexParameteri(type, GL_TEXTURE_WRAP_R, GL_CLAMP);
	}
}

void OglBuffer::OnError(const char* fn, String s) {
	LOG("OglBuffer: error: " << (String)fn << ": " << s);
}

void OglBuffer::StoreOutputLink(InternalPacketData& v) {
	static_assert(sizeof(v.u32) == sizeof(GLuint), "Unexpected GLuint size");
	
	v.ptr = this;
}

bool OglBuffer::LoadOutputLink(int in_id, InternalPacketData& v) {
	String buf_id = v.GetText();
	
	if (in_id >= 0) {
		if (in_id <= in.GetCount())
			in.SetCount(in_id+1);
		
		ASSERT(v.ptr);
		OglBufferInput& in = this->in[in_id];
		in.id = in_id;
		in.in_buf = (OglBuffer*)v.ptr;
		
		return true;
	}
	
	RTLOG("OglBuffer::LoadOutputLink: error: unexpected data");
	return false;
}


NAMESPACE_TOPSIDE_END

#endif
