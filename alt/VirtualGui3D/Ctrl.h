//$ class Ctrl {
	static Topside::Windows* wm;
	
	//static bool           invalid;
	//static uint32 prev_ticks;
	
	//static void TimerProc(dword time);
	//static void GuiSleep(int ms);
	//static void DoPaint();
	//static void PaintScene(SystemDraw& draw);
	
public:
	//static void InitFB();
	//static void ExitFB();
	//static void SetDesktopSize(Size sz);
	static void Invalidate();
	
	Topside::CoreWindow* GetWindow();
	static Topside::Windows* GetWindows();
	
	static void SetWindows(Topside::Windows* wm) {ASSERT(!Ctrl::wm); Ctrl::wm = wm;}
	
//$ };
