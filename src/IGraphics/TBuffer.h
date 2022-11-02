#ifndef _IGraphics_TemplateBuffer_h_
#define _IGraphics_TemplateBuffer_h_

NAMESPACE_PARALLEL_BEGIN


template <class Gfx>
struct BufferT;

template <class Gfx>
struct BufferStageT : GfxBufferStage {
	using Framebuffer = FramebufferT<Gfx>;
	using PipelineState = PipelineStateT<Gfx>;
	using DataState = DataStateT<Gfx>;
	using ProgramState = ProgramStateT<Gfx>;
	using ModelState = ModelStateT<Gfx>;
	using DataObject = DataObjectT<Gfx>;
	using Sample = GVar::Sample;
	using ShaderState = ShaderStateT<Gfx>;
	using Buffer = BufferT<Gfx>;
	using ContextState  = ContextStateT<Gfx>;
	using InputState  = InputStateT<Gfx>;
	using Texture  = TextureT<Gfx>;
	using NativeProgram = typename Gfx::NativeProgram;
	using NativeColorBufferConstRef = typename Gfx::NativeColorBufferConstRef;
	using Compiler = typename Gfx::Compiler;
	using Linker = typename Gfx::Linker;
	
	RTTI_DECL1(BufferStageT, GfxBufferStage);
	
	struct ShaderConf {
		String str;
		bool is_path = false;
		bool is_content = false;
	};
	
	ShaderConf					shdr_confs[GVar::SHADERTYPE_COUNT + 1];
	
	Buffer*						buf = 0;
	Framebuffer					fb;
	
	DataState*					data = 0;
	PipelineState*				pipeline = 0;
	String						pipeline_str = "default";
	String						program_str = "default";
	bool						data_writable = false;
	int							loopback = -1;
	int							quad_count = 0;
	bool						use_user_data = false;
	bool						initialized = false;
	ModelState*					quad = 0;
	
	FloatImage					brdf_img;
	Texture						brdf_tex;
	
	VectorMap<int,String>		buf_inputs;
	
	// VR
	vec2						viewport_scale;
	vec2						left_lens_center;
	vec2						right_lens_center;
	float						warp_scale;
	vec4						hmd_warp_param;
	vec3						aberr;

	
	bool Initialize(int id, AtomBase& a, const Script::WorldState& ws);
	bool PostInitialize();
	bool ImageInitialize();
	void Process(const RealtimeSourceConfig& cfg);
	void MakeFrameQuad(int count=1);
	void UseRenderedFramebuffer();
	void UpdateTexBuffers();
	void RefreshPipeline();
	bool RealizeData();
	bool Compile(ProgramState& prog);
	bool InitializeTexture(Size sz, int channels, Sample sample, const byte* data, int len);
	bool InitializeCubemap(Size sz, int channels, Sample sample, const Vector<byte>& d0, const Vector<byte>& d1, const Vector<byte>& d2, const Vector<byte>& d3, const Vector<byte>& d4, const Vector<byte>& d5);
	bool InitializeVolume(Size3 sz, int channels, Sample sample, const Vector<byte>& data);
	void ReadTexture(Size sz, int channels, Sample sample, const byte* data, int len);
	void ReadTexture(Size3 sz, int channels, Sample sample, const Vector<byte>& data);
	void ReadCubemap(Size sz, int channels, const Vector<byte>& d0, const Vector<byte>& d1, const Vector<byte>& d2, const Vector<byte>& d3, const Vector<byte>& d4, const Vector<byte>& d5);
	int NewWriteBuffer();
	void TexFlags(GVar::TextureMode type, GVar::Filter filter, GVar::Wrap repeat);
	void ClearTex();
	void CreateTex(bool create_depth, bool create_fbo);
	bool LoadInputLink(int in_id, const PacketValue& v);
	bool LoadInputLink(int in_id, const InternalPacketData& v);
	void SetVars(ProgramState& prog, const RealtimeSourceConfig& cfg, const DataObject& o);
	void SetVar(ProgramState& prog, int var, const RealtimeSourceConfig& cfg, const DataObject& o);
	GfxCompilerArgs GetCompilerArgs() const;
	void CompileJIT();
	void SetAudio(bool b);
	
