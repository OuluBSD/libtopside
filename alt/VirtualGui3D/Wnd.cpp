#include <EcsLocal/EcsLocal.h>


NAMESPACE_UPP

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

bool Ctrl::ProcessEvents(bool *quit) {
	bool ret = ProcessEvent(quit);
	while(ProcessEvent(quit))
		;
	TimerProc(VirtualGui3DPtr->GetTickCount());
	//SweepMkImageCache();
	DoPaint();
	return ret;
}

bool Ctrl::ProcessEvent(bool *quit) {
	LLOG("@ ProcessEvent");
	ASSERT(IsMainThread());
	//if(!GetMouseLeft() && !GetMouseRight() && !GetMouseMiddle())
	//	ReleaseCtrlCapture();
	bool ret = VirtualGui3DPtr->ProcessEvent(quit);
	//DefferedFocusSync();
	//SyncCaret();
	//SyncTopWindows();
	return ret;
}

/*void Ctrl::TimerProc(dword time) {
	uint32 ticks = SDL_GetTicks();
	uint32 diff = ticks - prev_ticks;
	if (diff > 0) {
		AddGlobalTicks(diff);
		prev_ticks = ticks;
	}
}*/

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
