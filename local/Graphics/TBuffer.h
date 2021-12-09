#ifndef _Graphics_TemplateBuffer_h_
#define _Graphics_TemplateBuffer_h_

NAMESPACE_TOPSIDE_BEGIN


template <class Gfx>
struct BufferT : GfxBuffer {
	using Base = BufferT<Gfx>;
	using BinderIface = typename Gfx::BinderIface;
	using DataState = typename Gfx::DataState;
	using Framebuffer = typename Gfx::Framebuffer;
	using ContextState = typename Gfx::ContextState;
	using RuntimeState = typename Gfx::RuntimeState;
	using Buffer = typename Gfx::Buffer;
	using Shader = typename Gfx::Shader;
	using ShaderState = typename Gfx::ShaderState;
	using ShaderPipeline = typename Gfx::ShaderPipeline;
	using DataObject = typename Gfx::DataObject;
	using InputState = typename Gfx::InputState;
	using Compiler = typename Gfx::Compiler;
	using Linker = typename Gfx::Linker;
	using Sample = ShaderVar::Sample;
	RTTI_DECL1(BufferT, Base)
	
	
	Vector<String>				link_ids;
	Vector<BinderIface*>		binders;
	String						last_error;
	
	// set by user
	Vector<byte>				fb_out;
	EnvStateRef					env;
	int							loopback = -1;
	bool						initialized = false;
	
	Framebuffer					fb;
	ContextState				ctx;
	RuntimeState				rt;
	DataState					data;
	
	static Callback2<String, BufferT*> WhenLinkInit;
	
	
	
	void Visit(RuntimeVisitor& vis) {vis & env;}
	void SetEnvState(EnvStateRef env) {this->env = env;}
	void AddLink(String s) {if (!s.IsEmpty()) link_ids << s;}
	bool IsInitialized() const {return initialized;}
	
