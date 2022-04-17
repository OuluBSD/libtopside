#include "IGraphics.h"

NAMESPACE_PARALLEL_BEGIN

template <class Gfx>
Callback2<String, BufferT<Gfx>*> BufferT<Gfx>::WhenLinkInit;


template <class Gfx>
void BufferT<Gfx>::MakeFrameQuad() {
	// essentially same as glRectf(-1.0, -1.0, 1.0, 1.0);
	Mesh m;
	m.vertices.SetCount(4);
	Vertex& tl = m.vertices[0];
	Vertex& tr = m.vertices[1];
	Vertex& br = m.vertices[2];
	Vertex& bl = m.vertices[3];
	tl.SetPosTex(vec3(-1, +1, 0), vec2(-1,+1));
	tr.SetPosTex(vec3(+1, +1, 0), vec2(+1,+1));
	br.SetPosTex(vec3(+1, -1, 0), vec2(+1,-1));
	bl.SetPosTex(vec3(-1, -1, 0), vec2(-1,-1));
	m.indices << 0 << 2 << 1; // top-right triangle CCW
	m.indices << 0 << 3 << 2; // bottom-left triangle CCW
	
	DataObject& o = data.AddObject();
	o.Refresh(m);
}

template <class Gfx>
bool BufferT<Gfx>::LoadShaderFile(GVar::ShaderType shader_type, String shader_path, String library_path) {
	DLOG("BufferT::LoadShaderFile: " << shader_path);
	
	ASSERT(shader_type > GVar::SHADERTYPE_NULL && shader_type < GVar::SHADERTYPE_COUNT);
	ShaderState& shader = rt.shaders[shader_type];
	
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
			LOG("LoadShaderFile: error: file does not exist: " << path);
			succ = false;
		}
	}
	if (!succ) return false;
	
	if (!FileExists(shader_path))
		shader_path = ShareDirFile(shader_path);
	
	if (!FileExists(shader_path)) {
		LOG("LoadShaderFile: error: file does not exist: " << shader_path);
		return false;
	}
	
	String content = LoadFile(shader_path);
	if (content.IsEmpty()) {
		LOG("LoadShaderFile: error: got empty shader file from: " << shader_path);
		return false;
	}
	
	//DUMP(content);
	shader.code = content;
	shader.library = library;
	
	return true;
}

template <class Gfx>
bool BufferT<Gfx>::LoadBuiltinShader(GVar::ShaderType shader_type, String id) {
	int i = SoftShaderLibrary::GetMap(shader_type).Find(id);
	if (i < 0) {
		last_error = "could not find shader";
		return false;
	}
	
	soft[shader_type] = SoftShaderLibrary::GetMap(shader_type)[i]();
	
	return true;
}

template <class Gfx>
void BufferT<Gfx>::Update(double dt) {
	if (rt.is_time_used) {
		ctx.time_us += dt;
		if (ctx.time_us >= 1.0) {
			ctx.time_us = fmod(ctx.time_us, 1.0);
			ctx.time = GetSysTime();
			RTLOG("Update: " << dt << ", time=" << ctx.time.ToString());
		}
	}
}

template <class Gfx>
bool BufferT<Gfx>::SetLoopback(String loopback_str) {
	if (loopback_str.IsEmpty()) {
		loopback = -1;
		return false;
	}
	
	if (!IsAllDigit(loopback_str)) {
		LOG("SetLoopback: error: expected digit string, got '" << loopback_str << "'");
		return false;
	}
	
	loopback = StrInt(loopback_str);
	if (loopback < -1 || loopback >= 4) {
		LOG("SetLoopback: error: invalid loopback #" << loopback << ", expected between -1 and +3");
		return false;
	}
	
	fb.is_doublebuf = loopback >= 0;
	
	return true;
}

template <class Gfx>
bool BufferT<Gfx>::InitializeTexture(Size sz, int channels, Sample sample, const byte* data, int len) {
	RTLOG("InitializeTexture: " << sz.ToString() << ", " << HexStr((void*)data) << ", " << len);
	TODO
	#if 0
	UpdateTexBuffers();
	
	ReadTexture(sz, channels, data, len);
	#endif
	return true;
}

template <class Gfx>
bool BufferT<Gfx>::InitializeCubemap(Size sz, int channels, Sample sample, const Vector<byte>& d0, const Vector<byte>& d1, const Vector<byte>& d2, const Vector<byte>& d3, const Vector<byte>& d4, const Vector<byte>& d5) {
	RTLOG("InitializeCubemap: " << sz.ToString());
	TODO
	#if 0
	is_cubemap = true;
	
	UpdateTexBuffers();
	
	ReadCubemap(sz, channels, d0, d1, d2, d3, d4, d5);
	#endif
	return true;
}

