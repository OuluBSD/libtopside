#include "Atom.h"

namespace Upp {

SystemDraw& AtomVirtualGui::BeginDraw()
{
	idraw.Clear();
	idraw = new ImageDraw(GetSize());
	sysdraw.SetTarget(&*idraw);
	return sysdraw;
}

void AtomVirtualGui::CommitDraw()
{
	//gldraw.Finish();
	//SDL_GL_SwapWindow(win);
}

};