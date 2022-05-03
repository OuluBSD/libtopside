#ifndef _IGraphics_TFramebuffer_h_
#define _IGraphics_TFramebuffer_h_

NAMESPACE_PARALLEL_BEGIN


#if 0
template <class Gfx>
struct FramebufferT : GfxFramebuffer {
	RTTI_DECL1(FramebufferT, GfxFramebuffer)
	using Base = FramebufferT<Gfx>;
	using NativeFrameBuffer = typename Gfx::NativeFramebuffer;
	using NatTex = typename Gfx::NativeTexture;
	
	NativeFrameBufferRef fb;
	NatTex tex;
	
	
	FramebufferT() {
		fb = Null;
		tex = Null;
	}
	
	const NatTex& GetTexture() const {return tex;}
	
};
#endif


template <class Gfx> struct InputStateT;


template <class Gfx>
struct FramebufferT : Gfx::FramebufferBase {
	using Base = FramebufferT<Gfx>;
	using NativeColorBufferRef = typename Gfx::NativeColorBufferRef;
	using NativeDepthBufferRef = typename Gfx::NativeDepthBufferRef;
	using NativeFrameBufferRef = typename Gfx::NativeFrameBufferRef;
	using NativeFrameBufferConstRef = typename Gfx::NativeFrameBufferConstRef;
	using SystemFrameBufferRef = typename Gfx::SystemFrameBufferRef;
	//using NativeProgram  = typename Gfx::NativeProgram;
	//using NativePipeline = typename Gfx::NativePipeline;
	//using NativeShaderRef = typename Gfx::NativeShaderRef;
	//using ShaderState = typename Gfx::ShaderState;
	//using ShaderState = ShaderStateT<Gfx>;
	//using InputState  = typename Gfx::InputState;
	//using InputState  = InputStateT<Gfx>;
	//using DataObject = typename Gfx::DataObject;
	//using DataState = DataStateT<Gfx>;
	RTTI_DECL1(FramebufferT, GfxFramebuffer)
	
	NativeColorBufferRef	color_buf[2];
	NativeDepthBufferRef	depth_buf[2];
	NativeFrameBufferRef	frame_buf[2];
	bool locked = false;
	
	
	
	
	
	FramebufferT() {
		for(int i = 0; i < 2; i++) {
			color_buf[i] = Null;
			depth_buf[i] = Null;
			frame_buf[i] = Null;
		}
	}
	
	NativeFrameBufferConstRef GetReadFramebuffer() const;
	NativeColorBufferRef GetActiveColorBuffer();
	
	void Init(NativeColorBufferRef clr, int w, int h, int stride);
	void Init(NativeFrameBufferRef fbo, NativeColorBufferRef clr, int w, int h, int stride);
	
	bool Create(int w, int h, int channels=3) override {TODO}
	void Enter() override {ASSERT(!locked); locked = true;}
	void Leave() override {ASSERT(locked);  locked = false;}
	byte* GetIterator(int x, int y) override {Panic("Not usable: OglFramebuffer::GetIterator"); return 0;}
	void DrawFill(const byte* mem, int sz) override;
	
	void Bind();
	void Clear();
	void Render();
	
	
	void SetWindowFbo(bool b=true);
	
};

/*template <class Gfx>
struct StandaloneFramebufferT : FramebufferT<Gfx> {
	using SystemFrameBuffer = typename Gfx::SystemFrameBuffer;
	using Base = FramebufferT<Gfx>;
	
	SystemFrameBuffer sys_buf;
	
	
	RTTI_DECL1(StandaloneFramebufferT, Base);
	
	void Init(Size sz, int stride, BinarySample::Type t) {
		ASSERT(t == BinarySample::U8_LE);
		Base::Init(sys_buf, sz.cx, sz.cy, stride);
	}
	
};*/

template <class Gfx>
struct InputStateT : GfxInputState {
	RTTI_DECL1(InputStateT, GfxInputState)
	using Base = InputStateT<Gfx>;
	using Buffer = typename Gfx::Buffer;
	
	const Buffer* in_buf = 0;
	//One<StandaloneFramebufferT<Gfx>> fb_for_rawdata;
	
	void Clear() {
		this->GfxInputState::Clear();
		in_buf = 0;
	}
	
};


NAMESPACE_PARALLEL_END

#endif
