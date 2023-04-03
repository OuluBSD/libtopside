#ifndef _CtrlCore_Ctrl_h_
#define _CtrlCore_Ctrl_h_


NAMESPACE_UPP



void EnterGuiMutex();
bool TryEnterGuiMutex();
void LeaveGuiMutex();

struct GuiLock {
	GuiLock()  { EnterGuiMutex(); }
	~GuiLock() { LeaveGuiMutex(); }
};


bool GetMouseLeft();
Point GetMousePos();

class Ctrl;

class CtrlFrame :
	RTTIBase
{
	
public:
	RTTI_DECL0(CtrlFrame)
	
	CtrlFrame() {}
	virtual ~CtrlFrame() {}

};


struct KeyInfo {
	const char *name;
	dword key[4];
};


class Bar :
	RTTIBase
{
public:
	struct Item {
		Item() {}
		virtual ~Item(){}
	};
	
private:
	
	
	
public:
	RTTI_DECL0(Bar)
	typedef Bar CLASSNAME;
	Bar();
	
	Bar& Add(String title, Callback cb);
	Bar& Separator();
	
	virtual void   Paint(Draw& w) {}
	virtual int    OverPaint() const {return 0;}
	virtual bool   HotKey(dword key) {return false;}
	virtual Bar::Item& AddItem(Callback cb) {NEVER()}
	virtual Bar::Item& AddSubMenu(Callback1<Bar&> proc) {NEVER()}
	
};


inline String FromSystemCharset(String s) {return s;}

class TopWindow;

enum {
	GUI_SETMOUSECURSOR = 1,
	
};

