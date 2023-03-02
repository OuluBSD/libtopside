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
	
	class Logc {
		dword data;

		static int LSGN(dword d)       { return int16((d & 0x7fff) | ((d & 0x4000) << 1)); }

	public:
		bool  operator==(Logc q) const { return data == q.data; }
		bool  operator!=(Logc q) const { return data != q.data; }
		int   GetAlign() const         { return (data >> 30) & 3; }
		int   GetA() const             { return LSGN(data >> 15); }
		int   GetB() const             { return LSGN(data); }
		void  SetAlign(int align)      { data = (data & ~(3 << 30)) | (align << 30); }
		void  SetA(int a)              { data = (data & ~(0x7fff << 15)) | ((a & 0x7fff) << 15); }
		void  SetB(int b)              { data = (data & ~0x7fff) | (b & 0x7fff); }
		bool  IsEmpty() const;

		Logc(int al, int a, int b)     { data = (al << 30) | ((a & 0x7fff) << 15) | (b & 0x7fff); }
		Logc()                         { data = 0xffffffff; }
	};

	struct LogPos : Moveable<LogPos> {
		Logc x, y;

		bool operator==(LogPos b) const   { return x == b.x && y == b.y; }
		bool operator!=(LogPos b) const   { return !(*this == b); }

		LogPos(Logc x, Logc y)            : x(x), y(y) {}
		LogPos()                          {}
	};
	
	static Logc PosLeft(int pos, int size)       { return Logc(LEFT, pos, size); }
	static Logc PosRight(int pos, int size)      { return Logc(RIGHT, pos, size); }
	static Logc PosTop(int pos, int size)        { return Logc(TOP, pos, size); }
	static Logc PosBottom(int pos, int size)     { return Logc(BOTTOM, pos, size); }
	static Logc PosSize(int lpos, int rpos)      { return Logc(SIZE, lpos, rpos); }
	static Logc PosCenter(int size, int offset)  { return Logc(CENTER, offset, size); }
	static Logc PosCenter(int size)              { return Logc(CENTER, 0, size); }
	
	
private:
	struct MultiFrame { // in case there are more than 1 CtrlFrames
		int alloc;
		int count;
	};
	
	struct Rect16_ { // so that it can be in union
		int16 left, top, right, bottom;
	};
	
	struct Frame {
		union {
			CtrlFrame *frame;
			Frame     *frames;
		};
		union {
			MultiFrame multi;
			Rect16_    view;
		};
		
		void SetView(const Rect& r) { view.left = r.left; view.right = r.right; view.top = r.top; view.bottom = r.bottom; }
		Rect GetView() const        { return Rect16(view.left, view.top, view.right, view.bottom); }
	};
	
	struct MoveCtrl : Moveable<MoveCtrl> {
		Ptr<Ctrl>  ctrl;
		Rect       from;
		Rect       to;
	};
	
	struct Scroll : Moveable<Scroll> {
		Rect rect;
		int  dx;
		int  dy;
	};
	
	struct Top {
		GUIPLATFORM_CTRL_TOP_DECLS
		Vector<Scroll> scroll;
		VectorMap<Ctrl *, MoveCtrl> move;
		VectorMap<Ctrl *, MoveCtrl> scroll_move;
		Ptr<Ctrl>      owner;
	};
	
	
	Frame        frame;
	LogPos       pos;//8
	Rect16       rect; //8
	
	union {
		Ctrl *uparent;
		Top  *utop;
	};
	
	
	Ctrl        *prev_sibling = nullptr;
	Ctrl        *next_sibling = nullptr;
	Ctrl        *children = nullptr;
	
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
	
	static  bool do_debug_draw;
	static  Ptr<Ctrl> focusCtrl;
	static  Ptr<Ctrl> captureCtrl;
	static  int64     EndSessionLoopNo;
	static  bool      ignoreclick;
	static  int       LoopLevel;
	static  Ctrl     *LoopCtrl;
	static  int64     EventLoopNo;
	
	static Ptr<Ctrl> FocusCtrl() { return focusCtrl; }
	static void      FocusCtrl(Ptr<Ctrl> fc) { focusCtrl = fc; }
	
	void SetWndRect(const Rect& r);
	
	static  void  EndIgnore();
	Image   DispatchMouse(int e, Point p, int zd = 0);
	
	static  void  DefferedFocusSync();
	static  bool  DispatchKey(dword keycode, int count);
	
	void SetFocusWnd();
	
	static void      AnimateCaret();
	static void      SyncCaret();
	
	void    Refresh0(const Rect& area);
	void    UpdateArea(SystemDraw& draw, const Rect& clip);
	
	void    SyncLayout(int force = 0);
	
	void WndShow(bool b);
	void WndSetPos(const Rect& rect);
	
	bool IsWndOpen() const;
	
	bool SetWndCapture();
	bool HasWndCapture() const;
	bool ReleaseWndCapture();
	
	static void SetMouseCursor(const Image& m);
	
	void ClickActivateWnd();
	void ActivateWnd();
	bool SetWndFocus();
	bool HasWndFocus() const;
	
	void WndInvalidateRect(const Rect& r);

	void WndScrollView(const Rect& r, int dx, int dy);

	void SetWndForeground();
	bool IsWndForeground() const;
	
	void WndEnable(bool b);
	
	Rect GetWndScreenRect() const;
	
	void WndUpdate();
	void WndUpdate(const Rect& r);
	
	void WndDestroy();
	
	void SysEndLoop();
	
	Top         *GetTop()               { return top ? utop : NULL; }
	const Top   *GetTop() const         { return top ? utop : NULL; }
	void         DeleteTop();
	
	void SetTop(Top *t)                 { utop = t; top = true; }
	
	Frame& GetFrame0(int i);
	
	static void InitTimer();
	
	friend class TopWindow;
	
	typedef Ctrl CLASSNAME;
	
	void        GuiPlatformConstruct();
	void        GuiPlatformDestruct();
	void        GuiPlatformRemove();
	void        GuiPlatformGetTopRect(Rect& r) const;
	bool        GuiPlatformRefreshFrameSpecial(const Rect& r);
	bool        GuiPlatformSetFullRefreshSpecial();
	static void GuiPlatformSelection(PasteClip& d);
	
