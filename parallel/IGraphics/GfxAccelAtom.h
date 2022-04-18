#ifndef _IGraphics_GfxAccelAtom_h_
#define _IGraphics_GfxAccelAtom_h_

NAMESPACE_PARALLEL_BEGIN


template <class Gfx> bool IsDefaultGfxVal(const ValCls& val);

#ifdef flagSDL2
template <> inline bool IsDefaultGfxVal<SdlCpuGfx>(const ValCls& val) {return val == ValCls::VIDEO;}
#ifdef flagOGL
template <> inline bool IsDefaultGfxVal<SdlOglGfx>(const ValCls& val) {return val == ValCls::FBO;}
#endif
#endif

#ifdef flagOGL
template <> inline bool IsDefaultGfxVal<X11OglGfx>(const ValCls& val) {return val == ValCls::FBO;}
#endif

#ifdef flagSCREEN
template <> inline bool IsDefaultGfxVal<X11SwGfx>(const ValCls& val) {return val == ValCls::FBO;}
#endif


template <class Gfx>
struct ShaderDataPackT {
	using DataState = DataStateT<Gfx>;
	
	One<SoftShaderBaseT<Gfx>>	frag_prog;
	One<SoftShaderBaseT<Gfx>>	vtx_prog;
	One<BinderIfaceVideo>		prog;
	DataState					accel_state;
	
};


template <class Gfx>
class GfxAccelAtom {
	static_assert(Gfx::is_vendor_agnostic == false, "");
	
protected:
	friend class Events;
	
	using Buffer			= typename Gfx::Buffer;
	using Renderer			= RendererT<Gfx>;
	using StateDraw			= StateDrawT<Gfx>;
	using ShaderPipeline	= typename Gfx::ShaderPipeline;
	using DataState			= DataStateT<Gfx>;
	using ShaderDataPack	= ShaderDataPackT<Gfx>;
	using NativeDisplay		= typename Gfx::NativeDisplay;
	using NativeWindow		= typename Gfx::NativeWindow;
	using NativeRenderer	= typename Gfx::NativeRenderer;
	using NativeFrameBuffer	= typename Gfx::NativeFrameBuffer;
	using SystemFrameBuffer	= typename Gfx::SystemFrameBuffer;
	using ValFormat			= typename Gfx::ValFormat;
	using RendererInfo		= typename Gfx::NativeRendererInfo;
	using GLContext			= typename Gfx::NativeGLContext;
	using Framebuffer = FramebufferT<Gfx>;
	
	Buffer					buf;
    NativeWindow			win;
    NativeDisplay			display;
    NativeRenderer			nat_rend;
    SystemFrameBuffer*		fb = 0;
	AtomBase*				ab = NULL;
	int						fb_stride;
    RendererInfo			rend_info;
    Rect					desired_rect;
	Size					screen_sz;
	String					title;
	GLContext				glcontext = NULL;
	Renderer				rend;
	StateDraw				draw;
	SystemDraw				sysdraw;
	EnvStateRef				env;
	bool is_opengl = false;
	bool is_sw = false;
	bool is_dx11 = false;
	bool full_screen = false;
	bool is_maximized = false;
	bool is_sizeable = false;
	bool mouse_captured = false;
	bool is_user_shader = false;
	bool close_machine = false;
	String frag_shdr;
	String vtx_shdr;
	String frag_path;
	String vtx_path;
	String library_paths;
	
	Packet fb_packet;
	Packet raw_packet;
	
	// requires template specialization
	void GfxFlags(uint32& flags);
	bool GfxRenderer();
	
	
	void SetWindowRect(Rect r);
	Buffer& GetBuffer() {return buf;}
	
public:
	GfxAccelAtom() : ab(0) {desired_rect = RectC(0,0,1280,720);}
	
	void SetAtom(AtomBase* ab) {this->ab = ab;}
	void SetNative(NativeDisplay& display, NativeWindow& window, NativeRenderer* rend, SystemFrameBuffer* fb);
	
	bool Initialize(AtomBase& a, const Script::WorldState& ws);
	bool ProcessPacket(PacketValue& in, PacketValue& out);
	void Uninitialize();
	
	bool Open(Size sz, int channels);
	bool AcceptsOrder() const {return is_user_shader || frag_shdr.GetCount();}
	bool ImageInitialize();
	void Close();
	bool IsOpen() const;
	void Update(double dt);
	
	void Maximize(bool b=true);
	void Fullscreen(bool b=true);
	GfxAccelAtom& Sizeable(bool b=true) {is_sizeable = b; return *this;}
	void SetTitle(String title);
	void SetRect(Rect r);
	void Render(const RealtimeSourceConfig& cfg);
	bool Recv(int ch_i, const Packet& p);
	SystemDraw& BeginDraw();
	void CommitDraw();
	void FrameCopy(const ValFormat& vfmt, const byte* data, int len) {}
	
	Size GetSize() {return Gfx::GetWindowSize(win);}
	bool IsCaptured() const {return mouse_captured;}
	
	void SetShaderFile(String frag_path, String vtx_path, String library_paths) {this->frag_path = frag_path; this->vtx_path = vtx_path; this->library_paths = library_paths;}
	void SetFragmentShader(String s) {frag_shdr = s;}
	void SetVertexShader(String s) {vtx_shdr = s;}
	
};


NAMESPACE_PARALLEL_END

#endif
