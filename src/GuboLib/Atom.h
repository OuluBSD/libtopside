#ifndef _GuboLib_Atom_h
#define _GuboLib_Atom_h

NAMESPACE_TOPSIDE_BEGIN
	
struct AtomVirtualGui3D : VirtualGui3D {
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
	virtual bool        Poll(UPP::CtrlEvent& e);
	virtual void        SetTitle(String title);
	virtual uint32      GetTickCount();

	virtual void        Quit();
	//virtual void        HandleSDLEvent(SDL_Event* event);
	
	SystemDraw          sysdraw;
	
	Gu::SurfaceSystemRef	wins;
	Gu::SurfaceManagerRef	mgr;
	
	void SetTarget(Draw& d);
	//void Attach(SDL_Window *win, SDL_GLContext glcontext);
	//void Detach();

	bool Create(const Rect& rect, const char *title);
	void Destroy();
	
	
	AtomVirtualGui3D();
	~AtomVirtualGui3D();
};

void RunVirtualGui(VirtualGui3D& gui, Event<> app_main);


NAMESPACE_TOPSIDE_END

#endif
