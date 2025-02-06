#include "GuboLib.h"

NAMESPACE_TOPSIDE_BEGIN

void AtomVirtualGui3D::SetTarget(Draw& d) {
	#if IS_TS_CORE
	sysdraw.SetTarget(&d);
	#else
	Panic("TODO");
	#endif
}

SystemDraw& AtomVirtualGui3D::BeginDraw()
{
	#if IS_TS_CORE
	return sysdraw;
	#else
	SystemDraw* sd = 0;
	Panic("TODO");
	return *sd;
	#endif
}

void AtomVirtualGui3D::CommitDraw()
{
	//gldraw.Finish();
	//SDL_GL_SwapWindow(win);
}

NAMESPACE_TOPSIDE_END
