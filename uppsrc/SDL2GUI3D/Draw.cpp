#include "SDL2GUI3D.h"

namespace UPP {

SystemDraw& SDL2GUI3D::BeginDraw()
{
	gldraw.Init(GetSize(), (uint64)glcontext);
	sysdraw.SetTarget(&gldraw);
	return sysdraw;
}

void SDL2GUI3D::CommitDraw()
{
	gldraw.Finish();
	SDL_GL_SwapWindow(win);
}

};