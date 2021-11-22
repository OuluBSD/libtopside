#include <AtomSDL2/AtomSDL2.h>

#ifdef flagSCREEN

NAMESPACE_SDL2_BEGIN



void GLAPIENTRY
OpenGLMessageCallback( GLenum source,
                 GLenum type,
                 GLuint id,
                 GLenum severity,
                 GLsizei length,
                 const GLchar* message,
                 const void* userParam )
{
	if (!IsGfxAccelDebugMessages())
		return;
	String s;
	s << "OpenGL debug: ";
	if (type == GL_DEBUG_TYPE_ERROR)
		s << "error: ";
	s << "type = " << HexStr(type);
	s << ", severity = " << HexStr(severity);
	s << ", message = " << String(message);
	LOG(s);
}




Size Screen::GetSize() {
	int w, h;
	SDL_GetWindowSize(win, &w, &h);
	return Size(w, h);
}

bool Screen::Open0() {
	AppFlags& app_flags = GetAppFlags();
	is_opengl = true;
	is_dx11 = false;
	
	
	// Window
	screen_sz = desired_rect.GetSize();
	uint32 flags = 0;
	
	if (is_opengl) {
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		flags |= SDL_WINDOW_OPENGL;
	}
	if (full_screen)	flags |= SDL_WINDOW_FULLSCREEN;
	if (is_sizeable)	flags |= SDL_WINDOW_RESIZABLE;
	if (is_maximized)	flags |= SDL_WINDOW_MAXIMIZED;
	
	if (SDL_CreateWindowAndRenderer(screen_sz.cx, screen_sz.cy, flags, &win, &rend) == -1)
        return false;
	SDL_SetWindowTitle(win, title);
    
    // Renderer
    SDL_GetRendererInfo(rend, &rend_info);
	if ((rend_info.flags & SDL_RENDERER_ACCELERATED) == 0 ||
        (rend_info.flags & SDL_RENDERER_TARGETTEXTURE) == 0)
        return false;
	
	// GL context
	if (is_opengl) {
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
		
		#ifdef flagDEBUG
		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback( OpenGLMessageCallback, 0 );
		#endif
		
	}
	
    // Fullscreen
	#if defined flagDX12_PBR || defined flagOPENGL_PBR
	if (full_screen)
		SDL_SetWindowFullscreen(win, SDL_WINDOW_FULLSCREEN);
	#endif
	
	
	if (frag_path.GetCount())
		is_ogl_buf = true;
	
	if (is_ogl_buf) {
		if (!ImageInitialize())
			return false;
	}
	
	return true;
}

void Screen::Close0() {
	last_packet.Clear();
	
	if (glcontext) {
		GetAppFlags().SetOpenGLContextOpen(false);
		SDL_GL_DeleteContext(glcontext);
		glcontext = 0;
	}
	if (rend) {
		SDL_DestroyRenderer(rend);
		rend = 0;
	}
	if (win) {
		SDL_DestroyWindow(win);
		win = 0;
	}
	if (fb) {
        SDL_DestroyTexture(fb);
        fb = 0;
    }
}

