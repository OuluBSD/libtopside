#ifndef _IGraphics_GfxAccelAtom_h_
#define _IGraphics_GfxAccelAtom_h_

NAMESPACE_PARALLEL_BEGIN


template <class Gfx> bool IsDefaultGfxVal(const ValCls& val);

#ifdef flagSDL2
template <> inline bool IsDefaultGfxVal<SdlCpuGfx>(const ValCls& val) {return val == ValCls::VIDEO;}
template <> inline bool IsDefaultGfxVal<SdlSwGfx>(const ValCls& val) {return val == ValCls::FBO;}
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
struct ShaderDataPackT : RTTIBase {
	using DataState = DataStateT<Gfx>;
	
	RTTI_DECL0(ShaderDataPackT)
	
	One<SoftShaderBaseT<Gfx>>	frag_prog;
	One<SoftShaderBaseT<Gfx>>	vtx_prog;
	One<BinderIfaceVideo>		prog;
	DataState					accel_state;
	
	void Visit(RuntimeVisitor& vis) {if (prog) vis % *prog;}
};


template <class Gfx>
class GfxAccelAtom {
	
protected:
	friend class Events;
	
	using Buffer				= typename Gfx::Buffer;
	using Renderer				= RendererT<Gfx>;
	using StateDraw				= StateDrawT<Gfx>;
	using ShaderPipeline		= typename Gfx::ShaderPipeline;
	using DataState				= DataStateT<Gfx>;
	using ShaderDataPack		= ShaderDataPackT<Gfx>;
	using NativeDisplay			= typename Gfx::NativeDisplay;
	using NativeWindow			= typename Gfx::NativeWindow;
	using NativeRenderer		= typename Gfx::NativeRenderer;
	using NativeColorBufferRef	= typename Gfx::NativeColorBufferRef;
	using NativeFrameBufferRef	= typename Gfx::NativeFrameBufferRef;
	using SystemFrameBufferRef	= typename Gfx::SystemFrameBufferRef;
	using ValFormat				= typename Gfx::ValFormat;
	using RendererInfo			= typename Gfx::NativeRendererInfo;
	using GLContext				= typename Gfx::NativeGLContext;
	using Framebuffer = FramebufferT<Gfx>;
	
	GfxBufferFieldT<Gfx>	bf;
    NativeWindow			win;
    NativeDisplay			display;
    NativeRenderer			nat_rend;
    SystemFrameBufferRef	fb = 0;
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
	bool is_opengl = false;
	bool is_sw = false;
	bool is_dx11 = false;
	bool full_screen = false;
	bool is_maximized = false;
	bool is_sizeable = false;
	bool mouse_captured = false;
	bool close_machine = false;
	
	Packet fb_packet;
	Packet raw_packet;
	
	// requires template specialization
	void GfxFlags(uint32& flags);
	bool GfxRenderer();
	
	
	void SetWindowRect(Rect r);
	Buffer& GetBuffer() {return bf.GetBuffer();}
	
public:
	GfxAccelAtom() : ab(0) {desired_rect = RectC(0,0,1280,720);}
	
	void SetAtom(AtomBase* ab) {this->ab = ab;}
	void SetNative(NativeDisplay& display, NativeWindow& window, NativeRenderer* rend, SystemFrameBufferRef fb);
	
	bool Initialize(AtomBase& a, const Script::WorldState& ws);
	bool PostInitialize();
	bool Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch);
	void Uninitialize();
	
	bool Open(Size sz, int channels);
	bool AcceptsOrder() const {return bf.AcceptsOrder();}
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
	
};


NAMESPACE_PARALLEL_END

#endif
