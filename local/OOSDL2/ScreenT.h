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
    NatRend*				rend = NULL;
    //NatFrameBuf*			fb = NULL;
    SDL_RendererInfo		rend_info;
    Rect					desired_rect;
	Size					screen_sz;
	String					title;
	SDL_GLContext			glcontext = 0;
	Renderer				hw_rend;
	StateDraw				hw_draw;
	SystemDraw				sysdraw;
	Packet					last_packet;
	bool is_opengl = false;
	bool is_dx11 = false;
	bool full_screen = false;
	bool is_maximized = false;
	bool is_sizeable = false;
	bool mouse_captured = false;
	bool is_buf = false;
	String frag_path;
	String vtx_path;
	String library_paths;
	
	bool Open0() override {
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
			Gfx::SetDebugOutput(true);
			#endif
		}
		
	    // Fullscreen
		#if defined flagDX12_PBR || defined flagOPENGL_PBR
		if (full_screen)
			SDL_SetWindowFullscreen(win, SDL_WINDOW_FULLSCREEN);
		#endif
		
		
		if (frag_path.GetCount())
			is_buf = true;
		
		if (is_buf) {
			if (!this->ImageInitialize())
				return false;
		}
		
		return true;
	}
	
	bool ImageInitialize() {
		ASSERT(this->buf)
		if (!this->buf) return false;
		
		Buffer& buf = *this->buf;
		auto& fb = buf.fb;
		fb.is_win_fbo = true;
		fb.size = screen_sz;
		fb.fps = 60;
		
		if (frag_path.GetCount()) {
			if (!buf.LoadShaderFile(GVar::FRAGMENT_SHADER, frag_path, library_paths)) {
				LOG("Screen::ImageInitialize: error: fragment shader loading failed from '" + frag_path + "'");
				return false;
			}
		}
		else {
			buf.rt.SetCode(GVar::FRAGMENT_SHADER, def_shader);
		}
		
		if (vtx_path.GetCount()) {
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
	
	void Close0() override {
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
	}
	
	
	uint32 GetInitFlag() const override {return SDL_INIT_VIDEO;}
	
	void SetWindowRect(Rect r);
	
public:
	ScreenT(Context* ctx, AtomBase* ab) : Component(ctx, ab) {desired_rect = RectC(0,0,1280,720);}
	
	void Maximize(bool b=true) {
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
	void Fullscreen(bool b=true) {
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
	
	ScreenT& Sizeable(bool b=true) {is_sizeable = b; return *this;}
	
	void SetTitle(String title) {
		this->title = title;
		if (IsOpen() && win)
			SDL_SetWindowTitle(win, title);
	}
	
	void SetRect(Rect r) {
		desired_rect = r;
		if (IsOpen() && win && !full_screen) {
			SDL_SetWindowPosition(win, r.left, r.top);
			SDL_SetWindowSize(win, r.Width(), r.Height());
		}
	}
	
	void Render(const RealtimeSourceConfig& cfg) {
		auto& buf = this->buf;
		
		if (!last_packet) {
			RTLOG("Screen::Render: warning: cannot render without packet");
			return;
		}
		
		
		ASSERT(last_packet);
		Format fmt = last_packet->GetFormat();
		if (fmt.IsFbo()) {
			RTLOG("Screen::Render: from video packet: " << last_packet->ToString());
			const VideoFormat& vfmt = fmt.vid;
			
			if (last_packet->IsData<InternalPacketData>()) {
				const InternalPacketData& d = last_packet->GetData<InternalPacketData>();
				
				if (!d.ptr) {
					ASSERT_(0, "no pointer in InternalPacketData");
				}
				else if (d.IsText("oglstate")) {
					Framebuffer& sd = *(Framebuffer*)d.ptr;
					
					BeginDraw();
					
					TODO // process state with buf & require valid shader and pipeline in buf
					
					CommitDraw();
				}
				else if (d.IsText("oglpipe")) {
					ShaderPipeline& sd = *(ShaderPipeline*)d.ptr;
					
					BeginDraw();
					
					if (is_buf)
						TODO // merge external pipeline and Buffer pipeline?
					
					ASSERT(buf);
					if (buf)
						buf->Process(sd);
					
					CommitDraw();
				}
				else
					TODO
			}
			else {
				BeginDraw();
				
				ASSERT(!is_buf || buf);
				if (is_buf && buf) {
					buf->Process(cfg);
				}
				else {
					RTLOG("Screen::Render: error: no ogl buf");
				}
				
				CommitDraw();
			}
		}
		else if (fmt.IsOrder() && is_buf) {
			RTLOG("Screen::Render: from order packet: " << last_packet->ToString());
			BeginDraw();
			buf->Process(cfg);
			CommitDraw();
		}
		else {
			RTLOG("Screen::Render: error: unexpected packet: " << last_packet->ToString());
			
		}
		
		last_packet.Clear();
	}
	
	bool Recv(int ch_i, const Packet& p) {
		auto& buf = this->buf;
		bool succ = true;
		Format fmt = p->GetFormat();
		if (fmt.IsFbo()) {
			Size3 sz = fmt.fbo.GetSize();
			int base = ab->GetSink()->GetSinkCount() > 1 ? 1 : 0;
			if (p->IsData<InternalPacketData>()) {
				succ = buf->LoadOutputLink(sz, ch_i - base, p->GetData<InternalPacketData>());
			}
			else {
				RTLOG("Screen::Recv: cannot handle packet: " << p->ToString());
			}
		}
		
		if (ch_i == 0)
			last_packet = p;
		
		return succ;
	}
	
	SystemDraw& BeginDraw() {
		AppFlags& flags = GetAppFlags();
		if (is_opengl) {
		    hw_rend.win = win;
		    hw_rend.rend = this->rend;
			hw_rend.SetSize(screen_sz);
		    hw_rend.PreFrame();
		    //hw_draw.rend = &hw_rend;
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
	
	void CommitDraw() {
		AppFlags& flags = GetAppFlags();
		
		hw_draw.fb->Leave();
		hw_rend.PostFrame();
	}
	
	void SetBuffer(Buffer& buf) {this->buf = &buf;}
	
	Size GetSize() {return Gfx::GetWindowSize(*win);}
	bool IsCaptured() const {return mouse_captured;}
	
	void SetShaderFile(String frag_path, String vtx_path, String library_paths) {this->frag_path = frag_path; this->vtx_path = vtx_path; this->library_paths = library_paths;}
	void SetTestImage(bool b) {is_buf = b;}
	
};


NAMESPACE_SDL2_END

#endif
