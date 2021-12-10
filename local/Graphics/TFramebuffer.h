#ifndef _Graphics_TFramebuffer_h_
#define _Graphics_TFramebuffer_h_

NAMESPACE_TOPSIDE_BEGIN


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


template <class Gfx>
struct InputStateT : GfxInputState {
	RTTI_DECL1(InputStateT, GfxInputState)
	using Base = InputStateT<Gfx>;
	using Buffer = typename Gfx::Buffer;
	
	const Buffer* in_buf = 0;
	
	void Clear() {
		GfxInputState::Clear();
		in_buf = 0;
	}
	
};

template <class Gfx>
struct FramebufferT : GfxFramebuffer {
	using Base = FramebufferT<Gfx>;
	using NatColorBuf = typename Gfx::NativeColorBuffer;
	using NatDepthBuf = typename Gfx::NativeDepthBuffer;
	using NatFrameBuf = typename Gfx::NativeFrameBuffer;
	using NatProgram  = typename Gfx::NativeProgram;
	using NatPipeline = typename Gfx::NativePipeline;
	using NatShader = typename Gfx::NativeShader;
	using ShaderState = typename Gfx::ShaderState;
	using InputState = typename Gfx::InputState;
	using DataObject = typename Gfx::DataObject;
	using DataState = typename Gfx::DataState;
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
	
	GLuint GetReadFramebuffer() const {return frame_buf[buf_i];}
	GLint GetGlType() const {TODO}
	GLint GetGlFormat() const {TODO}
	int GetGlSize() const {TODO}
	int GetGlSampleSize() const {TODO}
	
	void Init(NatFrameBuf& fb, int w, int h, int stride) {
		color_buf[0] = fb;
		size.cx = w;
		size.cy = h;
		channels = stride;
	}
	
	bool Create(int w, int h, int channels=3) override {TODO}
	void Enter() override {ASSERT(!locked); locked = true;}
	void Leave() override {ASSERT(locked);  locked = false;}
	byte* GetIterator(int x, int y) override {Panic("Not usable: OglFramebuffer::GetIterator"); return 0;}
	void DrawFill(const byte* mem, int sz) override {TODO}
	
	void Bind();
	void Clear();
	void Render();
};



NAMESPACE_TOPSIDE_END

#endif
