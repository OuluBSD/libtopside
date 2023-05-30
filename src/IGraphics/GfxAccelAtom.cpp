#include "IGraphics.h"
#include <SerialMach/SerialMach.h>

NAMESPACE_PARALLEL_BEGIN

#ifdef flagSDL2

#ifdef flagOGL
template <>
void GfxAccelAtom<SdlOglGfx>::GfxFlags(uint32& flags) {
	is_opengl = true;
}
#endif

template <>
void GfxAccelAtom<SdlSwGfx>::GfxFlags(uint32& flags) {
	is_sw = true;
}

#ifdef flagOGL
template <>
bool GfxAccelAtom<SdlOglGfx>::GfxRenderer() {
	return true;
}
#endif

template <>
bool GfxAccelAtom<SdlSwGfx>::GfxRenderer() {
	return true;
}

template <>
void GfxAccelAtom<SdlSwGfx>::FrameCopy(const VideoFormat& vfmt, const byte* mem, int len) {
	int frame_pitch = vfmt.GetSampleSize() * vfmt.GetSize().cx;
	int frame_size = vfmt.GetFrameSize();
	if (mem && len > 0 && len == frame_size) {
		rend.GetFramebuffer().DrawFill(mem, len, frame_pitch);
	}
}

#endif





#if defined flagPOSIXDESKTOP && defined flagOGL
template <>
void GfxAccelAtom<X11OglGfx>::GfxFlags(uint32& flags) {
	is_opengl = true;
}

template <>
bool GfxAccelAtom<X11OglGfx>::GfxRenderer() {
	return true;
}
#endif




#if defined flagSCREEN && defined flagPOSIXDESKTOP
template <>
void GfxAccelAtom<X11SwGfx>::GfxFlags(uint32& flags) {
	is_sw = true;
}

template <>
bool GfxAccelAtom<X11SwGfx>::GfxRenderer() {
	ASSERT(fb);
	
	NativeColorBufferRef clr = fb->Get(0);
	ASSERT(clr);
	
	rend.output.Init(fb, clr, screen_sz.cx, screen_sz.cy, fb_stride);
	rend.output.SetWindowFbo();
	
	auto& buf = bf.GetBuffer();
	auto& buf_fb = buf.Top().GetFramebuffer();
	buf_fb.Init(fb, clr, screen_sz.cx, screen_sz.cy, fb_stride);
	
	return true;
}
#endif


#if defined flagWIN32 && defined flagDX11
template <>
void GfxAccelAtom<WinD11Gfx>::GfxFlags(uint32& flags) {
	is_dx11 = true;
}

template <>
bool GfxAccelAtom<WinD11Gfx>::GfxRenderer() {
	ASSERT(fb);
	
	Microsoft::WRL::ComPtr<ID3D11Texture2D> clr;
	HRESULT hr = S_OK;
	
	
	// Create the backbuffer
    hr = fb->GetBuffer(
        0,
        __uuidof(ID3D11Texture2D),
        (void**) &clr);
	
    if (FAILED(hr))
        return false;
    
    clr->GetDesc(&impl.m_bbDesc);
    screen_sz.cx = impl.m_bbDesc.Width;
    screen_sz.cy = impl.m_bbDesc.Height;
    
    
    // Create the render target view based on the back buffer
    hr = display->CreateRenderTargetView(
        clr.Get(),
        nullptr,
        impl.m_pRenderTarget.GetAddressOf()
    );
	
	
	rend.output.Init(fb, clr, screen_sz.cx, screen_sz.cy, fb_stride);
	rend.output.SetWindowFbo();
	
	auto& buf = bf.GetBuffer();
	auto& buf_fb = buf.Top().GetFramebuffer();
	buf_fb.Init(fb, clr, screen_sz.cx, screen_sz.cy, fb_stride);
	
	return true;
}
#endif




template <class Gfx>
void GfxAccelAtom<Gfx>::SetNative(NativeDisplay& display, NativeWindow& window, NativeRenderer* rend, SystemFrameBufferRef fb) {
	win = window;
	this->display = display;
	this->nat_rend = rend ? *rend : 0;
	this->fb = fb;
}

