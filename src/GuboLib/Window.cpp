#include "GuboCore.h"

NAMESPACE_TOPSIDE_BEGIN

AtomVirtualGui3D::AtomVirtualGui3D()
{
	
}

AtomVirtualGui3D::~AtomVirtualGui3D()
{
	Destroy();
}

dword AtomVirtualGui3D::GetOptions()
{
	return GUI_SETMOUSECURSOR;
}

Size AtomVirtualGui3D::GetSize()
{
	ASSERT(mgr);
	if (mgr)
		return mgr->GetSize();
	return Size(0,0);
}

bool AtomVirtualGui3D::Create(const Rect& rect, const char *title)
{
	Machine& mach = TS::Serial::GetActiveMachine();
	wins = mach.Get<WindowSystem>();
	if (!wins)
		return false;
	
	mgr = wins->GetActiveScope();
	if (!mgr)
		return false;
	
	Size mgr_rect = rect.GetSize();
	mgr->SetFrameBox(mgr_rect);
	
	return true;
}

//extern SDL_TimerID waketimer_id;

void AtomVirtualGui3D::Destroy()
{
	mgr.Clear();
	wins.Clear();
}

/*void AtomVirtualGui3D::Attach(SDL_Window *win_, SDL_GLContext glcontext_)
{
	win = win_;
	glcontext = glcontext_;
}

void AtomVirtualGui3D::Detach()
{
	win = NULL;
	glcontext = NULL;
}*/

void AtomVirtualGui3D::Quit()
{
	
}

NAMESPACE_TOPSIDE_END