void Screen::Fullscreen(bool b) {
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

void Screen::Maximize(bool b) {
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

void Screen::SetTitle(String title) {
	this->title = title;
	if (IsOpen() && win)
		SDL_SetWindowTitle(win, title);
}

void Screen::SetRect(Rect r) {
	desired_rect = r;
	if (IsOpen() && win && !full_screen) {
		SDL_SetWindowPosition(win, r.left, r.top);
		SDL_SetWindowSize(win, r.Width(), r.Height());
	}
}

bool Screen::Recv(int ch_i, const Packet& p) {
	bool succ = true;
	Format fmt = p->GetFormat();
	if (fmt.IsFbo()) {
		Size3 sz = fmt.fbo.GetSize();
		int base = ab->GetSink()->GetSinkCount() > 1 ? 1 : 0;
		if (p->IsData<InternalPacketData>()) {
			succ = ogl_buf->LoadOutputLink(sz, ch_i - base, p->GetData<InternalPacketData>());
		}
		else {
			RTLOG("Screen::Recv: cannot handle packet: " << p->ToString());
		}
	}
	
	if (ch_i == 0)
		last_packet = p;
	
	return succ;
}

void Screen::Render(const RealtimeSourceConfig& cfg) {
	if (!last_packet) {
		RTLOG("Screen::Render: warning: cannot render without packet");
		return;
	}
	
	
	ASSERT(last_packet);
	Format fmt = last_packet->GetFormat();
	if (fmt.IsFbo()) {
		RTLOG("Screen::Render: from video packet: " << last_packet->ToString());
		const VideoFormat& vfmt = fmt.vid;
		
		BeginDraw();
		
		ASSERT(!is_ogl_buf || ogl_buf);
		if (is_ogl_buf && ogl_buf) {
			ogl_buf->Process(cfg);
		}
		else {
			RTLOG("Screen::Render: error: no ogl buf");
		}
		
		CommitDraw();
	}
	else if (fmt.IsOrder() && is_ogl_buf) {
		RTLOG("Screen::Render: from order packet: " << last_packet->ToString());
		BeginDraw();
		ogl_buf->Process(cfg);
		CommitDraw();
	}
	else {
		RTLOG("Screen::Render: error: unexpected packet: " << last_packet->ToString());
		
	}
	
	last_packet.Clear();
}

SystemDraw& Screen::BeginDraw() {
	AppFlags& flags = GetAppFlags();
	if (is_opengl) {
		hw_rend.screen_sz = screen_sz;
	    hw_rend.win = win;
	    hw_rend.rend = this->rend;
	    hw_rend.PreFrame();
	    hw_draw.rend = &hw_rend;
	    hw_draw.fb = &hw_rend.GetFramebuffer();
	    sysdraw.ptr = &hw_draw;
	    
	    hw_draw.fb->Enter();
	}
	else if (is_dx11) {
		TODO
	}
	else {
		Panic("Screen internal error");
	}
	
	return sysdraw;
}

void Screen::CommitDraw() {
	AppFlags& flags = GetAppFlags();
	
	hw_draw.fb->Leave();
	hw_rend.PostFrame();
}








const char* def_shader = R"SH4D3R(
#define M_PI	3.1415926535897932384626433832795

void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
    vec3 res = iResolution;
    float t = iTime;
    bool mode = mod(t, 6.0) > 3.0;
    //t = t * 504;
    //t = t * 0.2;
    vec3 shift = vec3(
        sin(t),
        sin(t + M_PI/3.0),
        sin(t + M_PI*2.0/3.0));
    if (mode)
        fragColor = vec4(
            fragCoord.x / res.x + shift.x,
            fragCoord.y / res.y + shift.y,
            1.0 - fragCoord.y / res.y + shift.z, 0);
    else
        fragColor = vec4(fragCoord.y/res.y + shift.x, (shift.y + 1.0) * 0.5, fragCoord.x/res.x, 0);
}
)SH4D3R";



bool Screen::ImageInitialize() {
	ASSERT(ogl_buf)
	if (!ogl_buf) return false;
	
	OglBuffer& buf = *ogl_buf;
	auto& st = buf.state;
	st.is_win_fbo = true;
	st.size = screen_sz;
	st.fps = 60;
	
	if (frag_path.GetCount()) {
		if (!buf.LoadShaderFile(ShaderVar::PROG_FRAGMENT, frag_path, library_paths)) {
			LOG("Screen::ImageInitialize: error: fragment shader loading failed from '" + frag_path + "'");
			return false;
		}
	}
	else {
		buf.state.SetCode(ShaderVar::PROG_FRAGMENT, def_shader);
	}
	
	if (vtx_path.GetCount()) {
		if (!buf.LoadShaderFile(ShaderVar::PROG_VERTEX, vtx_path, library_paths)) {
			LOG("Screen::ImageInitialize: error: fragment vertex loading failed from '" + frag_path + "'");
			return false;
		}
	}
	
	if (!buf.Initialize()) {
		ctx->SetError(buf.GetError());
		return false;
	}
	
	return true;
}


NAMESPACE_SDL2_END

#endif
