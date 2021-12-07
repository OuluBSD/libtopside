#ifndef _Graphics_Templates_h_
#define _Graphics_Templates_h_

NAMESPACE_TOPSIDE_BEGIN


class CpuMemFramebuffer;
class CpuMemBuffer;

class OglFramebuffer;
class OglFramebufferState;
class OglBuffer;
class OglShaderState;
class OglInputState;
class OglFramebufferObject;
class OglVertexShaderArgs;
class OglFragmentShaderArgs;
class OglShader;
class OglShaderPipeline;
class OglCompiler;
class OglLinker;

class SdlCpuRenderer;
class SdlOglRenderer;

struct CpuGfx {
	using Framebuffer = CpuMemFramebuffer;
	using Buffer = CpuMemBuffer;
	
	using NativeFramebuffer = uint32;
	using NativeTexture = int32;
	using NativeShader = uint32;
	using NativeColorBuffer = uint32;
	using NativeDepthBuffer = uint32;
	using NativeFrameBuffer = uint32;
	using NativeProgram = uint32;
	using NativePipeline = uint32;
	
	FramebufferObject::Type type = FramebufferObject::SW;
	
};

struct OglGfx {
	using Framebuffer = OglFramebuffer;
	using FramebufferState = OglFramebufferState;
	using Buffer = OglBuffer;
	using Shader = OglShader;
	using ShaderState = OglShaderState;
	using ShaderPipeline = OglShaderPipeline;
	using InputState = OglInputState;
	using FramebufferObject = OglFramebufferObject;
	using BinderIface = BinderIfaceOgl;
	using VertexShaderArgs = OglVertexShaderArgs;
	using FragmentShaderArgs = OglFragmentShaderArgs;
	using Compiler = OglCompiler;
	using Linker = OglLinker;
	
	using NativeFramebuffer = GLuint;
	using NativeTexture = GLuint;
	using NativeShader = GLuint;
	using NativeColorBuffer = GLuint;
	using NativeDepthBuffer = GLuint;
	using NativeFrameBuffer = GLuint;
	using NativeVertexArray = GLuint;
	using NativeVertexBuffer = GLuint;
	using NativeElementBuffer = GLuint;
	using NativeProgram = GLuint;
	using NativePipeline = GLuint;
	
	TS::FramebufferObject::Type type = TS::FramebufferObject::OGL;
	
	
};

struct SdlGfx {
	using NativeWindow = SDL_Window;
	using NativeRenderer = SDL_Renderer;
	
};

struct SdlCpuGfx : CpuGfx, SdlGfx {
	using Renderer = SdlCpuRenderer;
	
};

struct SdlOglGfx : OglGfx, SdlGfx {
	using Renderer = SdlOglRenderer;
	
};

template <class Gfx>
struct FramebufferT : Framebuffer {
	using NatFrameBuf = typename Gfx::NativeFramebuffer;
	using NatTex = typename Gfx::NativeTexture;
	
	NatFrameBuf fb;
	NatTex tex;
	
	
	FramebufferT() {
		fb = Null;
		tex = Null;
	}
	
	const NatTex& GetTexture() const {return tex;}
	
};

template <class Gfx>
struct RendererT : Renderer {
	using NatWin = typename Gfx::NativeWindow;
	using NatRend = typename Gfx::NativeRenderer;
	using FrameBuf = typename Gfx::Framebuffer;
	
	
	NatWin* win = NULL;
    NatRend* rend = NULL;
    FrameBuf output;
	
public:
	RendererT() {}
	virtual ~RendererT() {}
	
	
	Framebuffer& GetOutputFramebuffer() override {return output;}
	FrameBuf& GetFramebuffer() {return output;}
	
	
};

template <class Gfx>
struct DrawFramebufferT : DrawFramebuffer {
	using Base = DrawFramebufferT<Gfx>;
	using GfxRenderer = typename Gfx::Renderer;
	using GfxFramebuffer = typename Gfx::Framebuffer;
	
	GfxRenderer* rend = 0;
	GfxFramebuffer* fb = 0;
	
