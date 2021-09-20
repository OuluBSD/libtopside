#include "OOSDL2.h"
#include <SerialCore/SerialCore.h>

#ifdef flagGUI

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
	
	is_test_image = true;
	
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
	
	
	if (is_test_image) {
		if (!TestImageInitialize())
			return false;
	}
	
	return true;
}

void Screen::Close0() {
	if (glcontext) {
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

bool Screen::Recv(Packet& p) {
	last_packet = p;
	return true; // assuming 'do render' packet
}

void Screen::Render(const RealtimeSourceConfig& cfg) {
	RTLOG("Screen::Render");
	Format fmt = last_packet->GetFormat();
	if (fmt.IsVideo()) {
		const VideoFormat& vfmt = fmt.vid;
		
		BeginDraw();
		
		if (is_test_image) {
			test_image.frames = cfg.src_frame;
			test_image.ProcessStage(cfg);
		}
		else
			;
		
		CommitDraw();
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
	    hw_draw.fb = &hw_rend.GetOutputOpenGLFramebuffer();
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


NAMESPACE_SDL2_END

#endif
