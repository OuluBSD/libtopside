#include "AccelCore.h"

#if HAVE_OPENGL

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


void Ogl_RemoveToken(String& glsl, String token) {
	if (glsl.Left(token.GetCount() + 1) == token + " ") glsl = glsl.Mid(token.GetCount() + 1);
	glsl.Replace((String)" " + token + " ", " ");
	glsl.Replace((String)"\n" + token + " ", "\n");
}






void AccelComponentGroup::Ogl_ProcessStage(AccelComponentRef s_, GLuint gl_stage) {
	SCOPE_REF(s)
	GLint& fg_prog = s.prog[AccelComponent::PROG_FRAGMENT];
	ASSERT(fg_prog >= 0 || !s.RequiresShaderCode());
	if (fg_prog < 0)
		return;
	
	GLint prog = fg_prog;
	GLint uindex;
	
    glBindProgramPipeline(gl_stage);
	glUseProgram(prog);
	
	if (!s.is_searched_vars)
		s.Ogl_FindVariables(prog);
	
	int bi = s.NewWriteBuffer();
	
	if (!s.IsSinkInAccelerator()) {
		ASSERT(s.frame_buf[bi] > 0);
		const GLenum bufs[] = {GL_COLOR_ATTACHMENT0_EXT};
		
		// combine FBO
	    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, s.frame_buf[bi]);
	    
	    // set up render target
	    glDrawBuffers(sizeof bufs / sizeof bufs[0], bufs);
	}
	
	s.Ogl_SetVars(prog, stream);
	
	glClear(GL_COLOR_BUFFER_BIT);
	glRectf(-1.0, -1.0, 1.0, 1.0);
	
	
	
	OOSDL2::EnableOpenGLDebugMessages(1);
	
	if (s.frame_buf[bi] > 0) {
		// backup render target
	    //glDrawBuffer(GL_FRONT);
	    
	    // Some components (e.g. audio) needs to read the framebuffer
		s.UseRenderedFramebuffer();
		
	    // reset FBO
	    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
	}
	
	OOSDL2::EnableOpenGLDebugMessages(0);
	
	glBindProgramPipeline(0);
}

void AccelComponentGroup::Ogl_ClearPipeline() {
	if (gl_stages.GetCount()) {
		glDeleteProgramPipelines(gl_stages.GetCount(), gl_stages.Begin());
		gl_stages.Clear();
	}
}

void AccelComponentGroup::Ogl_CreatePipeline() {
	Ogl_ClearPipeline();
	
	gl_stages.SetCount(comps.GetCount());
	glGenProgramPipelines(gl_stages.GetCount(), gl_stages.Begin());
	
	int i = 0;
	for (AccelComponentRef& comp : comps) {
		uint32& gl_s = gl_stages[i];
		
		for(int j = 0; j < AccelComponent::PROG_COUNT; j++) {
			GLint& prog = comp->prog[j];
			if (prog >= 0) {
				int bit = 1 << j;
				ASSERT(j != AccelComponent::PROG_VERTEX   || bit == GL_VERTEX_SHADER_BIT);
				ASSERT(j != AccelComponent::PROG_FRAGMENT || bit == GL_FRAGMENT_SHADER_BIT);
				glUseProgramStages(gl_s, bit, prog);
			}
		}
		
		++i;
	}
}








void AccelComponent::Ogl_FindVariables(GLint prog) {
	for(int i = 0; i < VAR_COUNT; i++) {
		const char* var_name = names[i];
		GLint idx = glGetUniformLocation(prog, var_name);
		var_idx[i] = idx;
	}
	is_searched_vars = true;
}

void AccelComponent::Ogl_SetVars(GLint prog, const AccelStream& stream) {
	for(int i = 0; i < VAR_COUNT; i++)
		if (var_idx[i] >= 0)
			Ogl_SetVar(i, prog, stream);
}

