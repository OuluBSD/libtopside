#include "Graphics.h"

#ifdef flagSCREEN

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




Callback2<String, OglBuffer*> OglBuffer::WhenLinkInit;



void OglBuffer::AddBinder(BinderIfaceOgl* iface) {
	
	TODO
	
}

void OglBuffer::RemoveBinder(BinderIfaceOgl* iface) {
	
	TODO
	
}

void OglBuffer::Update(double dt) {
	if (var_idx[VAR_COMPAT_DATE] >= 0) {
		time_us += dt;
		if (time_us >= 1.0) {
			time_us = fmod(time_us, 1.0);
			time = GetSysTime();
			RTLOG("OglBuffer::Update: " << dt << ", time=" << time.ToString());
		}
	}
}

bool OglBuffer::SetLoopback(String loopback_str) {
	if (loopback_str.IsEmpty()) {
		loopback = -1;
		return false;
	}
	
	if (!IsAllDigit(loopback_str)) {
		LOG("OglBuffer::SetLoopback: error: expected digit string, got '" << loopback_str << "'");
		return false;
	}
	
	loopback = StrInt(loopback_str);
	if (loopback < -1 || loopback >= 4) {
		LOG("OglBuffer::SetLoopback: error: invalid loopback #" << loopback << ", expected between -1 and +3");
		return false;
	}
	
	is_doublebuf = loopback >= 0;
	
	return true;
}

bool OglBuffer::LoadFragmentShaderFile(String shader_path, String library_paths) {
	DLOG("OglBuffer::LoadFragmentShaderFile: " << shader_path);
	
	common_source_frag.Clear();
	Vector<String> libraries = Split(library_paths, ";");
	for (String& lib : libraries) {
		String path = RealizeShareFile(lib);
		if (FileExists(path))
			common_source_frag << LoadFile(path);
	}
	
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
	
	//DUMP(content);
	SetFragmentShaderSource(content);
	
	return true;
}

bool OglBuffer::LoadVertexShaderFile(String shader_path, String library_paths) {
	DLOG("OglBuffer::LoadVertexShaderFile: " << shader_path);
	
	common_source_vtx.Clear();
	Vector<String> libraries = Split(library_paths, ";");
	for (String& lib : libraries) {
		String path = RealizeShareFile(lib);
		if (FileExists(path))
			common_source_vtx << LoadFile(path);
	}
	
	if (!FileExists(shader_path))
		shader_path = ShareDirFile(shader_path);
	
	if (!FileExists(shader_path)) {
		LOG("OglBuffer::LoadVertexShaderFile: error: file does not exist: " << shader_path);
		return false;
	}
	
	String content = LoadFile(shader_path);
	if (content.IsEmpty()) {
		LOG("OglBuffer::LoadVertexShaderFile: error: got empty shader file from: " << shader_path);
		return false;
	}
	
	//DUMP(content);
	SetVertexShaderSource(content);
	
	return true;
}

bool OglBuffer::InitializeTextureRGBA(Size sz, int channels, const byte* data, int len) {
	RTLOG("OglBuffer::InitializeTextureRGBA: " << sz.ToString() << ", " << HexStr((void*)data) << ", " << len);
	
	UpdateTexBuffers();
	
	ReadTexture(sz, channels, data, len);
	
	return true;
}

bool OglBuffer::InitializeCubemapRGBA(Size sz, int channels, const Vector<byte>& d0, const Vector<byte>& d1, const Vector<byte>& d2, const Vector<byte>& d3, const Vector<byte>& d4, const Vector<byte>& d5) {
	RTLOG("OglBuffer::InitializeCubemapRGBA: " << sz.ToString());
	
	is_cubemap = true;
	
	UpdateTexBuffers();
	
	ReadCubemap(sz, channels, d0, d1, d2, d3, d4, d5);
	
	return true;
}

