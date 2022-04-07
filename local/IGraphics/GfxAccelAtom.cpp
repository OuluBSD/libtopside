#include "IGraphics.h"
#include <SerialMach/SerialMach.h>

NAMESPACE_PARALLEL_BEGIN

#ifdef flagSDL2

template <>
void GfxAccelAtom<SdlOglGfx>::GfxFlags(uint32& flags) {
	is_opengl = true;
	
	TODO // not here
	
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	flags |= SDL_WINDOW_OPENGL;
	
	if (full_screen)	flags |= SDL_WINDOW_FULLSCREEN;
	if (is_sizeable)	flags |= SDL_WINDOW_RESIZABLE;
	if (is_maximized)	flags |= SDL_WINDOW_MAXIMIZED;
	
}

template <>
void GfxAccelAtom<SdlCpuGfx>::GfxFlags(uint32& flags) {
	is_sw = true;
	
	TODO // not here
	
	if (full_screen)	flags |= SDL_WINDOW_FULLSCREEN;
	if (is_sizeable)	flags |= SDL_WINDOW_RESIZABLE;
	if (is_maximized)	flags |= SDL_WINDOW_MAXIMIZED;
	
}

template <>
bool GfxAccelAtom<SdlOglGfx>::GfxRenderer() {
	// Renderer
    SDL_GetRendererInfo(nat_rend, &rend_info);
	if ((rend_info.flags & SDL_RENDERER_ACCELERATED) == 0 ||
        (rend_info.flags & SDL_RENDERER_TARGETTEXTURE) == 0)
        return false;
	
	// GL context
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 0);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 0);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
	glcontext = SDL_GL_CreateContext(win);
	GetAppFlags().SetOpenGLContextOpen();
	
	// Glew
	GLenum err = glewInit();
	if (err != GLEW_OK) {
		LOG("Glew error: " << (const char*)glewGetErrorString(err));
		return false;
	}
	
	return true;
}