template <class Gfx>
bool BufferT<Gfx>::InitializeVolume(Size3 sz, int channels, Sample sample, const Vector<byte>& data) {
	RTLOG("InitializeVolume: " << sz.ToString() << ", " << data.GetCount());
	TODO
	#if 0
	UpdateTexBuffers();
	
	ReadTexture(sz, channels, data);
	#endif
	return true;
}

#if 0
template <class Gfx>
void BufferT<Gfx>::ReadTexture(Size sz, int channels, Sample sample, const byte* data, int len) {
	TODO
	#if 0
	GLenum type		= GL_TEXTURE_2D;
	
	GLuint& color_buf = this->color_buf[0];
	ASSERT(color_buf > 0);
	ASSERT(sz == fb_size);
	ASSERT(s.GetSize() == len);
	int intl_fmt = GetGfxChannelFormat(channels);
	
	Gfx::BindTexture (type, color_buf);
	Gfx::TexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	Gfx::TexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	Gfx::PixelStorei(GL_UNPACK_ALIGNMENT, 1);
	
	Gfx::TexImage2D(type, 0, GL_RGBA32F,
		sz.cx,
		sz.cy,
		0, intl_fmt, GL_UNSIGNED_BYTE,
		data);
	
	TexFlags(type, fb_filter, fb_wrap);
	#endif
}

template <class Gfx>
void BufferT<Gfx>::ReadTexture(Size3 sz, int channels, Sample sample, const Vector<byte>& data) {
	TODO
	#if 0
	GLenum type		= GL_TEXTURE_3D;
	
	ASSERT(fb.size.cx == sz.cx && fb.size.cy == sz.cy);
	auto& color_buf = fb.color_buf[0];
	ASSERT(color_buf);
	//int intl_fmt = GetGfxChannelFormat(channels);
	
	Gfx::BindTexture (type, color_buf);
	Gfx::TexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	Gfx::TexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	Gfx::PixelStorei(GL_UNPACK_ALIGNMENT, 1);
	Gfx::TexImage3D(type, 0, GL_RGBA32F,
		sz.cx,
		sz.cy,
		sz.cz,
		//0, intl_fmt, GL_UNSIGNED_BYTE,
		0, fb.fmt, fb.type,
		data.Begin());
	
	TexFlags(type, fb.filter, fb.wrap);
	#endif
}


template <class Gfx>
void BufferT<Gfx>::ReadCubemap(Size sz, int channels, const Vector<byte>& d0, const Vector<byte>& d1, const Vector<byte>& d2, const Vector<byte>& d3, const Vector<byte>& d4, const Vector<byte>& d5) {
	GLenum type		= GL_TEXTURE_CUBE_MAP;
	GLuint& tex		= color_buf[0];
	int ch_code		= GetGfxChannelFormat(channels);
	
	Gfx::BindTexture (type, tex);
	
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
		Gfx::TexImage2D(tex_type, 0, GL_RGBA,
					 sz.cx, sz.cy,
					 0, ch_code,
					 GL_UNSIGNED_BYTE,
					 data->Begin());
	}
	
	TexFlags(type, fb_filter, fb_wrap);
	
	GLenum err = Gfx::GetError();
	if (err != GL_NO_ERROR)
		OnError("ReadCubemap", "Gfx error " + HexStr(err));
	
	Gfx::BindTexture(type, 0);
}

#endif

