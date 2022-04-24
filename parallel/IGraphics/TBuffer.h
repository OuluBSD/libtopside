#ifndef _IGraphics_TemplateBuffer_h_
#define _IGraphics_TemplateBuffer_h_

NAMESPACE_PARALLEL_BEGIN


template <class Gfx>
struct BufferT : GfxBuffer {
	static_assert(Gfx::is_vendor_agnostic == false, "");
	//static_assert(Gfx::is_vendor_agnostic == true, "For BufferT Gfx template argument should be vendor agnostic");
	
	using Base = BufferT<Gfx>;
	using Buffer = BufferT<Gfx>;
	//using BinderIface = typename Gfx::BinderIface;
	using DataState = DataStateT<Gfx>;
	//using Framebuffer = typename Gfx::Framebuffer;
	using Framebuffer = FramebufferT<Gfx>;
	//using ContextState = typename Gfx::ContextState;
	using RuntimeState = RuntimeStateT<Gfx>;
	//using Shader = typename Gfx::Shader;
	//using ShaderState = typename Gfx::ShaderState;
	using ShaderState = ShaderStateT<Gfx>;
	//using InputState  = typename Gfx::InputState;
	using InputState  = InputStateT<Gfx>;
	using ContextState  = ContextStateT<Gfx>;
	using ShaderPipeline = ShaderPipelineT<Gfx>;
	using DataObject = DataObjectT<Gfx>;
	using Compiler = typename Gfx::Compiler;
	using Linker = typename Gfx::Linker;
	using NativeFrameBuffer = typename Gfx::NativeFrameBuffer;
	using Sample = GVar::Sample;
	using SoftShaderBase = SoftShaderBaseT<Gfx>;
	using SoftShaderLibrary = typename Gfx::SoftShaderLibrary;
	using NativeColorBufferRef = typename Gfx::NativeColorBufferRef;
	using NativeColorBufferConstRef = typename Gfx::NativeColorBufferConstRef;
	
	RTTI_DECL1(BufferT, GfxBuffer)
	
	
	Vector<String>				link_ids;
	//Vector<BinderIface*>		binders;
	String						last_error;
	
	One<SoftShaderBase>			soft[GVar::SHADERTYPE_COUNT];
	
	// set by user
	Vector<byte>				fb_out;
	EnvStateRef					env;
	int							loopback = -1;
	//int							test_shader = -1;
	bool						initialized = false;
	
	Framebuffer					fb;
	ContextState				ctx;
	RuntimeState				rt;
	DataState					data;
	DataState*					user_data = 0;
	bool						use_user_data = false;
	
	
	
	static Callback2<String, Base*> WhenLinkInit;
	
	
	
	
	BufferT() {}
	
	void MakeFrameQuad();
	void Visit(RuntimeVisitor& vis) override {vis & env;}
	void SetEnvState(EnvStateRef env) {this->env = env;}
	void AddLink(String s) {if (!s.IsEmpty()) link_ids << s;}
	bool IsInitialized() const {return initialized;}
	//void SetBuiltinShader(int i) {test_shader = i;}
	void SetDataStateOverride(DataState* s) {user_data = s; use_user_data = s != 0;}
	
	DataState& GetState() {return user_data ? *user_data : data;}
	
	bool LoadShaderFile(GVar::ShaderType shader_type, String shader_path, String library_path);
	bool LoadBuiltinShader(GVar::ShaderType shader_type, String id);
	//void AddBinder(BinderIface* iface) {VectorFindAdd(binders, iface);}
	//void RemoveBinder(BinderIface* iface) {VectorRemoveKey(binders, iface);}
	
	void Update(double dt);
	bool SetLoopback(String loopback_str);
	bool InitializeTexture(Size sz, int channels, Sample sample, const byte* data, int len);
	bool InitializeCubemap(Size sz, int channels, Sample sample, const Vector<byte>& d0, const Vector<byte>& d1, const Vector<byte>& d2, const Vector<byte>& d3, const Vector<byte>& d4, const Vector<byte>& d5);
	bool InitializeVolume(Size3 sz, int channels, Sample sample, const Vector<byte>& data);
	//void ReadTexture(Size sz, int channels, Sample sample, const byte* data, int len);
	//void ReadTexture(Size3 sz, int channels, Sample sample, const Vector<byte>& data);
	void ReadCubemap(Size sz, int channels, const Vector<byte>& d0, const Vector<byte>& d1, const Vector<byte>& d2, const Vector<byte>& d3, const Vector<byte>& d4, const Vector<byte>& d5);
	bool Initialize();
	void RefreshPipeline();
	void Reset();
	void SetFramebufferSize(Size sz);
	void UpdateTexBuffers();
	int NewWriteBuffer();
	void Process(ShaderPipeline& pipe);
	void Process(const RealtimeSourceConfig& cfg);
	void UseRenderedFramebuffer();
	void ClearPipeline();
	void CreatePipeline();
	void FindVariables();
	void SetVars(DataState&, int gl_prog, const DataObject& o);
	void SetVar(DataState&, int var, int gl_prog, const DataObject& o);
	void SetVars(int gl_prog, const RealtimeSourceConfig& cfg);
	void SetVar(int var, int gl_prog, const RealtimeSourceConfig& cfg);
	void ClearTex();
	void CreateTex(bool create_depth, bool create_fbo);
	NativeColorBufferConstRef GetInputTex(int input_i) const;
	GVar::TextureType GetTexType(int input_i) const;
	bool SetupLoopback();
	bool BuiltinShader();
	template <int> bool BuiltinShaderT();
	bool CompilePrograms();
	NativeColorBufferConstRef GetOutputTexture(bool reading_self) const;
	void TexFlags(GVar::TextureType type, GVar::Filter filter, GVar::Wrap repeat);
	void OnError(const char* fn, String s);
	void StoreOutputLink(InternalPacketData& v);
	bool LoadOutputLink(Size3 sz, int in_id, const InternalPacketData& v);
	bool LoadOutputLink(int in_id, const PacketValue& v);
	void SetInputVolume(int in_id);
	void SetInputCubemap(int in_id);
	
};



NAMESPACE_PARALLEL_END

#endif
