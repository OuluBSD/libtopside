#include "IGraphics.h"


NAMESPACE_PARALLEL_BEGIN


template <class Gfx>
bool BufferStageT<Gfx>::Initialize(int id, AtomBase& a, const Script::WorldState& ws) {
	ShaderConf& lib_conf = shdr_confs[GVar::SHADERTYPE_COUNT];
	lib_conf.str = ws.Get(".library");
	lib_conf.is_path = true;
	
	quad_count = ws.GetInt(".s" + IntStr(id) + ".quad.count", 1);
	
	// Program string is a simplified way to set shader configuration
	String program_str = ws.Get(".program");
	if (program_str.GetCount()) {
		ShaderConf& vtx_conf = shdr_confs[GVar::VERTEX_SHADER];
		vtx_conf.is_path = false;
		vtx_conf.str = program_str + "_vertex";
		
		ShaderConf& frag_conf = shdr_confs[GVar::FRAGMENT_SHADER];
		frag_conf.is_path = false;
		frag_conf.str = program_str + "_fragment";
	}
	// Normally try to read exact arguments for shaders
	else {
		for(int i = 0; i < GVar::SHADERTYPE_COUNT; i++) {
			String type, extension;
			switch (i) {
				case GL::VERTEX_SHADER:				type = "vtx";  extension = "_vertex"; break;
				case GL::GEOMETRY_SHADER:			type = "geom"; extension = "_geometry"; break;
				case GL::TESS_CONTROL_SHADER:		type = "ctrl"; extension = "_tesscontrol"; break;
				case GL::TESS_EVALUATION_SHADER:	type = "eval"; extension = "_tesseval"; break;
				case GL::FRAGMENT_SHADER:			type = "frag"; extension = "_fragment"; break;
				default: break;
			}

			ShaderConf& conf = shdr_confs[i];
			int tries = id == 0 ? 2 : 1;
			
			for(int j = 0; j < tries; j++) {
				String prefix = "." + (j == 0 ? ("s" + IntStr(id) + ".") : String()) + "shader." + type + ".";
				
				String path = ws.Get(prefix + "path");
				String name = ws.Get(prefix + "name");
				//LOG(prefix + "path");
				
				if (name.GetCount())
					name += extension;
				
				if (path.IsEmpty() && name.IsEmpty() && i == GL::FRAGMENT_SHADER && j == tries-1) {
					LOG("BufferStageT<Gfx>::Initialize: error: no fragment shader given (for stage " << id << ")");
					return false;
				}
				
				if (path.GetCount()) {
					conf.is_path = true;
					conf.str = RealizeShareFile(path);
					break;
				}
				else if (name.GetCount()) {
					conf.is_path = false;
					conf.str = name;
					break;
				}
			}
			
		}
	}
	
	int tries = id == 0 ? 2 : 1;
	for(int j = 0; j < tries; j++) {
		String prefix = "." + (j == 0 ? ("s" + IntStr(id) + ".") : String());
		for(int i = 0; i < 4; i++) {
			String key = prefix + "buf" + IntStr(i);
			//LOG(key);
			String value = ws.Get(key);
			if (value.IsEmpty())
				;
			else if (value == "volume")
				SetInputVolume(i);
			else if (value == "cubemap")
				SetInputCubemap(i);
			else
				TODO
		}
	}
	
	return true;
}

template <class Gfx>
bool BufferStageT<Gfx>::PostInitialize() {
	if (!fb.is_win_fbo) {
		if (fb.is_audio) {
			int sample_rate = buf->snd_sample_rate;
			int frame_samples = buf->snd_frame_samples;
			fb.size = Size(frame_samples,1);
			fb.channels = 2;
			fb.fps = (double)sample_rate / frame_samples;
			fb.sample = GVar::SAMPLE_U16;
		}
		else {
			fb.size = Size(1280,720);
			fb.channels = 4;
			fb.fps = 60;
			fb.sample = GVar::SAMPLE_FLOAT;
		}
	}
	return true;
}