	Renderer* GetRenderer() override {return rend;}
	Framebuffer* GetFramebuffer() override {return fb;}
	
	
};

template <class Gfx>
struct FramebufferObjectT : FramebufferObject {
	using Base = FramebufferObjectT<Gfx>;
	RTTI_DECL1(FramebufferObjectT, FramebufferObject)
	
	using GfxFramebufferState = typename Gfx::FramebufferState;
	using GfxTex = typename Gfx::NativeTexture;
	using VertexArray = typename Gfx::NativeVertexArray;
	using VertexBuffer = typename Gfx::NativeVertexBuffer;
	using ElementBuffer = typename Gfx::NativeElementBuffer;
	
	GfxFramebufferState* state = 0;
	VectorMap<int,GfxTex> tex;
	uint32 element_count = 0;
	VertexArray vao;
	VertexBuffer vbo;
	ElementBuffer ebo;
	
    mat4 view;
    mat4 proj;
    mat4 scale;
    mat4 model;
    bool is_global_view = false;
    int id = -1;
	
	
	FramebufferObjectT() {
		vao = Null;
		vbo = Null;
		ebo = Null;
	}
	
	void SetState(GfxFramebufferState& state) {this->state = &state;}
	
	
};

template <class Gfx>
struct FramebufferInputStateT : FramebufferInputState {
	using Base = FramebufferInputStateT<Gfx>;
	using GfxBuffer = typename Gfx::Buffer;
	
	const GfxBuffer* in_buf = 0;
	
	void Clear() {
		FramebufferInputState::Clear();
		in_buf = 0;
	}
	
};

template <class Gfx>
struct ShaderStateT : ShaderState {
	using Base = ShaderStateT<Gfx>;
	using NativeShader = typename Gfx::NativeShader;
	
	
	NativeShader shader;
	
	ShaderStateT() {
		shader = Null;
	}
	
};

template <class Gfx>
struct FramebufferStateT : FramebufferState {
	using Base = FramebufferStateT<Gfx>;
	using ColorBuf = typename Gfx::NativeColorBuffer;
	using DepthBuf = typename Gfx::NativeDepthBuffer;
	using FrameBuf = typename Gfx::NativeFrameBuffer;
	using Program  = typename Gfx::NativeProgram;
	using Pipeline = typename Gfx::NativePipeline;
	using NativeShader = typename Gfx::NativeShader;
	using ShaderState = typename Gfx::ShaderState;
	using InputState = typename Gfx::InputState;
	using GfxFramebufferObject = typename Gfx::FramebufferObject;
	using GfxFramebufferState = typename Gfx::FramebufferState;
	RTTI_DECL1(FramebufferStateT, FramebufferState)
	
	ColorBuf	color_buf[2];
	DepthBuf	depth_buf[2];
	FrameBuf	frame_buf[2];
	Program		prog;
	Pipeline	pipeline;
	bool		is_searched_vars = 0;
	int			var_idx[ShaderVar::VAR_COUNT];
	
	ShaderState shaders[ShaderVar::PROG_COUNT];
	InputState inputs[ShaderVar::INPUT_COUNT];
	
	// objects
	Array<GfxFramebufferObject> objects;
	Vector<String> user_vars;
	
	NativeShader shader;
	
	
	FramebufferStateT() {
		for(int i = 0; i < 2; i++) {
			color_buf[i] = Null;
			depth_buf[i] = Null;
			frame_buf[i] = Null;
		}
		prog = Null;
		pipeline = Null;
		shader = Null;
		memset(&var_idx, 0, sizeof(var_idx));
	}
	
	void SetCode(ShaderVar::Type t, const String& s) {shaders[t].code = s;}
	GLuint GetReadFramebuffer() const {return frame_buf[buf_i];}
	GLint GetGlType() const;
	GLint GetGlFormat() const;
	int GetGlSize() const;
	int GetGlSampleSize() const;
	
	
	FramebufferObject& CreateObject() override {
		GfxFramebufferState* s = CastPtr<GfxFramebufferState>(this);
		ASSERT(s);
		GfxFramebufferObject* p = new GfxFramebufferObject();
		p->SetState(*s);
		objects.Add(p);
		p->id = objects.GetCount() - 1;
		RendVer1(OnRealizeObject, p->id);
		return *p;
	}

};