template <class Gfx>
bool GfxAccelAtom<Gfx>::Initialize(AtomBase& a, const Script::WorldState& ws) {
	this->ab = &a;
	
	Serial::Link* link = a.GetLink();
	Serial::FramePollerBase* base = CastPtr<Serial::FramePollerBase>(link);
	Serial::PollerLink* poller = CastPtr<Serial::PollerLink>(link);
	if (base) {
		base->SetFPS(60);
	}
	else {
		LOG("GfxAccelAtom<Gfx>::Initialize: warning: unexpected link type");
	}
	
	if (!bf.Initialize(a, ws))
		return false;
	
	Sizeable(ws.Get(".sizeable") == "true");
	Maximize(ws.Get(".maximize") == "true");
	Fullscreen(ws.Get(".fullscreen") == "true");
	
	close_machine = ws.Get(".close_machine") == "true";
	
	a.AddAtomToUpdateList();
	
	//AtomBase::GetMachine().template Get<AtomSystem>()->AddPolling(AtomBase::AsRefT());
	ISinkRef sink = a.GetSink();
	sink->GetValue(0).SetMaxQueueSize(1);
	
	if (poller) {
		int sink_count = sink->GetSinkCount();
		if (sink_count > 1) {
			for(int i = 0; i < sink_count; i++)
				if (IsDefaultGfxVal<Gfx>(sink->GetValue(i).GetFormat().vd.val))
					poller->SetFinalizeOnSide();
		}
	}
	else {
		LOG(link->GetDynamicName());
		TODO // check if ok
	}
	
	return true;
}

template <class Gfx>
bool GfxAccelAtom<Gfx>::PostInitialize() {
	return bf.PostInitialize();
}

template <class Gfx>
void GfxAccelAtom<Gfx>::Uninitialize() {
	ab->RemoveAtomFromUpdateList();
	bf.ClearRef();
	Gfx::ClearFramebufferRef(fb);
	fb_packet.Clear();
	raw_packet.Clear();
}

template <class Gfx>
bool GfxAccelAtom<Gfx>::Open(Size sz, int channels, bool skip_fullscreen) {
	AppFlags& app_flags = GetAppFlags();
	is_sw = false;
	is_opengl = false;
	is_dx11 = false;
	
	
	// Window
	screen_sz = sz;
	fb_stride = channels;
	uint32 flags = 0;
	
	GfxFlags(flags);
	
	ASSERT(win);
	//ASSERT(nat_rend);
	
	Gfx::SetTitle(display, win, title);
    
    GfxRenderer();
	
	#ifdef flagDEBUG
	Gfx::SetDebugOutput(true);
	#endif
	
	if (full_screen && !skip_fullscreen)
		Gfx::SetWindowFullscreen(win);
	
	//if (AcceptsOrder()) {
	if (!this->bf.ImageInitialize(true, screen_sz)) {
		LOG("GfxAccelAtom<Gfx>::Open: error: could not initialize image");
		return false;
	}
	//}
	
	is_open = true;
	return true;
}

template <class Gfx>
void GfxAccelAtom<Gfx>::Close() {
	is_open = false;
	
	fb_packet.Clear();
	raw_packet.Clear();
	
	if (glcontext) {
		GetAppFlags().SetOpenGLContextOpen(false);
		Gfx::DeleteContext(glcontext);
		glcontext = 0;
	}
	if (nat_rend) {
		Gfx::DestroyRenderer(nat_rend);
		Gfx::ClearRendererRef(nat_rend);
	}
	if (win) {
		Gfx::DestroyWindow(win);
		win = 0;
	}
}

template <class Gfx>
bool GfxAccelAtom<Gfx>::IsOpen() const {
	return is_open;
}

template <class Gfx>
void GfxAccelAtom<Gfx>::Update(double dt) {
	auto& buf = bf.GetBuffer();
	auto& env = buf.env;
	auto& fb = buf.Single().GetFramebuffer();
	
	if (env) {
		Size& video_size = env->template Set<Size>(SCREEN0_SIZE);
		const bool& close_window = env->template Set<bool>(SCREEN0_CLOSE);
		Buffer& buf = GetBuffer();
		
		if (close_window) {
			if (close_machine)
				ab->GetMachine().SetNotRunning();
			else
				ab->Destroy();
		}
		else if (video_size != fb.size) {
			if (video_size.IsEmpty())
				video_size = fb.size;
			else
				buf.SetFramebufferSize(video_size);
		}
	}
}

template <class Gfx>
void GfxAccelAtom<Gfx>::Maximize(bool b) {
	if (b == is_maximized)
		return;
	is_maximized = b;
	if (IsOpen() && win) {
		if (b)
			Gfx::MaximizeWindow(win);
		else
			Gfx::RestoreWindow(win);
	}
}

template <class Gfx>
void GfxAccelAtom<Gfx>::Fullscreen(bool b) {
	if (b == full_screen)
		return;
	full_screen = b;
	if (IsOpen() && win) {
		Gfx::SetWindowFullscreen(win, b);
	}
}

template <class Gfx>
void GfxAccelAtom<Gfx>::SetTitle(String title) {
	this->title = title;
	if (IsOpen() && win)
		Gfx::SetTitle(display, win, title);
}

