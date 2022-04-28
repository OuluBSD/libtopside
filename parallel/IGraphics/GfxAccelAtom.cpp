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
void GfxAccelAtom<SdlCpuGfx>::GfxFlags(uint32& flags) {
	is_sw = true;
}

#ifdef flagOGL
template <>
bool GfxAccelAtom<SdlOglGfx>::GfxRenderer() {
	return true;
}
#endif

template <>
bool GfxAccelAtom<SdlCpuGfx>::GfxRenderer() {
	ASSERT(fb);
	ASSERT(*fb);
	
	rend.output.Init(*fb, screen_sz.cx, screen_sz.cy, fb_stride);
	rend.output.SetWindowFbo();
	
	//buf.fb.Init(fb, screen_sz.cx, screen_sz.cy, fb_stride);
	TODO
	
	return true;
}

template <>
void GfxAccelAtom<SdlCpuGfx>::FrameCopy(const VideoFormat& vfmt, const byte* mem, int len) {
	int frame_size = vfmt.GetFrameSize();
	if (mem && len > 0 && len == frame_size) {
		rend.GetFramebuffer().DrawFill(mem, len);
	}
}

#endif





#if defined flagOGL
template <>
void GfxAccelAtom<X11OglGfx>::GfxFlags(uint32& flags) {
	is_opengl = true;
}

template <>
bool GfxAccelAtom<X11OglGfx>::GfxRenderer() {
	return true;
}
#endif




#if defined flagSCREEN
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
	
	bf.GetBuffer().fb.Init(fb, clr, screen_sz.cx, screen_sz.cy, fb_stride);
	
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
}

template <class Gfx>
bool GfxAccelAtom<Gfx>::Open(Size sz, int channels) {
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
	
	if (full_screen)
		Gfx::SetWindowFullscreen(win);
	
	if (AcceptsOrder()) {
		if (!this->bf.ImageInitialize(screen_sz)) {
			LOG("GfxAccelAtom<Gfx>::Open: error: could not initialize image");
			return false;
		}
	}
	
	return true;
}

template <class Gfx>
void GfxAccelAtom<Gfx>::Close() {
	fb_packet.Clear();
	raw_packet.Clear();
	
	if (glcontext) {
		GetAppFlags().SetOpenGLContextOpen(false);
		Gfx::DeleteContext(glcontext);
		glcontext = 0;
	}
	if (nat_rend) {
		Gfx::DestroyRenderer(nat_rend);
		nat_rend = 0;
	}
	if (win) {
		Gfx::DestroyWindow(win);
		win = 0;
	}
}

template <class Gfx>
bool GfxAccelAtom<Gfx>::IsOpen() const {
	TODO
}

template <class Gfx>
void GfxAccelAtom<Gfx>::Update(double dt) {
	if (bf.env) {
		Size& video_size = bf.env->template Set<Size>(SCREEN0_SIZE);
		const bool& close_window = bf.env->template Set<bool>(SCREEN0_CLOSE);
		Buffer& buf = GetBuffer();
		
		if (close_window) {
			if (close_machine)
				ab->GetMachine().SetNotRunning();
			else
				ab->Destroy();
		}
		else if (video_size != buf.fb.size) {
			if (video_size.IsEmpty())
				video_size = buf.fb.size;
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
		const auto& vfmt = Gfx::GetFormat(fmt);
		
		if (pv.IsData<InternalPacketData>()) {
			const InternalPacketData& d = pv.GetData<InternalPacketData>();
			
			if (!d.ptr) {
				ASSERT_(0, "no pointer in InternalPacketData");
			}
			else if (d.IsText("gfxpack")) {
				ShaderDataPackT<Gfx>* gsd = (ShaderDataPackT<Gfx>*)d.ptr;
				TODO
			}
			else if (d.IsText("gfxstate")) {
				GfxDataState* gsd = (GfxDataState*)d.ptr;
				DataState* sd = CastPtr<DataState>(gsd);
				ASSERT(sd);
				if (sd)
					bf.GetBuffer().SetDataStateOverride(sd);
			}
			else if (d.IsText("gfxvector")) {
				fb_packet = p;
			}
			else if (d.IsText("gfxbuf")) {
				Size3 sz = vfmt.GetSize();
				int base = ab->GetSink()->GetSinkCount() > 1 ? 1 : 0;
				if (pv.IsData<InternalPacketData>()) {
					succ = bf.GetBuffer().LoadInputLink(sz, ch_i - base, d);
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
	else {
		DUMP(fmt);
		//RTLOG("GfxAccelAtom::Render: error: unexpected packet: " << last_packet->ToString());
		ASSERT(0);
		succ = false;
	}
	
	return succ;
}

template <class Gfx>
SystemDraw& GfxAccelAtom<Gfx>::BeginDraw() {
	AppFlags& flags = GetAppFlags();
	if (is_opengl || is_sw) {
	    rend.display = display;
	    rend.win = win;
	    rend.rend = nat_rend;
		rend.SetSize(screen_sz);
	    //draw.rend = nat_rend;
	    //draw.fb = &rend.GetFramebuffer();
	    draw.SetFormat(rend.GetFramebuffer());
	    sysdraw.ptr = &draw;
	    
	    rend.PreFrame();
	    //draw.fb->Enter();
	}
	else if (is_dx11) {
		TODO
	}
	else {
		Panic("Screen internal error");
	}
	
	return sysdraw;
}

template <class Gfx>
void GfxAccelAtom<Gfx>::CommitDraw() {
	AppFlags& flags = GetAppFlags();
	
	//draw.fb->Leave();
	rend.PostFrame();
}


/*#if defined flagSDL2 && defined flagOGL
template class GfxAccelAtom<SdlOglGfx>;
#endif

#ifdef flagSDL2
template class GfxAccelAtom<SdlCpuGfx>;
#endif*/


GFX_EXCPLICIT_INITIALIZE_CLASS(GfxAccelAtom)


NAMESPACE_PARALLEL_END
