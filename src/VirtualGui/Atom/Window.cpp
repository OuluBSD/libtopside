#include "Atom.h"

namespace UPP {

AtomVirtualGui::AtomVirtualGui()
{
	
}

AtomVirtualGui::~AtomVirtualGui()
{
	Destroy();
}

dword AtomVirtualGui::GetOptions()
{
	return GUI_SETMOUSECURSOR;
}

Size AtomVirtualGui::GetSize()
{
	ASSERT(mgr);
	if (mgr)
		return mgr->GetSize();
	return Size(0,0);
}

bool AtomVirtualGui::Create(const Rect& rect, const char *title)
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

void AtomVirtualGui::Destroy()
{
	mgr.Clear();
	wins.Clear();
}

/*void AtomVirtualGui::Attach(SDL_Window *win_, SDL_GLContext glcontext_)
{
	win = win_;
	glcontext = glcontext_;
}

void AtomVirtualGui::Detach()
{
	win = NULL;
	glcontext = NULL;
}*/

void AtomVirtualGui::Quit()
{
	
}

}