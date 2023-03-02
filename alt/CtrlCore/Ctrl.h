#ifndef _CtrlCoreAlt_Ctrl_h_
#define _CtrlCoreAlt_Ctrl_h_


NAMESPACE_UPP
class Absolute2D;
END_UPP_NAMESPACE


namespace TS { namespace Ecs {

class Windows;
//class WindowManager;
class Geom2DComponent;
class VirtualGui;
//class WindowSystem;
class DefaultGuiAppComponent;

}}


NAMESPACE_UPP


class ProgPainter;


struct LogPos {
	
	enum {
		NO_HORZ = 0,
		LEFT,
		RIGHT,
		HORZ,
		NO_VERT = 0,
		TOP,
		BOTTOM,
		VERT
	};
	int l = 0, r = 0, t = 0, b = 0, w = 0, h = 0, f = 0, n = 0;
	Byte vtype = 0, htype = 0;
};



#if 0
class CtrlFrame :
	RTTIBase
{
	
protected:
	friend class Ctrl;
	
	Ctrl* ctrl = NULL;
	bool has_mouse = false;
	
	CtrlFrame* GetCaptured();
	CtrlFrame* GetWithMouse();
	void SetCaptured(CtrlFrame* c);
	//void SetWithMouse(CtrlFrame* c);
	
public:
	RTTI_DECL0(CtrlFrame)
	
	virtual void FramePaint(Draw& w, const Rect& r) {}
	virtual void ContinueGlobalMouseMomentum() {}
	void SetCapture();
	void ReleaseCapture();
	virtual void FrameRemove() {}
	virtual void FrameAdd(Ctrl&) {}
	
	CtrlFrame() {}
	virtual ~CtrlFrame() {}
	
private:
	CtrlFrame(const CtrlFrame&);
	void operator=(const CtrlFrame&);
};
#endif



struct KeyInfo {
	const char *name;
	dword key[4];
};


