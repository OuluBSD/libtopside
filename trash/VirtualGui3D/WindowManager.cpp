#if 0
#include "Internal.h"

#if HAVE_WINDOWSYSTEM

NAMESPACE_ECS_BEGIN


WindowManager::WindowManager() {
	
}

/*void WindowManager::Run() {
	flag.Start();
	
	
	while (flag.IsRunning()) {
		Update();
		Sleep(1);
	}
	
	
	flag.SetStopped();
}*/

void WindowManager::Update(double dt) {
	bool closed = false;
	
	for(int i = 0; i < screens.GetCount(); i++) {
		Workspace2D& s = screens[i];
		
		CtrlEvent e;
		while (s.Poll(e)) {
			
			if (e.type == EVENT_SHUTDOWN)
				flag.SetNotRunning();
			
		}
		closed = s.ProcessCloseQueue() || closed;
		
		s.Render();
	}
}

void WindowManager::Close() {
	for(int i = 0; i < screens.GetCount(); i++) {
		Windows* wins = CastPtr<Windows>(&screens[i]);
		if (wins) {
			wins->CloseAll();
			wins->ProcessCloseQueue();
		}
	}
	owned_wins.Clear();
	
	for(int i = screens.GetCount()-1; i >= 0; i--)
		screens[i].Shutdown();
	screens.Clear();
}

void WindowManager::CloseWindow(TopWindow* tw) {
	lock.Enter();
	for(int i = 0; i < owned_wins.GetCount(); i++) {
		if (&owned_wins[i] == tw) {
			owned_wins.Remove(i--);
		}
	}
	lock.Leave();
}

void WindowManager::Uninitialize() {
	for (Windows& w : screens) {
		w.CloseAll();
	}
	screens.Clear();
}






NAMESPACE_ECS_END

#endif
#endif
