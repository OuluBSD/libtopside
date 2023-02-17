#include "Atom.h"

namespace Upp {

void AtomVirtualGui::SetTarget(Draw& d) {
	sysdraw.SetTarget(&d);
}

SystemDraw& AtomVirtualGui::BeginDraw()
{
	#if 0
	gldraw.Init(GetSize(), (uint64)glcontext);
	sysdraw.SetTarget(&gldraw);
	#endif
	return sysdraw;
}

void AtomVirtualGui::CommitDraw()
{
	//gldraw.Finish();
	//SDL_GL_SwapWindow(win);
}

};
