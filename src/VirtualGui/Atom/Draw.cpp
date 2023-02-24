#include "Atom.h"

namespace UPP {

void AtomVirtualGui::SetTarget(Draw& d) {
	sysdraw.SetTarget(&d);
}

SystemDraw& AtomVirtualGui::BeginDraw()
{
	return sysdraw;
}

void AtomVirtualGui::CommitDraw()
{
	//gldraw.Finish();
	//SDL_GL_SwapWindow(win);
}

};