template <class Gfx>
struct ShaderPipelineT :
	ShaderPipeline
{
	RTTI_DECL1(ShaderPipelineT, ShaderPipeline)
	using Base = ShaderPipelineT<Gfx>;
	
	
	
	
	
};

template <class Gfx>
struct ShaderT :
	Shader,
	ErrorReporter
{
	using Base = ShaderT<Gfx>;
	using GfxFramebufferState = typename Gfx::FramebufferState;
	using GfxVertexShaderArgs = typename Gfx::VertexShaderArgs;
	using GfxFragmentShaderArgs = typename Gfx::FragmentShaderArgs;
	RTTI_DECL1(ShaderT, Shader)
	
    GfxFramebufferState* state = 0;
    
    
	
    bool CheckCompileErrors(GLuint shader, String type);
	void BasicMeshRefresh(ModelMesh& model, Mesh& mesh);
    
	FramebufferObject* CreateObject() override {return state ? &state->CreateObject() : 0;}

	virtual void Process(GfxVertexShaderArgs& args) {Panic("not implemented");}
	virtual void Process(GfxFragmentShaderArgs& args) {Panic("not implemented");}
	
	
	
	
	#if 0
	bool Load(String vertex_path, String fragment_path, String geometry_path = "") override;
	void SetLoaded(bool b=true) {is_loaded = true;}
	bool IsLoaded() const override {return is_loaded;}
	void Refresh(ModelMesh& model) override;
    void Refresh(ModelMesh& model, Mesh& mesh) override;
	void Use() override;
	
	
	void SetBool(const String &name, bool value) const override;
	void SetInt(const String &name, int value) const override;
	void SetFloat(const String &name, float value) const override;
	void SetVec2(const String &name, const vec2 &value) const override;
	void SetVec3(const String &name, const vec3 &value) const override;
	void SetVec4(const String &name, const vec4 &value) const override;
	void SetMat2(const String &name, const mat2 &mat) const override;
	void SetMat3(const String &name, const mat3 &mat) const override;
	void SetMat4(const String &name, const mat4 &mat) const override;
	void SetVec2(const String &name, float x, float y) const override;
	void SetVec3(const String &name, float x, float y, float z) const override;
	void SetVec4(const String &name, float x, float y, float z, float w) const override;
	#endif
	
};

template <class Gfx>
struct FramebufferStateExtT : RTTIBase {
	using Base = FramebufferStateExtT<Gfx>;
	using GfxFramebufferState = typename Gfx::FramebufferState;
	using GfxShader = typename Gfx::Shader;
	RTTI_DECL0(FramebufferStateExtT)
	
	GfxFramebufferState* state = 0;
	GfxShader* stages[ShaderVar::PROG_COUNT];
	
	
	FramebufferStateExtT() {Clear();}
	void SetVertex(GfxShader& s) {stages[ShaderVar::PROG_VERTEX] = &s;}
	void SetFragment(GfxShader& s) {stages[ShaderVar::PROG_FRAGMENT] = &s;}
	
	
	void Clear() {
		//FramebufferState::Clear();
		state = 0;
		for(int i = 0; i < ShaderVar::PROG_COUNT; i++)
			stages[i] = 0;
	}
	
	void LoadState(FramebufferStateT<Gfx>& state) {
		Clear();
		
		this->state = &state;
		AppendState(state);
	}
	
	void AppendState(FramebufferStateT<Gfx>& state) {
		for(int i = 0; i < ShaderVar::PROG_COUNT; i++) {
			if (state.stages[i])
				stages[i] = CastPtr<ShaderT<Gfx>>(state.stages[i]);
		}
	}

};

template <class Gfx>
struct GCompilerT : GCompiler {
	using Base = GCompilerT<Gfx>;
	using NativeShader = typename Gfx::NativeShader;
	RTTI_DECL1(GCompilerT, GCompiler)
	
};