void AccelComponent::Ogl_SetVar(int var, GLint prog, const AccelStream& stream) {
	int uindex = var_idx[var];
	ASSERT(uindex >= 0);
	if (uindex < 0)
		return;
	
	if (var == VAR_MOUSE) {
		TODO
	}
	
	else if (var == VAR_AUDIOTIME) {
		glUniform1f(uindex, stream.atotal_seconds);
	}
	
	else if (var == VAR_COMPAT_RESOLUTION) {
		glUniform3f(uindex, stream.video_size.cx, stream.video_size.cy, 1.0);
	}
	
	else if (var == VAR_COMPAT_TIME) {
		glUniform1f(uindex, stream.vtotal_seconds);
	}
	
	else if (var == VAR_COMPAT_TIMEDELTA) {
		glUniform1f(uindex, stream.frame_seconds);
	}
	
	else if (var == VAR_COMPAT_FRAME) {
		if (IsIn<AudioContext>())
			glUniform1i(uindex, stream.aframes);
		else
			glUniform1i(uindex, stream.vframes);
	}
	
	else if (var == VAR_COMPAT_MOUSE) {
		glUniform4f(uindex,
			stream.mouse_toycompat_click.x,
			stream.mouse_toycompat_click.y,
			stream.mouse_toycompat_drag.x,
			stream.mouse_toycompat_drag.y);
	}
	
	else if (var == VAR_COMPAT_DATE) {
		double sec = ((int)stream.time.hour * 60 + (int)stream.time.minute) * 60 + (int)stream.time.second;
		sec += 0.000001 * stream.time_us;
		glUniform4f(uindex, stream.time.year, stream.time.month, stream.time.day, sec);
	}
	
	else if (var == VAR_COMPAT_SAMPLERATE) {
		glUniform1f(uindex, stream.aud_fmt.freq);
	}
	
	else if (var == VAR_COMPAT_OFFSET) {
		if (stream.video_size.cx > 0 && stream.video_size.cy > 0) {
			float x = stream.video_offset.x;
			float y = stream.video_size.cy - stream.video_size.cy - stream.video_offset.y; // -y_offset
			glUniform2f(uindex, x, y);
		} else {
			glUniform2f(uindex, 0.0, 0.0);
		}
	}
	
	else if (var >= VAR_COMPAT_CHANNEL0 && var <= VAR_COMPAT_CHANNEL3) {
		int ch = var - VAR_COMPAT_CHANNEL0;
		if (in.GetCount() >= ch+1) {
			int tex = Ogl_GetInputTex(ch);
			ASSERT(tex != 0);
			glActiveTexture(GL_TEXTURE0 + ch);
			glBindTexture(Ogl_GetTexType(ch), tex);
			glUniform1i(uindex, ch);
		}
	}
	
	else if (var == VAR_COMPAT_FRAMERATE) {
		glUniform1f(uindex, stream.fps_limit);
	}
	
	else if (var == VAR_COMPAT_CHANNELTIME) {
		double values[4];
		int j = 0;
		for (AcceleratorHeader& h : in) {
			TODO // get time from packet
			/*if (h.stream)
				values[j] = h.stream->GetSeconds();
			else
				values[j] = stream.vtotal_seconds;*/
			
			++j;
		}
		for(; j < 4; ++j) {
			values[j] = stream.vtotal_seconds;
		}
		glUniform4f(uindex, values[0], values[1], values[2], values[3]);
	}
	
	else if (var >= VAR_COMPAT_CHANNELRESOLUTION0 && var <= VAR_COMPAT_CHANNELRESOLUTION3) {
		int ch = var - VAR_COMPAT_CHANNELRESOLUTION0;
		GLfloat values[3] = {0,0,0};
		if (ch < in.GetCount()) {
			AcceleratorHeader& in = this->in.At(ch);
			if (in.GetVideo()) {
				const auto& fmt = in.GetVideo()->GetActiveFormat();
				values[0] = fmt.res.cx;
				values[1] = fmt.res.cy;
				values[2] = fmt.GetChannelCountFD();
			}
			/*else if (
				in.type == AcceleratorHeader::TEXTURE ||
				in.type == AcceleratorHeader::CUBEMAP ||
				in.type == AcceleratorHeader::VOLUME) {
				ASSERT(in.id >= 0);
				if (in.id >= 0 && ctx) {
					AccelComponentRef comp = ctx->GetComponentById(in.id);
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

void AccelComponent::Ogl_ClearTex() {
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

void AccelComponent::Ogl_ClearProg() {
	for(int i = 0; i < PROG_COUNT; i++) {
		auto& prog = this->prog[i];
		if (prog >= 0) {
			glDeleteProgram(prog);
			prog = -1;
		}
	}
}

void AccelComponent::Ogl_UpdateTex(Size sz, const Vector<byte>& data) {
	glBindTexture(GL_TEXTURE_2D, color_buf[0]);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, sz.cx, sz.cy, GL_RED, GL_UNSIGNED_BYTE, data.Begin());
	glBindTexture(GL_TEXTURE_2D, 0);
}

void AccelComponent::Ogl_CreateTex(Size sz, int channels, bool create_depth, bool create_fbo, int filter, int repeat) {
	int buf_count = 1;
	if (is_doublebuf)
		buf_count++;
	
	OOSDL2::EnableOpenGLDebugMessages(1);
	
	for(int bi = 0; bi < buf_count; bi++) {
		GLuint& color_buf = this->color_buf[bi];
		GLuint& depth_buf = this->depth_buf[bi];
		GLuint& frame_buf = this->frame_buf[bi];
		ASSERT(color_buf == 0);
		
		// color buffer
		glGenTextures(1, &color_buf);
		glBindTexture(GL_TEXTURE_2D, color_buf);
		glTexImage2D(GL_TEXTURE_2D, 0, GetOglChCode(channels, true), sz.cx, sz.cy, 0, GetOglChCode(channels), GL_UNSIGNED_BYTE, 0);
		Ogl_TexFlags(GL_TEXTURE_2D, filter, repeat);
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
	
	OOSDL2::EnableOpenGLDebugMessages(0);
}

GLint AccelComponent::Ogl_GetInputTex(int input_i) const {
	const char* fn_name = "Ogl_GetInputTex";
	DLOG("AccelComponent(" << GetTypeString() << ")::GetInputTex");
	ASSERT(ctx);
	if (!ctx || input_i < 0 || input_i >= in.GetCount())
		return -1;
	
	const AcceleratorHeader& in = this->in.At(input_i);
	AccelComponentRef in_comp = ctx->GetComponentById(in.GetId());
	int tex = in_comp->Ogl_GetOutputTexture(in_comp == this);
	ASSERT(tex > 0);
	
	return tex;
}

int AccelComponent::Ogl_GetTexType(int input_i) const {
	const AcceleratorHeader& in = this->in.At(input_i);
	
	if (in.GetType() == AcceleratorHeader::TYPE_VOLUME)
		return GL_TEXTURE_3D;
	
	else if (in.GetType() == AcceleratorHeader::TYPE_CUBEMAP)
		return GL_TEXTURE_CUBE_MAP;
	
	else
		return GL_TEXTURE_2D;
}










bool AccelComponent::Ogl_CompilePrograms() {
	const char* fn_name = "Ogl_CompilePrograms";
	for(int i = 0; i < PROG_COUNT; i++) {
		if (i == PROG_FRAGMENT && !Ogl_CompileFragmentShader())
			return false;
	}
	
	return true;
}

bool AccelComponent::Ogl_CompileFragmentShader() {
	const char* fn_name = "Ogl_CompilePrograms";
	
	ASSERT(prog[PROG_FRAGMENT] < 0);
	String& fg_glsl = code[PROG_FRAGMENT];
	if (fg_glsl.GetCount() == 0) {
		if (RequiresShaderCode()) {
			Close();
			OnError(fn_name, "empty source code");
			return false;
		}
		else
			return true;
	}
	
	int max_tries = 1;
	if (IsIn<AudioContext>())
		max_tries = 2;
	
	for (int tries = 0; tries < max_tries; tries++) {
		DLOG("\tCompiling stage: tries " << tries << ": " << GetTypeString() << ": " << id << ": " << name);
		
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
				AcceleratorHeader& in = this->in.At(j);
				if (in.GetType() == AcceleratorHeader::TYPE_CUBEMAP)
					code << "uniform samplerCube iChannel" << IntStr(j) << ";\n";
				else if (in.GetType() == AcceleratorHeader::TYPE_VOLUME)
					code << "uniform sampler3D iChannel" << IntStr(j) << ";\n";
				else
					code << "uniform sampler2D iChannel" << IntStr(j) << ";\n";
			}
			else
				code << "uniform sampler2D iChannel" << IntStr(j) << ";\n";
		}
		code << "\n";
		
		for (String& src : ctx->GetParent()->common_source) {
			code += src + "\n";
		}
		
		code += fg_glsl;
		
		if (IsIn<VideoContext>() || IsIn<DisplayContext>()) {
			code +=		"\nvoid main (void) {\n"
						"	vec4 color = vec4 (0.0, 0.0, 0.0, 1.0);\n"
						"	mainImage (color, gl_FragCoord.xy);\n"
						"	gl_FragColor = color;\n"
						"}\n\n";
		}
		else if (IsIn<AudioContext>()) {
			if (tries == 0) {
				code +=		"\nvoid main (void) {\n"
							"	vec2 value = mainSound (int(gl_FragCoord.x), in_audio_seconds);\n"
							"	gl_FragColor = vec4(value, 0.0, 1.0);\n"
							"}\n\n";
			}
			else if (tries == 1) {
				code +=		"\nvoid main (void) {\n"
							"	float t = in_audio_seconds + gl_FragCoord.x / iSampleRate;\n"
							"	vec2 value = mainSound (t);\n"
							"	gl_FragColor = vec4(value, 0.0, 1.0);\n"
							"}\n\n";
			}
		}
		else {
			OnError(fn_name, "type of stage " + IntStr(id) + " is not supported");
			return false;
		}
		
		// Hotfixes
		code.Replace("precision float;", "");
		if (code.Find("vec4 char(") >= 0)
			code.Replace("char(", "_char(");
		
		//LOG(code);
		
		if (!Ogl_CompileProgram(PROG_FRAGMENT, code)) {
			if (tries < max_tries-1)
				continue;
			LOG(GetLineNumStr(code));
			Close();
			break;
		}
		
		return true;
	}
	
	return false;
}

bool AccelComponent::Ogl_CompileProgram(int prog_i, String shader_source) {
	GLint frag, program;
	
	OOSDL2::EnableOpenGLDebugMessages(1);
	
	frag = Ogl_CompileShader(prog_i, shader_source);
	if (frag < 0)
		return false;
		
	program = glCreateProgram();
	glProgramParameteri(program, GL_PROGRAM_SEPARABLE, GL_TRUE);
	
	glAttachShader(program, frag);
	glDeleteShader (frag);
	
	prog[prog_i] = program;
	
	is_searched_vars = false;
	
	OOSDL2::EnableOpenGLDebugMessages(0);
	
	return true;
}

GLint AccelComponent::Ogl_CompileShader(int prog_i, String shader_source) {
	const char* fn_name = "Ogl_CompileShader";
	
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

bool AccelComponent::Ogl_LinkStages() {
	const char* fn_name = "Ogl_LinkStages";
	for(int j = 0; j < AccelComponent::PROG_COUNT; j++) {
		if (prog[j] >= 0) {
			LOG("\tLinking stage " << GetTypeString() << ": " << name << ": program " << j);
			
			if (!Ogl_LinkProgram(j)) {
				Close();
				return false;
			}
		}
	}
	
	return true;
}

bool AccelComponent::Ogl_LinkProgram(int prog_i) {
	const char* fn_name = "Ogl_LinkProgram";
	GLint program = prog[prog_i];
	GLint status = GL_FALSE;
	GLint loglen, n_uniforms;
	
	if (program < 0) {
		if (RequiresShaderCode()) {
			OnError(fn_name, "internal error: opengl program was expected to be valid");
			return false;
		}
		else
			return true;
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

bool AccelComponent::Ogl_CheckInputTextures() {
	const char* fn_name = "Ogl_CheckInputTextures";
	bool fail = false;
	for(int i = 0; i < PROG_COUNT; i++) {
		auto& prog = this->prog[i];
		if (prog >= 0) {
			for(int j = 0; j < CHANNEL_COUNT; j++) {
				GLint uindex = glGetUniformLocation(prog, "iChannel" + IntStr(j));
				if (uindex >= 0) {
					if (in.GetCount() > j) {
						int tex = Ogl_GetInputTex(j);
						if (tex == 0) {
							OnError(fn_name,
								ToString() +
								": no texture for stage " + IntStr(id) +
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

GLint AccelComponent::Ogl_GetOutputTexture(bool reading_self) const {
	ASSERT(!reading_self || is_doublebuf);
	int buf_i = this->buf_i;
	if (reading_self)
		buf_i = (buf_i + 1) % 2;
	if (color_buf[buf_i] == 0) {DLOG(ToString() + " Ogl_GetOutputTexture failed");}
	ASSERT(color_buf[buf_i] > 0);
	return color_buf[buf_i];
}

void AccelComponent::Ogl_TexFlags(int type, int filter, int repeat) {
	if (filter == AcceleratorHeader::FILTER_NEAREST) {
		glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	}
	else if (filter == AcceleratorHeader::FILTER_LINEAR) {
		glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}
	else if (filter == AcceleratorHeader::FILTER_MIPMAP) {
		glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glGenerateMipmap(type);
	}
	
	if (repeat == AcceleratorHeader::WRAP_REPEAT) {
		glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);
		if (type == GL_TEXTURE_3D)
			glTexParameteri(type, GL_TEXTURE_WRAP_R, GL_REPEAT);
	}
	else if (repeat == AcceleratorHeader::WRAP_CLAMP) {
		glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_CLAMP);
		if (type == GL_TEXTURE_3D)
			glTexParameteri(type, GL_TEXTURE_WRAP_R, GL_CLAMP);
	}
}


NAMESPACE_TOPSIDE_END

#endif
