#ifndef _CtrlCore_WindowManager_h_
#define _CtrlCore_WindowManager_h_

#if 0

NAMESPACE_TOPSIDE_BEGIN


class WindowManager {
	Array<Screen> screens;
	Array<TopWindow> owned_wins;
	RunningFlag flag;
	Mutex lock;
	
	
public:
	WindowManager();
	~WindowManager() {Close();}
	
	void Close();
	
	template <class T>
	T& AddScreen() {
		T* t = new T();
		t->wm = this;
		if (!t->Init())
			throw Exc("Screen init failed");
		lock.Enter();
		screens.Add(t);
		lock.Leave();
		return *t;
	}
	
	
	template <class T> T& AddWindow(int screen, T* obj_ptr) {
		lock.Enter();
		TopWindow* swc = obj_ptr;
		owned_wins.Add(swc); // Class must inherit TopWindow
		CoreWindow& cw = screens[screen].AddWindow(*swc);
		lock.Leave();
		return *obj_ptr;
	}
	
	template <class T> T& AddWindow(int screen) {
		T* obj_ptr = new T();
		return AddWindow(screen, obj_ptr);
	}
	
	void CloseWindow(TopWindow* tw);
	
	void Run();
};






NAMESPACE_TOPSIDE_END

#endif
#endif
