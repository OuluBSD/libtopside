#include "IGraphics.h"


NAMESPACE_PARALLEL_BEGIN

extern const char* stereo_vtx_shader;
extern const char* stereo_frag_shader;

template <class Gfx>
void BufferStageT<Gfx>::SetStereo(int stereo_id) {
	if (stereo_id == 0)
		fb.is_stereo_left = true;
	else if (stereo_id == 1)
		fb.is_stereo_right = true;
}

template <class Gfx>
void BufferStageT<Gfx>::SetStereoLens() {
	fb.is_affine = true;
	fb.is_stereo_lenses = true;
	quad_count = 2;
	
	ShaderConf& vtx_conf = shdr_confs[GVar::VERTEX_SHADER];
	ShaderConf& frag_conf = shdr_confs[GVar::FRAGMENT_SHADER];
	if (Gfx::Type == GVar::OGL) {
		vtx_conf.is_content = true;
		vtx_conf.str = stereo_vtx_shader;
		frag_conf.is_content = true;
		frag_conf.str = stereo_frag_shader;
	}
	else if (Gfx::Type == GVar::SW) {
		vtx_conf.str = "stereo_vertex";
		frag_conf.str = "stereo_fragment";
	}
	else {
		TODO
	}
	
}

template <class Gfx>
void BufferStageT<Gfx>::SetDataState(DataState* s) {
	data = s;
	pipeline = 0;
	
	if (data && data->pipelines.GetCount() == 1) {
		if (data->pipelines.GetCount() == 1) {
			pipeline_str = data->dictionary[data->pipelines.GetKey(0)];
			pipeline = &data->pipelines[0];
		}
		else {
			int id = data->dictionary.Find(pipeline_str);
			if (id >= 0) {
				int i = data->pipelines.Find(id);
				if (i >= 0)
					pipeline = &data->pipelines[i];
			}
		}
		/*if (pipeline->programs.GetCount() == 1) {
			prog = &pipeline->programs[0];
			
			if (prog->pending_compilation) {
				Compile();
			}
		}*/
		
	}
	if (pipeline && buf->mode == Buffer::PENDING_PACKET) {
		for (ProgramState& prog : pipeline->programs.GetValues()) {
			if (prog.pending_compilation && !prog.failed) {
				prog.pending_compilation = false;
				
				if (!prog.Compile(GetCompilerArgs())) {
					LOG("BufferStageT::SetDataState: error: shader compiling failed: " << prog.GetError());
					prog.failed = true;
					data = 0;
					pipeline = 0;
					return;
				}
			}
		}
		pipeline->Realize();
	}
	
	CompileJIT();
}

template <class Gfx>
void BufferStageT<Gfx>::CompileJIT() {
	if (pipeline) {
		for (ProgramState& prog : pipeline->programs.GetValues()) {
			if (prog.pending_compilation) {
				prog.pending_compilation = false;
				prog.Compile(GetCompilerArgs());
			}
		}
		pipeline->Realize();
	}
}

template <class Gfx>
GfxCompilerArgs BufferStageT<Gfx>::GetCompilerArgs() const {
	GfxCompilerArgs args;
	args.is_affine = fb.is_affine;
	args.is_audio = fb.is_audio;
	return args;
}