#ifdef GUIPLATFORM_CTRL_DECLS_INCLUDE
	#include GUIPLATFORM_CTRL_DECLS_INCLUDE
#else
	GUIPLATFORM_CTRL_DECLS
#endif
	
	static void InstallPanicBox();
	
	static void TimerProc(double dt);
	
public:
	
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
	
	static Vector<Ctrl*> GetTopCtrls();
	static void   CloseTopCtrls();
	
	static  int    RegisterSystemHotKey(dword key, Function<void ()> cb);
	static  void   UnregisterSystemHotKey(int id);
	
	virtual void   SetData(const Value& data);
	virtual Value  GetData() const;
	
	virtual void Paint(Draw& d) {}
	virtual int OverPaint() const {return 0;}
	
	virtual void   CancelMode();
	
	virtual Image  FrameMouseEvent(int event, Point p, int zdelta, dword keyflags);
	virtual Image  MouseEvent(int event, Point p, int zdelta, dword keyflags);
	virtual void   MouseEnter(Point p, dword keyflags);
	virtual void   MouseMove(Point p, dword keyflags);
	virtual void   LeftDown(Point p, dword keyflags);
	virtual void   LeftDouble(Point p, dword keyflags);
	virtual void   LeftTriple(Point p, dword keyflags);
	virtual void   LeftRepeat(Point p, dword keyflags);
	virtual void   LeftDrag(Point p, dword keyflags);
	virtual void   LeftHold(Point p, dword keyflags);
	virtual void   LeftUp(Point p, dword keyflags);
	virtual void   RightDown(Point p, dword keyflags);
	virtual void   RightDouble(Point p, dword keyflags);
	virtual void   RightTriple(Point p, dword keyflags);
	virtual void   RightRepeat(Point p, dword keyflags);
	virtual void   RightDrag(Point p, dword keyflags);
	virtual void   RightHold(Point p, dword keyflags);
	virtual void   RightUp(Point p, dword keyflags);
	virtual void   MiddleDown(Point p, dword keyflags);
	virtual void   MiddleDouble(Point p, dword keyflags);
	virtual void   MiddleTriple(Point p, dword keyflags);
	virtual void   MiddleRepeat(Point p, dword keyflags);
	virtual void   MiddleDrag(Point p, dword keyflags);
	virtual void   MiddleHold(Point p, dword keyflags);
	virtual void   MiddleUp(Point p, dword keyflags);
	virtual void   MouseWheel(Point p, int zdelta, dword keyflags);
	virtual void   MouseLeave();
	
	virtual Image  CursorImage(Point p, dword keyflags);

	virtual bool   Key(dword key, int count);
	virtual void   GotFocus();
	virtual void   LostFocus();
	virtual bool   HotKey(dword key);

	virtual void PadTouch(int controller, Pointf p) {}
	virtual void PadUntouch(int controller) {}
	
	virtual void   PostInput(); // Deprecated
	
	virtual void   Layout();
	
	virtual Size   GetMinSize() const;
	
	virtual void   Updated();
	
	virtual void   Close();
	
	virtual String GetDesc() const;
	
	Event<>          WhenAction;
	
	void             AddChild(Ctrl *child);
	void             RemoveChild(Ctrl *child);
	Ctrl            *GetParent() const     { return top ? NULL : uparent; }
	Ctrl            *GetLastChild() const  { return children ? children->prev_sibling : nullptr; }
	Ctrl            *GetPrev() const       { Ctrl *parent = GetParent(); return parent && prev_sibling != parent->GetLastChild() ? prev_sibling : nullptr; }
	Ctrl            *GetNext() const       { Ctrl *parent = GetParent(); return parent && next_sibling != parent->children ? next_sibling : nullptr; }
	int              GetChildIndex(const Ctrl *child) const;
	Ctrl            *GetIndexChild(int i) const;
	int              GetChildCount() const;
	
	bool             IsChild() const    { return GetParent(); }
	
	bool             IsForeground() const;
	void             SetForeground();
	
	const Ctrl      *GetTopCtrl() const;
	Ctrl            *GetTopCtrl();
	const Ctrl      *GetOwner() const;
	Ctrl            *GetOwner();
	
	const TopWindow *GetTopWindow() const;
	TopWindow       *GetTopWindow();
	
	Ctrl&            SetFrame(int i, CtrlFrame& frm);
	Ctrl&            SetFrame(CtrlFrame& frm)            { return SetFrame(0, frm); }
	Ctrl&            AddFrame(CtrlFrame& frm);
	int              GetFrameCount() const   { return multi_frame ? frame.multi.count : frame.frame ? 1 : 0; }
	
	bool        IsOpen() const;

	void        Shutdown()                               { destroying = true; }
	bool        IsShutdown() const                       { return destroying; }

	Ctrl&       SetPos(LogPos p, bool inframe);
	
	Ctrl&       SetPos(LogPos p);
	Ctrl&       SetPos(Logc x, Logc y)                   { return SetPos(LogPos(x, y)); }
	
	void        SetRect(const Rect& r);
	void        SetRect(int x, int y, int cx, int cy);
	
	bool        InFrame() const                          { return inframe; }
	
	void        RefreshLayout()                          { SyncLayout(1); }
	void        RefreshLayoutDeep()                      { SyncLayout(2); }
	void        RefreshParentLayout();
	
	Ctrl&       LeftPos(int a, int size = STDSIZE);
	Ctrl&       RightPos(int a, int size = STDSIZE);
	Ctrl&       TopPos(int a, int size = STDSIZE);
	Ctrl&       BottomPos(int a, int size = STDSIZE);
	Ctrl&       HSizePos(int a = 0, int b = 0);
	Ctrl&       VSizePos(int a = 0, int b = 0);
	Ctrl&       SizePos();
	Ctrl&       HCenterPos(int size = STDSIZE, int delta = 0);
	Ctrl&       VCenterPos(int size = STDSIZE, int delta = 0);
	
	Ctrl&       LeftPosZ(int a, int size = STDSIZE);
	Ctrl&       RightPosZ(int a, int size = STDSIZE);
	Ctrl&       TopPosZ(int a, int size = STDSIZE);
	Ctrl&       BottomPosZ(int a, int size = STDSIZE);
	Ctrl&       HSizePosZ(int a = 0, int b = 0);
	Ctrl&       VSizePosZ(int a = 0, int b = 0);
	Ctrl&       HCenterPosZ(int size = STDSIZE, int delta = 0);
	Ctrl&       VCenterPosZ(int size = STDSIZE, int delta = 0);
	
	Rect        GetRect() const;
	Rect        GetScreenRect() const;
	
	Rect        GetView() const;
	Rect        GetScreenView() const;
	Size        GetSize() const;
	
	Rect        GetWorkArea() const;
	
	void        Refresh(const Rect& r);
	void        Refresh(int x, int y, int cx, int cy);
	void        Refresh();
	
	void        RefreshFrame(const Rect& r);
	void        RefreshFrame(int x, int y, int cx, int cy);
	void        RefreshFrame();
	
	bool    HasMouse() const;
	bool    HasMouseDeep() const;
	
	bool    SetCapture();
	bool    ReleaseCapture();
	bool    HasCapture() const;
	static bool ReleaseCtrlCapture();
	static Ctrl *GetCaptureCtrl();
	
	bool    SetFocus();
	bool    HasFocus() const                   { return FocusCtrl() == this; }
	bool    HasFocusDeep() const;
	Ctrl&   WantFocus(bool ft = true)          { wantfocus = ft; return *this; }
	Ctrl&   NoWantFocus()                      { return WantFocus(false); }
	bool	IsWantFocus() const                { return wantfocus; }
	
	static Ctrl *GetFocusCtrl()                { return FocusCtrl(); }

	void    Show(bool show = true);
	void    Hide()                             { Show(false); }
	bool    IsShown() const                    { return visible; }
	bool    IsVisible() const;

	void    Enable(bool enable = true);
	void    Disable()                          { Enable(false); }
	bool    IsEnabled() const                  { return enabled; }
	
	void    Add(Ctrl& ctrl)                    { AddChild(&ctrl); }
	Ctrl&   operator<<(Ctrl& ctrl)             { Add(ctrl); return *this; }

	void    Remove();
	
	Value        operator~() const             { return GetData(); }
	const Value& operator<<=(const Value& v)   { SetData(v); return v; }
	bool         IsNullInstance() const        { return GetData().IsNull(); }

	Callback     operator<<=(Callback  action) { WhenAction = action; return action; }

	Event<>&     operator<<(Event<> action)    { return WhenAction << action; }
	Event<>&     operator^=(Event<> action)    { return WhenAction = action; }
	
	static Ctrl *GetActiveCtrl();
	
	void   PopUp(Ctrl *owner = NULL, bool savebits = true, bool activate = true, bool dropshadow = false,
	             bool topmost = false);
	
	void   SetAlpha(byte alpha);

	static bool IsWaitingEvent();
	static bool ProcessEvent(bool *quit = NULL);
	static bool ProcessEvents(bool *quit = NULL);
	
	static void  EventLoop(Ctrl *loopctrl = NULL);
	
	bool   InLoop() const;
	
	static Rect   GetVirtualWorkArea();
	static Rect   GetVirtualScreenArea();
	static Rect   GetPrimaryWorkArea();
	static Rect   GetPrimaryScreenArea();
	static void   GetWorkArea(Array<Rect>& rc);
	static int    GetKbdDelay();
	static int    GetKbdSpeed();
	static bool   IsAlphaSupported();
	static Rect   GetDefaultWindowRect();
	static bool   IsCompositedGui();
	
	static void   GlobalBackBuffer(bool b = true);
	
	String        Name() const;
	
	static void GuiSleep(int ms);
	
	RTTI_DECL0(Ctrl)
	Ctrl();
	virtual ~Ctrl() {}
	
	
	static void SetDebugDraw(bool b=true) {do_debug_draw = b;}
	static bool IsDebugDraw() {return do_debug_draw;}
	
	
	
	/*
	void DeepMouseMoveInFrameContent(Point pt, dword keyflags);
	void MouseMoveInFrameContent(Point pt, dword keyflags);
	Rect GetContentRect() const;
	Point GetContentPoint(const Point& pt);
	bool MouseWheelInFrameContent(Point p, int zdelta, dword keyflags);
	bool MouseEventInFrameCaptured(int mouse_code, const Point& pt, dword keyflags);
	void MouseEventInFrameContent(int mouse_code, const Point& pt, dword keyflags);
	*/
	/*
	bool Redraw(bool only_pending);
	bool Is2D() const;
	Ctrl* Get2D();
	void DeepLayout();
	bool Dispatch(const CtrlEvent& e);
	void DeepFrameLayout();
	void MouseLeaveFrame();
	void DeepUnfocus();
	void PaintPreFrame(ProgPainter& pp);
	void PaintPostFrame(ProgPainter& pp);
	void PaintDebug(ProgPainter& pp);
	bool IsCtrl() const;
	
	void Update();
	*/
	
};






String GetKeyDesc(dword key);

Point GetMousePos();

bool ThreadHasGuiLock();




END_UPP_NAMESPACE

#endif