	bool LoadShaderFile(ShaderVar::Type shader_type, String shader_path, String library_path) {
		DLOG("BufferT::LoadShaderFile: " << shader_path);
		
		ASSERT(shader_type > ShaderVar::PROG_NULL && shader_type < ShaderVar::PROG_COUNT);
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
	
	
	
	
	
	void AddBinder(BinderIface* iface) {
		VectorFindAdd(binders, iface);
	}
	
	void RemoveBinder(BinderIface* iface) {
		VectorRemoveKey(binders, iface);
	}
	
	void Update(double dt) {
		if (rt.is_time_used) {
			ctx.time_us += dt;
			if (ctx.time_us >= 1.0) {
				ctx.time_us = fmod(ctx.time_us, 1.0);
				ctx.time = GetSysTime();
				RTLOG("Update: " << dt << ", time=" << ctx.time.ToString());
			}
		}
	}
	
	bool SetLoopback(String loopback_str) {
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
	
	bool InitializeTexture(Size sz, int channels, Sample sample, const byte* data, int len) {
		RTLOG("InitializeTexture: " << sz.ToString() << ", " << HexStr((void*)data) << ", " << len);
		#if 0
		UpdateTexBuffers();
		
		ReadTexture(sz, channels, data, len);
		#endif
		return true;
	}
	
	bool InitializeCubemap(Size sz, int channels, Sample sample, const Vector<byte>& d0, const Vector<byte>& d1, const Vector<byte>& d2, const Vector<byte>& d3, const Vector<byte>& d4, const Vector<byte>& d5) {
		RTLOG("InitializeCubemap: " << sz.ToString());
		#if 0
		is_cubemap = true;
		
		UpdateTexBuffers();
		
		ReadCubemap(sz, channels, d0, d1, d2, d3, d4, d5);
		#endif
		return true;
	}
	
	bool InitializeVolume(Size3 sz, int channels, Sample sample, const Vector<byte>& data) {
		RTLOG("InitializeVolume: " << sz.ToString() << ", " << data.GetCount());
		TODO
		#if 0
		UpdateTexBuffers();
		
		ReadTexture(sz, channels, data);
		#endif
		return true;
	}
	
	void ReadTexture(Size sz, int channels, Sample sample, const byte* data, int len) {
		TODO
		#if 0
		GLenum type		= GL_TEXTURE_2D;
		
		GLuint& color_buf = this->color_buf[0];
		ASSERT(color_buf > 0);
		ASSERT(sz == fb_size);
		ASSERT(s.GetSize() == len);
		int intl_fmt = GetGfxChannelFormat(channels);
		
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
	
	void ReadTexture(Size3 sz, int channels, Sample sample, const Vector<byte>& data) {
		TODO
		#if 0
		GLenum type		= GL_TEXTURE_3D;
		
		ASSERT(fb_size.cx == sz.cx && fb_size.cy == sz.cy);
		GLuint& color_buf = this->color_buf[0];
		ASSERT(color_buf > 0);
		//int intl_fmt = GetGfxChannelFormat(channels);
		
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
	
	void ReadCubemap(Size sz, int channels, const Vector<byte>& d0, const Vector<byte>& d1, const Vector<byte>& d2, const Vector<byte>& d3, const Vector<byte>& d4, const Vector<byte>& d5) {
		GLenum type		= GL_TEXTURE_CUBE_MAP;
		GLuint& tex		= color_buf[0];
		int ch_code		= GetGfxChannelFormat(channels);
		
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
			OnError("ReadCubemap", "gl error " + HexStr(err));
		
		glBindTexture(type, 0);
	}
	
	#endif
	
	bool Initialize() {
		DLOG("BufferT::Initialize: load new program");
		
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
	
	void RefreshPipeline() {
		DLOG("BufferT::RefreshPipeline begin");
		
		CreatePipeline();
		
		UpdateTexBuffers();
		
		//if (!CheckInputTextures())
		//	return;
		
		Reset();
		
		DLOG("BufferT::RefreshPipeline end");
	}
	
	void Reset() {
		ctx.time_total = 0;
	}
	
	void SetFramebufferSize(Size sz) {
		ASSERT(sz.cx > 0 && sz.cy > 0);
		fb.size = sz;
		if (initialized)
			UpdateTexBuffers();
	}
	
	void UpdateTexBuffers() {
		auto& s = fb;
		if (!s.is_win_fbo) {
			ASSERT(s.channels > 0);
			ASSERT(s.size.cx > 0 && s.size.cy > 0);
			
			/*s.gl_sample_size		= s.sample == SAMPLE_BYTE ? 1 : 4;
			s.gl_type				= s.sample == SAMPLE_BYTE ? GL_UNSIGNED_BYTE : GL_FLOAT;
			fb_accel_type			= fb_accel_sampletype == SAMPLE_BYTE ? GL_UNSIGNED_BYTE : GL_FLOAT;
			
			fb_size_bytes			= fb_size.cx * fb_size.cy * fb_sample_size * fb_channels;
			fb_accel_size_bytes		= fb_size.cx * fb_size.cy * fb_accel_sample_size* fb_accel_channels;
			fb_fmt					= GetGfxChannelFormat(fb_channels, fb_type == GL_FLOAT);
			fb_accel_fmt			= GetGfxChannelFormat(fb_accel_channels, fb_accel_type == GL_FLOAT);
			*/
			
			TODO
			/*ASSERT(s.GetGlSize() > 0);
			ASSERT(s.GetGlFormat() >= 0);
			ASSERT(s.GetGlType() >= 0);*/
			
			ClearTex();
			
			CreateTex(
				true, true);
			
		}
	}
	
	int NewWriteBuffer() {
		auto& s = fb;
		if (s.is_doublebuf)
			s.buf_i = (s.buf_i + 1) % 2;
		return s.buf_i;
	}
	
	void Process(ShaderPipeline& pipe) {
		
		TODO
		
	}
	
	void Process(const RealtimeSourceConfig& cfg) {
		GLint prog = rt.prog;
		GLint pipeline = rt.pipeline;
		
		ASSERT(prog > 0);
		if (prog == 0)
			return;
		
		RTLOG("Process " << HexStr(this) << " time: " << ctx.time_total);
		
		ctx.time_total = cfg.time_total;
		//RTLOG("Process: " << time_total);
		ctx.frames++;
		
		if (env) {
			Size& video_size = env->Set<Size>(SCREEN0_SIZE);
			if (video_size.cx == 0 && video_size.cy == 0)
				video_size = fb.size;
			else if (video_size != fb.size) {
				fb.size = video_size;
				UpdateTexBuffers();
			}
		}
		
		glBindProgramPipeline(pipeline);
		glUseProgram(prog);
		
		if (!rt.is_searched_vars)
			FindVariables();
		
		int bi = NewWriteBuffer();
		
		if (!fb.is_win_fbo) {
			ASSERT(fb.frame_buf[bi] > 0);
			const GLenum bufs[] = {GL_COLOR_ATTACHMENT0_EXT};
			
			// combine FBO
		    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fb.frame_buf[bi]);
		    
		    // set up render target
		    glDrawBuffers(sizeof bufs / sizeof bufs[0], bufs);
		}
		
		
		SetVars(prog, cfg);
		
		RendVer(OnProcess);
		
		
		glClear(GL_COLOR_BUFFER_BIT);
		
		if (binders.GetCount()) {
			Buffer* buf = CastPtr<Buffer>(this);
			ASSERT(buf);
			Shader shader;
			shader.SetState(data);
			for (BinderIface* iface : binders)
				iface->Render(*buf, shader);
		}
		else {
			glRectf(-1.0, -1.0, 1.0, 1.0);
		}
		
		// render VBA from state
		for (DataObject& o : data.objects) {
			SetVars(rt.prog, o);
			o.Paint();
		}
		
		
		EnableGfxAccelDebugMessages(1);
		
		ASSERT(fb.is_win_fbo == (fb.frame_buf[bi] == 0));
		if (fb.frame_buf[bi] > 0) {
			// backup render target
		    //glDrawBuffer(GL_FRONT);
		    
		    // Some components (e.g. audio) needs to read the framebuffer
		    if (fb.is_read_fb_output)
				UseRenderedFramebuffer();
			
		    // reset FBO
		    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
		}
		
		EnableGfxAccelDebugMessages(0);
		
		glBindProgramPipeline(0);
		
		if (fb.is_audio) {
			ctx.block_offset += fb.size.cx;
		}
		else {
			ctx.block_offset += 1.0;
		}
	}
	
	void UseRenderedFramebuffer() {
		auto& s = fb;
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
	
	void ClearPipeline() {
		if (rt.pipeline) {
			glDeleteProgramPipelines(1, &rt.pipeline);
			rt.pipeline = 0;
		}
	}
	
	void CreatePipeline() {
		ClearPipeline();
		
		glGenProgramPipelines(1, &rt.pipeline);
		
		
		// only 1 program in pipeline currently
		{
			auto& prog = rt.prog;
			if (prog >= 0) {
				int bmask = 0;
				for(int i = 0; i < ShaderVar::PROG_COUNT; i++) {
					if (rt.shaders[(ShaderVar::Type)i].enabled) {
						// Note: ShaderVar::Type is relative to GL_*_SHADER_BIT
						int bit = 1 << i;
						ASSERT(i != ShaderVar::PROG_VERTEX   || bit == GL_VERTEX_SHADER_BIT);
						ASSERT(i != ShaderVar::PROG_FRAGMENT || bit == GL_FRAGMENT_SHADER_BIT);
						bmask |= bit;
					}
				}
				ASSERT(bmask != 0);
				glUseProgramStages(rt.pipeline, bmask, prog);
			}
		}
	}
	
	
	
	
	
	
	
	void FindVariables() {
		GLint n_uniforms;
		glGetProgramiv(rt.prog, GL_ACTIVE_UNIFORMS, &n_uniforms);
		GLchar name[80];
		GLsizei namelen;
		memset(rt.var_idx, -1, sizeof(rt.var_idx));
		rt.user_vars.Clear();
		for (int i = 0; i < n_uniforms; i++) {
			GLint size;
			GLenum type;
			
			glGetActiveUniform(rt.prog, i, 79, &namelen, &size, &type, name);
			name[namelen] = '\0';
			String name_str(name);
			
			bool found = false;
			bool state_var = false;
			for(int j = 0; j < ShaderVar::VAR_COUNT; j++) {
				const char* var_name = ShaderVar::names[j];
				if (strncmp(var_name, name, 128) == 0) {
					rt.var_idx[j] = i;
					if (j == ShaderVar::VAR_COMPAT_DATE && !rt.is_time_used)
						rt.is_time_used = true;
					found = true;
					state_var = !ShaderVar::is_obj_var[j];
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
	
	void SetVars(GLint prog, const DataObject& o) {
		for(int i = 0; i < ShaderVar::VAR_COUNT; i++)
			if (ShaderVar::is_obj_var[i] && rt.var_idx[i] >= 0)
				SetVar(i, prog, o);
	}
	
	void SetVar(int var, GLint prog, const DataObject& o) {
		using namespace ShaderVar;
		int uindex = rt.var_idx[var];
		ASSERT(uindex >= 0);
		if (var == VAR_VIEW) {
			if (o.is_global_view)
				TODO
			else
				glUniformMatrix4fv(uindex, 1, GL_FALSE, &o.view[0][0]);
		}
		else if (var == VAR_PROJECTION) {
			/*if (o.is_global_proj)
				TODO
			else*/
			glUniformMatrix4fv(uindex, 1, GL_FALSE, &o.proj[0][0]);
		}
		else if (var == VAR_SCALE) {
			glUniformMatrix4fv(uindex, 1, GL_FALSE, &o.scale[0][0]);
		}
		else if (var == VAR_MODEL) {
			glUniformMatrix4fv(uindex, 1, GL_FALSE, &o.model[0][0]);
		}
	}
	
	void SetVars(GLint prog, const RealtimeSourceConfig& cfg) {
		for(int i = 0; i < ShaderVar::VAR_COUNT; i++)
			if (!ShaderVar::is_obj_var[i] && rt.var_idx[i] >= 0)
				SetVar(i, prog, cfg);
	}
	
	void SetVar(int var, GLint prog, const RealtimeSourceConfig& cfg) {
		using namespace ShaderVar;
		int uindex = rt.var_idx[var];
		ASSERT(uindex >= 0);
		if (uindex < 0)
			return;
		
		RendVer1(OnUpdateVar, ShaderVar::names[var]);
		
		if (var == VAR_AUDIOTIME) {
			glUniform1f(uindex, (GLfloat)ctx.time_total);
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
			ASSERT(fb.size.cx > 0 && fb.size.cy > 0);
			glUniform3f(uindex, (GLfloat)fb.size.cx, (GLfloat)fb.size.cy, 1.0f);
		}
		
		else if (var == VAR_COMPAT_TIME) {
			//RTLOG("SetVar: " << time_total);
			glUniform1f(uindex, (GLfloat)ctx.time_total);
		}
		
		else if (var == VAR_COMPAT_TIMEDELTA) {
			ASSERT(ctx.frame_time != 0.0);
			glUniform1f(uindex, (GLfloat)ctx.frame_time);
		}
		
		else if (var == VAR_COMPAT_FRAME) {
			ASSERT(ctx.frames >= 0);
			glUniform1i(uindex, ctx.frames);
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
			double sec = ((int)ctx.time.hour * 60 + (int)ctx.time.minute) * 60 + (int)ctx.time.second;
			sec += ctx.time_us;
			glUniform4f(uindex, (GLfloat)ctx.time.year, (GLfloat)ctx.time.month, (GLfloat)ctx.time.day, (GLfloat)sec);
		}
		
		else if (var == VAR_COMPAT_SAMPLERATE) {
			glUniform1f(uindex, (GLfloat)ctx.sample_rate);
		}
		
		else if (var == VAR_COMPAT_OFFSET) {
			if (fb.size.cx > 0 && fb.size.cy > 0) {
				int x = fb.offset.x;
				int y = fb.size.cy - fb.size.cy - fb.offset.y; // -y_offset
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
			ASSERT(fb.fps > 0);
			glUniform1f(uindex, (GLfloat)fb.fps);
		}
		
		else if (var == VAR_COMPAT_CHANNELTIME) {
			double values[INPUT_COUNT];
			for(int j = 0; j < INPUT_COUNT; j++) {
				InputState& in = rt.inputs[j];
				values[j] = in.in_buf ? in.in_buf->ctx.time_total : 0;
			}
			glUniform4f(uindex, (GLfloat)values[0], (GLfloat)values[1], (GLfloat)values[2], (GLfloat)values[3]);
		}
		
		else if (var >= VAR_COMPAT_CHANNELRESOLUTION0 && var <= VAR_COMPAT_CHANNELRESOLUTION3) {
			int ch = var - VAR_COMPAT_CHANNELRESOLUTION0;
			GLfloat values[3] = {0,0,0};
			InputState& in = rt.inputs[ch];
			const BufferT* in_buf = in.in_buf;
			if (in_buf) {
				values[0] = (GLfloat)in_buf->fb.size.cx;
				values[1] = (GLfloat)in_buf->fb.size.cy;
				values[2] = (GLfloat)in_buf->fb.depth;
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
			glUniform3f(uindex, values[0], values[1], values[2]);
		}
		
		else if (var == VAR_COMPAT_BLOCKOFFSET) {
			glUniform1f(uindex, (GLfloat)ctx.block_offset);
		}
		else {
			ASSERT_(false, "Invalid variable");
		}
	}
	
	void ClearTex() {
		for(int bi = 0; bi < 2; bi++) {
			GLuint& color_buf = fb.color_buf[bi];
			GLuint& depth_buf = fb.depth_buf[bi];
			GLuint& frame_buf = fb.frame_buf[bi];
			
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
	
	void CreateTex(bool create_depth, bool create_fbo) {
		auto& s = fb;
		
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
	
	GLint GetInputTex(int input_i) const {
		const char* fn_name = "GetInputTex";
		//DLOG("BufferT::GetInputTex");
		if (input_i < 0 || input_i >= ShaderVar::INPUT_COUNT)
			return -1;
		
		const InputState& in = rt.inputs[input_i];
		if (in.in_buf == 0) {
			RTLOG("GetInputTex: warning: no input fbo buffer");
			return -1;
		}
		
		const BufferT* in_comp = in.in_buf;
		if (!in_comp)
			return -1;
		
		int tex = in_comp->GetOutputTexture(in_comp == this);
		ASSERT(tex > 0);
		
		return tex;
	}
	
	int GetTexType(int input_i) const {
		if (input_i < 0 || input_i >= ShaderVar::INPUT_COUNT)
			return -1;
		
		const InputState& in = rt.inputs[input_i];
		
		if (in.type == ShaderVar::VOLUME)
			return GL_TEXTURE_3D;
		
		else if (in.type == ShaderVar::CUBEMAP)
			return GL_TEXTURE_CUBE_MAP;
		
		else
			return GL_TEXTURE_2D;
	}
	
	
	
	
	
	
	
	bool SetupLoopback() {
		if (loopback < 0)
			return true;
		
		if (loopback >= ShaderVar::INPUT_COUNT) {
			LOG("SetupLoopback: error: too large loopback id #" << loopback);
			return false;
		}
		
		InputState& in = rt.inputs[loopback];
		in.in_buf = CastPtr<Buffer>(this);
		in.id = rt.id;
		in.type = ShaderVar::BUFFER;
		ASSERT(in.in_buf);
		
		return true;
	}
	
	bool CompilePrograms() {
		/*const char* fn_name = "CompilePrograms";
		for(int i = 0; i < PROG_COUNT; i++) {
			if (i == PROG_FRAGMENT && !CompileFragmentShader())
				return false;
			if (i == PROG_VERTEX && !CompileVertexShader())
				return false;
		}*/
		
		Compiler comps[ShaderVar::PROG_COUNT];
		Linker linker;
		linker.EnableLog();
		for(int i = 0; i < ShaderVar::PROG_COUNT; i++) {
			auto& s = rt.shaders[i];
			if (s.code.IsEmpty())
				continue;
			
			Compiler& comp = comps[i];
			s.enabled = true;
			
			if (!comp.Compile(ctx, rt, fb, s, (ShaderVar::Type)i)) {
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
	
	GLint GetOutputTexture(bool reading_self) const {
		auto& s = fb;
		ASSERT(!reading_self || s.is_doublebuf);
		int buf_i = s.buf_i;
		
		
		if (reading_self)
			buf_i = (buf_i + 1) % 2;
		if (s.color_buf[buf_i] == 0) {DLOG("BufferT::GetOutputTexture failed");}
		ASSERT(s.color_buf[buf_i] > 0);
		return s.color_buf[buf_i];
	}
	
	void TexFlags(int type, ShaderVar::Filter filter, ShaderVar::Wrap repeat) {
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
	
	void OnError(const char* fn, String s) {
		LOG("BufferT: error: " << (String)fn << ": " << s);
		last_error.Clear();
		last_error << fn << ": " << s;
	}
	
	
	void StoreOutputLink(InternalPacketData& v) {
		static_assert(sizeof(v.u32) == sizeof(GLuint), "Unexpected GLuint size");
		
		v.ptr = this;
	}
	
	bool LoadOutputLink(Size3 sz, int in_id, InternalPacketData& v) {
		if (in_id >= 0 && in_id < ShaderVar::INPUT_COUNT) {
			//LOG("LoadOutputLink: " << name << " #" << in_id);
			
			ASSERT(v.ptr);
			InputState& in = rt.inputs[in_id];
			in.id = in_id;
			in.in_buf = (Buffer*)v.ptr;
			
			ASSERT(sz.cx > 0 && sz.cy > 0);
			
			if (fb.is_cubemap)
				in.type = ShaderVar::CUBEMAP;
			else if (sz.cz > 0)
				in.type = ShaderVar::VOLUME;
			else
				in.type = ShaderVar::TEXTURE;
			
			return true;
		}
		
		RTLOG("LoadOutputLink: error: unexpected data");
		return false;
	}
	
	void SetInputVolume(int in_id) {
		TODO
		#if 0
		if (in_id >= in_buf.GetCount())
			in_buf.SetCount(in_id+1);
		
		BufferTInput& in = in_buf[in_id];
		in.type = BufferTInput::VOLUME;
		#endif
	}
	
	void SetInputCubemap(int in_id) {
		TODO
		#if 0
		if (in_id >= in_buf.GetCount())
			in_buf.SetCount(in_id+1);
		
		BufferTInput& in = in_buf[in_id];
		in.type = BufferTInput::CUBEMAP;
		#endif
	}
		
};

template <class Gfx> inline Callback2<String, BufferT<Gfx>*> BufferT<Gfx>::WhenLinkInit;


NAMESPACE_TOPSIDE_END

#endif
