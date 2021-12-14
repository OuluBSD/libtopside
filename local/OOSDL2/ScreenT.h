#ifndef _OOSDL2_ScreenT_h_
#define _OOSDL2_ScreenT_h_

NAMESPACE_SDL2_BEGIN


extern const char* def_shader;


void SetContextError(Context* ctx, String msg);


template <class Gfx>
class ScreenT : public Component {
	
protected:
	friend class Events;
	
	using Buffer = typename Gfx::Buffer;
	using Renderer = typename Gfx::Renderer;
	using StateDraw = typename Gfx::StateDraw;
	using Framebuffer = typename Gfx::Framebuffer;
	using ShaderPipeline = typename Gfx::ShaderPipeline;
	using NatWin = typename Gfx::NativeWindow;
	using NatRend = typename Gfx::NativeRenderer;
	using NatFrameBuf = typename Gfx::NativeFrameBuffer;
	
	Buffer* buf = 0;
    NatWin*					win = NULL;
    NatRend*				nat_rend = NULL;
    //NatFrameBuf*			fb = NULL;
	int						fb_stride;
    SDL_RendererInfo		rend_info;
    Rect					desired_rect;
	Size					screen_sz;
	String					title;
	SDL_GLContext			glcontext = 0;
	Renderer				rend;
	StateDraw				draw;
	SystemDraw				sysdraw;
	Packet					last_packet;
	bool is_opengl = false;
	bool is_sw = false;
	bool is_dx11 = false;
	bool full_screen = false;
	bool is_maximized = false;
	bool is_sizeable = false;
	bool mouse_captured = false;
	bool is_user_shader = false;
	String test_image;
	String frag_path;
	String vtx_path;
	String library_paths;
	
	
	// requires template specialization
	void GfxFlags(uint32& flags);
	bool GfxRenderer();
	
	
	bool Open0() override;
	bool AcceptsOrder() const {return is_user_shader || test_image.GetCount();}
	bool ImageInitialize();
	void Close0() override;
	
	uint32 GetInitFlag() const override {return SDL_INIT_VIDEO;}
	
	void SetWindowRect(Rect r);
	
	public:
	ScreenT(Context* ctx, AtomBase* ab) : Component(ctx, ab) {desired_rect = RectC(0,0,1280,720);}
	
	void Maximize(bool b=true);
	void Fullscreen(bool b=true);
	ScreenT& Sizeable(bool b=true) {is_sizeable = b; return *this;}
	void SetTitle(String title);
	void SetRect(Rect r);
	void Render(const RealtimeSourceConfig& cfg);
	bool Recv(int ch_i, const Packet& p);
	SystemDraw& BeginDraw();
	void CommitDraw();
	
	void SetBuffer(Buffer& buf) {this->buf = &buf;}
	
	Size GetSize() {return Gfx::GetWindowSize(*win);}
	bool IsCaptured() const {return mouse_captured;}
	
	void SetShaderFile(String frag_path, String vtx_path, String library_paths) {this->frag_path = frag_path; this->vtx_path = vtx_path; this->library_paths = library_paths;}
	void SetTestImage(String s) {test_image = s;}
	
};


NAMESPACE_SDL2_END

#endif
