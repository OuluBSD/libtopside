#include "Internal.h"

#if HAVE_WINDOWSYSTEM

NAMESPACE_UPP

void Ctrl::EventLoopIteration(double dt, bool* quit) {
	ProcessEvents(dt, quit);
}

bool Ctrl::ProcessEvents(double dt, bool *quit) {
	bool ret = ProcessEvent(quit);
	while(ProcessEvent(quit))
		;
	TimerProc(dt);
	return ret;
}

bool Ctrl::ProcessEvent(bool *quit) {
	LLOG("@ ProcessEvent");
	ASSERT(IsMainThread());
	//if(!GetMouseLeft() && !GetMouseRight() && !GetMouseMiddle())
	//	ReleaseCtrlCapture();
	
	bool ret = false;
	//ret = VirtualGui3DPtr->ProcessEvent(quit);
	
	//DefferedFocusSync();
	//SyncCaret();
	//SyncTopWindows();
	return ret;
}

void Ctrl::TimerProc(double dt) {
	static double total_dt;
	total_dt += dt;
	uint32 diff = total_dt * 1000UL;
	if (diff > 0) {
		AddGlobalTicks(diff);
		total_dt = 0;
	}
}

#if 0

void Ctrl::SetDesktopSize(Size sz) {
	LOG("todo: SetDesktopSize " << sz.ToString());
}

void Ctrl::EventLoop(Ctrl *ctrl) {
	/*bool quit = false;
	TimeStop t;
	TS::Machine& mach = TS::GetMachine();
	ProcessEvents(&quit);
	while (!quit && !Thread::IsShutdownThreads() && mach.IsRunning()) {
		double dt = t.ResetSeconds();
	    mach.Update(dt);
		//SyncCaret();
		GuiSleep(20);
		ProcessEvents(&quit);
	}*/
	TODO
}

void Ctrl::GuiSleep(int ms) {
	GuiLock __;
	ASSERT(IsMainThread());
	LLOG("GuiSleep");
	int level = LeaveGuiMutexAll();
	VirtualGui3DPtr->WaitEvent(ms);
	EnterGuiMutex(level);
}

void Ctrl::DoPaint() {
	SystemDraw& draw = VirtualGui3DPtr->BeginDraw();
	PaintScene(draw);
	//PaintCaretCursor(draw);
	VirtualGui3DPtr->CommitDraw();
}

void Ctrl::PaintScene(SystemDraw& draw) {
	CastPtr<SDL2GUI3D>(draw.gui)->Render(invalid);
	invalid = false;
}

#endif

void Ctrl::Invalidate() {
	using namespace TS;
	static Ref<Ecs::WindowSystem> win;
	if (!win) {
		TODO
		/*win = GetActiveMachine().Get<Ecs::WindowSystem>();
		if (win)
			win->Invalidate();*/
	}
	else
		win->Invalidate();
}

END_UPP_NAMESPACE

#endif