class Ctrl :
	public Pte<Ctrl>,
	RTTIBase
{
	
public:
	RTTI_DECL0(Ctrl)
	
	enum {
		MOUSEMOVE,
		MOUSEWHEEL,
		LEFTDOUBLE,
		RIGHTDOUBLE,
		MIDDLEDOUBLE,
		LEFTDOWN,
		RIGHTDOWN,
		MIDDLEDOWN,
		LEFTUP,
		RIGHTUP,
		MIDDLEUP,
		CURSORIMAGE,
		ACTION,
		DOWN,
		UP,
		MAXIMIZED,
		MAXIOVERLAPPEDMIZED,
		OVERLAPPED,
	};
	
	struct PasteClip {
		
	};
	
	struct Top {
		Ctrl*      owner_window;
		
	};
	
	bool fullrefresh;
	bool isopen;
	bool popup;
	Top* top;
	static Ctrl* captureCtrl;
	static Ctrl* LoopCtrl;
	
	static Ptr<Ctrl>      desktop;
	static Ptr<Ctrl>      focusCtrl;
	static Vector<Ctrl *> topctrl;
	
	static bool           invalid;
	static bool           ignoreclick;
	static bool           inloop;
	
	static Point          fbCursorPos;
	static Image          fbCursorImage;
	
	static Rect           fbCaretRect;
	static int            fbCaretTm;
	static bool           fbEndSession;
	static int            PaintLock;
	static dword          EndSessionLoopNo;
	static dword          EventLoopNo;
	static dword          LoopLevel;
	
	Event<> WhenInvalidate;
	
	int FindTopCtrl() const;
	bool IsAlphaSupported();
	bool IsCompositedGui();
	bool IsWaitingEvent();
	bool IsWndOpen() const;
	bool IsWndForeground() const;
	bool IsOpen() const {return false;}
	bool IsChild() const {return false;}
	bool IsEnabled() const {return false;}
	bool SetWndFocus();
	bool SetWndCapture();
	bool ReleaseWndCapture();
	bool HasWndFocus() const;
	bool HasWndCapture() const;
	void WndScrollView(const Rect& r, int dx, int dy);
	void WndSetPos(const Rect& rect);
	void WndInvalidateRect(const Rect&);
	void PopUp(Ctrl *owner, bool savebits, bool activate, bool dropshadow=0, bool topmost=0);
	static Vector<Ctrl *> GetTopCtrls();
	Ctrl *GetOwner();
	Ctrl *GetActiveCtrl();
	Top *GetTop() {return 0;}
	int RegisterSystemHotKey(dword key, Function<void ()> cb);
	void UnregisterSystemHotKey(int id);
	void SyncRect() {}
	void DeleteTop() {}
	void UpdateArea(SystemDraw& d, Rect r) {}
	static void DoPaint(bool force=false);
	void DestroyFrame() {}
	void WndShow(bool b);
	void SetOpen(bool b) {}
	void WndUpdate();
	void WndUpdate(const Rect&);
	void WndDestroy();
	void WndEnable(bool);
	void DestroyWnd();
	void PutForeground();
	void SetWndForeground();
	void ActivateWnd() {}
	void NewTop() {}
	void SetAlpha(byte alpha);
	void GetWorkArea(Array<Rect>& rc);
	static Rect GetClipBound(const Vector<Rect>& inv, const Rect& r);
	Rect GetWndScreenRect() const;
	Rect GetWorkArea() const;
	Rect GetVirtualScreenArea() const {return Rect();}
	Rect GetVirtualScreenArea();
	Rect GetVirtualWorkArea();
	Rect GetPrimaryWorkArea();
	Rect GetPrimaryScreenArea();
	Rect GetDefaultWindowRect();
	static int GetKbdDelay();
	static int GetKbdSpeed();
	void SyncFrameRect(Rect r) {}
	void SetWndRect(Rect r) {}
	void SetForeground() {}
	void SetFocusWnd() {}
	void RefreshLayoutDeep() {}
	void InstallPanicBox();
	void SysEndLoop();
	void SetDesktop(Ctrl& q);
	TopWindow* GetTopWindow() const {return 0;}
	Image DispatchMouse(int e, Point p, int zd) {return Image();}
	static void EndIgnore() {}
	void PostInput() {}
	Ctrl* FindMouseTopCtrl();
	
	static void DeleteDesktopTop();
	static void GlobalBackBuffer() {}
	static void InitTimer() {}
	static void ChStdSkin() {}
	static void CloseTopCtrls() {}
	static void InitFB();
	static void ExitFB();
	static void SetDesktopSize(Size sz);
	static void SyncTopWindows();
	static void MouseEventFB(Ptr<Ctrl> t, int event, Point p, int zdelta);
	static Ctrl* GetDesktop() {return 0;}
	static  bool  DispatchKey(dword keycode, int count) {return false;}
	static bool  ReleaseCtrlCapture() {return false;}
	static bool  EventLoopIteration(void* p);
	static bool  ProcessEvents(bool *quit);
	static void      EventLoop(Ctrl *ctrl);
	static void      SyncCaret() {}
	static void      AnimateCaret() {}
	static int      LeaveGuiMutexAll() {return 0;}
	static void      EnterGuiMutex(int) {}
	static void      CursorSync();
	static  void  DefferedFocusSync() {}
	static  void  GuiSleep(int ms);
	
public:
	typedef Ctrl CLASSNAME;
	Ctrl() {}
	virtual ~Ctrl() {}
	
	
	virtual void   Layout() {}
	virtual void   Paint(Draw& w) {}
	virtual void   MouseEnter(Point p, dword keyflags) {}
	virtual void   MouseMove(Point p, dword keyflags) {}
	virtual void   LeftDown(Point p, dword keyflags) {}
	virtual void   LeftDouble(Point p, dword keyflags) {}
	virtual void   LeftTriple(Point p, dword keyflags) {}
	virtual void   LeftRepeat(Point p, dword keyflags) {}
	virtual void   LeftDrag(Point p, dword keyflags) {}
	virtual void   LeftHold(Point p, dword keyflags) {}
	virtual void   LeftUp(Point p, dword keyflags) {}
	virtual void   RightDown(Point p, dword keyflags) {}
	virtual void   RightDouble(Point p, dword keyflags) {}
	virtual void   RightTriple(Point p, dword keyflags) {}
	virtual void   RightRepeat(Point p, dword keyflags) {}
	virtual void   RightDrag(Point p, dword keyflags) {}
	virtual void   RightHold(Point p, dword keyflags) {}
	virtual void   RightUp(Point p, dword keyflags) {}
	virtual void   MiddleDown(Point p, dword keyflags) {}
	virtual void   MiddleDouble(Point p, dword keyflags) {}
	virtual void   MiddleTriple(Point p, dword keyflags) {}
	virtual void   MiddleRepeat(Point p, dword keyflags) {}
	virtual void   MiddleDrag(Point p, dword keyflags) {}
	virtual void   MiddleHold(Point p, dword keyflags) {}
	virtual void   MiddleUp(Point p, dword keyflags) {}
	virtual void   MouseWheel(Point p, int zdelta, dword keyflags) {}
	virtual void   MouseLeave() {}
	virtual bool   Key(dword key, int count) {return false;}
	virtual void   Updated() {}
	virtual void   GotFocus() {}
	virtual void   LostFocus() {}
	
	void           AddFrame(CtrlFrame&) {}
	void           SetFrame(CtrlFrame&) {}
	void           SetFocus() {}
	void           Refresh() {}
	void           Shutdown() {}
	void           ClearModify() {}
	void           SetModify() {}
	void           Update() {}
	void           GripResize() {}
	void           ClickActivateWnd() {}
	void           WantFocus(bool b=true) {}
	Image FrameMouseEvent(int event, Point p, int zdelta, dword keyflags) {return Image();}
	Image MouseEvent(int event, Point p, int zdelta, dword keyflags) {return Image();}
	Ctrl*			GetTopCtrl() {return 0;}
	Rect			GetScreenView() const {return Rect(0,0,0,0);}
	String			Name() const;
	Ctrl*			GetParent() const {return 0;}
	void			SetMouseCursor(const Image& image);
	
	// VirtualGui
	static void Invalidate();
	static bool ProcessEvents(double dt, bool *quit);
	static bool ProcessEvent(bool *quit);
	static void TimerProc(double dt) {}
	static void DoMouseFB(int event, Point p, int zdelta = 0);
	static bool DoKeyFB(dword key, int cnt);
	static void PaintAll() {}
	static bool InLoop() {return false;}
	static void EndSession();
	static void PaintScene(SystemDraw&);
	static void PaintCaretCursor(SystemDraw&);
	
	void GuiPlatformConstruct();
	void GuiPlatformRemove();
	bool GuiPlatformSetFullRefreshSpecial();
	void GuiPlatformSelection(PasteClip&);
	bool GuiPlatformRefreshFrameSpecial(const Rect& r);
	void GuiPlatformGetTopRect(Rect& r) const;
	
	Size GetSize() const {return Size(0,0);}
	Rect GetRect() const {return Rect(0,0,0,0);}
	void SetRect(const Rect& r) {}
	int GetChildCount() const {return 0;}
	int GetCursor() const {return 0;}
	int Get() const {return 0;}
	Ctrl* GetIndexChild(int i) {return 0;}
	bool HasFocus() const {return false;}
	bool IsCursor() const {return false;}
	bool IsModified() const {return false;}
	bool HasMouse() const {return false;}
	
	Ctrl& Add(Ctrl& c) {return *this;}
	Ctrl& RemoveChild(Ctrl* c) {return *this;}
	Ctrl& SizePos() {return *this;}
	Ctrl& HSizePos(int a=0, int b=0) {return *this;}
	Ctrl& VSizePos(int a=0, int b=0) {return *this;}
	Ctrl& BottomPosZ(int a=0, int b=0) {return *this;}
	Ctrl& LeftPos(int a=0, int b=0) {return *this;}
	Ctrl& RightPos(int a=0, int b=0) {return *this;}
	Ctrl& BottomPos(int a=0, int b=0) {return *this;}
	Ctrl& TopPos(int a=0, int b=0) {return *this;}
	Ctrl& Horz() {return *this;}
	
	void Show(bool b=true) {}
	
	void operator^=(Event<> e) {}
	
	Event<> WhenClose;
};