template <class Gfx>
bool BufferT<Gfx>::Initialize() {
	DLOG("BufferT::Initialize: load new program");
	
	ASSERT(!initialized);
	ASSERT(fb.fps > 0);
	ctx.frame_time = 1.0 / fb.fps;
	ctx.time = GetSysTime();
	ctx.block_offset = 0;
	
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

template <class Gfx>
void BufferT<Gfx>::RefreshPipeline() {
	DLOG("BufferT::RefreshPipeline begin");
	
	CreatePipeline();
	
	UpdateTexBuffers();
	
	//if (!CheckInputTextures())
	//	return;
	
	Reset();
	
	DLOG("BufferT::RefreshPipeline end");
}

template <class Gfx>
void BufferT<Gfx>::Reset() {
	ctx.time_total = 0;
}

template <class Gfx>
void BufferT<Gfx>::SetFramebufferSize(Size sz) {
	ASSERT(sz.cx > 0 && sz.cy > 0);
	fb.size = sz;
	if (initialized)
		UpdateTexBuffers();
}

template <class Gfx>
void BufferT<Gfx>::UpdateTexBuffers() {
	auto& s = fb;
	if (!s.is_win_fbo) {
		ASSERT(s.channels > 0);
		ASSERT(s.size.cx > 0 && s.size.cy > 0);
		
		this->BaseUpdateTexBuffers(s);
		
		ClearTex();
		
		CreateTex(
			true, true);
		
	}
}

template <class Gfx>
int BufferT<Gfx>::NewWriteBuffer() {
	auto& s = fb;
	if (s.is_doublebuf)
		s.buf_i = (s.buf_i + 1) % 2;
	return s.buf_i;
}

template <class Gfx>
void BufferT<Gfx>::Process(ShaderPipeline& pipe) {
	
	TODO
	
}

template <class Gfx>
void BufferT<Gfx>::Process(const RealtimeSourceConfig& cfg) {
	auto& prog = rt.prog;
	auto& pipeline = rt.pipeline;
	
	ASSERT(prog);
	if (prog == 0)
		return;
	
	RTLOG("Process " << HexStr(this) << " time: " << ctx.time_total);
	
	ctx.time_total = cfg.time_total;
	//RTLOG("Process: " << time_total);
	ctx.frames++;
	
	if (env) {
		Size& video_size = env->Set<Size>(SCREEN0_SIZE);
		if (video_size.cx == 0 || video_size.cy == 0)
			video_size = fb.size;
		else if (video_size != fb.size) {
			fb.size = video_size;
			UpdateTexBuffers();
		}
	}
	
	Gfx::BindProgramPipeline(pipeline);
	Gfx::UseProgram(prog);

	
	if (!rt.is_searched_vars)
		FindVariables();
	
	int bi = NewWriteBuffer();
	
	if (!fb.is_win_fbo) {
		ASSERT(fb.frame_buf[bi]);
	    Gfx::BindFramebuffer(fb.frame_buf[bi]);
	    Gfx::DrawBuffers(GVar::COLOR0_EXT);
	}


	SetVars(prog, cfg);

	RendVer(OnProcess);


	Gfx::Clear(GVar::COLOR_BUFFER);
	
	
	if (!use_user_data) {
		/*if (binders.GetCount()) {
			Buffer* buf = CastPtr<Buffer>(this);
			ASSERT(buf);
			Shader shader;
			shader.SetState(data);
			for (BinderIface* iface : binders)
				iface->Render(data);
		}*/
		
		//if (binders.IsEmpty()) {
		if (0)
			Gfx::RenderScreenRect();
		else if (!user_data && data.objects.IsEmpty())
			MakeFrameQuad();
		//}
		
		// render VBA from state
		Gfx::BeginRender();
		for (DataObject& o : data.objects) {
			SetVars(data, rt.prog, o);
			o.Paint(data);
		}
		Gfx::EndRender();
	}
	else if (user_data) {
		Gfx::BeginRender();
		for (DataObject& o : user_data->objects) {
			SetVars(*user_data, rt.prog, o);
			o.Paint(*user_data);
		}
		Gfx::EndRender();
	}
	
	EnableGfxAccelDebugMessages(1);
	
	ASSERT(fb.is_win_fbo == (fb.frame_buf[bi] == 0));
	if (fb.frame_buf[bi]) {
		// backup render target
	    //Gfx::DrawBuffer(GL_FRONT);
	    
	    // Some components (e.g. audio) needs to read the framebuffer
	    if (fb.is_read_fb_output)
			UseRenderedFramebuffer();
		
	    Gfx::BindFramebufferDefault();
	}
	
	EnableGfxAccelDebugMessages(0);
	
	Gfx::UnbindProgramPipeline();
	
	if (fb.is_audio) {
		ctx.block_offset += fb.size.cx;
	}
	else {
		ctx.block_offset += 1.0;
	}
}

template <class Gfx>
void BufferT<Gfx>::UseRenderedFramebuffer() {
	TODO
	#if 0
	auto& s = fb;
	auto fmt = s.GetGlFormat();
	auto type = s.GetGlType();
	ASSERT(s.GetGlSize() > 0);
	ASSERT(s.size.cx > 0 && s.size.cy > 0);
	ASSERT(fmt >= 0);
	ASSERT(s.GetGlType() >= 0);
	
	fb_out.SetCount(s.GetGlSize());
	
	ASSERT(s.color_buf[s.buf_i] > 0);
	Gfx::ReadBuffer(GL_COLOR_ATTACHMENT0_EXT);
	
	TODO // glReadPixels will crash mysteriously
	Gfx::ReadPixels(0, 0, s.size.cx, s.size.cy, fmt, type, fb_out.Begin());
	#endif
}

template <class Gfx>
void BufferT<Gfx>::ClearPipeline() {
	if (rt.pipeline) {
		Gfx::DeleteProgramPipeline(rt.pipeline);
	}
}

template <class Gfx>
void BufferT<Gfx>::CreatePipeline() {
	ClearPipeline();
	
	Gfx::GenProgramPipeline(rt.pipeline);
	
	
	// only 1 program in pipeline currently
	{
		auto& prog = rt.prog;
		if (prog >= 0) {
			int bmask = 0;
			for(int i = 0; i < GVar::SHADERTYPE_COUNT; i++) {
				if (rt.shaders[(GVar::ShaderType)i].enabled) {
					int bit = 1 << i;
					bmask |= bit;
				}
			}
			ASSERT(bmask != 0);
			Gfx::UseProgramStages(rt.pipeline, bmask, prog);
		}
	}
}







template <class Gfx>
void BufferT<Gfx>::FindVariables() {
	int n_uniforms = 0;
	Gfx::GetProgramiv(rt.prog, GVar::ACTIVE_UNIFORMS, n_uniforms);
	
	memset(rt.var_idx, -1, sizeof(rt.var_idx));
	rt.user_vars.Clear();
	RendVer(OnClearVars);
	for (int i = 0; i < n_uniforms; i++) {
		int size = 0;
		int type = 0;
		String name_str = Gfx::GetActiveUniform(rt.prog, i, &size, &type);
		const char* name = name_str;
		
		bool found = false;
		bool state_var = false;
		for(int j = 0; j < GVar::VAR_COUNT; j++) {
			const char* var_name = GVar::names[j];
			if (strncmp(var_name, name, 128) == 0) {
				rt.var_idx[j] = i;
				if (j == GVar::VAR_COMPAT_DATE && !rt.is_time_used)
					rt.is_time_used = true;
				found = true;
				state_var = !GVar::is_obj_var[j];
				break;
			}
		}
		
		if (!found) {
			rt.user_vars << name_str;
		}
		
		RendVer2(OnRealizeVar, name_str, state_var);
	}
	
	rt.is_searched_vars = true;
}

template <class Gfx>
void BufferT<Gfx>::SetVars(DataState& d, int gl_prog, const DataObject& o) {
	for(int i = 0; i < GVar::VAR_COUNT; i++)
		if (GVar::is_obj_var[i] && rt.var_idx[i] >= 0)
			SetVar(d, i, gl_prog, o);
}

template <class Gfx>
void BufferT<Gfx>::SetVar(DataState& data, int var, int gl_prog, const DataObject& o) {
	using namespace GVar;
	int uindex = rt.var_idx[var];
	ASSERT(uindex >= 0);
	if (var == VAR_VIEW) {
		Gfx::UniformMatrix4fv(uindex, data.view);
	}
	else if (var == VAR_LIGHTDIR) {
		Gfx::Uniform3f(uindex, data.light_dir[0], data.light_dir[1], data.light_dir[2]);
	}
	else if (var == VAR_PROJECTIONOVERRIDE) {
		Gfx::UniformMatrix4fv(uindex, o.proj_override);
	}
	else if (var == VAR_SCALE) {
		Gfx::UniformMatrix4fv(uindex, o.scale);
	}
	else if (var == VAR_VIEWOVERRIDE) {
		Gfx::UniformMatrix4fv(uindex, o.view_override);
	}
	else if (var == VAR_MODEL) {
		Gfx::UniformMatrix4fv(uindex, o.model);
	}
	else if (var >= VAR_NONE && var <= VAR_UNKNOWN) {
		int tex_ch = var - VAR_NONE;
		int tex_i = o.tex_id[tex_ch];
		auto& tex = data.textures[tex_i];
		Gfx::ActiveTexture(tex_ch);
		Gfx::BindTextureRO(GVar::TEXTYPE_2D, tex);
		Gfx::Uniform1i(uindex, tex_ch);
	}
	else TODO
	#if 0
	if (var == VAR_VIEW) {
		if (o.is_global_view)
			Gfx::UniformMatrix4fv(uindex, data.view);
		else
			Gfx::UniformMatrix4fv(uindex, o.view);
	}
	else if (var == VAR_PROJECTION) {
		/*if (o.is_global_proj)
			TODO
		else*/
		Gfx::UniformMatrix4fv(uindex, o.proj);
	}
	else if (var == VAR_SCALE) {
		Gfx::UniformMatrix4fv(uindex, o.scale);
	}
	else if (var == VAR_MODEL) {
		Gfx::UniformMatrix4fv(uindex, o.model);
	}
	#endif
}

template <class Gfx>
void BufferT<Gfx>::SetVars(int gl_prog, const RealtimeSourceConfig& cfg) {
	for(int i = 0; i < GVar::VAR_COUNT; i++)
		if (!GVar::is_obj_var[i] && rt.var_idx[i] >= 0)
			SetVar(i, gl_prog, cfg);
}

template <class Gfx>
void BufferT<Gfx>::SetVar(int var, int gl_prog, const RealtimeSourceConfig& cfg) {
	using namespace GVar;
	int uindex = rt.var_idx[var];
	ASSERT(uindex >= 0);
	if (uindex < 0)
		return;
	
	RendVer1(OnUpdateVar, GVar::names[var]);
	
	if (var == VAR_AUDIOTIME) {
		Gfx::Uniform1f(uindex, (float)ctx.time_total);
	}
	
	else if (var == VAR_VIEW) {
		ASSERT(0); // pass
	}
	else if (var == VAR_VIEWOVERRIDE) {
		ASSERT(0); // pass
	}
	else if (var == VAR_PROJECTIONOVERRIDE) {
		ASSERT(0); // pass
	}
	else if (var == VAR_SCALE) {
		ASSERT(0); // pass
	}
	else if (var == VAR_MODEL) {
		ASSERT(0); // pass
	}
	else if (var == VAR_COMPAT_RESOLUTION) {
		ASSERT(fb.size.cx > 0 && fb.size.cy > 0);
		Gfx::Uniform3f(uindex, (float)fb.size.cx, (float)fb.size.cy, 1.0f);
	}
	
	else if (var == VAR_COMPAT_TIME) {
		//RTLOG("SetVar: " << time_total);
		Gfx::Uniform1f(uindex, (float)ctx.time_total);
	}
	
	else if (var == VAR_COMPAT_TIMEDELTA) {
		ASSERT(ctx.frame_time != 0.0);
		Gfx::Uniform1f(uindex, (float)ctx.frame_time);
	}
	
	else if (var == VAR_COMPAT_FRAME) {
		ASSERT(ctx.frames >= 0);
		Gfx::Uniform1i(uindex, ctx.frames);
	}
	
	else if (var == VAR_COMPAT_MOUSE) {
		if (env) {
			#ifdef flagSCREEN
			Point& mouse_drag = env->Set<Point>(MOUSE_TOYCOMPAT_DRAG);
			Point& mouse_click = env->Set<Point>(MOUSE_TOYCOMPAT_CLICK);
			Gfx::Uniform4f(uindex,
				(float)mouse_click.x,
				(float)mouse_click.y,
				(float)mouse_drag.x,
				(float)mouse_drag.y);
			#endif
		}
	}
	
	else if (var == VAR_COMPAT_DATE) {
		double sec = ((int)ctx.time.hour * 60 + (int)ctx.time.minute) * 60 + (int)ctx.time.second;
		sec += ctx.time_us;
		Gfx::Uniform4f(uindex, (float)ctx.time.year, (float)ctx.time.month, (float)ctx.time.day, (float)sec);
	}
	
	else if (var == VAR_COMPAT_SAMPLERATE) {
		Gfx::Uniform1f(uindex, (float)ctx.sample_rate);
	}
	
	else if (var == VAR_COMPAT_OFFSET) {
		if (fb.size.cx > 0 && fb.size.cy > 0) {
			int x = fb.offset.x;
			int y = fb.size.cy - fb.size.cy - fb.offset.y; // -y_offset
			Gfx::Uniform2f(uindex, (float)x, (float)y);
		} else {
			Gfx::Uniform2f(uindex, 0.0f, 0.0f);
		}
	}
	
	else if (var >= VAR_COMPAT_CHANNEL0 && var <= VAR_COMPAT_CHANNEL3) {
		int ch = var - VAR_COMPAT_CHANNEL0;
		int tex_ch = COMPAT_OFFSET + ch;
		const NativeFrameBuffer* tex = GetInputTex(ch);
		ASSERT(tex);
		Gfx::ActiveTexture(tex_ch);
		Gfx::BindTextureRO(GetTexType(ch), *tex);
		Gfx::Uniform1i(uindex, tex_ch);
	}
	
	else if (var == VAR_COMPAT_FRAMERATE) {
		ASSERT(fb.fps > 0);
		Gfx::Uniform1f(uindex, (float)fb.fps);
	}
	
	else if (var == VAR_COMPAT_CHANNELTIME) {
		double values[INPUT_COUNT];
		for(int j = 0; j < INPUT_COUNT; j++) {
			InputState& in = rt.inputs[j];
			values[j] = in.in_buf ? in.in_buf->ctx.time_total : 0;
		}
		Gfx::Uniform4f(uindex, (float)values[0], (float)values[1], (float)values[2], (float)values[3]);
	}
	
	else if (var >= VAR_COMPAT_CHANNELRESOLUTION0 && var <= VAR_COMPAT_CHANNELRESOLUTION3) {
		int ch = var - VAR_COMPAT_CHANNELRESOLUTION0;
		float values[3] = {0,0,0};
		InputState& in = rt.inputs[ch];
		const BufferT* in_buf = in.in_buf;
		if (in_buf) {
			values[0] = (float)in_buf->fb.size.cx;
			values[1] = (float)in_buf->fb.size.cy;
			values[2] = (float)in_buf->fb.depth;
		}
		/*else if (
			in.type == BufferTInput::TEXTURE ||
			in.type == BufferTInput::CUBEMAP ||
			in.type == BufferTInput::VOLUME) {
			ASSERT(in.id >= 0);
			if (in.id >= 0 && ctx) {
				BufferT& comp = ctx->GetComponentById(in.id);
				values[0] = in.res.cx;
				values[1] = in.res.cy;
				values[2] = in.vol_depth;
			}
		}*/
		Gfx::Uniform3f(uindex, values[0], values[1], values[2]);
	}
	
	else if (var == VAR_COMPAT_BLOCKOFFSET) {
		Gfx::Uniform1f(uindex, (float)ctx.block_offset);
	}
	else {
		ASSERT_(false, "Invalid variable");
	}
}

template <class Gfx>
void BufferT<Gfx>::ClearTex() {
	for(int bi = 0; bi < 2; bi++) {
		auto& color_buf = fb.color_buf[bi];
		auto& depth_buf = fb.depth_buf[bi];
		auto& frame_buf = fb.frame_buf[bi];
		
		if (color_buf > 0) {
			Gfx::DeleteTexture(color_buf);
			color_buf = Null;
		}
		if (depth_buf > 0) {
			Gfx::DeleteRenderbuffer(depth_buf);
			depth_buf = Null;
		}
		if (frame_buf > 0) {
			Gfx::DeleteFramebuffer(frame_buf);
			frame_buf = Null;
		}
	}
}

template <class Gfx>
void BufferT<Gfx>::CreateTex(bool create_depth, bool create_fbo) {
	auto& s = fb;
	
	int buf_count = 1;
	if (s.is_doublebuf)
		buf_count++;
	
	Size sz = s.size;
	
	EnableGfxAccelDebugMessages(1);
	
	for(int bi = 0; bi < buf_count; bi++) {
		auto& color_buf = s.color_buf[bi];
		auto& depth_buf = s.depth_buf[bi];
		auto& frame_buf = s.frame_buf[bi];
		ASSERT(color_buf == 0);
		
		//auto fmt = s.GetGlFormat();
		
		// color buffer
		Gfx::GenTexture(s.color_buf[0]);
		Gfx::BindTextureRW(GVar::TEXTYPE_2D, color_buf);
		//TODO Gfx::TexImage2D(GL_TEXTURE_2D, 0, fmt, sz.cx, sz.cy, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
		TexFlags(GVar::TEXTYPE_2D, s.filter, s.wrap);
		Gfx::UnbindTexture(GVar::TEXTYPE_2D);
		
		// depth buffer
		if (create_depth) {
			Gfx::CreateRenderbuffer(depth_buf);
			Gfx::BindRenderbuffer(depth_buf);
			Gfx::RenderbufferStorage(sz);
			Gfx::UnbindRenderbuffer();
		}
		
		// FBO
		if (create_fbo) {
			Gfx::CreateFramebuffer(frame_buf);
			Gfx::BindFramebuffer(frame_buf);
			
			// combine FBO to color buffer
			Gfx::FramebufferTexture2D(color_buf);
			
			// combine FBO to depth buffer
			if (create_depth)
				Gfx::FramebufferRenderbuffer(depth_buf);
			
			// reset FBO
			Gfx::UnbindFramebuffer();
		}
	}
	
	EnableGfxAccelDebugMessages(0);
}

template <class Gfx>
const TNG NativeFrameBuffer* BufferT<Gfx>::GetInputTex(int input_i) const {
	const char* fn_name = "GetInputTex";
	//DLOG("BufferT::GetInputTex");
	if (input_i < 0 || input_i >= GVar::INPUT_COUNT)
		return 0;
	
	const InputState& in = rt.inputs[input_i];
	if (in.in_buf == 0) {
		RTLOG("GetInputTex: warning: no input fbo buffer");
		return 0;
	}
	
	const BufferT* in_comp = in.in_buf;
	if (!in_comp)
		return 0;
	
	const NativeFrameBuffer& tex = in_comp->GetOutputTexture(in_comp == this);
	ASSERT(tex);
	
	return &tex;
}

template <class Gfx>
GVar::TextureType BufferT<Gfx>::GetTexType(int input_i) const {
	if (input_i < 0 || input_i >= GVar::INPUT_COUNT)
		return GVar::TEXTYPE_2D;
	
	const InputState& in = rt.inputs[input_i];
	
	if (in.type == GVar::VOLUME_INPUT)
		return GVar::TEXTYPE_3D;
	
	else if (in.type == GVar::CUBEMAP_INPUT)
		return GVar::TEXTYPE_CUBE_MAP;
	
	else
		return GVar::TEXTYPE_2D;
}







template <class Gfx>
bool BufferT<Gfx>::SetupLoopback() {
	if (loopback < 0)
		return true;
	
	if (loopback >= GVar::INPUT_COUNT) {
		LOG("SetupLoopback: error: too large loopback id #" << loopback);
		return false;
	}
	
	InputState& in = rt.inputs[loopback];
	in.in_buf = this;
	in.id = rt.id;
	in.type = GVar::BUFFER_INPUT;
	ASSERT(in.in_buf);
	
	return true;
}

template <class Gfx>
bool BufferT<Gfx>::BuiltinShader() {return false;}

template <class Gfx>
template <int>
bool BufferT<Gfx>::BuiltinShaderT() {
	bool succ = false;
	if (!rt.pipeline)
		rt.pipeline.Create();
	for(int i = 0; i < GVar::SHADERTYPE_COUNT; i++) {
		if (soft[i]) {
			GVar::ShaderType t = (GVar::ShaderType)i;
			auto& s = rt.shaders[i];
			s.shader.Create(t);
			s.shader = &*soft[i];
			s.enabled = true;
			if (!rt.prog) {
				rt.prog.Create();
			}
			rt.prog.Attach(rt.shaders[i].shader);
			rt.pipeline.Use(rt.prog, 1 << i);
			if (i == GVar::FRAGMENT_SHADER)
				succ = true;
		}
	}
	return succ;
}

#ifdef flagSDL2
template <>
bool BufferT<SdlCpuGfx>::BuiltinShader() {
	return BuiltinShaderT<0>();
}
#endif

#ifdef flagPOSIX
template <>
bool BufferT<X11SwGfx>::BuiltinShader() {
	return BuiltinShaderT<0>();
}
#endif

template <class Gfx>
bool BufferT<Gfx>::CompilePrograms() {
	/*const char* fn_name = "CompilePrograms";
	for(int i = 0; i < PROG_COUNT; i++) {
		if (i == FRAGMENT_SHADER && !CompileFragmentShader())
			return false;
		if (i == VERTEX_SHADER && !CompileVertexShader())
			return false;
	}*/
	
	if (BuiltinShader()) {
		use_user_data = true;
		return true;
	}
	use_user_data = false;
	
	Compiler comps[GVar::SHADERTYPE_COUNT];
	Linker linker;
	linker.EnableLog();
	for(int i = 0; i < GVar::SHADERTYPE_COUNT; i++) {
		auto& s = rt.shaders[i];
		if (s.code.IsEmpty())
			continue;
		
		Compiler& comp = comps[i];
		s.enabled = true;
		
		if (!comp.Compile(ctx, rt, fb, s, (GVar::ShaderType)i)) {
			last_error = comp.GetError();
			return false;
		}
	}
	
	if (!linker.Link(rt)) {
		last_error = linker.GetError();
		return false;
	}
	
	return true;
}

template <class Gfx>
const TNG NativeFrameBuffer& BufferT<Gfx>::GetOutputTexture(bool reading_self) const {
	auto& s = fb;
	ASSERT(!reading_self || s.is_doublebuf);
	int buf_i = s.buf_i;
	
	
	if (reading_self)
		buf_i = (buf_i + 1) % 2;
	if (s.color_buf[buf_i] == 0) {DLOG("BufferT::GetOutputTexture failed");}
	ASSERT(s.color_buf[buf_i]);
	return s.color_buf[buf_i];
}

template <class Gfx>
void BufferT<Gfx>::TexFlags(GVar::TextureType type, GVar::Filter filter, GVar::Wrap repeat) {
	Gfx::TexParameteri(type, filter, repeat);
}

template <class Gfx>
void BufferT<Gfx>::OnError(const char* fn, String s) {
	LOG("BufferT: error: " << (String)fn << ": " << s);
	last_error.Clear();
	last_error << fn << ": " << s;
}

template <class Gfx>
void BufferT<Gfx>::StoreOutputLink(InternalPacketData& v) {
	static_assert(sizeof(v.u32) == sizeof(uint32), "Unexpected GLuint size");
	
	v.SetText("gfxbuf");
	v.ptr = static_cast<GfxBuffer*>(this);
}

template <class Gfx>
bool BufferT<Gfx>::LoadOutputLink(Size3 sz, int in_id, const InternalPacketData& v) {
	if (in_id >= 0 && in_id < GVar::INPUT_COUNT) {
		//LOG("LoadOutputLink: " << name << " #" << in_id);
		GfxBuffer* gbuf = (GfxBuffer*)v.ptr;
		Buffer* buf = CastPtr<Buffer>(gbuf);
		if (!buf) {
			ASSERT_(0, "Buffer's Gfx type differs");
			return false;
		}
		ASSERT(v.ptr);
		InputState& in = rt.inputs[in_id];
		in.id = in_id;
		in.in_buf = buf;
		
		ASSERT(sz.cx > 0 && sz.cy > 0);
		
		if (fb.is_cubemap)
			in.type = GVar::CUBEMAP_INPUT;
		else if (sz.cz > 0)
			in.type = GVar::VOLUME_INPUT;
		else
			in.type = GVar::TEXTURE_INPUT;
		
		return true;
	}
	
	RTLOG("LoadOutputLink: error: unexpected data");
	return false;
}



template <class Gfx>
bool BufferT<Gfx>::LoadOutputLink(int in_id, const PacketValue& v) {
	if (in_id == 0) {
		const Vector<byte>& data = v.GetData();
		Format fmt = v.GetFormat();
		if (fmt.IsVideo()) {
			VideoFormat& vfmt = fmt;
			int frame_sz = vfmt.GetFrameSize();
			ASSERT(data.GetCount() == frame_sz);
			if (data.GetCount() == frame_sz)
				fb.DrawFill(data.Begin(), frame_sz);
		}
	}
	
	
	#if 0
	if (in_id >= 0 && in_id < GVar::INPUT_COUNT) {
		//LOG("LoadOutputLink: " << name << " #" << in_id);
		
		InputState& in = rt.inputs[in_id];
		in.id = in_id;
		if (in.fb_for_rawdata.IsEmpty()) {
			in.fb_for_rawdata.Create();
			in.fb_for_rawdata->Init(
				vfmt.GetSize(),
				vfmt.GetChannels(),
				vfmt.GetType(),
				v.Begin(), v.GetCount());
		}
		else {
			in.fb_for_rawdata->ReadTexture(
				vfmt.GetSize(),
				vfmt.GetChannels(),
				vfmt.GetType(),
				v.Begin(), v.GetCount());
		}
		in.in_buf = &*in.fb_for_rawdata;
		
		
		Size3 sz = vfmt.GetSize();
		ASSERT(sz.cx > 0 && sz.cy > 0);
		
		if (fb.is_cubemap)
			in.type = GVar::CUBEMAP_INPUT;
		else if (sz.cz > 0)
			in.type = GVar::VOLUME_INPUT;
		else
			in.type = GVar::TEXTURE_INPUT;
		
		return true;
	}
	#endif
	
	
	RTLOG("LoadOutputLink: error: unexpected data");
	return false;
}

template <class Gfx>
void BufferT<Gfx>::SetInputVolume(int in_id) {
	TODO
	#if 0
	if (in_id >= in_buf.GetCount())
		in_buf.SetCount(in_id+1);
	
	BufferTInput& in = in_buf[in_id];
	in.type = BufferTInput::VOLUME;
	#endif
}

template <class Gfx>
void BufferT<Gfx>::SetInputCubemap(int in_id) {
	TODO
	#if 0
	if (in_id >= in_buf.GetCount())
		in_buf.SetCount(in_id+1);
	
	BufferTInput& in = in_buf[in_id];
	in.type = BufferTInput::CUBEMAP;
	#endif
}


GFX_EXCPLICIT_INITIALIZE_CLASS(BufferT)


NAMESPACE_PARALLEL_END
