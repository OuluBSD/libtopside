#include <AtomSDL2/AtomSDL2.h>


NAMESPACE_SDL2_BEGIN


template <>
void ScreenT<SdlOglGfx>::GfxFlags(uint32& flags) {
	is_opengl = true;
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	flags |= SDL_WINDOW_OPENGL;
}

template <>
void ScreenT<SdlCpuGfx>::GfxFlags(uint32& flags) {
	is_sw = true;
}

template <>
bool ScreenT<SdlOglGfx>::GfxRenderer() {
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
bool ScreenT<SdlCpuGfx>::GfxRenderer() {
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
void ScreenT<SdlCpuGfx>::FrameCopy(const VideoFormat& vfmt, const byte* mem, int len) {
	int frame_size = vfmt.GetFrameSize();
	if (mem && len > 0 && len == frame_size) {
		rend.GetFramebuffer().DrawFill(mem, len);
	}
}

template <class Gfx>
bool ScreenT<Gfx>::Open0() {
	AppFlags& app_flags = GetAppFlags();
	is_sw = false;
	is_opengl = false;
	is_dx11 = false;
	
	
	// Window
	screen_sz = desired_rect.GetSize();
	uint32 flags = 0;
	
	GfxFlags(flags);
	
	if (full_screen)	flags |= SDL_WINDOW_FULLSCREEN;
	if (is_sizeable)	flags |= SDL_WINDOW_RESIZABLE;
	if (is_maximized)	flags |= SDL_WINDOW_MAXIMIZED;
	
	if (SDL_CreateWindowAndRenderer(screen_sz.cx, screen_sz.cy, flags, &win, &nat_rend) == -1)
        return false;
	SDL_SetWindowTitle(win, title);
    
    GfxRenderer();
	
	#ifdef flagDEBUG
	Gfx::SetDebugOutput(true);
	#endif
	
	if (full_screen)
		SDL_SetWindowFullscreen(win, SDL_WINDOW_FULLSCREEN);
	
	if (frag_path.GetCount())
		is_user_shader = true;
	
	if (AcceptsOrder()) {
		if (!this->ImageInitialize())
			return false;
	}
	
	return true;
}

template <class Gfx>
bool ScreenT<Gfx>::ImageInitialize() {
	ASSERT(this->buf)
	if (!this->buf) return false;
	
	Buffer& buf = *this->buf;
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
		buf.rt.SetCode(GVar::FRAGMENT_SHADER, def_shader);
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
		SetContextError(ctx, buf.GetError());
		return false;
	}
	
	return true;
}

template <class Gfx>
void ScreenT<Gfx>::Close0() {
	fb_packet.Clear();
	
	if (glcontext) {
		GetAppFlags().SetOpenGLContextOpen(false);
		SDL_GL_DeleteContext(glcontext);
		glcontext = 0;
	}
	if (nat_rend) {
		SDL_DestroyRenderer(nat_rend);
		nat_rend = 0;
	}
	if (win) {
		SDL_DestroyWindow(win);
		win = 0;
	}
}

template <class Gfx>
void ScreenT<Gfx>::Maximize(bool b) {
	if (b == is_maximized)
		return;
	is_maximized = b;
	if (IsOpen() && win) {
		if (b)
			SDL_MaximizeWindow(win);
		else
			SDL_RestoreWindow(win);
	}
}

template <class Gfx>
void ScreenT<Gfx>::Fullscreen(bool b) {
	if (b == full_screen)
		return;
	full_screen = b;
	if (IsOpen() && win) {
		if (b)
			SDL_SetWindowFullscreen(win, SDL_WINDOW_FULLSCREEN);
		else
			SDL_SetWindowFullscreen(win, 0);
	}
}

template <class Gfx>
void ScreenT<Gfx>::SetTitle(String title) {
	this->title = title;
	if (IsOpen() && win)
		SDL_SetWindowTitle(win, title);
}

template <class Gfx>
void ScreenT<Gfx>::SetRect(Rect r) {
	desired_rect = r;
	if (IsOpen() && win && !full_screen) {
		SDL_SetWindowPosition(win, r.left, r.top);
		SDL_SetWindowSize(win, r.Width(), r.Height());
	}
}

template <class Gfx>
void ScreenT<Gfx>::Render(const RealtimeSourceConfig& cfg) {
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
		fb_packet.Clear();
	}
	else if (buf) {
		buf->Process(cfg);
	}
	else {
		RTLOG("Screen::Render: error: no gfx buf");
	}
	
	CommitDraw();
}

template <class Gfx>
bool ScreenT<Gfx>::Recv(int ch_i, const Packet& p) {
	auto& buf = this->buf;
	bool succ = true;
	Format fmt = p->GetFormat();
	if (IsDefaultGfxVal<Gfx>(fmt.vd.val)) {
		const auto& vfmt = Gfx::GetFormat(fmt);
		
		if (p->IsData<InternalPacketData>()) {
			const InternalPacketData& d = p->GetData<InternalPacketData>();
			
			if (!d.ptr) {
				ASSERT_(0, "no pointer in InternalPacketData");
			}
			else if (d.IsText("gfxstate")) {
				DataState& sd = *(DataState*)d.ptr;
				
				//ASSERT(!is_user_shader || buf);
				if (/*is_user_shader &&*/ buf) {
					buf->SetDataStateOverride(&sd);
				}
				else {
					RTLOG("Screen::Render: error: no gfx buf");
				}
			}
			else if (d.IsText("gfxvector")) {
				fb_packet = p;
			}
			else if (d.IsText("gfxbuf")) {
				Size3 sz = vfmt.GetSize();
				int base = ab->GetSink()->GetSinkCount() > 1 ? 1 : 0;
				if (p->IsData<InternalPacketData>()) {
					succ = buf->LoadOutputLink(sz, ch_i - base, d);
				}
				else {
					RTLOG("Screen::Recv: cannot handle packet: " << p->ToString());
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
		RTLOG("Screen::Render: error: unexpected packet: " << last_packet->ToString());
		ASSERT(0);
		succ = false;
	}
	
	return succ;
}

template <class Gfx>
SystemDraw& ScreenT<Gfx>::BeginDraw() {
	AppFlags& flags = GetAppFlags();
	if (is_opengl || is_sw) {
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
void ScreenT<Gfx>::CommitDraw() {
	AppFlags& flags = GetAppFlags();
	
	//draw.fb->Leave();
	rend.PostFrame();
}


template class ScreenT<SdlOglGfx>;
template class ScreenT<SdlCpuGfx>;


NAMESPACE_SDL2_END