template <class Gfx>
struct GLinkerT : GLinker {
	using Base = GLinkerT<Gfx>;
	RTTI_DECL1(GLinkerT, GLinker)
	
	bool log = false;
	
	
	
	void EnableLog() {log = true;}
	void DisableLog() {log = false;}
	
};

template <class Gfx>
struct BufferT : GBuffer {
	using Base = BufferT<Gfx>;
	using GfxBinderIface = typename Gfx::BinderIface;
	using GfxFramebufferState = typename Gfx::FramebufferState;
	using GfxBuffer = typename Gfx::Buffer;
	using GfxShader = typename Gfx::Shader;
	using GfxShaderState = typename Gfx::ShaderState;
	using GfxShaderPipeline = typename Gfx::ShaderPipeline;
	using GfxFramebufferObject = typename Gfx::FramebufferObject;
	using GfxInputState = typename Gfx::InputState;
	using GfxCompiler = typename Gfx::Compiler;
	using GfxLinker = typename Gfx::Linker;
	using Sample = ShaderVar::Sample;
	RTTI_DECL1(BufferT, Base)
	
	
	Vector<String>				link_ids;
	Vector<GfxBinderIface*>		binders;
	String						last_error;
	
	// set by user
	Vector<byte>				fb_out;
	EnvStateRef					env;
	int							loopback = -1;
	bool						initialized = false;
	
	GfxFramebufferState			state;
	
	static Callback2<String, BufferT*> WhenLinkInit;
	
	
	
	void Visit(RuntimeVisitor& vis) {vis & env;}
	void SetEnvState(EnvStateRef env) {this->env = env;}
	void AddLink(String s) {if (!s.IsEmpty()) link_ids << s;}
	bool IsInitialized() const {return initialized;}
	