template <>
bool GfxAccelAtom<SdlCpuGfx>::GfxRenderer() {
	fb_stride = 3;
	SDL_Texture* fb = SDL_CreateTexture(nat_rend, SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_STREAMING, screen_sz.cx, screen_sz.cy);
	if (!fb) {
		LOG("error: couldn't create framebuffer texture");
		return false;
	}
	
	SDL_SetRenderTarget(nat_rend, fb);
	
	auto& rend_fb = rend.GetFramebuffer();
	rend_fb.Init(fb, screen_sz.cx, screen_sz.cy, fb_stride);
	rend_fb.SetWindowFbo();
	
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





#if 0
/* TODO remove these */
#endif

template <>
void GfxAccelAtom<X11OglGfx>::GfxFlags(uint32& flags) {
	is_opengl = true;
}

template <>
bool GfxAccelAtom<X11OglGfx>::GfxRenderer() {
	return true;
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
	
	
	String env_name = ws.Get(".env");
	if (!env_name.IsEmpty()) {
		SpaceRef l = a.GetSpace();
		env = l->FindNearestState(env_name);
		if (!env) {
			LOG("GfxAccelAtom<Gfx>::Initialize: error: environment state with name '" << env_name << "' not found");
			return false;
		}
	}
	
	close_machine = ws.Get(".close_machine") == "true";
		
	
	Buffer& buf = GetBuffer();
	buf.SetEnvState(env);
	buf.AddLink(ws.Get(".link"));
	
	String loopback = ws.Get(".loopback");
	if (loopback.GetCount() && !buf.SetLoopback(loopback)) {
		LOG("GfxAccelAtom<Gfx>::Initialize: error: assigning loopback failed");
		return false;
	}
	
	String fragment_path = ws.Get(".fragment");
	String vertex_path = ws.Get(".vertex");
	String library_path = ws.Get(".library");
	if (fragment_path.IsEmpty()) fragment_path = ws.Get(".filepath");
	
	SetShaderFile(fragment_path, vertex_path, library_path);
	SetFragmentShader(ws.Get(".fragshader"));
	SetVertexShader(ws.Get(".vtxshader"));
	Sizeable(ws.Get(".sizeable") == "true");
	Maximize(ws.Get(".maximize") == "true");
	Fullscreen(ws.Get(".fullscreen") == "true");
	
	// ShaderBase duplicate
	for(int i = 0; i < 4; i++) {
		String key = ".buf" + IntStr(i);
		String value = ws.Get(key);
		if (value.IsEmpty())
			;
		else if (value == "volume")
			buf.SetInputVolume(i);
		else if (value == "cubemap")
			buf.SetInputCubemap(i);
		else
			TODO
	}
	
	a.AddAtomToUpdateList();
	
	//AtomBase::GetMachine().template Get<AtomSystem>()->AddPolling(AtomBase::AsRefT());
	ISinkRef sink = a.GetSink();
	sink->GetValue(0).SetMaxQueueSize(1);
	
	if (poller) {
		int sink_count = sink->GetSinkCount();
		for(int i = 0; i < sink_count; i++)
			if (IsDefaultGfxVal<Gfx>(sink->GetValue(i).GetFormat().vd.val))
				poller->SetFinalizeOnSide();
	}
	else {
		TODO // check if ok
	}
	
	return true;
}

template <class Gfx>
void GfxAccelAtom<Gfx>::Uninitialize() {
	ab->RemoveAtomFromUpdateList();
}

template <class Gfx>
bool GfxAccelAtom<Gfx>::Open() {
	AppFlags& app_flags = GetAppFlags();
	is_sw = false;
	is_opengl = false;
	is_dx11 = false;
	
	
	// Window
	screen_sz = desired_rect.GetSize();
	uint32 flags = 0;
	
	GfxFlags(flags);
	
	if (!Gfx::CreateWindowAndRenderer(screen_sz, flags, win, nat_rend)) {
		LOG("GfxAccelAtom<Gfx>::Open: error: could not create window and renderer");
        return false;
	}
	Gfx::SetTitle(display, win, title);
    
    GfxRenderer();
	
	#ifdef flagDEBUG
	Gfx::SetDebugOutput(true);
	#endif
	
	if (full_screen)
		Gfx::SetWindowFullscreen(win);
	
	if (frag_path.GetCount())
		is_user_shader = true;
	
	if (AcceptsOrder()) {
		if (!this->ImageInitialize()) {
			LOG("GfxAccelAtom<Gfx>::Open: error: could not initialize image");
			return false;
		}
	}
	
	return true;
}

template <class Gfx>
bool GfxAccelAtom<Gfx>::ImageInitialize() {
	auto& fb = buf.fb;
	fb.is_win_fbo = true;
	fb.size = screen_sz;
	fb.fps = 60;
	
	frag_path = RealizeShareFile(frag_path);
	vtx_path = RealizeShareFile(vtx_path);
	
	if (frag_shdr.GetCount()) {
		if (!buf.LoadBuiltinShader(GVar::FRAGMENT_SHADER, frag_shdr)) {
			LOG("Screen::ImageInitialize: error: fragment shader loading failed from '" + frag_shdr + "'");
			return false;
		}
	}
	else if (frag_path.GetCount()) {
		if (!buf.LoadShaderFile(GVar::FRAGMENT_SHADER, frag_path, library_paths)) {
			LOG("Screen::ImageInitialize: error: fragment shader loading failed from '" + frag_path + "'");
			return false;
		}
	}
	else {
		LOG("Screen::ImageInitialize: error: no fragment shade given");
		return false;
	}
	
	if (vtx_shdr.GetCount()) {
		if (!buf.LoadBuiltinShader(GVar::VERTEX_SHADER, vtx_shdr)) {
			LOG("Screen::ImageInitialize: error: vertex shader loading failed from '" + vtx_shdr + "'");
			return false;
		}
	}
	else if (vtx_path.GetCount()) {
		if (!buf.LoadShaderFile(GVar::VERTEX_SHADER, vtx_path, library_paths)) {
			LOG("Screen::ImageInitialize: error: fragment vertex loading failed from '" + frag_path + "'");
			return false;
		}
	}
	
	if (!buf.Initialize()) {
		LOG("Screen::ImageInitialize: error: " << buf.GetError());
		return false;
	}
	
	return true;
}

template <class Gfx>
void GfxAccelAtom<Gfx>::Close() {
	fb_packet = 0;
	
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
	auto& buf = this->buf;
	
	BeginDraw();
	
	if (fb_packet) {
		Format fmt = fb_packet->GetFormat();
		const auto& vfmt = Gfx::GetFormat(fmt);
		const InternalPacketData& d = fb_packet->GetData<InternalPacketData>();
		ShaderPipeline& sd = *(ShaderPipeline*)d.ptr;
		BeginDraw();
		FrameCopy(vfmt, (const byte*)d.ptr, d.count);
		CommitDraw();
		fb_packet = 0;
	}
	else {
		buf.Process(cfg);
	}
	
	CommitDraw();
}

template <class Gfx>
bool GfxAccelAtom<Gfx>::Recv(int ch_i, PacketValue& p) {
	auto& buf = this->buf;
	bool succ = true;
	Format fmt = p.GetFormat();
	if (IsDefaultGfxVal<Gfx>(fmt.vd.val)) {
		const auto& vfmt = Gfx::GetFormat(fmt);
		
		if (p.IsData<InternalPacketData>()) {
			const InternalPacketData& d = p.GetData<InternalPacketData>();
			
			if (!d.ptr) {
				ASSERT_(0, "no pointer in InternalPacketData");
			}
			else if (d.IsText("gfxstate")) {
				DataState& sd = *(DataState*)d.ptr;
				buf.SetDataStateOverride(&sd);
			}
			else if (d.IsText("gfxvector")) {
				fb_packet = &p;
			}
			else if (d.IsText("gfxbuf")) {
				Size3 sz = vfmt.GetSize();
				int base = ab->GetSink()->GetSinkCount() > 1 ? 1 : 0;
				if (p.IsData<InternalPacketData>()) {
					succ = buf.LoadOutputLink(sz, ch_i - base, d);
				}
				else {
					RTLOG("Screen::Recv: cannot handle packet: " << p.ToString());
				}
			}
			else {
				DUMP(d.GetText());
				TODO // some old class pushing ptr without txt?
			}
		}
	}
	else if (fmt.IsOrder() && AcceptsOrder()) {
		// pass
	}
	else {
		DUMP(fmt);
		//RTLOG("Screen::Render: error: unexpected packet: " << last_packet->ToString());
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


#ifdef flagSDL2
template class GfxAccelAtom<SdlOglGfx>;
template class GfxAccelAtom<SdlCpuGfx>;
#endif


GFX_EXCPLICIT_INITIALIZE_CLASS(GfxAccelAtom)


NAMESPACE_PARALLEL_END
