#ifndef _SDL2GUI3D_SDL2GUI3D_h
#define _SDL2GUI3D_SDL2GUI3D_h

#include <CtrlLib/CtrlLib.h>
#include <GLDraw/GLDraw.h>

#ifdef PLATFORM_POSIX
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif

namespace UPP {
	
struct SDL2GUI3D : VirtualGui3D {
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

	SDL_Window   *win;
	SDL_GLContext glcontext;
	int64         serial;
	GLDraw        gldraw;
	SystemDraw    sysdraw;

	void Attach(SDL_Window *win, SDL_GLContext glcontext);
	void Detach();

	bool Create(const Rect& rect, const char *title);
	void Destroy();
	
	SDL2GUI3D();
	~SDL2GUI3D();
};


#define GUI_APP_MAIN \
void GuiMainFn_(); \
\
extern "C" int main(int argc, char *argv[]) {\
	UPP::AppInit__(argc, (const char **)argv); \
	SDL2GUI3D gui; \
	gui.Create(Rect(0, 0, 1920, 1000), "Virtual Gui Test"); \
	VirtualGui3DPtr = &gui; \
	Ctrl::InitFB(); \
	Ctrl::SetDesktopSize(gui.GetSize()); \
	GuiMainFn_(); \
	Ctrl::ExitFB(); \
	Ctrl::CloseTopCtrls(); \
	return ::UPP::GetExitCode(); \
} \
\
void GuiMainFn_()


}

#endif