	bool LoadShaderFile(ShaderVar::Type shader_type, String shader_path, String library_path) {
		DLOG("BufferT::LoadShaderFile: " << shader_path);
		
		ASSERT(shader_type > ShaderVar::PROG_NULL && shader_type < ShaderVar::PROG_COUNT);
		GfxShaderState& shader = state.shaders[shader_type];
		
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
	
	
	
	
	
	void AddBinder(GfxBinderIface* iface) {
		VectorFindAdd(binders, iface);
	}
	
	void RemoveBinder(GfxBinderIface* iface) {
		VectorRemoveKey(binders, iface);
	}
	
	void Update(double dt) {
		if (state.is_time_used) {
			state.time_us += dt;
			if (state.time_us >= 1.0) {
				state.time_us = fmod(state.time_us, 1.0);
				state.time = GetSysTime();
				RTLOG("Update: " << dt << ", time=" << state.time.ToString());
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
		
		state.is_doublebuf = loopback >= 0;
		
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
		#if 0
		UpdateTexBuffers();
		
		ReadTexture(sz, channels, data);
		#endif
		return true;
	}
	
	void ReadTexture(Size sz, int channels, Sample sample, const byte* data, int len) {
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
		state.time_total = 0;
	}
	
	void SetFramebufferSize(Size sz) {
		ASSERT(sz.cx > 0 && sz.cy > 0);
		state.size = sz;
		if (initialized)
			UpdateTexBuffers();
	}
	
	void UpdateTexBuffers() {
		auto& s = state;
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
			ASSERT(s.GetGlSize() > 0);
			ASSERT(s.GetGlFormat() >= 0);
			ASSERT(s.GetGlType() >= 0);
			ClearTex();
			
			CreateTex(
				true, true);
			
		}
	}
	
	int NewWriteBuffer() {
		auto& s = state;
		if (s.is_doublebuf)
			s.buf_i = (s.buf_i + 1) % 2;
		return s.buf_i;
	}
	
	void Process(GfxShaderPipeline& pipe) {
		
		TODO
		
	}
	
	void Process(const RealtimeSourceConfig& cfg) {
		auto& s = state;
		GLint prog = s.prog;
		GLint pipeline = s.pipeline;
		
		ASSERT(prog > 0);
		if (prog == 0)
			return;
		
		RTLOG("Process " << HexStr(this) << " time: " << s.time_total);
		
		s.time_total = cfg.time_total;
		//RTLOG("Process: " << time_total);
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
			GfxBuffer* buf = CastPtr<GfxBuffer>(this);
			ASSERT(buf);
			GfxShader shader(state);
			for (GfxBinderIface* iface : binders)
				iface->Render(*buf, shader);
		}
		else {
			glRectf(-1.0, -1.0, 1.0, 1.0);
		}
		
		// render VBA from state
		for (GfxFramebufferObject& o : state.objects) {
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
	
	void UseRenderedFramebuffer() {
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
	
	void ClearPipeline() {
		if (state.pipeline) {
			glDeleteProgramPipelines(1, &state.pipeline);
			state.pipeline = 0;
		}
	}
	
	void CreatePipeline() {
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
	
	
	
	
	
	
	
	void FindVariables() {
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
	
	void SetVars(GLint prog, const GfxFramebufferObject& o) {
		for(int i = 0; i < ShaderVar::VAR_COUNT; i++)
			if (ShaderVar::is_obj_var[i] && state.var_idx[i] >= 0)
				SetVar(i, prog, o);
	}
	
	void SetVar(int var, GLint prog, const GfxFramebufferObject& o) {
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
			if (!ShaderVar::is_obj_var[i] && state.var_idx[i] >= 0)
				SetVar(i, prog, cfg);
	}
	
	void SetVar(int var, GLint prog, const RealtimeSourceConfig& cfg) {
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
			//RTLOG("SetVar: " << time_total);
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
				GfxInputState& in = s.inputs[j];
				values[j] = in.in_buf ? in.in_buf->state.time_total : 0;
			}
			glUniform4f(uindex, (GLfloat)values[0], (GLfloat)values[1], (GLfloat)values[2], (GLfloat)values[3]);
		}
		
		else if (var >= VAR_COMPAT_CHANNELRESOLUTION0 && var <= VAR_COMPAT_CHANNELRESOLUTION3) {
			int ch = var - VAR_COMPAT_CHANNELRESOLUTION0;
			GLfloat values[3] = {0,0,0};
			GfxInputState& in = state.inputs[ch];
			const BufferT* in_buf = in.in_buf;
			if (in_buf) {
				values[0] = (GLfloat)in_buf->state.size.cx;
				values[1] = (GLfloat)in_buf->state.size.cy;
				values[2] = (GLfloat)in_buf->state.depth;
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
			glUniform1f(uindex, (GLfloat)s.block_offset);
		}
		else {
			ASSERT_(false, "Invalid variable");
		}
	}
	
	void ClearTex() {
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
	
	void CreateTex(bool create_depth, bool create_fbo) {
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
	
	GLint GetInputTex(int input_i) const {
		const char* fn_name = "GetInputTex";
		//DLOG("BufferT::GetInputTex");
		if (input_i < 0 || input_i >= ShaderVar::INPUT_COUNT)
			return -1;
		
		const GfxInputState& in = state.inputs[input_i];
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
		
		const GfxInputState& in = state.inputs[input_i];
		
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
		
		GfxInputState& in = state.inputs[loopback];
		in.in_buf = CastPtr<GfxBuffer>(this);
		in.id = state.id;
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
		
		GfxCompiler comps[ShaderVar::PROG_COUNT];
		GfxLinker linker;
		linker.EnableLog();
		for(int i = 0; i < ShaderVar::PROG_COUNT; i++) {
			auto& s = state.shaders[i];
			if (s.code.IsEmpty())
				continue;
			
			GfxCompiler& comp = comps[i];
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
	
	GLint GetOutputTexture(bool reading_self) const {
		auto& s = state;
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
			GfxInputState& in = state.inputs[in_id];
			in.id = in_id;
			in.in_buf = (GfxBuffer*)v.ptr;
			
			ASSERT(sz.cx > 0 && sz.cy > 0);
			
			if (state.is_cubemap)
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