	DataState& LocalState() {ASSERT(data); return *data;}
	DataState& GetState() {ASSERT(data); return *data;}
	NativeColorBufferConstRef GetOutputTexture(bool reading_self) const;
	bool IsInitialized() const {return initialized;}
	const Framebuffer& GetFramebuffer() const {return fb;}
	Framebuffer& GetFramebuffer() {return fb;}
	
	void SetStereo(int stereo_id);
	void SetStereoLens();
	void SetDataState(DataState* s, bool data_writable);
	bool SetLoopback(String loopback_str);
	
	
};

template <class Gfx>
struct BufferT : GfxBuffer {
	using Base = BufferT<Gfx>;
	using Buffer = BufferT<Gfx>;
	using DataState = DataStateT<Gfx>;
	using ModelState = ModelStateT<Gfx>;
	using Framebuffer = FramebufferT<Gfx>;
	using PipelineState = PipelineStateT<Gfx>;
	using ShaderState = ShaderStateT<Gfx>;
	using InputState  = InputStateT<Gfx>;
	using ContextState  = ContextStateT<Gfx>;
	using ShaderPipeline = ShaderPipelineT<Gfx>;
	using DataObject = DataObjectT<Gfx>;
	using BufferStage = BufferStageT<Gfx>;
	using NativeFrameBufferRef = typename Gfx::NativeFrameBufferRef;
	using Sample = GVar::Sample;
	using NativeColorBufferRef = typename Gfx::NativeColorBufferRef;
	using NativeProgram = typename Gfx::NativeProgram;
	using NativeColorBufferConstRef = typename Gfx::NativeColorBufferConstRef;
	
	RTTI_DECL1(BufferT, GfxBuffer)
	
	
	enum {
		MODE_UNDEFINED,
		PENDING_PACKET,
		SINGLE_IMAGEBUF,
		SINGLE_TEXTURE,
		SINGLE_CUBEMAP,
		SINGLE_VOLUME,
		SINGLE_SOUND,
		MULTI_STEREO,
		MULTI_CUSTOM,
		
		MODE_COUNT
	};
	
	int							mode = 0;
	Vector<String>				link_ids;
	
	
	// set by user
	Vector<byte>				fb_out;
	EnvStateRef					env;
	
	ArrayMap<String, DataState>	data;
	Array<BufferStage>			stages;
	ContextState				ctx;
	bool						is_local_time = false;
	bool						is_initialized = false;
	
	int snd_sample_rate = 44100;
	int snd_frame_samples = 1024;
	
	
	static Callback2<String, Base*> WhenLinkInit;
	
	
	
	
	BufferT() {}
	
	void Visit(RuntimeVisitor& vis) override {vis & env;}
	void AddLink(String s) {if (!s.IsEmpty()) link_ids << s;}
	
	
public:
	void ClearRef() {env.Clear();}
	void Update(double dt);
	bool Initialize(AtomBase& a, const Script::WorldState& ws);
	bool ImageInitialize(bool is_win_fbo, Size screen_sz, bool add_data_states);
	bool PostInitialize();
	bool InitializeRenderer();
	void Process(const RealtimeSourceConfig& cfg);
	void OnError(const char* fn, String s);
	void StoreOutputLink(InternalPacketData& v);
	BufferStage& Top() {return stages.Top();}
	BufferStage& Single() {ASSERT(stages.GetCount() == 1); return stages.Top();}
	BufferStage& InitSingle();
	bool IsSingleInitialized() const {return stages.GetCount() == 1 && stages[0].IsInitialized();}
	void Reset();
	bool IsAudio() const {return mode == SINGLE_SOUND;}
	bool AcceptsOrders() const {return is_initialized;}
	bool LoadInputLink(int in_id, const InternalPacketData& v);
	
	void SetFramebufferSize(Size sz);
	void SetLocalTime(bool b=true) {is_local_time = b;}
	void SetStereoDataState(DataState* s);
	void SetDataStateOverride(DataState* s, bool data_writable);
	
	NativeColorBufferConstRef GetOutputTexture(bool reading_self) const;
	DataState& GetState();
	
};



NAMESPACE_PARALLEL_END

#endif
