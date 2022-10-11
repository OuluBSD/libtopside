#ifndef _CtrlCore_WindowManager_h_
#define _CtrlCore_WindowManager_h_

#ifdef flagGUI

NAMESPACE_ECS_BEGIN


class WindowManager {
	
protected:
	friend class WindowSystem;
	
	Array<Windows> screens;
	Array<TopWindow> owned_wins;
	RunningFlag flag;
	Mutex lock;
	
	
public:
	WindowManager();
	~WindowManager() {Close();}
	
	void Close();
	
	template <class T>
	T& AddScreen() {
		ASSERT_(screens.IsEmpty(), "only 1 screen support is implemented for now: see static Ctrl::SetWindows");
		T* t = new T();
		t->wm = this;
		if (!t->Init())
			throw Exc("Screen init failed");
		lock.Enter();
		screens.Add(t);
		lock.Leave();
		return *t;
	}
	
	
	void CloseWindow(TopWindow* tw);
	void Shutdown();
	
	void Run();
	
	
	int GetScreenCount() const {return screens.GetCount();}
	Windows& GetScreen(int i) {return screens[i];}
	
};






NAMESPACE_ECS_END

#endif
#endif
