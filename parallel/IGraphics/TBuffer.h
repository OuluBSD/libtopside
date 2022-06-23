#ifndef _IGraphics_TemplateBuffer_h_
#define _IGraphics_TemplateBuffer_h_

NAMESPACE_PARALLEL_BEGIN


template <class Gfx>
struct BufferT;

template <class Gfx>
struct BufferStageT : GfxBuffer {
	using Framebuffer = FramebufferT<Gfx>;
	using RuntimeState = RuntimeStateT<Gfx>;
	using DataState = DataStateT<Gfx>;
	using SoftShaderBase = SoftShaderBaseT<Gfx>;
	using DataObject = DataObjectT<Gfx>;
	using Sample = GVar::Sample;
	using ShaderState = ShaderStateT<Gfx>;
	using Buffer = BufferT<Gfx>;
	using ContextState  = ContextStateT<Gfx>;
	using InputState  = InputStateT<Gfx>;
	using NativeProgram = typename Gfx::NativeProgram;
	using NativeColorBufferConstRef = typename Gfx::NativeColorBufferConstRef;
	using Compiler = typename Gfx::Compiler;
	using Linker = typename Gfx::Linker;
	
	
	Buffer*						buf = 0;
	RuntimeState				rt;
	Framebuffer					fb;
	Framebuffer					stereo_fb[2];
	
	DataState					data;
	DataState*					user_data = 0;
	bool						use_user_data = false;
	bool						is_stereo = false;
	bool						initialized = false;
	
	One<SoftShaderBase>			soft[GVar::SHADERTYPE_COUNT];
	
	
	
	void Process(const RealtimeSourceConfig& cfg);
	void MakeFrameQuad();
	void UseRenderedFramebuffer();
	void RefreshPipeline();
	void UpdateTexBuffers();
	void CreatePipeline();
	bool LoadShader(GVar::ShaderType shader_type, String shader_id, String shader_path, String library_path);
	bool InitializeTexture(Size sz, int channels, Sample sample, const byte* data, int len);
	bool InitializeCubemap(Size sz, int channels, Sample sample, const Vector<byte>& d0, const Vector<byte>& d1, const Vector<byte>& d2, const Vector<byte>& d3, const Vector<byte>& d4, const Vector<byte>& d5);
	bool InitializeVolume(Size3 sz, int channels, Sample sample, const Vector<byte>& data);
	void ReadTexture(Size sz, int channels, Sample sample, const byte* data, int len);
	void ReadTexture(Size3 sz, int channels, Sample sample, const Vector<byte>& data);
	void ReadCubemap(Size sz, int channels, const Vector<byte>& d0, const Vector<byte>& d1, const Vector<byte>& d2, const Vector<byte>& d3, const Vector<byte>& d4, const Vector<byte>& d5);
	void FindVariables();
	int NewWriteBuffer(Framebuffer& fb);
	void TexFlags(GVar::TextureType type, GVar::Filter filter, GVar::Wrap repeat);
	void ClearPipeline();
	void ClearTex();
	void ClearTex(Framebuffer& fb);
	void CreateTex(Framebuffer& fb, bool create_depth, bool create_fbo);
	bool CompilePrograms();
	bool LoadInputLink(int in_id, const InternalPacketData& v);
	bool LoadInputLink(int in_id, const PacketValue& v);
	int BuiltinShader();
	template <int> int BuiltinShaderT();
	
	DataState& GetState() {return user_data ? *user_data : data;}
	NativeColorBufferConstRef GetInputTex(int input_i) const;
	GVar::TextureType GetTexType(int input_i) const;
	NativeColorBufferConstRef GetOutputTexture(bool reading_self) const;
	bool IsInitialized() const {return initialized;}
	
	void SetDataStateOverride(DataState* s) {user_data = s; use_user_data = s != 0;}
	bool SetLoopback(String loopback_str);
	void SetVars(DataState&, NativeProgram& gl_prog, const DataObject& o);
	void SetVar(DataState&, int var, NativeProgram& gl_prog, const DataObject& o);
	void SetVars(NativeProgram& gl_prog, const RealtimeSourceConfig& cfg);
	void SetVar(int var, NativeProgram& gl_prog, const RealtimeSourceConfig& cfg);
	void SetInputVolume(int in_id);
	void SetInputCubemap(int in_id);
	
	
private:
	bool LoadShaderFile(GVar::ShaderType shader_type, String shader_path, String library_path);
	bool LoadBuiltinShader(GVar::ShaderType shader_type, String id);
	
};

template <class Gfx>
struct BufferT : GfxBuffer {
	using Base = BufferT<Gfx>;
	using Buffer = BufferT<Gfx>;
	using DataState = DataStateT<Gfx>;
	using Framebuffer = FramebufferT<Gfx>;
	using RuntimeState = RuntimeStateT<Gfx>;
	using ShaderState = ShaderStateT<Gfx>;
	using InputState  = InputStateT<Gfx>;
	using ContextState  = ContextStateT<Gfx>;
	using ShaderPipeline = ShaderPipelineT<Gfx>;
	using DataObject = DataObjectT<Gfx>;
	using BufferStage = BufferStageT<Gfx>;
	using NativeFrameBufferRef = typename Gfx::NativeFrameBufferRef;
	using Sample = GVar::Sample;
	using SoftShaderBase = SoftShaderBaseT<Gfx>;
	using SoftShaderLibrary = typename Gfx::SoftShaderLibrary;
	using NativeColorBufferRef = typename Gfx::NativeColorBufferRef;
	using NativeProgram = typename Gfx::NativeProgram;
	using NativeColorBufferConstRef = typename Gfx::NativeColorBufferConstRef;
	
	RTTI_DECL1(BufferT, GfxBuffer)
	
	
	Vector<String>				link_ids;
	//Vector<BinderIface*>		binders;
	
	
	// set by user
	Vector<byte>				fb_out;
	EnvStateRef					env;
	int							loopback = -1;
	//int						test_shader = -1;
	
	Array<BufferStage>			stages;
	ContextState				ctx;
	bool						is_local_time = false;
	bool						is_stereo = false;
	
	
	
	static Callback2<String, Base*> WhenLinkInit;
	
	
	
	
	BufferT() {}
	
	void Visit(RuntimeVisitor& vis) override {vis & env;}
	void SetEnvState(EnvStateRef env) {this->env = env;}
	void AddLink(String s) {if (!s.IsEmpty()) link_ids << s;}
	//void SetBuiltinShader(int i) {test_shader = i;}
	
	
public:
	//bool LoadStereoShader(String vtx_path, String frag_path);
	
	//void AddBinder(BinderIface* iface) {VectorFindAdd(binders, iface);}
	//void RemoveBinder(BinderIface* iface) {VectorRemoveKey(binders, iface);}
	
	void Update(double dt);
	bool Initialize();
	void SetFramebufferSize(Size sz);
	void Process(ShaderPipeline& pipe);
	void Process(const RealtimeSourceConfig& cfg);
	bool SetupLoopback();
	void OnError(const char* fn, String s);
	void StoreOutputLink(InternalPacketData& v);
	void SetLocalTime(bool b=true) {is_local_time = b;}
	void SetStereoImage(bool b=true) {is_stereo = b;}
	Framebuffer& GetFramebuffer() {return stages.Top().fb;}
	const Framebuffer& GetFramebuffer() const {return stages.Top().fb;}
	BufferStage& Single() {ASSERT(stages.GetCount() == 1); return stages.Top();}
	void Reset();
	
};



NAMESPACE_PARALLEL_END

#endif