bool OglBuffer::InitializeVolume(Size3 sz, int channels, const Vector<byte>& data) {
	RTLOG("OglBuffer::InitializeVolume: " << sz.ToString() << ", " << data.GetCount());
	
	UpdateTexBuffers();
	
	ReadTexture(sz, channels, data);
	
	return true;
}

void OglBuffer::ReadTexture(Size sz, int channels, const byte* data, int len) {
	GLenum type		= GL_TEXTURE_2D;
	
	GLuint& color_buf = this->color_buf[0];
	ASSERT(color_buf > 0);
	ASSERT(sz == fb_size);
	ASSERT(fb_size_bytes == len);
	int intl_fmt = GetOglChCode(channels);
	
	glBindTexture (type, color_buf);
	glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	
	glTexImage2D(type, 0, GL_RGBA32F,
		sz.cx,
		sz.cy,
		0, intl_fmt, GL_UNSIGNED_BYTE,
		data);
	
	TexFlags(type, fb_filter, fb_wrap);
}

void OglBuffer::ReadTexture(Size3 sz, int channels, const Vector<byte>& data) {
	GLenum type		= GL_TEXTURE_3D;
	
	ASSERT(fb_size.cx == sz.cx && fb_size.cy == sz.cy);
	GLuint& color_buf = this->color_buf[0];
	ASSERT(color_buf > 0);
	//int intl_fmt = GetOglChCode(channels);
	
	glBindTexture (type, color_buf);
	glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage3D(type, 0, GL_RGBA32F,
		sz.cx,
		sz.cy,
		sz.cz,
		//0, intl_fmt, GL_UNSIGNED_BYTE,
		0, fb_fmt, fb_type,
		data.Begin());
	
	TexFlags(type, fb_filter, fb_wrap);
}

void OglBuffer::ReadCubemap(Size sz, int channels, const Vector<byte>& d0, const Vector<byte>& d1, const Vector<byte>& d2, const Vector<byte>& d3, const Vector<byte>& d4, const Vector<byte>& d5) {
	GLenum type		= GL_TEXTURE_CUBE_MAP;
	GLuint& tex		= color_buf[0];
	int ch_code		= GetOglChCode(channels);
	
	glBindTexture (type, tex);
	
	ASSERT(tex > 0);
	
	for(int i = 0; i < 6; i++) {
		GLenum tex_type	= GL_TEXTURE_CUBE_MAP_POSITIVE_X + i;
		const Vector<byte>* data = 0;
		switch (i) {
			case 0: data = &d0; break;
			case 1: data = &d1; break;
			case 2: data = &d2; break;
			case 3: data = &d3; break;
			case 4: data = &d4; break;
			case 5: data = &d5; break;
		}
		glTexImage2D(tex_type, 0, GL_RGBA,
					 sz.cx, sz.cy,
					 0, ch_code,
					 GL_UNSIGNED_BYTE,
					 data->Begin());
	}
	
	TexFlags(type, fb_filter, fb_wrap);
	
	GLenum err = glGetError();
	if (err != GL_NO_ERROR)
		OnError("OglBuffer::ReadCubemap", "gl error " + HexStr(err));
	
	glBindTexture(type, 0);
}

bool OglBuffer::Initialize() {
	DLOG("OglBuffer::Initialize: load new program");
	
	ASSERT(fps > 0);
	frame_time = 1.0 / fps;
	time = GetSysTime();
	block_offset = 0;
	
	if (!SetupLoopback())
		return false;
	
	if (!CompilePrograms())
		return false;
	
	if (!LinkStages())
		return false;
	
	RefreshPipeline();
	
	for (String& s : link_ids)
		WhenLinkInit(s, this);
	
	initialized = true;
	
	return true;
}

void OglBuffer::RefreshPipeline() {
	DLOG("OglBuffer::RefreshPipeline begin");
	
	CreatePipeline();
	
	UpdateTexBuffers();
	
	//if (!CheckInputTextures())
	//	return;
	
	Reset();
	
	DLOG("OglBuffer::RefreshPipeline end");
}

