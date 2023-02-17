#ifndef _AtomVirtualGui_AtomVirtualGui_h
#define _AtomVirtualGui_AtomVirtualGui_h

#include <CtrlLib/CtrlLib.h>
#include <SerialLib/SerialLib.h>

namespace Upp {
using namespace TS;
using namespace TS::Serial;
	
struct AtomVirtualGui : VirtualGui {
	virtual dword       GetOptions();
	virtual Size        GetSize();
	virtual dword       GetMouseButtons();
	virtual dword       GetModKeys();
	virtual bool        IsMouseIn();
	virtual bool        ProcessEvent(bool *quit);
	virtual void        WaitEvent(int ms);
	virtual bool        IsWaitingEvent();
	virtual void        WakeUpGuiThread();
	virtual void        SetMouseCursor(const Image& image);
	virtual SystemDraw& BeginDraw();
	virtual void        CommitDraw();

	virtual void        Quit();
	//virtual void        HandleSDLEvent(SDL_Event* event);
	
	SystemDraw          sysdraw;
	
	WindowSystemRef		wins;
	WindowManagerRef	mgr;
	
	void SetTarget(Draw& d);
	//void Attach(SDL_Window *win, SDL_GLContext glcontext);
	//void Detach();

	bool Create(const Rect& rect, const char *title);
	void Destroy();
	
	AtomVirtualGui();
	~AtomVirtualGui();
};

};

#endif
