#include "OOSDL2.h"

#ifdef flagGUI

NAMESPACE_SDL2_BEGIN


bool __enable_opengl_debug;

void GLAPIENTRY
OpenGLMessageCallback( GLenum source,
                 GLenum type,
                 GLuint id,
                 GLenum severity,
                 GLsizei length,
                 const GLchar* message,
                 const void* userParam )
{
	if (!__enable_opengl_debug)
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

void EnableOpenGLDebugMessages(bool b) {__enable_opengl_debug = b;}



Size Screen::GetSize() {
	int w, h;
	SDL_GetWindowSize(win, &w, &h);
	return Size(w, h);
}

bool Screen::Open0() {
	AppFlags& app_flags = GetAppFlags();
	is_opengl = app_flags.IsOpenGL();
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
	
	// Software framebuffer
	/*if (app_flags.IsSoftwareRenderer()) {
		int fb_stride = 3;
		SDL_Texture* fb = SDL_CreateTexture(rend, SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_STREAMING, screen_sz.cx, screen_sz.cy);
		if (!fb) {
			LOG("error: couldn't create framebuffer texture");
		}
		
		data->sw_rend.GetOutputSoftFramebuffer().Init(fb, screen_sz.cx, screen_sz.cy, fb_stride);
	}*/
	
    // Fullscreen
	#if defined flagDX12_PBR || defined flagOPENGL_PBR
	if (full_screen)
		SDL_SetWindowFullscreen(win, SDL_WINDOW_FULLSCREEN);
	#endif
	
	
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
		sw_rend.screen_sz = screen_sz;
	    sw_rend.win = win;
	    sw_rend.rend = this->rend;
	    sw_rend.PreFrame();
	    sw_draw.rend = &sw_rend;
	    sw_draw.fb = &sw_rend.GetOutputCpuFramebuffer();
	    sysdraw.ptr = &sw_draw;
	    
	    sw_draw.fb->Enter();
	}
	
	return sysdraw;
}

void Screen::CommitDraw() {
	AppFlags& flags = GetAppFlags();
	if (flags.IsSoftwareRenderer()) {
		sw_draw.fb->Leave();
		sw_rend.PostFrame();
	}
	else if (flags.IsOpenGL()) {
		hw_draw.fb->Leave();
		hw_rend.PostFrame();
	}
}



NAMESPACE_SDL2_END

#endif
