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
	using NativeFrameBuffer = typename Gfx::NativeFrameBuffer;
	using Sample = GVar::Sample;
	RTTI_DECL1(BufferT, Base)
	
	
	Vector<String>				link_ids;
	Vector<BinderIface*>		binders;
	String						last_error;
	
	SoftShaderLibrary::FragmentShader	test_fragment = 0;
	
	// set by user
	Vector<byte>				fb_out;
	EnvStateRef					env;
	int							loopback = -1;
	int							test_shader = -1;
	bool						initialized = false;
	
	Framebuffer					fb;
	ContextState				ctx;
	RuntimeState				rt;
	DataState					data;
	
	static Callback2<String, BufferT*> WhenLinkInit;
	
	
	
	
	BufferT() {
		
	}
	
	void MakeFrameQuad();
	void Visit(RuntimeVisitor& vis) {vis & env;}
	void SetEnvState(EnvStateRef env) {this->env = env;}
	void AddLink(String s) {if (!s.IsEmpty()) link_ids << s;}
	bool IsInitialized() const {return initialized;}
	void SetTestShader(int i) {test_shader = i;}
	
	bool LoadShaderFile(GVar::ShaderType shader_type, String shader_path, String library_path);
	bool LoadTestShader(GVar::ShaderType shader_type, String id);
	void AddBinder(BinderIface* iface) {VectorFindAdd(binders, iface);}
	void RemoveBinder(BinderIface* iface) {VectorRemoveKey(binders, iface);}
	
	void Update(double dt);
	bool SetLoopback(String loopback_str);
	bool InitializeTexture(Size sz, int channels, Sample sample, const byte* data, int len);
	bool InitializeCubemap(Size sz, int channels, Sample sample, const Vector<byte>& d0, const Vector<byte>& d1, const Vector<byte>& d2, const Vector<byte>& d3, const Vector<byte>& d4, const Vector<byte>& d5);
	bool InitializeVolume(Size3 sz, int channels, Sample sample, const Vector<byte>& data);
	void ReadTexture(Size sz, int channels, Sample sample, const byte* data, int len);
	void ReadTexture(Size3 sz, int channels, Sample sample, const Vector<byte>& data);
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
	void SetVars(GLint prog, const DataObject& o);
	void SetVar(int var, GLint prog, const DataObject& o);
	void SetVars(GLint prog, const RealtimeSourceConfig& cfg);
	void SetVar(int var, GLint prog, const RealtimeSourceConfig& cfg);
	void ClearTex();
	void CreateTex(bool create_depth, bool create_fbo);
	const NativeFrameBuffer* GetInputTex(int input_i) const;
	GVar::TextureType GetTexType(int input_i) const;
	bool SetupLoopback();
	bool TestShader();
	bool CompilePrograms();
	const NativeFrameBuffer& GetOutputTexture(bool reading_self) const;
	void TexFlags(int type, GVar::Filter filter, GVar::Wrap repeat);
	void OnError(const char* fn, String s);
	void StoreOutputLink(InternalPacketData& v);
	bool LoadOutputLink(Size3 sz, int in_id, InternalPacketData& v);
	void SetInputVolume(int in_id);
	void SetInputCubemap(int in_id);
		
};

template <class Gfx> inline Callback2<String, BufferT<Gfx>*> BufferT<Gfx>::WhenLinkInit;


NAMESPACE_TOPSIDE_END

#endif