void OglBuffer::Reset() {
	time_total = 0;
}

const OglBuffer* OglBuffer::GetComponentById(int id) const {
	ASSERT(id >= 0);
	for (const OglBufferInput& s : in_buf)
		if (s.id == id)
			return s.GetBuffer();
	return 0;
}

void OglBuffer::SetFramebufferSize(Size sz) {
	ASSERT(sz.cx > 0 && sz.cy > 0);
	fb_size = sz;
	UpdateTexBuffers();
}

void OglBuffer::UpdateTexBuffers() {
	if (!is_win_fbo) {
		ASSERT(fb_channels > 0);
		ASSERT(fb_accel_channels > 0);
		ASSERT(fb_size.cx > 0 && fb_size.cy > 0);
		
		fb_sample_size			= fb_sampletype == SAMPLE_BYTE ? 1 : 4;
		fb_type					= fb_sampletype == SAMPLE_BYTE ? GL_UNSIGNED_BYTE : GL_FLOAT;
		fb_accel_sample_size	= fb_accel_sampletype == SAMPLE_BYTE ? 1 : 4;
		fb_accel_type			= fb_accel_sampletype == SAMPLE_BYTE ? GL_UNSIGNED_BYTE : GL_FLOAT;
		
		fb_size_bytes			= fb_size.cx * fb_size.cy * fb_sample_size * fb_channels;
		fb_accel_size_bytes		= fb_size.cx * fb_size.cy * fb_accel_sample_size* fb_accel_channels;
		fb_fmt					= GetOglChCode(fb_channels, fb_type == GL_FLOAT);
		fb_accel_fmt			= GetOglChCode(fb_accel_channels, fb_accel_type == GL_FLOAT);
		
		ASSERT(fb_size_bytes > 0);
		ASSERT(fb_accel_size_bytes > 0);
		ASSERT(fb_fmt >= 0);
		ASSERT(fb_accel_fmt >= 0);
		ASSERT(fb_type >= 0);
		ClearTex();
		
		CreateTex(
			true, true,
			fb_filter,
			fb_wrap);
		
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
	
	if (env) {
		Size& video_size = env->Set<Size>(SCREEN0_SIZE);
		if (video_size.cx == 0 && video_size.cy == 0)
			video_size = fb_size;
		else if (video_size != fb_size) {
			fb_size = video_size;
			UpdateTexBuffers();
		}
	}
	
	
	GLint prog = fg_prog;
	
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
	
	if (is_shader_audio_main) {
		block_offset += fb_size.cx;
	}
	else {
		block_offset += 1.0;
	}
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
		glUniform1f(uindex, (GLfloat)time_total);
	}
	
	else if (var == VAR_COMPAT_RESOLUTION) {
		ASSERT(fb_size.cx > 0 && fb_size.cy > 0);
		glUniform3f(uindex, (GLfloat)fb_size.cx, (GLfloat)fb_size.cy, 1.0f);
	}
	
	else if (var == VAR_COMPAT_TIME) {
		//RTLOG("OglBuffer::SetVar: " << time_total);
		glUniform1f(uindex, (GLfloat)time_total);
	}
	
	else if (var == VAR_COMPAT_TIMEDELTA) {
		ASSERT(frame_time != 0.0);
		glUniform1f(uindex, (GLfloat)frame_time);
	}
	
	else if (var == VAR_COMPAT_FRAME) {
		ASSERT(frames >= 0);
		glUniform1i(uindex, frames);
	}
	
	else if (var == VAR_COMPAT_MOUSE) {
		if (env) {
			Point& mouse_drag = env->Set<Point>(MOUSE_TOYCOMPAT_DRAG);
			Point& mouse_click = env->Set<Point>(MOUSE_TOYCOMPAT_CLICK);
			glUniform4f(uindex,
				(GLfloat)mouse_click.x,
				(GLfloat)mouse_click.y,
				(GLfloat)mouse_drag.x,
				(GLfloat)mouse_drag.y);
		}
	}
	
	else if (var == VAR_COMPAT_DATE) {
		double sec = ((int)time.hour * 60 + (int)time.minute) * 60 + (int)time.second;
		sec += time_us;
		glUniform4f(uindex, (GLfloat)time.year, (GLfloat)time.month, (GLfloat)time.day, (GLfloat)sec);
	}
	
	else if (var == VAR_COMPAT_SAMPLERATE) {
		glUniform1f(uindex, (GLfloat)sample_rate);
	}
	
	else if (var == VAR_COMPAT_OFFSET) {
		if (fb_size.cx > 0 && fb_size.cy > 0) {
			int x = fb_offset.x;
			int y = fb_size.cy - fb_size.cy - fb_offset.y; // -y_offset
			glUniform2f(uindex, (GLfloat)x, (GLfloat)y);
		} else {
			glUniform2f(uindex, 0.0f, 0.0f);
		}
	}
	
	else if (var >= VAR_COMPAT_CHANNEL0 && var <= VAR_COMPAT_CHANNEL3) {
		int ch = var - VAR_COMPAT_CHANNEL0;
		if (in_buf.GetCount() >= ch+1) {
			int tex = GetInputTex(ch);
			ASSERT(tex != 0);
			glActiveTexture(GL_TEXTURE0 + ch);
			glBindTexture(GetTexType(ch), tex);
			glUniform1i(uindex, ch);
		}
	}
	
	else if (var == VAR_COMPAT_FRAMERATE) {
		ASSERT(fps > 0);
		glUniform1f(uindex, (GLfloat)fps);
	}
	
	else if (var == VAR_COMPAT_CHANNELTIME) {
		double values[4];
		for(int j = 0; j < 4; j++) {
			if (j < in_buf.GetCount()) {
				OglBufferInput& in = in_buf[j];
				const OglBuffer* in_buf = in.GetBuffer();
				values[j] = in_buf ? in_buf->time_total : 0;
			}
			else
				values[j] = time_total;
		}
		glUniform4f(uindex, (GLfloat)values[0], (GLfloat)values[1], (GLfloat)values[2], (GLfloat)values[3]);
	}
	
	else if (var >= VAR_COMPAT_CHANNELRESOLUTION0 && var <= VAR_COMPAT_CHANNELRESOLUTION3) {
		int ch = var - VAR_COMPAT_CHANNELRESOLUTION0;
		GLfloat values[3] = {0,0,0};
		if (ch < in_buf.GetCount()) {
			OglBufferInput& in = in_buf[ch];
			const OglBuffer* in_buf = in.GetBuffer();
			if (in_buf) {
				values[0] = (GLfloat)in_buf->fb_size.cx;
				values[1] = (GLfloat)in_buf->fb_size.cy;
				values[2] = (GLfloat)in_buf->fb_depth;
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
	
	else if (var == VAR_COMPAT_BLOCKOFFSET) {
		glUniform1f(uindex, (GLfloat)block_offset);
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
	
	EnableGfxAccelDebugMessages(1);
	
	for(int bi = 0; bi < buf_count; bi++) {
		GLuint& color_buf = this->color_buf[bi];
		GLuint& depth_buf = this->depth_buf[bi];
		GLuint& frame_buf = this->frame_buf[bi];
		ASSERT(color_buf == 0);
		
		ASSERT(fb_accel_fmt == GetOglChCode(fb_accel_channels, true));
		ASSERT(fb_fmt == GetOglChCode(fb_channels, fb_type == GL_FLOAT));
		ASSERT(fb_type == GL_UNSIGNED_BYTE || fb_type == GL_FLOAT);
		
		// color buffer
		glGenTextures(1, &color_buf);
		glBindTexture(GL_TEXTURE_2D, color_buf);
		//glTexImage2D(GL_TEXTURE_2D, 0, fb_accel_fmt, sz.cx, sz.cy, 0, fb_fmt, fb_type, 0);
		glTexImage2D(GL_TEXTURE_2D, 0, fb_accel_fmt, sz.cx, sz.cy, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
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
	if (input_i < 0 || input_i >= in_buf.GetCount())
		return -1;
	
	const OglBufferInput& in = in_buf[input_i];
	if (in.in_buf == 0) {
		RTLOG("OglBuffer::GetInputTex: warning: no input fbo buffer");
		return -1;
	}
	
	const OglBuffer* in_comp = in.in_buf;
	if (!in_comp)
		return -1;
	
	int tex = in_comp->GetOutputTexture(in_comp == this);
	ASSERT(tex > 0);
	
	return tex;
}

int OglBuffer::GetTexType(int input_i) const {
	const OglBufferInput& in = in_buf[input_i];
	
	if (in.type == OglBufferInput::VOLUME)
		return GL_TEXTURE_3D;
	
	else if (in.type == OglBufferInput::CUBEMAP)
		return GL_TEXTURE_CUBE_MAP;
	
	else
		return GL_TEXTURE_2D;
}










bool OglBuffer::SetupLoopback() {
	if (loopback < 0)
		return true;
	
	if (loopback >= 4) {
		LOG("OglBuffer::SetupLoopback: error: too large loopback id #" << loopback);
		return false;
	}
	
	if (loopback >= in_buf.GetCount())
		in_buf.SetCount(loopback+1);
	
	OglBufferInput& in = in_buf[loopback];
	in.in_buf = this;
	in.type = OglBufferInput::BUFFER;
	in.wrap = OglBufferInput::WRAP_REPEAT;
	in.filter = OglBufferInput::FILTER_LINEAR;
	in.vflip = false;
	
	return true;
}

bool OglBuffer::CompilePrograms() {
	const char* fn_name = "CompilePrograms";
	for(int i = 0; i < PROG_COUNT; i++) {
		if (i == PROG_FRAGMENT && !CompileFragmentShader())
			return false;
		if (i == PROG_VERTEX && !CompileVertexShader())
			return false;
	}
	
	return true;
}

bool OglBuffer::CompileFragmentShader() {
	const char* fn_name = "CompileFragmentShader";
	
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
				"uniform vec2      iOffset;\n"
				"uniform vec4      iMouse;                // mouse pixel coords. xy: current (if MLB down), zw: click\n"
				"uniform vec4      iDate;                 // (year, month, day, time in secs)\n"
				"uniform float     iFrameRate;\n"
				"uniform float     iSampleRate;           // sound sample rate (i.e., 44100)\n"
				"uniform float     iChannelTime[4];       // channel playback time (in seconds)\n"
				"uniform vec3      iChannelResolution[4]; // channel resolution (in pixels)\n"
				"uniform float     iBlockOffset;          // total consumed samples (mostly for audio, for video it's same as iFrame)\n"
				;
	
	for(int j = 0; j < 4; j++) {
		if (j < in_buf.GetCount()) {
			OglBufferInput& in = in_buf[j];
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
	
	for(int j = 0; j < common_source_frag.GetCount(); j++) {
		code += common_source_frag[j] + "\n";
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

bool OglBuffer::CompileVertexShader() {
	const char* fn_name = "CompileVertexShader";
	
	ASSERT(prog[PROG_VERTEX] < 0);
	String& fg_glsl = code[PROG_VERTEX];
	if (fg_glsl.GetCount() == 0) {
		OnError(fn_name, "empty source code");
		return false;
	}
	
	DLOG("\tCompiling stage: " << id << ": " << name);
	
	String code;
	
	code =		"#version 430\n"
				"#define GL_ES\n"
				
				"layout (location = 0) in vec3 pos;\n"
				"layout (location = 1) in vec3 normal;\n"
				"layout (location = 2) in vec2 tex_coords;\n"

				"in int gl_VertexID;\n"
				"in int gl_InstanceID;\n"
				
				"out vec2 TexCoords;\n"
				"out gl_PerVertex\n"
				"{\n"
				"  vec4 gl_Position;\n"
				"  float gl_PointSize;\n"
				"  float gl_ClipDistance[];\n"
				"};\n"
				
				"uniform vec2      in_mouse;\n"
				"uniform float     in_audio_seconds;\n"
				
				"uniform vec3      iResolution;           // viewport resolution (in pixels)\n"
				"uniform float     iTime;                 // shader playback time (in seconds)\n"
				"uniform float     iTimeDelta;            // duration since the previous frame (in seconds)\n"
				"uniform int       iFrame;                // frames since the shader (re)started\n"
				"uniform vec2      iOffset;\n"
				"uniform vec4      iMouse;                // mouse pixel coords. xy: current (if MLB down), zw: click\n"
				"uniform vec4      iDate;                 // (year, month, day, time in secs)\n"
				"uniform float     iFrameRate;\n"
				"uniform float     iSampleRate;           // sound sample rate (i.e., 44100)\n"
				"uniform float     iChannelTime[4];       // channel playback time (in seconds)\n"
				"uniform vec3      iChannelResolution[4]; // channel resolution (in pixels)\n"
				"uniform float     iBlockOffset;          // total consumed samples (mostly for audio, for video it's same as iFrame)\n"
				;
	
	for(int j = 0; j < 4; j++) {
		if (j < in_buf.GetCount()) {
			OglBufferInput& in = in_buf[j];
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
	
	for(int j = 0; j < common_source_frag.GetCount(); j++) {
		code += common_source_frag[j] + "\n";
	}
	
	code += fg_glsl;
	
	code +=		"\nvoid main (void) {\n"
				"	mainVertex();\n"
				"}\n\n";
	
	//LOG(code);
	
	if (!CompileProgram(PROG_VERTEX, code)) {
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
	else if (prog_i == PROG_VERTEX) {
		shader_type = GL_VERTEX_SHADER;
	}
	else {
		OnError(fn_name, "TODO: other programs than fragment shader");
		return -1;
	}
	
	GLuint shader = glCreateShader(shader_type);
	GLint status = GL_FALSE;
	GLint loglen;
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
					if (in_buf.GetCount() > j) {
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
	last_error.Clear();
	last_error << fn << ": " << s;
}

void OglBuffer::StoreOutputLink(InternalPacketData& v) {
	static_assert(sizeof(v.u32) == sizeof(GLuint), "Unexpected GLuint size");
	
	v.ptr = this;
}

bool OglBuffer::LoadOutputLink(Size3 sz, int in_id, InternalPacketData& v) {
	
	if (in_id >= 0) {
		//LOG("OglBuffer::LoadOutputLink: " << name << " #" << in_id);
		
		if (in_id >= in_buf.GetCount())
			in_buf.SetCount(in_id+1);
		
		ASSERT(v.ptr);
		OglBufferInput& in = in_buf[in_id];
		in.id = in_id;
		in.in_buf = (OglBuffer*)v.ptr;
		
		ASSERT(sz.cx > 0 && sz.cy > 0);
		
		if (in.in_buf->IsCubemap())
			in.type = OglBufferInput::CUBEMAP;
		else if (sz.cz > 0)
			in.type = OglBufferInput::VOLUME;
		else
			in.type = OglBufferInput::TEXTURE;
		
		return true;
	}
	
	RTLOG("OglBuffer::LoadOutputLink: error: unexpected data");
	return false;
}

void OglBuffer::SetInputVolume(int in_id) {
	if (in_id >= in_buf.GetCount())
		in_buf.SetCount(in_id+1);
	
	OglBufferInput& in = in_buf[in_id];
	in.type = OglBufferInput::VOLUME;
}

void OglBuffer::SetInputCubemap(int in_id) {
	if (in_id >= in_buf.GetCount())
		in_buf.SetCount(in_id+1);
	
	OglBufferInput& in = in_buf[in_id];
	in.type = OglBufferInput::CUBEMAP;
}


NAMESPACE_TOPSIDE_END

#endif
