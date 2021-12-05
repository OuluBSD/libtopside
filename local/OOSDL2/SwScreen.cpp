#include <AtomSDL2/AtomSDL2.h>

#ifdef flagSCREEN

NAMESPACE_SDL2_BEGIN


Size SwScreen::GetSize() {
	int w, h;
	SDL_GetWindowSize(win, &w, &h);
	return Size(w, h);
}

bool SwScreen::Open0() {
	AppFlags& app_flags = GetAppFlags();
	
	
	// Window
	screen_sz = desired_rect.GetSize();
	uint32 flags = 0;
	
	if (full_screen)	flags |= SDL_WINDOW_FULLSCREEN;
	if (is_sizeable)	flags |= SDL_WINDOW_RESIZABLE;
	if (is_maximized)	flags |= SDL_WINDOW_MAXIMIZED;
	
	if (SDL_CreateWindowAndRenderer(screen_sz.cx, screen_sz.cy, flags, &win, &rend) == -1)
        return false;
	SDL_SetWindowTitle(win, title);
    
    
	// Software framebuffer
	fb_stride = 3;
	SDL_Texture* fb = SDL_CreateTexture(rend, SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_STREAMING, screen_sz.cx, screen_sz.cy);
	if (!fb) {
		LOG("error: couldn't create framebuffer texture");
	}
	
	sw_rend.GetOutputCpuFramebuffer().Init(fb, screen_sz.cx, screen_sz.cy, fb_stride);
	
	
	return true;
}

void SwScreen::Close0() {
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

void SwScreen::Fullscreen(bool b) {
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

void SwScreen::Maximize(bool b) {
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

void SwScreen::SetTitle(String title) {
	this->title = title;
	if (IsOpen() && win)
		SDL_SetWindowTitle(win, title);
}

void SwScreen::SetRect(Rect r) {
	desired_rect = r;
	if (IsOpen() && win && !full_screen) {
		SDL_SetWindowPosition(win, r.left, r.top);
		SDL_SetWindowSize(win, r.Width(), r.Height());
	}
}

bool SwScreen::Recv(int ch_i, const Packet& p) {
	if (ch_i == 0)
		last_packet = p;
	// TODO: check if 'do render' packet, otherwise return false
	return true; // assuming 'do render' packet
}

void SwScreen::Render() {
	if (!last_packet) {
		RTLOG("SwScreen::Render: warning: cannot render without packet");
		return;
	}
	
	Packet& p = last_packet;
	Format fmt = p->GetFormat();
	if (fmt.IsVideo()) {
		const VideoFormat& vfmt = fmt.vid;
		int exp_size = screen_sz.GetArea() * fb_stride;
		int frame_size = fmt.vid.GetFrameSize();
		
		if (p->IsData<InternalPacketData>()) {
			const InternalPacketData& d = p->GetData<InternalPacketData>();
			
			if (d.IsText("cpustate") && d.ptr) {
				CpuFramebufferState& sd = *(CpuFramebufferState*)d.ptr;
				
				CpuShaderPipeline pipe;
				pipe.LoadState(sd);
				
				BeginDraw();
				sw_draw.DrawShaderPipeline(pipe);
				CommitDraw();
			}
			else if (d.ptr && d.count > 0 && d.count == frame_size) {
				const byte* b = (const byte*)d.ptr;
				int len = d.count;
				BeginDraw();
				sw_draw.DrawImageMemory(b, len, 0,0, vfmt.res[0], vfmt.res[1], vfmt.GetPackedSingleSize(), vfmt.GetPackedCount());
				CommitDraw();
			}
		}
		else {
			if (exp_size == frame_size) {
				const Vector<byte>& data = p->GetData();
				ASSERT(data.GetCount() == frame_size);
				
				BeginDraw();
				sw_draw.DrawImageMemory((const byte*)data.Begin(), data.GetCount(), 0,0, vfmt.res[0], vfmt.res[1], vfmt.GetPackedSingleSize(), vfmt.GetPackedCount());
				CommitDraw();
			}
			else {
				RTLOG("SwScreen::Render: error: got video packet with wrong frame size");
			}
		}
	}
	else if (fmt.IsProg()) {
		const InternalPacketData& d = p->GetData<InternalPacketData>();
		const DrawCommand* cmd = (const DrawCommand*)d.ptr;
		ASSERT(cmd);
		
		BeginDraw();
		
		DrawProg p;
		p.SetTarget(sw_draw);
		p.Process(cmd);
		
		CommitDraw();
	}
	else {
		TODO
	}
	
}

SystemDraw& SwScreen::BeginDraw() {
	AppFlags& flags = GetAppFlags();
	
	sw_rend.screen_sz = screen_sz;
    sw_rend.win = win;
    sw_rend.rend = this->rend;
    sw_rend.PreFrame();
    sw_draw.rend = &sw_rend;
    sw_draw.fb = &sw_rend.GetOutputCpuFramebuffer();
    sysdraw.ptr = &sw_draw;
    
    sw_draw.fb->Enter();
	
	return sysdraw;
}

void SwScreen::CommitDraw() {
	AppFlags& flags = GetAppFlags();
	
	sw_draw.fb->Leave();
	sw_rend.PostFrame();
}



NAMESPACE_SDL2_END

#endif
