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


bool OglBuffer::LoadShaderFile(ShaderVar::Type shader_type, String shader_path, String library_path) {
	DLOG("OglBuffer::LoadShaderFile: " << shader_path);
	
	ASSERT(shader_type > ShaderVar::PROG_NULL && shader_type < ShaderVar::PROG_COUNT);
	OglShaderState& shader = state.shaders[shader_type];
	
	Vector<String> libraries = Split(library_path, ";");
	String library;
	bool succ = true;
	for (String& lib : libraries) {
		String path = RealizeShareFile(lib);
		if (FileExists(path)) {
			if (libraries.GetCount() > 1)
				library << "// FILE: " << path << "\n\n";
			library << LoadFile(path) << "\n\n";
		}
		else {
			LOG("OglBuffer::LoadShaderFile: error: file does not exist: " << path);
			succ = false;
		}
	}
	if (!succ) return false;
	
	if (!FileExists(shader_path))
		shader_path = ShareDirFile(shader_path);
	
	if (!FileExists(shader_path)) {
		LOG("OglBuffer::LoadShaderFile: error: file does not exist: " << shader_path);
		return false;
	}
	
	String content = LoadFile(shader_path);
	if (content.IsEmpty()) {
		LOG("OglBuffer::LoadShaderFile: error: got empty shader file from: " << shader_path);
		return false;
	}
	
	//DUMP(content);
	shader.code = content;
	shader.library = library;
	
	return true;
}





void OglBuffer::AddBinder(BinderIfaceOgl* iface) {
	VectorFindAdd(binders, iface);
}

void OglBuffer::RemoveBinder(BinderIfaceOgl* iface) {
	VectorRemoveKey(binders, iface);
}