template <class Gfx>
bool BufferStageT<Gfx>::ImageInitialize() {
	ShaderConf& lib_conf = shdr_confs[GVar::SHADERTYPE_COUNT];
	
	for(int i = 0; i < GVar::SHADERTYPE_COUNT; i++) {
		ShaderConf& conf = shdr_confs[i];
		
		if (conf.str.GetCount() &&
			!LoadShader((GVar::ShaderType)i, conf.str, conf.is_path, lib_conf.str))
			return false;
	}
	
	return true;
}

template <class Gfx>
bool BufferStageT<Gfx>::LoadShaderFile(GVar::ShaderType shader_type, String shader_path, String library_path) {
	DLOG("BufferStageT::LoadShaderFile: " << shader_path);
	
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
bool BufferStageT<Gfx>::LoadShader(GVar::ShaderType shader_type, String str, bool is_path, String library_paths) {
	if (str.IsEmpty()) {
		LOG("BufferStageT<Gfx>::LoadShader: error: no shader given");
		return false;
	}
	
	if (!is_path) {
		if (!LoadBuiltinShader(shader_type, str)) {
			LOG("BufferStageT<Gfx>::LoadShader: error: shader loading failed from '" + str + "'");
			return false;
		}
	}
	else {
		if (!LoadShaderFile(shader_type, str, library_paths)) {
			LOG("BufferStageT<Gfx>::LoadShader: error: shader loading failed from '" + str + "'");
			return false;
		}
	}
	
	return true;
}

/*template <class Gfx>
bool BufferStageT<Gfx>::LoadStereoShader(String shdr_vtx_path, String shdr_frag_path) {
	if (!LoadShaderFile(stereo_rt, GVar::FRAGMENT_SHADER, shdr_frag_path, "")) {
		LOG("BufferStageT<Gfx>::LoadStereoShader: error: shader loading failed from '" + shdr_frag_path + "'");
		return false;
	}
	if (!LoadShaderFile(stereo_rt, GVar::VERTEX_SHADER, shdr_vtx_path, "")) {
		LOG("BufferStageT<Gfx>::LoadStereoShader: error: shader loading failed from '" + shdr_vtx_path + "'");
		return false;
	}
	return true;
}*/

template <class Gfx>
bool BufferStageT<Gfx>::LoadBuiltinShader(GVar::ShaderType shader_type, String id) {
	int i = SoftShaderLibrary::GetMap(shader_type).Find(id);
	if (i < 0) {
		SetError("could not find shader");
		return false;
	}
	
	soft[shader_type] = SoftShaderLibrary::GetMap(shader_type)[i]();
	
	return true;
}

template <class Gfx>
void BufferStageT<Gfx>::MakeFrameQuad() {
	// essentially same as glRectf(-1.0, -1.0, 1.0, 1.0);
	Mesh m;
	m.vertices.SetCount(4);
	Vertex& tl = m.vertices[0];
	Vertex& tr = m.vertices[1];
	Vertex& br = m.vertices[2];
	Vertex& bl = m.vertices[3];
	tl.SetPosTex(vec3(-1, +1, 0), vec2(0,+1));
	tr.SetPosTex(vec3(+1, +1, 0), vec2(+1,+1));
	br.SetPosTex(vec3(+1, -1, 0), vec2(+1,0));
	bl.SetPosTex(vec3(-1, -1, 0), vec2(0,0));
	m.indices << 0 << 2 << 1; // top-right triangle CCW
	m.indices << 0 << 3 << 2; // bottom-left triangle CCW
	
	DataObject& o = data.AddObject();
	o.Refresh(m);
}

template <class Gfx>
void BufferStageT<Gfx>::Process(const RealtimeSourceConfig& cfg) {
	ASSERT(rt.prog);
	if (rt.prog == 0)
		return;
	
	Gfx::BindProgramPipeline(rt.pipeline);
	Gfx::UseProgram(rt.prog);
	if (!rt.is_searched_vars)
		FindVariables();

	int bi = NewWriteBuffer();
	
	if (!fb.is_win_fbo) {
		ASSERT(fb.frame_buf[bi]);
	    Gfx::BindFramebuffer(fb.frame_buf[bi]);
	    Gfx::DrawBuffers(GVar::COLOR0_EXT);
	}
	
	SetVars(rt.prog, cfg);

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
		else if (!user_data && data.objects.IsEmpty()) {
			for(int i = 0; i < quad_count; i++)
				MakeFrameQuad();
		}
		//}
		
		// render VBA from state
		Gfx::BeginRender();
		for (DataObject& o : data.objects) {
			if (!o.is_visible)
				continue;
			SetVars(data, rt.prog, o);
			o.Paint(data);
		}
		Gfx::EndRender();
	}
	else if (user_data) {
		Gfx::BeginRender();
		for (DataObject& o : user_data->objects) {
			if (!o.is_visible)
				continue;
			SetVars(*user_data, rt.prog, o);
			o.Paint(*user_data);
		}
		Gfx::EndRender();
	}
	
	Gfx::UnbindProgramPipeline();
	
	
	EnableGfxAccelDebugMessages(1);
	
	//ASSERT(fb.is_win_fbo == (fb.frame_buf[bi] == 0));
	//if (fb.frame_buf[bi]) {
	if (!fb.is_win_fbo) {
		// backup render target
	    //Gfx::DrawBuffer(GL_FRONT);
	    
	    // Some components (e.g. audio) needs to read the framebuffer
	    if (fb.is_read_fb_output)
			UseRenderedFramebuffer();
		
	    Gfx::BindFramebufferDefault();
	}
	
	EnableGfxAccelDebugMessages(0);
	
}