template <class Gfx>
bool BufferStageT<Gfx>::Initialize(int id, AtomBase& a, const Script::WorldState& ws) {
	ShaderConf& lib_conf = shdr_confs[GVar::SHADERTYPE_COUNT];
	lib_conf.str = ws.Get(".library");
	lib_conf.is_path = true;
	
	if (!quad_count)
		quad_count = ws.GetInt(".s" + IntStr(id) + ".quad.count", 1);
	
	// Program string is a simplified way to set shader configuration
	String program_str = ws.Get(".program");
	if (buf->stages.GetCount() == 1 && program_str.GetCount()) {
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
			if (!conf.str.IsEmpty())
				continue;
			
			int tries = (id == 0 || fb.is_stereo_left || fb.is_stereo_right) ? 2 : 1;
			
			for(int j = 0; j < tries; j++) {
				String prefix = "." + (j == 0 ? ("s" + IntStr(id) + ".") : String()) + "shader." + type + ".";
				
				String path = ws.Get(prefix + "path");
				String name = ws.Get(prefix + "name");
				//LOG(prefix + "path");
				
				if (name.GetCount())
					name += extension;
				
				/*if (path.IsEmpty() && name.IsEmpty() && i == GL::FRAGMENT_SHADER && j == tries-1) {
					LOG("BufferStageT<Gfx>::Initialize: error: no fragment shader given (for stage " << id << ")");
					return false;
				}*/
				
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
				continue;
			
			TODO
			/*if (value == "volume")
				prog->SetInputVolume(i);
			else if (value == "cubemap")
				prog->SetInputCubemap(i);
			else
				TODO*/
		}
	}
	
	String loopback = ws.Get(".loopback");
	if (loopback.GetCount() && id == 0) {
		if (!SetLoopback(loopback)) {
			LOG("GfxBufferStageT<Gfx>::Initialize: error: assigning loopback failed");
			return false;
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
			fb.size = Size(TS::default_width,TS::default_height);
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
	
	if (fb.is_stereo_lenses) {
		float horz_sep = 0.063f;
		float vpos = 0.025953f;
		//float warp_adj = 1.0f;
		viewport_scale = vec2(fb.size.cx, fb.size.cy);
		left_lens_center  = vec2(viewport_scale[0] * (1 - horz_sep)/2.0f, viewport_scale[1] * (0.5 + vpos));
		right_lens_center = vec2(viewport_scale[0] * (1 + horz_sep)/2.0f, viewport_scale[1] * (0.5 + vpos));
		//float ws = (left_lens_center[0] > right_lens_center[0]) ? left_lens_center[0] : right_lens_center[0];
		warp_scale = fb.size.cx / 2; // ws * warp_adj
		hmd_warp_param = vec4(0,0,0,1);
		aberr = vec3(1,1,1);
	}
	
	for(int i = 0; i < GVar::SHADERTYPE_COUNT; i++) {
		ShaderConf& conf = shdr_confs[i];
		
		if (conf.str.GetCount()) {
			TODO
			//if (!prog->LoadShader((GVar::ShaderType)i, conf.str, conf.is_path, conf.is_content, lib_conf.str))
			//	return false;
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
void BufferStageT<Gfx>::MakeFrameQuad() {
	// essentially same as glRectf(-1.0, -1.0, 1.0, 1.0);
	Mesh m;
	m.vertices.SetCount(4);
	Vertex& tl = m.vertices[0];
	Vertex& tr = m.vertices[1];
	Vertex& br = m.vertices[2];
	Vertex& bl = m.vertices[3];
	float z = 1;
	tl.SetPosTex(vec3(-1, +1, z), vec2(0,+1));
	tr.SetPosTex(vec3(+1, +1, z), vec2(+1,+1));
	br.SetPosTex(vec3(+1, -1, z), vec2(+1,0));
	bl.SetPosTex(vec3(-1, -1, z), vec2(0,0));
	m.indices << 0 << 2 << 1; // top-right triangle CCW
	m.indices << 0 << 3 << 2; // bottom-left triangle CCW
	
	ModelState& mdl = LocalState().models.IsEmpty() ? LocalState().AddModelT() : LocalState().models.Top();
	DataObject& o = mdl.AddObject();
	o.Refresh(m);
}

template <class Gfx>
void BufferStageT<Gfx>::Process(const RealtimeSourceConfig& cfg) {
	if (!data)
		return;
	ASSERT(this->pipeline);
	auto& pipeline = *this->pipeline;
	
	ASSERT(pipeline.native);
	if (pipeline.native == 0)
		return;
	
	Gfx::BindProgramPipeline(pipeline.native);
	
	int bi = NewWriteBuffer();
	
	if (!fb.is_win_fbo) {
		ASSERT(fb.frame_buf[bi]);
	    Gfx::BindFramebuffer(fb.frame_buf[bi]);
	    Gfx::DrawBuffers(GVar::COLOR0_EXT);
	}
	
	RendVer(OnProcess);
	
	Gfx::Clear(GVar::COLOR_BUFFER);
	Gfx::Clear(GVar::DEPTH_BUFFER);
	//Gfx::Clear(GVar::STENCIL_BUFFER);
	
	if (data_writable) {
		if (0)
			Gfx::RenderScreenRect();
		else if (data->models.IsEmpty()) {
			for(int i = 0; i < quad_count; i++)
				MakeFrameQuad();
		}
	}
	
	// render VBA from state
	Gfx::BeginRender();
	
	//if (ctx.frames > 0)
	{
		ProgramState* prev_prog = 0;
		for (ModelState& m : data->models.GetValues()) {
			ASSERT(m.prog >= 0);
			if (m.prog < 0)
				continue;
			ProgramState& prog = pipeline.programs.Get(m.prog);
			
			Gfx::UseProgram(prog.native);
			if (!prog.is_searched_vars)
				prog.FindVariables();
			
			if (prev_prog != &prog) {
				prog.SetVars(buf->ctx, buf->env, cfg);
				prev_prog = &prog;
			}
			
			for (DataObject& o : m.objects) {
				if (!o.is_visible)
					continue;
				
				
				SetVars(prog, cfg, o);
				
				Gfx::BeginRenderObject();
				
				typename ProgramState::ViewTarget vtgt = ProgramState::VIEW_TARGET_MONO;
				if (fb.is_stereo_left)   vtgt = ProgramState::VIEW_TARGET_STEREO_LEFT;
				if (fb.is_stereo_right)  vtgt = ProgramState::VIEW_TARGET_STEREO_RIGHT;
				
				prog.SetVars(buf->ctx, m, o, vtgt);
				o.Paint(m);
				
				Gfx::EndRenderObject();
			}
		}
	}
	
	Gfx::EndRender();
	
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
	GVar::TextureMode type = GVar::TEXMODE_2D;
	
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
	GVar::TextureMode type = GVar::TEXMODE_3D;
	
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
	GVar::TextureMode type = GVar::TEXMODE_CUBE_MAP;
	auto& tex			= fb.color_buf[0];
	//int ch_code		= GetGfxChannelFormat(channels);
	
	Gfx::BindTextureRW(type, tex);
	
	ASSERT(tex);
	
	for(int i = 0; i < 6; i++) {
		GVar::TextureMode tex_type = (GVar::TextureMode)(GVar::TEXMODE_CUBE_MAP_SIDE_0 + i);
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
	ASSERT(pipeline);
	pipeline->Realize();
	UpdateTexBuffers();
}

template <class Gfx>
bool BufferStageT<Gfx>::Compile(ProgramState& prog) {
	prog.pending_compilation = false;
	return prog.Compile(GetCompilerArgs());
}

template <class Gfx>
void BufferStageT<Gfx>::UpdateTexBuffers() {
	if (!fb.is_win_fbo) {
		ASSERT(fb.channels > 0);
		ASSERT(fb.size.cx > 0 && fb.size.cy > 0);
		
		buf->BaseUpdateTexBuffers(fb);
		
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
	
	GVar::TextureMode type = GVar::TEXMODE_2D;
	if (fb.depth > 0) {
		type = GVar::TEXMODE_3D;
		create_depth = create_fbo = false;
	}
	else if (fb.is_cubemap) {
		type = GVar::TEXMODE_CUBE_MAP;
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
int BufferStageT<Gfx>::NewWriteBuffer() {
	if (fb.is_doublebuf)
		fb.buf_i = (fb.buf_i + 1) % 2;
	return fb.buf_i;
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
void BufferStageT<Gfx>::TexFlags(GVar::TextureMode type, GVar::Filter filter, GVar::Wrap repeat) {
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
		// if data is InternalPacketData call other LoadInputLink
		TODO
	}
	
	RTLOG("LoadInputLink: error: unexpected data");
	return false;
}

template <class Gfx>
bool BufferStageT<Gfx>::LoadInputLink(ProgramState& prog, int in_id, const InternalPacketData& v) {
	return prog.LoadInputLink(in_id, v);
}

template <class Gfx>
void BufferStageT<Gfx>::SetVars(ProgramState& prog, const RealtimeSourceConfig& cfg, const DataObject& o) {
	for(int i = 0; i < GVar::VAR_COUNT; i++)
		if (!GVar::is_obj_var[i] && prog.var_idx[i] >= 0)
			SetVar(prog, i, cfg, o);
}

template <class Gfx>
void BufferStageT<Gfx>::SetVar(ProgramState& prog, int var, const RealtimeSourceConfig& cfg, const DataObject& o) {
	using namespace GVar;
	int uindex = prog.var_idx[var];
	ASSERT(uindex >= 0);
	if (uindex < 0)
		return;
	
	if (var >= VAR_BUFFERSTAGE0_COLOR && var <= VAR_BUFFERSTAGE4_COLOR) {
		int ch = var - VAR_BUFFERSTAGE0_COLOR;
		int tex_ch = BUFFERSTAGE_OFFSET + ch;
		
		if (ch < buf->stages.GetCount()) {
			auto& stage = buf->stages[ch];
			NativeColorBufferConstRef tex = stage.fb.color_buf[stage.fb.buf_i];
			// may fail in early program: ASSERT(tex);
			if (tex) {
				//typename Gfx::NativeColorBufferConstRef clr = Gfx::GetFrameBufferColor(*tex, TEXTYPE_NONE);
				Gfx::ActiveTexture(tex_ch);
				Gfx::BindTextureRO(GVar::TEXMODE_2D, tex);
				Gfx::TexParameteri(GVar::TEXMODE_2D, GVar::FILTER_LINEAR, GVar::WRAP_REPEAT);
				Gfx::Uniform1i(uindex, tex_ch);
				Gfx::DeactivateTexture();
			}
		}
	}
	else if (var == VAR_COMPAT_FRAMERATE) {
		ASSERT(fb.fps > 0);
		Gfx::Uniform1f(uindex, (float)fb.fps);
	}
	else if (var == VAR_LENS_CENTER) {
		if (o.model.data[3][0] < 0)
			Gfx::Uniform2f(uindex, left_lens_center[0], left_lens_center[1]);
		else
			Gfx::Uniform2f(uindex, right_lens_center[0], right_lens_center[1]);
	}
	else if (var == VAR_VIEWPORT_SCALE) {
		Gfx::Uniform2f(uindex, viewport_scale[0], viewport_scale[1]);
	}
	else if (var == VAR_WARP_SCALE) {
		Gfx::Uniform1f(uindex, warp_scale);
	}
	else if (var == VAR_HMD_WARP_PARAM) {
		Gfx::Uniform4f(uindex, hmd_warp_param[0], hmd_warp_param[1], hmd_warp_param[2], hmd_warp_param[3]);
	}
	else if (var == VAR_ABERR) {
		Gfx::Uniform3f(uindex, aberr[0], aberr[1], aberr[2]);
	}
	else if (var == VAR_COMPAT_RESOLUTION) {
		// from fb.size
		ASSERT(fb.size.cx > 0 && fb.size.cy > 0);
		Gfx::Uniform3f(uindex, (float)fb.size.cx, (float)fb.size.cy, 1.0f);
	}
	else if (var == VAR_BRDF_SPEC) {
		if (brdf_img.IsEmpty()) {
			MakeSpecBRDF(brdf_img, 32);
			brdf_tex.Load(brdf_img);
		}
		//int ch = var - VAR_GLOBAL_BEGIN;
		int ch = 0;
		int tex_ch = GLOBAL_OFFSET + ch;
		
		// may fail in early program: ASSERT(brdf_tex.tex);
		if (brdf_tex.tex) {
			Gfx::ActiveTexture(tex_ch);
			Gfx::BindTextureRO(GVar::TEXMODE_2D, brdf_tex.tex);
			Gfx::TexParameteri(GVar::TEXMODE_2D, GVar::FILTER_LINEAR, GVar::WRAP_REPEAT);
			Gfx::Uniform1i(uindex, tex_ch);
			Gfx::DeactivateTexture();
		}
	}
}






const char* stereo_vtx_shader = R"SH4D3R(
void mainVertex(out vec4 pos_out)
{
	vec3 pos = iPos.xyz;
	pos_out = normalize(iModel * vec4(pos, 1.0));
}

)SH4D3R";







const char* stereo_frag_shader = R"SH4D3R(
void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
    // output_loc is the fragment location on screen from [0,1]x[0,1]
    vec2 output_loc = vec2(vTexCoord.s, vTexCoord.t);
    
    // Compute fragment location in lens-centered coordinates at world scale
    vec2 r = output_loc * iViewportScale - iLensCenter;
    
    // scale for distortion model
    // distortion model has r=1 being the largest circle inscribed (e.g. eye_w/2)
    r /= iWarpScale;
    
    // |r|**2
    float r_mag = length(r);
    
    // offset for which fragment is sourced
    vec2 r_displaced = r * (iHmdWarpParam[3] + iHmdWarpParam.z * r_mag +
    iHmdWarpParam.y * r_mag * r_mag +
    iHmdWarpParam.x * r_mag * r_mag * r_mag);
    
    // back to world scale
    r_displaced *= iWarpScale;
    
    // back to viewport co-ord
    vec2 tc_r = (iLensCenter + iAberr.r * r_displaced) / iViewportScale;
    vec2 tc_g = (iLensCenter + iAberr.g * r_displaced) / iViewportScale;
    vec2 tc_b = (iLensCenter + iAberr.b * r_displaced) / iViewportScale;

    float red   = texture(iDiffuse, tc_r).r;
    float green = texture(iDiffuse, tc_g).g;
    float blue  = texture(iDiffuse, tc_b).b;
    
    // Black edges off the texture
    fragColor = ((tc_g.x < 0.0) || (tc_g.x > 1.0) || (tc_g.y < 0.0) || (tc_g.y > 1.0)) ? vec4(0.0, 0.0, 0.0, 1.0) : vec4(red, green, blue, 1.0);
    
    // Simple output
    //fragColor = vec4(texture(iDiffuse, vTexCoord).rgb, 1);
}
)SH4D3R";


GFX3D_EXCPLICIT_INITIALIZE_CLASS(BufferStageT)


NAMESPACE_PARALLEL_END
