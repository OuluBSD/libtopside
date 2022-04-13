#ifndef _IGraphics_TFramebuffer_h_
#define _IGraphics_TFramebuffer_h_

NAMESPACE_PARALLEL_BEGIN


#if 0
template <class Gfx>
struct FramebufferT : GfxFramebuffer {
	RTTI_DECL1(FramebufferT, GfxFramebuffer)
	using Base = FramebufferT<Gfx>;
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
#endif


template <class Gfx> struct InputStateT;


template <class Gfx>
struct FramebufferT : Gfx::FramebufferBase {
	using Base = FramebufferT<Gfx>;
	using NatColorBuf = typename Gfx::NativeColorBuffer;
	using NatDepthBuf = typename Gfx::NativeDepthBuffer;
	using NatFrameBuf = typename Gfx::NativeFrameBuffer;
	using SysFrameBuf = typename Gfx::SystemFrameBuffer;
	using NatProgram  = typename Gfx::NativeProgram;
	using NatPipeline = typename Gfx::NativePipeline;
	using NatShader = typename Gfx::NativeShader;
	//using ShaderState = typename Gfx::ShaderState;
	using ShaderState = ShaderStateT<Gfx>;
	//using InputState  = typename Gfx::InputState;
	using InputState  = InputStateT<Gfx>;
	using DataObject = typename Gfx::DataObject;
	using DataState = DataStateT<Gfx>;
	RTTI_DECL1(FramebufferT, GfxFramebuffer)
	
	NatColorBuf	color_buf[2];
	NatDepthBuf	depth_buf[2];
	NatFrameBuf	frame_buf[2];
	bool locked = false;
	
	
	
	
	
	FramebufferT() {
		for(int i = 0; i < 2; i++) {
			color_buf[i] = Null;
			depth_buf[i] = Null;
			frame_buf[i] = Null;
		}
	}
	
	const NatFrameBuf& GetReadFramebuffer() const;
	NatColorBuf& GetActiveColorBuffer();
	
	void Init(SysFrameBuf& fb, int w, int h, int stride);
	
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