void OglBuffer::Update(double dt) {
	if (state.is_time_used) {
		state.time_us += dt;
		if (state.time_us >= 1.0) {
			state.time_us = fmod(state.time_us, 1.0);
			state.time = GetSysTime();
			RTLOG("OglBuffer::Update: " << dt << ", time=" << state.time.ToString());
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
	
	state.is_doublebuf = loopback >= 0;
	
	return true;
}

#if 0
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

#endif

bool OglBuffer::InitializeTexture(Size sz, int channels, Sample sample, const byte* data, int len) {
	RTLOG("OglBuffer::InitializeTexture: " << sz.ToString() << ", " << HexStr((void*)data) << ", " << len);
	#if 0
	UpdateTexBuffers();
	
	ReadTexture(sz, channels, data, len);
	#endif
	return true;
}

bool OglBuffer::InitializeCubemap(Size sz, int channels, Sample sample, const Vector<byte>& d0, const Vector<byte>& d1, const Vector<byte>& d2, const Vector<byte>& d3, const Vector<byte>& d4, const Vector<byte>& d5) {
	RTLOG("OglBuffer::InitializeCubemap: " << sz.ToString());
	#if 0
	is_cubemap = true;
	
	UpdateTexBuffers();
	
	ReadCubemap(sz, channels, d0, d1, d2, d3, d4, d5);
	#endif
	return true;
}

bool OglBuffer::InitializeVolume(Size3 sz, int channels, Sample sample, const Vector<byte>& data) {
	RTLOG("OglBuffer::InitializeVolume: " << sz.ToString() << ", " << data.GetCount());
	#if 0
	UpdateTexBuffers();
	
	ReadTexture(sz, channels, data);
	#endif
	return true;
}

void OglBuffer::ReadTexture(Size sz, int channels, Sample sample, const byte* data, int len) {
	#if 0
	GLenum type		= GL_TEXTURE_2D;
	
	GLuint& color_buf = this->color_buf[0];
	ASSERT(color_buf > 0);
	ASSERT(sz == fb_size);
	ASSERT(s.GetSize() == len);
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
	#endif
}

void OglBuffer::ReadTexture(Size3 sz, int channels, Sample sample, const Vector<byte>& data) {
	#if 0
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
	#endif
}

#if 0

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

#endif

bool OglBuffer::Initialize() {
	DLOG("OglBuffer::Initialize: load new program");
	
	ASSERT(state.fps > 0);
	state.frame_time = 1.0 / state.fps;
	state.time = GetSysTime();
	state.block_offset = 0;
	
	if (!SetupLoopback())
		return false;
	
	if (!CompilePrograms())
		return false;
	
	RefreshPipeline();
	FindVariables();
	
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
	state.time_total = 0;
}

#if 0
const OglBuffer* OglBuffer::GetComponentById(int id) const {
	ASSERT(id >= 0);
	for (const OglBufferInput& s : in_buf)
		if (s.id == id)
			return s.GetBuffer();
	return 0;
}
#endif
void OglBuffer::SetFramebufferSize(Size sz) {
	TODO
	#if 0
	ASSERT(sz.cx > 0 && sz.cy > 0);
	fb_size = sz;
	UpdateTexBuffers();
	#endif
}

void OglBuffer::UpdateTexBuffers() {
	auto& s = state;
	if (!s.is_win_fbo) {
		ASSERT(s.channels > 0);
		ASSERT(s.size.cx > 0 && s.size.cy > 0);
		
		/*s.gl_sample_size		= s.sample == SAMPLE_BYTE ? 1 : 4;
		s.gl_type				= s.sample == SAMPLE_BYTE ? GL_UNSIGNED_BYTE : GL_FLOAT;
		fb_accel_type			= fb_accel_sampletype == SAMPLE_BYTE ? GL_UNSIGNED_BYTE : GL_FLOAT;
		
		fb_size_bytes			= fb_size.cx * fb_size.cy * fb_sample_size * fb_channels;
		fb_accel_size_bytes		= fb_size.cx * fb_size.cy * fb_accel_sample_size* fb_accel_channels;
		fb_fmt					= GetOglChCode(fb_channels, fb_type == GL_FLOAT);
		fb_accel_fmt			= GetOglChCode(fb_accel_channels, fb_accel_type == GL_FLOAT);
		*/
		ASSERT(s.GetGlSize() > 0);
		ASSERT(s.GetGlFormat() >= 0);
		ASSERT(s.GetGlType() >= 0);
		ClearTex();
		
		CreateTex(
			true, true);
		
	}
}

int OglBuffer::NewWriteBuffer() {
	auto& s = state;
	if (s.is_doublebuf)
		s.buf_i = (s.buf_i + 1) % 2;
	return s.buf_i;
}

void OglBuffer::Process(const RealtimeSourceConfig& cfg) {
	auto& s = state;
	GLint prog = s.prog;
	GLint pipeline = s.pipeline;
	
	ASSERT(prog >= 0);
	if (prog < 0)
		return;
	
	RTLOG("OglBuffer::Process " << HexStr(this) << " time: " << s.time_total);
	
	s.time_total = cfg.time_total;
	//RTLOG("OglBuffer::Process: " << time_total);
	s.frames++;
	
	if (env) {
		Size& video_size = env->Set<Size>(SCREEN0_SIZE);
		if (video_size.cx == 0 && video_size.cy == 0)
			video_size = s.size;
		else if (video_size != s.size) {
			s.size = video_size;
			UpdateTexBuffers();
		}
	}
	
	glBindProgramPipeline(pipeline);
	glUseProgram(prog);
	
	if (!s.is_searched_vars)
		FindVariables();
	
	int bi = NewWriteBuffer();
	
	if (!s.is_win_fbo) {
		ASSERT(s.frame_buf[bi] > 0);
		const GLenum bufs[] = {GL_COLOR_ATTACHMENT0_EXT};
		
		// combine FBO
	    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, s.frame_buf[bi]);
	    
	    // set up render target
	    glDrawBuffers(sizeof bufs / sizeof bufs[0], bufs);
	}
	
	
	SetVars(prog, cfg);
	
	RendVer(OnProcess);
	
	
	glClear(GL_COLOR_BUFFER_BIT);
	
	if (binders.GetCount()) {
		OglShader shader(state);
		for (BinderIfaceOgl* iface : binders)
			iface->Render(*this, shader);
	}
	else {
		glRectf(-1.0, -1.0, 1.0, 1.0);
	}
	
	// render VBA from state
	for (OglFramebufferObject& o : state.objects) {
		SetVars(state.prog, o);
		o.Paint();
	}
	
	
	EnableGfxAccelDebugMessages(1);
	
	ASSERT(s.is_win_fbo == (s.frame_buf[bi] == 0));
	if (s.frame_buf[bi] > 0) {
		// backup render target
	    //glDrawBuffer(GL_FRONT);
	    
	    // Some components (e.g. audio) needs to read the framebuffer
	    if (s.is_read_fb_output)
			UseRenderedFramebuffer();
		
	    // reset FBO
	    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
	}
	
	EnableGfxAccelDebugMessages(0);
	
	glBindProgramPipeline(0);
	
	if (s.is_audio) {
		s.block_offset += s.size.cx;
	}
	else {
		s.block_offset += 1.0;
	}
}

void OglBuffer::UseRenderedFramebuffer() {
	auto& s = state;
	auto fmt = s.GetGlFormat();
	auto type = s.GetGlType();
	ASSERT(s.GetGlSize() > 0);
	ASSERT(s.size.cx > 0 && s.size.cy > 0);
	ASSERT(fmt >= 0);
	ASSERT(s.GetGlType() >= 0);
	
	fb_out.SetCount(s.GetGlSize());
	
	ASSERT(s.color_buf[s.buf_i] > 0);
	glReadBuffer(GL_COLOR_ATTACHMENT0_EXT);
	
	TODO // glReadPixels will crash mysteriously
	glReadPixels(0, 0, s.size.cx, s.size.cy, fmt, type, fb_out.Begin());
}

void OglBuffer::ClearPipeline() {
	if (state.pipeline) {
		glDeleteProgramPipelines(1, &state.pipeline);
		state.pipeline = 0;
	}
}

void OglBuffer::CreatePipeline() {
	ClearPipeline();
	
	glGenProgramPipelines(1, &state.pipeline);
	
	
	// only 1 program in pipeline currently
	{
		auto& prog = state.prog;
		if (prog >= 0) {
			int bmask = 0;
			for(int i = 0; i < ShaderVar::PROG_COUNT; i++) {
				if (state.shaders[(ShaderVar::Type)i].enabled) {
					// Note: ShaderVar::Type is relative to GL_*_SHADER_BIT
					int bit = 1 << i;
					ASSERT(i != ShaderVar::PROG_VERTEX   || bit == GL_VERTEX_SHADER_BIT);
					ASSERT(i != ShaderVar::PROG_FRAGMENT || bit == GL_FRAGMENT_SHADER_BIT);
					bmask |= bit;
				}
			}
			ASSERT(bmask != 0);
			glUseProgramStages(state.pipeline, bmask, prog);
		}
	}
}







void OglBuffer::FindVariables() {
	GLint n_uniforms;
	glGetProgramiv(state.prog, GL_ACTIVE_UNIFORMS, &n_uniforms);
	GLchar name[80];
	GLsizei namelen;
	memset(state.var_idx, -1, sizeof(state.var_idx));
	state.user_vars.Clear();
	for (int i = 0; i < n_uniforms; i++) {
		GLint size;
		GLenum type;
		
		glGetActiveUniform(state.prog, i, 79, &namelen, &size, &type, name);
		name[namelen] = '\0';
		String name_str(name);
		
		bool found = false;
		bool state_var = false;
		for(int j = 0; j < ShaderVar::VAR_COUNT; j++) {
			const char* var_name = ShaderVar::names[j];
			if (strncmp(var_name, name, 128) == 0) {
				state.var_idx[j] = i;
				if (j == ShaderVar::VAR_COMPAT_DATE && !state.is_time_used)
					state.is_time_used = true;
				found = true;
				state_var = !ShaderVar::is_obj_var[j];
				break;
			}
		}
		
		if (!found) {
			state.user_vars << name_str;
		}
		
		RendVer2(OnRealizeVar, name_str, state_var);
	}
	
	state.is_searched_vars = true;
}

void OglBuffer::SetVars(GLint prog, const OglFramebufferObject& o) {
	for(int i = 0; i < ShaderVar::VAR_COUNT; i++)
		if (ShaderVar::is_obj_var[i] && state.var_idx[i] >= 0)
			SetVar(i, prog, o);
}

void OglBuffer::SetVar(int var, GLint prog, const OglFramebufferObject& o) {
	using namespace ShaderVar;
	int uindex = state.var_idx[var];
	ASSERT(uindex >= 0);
	if (var == VAR_VIEW) {
		if (o.is_global_view)
			TODO
		else
			glUniformMatrix4fv(uindex, 1, GL_FALSE, &o.view[0][0]);
	}
	else if (var == VAR_PROJECTION) {
		if (o.is_global_proj)
			TODO
		else
			glUniformMatrix4fv(uindex, 1, GL_FALSE, &o.proj[0][0]);
	}
	else if (var == VAR_SCALE) {
		glUniformMatrix4fv(uindex, 1, GL_FALSE, &o.scale[0][0]);
	}
	else if (var == VAR_MODEL) {
		glUniformMatrix4fv(uindex, 1, GL_FALSE, &o.model[0][0]);
	}
}

void OglBuffer::SetVars(GLint prog, const RealtimeSourceConfig& cfg) {
	for(int i = 0; i < ShaderVar::VAR_COUNT; i++)
		if (!ShaderVar::is_obj_var[i] && state.var_idx[i] >= 0)
			SetVar(i, prog, cfg);
}

void OglBuffer::SetVar(int var, GLint prog, const RealtimeSourceConfig& cfg) {
	using namespace ShaderVar;
	auto& s = state;
	int uindex = state.var_idx[var];
	ASSERT(uindex >= 0);
	if (uindex < 0)
		return;
	
	RendVer1(OnUpdateVar, ShaderVar::names[var]);
	
	if (var == VAR_AUDIOTIME) {
		glUniform1f(uindex, (GLfloat)s.time_total);
	}
	
	else if (var == VAR_VIEW) {
		ASSERT(0); // pass
	}
	else if (var == VAR_PROJECTION) {
		ASSERT(0); // pass
	}
	else if (var == VAR_SCALE) {
		ASSERT(0); // pass
	}
	else if (var == VAR_MODEL) {
		ASSERT(0); // pass
	}
	else if (var == VAR_COMPAT_RESOLUTION) {
		ASSERT(s.size.cx > 0 && s.size.cy > 0);
		glUniform3f(uindex, (GLfloat)s.size.cx, (GLfloat)s.size.cy, 1.0f);
	}
	
	else if (var == VAR_COMPAT_TIME) {
		//RTLOG("OglBuffer::SetVar: " << time_total);
		glUniform1f(uindex, (GLfloat)s.time_total);
	}
	
	else if (var == VAR_COMPAT_TIMEDELTA) {
		ASSERT(s.frame_time != 0.0);
		glUniform1f(uindex, (GLfloat)s.frame_time);
	}
	
	else if (var == VAR_COMPAT_FRAME) {
		ASSERT(s.frames >= 0);
		glUniform1i(uindex, s.frames);
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
		double sec = ((int)s.time.hour * 60 + (int)s.time.minute) * 60 + (int)s.time.second;
		sec += s.time_us;
		glUniform4f(uindex, (GLfloat)s.time.year, (GLfloat)s.time.month, (GLfloat)s.time.day, (GLfloat)sec);
	}
	
	else if (var == VAR_COMPAT_SAMPLERATE) {
		glUniform1f(uindex, (GLfloat)s.sample_rate);
	}
	
	else if (var == VAR_COMPAT_OFFSET) {
		if (s.size.cx > 0 && s.size.cy > 0) {
			int x = s.offset.x;
			int y = s.size.cy - s.size.cy - s.offset.y; // -y_offset
			glUniform2f(uindex, (GLfloat)x, (GLfloat)y);
		} else {
			glUniform2f(uindex, 0.0f, 0.0f);
		}
	}
	
	else if (var >= VAR_COMPAT_CHANNEL0 && var <= VAR_COMPAT_CHANNEL3) {
		int ch = var - VAR_COMPAT_CHANNEL0;
		int tex = GetInputTex(ch);
		ASSERT(tex != 0);
		glActiveTexture(GL_TEXTURE0 + ch);
		glBindTexture(GetTexType(ch), tex);
		glUniform1i(uindex, ch);
	}
	
	else if (var == VAR_COMPAT_FRAMERATE) {
		ASSERT(s.fps > 0);
		glUniform1f(uindex, (GLfloat)s.fps);
	}
	
	else if (var == VAR_COMPAT_CHANNELTIME) {
		double values[INPUT_COUNT];
		for(int j = 0; j < INPUT_COUNT; j++) {
			OglInputState& in = s.inputs[j];
			values[j] = in.in_buf ? in.in_buf->state.time_total : 0;
		}
		glUniform4f(uindex, (GLfloat)values[0], (GLfloat)values[1], (GLfloat)values[2], (GLfloat)values[3]);
	}
	
	else if (var >= VAR_COMPAT_CHANNELRESOLUTION0 && var <= VAR_COMPAT_CHANNELRESOLUTION3) {
		int ch = var - VAR_COMPAT_CHANNELRESOLUTION0;
		GLfloat values[3] = {0,0,0};
		OglInputState& in = state.inputs[ch];
		const OglBuffer* in_buf = in.in_buf;
		if (in_buf) {
			values[0] = (GLfloat)in_buf->state.size.cx;
			values[1] = (GLfloat)in_buf->state.size.cy;
			values[2] = (GLfloat)in_buf->state.depth;
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
		glUniform3f(uindex, values[0], values[1], values[2]);
	}
	
	else if (var == VAR_COMPAT_BLOCKOFFSET) {
		glUniform1f(uindex, (GLfloat)s.block_offset);
	}
	else {
		ASSERT_(false, "Invalid variable");
	}
}

void OglBuffer::ClearTex() {
	for(int bi = 0; bi < 2; bi++) {
		GLuint& color_buf = state.color_buf[bi];
		GLuint& depth_buf = state.depth_buf[bi];
		GLuint& frame_buf = state.frame_buf[bi];
		
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
#if 0
void OglBuffer::ClearProg() {
	for(int i = 0; i < PROG_COUNT; i++) {
		auto& prog = this->prog[i];
		if (prog >= 0) {
			glDeleteProgram(prog);
			prog = -1;
		}
	}
}
#endif
void OglBuffer::CreateTex(bool create_depth, bool create_fbo) {
	auto& s = state;
	
	int buf_count = 1;
	if (s.is_doublebuf)
		buf_count++;
	
	Size sz = s.size;
	
	EnableGfxAccelDebugMessages(1);
	
	for(int bi = 0; bi < buf_count; bi++) {
		GLuint& color_buf = s.color_buf[bi];
		GLuint& depth_buf = s.depth_buf[bi];
		GLuint& frame_buf = s.frame_buf[bi];
		ASSERT(color_buf == 0);
		
		auto fmt = s.GetGlFormat();
		
		// color buffer
		glGenTextures(1, s.color_buf);
		glBindTexture(GL_TEXTURE_2D, color_buf);
		glTexImage2D(GL_TEXTURE_2D, 0, fmt, sz.cx, sz.cy, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
		TexFlags(GL_TEXTURE_2D, s.filter, s.wrap);
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
	if (input_i < 0 || input_i >= ShaderVar::INPUT_COUNT)
		return -1;
	
	const OglInputState& in = state.inputs[input_i];
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
	if (input_i < 0 || input_i >= ShaderVar::INPUT_COUNT)
		return -1;
	
	const OglInputState& in = state.inputs[input_i];
	
	if (in.type == ShaderVar::VOLUME)
		return GL_TEXTURE_3D;
	
	else if (in.type == ShaderVar::CUBEMAP)
		return GL_TEXTURE_CUBE_MAP;
	
	else
		return GL_TEXTURE_2D;
}







bool OglBuffer::SetupLoopback() {
	if (loopback < 0)
		return true;
	
	if (loopback >= ShaderVar::INPUT_COUNT) {
		LOG("OglBuffer::SetupLoopback: error: too large loopback id #" << loopback);
		return false;
	}
	
	OglInputState& in = state.inputs[loopback];
	in.in_buf = this;
	in.id = state.id;
	in.type = ShaderVar::BUFFER;
	
	return true;
}

bool OglBuffer::CompilePrograms() {
	/*const char* fn_name = "CompilePrograms";
	for(int i = 0; i < PROG_COUNT; i++) {
		if (i == PROG_FRAGMENT && !CompileFragmentShader())
			return false;
		if (i == PROG_VERTEX && !CompileVertexShader())
			return false;
	}*/
	
	OglCompiler comps[ShaderVar::PROG_COUNT];
	OglLinker linker;
	linker.EnableLog();
	for(int i = 0; i < ShaderVar::PROG_COUNT; i++) {
		auto& s = state.shaders[i];
		if (s.code.IsEmpty())
			continue;
		
		OglCompiler& comp = comps[i];
		s.enabled = true;
		
		if (!comp.Compile(state, s, (ShaderVar::Type)i, s.code, s.library)) {
			last_error = comp.GetError();
			return false;
		}
	}
	
	if (!linker.Link(state)) {
		last_error = linker.GetError();
		return false;
	}
	
	return true;
}
#if 0
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
	
				"uniform vec2      iMouse;\n"
				"uniform float     iAudioSeconds;\n"
				
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
					"	float t = iAudioSeconds + gl_FragCoord.x / iSampleRate;\n"
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
				
				"uniform vec2      iMouse;\n"
				"uniform float     iAudioSeconds;\n"
				
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

#endif

GLint OglBuffer::GetOutputTexture(bool reading_self) const {
	auto& s = state;
	ASSERT(!reading_self || s.is_doublebuf);
	int buf_i = s.buf_i;
	if (reading_self)
		buf_i = (buf_i + 1) % 2;
	if (s.color_buf[buf_i] == 0) {DLOG("GetOutputTexture failed");}
	ASSERT(s.color_buf[buf_i] > 0);
	return s.color_buf[buf_i];
}

void OglBuffer::TexFlags(int type, ShaderVar::Filter filter, ShaderVar::Wrap repeat) {
	if (filter == ShaderVar::FILTER_NEAREST) {
		glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	}
	else if (filter == ShaderVar::FILTER_LINEAR) {
		glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}
	else if (filter == ShaderVar::FILTER_MIPMAP) {
		glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glGenerateMipmap(type);
	}
	
	if (repeat == ShaderVar::WRAP_REPEAT) {
		glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);
		if (type == GL_TEXTURE_3D)
			glTexParameteri(type, GL_TEXTURE_WRAP_R, GL_REPEAT);
	}
	else if (repeat == ShaderVar::WRAP_CLAMP) {
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
	if (in_id >= 0 && in_id < ShaderVar::INPUT_COUNT) {
		//LOG("OglBuffer::LoadOutputLink: " << name << " #" << in_id);
		
		ASSERT(v.ptr);
		OglInputState& in = state.inputs[in_id];
		in.id = in_id;
		in.in_buf = (OglBuffer*)v.ptr;
		
		ASSERT(sz.cx > 0 && sz.cy > 0);
		
		if (state.is_cubemap)
			in.type = ShaderVar::CUBEMAP;
		else if (sz.cz > 0)
			in.type = ShaderVar::VOLUME;
		else
			in.type = ShaderVar::TEXTURE;
		
		return true;
	}
	
	RTLOG("OglBuffer::LoadOutputLink: error: unexpected data");
	return false;
}

void OglBuffer::SetInputVolume(int in_id) {
	TODO
	#if 0
	if (in_id >= in_buf.GetCount())
		in_buf.SetCount(in_id+1);
	
	OglBufferInput& in = in_buf[in_id];
	in.type = OglBufferInput::VOLUME;
	#endif
}

void OglBuffer::SetInputCubemap(int in_id) {
	TODO
	#if 0
	if (in_id >= in_buf.GetCount())
		in_buf.SetCount(in_id+1);
	
	OglBufferInput& in = in_buf[in_id];
	in.type = OglBufferInput::CUBEMAP;
	#endif
}

NAMESPACE_TOPSIDE_END

#endif