template <class Gfx>
void GfxAccelAtom<Gfx>::SetRect(Rect r) {
	desired_rect = r;
	if (IsOpen() && win && !full_screen) {
		Gfx::SetWindowPosition(win, r.TopLeft());
		Gfx::SetWindowSize(win, r.GetSize());
	}
}

template <class Gfx>
void GfxAccelAtom<Gfx>::Render(const RealtimeSourceConfig& cfg) {
	
	if (raw_packet) {
		Format fmt = raw_packet->GetFormat();
		const auto& vfmt = Gfx::GetFormat(fmt);
		const Vector<byte>& data = raw_packet->GetData();
		BeginDraw();
		FrameCopy(vfmt, (const byte*)data.Begin(), data.GetCount());
		CommitDraw();
		raw_packet.Clear();
	}
	else if (fb_packet) {
		Format fmt = fb_packet->GetFormat();
		const auto& vfmt = Gfx::GetFormat(fmt);
		const InternalPacketData& d = fb_packet->GetData<InternalPacketData>();
		ShaderPipeline& sd = *(ShaderPipeline*)d.ptr;
		BeginDraw();
		FrameCopy(vfmt, (const byte*)d.ptr, d.count);
		CommitDraw();
		fb_packet.Clear();
	}
	else {
		BeginDraw();
		bf.GetBuffer().Process(cfg);
		CommitDraw();
	}
	
}

template <class Gfx>
bool GfxAccelAtom<Gfx>::Recv(int ch_i, const Packet& p) {
	PacketValue& pv = *p;
	
	bool succ = true;
	Format fmt = pv.GetFormat();
	if (IsDefaultGfxVal<Gfx>(fmt.vd.val)) {
		//const auto& vfmt = Gfx::GetFormat(fmt);
		
		if (pv.IsData<InternalPacketData>()) {
			const InternalPacketData& d = pv.GetData<InternalPacketData>();
			
			if (!d.ptr) {
				ASSERT_(0, "no pointer in InternalPacketData");
			}
			/*else if (d.IsText("gfxpack")) {
				ShaderDataPackT<Gfx>* gsd = (ShaderDataPackT<Gfx>*)d.ptr;
				TODO
			}*/
			else if (d.IsText("gfxstate")) {
				GfxDataState* gsd = (GfxDataState*)d.ptr;
				DataState* sd = CastPtr<DataState>(gsd);
				ASSERT(sd);
				if (sd)
					bf.GetBuffer().SetDataStateOverride(sd, false);
			}
			else if (d.IsText("gfxvector")) {
				fb_packet = p;
			}
			else if (d.IsText("gfxbuf")) {
				//Size3 sz = vfmt.GetSize();
				int base = ab->GetSink()->GetSinkCount() > 1 ? 1 : 0;
				if (pv.IsData<InternalPacketData>()) {
					succ = bf.GetBuffer().LoadInputLink(ch_i - base, d);
				}
				else {
					RTLOG("GfxAccelAtom::Recv: cannot handle packet: " << pv.ToString());
				}
			}
			else {
				DUMP(d.GetText());
				TODO // some old class pushing ptr without txt?
			}
		}
		else {
			raw_packet = p;
		}
	}
	else if (fmt.IsOrder() && AcceptsOrder()) {
		// pass
	}
	else if (fmt.vd == VD(Ogl, Prog)) {
		TODO
		/*
		Don't use GLDraw here!
		Render DrawCommand queue in IGraphics package!
		Take a hint from GLDraw package and class
		*/
	}
	else {
		DUMP(fmt);
		//RTLOG("GfxAccelAtom::Render: error: unexpected packet: " << last_packet->ToString());
		ASSERT(0);
		succ = false;
	}
	
	return succ;
}

template <class Gfx>
Draw& GfxAccelAtom<Gfx>::BeginDraw() {
	AppFlags& flags = GetAppFlags();
	if (is_opengl || is_sw || is_dx11) {
	    rend.display = display;
	    rend.win = win;
	    rend.rend = nat_rend;
		rend.SetSize(screen_sz);
	    draw.SetFormat(rend.GetFramebuffer());
	    sysdraw.SetTarget(&draw);
	    
	    rend.PreFrame();
	}
	/*else if (is_dx11) {
		TODO
	}*/
	else {
		Panic("Screen internal error");
	}
	
	return sysdraw;
}

template <class Gfx>
void GfxAccelAtom<Gfx>::CommitDraw() {
	AppFlags& flags = GetAppFlags();
	
	rend.PostFrame();
}



GFX3D_EXCPLICIT_INITIALIZE_CLASS(GfxAccelAtom)


NAMESPACE_PARALLEL_END
