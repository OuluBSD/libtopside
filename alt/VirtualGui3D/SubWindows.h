#ifndef _CtrlCore_Windows_h_
#define _CtrlCore_Windows_h_

#ifdef flagGUI

NAMESPACE_ECS_BEGIN


class SubMenuFrameList : public Ctrl {
	
public:
	
};

class SubMenuFrame : public Ctrl {
	int height, shift, arrow_border;
	bool left_arrow, right_arrow;
	Windows* wins;
	Color clr_bg, clr_tr;
	Vector<int> id_pos;
	int clicked_id;
	
protected:
	void Close();
	void Maximize();
	void Minimize();
	void CloseOthers();
	
public:
	RTTI_DECL1(SubMenuFrame, Ctrl)
	typedef SubMenuFrame CLASSNAME;
	SubMenuFrame(Windows* wins);
	
	virtual void Paint(Draw& w);
	virtual void LeftDown(Point p, dword keyflags);
	virtual void RightDown(Point p, dword keyflags);
	virtual void MouseWheel(Point p, int zdelta, dword keyflags);
	
	void LocalMenu(Bar& bar);
};

class Windows : public Ctrl {
	RTTI_DECL1(Windows, Ctrl)
	void Visit(RuntimeVisitor& vis) {}
	
protected:
	friend class OpenVR;
	
	Vector<int> close_window_queue;
	void CloseWindow(int win_id);
	
	
protected:
	friend class WindowManager;
	
	WindowManager* wm = NULL;
	int win_counter = 0;
	ArrayMap<int, CoreWindow*> wins;
	//SubMenuFrame menu;
	//Ctrl sub_area;
	bool maximize_all;
	int active_pos, active_id;
	Array<TopWindow> created_wins;
	Ctrl* captured = NULL;
	Ctrl* with_mouse = NULL;
	CtrlFrame* frame_with_mouse = NULL;
	CtrlFrame* frame_captured = NULL;
	EmptySpaceCtrl* esc = NULL;
	
protected:
	typedef Windows CLASSNAME;
	
	friend class UPP::TopWindow;
	friend class CoreWindow;
	friend class SubMenuFrame;
	//friend class Core;
	friend class UPP::CtrlFrame;
	friend class UPP::Ctrl;
	
	void QueueCloseWindow(int win_id) {close_window_queue.Add(win_id);}
	void MoveWindow(Point pt, int win_id);
	void FocusWindow(int win_id);
	void FocusWindowPos(int win_pos);
	void MaximizeWindow(int win_id);
	void MinimizeWindow(int win_id);
	void RestoreWindow(int win_id);
	void IsActiveWindow(bool* result, int win_id) {*result = win_id == active_id;}
	void SetWindowMaximized(CoreWindow& sw, bool b);
	
	void FocusPrevious();
	void SetTitle(int win_id, const String& title);
	String GetTitle(int win_id);
	void CloseOthers(int win_id);
	
	void LoadRectAll();
	void SetMaximizeAll(bool b=true) {maximize_all = b;}
	
	Ctrl* GetCaptured() {return captured;}
	Ctrl* GetWithMouse() {return with_mouse;}
	void SetCaptured(Ctrl* c) {captured = c;}
	void SetWithMouse(Ctrl* c) {with_mouse = c;}
	CtrlFrame* GetFrameCaptured() {return frame_captured;}
	CtrlFrame* GetFrameWithMouse() {return frame_with_mouse;}
	void SetFrameCaptured(CtrlFrame* c) {frame_captured = c;}
	void SetFrameWithMouse(CtrlFrame* c) {frame_with_mouse = c;}
	
public:
	Windows();
	~Windows();
	
	hash_t GetHashValue() const {return (hash_t)(size_t)this;}
	
	void AddWindow(CoreWindow&);
	CoreWindow& GetWindow(TopWindow& ctrl);
	CoreWindow* GetActiveWindow() {int i = wins.Find(active_id); return i >= 0 ? wins[i] : NULL;}
	int GetActiveWindowPos() {return active_pos;}
	int GetActiveWindowId()  {return active_id;}
	int GetPosId(int win_pos) {if (win_pos >= 0 && win_pos < wins.GetCount()) return wins.GetKey(win_pos); return -1;}
	
	void FocusWindow(TopWindow* ctrl);
	void OrderTileWindows();
	void OrderTileWindowsVert();
	void CloseAll();
	//void Redraw(int child_id, bool only_pending);
	void SetEmptySpaceCtrl(EmptySpaceCtrl& esc) {this->esc = &esc;}
	
	bool ProcessCloseQueue() {bool ret = close_window_queue.GetCount(); for(int i = 0; i < close_window_queue.GetCount(); i++) CloseWindow(close_window_queue[i]); close_window_queue.Clear(); return ret;}
	virtual bool CheckRender();
	virtual bool DeepKey(dword key, int count);
	virtual void CloseWindow(CoreWindow& cw) = 0;
	bool Key(dword key, int count) override;
	void LeftDown(Point p, dword keyflags) override;
	void Layout() override;
	void PostLayout() override;
	
	int GetCount() const {return wins.GetCount();}
	CoreWindow& operator[] (int i) {return *wins[i];}
	CoreWindow& Get(int i) {return *wins[i];}
	
	TopWindow* GetVisibleTopWindow();
	TopWindow& GetVisibleTopWindowRef() {return *GetVisibleTopWindow();}
	
	
	Callback WhenActiveWindowChanges, WhenWindowClose;
};


NAMESPACE_ECS_END

#endif
#endif