template <class Gfx>
void BufferStageT<Gfx>::UseRenderedFramebuffer() {
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
bool BufferStageT<Gfx>::SetLoopback(String loopback_str) {
	TODO
	#if 0
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
	#endif
}

template <class Gfx>
bool BufferStageT<Gfx>::InitializeTexture(Size sz, int channels, Sample sample, const byte* data, int len) {
	RTLOG("InitializeTexture: " << sz.ToString() << ", " << HexStr((void*)data) << ", " << len);
	
	UpdateTexBuffers();
	
	ReadTexture(sz, channels, sample, data, len);
	
	initialized = true;
	return true;
}

template <class Gfx>
bool BufferStageT<Gfx>::InitializeCubemap(Size sz, int channels, Sample sample, const Vector<byte>& d0, const Vector<byte>& d1, const Vector<byte>& d2, const Vector<byte>& d3, const Vector<byte>& d4, const Vector<byte>& d5) {
	RTLOG("InitializeCubemap: " << sz.ToString());
	fb.is_cubemap = true;
	
	UpdateTexBuffers();
	
	ReadCubemap(sz, channels, d0, d1, d2, d3, d4, d5);
	
	initialized = true;
	return true;
}

template <class Gfx>
bool BufferStageT<Gfx>::InitializeVolume(Size3 sz, int channels, Sample sample, const Vector<byte>& data) {
	RTLOG("InitializeVolume: " << sz.ToString() << ", " << data.GetCount());
	fb.size = Size(sz.cx, sz.cy);
	fb.depth = sz.cz;
	fb.sample = sample;
	ASSERT(sz.cx > 0 && sz.cy > 0);
	ASSERT(sz.cz > 0);
	
	UpdateTexBuffers();
	
	ReadTexture(sz, channels, sample, data);
	
	initialized = true;
	return true;
}

template <class Gfx>
void BufferStageT<Gfx>::ReadTexture(Size sz, int channels, Sample sample, const byte* data, int len) {
	GVar::TextureType type = GVar::TEXTYPE_2D;
	
	int exp_len = sz.cx * sz.cy * channels * GVar::GetSampleSize(sample);
	ASSERT(len == exp_len);
	if (len != exp_len)
		return;
	
	auto& color_buf = fb.color_buf[0];
	ASSERT(color_buf);
	//ASSERT(sz == fb_size);
	//ASSERT(s.GetSize() == len);
	
	Gfx::BindTextureRW(type, color_buf);
	Gfx::TexParameteri(type, GVar::FILTER_LINEAR, GVar::WRAP_REPEAT);
	Gfx::SetTexture(type, sz, sample, channels, data);
	
	TexFlags(type, fb.filter, fb.wrap);
}

template <class Gfx>
void BufferStageT<Gfx>::ReadTexture(Size3 sz, int channels, Sample sample, const Vector<byte>& data) {
	GVar::TextureType type = GVar::TEXTYPE_3D;
	
	ASSERT(fb.size.cx == sz.cx && fb.size.cy == sz.cy);
	auto& color_buf = fb.color_buf[0];
	ASSERT(color_buf);
	//int intl_fmt = GetGfxChannelFormat(channels);
	
	Gfx::BindTextureRW(type, color_buf);
	Gfx::TexParameteri(type, GVar::FILTER_LINEAR, GVar::WRAP_REPEAT);
	Gfx::SetTexture(type, sz, sample, channels, data.Begin());
	
	TexFlags(type, fb.filter, fb.wrap);
}


template <class Gfx>
void BufferStageT<Gfx>::ReadCubemap(Size sz, int channels, const Vector<byte>& d0, const Vector<byte>& d1, const Vector<byte>& d2, const Vector<byte>& d3, const Vector<byte>& d4, const Vector<byte>& d5) {
	GVar::TextureType type = GVar::TEXTYPE_CUBE_MAP;
	auto& tex			= fb.color_buf[0];
	//int ch_code		= GetGfxChannelFormat(channels);
	
	Gfx::BindTextureRW(type, tex);
	
	ASSERT(tex);
	
	for(int i = 0; i < 6; i++) {
		GVar::TextureType tex_type = (GVar::TextureType)(GVar::TEXTYPE_CUBE_MAP_SIDE_0 + i);
		const Vector<byte>* data = 0;
		switch (i) {
			case 0: data = &d0; break;
			case 1: data = &d1; break;
			case 2: data = &d2; break;
			case 3: data = &d3; break;
			case 4: data = &d4; break;
			case 5: data = &d5; break;
		}
		Gfx::SetTexture(
					tex_type,
					sz,
					GVar::Sample::SAMPLE_U8,
					channels,
					data->Begin());
	}
	
	TexFlags(type, fb.filter, fb.wrap);
	
	//GLenum err = Gfx::GetError();
	//if (err != GL_NO_ERROR)
	//	OnError("ReadCubemap", "Gfx error " + HexStr(err));
	
	Gfx::UnbindTexture(type);
}

template <class Gfx>
void BufferStageT<Gfx>::RefreshPipeline() {
	DLOG("BufferT::RefreshPipeline begin");
	
	CreatePipeline();
	
	UpdateTexBuffers();
	
	//if (!CheckInputTextures())
	//	return;
	
	DLOG("BufferT::RefreshPipeline end");
}

template <class Gfx>
void BufferStageT<Gfx>::ClearPipeline() {
	if (rt.pipeline) {
		Gfx::DeleteProgramPipeline(rt.pipeline);
	}
}

template <class Gfx>
void BufferStageT<Gfx>::CreatePipeline() {
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
void BufferStageT<Gfx>::UpdateTexBuffers() {
	if (!fb.is_win_fbo) {
		ASSERT(fb.channels > 0);
		ASSERT(fb.size.cx > 0 && fb.size.cy > 0);
		
		this->BaseUpdateTexBuffers(fb);
		
		ClearTex();
		
		CreateTex(true, true);
		
	}
}

template <class Gfx>
void BufferStageT<Gfx>::ClearTex() {
	for(int bi = 0; bi < 2; bi++) {
		auto& color_buf = fb.color_buf[bi];
		auto& depth_buf = fb.depth_buf[bi];
		auto& frame_buf = fb.frame_buf[bi];
		
		if (color_buf != 0) {
			Gfx::DeleteTexture(color_buf);
			color_buf = Null;
		}
		if (depth_buf != 0) {
			Gfx::DeleteRenderbuffer(depth_buf);
			depth_buf = Null;
		}
		if (frame_buf != 0) {
			Gfx::DeleteFramebuffer(frame_buf);
			frame_buf = Null;
		}
	}
}

template <class Gfx>
void BufferStageT<Gfx>::CreateTex(bool create_depth, bool create_fbo) {
	EnableGfxAccelDebugMessages(1);
	
	int buf_count = 1;
	if (fb.is_doublebuf)
		buf_count++;
	
	Size sz = fb.size;
	ASSERT(sz.cx > 0 && sz.cy > 0);
	
	GVar::TextureType type = GVar::TEXTYPE_2D;
	if (fb.depth > 0) {
		type = GVar::TEXTYPE_3D;
		create_depth = create_fbo = false;
	}
	else if (fb.is_cubemap) {
		type = GVar::TEXTYPE_CUBE_MAP;
		create_depth = create_fbo = false;
	}
	/*else if (fb.is_audio) {
		create_depth = create_fbo = false;
	}*/
	
	for(int bi = 0; bi < buf_count; bi++) {
		auto& color_buf = fb.color_buf[bi];
		auto& depth_buf = fb.depth_buf[bi];
		auto& frame_buf = fb.frame_buf[bi];
		ASSERT(color_buf == 0);
		
		// color buffer
		Gfx::ActiveTexture(CHANNEL_NONE);
		Gfx::GenTexture(color_buf);
		Gfx::BindTextureRW(type, color_buf);
		Gfx::ReserveTexture(type, fb);
		Gfx::UnbindTexture(type);
		Gfx::DeactivateTexture();
		
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
			
			TexFlags(type, fb.filter, fb.wrap);
			
			// combine FBO to color buffer
			Gfx::FramebufferTexture2D(TEXTYPE_NONE, color_buf); // TEXTYPE_NONE == color attachment 0
			
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
void BufferStageT<Gfx>::FindVariables() {
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
int BufferStageT<Gfx>::NewWriteBuffer() {
	if (fb.is_doublebuf)
		fb.buf_i = (fb.buf_i + 1) % 2;
	return fb.buf_i;
}

template <class Gfx>
void BufferStageT<Gfx>::SetVars(DataState& d, NativeProgram& gl_prog, const DataObject& o) {
	for(int i = 0; i < GVar::VAR_COUNT; i++)
		if (GVar::is_obj_var[i] && rt.var_idx[i] >= 0)
			SetVar(d, i, gl_prog, o);
}

template <class Gfx>
void BufferStageT<Gfx>::SetVar(DataState& data, int var, NativeProgram& gl_prog, const DataObject& o) {
	using namespace GVar;
	
	auto& env = buf->env;
	auto& ctx = buf->ctx;
	
	int uindex = rt.var_idx[var];
	ASSERT(uindex >= 0);
	if (var == VAR_AUDIOTIME) {
		//LOG("VAR_AUDIOTIME: " << ctx.time_total);
		Gfx::Uniform1f(uindex, (float)ctx.time_total);
	}
	else if (var == VAR_MODELCOLOR) {
		Gfx::Uniform4f(uindex, o.color[0], o.color[1], o.color[2], o.color[3]);
	}
	else if (var == VAR_VIEW) {
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
		if (tex_i >= 0) {
			auto& tex = data.textures[tex_i];
			Gfx::ActiveTexture(tex_ch);
			Gfx::BindTextureRO(GVar::TEXTYPE_2D, tex);
			Gfx::Uniform1i(uindex, tex_ch);
			Gfx::DeactivateTexture();
		}
	}
	else if (var >= VAR_COMPAT_CHANNEL0 && var <= VAR_COMPAT_CHANNEL1) {
		TODO
	}
	else if (var == VAR_COMPAT_CHANNELRESOLUTION) {
		TODO
	}
	else {
		TODO
	}
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
void BufferStageT<Gfx>::SetVars(NativeProgram& gl_prog, const RealtimeSourceConfig& cfg) {
	for(int i = 0; i < GVar::VAR_COUNT; i++)
		if (!GVar::is_obj_var[i] && rt.var_idx[i] >= 0)
			SetVar(i, gl_prog, cfg);
}

template <class Gfx>
void BufferStageT<Gfx>::SetVar(int var, NativeProgram& gl_prog, const RealtimeSourceConfig& cfg) {
	using namespace GVar;
	int uindex = rt.var_idx[var];
	ASSERT(uindex >= 0);
	if (uindex < 0)
		return;
	
	//RTLOG("BufferT<Gfx>::SetVar: " << GVar::names[var]);
	
	EnvStateRef& env = buf->env;
	ContextState& ctx = buf->ctx;
	
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
		//Gfx::UseProgram(gl_prog);
		/*float f[3];
		f[0] = (float)fb.size.cx;
		f[1] = (float)fb.size.cy;
		f[2] = 1.0f;
		Gfx::Uniform1fv(uindex, 3, f);*/
		//Gfx::ProgramUniform3f(gl_prog, uindex, (float)fb.size.cx, (float)fb.size.cy, 1.0f);
		Gfx::Uniform3f(uindex, (float)fb.size.cx, (float)fb.size.cy, 1.0f);
	}
	
	else if (var == VAR_COMPAT_TIME) {
		//RTLOG("SetVar: " << time_total);
		Gfx::Uniform1f(uindex, (float)ctx.time_total);
	}
	
	else if (var == VAR_COMPAT_TIMEDELTA) {
		ASSERT(ctx.frame_time != 0.0);
		Gfx::Uniform1f(uindex, (float)ctx.frame_time);
		//float f = (float)ctx.frame_time;
		//Gfx::Uniform1fv(uindex, 1, &f);
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
				(float)mouse_drag.x,
				(float)mouse_drag.y,
				(float)mouse_click.x,
				(float)mouse_click.y);
			#endif
		}
	}
	
	else if (var == VAR_COMPAT_DATE) {
		double sec = ((int)ctx.time.hour * 60 + (int)ctx.time.minute) * 60 + (int)ctx.time.second;
		sec += ctx.time_us;
		Gfx::Uniform4f(uindex, (float)ctx.time.year, (float)ctx.time.month, (float)ctx.time.day, (float)sec);
	}
	
	else if (var == VAR_COMPAT_SAMPLERATE) {
		ASSERT(ctx.sample_rate > 0);
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
		NativeColorBufferConstRef tex = GetInputTex(ch);
		// may fail in early program: ASSERT(tex);
		if (tex) {
			//typename Gfx::NativeColorBufferConstRef clr = Gfx::GetFrameBufferColor(*tex, TEXTYPE_NONE);
			Gfx::ActiveTexture(tex_ch);
			Gfx::BindTextureRO(GetTexType(ch), tex);
			Gfx::Uniform1i(uindex, tex_ch);
			Gfx::DeactivateTexture();
		}
	}
	
	else if (var >= VAR_BUFFERSTAGE0_COLOR && var <= VAR_BUFFERSTAGE4_COLOR) {
		int ch = var - VAR_BUFFERSTAGE0_COLOR;
		int tex_ch = BUFFERSTAGE_OFFSET + ch;
		
		if (ch < buf->stages.GetCount()) {
			auto& stage = buf->stages[ch];
			NativeColorBufferConstRef tex = stage.fb.color_buf[stage.fb.buf_i];
			// may fail in early program: ASSERT(tex);
			if (tex) {
				//typename Gfx::NativeColorBufferConstRef clr = Gfx::GetFrameBufferColor(*tex, TEXTYPE_NONE);
				Gfx::ActiveTexture(tex_ch);
				Gfx::BindTextureRO(GetTexType(ch), tex);
				Gfx::Uniform1i(uindex, tex_ch);
				Gfx::DeactivateTexture();
			}
		}
	}
	
	else if (var == VAR_COMPAT_FRAMERATE) {
		ASSERT(fb.fps > 0);
		Gfx::Uniform1f(uindex, (float)fb.fps);
	}
	
	else if (var == VAR_COMPAT_CHANNELTIME) {
		float values[INPUT_COUNT];
		for(int j = 0; j < INPUT_COUNT; j++) {
			InputState& in = rt.inputs[j];
			values[j] = in.buf ? in.buf->ctx.time_total : 0;
		}
		//Gfx::Uniform1fv(uindex, 4, values);
		Gfx::Uniform4f(uindex, (float)values[0], (float)values[1], (float)values[2], (float)values[3]);
	}
	
	else if (var == VAR_COMPAT_CHANNELRESOLUTION) {
		float values[3*4] = {0,0,0, 0,0,0, 0,0,0, 0,0,0};
		for(int j = 0; j < INPUT_COUNT; j++) {
			InputState& in = rt.inputs[j];
			const Buffer* in_buf = in.buf;
			if (in_buf){
				int off = j * 3;
				auto& in_fb = in_buf->GetFramebuffer();
				values[off + 0] = (float)in_fb.size.cx;
				values[off + 1] = (float)in_fb.size.cy;
				values[off + 2] = (float)in_fb.depth;
			}
		}
		Gfx::Uniform3fv(uindex, 4, values);
	}
	
	else if (var == VAR_COMPAT_BLOCKOFFSET) {
		Gfx::Uniform1f(uindex, (float)ctx.block_offset);
	}
	else {
		ASSERT_(false, "Invalid variable");
	}
}

template <class Gfx>
TNG NativeColorBufferConstRef BufferStageT<Gfx>::GetInputTex(int input_i) const {
	const char* fn_name = "GetInputTex";
	//DLOG("BufferT::GetInputTex");
	if (input_i < 0 || input_i >= GVar::INPUT_COUNT)
		return 0;
	
	const InputState& in = rt.inputs[input_i];
	if (in.buf == 0) {
		RTLOG("GetInputTex: warning: no input fbo buffer");
		return 0;
	}
	
	TODO
	/*const Buffer* in_comp = in.buf;
	if (!in_comp)
		return 0;
	
	NativeColorBufferConstRef tex = in_comp->GetOutputTexture(in_comp == this->buf);
	ASSERT(tex);
	
	return tex;*/
}

template <class Gfx>
GVar::TextureType BufferStageT<Gfx>::GetTexType(int input_i) const {
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
bool BufferStageT<Gfx>::CompilePrograms() {
	/*const char* fn_name = "CompilePrograms";
	for(int i = 0; i < PROG_COUNT; i++) {
		if (i == FRAGMENT_SHADER && !CompileFragmentShader())
			return false;
		if (i == VERTEX_SHADER && !CompileVertexShader())
			return false;
	}*/
	auto& ctx = buf->ctx;
	
	int r;
	if ((r = BuiltinShader()) != 0) {
		//breaks simple quad rendering: use_user_data = true;
		return r > 0;
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
			SetError(comp.GetError());
			return false;
		}
	}
	
	if (!linker.Link(rt)) {
		SetError(linker.GetError());
		return false;
	}
	
	return true;
}

template <class Gfx>
TNG NativeColorBufferConstRef BufferStageT<Gfx>::GetOutputTexture(bool reading_self) const {
	ASSERT(!reading_self || fb.is_doublebuf);
	int buf_i = fb.buf_i;
	
	if (reading_self)
		buf_i = (buf_i + 1) % 2;
	
	if (fb.color_buf[buf_i] == 0) {DLOG("BufferT::GetOutputTexture failed");}
	ASSERT(fb.color_buf[buf_i]);
	return fb.color_buf[buf_i];
}

template <class Gfx>
void BufferStageT<Gfx>::TexFlags(GVar::TextureType type, GVar::Filter filter, GVar::Wrap repeat) {
	Gfx::TexParameteri(type, filter, repeat);
}

template <class Gfx>
bool BufferStageT<Gfx>::LoadInputLink(int in_id, const PacketValue& v) {
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
	else {
		TODO
	}
	// if data is InternalPacketData call other LoadInputLink
	TODO
	#if 0
	if (in_id >= 0 && in_id < GVar::INPUT_COUNT) {
		//LOG("LoadInputLink: " << name << " #" << in_id);
		
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
		else {
			ASSERT(in.type != GVar::VOLUME_INPUT);
			in.type = GVar::TEXTURE_INPUT;
		}
		
		return true;
	}
	#endif
	
	
	RTLOG("LoadInputLink: error: unexpected data");
	return false;
}

template <class Gfx>
bool BufferStageT<Gfx>::LoadInputLink(int in_id, const InternalPacketData& v) {
	if (in_id >= 0 && in_id < GVar::INPUT_COUNT) {
		//LOG("LoadInputLink: " << name << " #" << in_id);
		GfxBuffer* gbuf = (GfxBuffer*)v.ptr;
		Buffer* buf = CastPtr<Buffer>(gbuf);
		if (!buf) {
			ASSERT_(0, "Buffer's Gfx type differs");
			return false;
		}
		ASSERT(v.ptr);
		InputState& in = rt.inputs[in_id];
		in.id = in_id;
		in.buf = buf;
		
		//auto& fb = buf->fb;
		ASSERT(fb.size.cx > 0 && fb.size.cy > 0);
		
		if (fb.is_cubemap)
			in.type = GVar::CUBEMAP_INPUT;
		else if (fb.depth > 0)
			in.type = GVar::VOLUME_INPUT;
		else {
			ASSERT(in.type != GVar::VOLUME_INPUT);
			in.type = GVar::TEXTURE_INPUT;
		}
		
		return true;
	}
	
	RTLOG("LoadInputLink: error: unexpected data");
	return false;
}

template <class Gfx>
void BufferStageT<Gfx>::SetInputVolume(int in_id) {
	ASSERT(in_id >= 0 && in_id < GVar::INPUT_COUNT);
	InputState& in = rt.inputs[in_id];
	in.type = GVar::VOLUME_INPUT;
}

template <class Gfx>
void BufferStageT<Gfx>::SetInputCubemap(int in_id) {
	ASSERT(in_id >= 0 && in_id < GVar::INPUT_COUNT);
	InputState& in = rt.inputs[in_id];
	in.type = GVar::CUBEMAP_INPUT;
}

template <class Gfx>
int BufferStageT<Gfx>::BuiltinShader() {return 0;}

template <class Gfx>
template <int>
int BufferStageT<Gfx>::BuiltinShaderT() {
	bool succ = false;
	if (!rt.pipeline)
		rt.pipeline.Create();
	int shdr_count = 0;
	for(int i = 0; i < GVar::SHADERTYPE_COUNT; i++) {
		if (soft[i]) {
			shdr_count++;
			GVar::ShaderType t = (GVar::ShaderType)i;
			auto& s = rt.shaders[i];
			ASSERT(!s.shader);
			if (!Gfx::CreateShader((GVar::ShaderType)i, s.shader)) {
				SetError("could not create shader (at BufferT<Gfx>::BuiltinShaderT)");
				return -1;
			}
			ASSERT(s.shader);
			if (!s.shader) continue;
			//s.shader.Create(t);
			s.shader->SetShaderBase(*soft[i]);
			s.enabled = true;
			if (!rt.prog) {
				rt.prog.Create();
			}
			rt.prog.Attach(*s.shader);
			rt.pipeline.Use(rt.prog, 1 << i);
			if (i == GVar::FRAGMENT_SHADER)
				succ = true;
		}
	}
	if (!succ) {
		if (shdr_count == 0)
			SetError("RuntimeState got no shaders");
		else
			SetError("RuntimeState got no soft fragment shader");
	}
	
	return succ ? 1 : -1;
}

#ifdef flagSDL2
template <>
int BufferStageT<SdlSwGfx>::BuiltinShader() {
	return BuiltinShaderT<0>();
}
#endif

#ifdef flagPOSIX
template <>
int BufferStageT<X11SwGfx>::BuiltinShader() {
	return BuiltinShaderT<0>();
}
#endif






GFX3D_EXCPLICIT_INITIALIZE_CLASS(BufferStageT)


NAMESPACE_PARALLEL_END
