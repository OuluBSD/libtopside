#include "GuboLib.h"

NAMESPACE_TOPSIDE_BEGIN

void AtomVirtualGui3D::SetTarget(Draw& d) {
	sysdraw.SetTarget(&d);
}

SystemDraw& AtomVirtualGui3D::BeginDraw()
{
	return sysdraw;
}

void AtomVirtualGui3D::CommitDraw()
{
	//gldraw.Finish();
	//SDL_GL_SwapWindow(win);
}

NAMESPACE_TOPSIDE_END
