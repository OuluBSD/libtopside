#include "SDL2GUI3D.h"

namespace UPP {

Size SDL2GUI3D::GetSize()
{
	int w, h;
	SDL_GetWindowSize(win, &w, &h);
	return Size(w, h);
}

bool SDL2GUI3D::Create(const Rect& rect, const char *title)
{
	SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER);

	win = SDL_CreateWindow(title, rect.left, rect.top, rect.GetWidth(), rect.GetHeight(),
	                       SDL_WINDOW_SHOWN|SDL_WINDOW_OPENGL|SDL_WINDOW_BORDERLESS);
	if(!win)
		return false;
	MemoryIgnoreLeaksBegin();
	glcontext = SDL_GL_CreateContext(win);
	MemoryIgnoreLeaksEnd();
	if(!glcontext) {
		Destroy();
		return false;
	}
	return true;
}

extern SDL_TimerID waketimer_id;

void SDL2GUI3D::Destroy()
{
	if(glcontext) {
		SDL_GL_DeleteContext(glcontext);
		glcontext = NULL;
		GLDraw::ResetCache();
	}
	if(win) {
		SDL_RemoveTimer(waketimer_id);
		SDL_DestroyWindow(win);
		win = NULL;
	}
}

void SDL2GUI3D::Attach(SDL_Window *win_, SDL_GLContext glcontext_)
{
	win = win_;
	glcontext = glcontext_;
}

void SDL2GUI3D::Detach()
{
	win = NULL;
	glcontext = NULL;
}

SDL2GUI3D::SDL2GUI3D()
{
	glcontext = NULL;
	win = NULL;
}

SDL2GUI3D::~SDL2GUI3D()
{
	Destroy();
	SDL_Quit();
}

void SDL2GUI3D::Quit()
{
//	SDL_Quit();
}

}