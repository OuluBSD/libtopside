//$ class Ctrl {
	static TS::Ecs::Windows* wm;
	
	//static bool           invalid;
	//static uint32 prev_ticks;
	
	static void TimerProc(double dt);
	//static void GuiSleep(int ms);
	//static void DoPaint();
	//static void PaintScene(SystemDraw& draw);
	
public:
	//static void InitFB();
	//static void ExitFB();
	//static void SetDesktopSize(Size sz);
	static void Invalidate();
	
	TS::Ecs::CoreWindow* GetWindow();
	static TS::Ecs::Windows* GetWindows();
	
	static void SetWindows(TS::Ecs::Windows* wm) {ASSERT(!Ctrl::wm); Ctrl::wm = wm;}
	
//$ };