inline String GetKeyDesc(dword key) {return "";}


class TopWindow :
	public Ctrl
{

	struct Frame : Ctrl {
		String title;
		int minsize;
		Ctrl close;
		Ctrl maximize;
		bool sizeable;
		void RefreshLayout() {}
		void Refresh() {}
		Image icon;
		void Enable(bool) {}
		void SetClient(Rect r) {}
		void SyncBox() {}
		bool IsOpen() const {return 0;}
		Rect GetClient() const {return Rect();}
		TopWindow* window;
		void Maximize() {}
		void Overlap() {}
	};
	
	Frame* frame;
	String title;
	int minsize;
	bool sizeable;
	bool noclosebox;
	bool maximizebox;
	bool center;
	bool fullscreen;
	int state;
	Image icon;
	
	
public:
	RTTI_DECL1(TopWindow, Ctrl)
	TopWindow() {}
	virtual ~TopWindow() {}
	
	TopWindow& Title(const char *s) {return *this;}
	TopWindow& Icon(Image) {return *this;}
	
	void SyncFrameRect(const Rect& r);
	void DestroyFrame();
	void GripResize();
	void SyncSizeHints();
	void SyncTitle();
	void SyncCaption();
	void OnClose();
	void SyncRect();
	void GuiPlatformConstruct();
	void GuiPlatformDestruct();
	void FocusEvent();
	void SerializePlacement(Stream& s, bool reminimize);
	void CreateGeom2DComponent();
	void Open(Ctrl *owner);
	void State(int reason);
	
	void Maximize(bool b=true);
	void Minimize(bool b=true);
	TopWindow& FullScreen(bool b=true);
	void Overlap(bool b=true);
	void Open();
	void OpenMain();
	TopWindow& TopMost(bool b, bool stay_top);
	bool IsTopMost() const;
	
	static void ShutdownWindows() {}
	
};


class TopWindowFrame : public Ctrl {
public:
	Ctrl* GetTopContainer() const {return 0;}
};


END_UPP_NAMESPACE

#endif
