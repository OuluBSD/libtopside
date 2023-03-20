#ifndef _GuboLib_Atom_h
#define _GuboLib_Atom_h

NAMESPACE_TOPSIDE_BEGIN
	
struct AtomVirtualGui3D : VirtualGui3D {
	#if IS_TS_CORE
	RTTI_DECL1(AtomVirtualGui3D, VirtualGui3D)
	#endif
	
	virtual dword       GetOptions();
	virtual dword       GetMouseButtons();
	virtual dword       GetModKeys();
	virtual bool        IsMouseIn();
	virtual bool        ProcessEvent(bool *quit);
	virtual void        SetMouseCursor(const Image& image);
	Size        GetSize() override;
	void        WaitEvent(int ms) override;
	bool        IsWaitingEvent() override;
	void        WakeUpGuiThread() override;
	SystemDraw& BeginDraw() override;
	void        CommitDraw() override;
	bool        Poll(UPP::CtrlEvent& e) override;
	void        SetTitle(String title) override;
	uint32      GetTickCount() override;

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

void RunVirtualGui3D(VirtualGui3D& gui, Event<> app_main);


NAMESPACE_TOPSIDE_END

#endif