class Bar :
	RTTIBase
{
public:
	struct Item {
		virtual Item& Text(const char *text);
		virtual Item& Key(dword key);
		virtual Item& Repeat(bool repeat = true);
		virtual Item& Image(const class Image& img);
		virtual Item& Check(bool check);
		virtual Item& Radio(bool check);
		virtual Item& Enable(bool _enable = true);
		virtual Item& Bold(bool bold = true);
		virtual Item& Tip(const char *tip);
		virtual Item& Help(const char *help);
		virtual Item& Topic(const char *topic);
		virtual Item& Description(const char *desc);
		virtual void  FinalSync();

		Item&   Label(const char *text);
		Item&   RightLabel(const char *text);

		Item& Key(KeyInfo& (*key)());

		Item();
		virtual ~Item();
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


class TopWindow;

class Ctrl :
	public Pte<Ctrl>,
	RTTIBase
{
	
public:
	enum PlacementConstants {
		CENTER   = 0,
		MIDDLE   = 0,
		LEFT     = 1,
		RIGHT    = 2,
		TOP      = 1,
		BOTTOM   = 2,
		SIZE     = 3,
		
		MINSIZE  = -16380,
		MAXSIZE  = -16381,
		STDSIZE  = -16382,
	};
	
	enum StateReason {
		FOCUS      = 10,
		ACTIVATE   = 11,
		DEACTIVATE = 12,
		SHOW       = 13,
		ENABLE     = 14,
		EDITABLE   = 15,
		OPEN       = 16,
		CLOSE      = 17,
		POSITION   = 100,
		LAYOUTPOS  = 101,
	};
	
	enum MouseEvents {
		BUTTON        = 0x0F,
		ACTION        = 0xFF0,

		MOUSEENTER    = 0x10,
		MOUSEMOVE     = 0x20,
		MOUSELEAVE    = 0x30,
		CURSORIMAGE   = 0x40,
		MOUSEWHEEL    = 0x50,

		DOWN          = 0x80,
		UP            = 0x90,
		DOUBLE        = 0xa0,
		REPEAT        = 0xb0,
		DRAG          = 0xc0,
		HOLD          = 0xd0,
		TRIPLE        = 0xe0,
		PEN           = 0xf0,
		PENLEAVE      = 0x100,

		LEFTDOWN      = LEFT|DOWN,
		LEFTDOUBLE    = LEFT|DOUBLE,
		LEFTREPEAT    = LEFT|REPEAT,
		LEFTUP        = LEFT|UP,
		LEFTDRAG      = LEFT|DRAG,
		LEFTHOLD      = LEFT|HOLD,
		LEFTTRIPLE    = LEFT|TRIPLE,

		RIGHTDOWN     = RIGHT|DOWN,
		RIGHTDOUBLE   = RIGHT|DOUBLE,
		RIGHTREPEAT   = RIGHT|REPEAT,
		RIGHTUP       = RIGHT|UP,
		RIGHTDRAG     = RIGHT|DRAG,
		RIGHTHOLD     = RIGHT|HOLD,
		RIGHTTRIPLE   = RIGHT|TRIPLE,

		MIDDLEDOWN     = MIDDLE|DOWN,
		MIDDLEDOUBLE   = MIDDLE|DOUBLE,
		MIDDLEREPEAT   = MIDDLE|REPEAT,
		MIDDLEUP       = MIDDLE|UP,
		MIDDLEDRAG     = MIDDLE|DRAG,
		MIDDLEHOLD     = MIDDLE|HOLD,
		MIDDLETRIPLE   = MIDDLE|TRIPLE
	};
	
	enum {
		NOBACKPAINT,
		FULLBACKPAINT,
		TRANSPARENTBACKPAINT,
		EXCLUDEPAINT,
	};
	
public:
	static  bool do_debug_draw;
	
public:
	RTTI_DECL0(Ctrl)
	
	struct Scroll : Moveable<Scroll> {
		Rect rect;
		int  dx;
		int  dy;
	};
	
	struct MoveCtrl : Moveable<MoveCtrl> {
		Ptr<Ctrl>  ctrl;
		Rect       from;
		Rect       to;
	};
	
	struct Top {
		GUIPLATFORM_CTRL_TOP_DECLS
		Vector<Scroll> scroll;
		VectorMap<Ctrl *, MoveCtrl> move;
		VectorMap<Ctrl *, MoveCtrl> scroll_move;
		Ptr<Ctrl>      owner;
	};
	
	union {
		Ctrl *uparent;
		Top  *utop;
	};
	
private:
	struct Frame : Moveable<Frame> {
		CtrlFrame* frame;
		operator CtrlFrame*() const {return frame;}
	};
	
	Vector<Frame> frames;
	Frame& GetFrame0(int i);
	
protected:
	static  int       LoopLevel;
	static  Ctrl     *LoopCtrl;
	static  int64     EventLoopNo;
	
	Ctrl* GetCaptured();
	Ctrl* GetWithMouse();
	void SetCaptured(Ctrl* c);
	void SetWithMouse(Ctrl* c);
	CtrlFrame* GetFrameCaptured();
	CtrlFrame* GetFrameWithMouse();
	void SetFrameCaptured(CtrlFrame* c);
	void SetFrameWithMouse(CtrlFrame* c);
	
	
	LogPos pos;
	byte         overpaint;

	bool         unicode:1;

	bool         fullrefresh:1;

	bool         transparent:1;
	bool         visible:1;
	bool         enabled:1;
	bool         wantfocus:1;
	bool         initfocus:1;
	bool         activepopup:1;
	bool         editable:1;
	bool         modify:1;
	bool         ignoremouse:1;
	bool         inframe:1;
	bool         inloop:1;
	bool         isopen:1;
	bool         popup:1;
	bool         popupgrab:1;
	byte         backpaint:2;//2

	bool         akv:1;
	bool         destroying:1;
	bool         layout_id_literal:1; // info_ptr points to layout char * literal, no heap involved
	bool         multi_frame:1; // there is more than single frame, they are stored in heap
	bool         top:1;
	
	Rect content_r;
	
	
	void Refresh0();// {Refresh();}
	void Layout0();// {Layout();}
	
public:
	Top         *GetTop()               { return top ? utop : NULL; }
	const Top   *GetTop() const         { return top ? utop : NULL; }
	void         DeleteTop();
	void SetTop(Top *t)                 { utop = t; top = true; }
	
	Ctrl            *GetParent() const;
	bool             IsChild() const    { return GetParent(); }
	
	static Ctrl *GetFocusCtrl();//                { return FocusCtrl(); }
	
protected:
	friend class TS::Ecs::VirtualGui;
	//friend class TS::Ecs::WindowSystem;
	friend class TopWindow;
	
	
public:
	typedef Ctrl CLASSNAME;
	Ctrl();
	virtual ~Ctrl() {}
	
#ifdef GUIPLATFORM_CTRL_DECLS_INCLUDE
	#include GUIPLATFORM_CTRL_DECLS_INCLUDE
#else
	GUIPLATFORM_CTRL_DECLS
#endif
	
	static void SetDebugDraw(bool b=true) {do_debug_draw = b;}
	static bool ProcessEvent(bool *quit = NULL);
	static bool ProcessEvents(double dt, bool *quit = NULL);
	static bool ReleaseCtrlCapture();
	static Ctrl *GetCaptureCtrl();
	
	//static oid EventLoop(Ctrl *ctrl);
	
	Rect GetRect() const;
	Size GetContentSize() const;
	void SetContentRect(const Rect& r);
	
	//void Add(GeomInteraction2D& c);
	void Add(Ctrl& c);
	void AddFrame(CtrlFrame& c);
	void AddChild(Ctrl* c);
	Ctrl* GetLastChild();
	Ctrl* GetIndexChild(int i);
	void RemoveChild(Ctrl* c);
	int GetChildCount() const;
	Ctrl& SetFrame(CtrlFrame&);
	Ctrl& SetFrame(int i, CtrlFrame& fr);
	void UpdateArea(SystemDraw& draw, const Rect& clip);
	
	Ctrl* GetParent();
	Ctrl* GetTopCtrl();
	TopWindow* GetTopWindow();
	const Ctrl* GetOwner() const;
	Ctrl* GetOwner();
	static Ctrl* GetActiveCtrl();
	
	Size GetSize() const;// {return GetFrameSize();}
	String Name() const;
	
	void SetFrameBox(const Rect& r);
	void DeepMouseMoveInFrameContent(Point pt, dword keyflags);
	void MouseMoveInFrameContent(Point pt, dword keyflags);
	Rect GetContentRect() const;
	Point GetContentPoint(const Point& pt);
	bool MouseWheelInFrameContent(Point p, int zdelta, dword keyflags);
	bool MouseEventInFrameCaptured(int mouse_code, const Point& pt, dword keyflags);
	void MouseEventInFrameContent(int mouse_code, const Point& pt, dword keyflags);
	
	virtual bool Key(dword key, int count);
	virtual Size GetMinSize() const {return Size(0,0);}
	virtual void FrameLayout(Rect& r) {}
	virtual void FrameAddSize(Size& sz) {}
	virtual void Paint(Draw& d) {}
	virtual void MouseEnter(Point frame_p, dword keyflags);
	virtual void MouseMove(Point content_p, dword keyflags) {}
	virtual void LeftDown(Point p, dword keyflags) {}
	virtual void LeftDouble(Point p, dword keyflags) {}
	virtual void LeftTriple(Point p, dword keyflags) {}
	virtual void LeftDrag(Point p, dword keyflags) {}
	virtual void LeftHold(Point p, dword keyflags) {}
	virtual void LeftRepeat(Point p, dword keyflags) {}
	virtual void LeftUp(Point p, dword keyflags) {}
	virtual void RightDown(Point p, dword keyflags) {}
	virtual void RightDouble(Point p, dword keyflags) {}
	virtual void RightTriple(Point p, dword keyflags) {}
	virtual void RightDrag(Point p, dword keyflags) {}
	virtual void RightHold(Point p, dword keyflags) {}
	virtual void RightRepeat(Point p, dword keyflags) {}
	virtual void RightUp(Point p, dword keyflags) {}
	virtual void MiddleDown(Point p, dword keyflags) {}
	virtual void MiddleDouble(Point p, dword keyflags) {}
	virtual void MiddleTriple(Point p, dword keyflags) {}
	virtual void MiddleDrag(Point p, dword keyflags) {}
	virtual void MiddleHold(Point p, dword keyflags) {}
	virtual void MiddleRepeat(Point p, dword keyflags) {}
	virtual void MiddleUp(Point p, dword keyflags) {}
	virtual void MouseWheel(Point p, int zdelta, dword keyflags) {}
	virtual Image CursorImage(Point p, dword keyflags);
	virtual void PadTouch(int controller, Pointf p) {}
	virtual void PadUntouch(int controller) {}
	virtual Image  FrameMouseEvent(int event, Point p, int zdelta, dword keyflags);
	virtual Image  MouseEvent(int event, Point p, int zdelta, dword keyflags);
	virtual void   MouseLeave();
	virtual bool   HotKey(dword key);
	virtual String GetDesc() const;
	virtual void   Layout();
	virtual void   Updated();
	virtual void   Close();
	virtual void   GotFocus();
	virtual void   LostFocus();
	virtual void   CancelMode();
	
	Ctrl& SizePos() {return HSizePos().VSizePos();}
	Ctrl& BottomPosZ(int i, int size = STDSIZE);
	Ctrl& HSizePos(int l=0, int r=0);
	Ctrl& VSizePos(int t=0, int b=0);
	Ctrl& BottomPos(int i, int size);
	Ctrl& TopPos(int i, int size);
	Ctrl& LeftPos(int i, int size);
	Ctrl& RightPos(int i, int size);
	
	bool Redraw(bool only_pending);
	bool Is2D() const;
	Ctrl* Get2D();
	void DeepLayout();
	bool Dispatch(const CtrlEvent& e);
	void DeepFrameLayout();
	void MouseLeaveFrame();
	void SetFocus();
	bool    HasFocus() const                   { return FocusCtrl() == this; }
	bool    HasFocusDeep() const;
	Ctrl&   WantFocus(bool ft = true)          { wantfocus = ft; return *this; }
	Ctrl&   NoWantFocus()                      { return WantFocus(false); }
	bool	IsWantFocus() const                { return wantfocus; }
	void DeepUnfocus();
	void PaintPreFrame(ProgPainter& pp);
	void PaintPostFrame(ProgPainter& pp);
	void PaintDebug(ProgPainter& pp);
	bool IsCtrl() const;
	void Refresh();
	void RefreshFrame();
	bool    HasMouse() const;
	bool    HasMouseDeep() const;
	void RefreshFrame(const Rect& r);
	
	Ctrl&       SetPos(LogPos p);
	void SetRect(const Rect& r);
	void SetRect(int x, int y, int cx, int cy);
	void Update();
	
	void        Shutdown()                               { destroying = true; }
	bool        IsShutdown() const                       { return destroying; }

	virtual int OverPaint() const {return 0;}
	
	Callback WhenAction;
	
	
	Ctrl& operator <<= (Callback cb) {WhenAction = cb; return *this;}
	
	
public:
	Absolute2D* aw = 0;
	
	//static bool           invalid;
	//static uint32 prev_ticks;
	
	static void TimerProc(double dt);
	//static void GuiSleep(int ms);
	//static void DoPaint();
	//static void PaintScene(SystemDraw& draw);
	static void SetMouseCursor(const Image& m);
	static bool IsAlphaSupported();
	static bool IsCompositedGui();
	static Vector<Ctrl*> GetTopCtrls();
	static int RegisterSystemHotKey(dword key, Callback cb);
	static void UnregisterSystemHotKey(int id);
	static bool IsWaitingEvent();
	static void   GetWorkArea(Array<Rect>& rc);
	static Rect   GetVirtualWorkArea();
	static Rect   GetVirtualScreenArea();
	static Rect   GetPrimaryWorkArea();
	static Rect   GetPrimaryScreenArea();
	static Rect   GetDefaultWindowRect();
	static int    GetKbdDelay();
	static int    GetKbdSpeed();
	static void InstallPanicBox();
	static void   GlobalBackBuffer(bool b = true);
	static void InitTimer();
	static void   CloseTopCtrls();
	static void  EndIgnore();
	static bool  DispatchKey(dword keycode, int count);
	static void      SyncCaret();
	static void  DefferedFocusSync();
	static bool ProcessEvents(bool *quit = NULL);
	static void      AnimateCaret();
	static void  EventLoop(Ctrl *loopctrl = NULL);
	static void GuiSleep(int ms);
	
	static Ptr<Ctrl> FocusCtrl() { return focusCtrl; }
	static void      FocusCtrl(Ptr<Ctrl> fc) { focusCtrl = fc; }
	
	static Ptr<Ctrl> focusCtrl;
	static Ptr<Ctrl> captureCtrl;
	static int64     EndSessionLoopNo;
	static bool      ignoreclick;
	
public:
	//static void InitFB();
	//static void ExitFB();
	//static void SetDesktopSize(Size sz);
	//static void Invalidate();
	

	void        GuiPlatformConstruct();
	void        GuiPlatformDestruct();
	void        GuiPlatformRemove();
	void        GuiPlatformGetTopRect(Rect& r) const;
	bool        GuiPlatformRefreshFrameSpecial(const Rect& r);
	bool        GuiPlatformSetFullRefreshSpecial();
	static void GuiPlatformSelection(PasteClip& d);
	
	Rect        GetScreenView() const;
	Rect        GetWorkArea() const;
	Rect        GetView() const;
	Rect        GetScreenRect() const;
	
	const Ctrl      *GetTopCtrl() const;
	
	virtual void   PostInput();
	
	bool    SetCapture();
	bool    ReleaseCapture();
	bool    HasCapture() const;
	
	void    Show(bool show = true);
	void    Hide()                             { Show(false); }
	bool    IsShown() const                    { return visible; }
	
	void WndDestroy();
	void WndUpdate();
	void WndUpdate(const Rect& r);
	void WndShow(bool b);
	void WndSetPos(const Rect& rect);
	void WndScrollView(const Rect& r, int dx, int dy);
	Rect GetWndScreenRect() const;
	bool IsWndOpen() const;
	void SetWndForeground();
	bool IsWndForeground() const;
	void ActivateWnd();
	void WndEnable(bool b);
	bool SetWndFocus();
	bool HasWndFocus() const;
	bool SetWndCapture();
	bool HasWndCapture() const;
	bool ReleaseWndCapture();
	void WndInvalidateRect(const Rect& r);
	void SetWndRect(const Rect& r);
	void SetAlpha(byte alpha);
	bool IsOpen() const;
	void SysEndLoop();
	void SetFocusWnd();
	void ClickActivateWnd();
	bool IsForeground() const;
	void SetForeground();
	Image   DispatchMouse(int e, Point p, int zd = 0);
	bool   InLoop() const;
	int GetFrameCount() const;
	void        RefreshParentLayout();
	
	void    Enable(bool enable = true);
	void    Disable()                          { Enable(false); }
	bool    IsEnabled() const                  { return enabled; }
	bool        InFrame() const                          { return inframe; }
	
	void    SyncLayout(int force = 0);
	void        RefreshLayout()                          { SyncLayout(1); }
	void        RefreshLayoutDeep()                      { SyncLayout(2); }
	
	void   PopUp(Ctrl *owner = NULL, bool savebits = true, bool activate = true, bool dropshadow = false,
	             bool topmost = false);

	Event<int>  WhenOpen;
	Event<int>  WhenClose;
	
};

class EmptySpaceCtrl : public Ctrl {
	RTTI_DECL1(EmptySpaceCtrl, Ctrl)
	
};



class ParentCtrl : public Ctrl {
	
public:
	RTTI_DECL1(ParentCtrl, Ctrl)
	
	
	
	
};







String GetKeyDesc(dword key);

Point GetMousePos();

bool ThreadHasGuiLock();




END_UPP_NAMESPACE

#endif
