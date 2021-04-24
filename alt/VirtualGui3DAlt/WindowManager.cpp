#if 0
#include <EcsLib/EcsLib.h>


NAMESPACE_OULU_BEGIN


WindowManager::WindowManager() {
	
}

void WindowManager::Run() {
	flag.Start();
	
	
	while (flag.IsRunning()) {
		
		for(int i = 0; i < screens.GetCount(); i++) {
			Screen& s = screens[i];
			
			Event e;
			while (s.Poll(e)) {
				
				if (e.type == EVENT_SHUTDOWN)
					flag.SetNotRunning();
				
			}
			s.ProcessCloseQueue();
			
			s.Render();
		}
		
		Sleep(1);
	}
	
	
	flag.SetStopped();
}

void WindowManager::Close() {
	for(int i = 0; i < screens.GetCount(); i++) {
		Windows* wins = dynamic_cast<Windows*>(&screens[i]);
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






NAMESPACE_OULU_END

#endif
