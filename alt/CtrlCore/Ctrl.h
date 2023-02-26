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


struct ClipData : Moveable<ClipData> {
	Value  data;
	String (*render)(const Value& data);

	String  Render() const                   { return render ? (*render)(data) : ~data; }

	ClipData(const Value& data, String (*render)(const Value& data));
	ClipData(const String& data);
	ClipData();
};


class PasteClip {
	friend struct UDropTarget;
	friend class  Ctrl;
	friend PasteClip sMakeDropClip(bool paste);

	GUIPLATFORM_PASTECLIP_DECLS

	byte         action;
	byte         allowed;
	bool         paste;
	bool         accepted;
	String       fmt;
	String       data;

	void GuiPlatformConstruct();

public:
	bool   IsAvailable(const char *fmt) const;
	String Get(const char *fmt) const;

	bool   Accept();

	bool   Accept(const char *fmt);
	String GetFormat()                  { return fmt; }
	String Get() const                  { return data; }
	operator String() const             { return Get(); }
	String operator ~() const           { return Get(); }

	void   Reject()                     { accepted = false; }

	int    GetAction() const            { return action; }
	int    GetAllowedActions() const    { return allowed; }
	void   SetAction(int x)             { action = x; }

	bool   IsAccepted() const           { return accepted; }

	bool   IsQuery() const              { return !paste; }
	bool   IsPaste() const              { return paste; }

	PasteClip();
};



class Ctrl;

class CtrlFrame :
	public GeomInteraction2D
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
	RTTI_DECL1(CtrlFrame, GeomInteraction2D)
	
	virtual void FramePaint(Draw& w, const Rect& r) {}
	/*virtual void FrameLayout(Rect& r) = 0;
	virtual void FrameAddSize(Size& sz) = 0;
	virtual void FrameAdd(Ctrl& parent);
	virtual void FrameRemove();
	virtual int  OverPaint() const;
	virtual void MouseEnter(Point frame_p, dword keyflags) {}
	virtual void MouseMove(Point frame_p, dword keyflags) {}
	virtual void MouseLeave() {}
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
	virtual void MouseWheel(Point p, int zdelta, dword keyflags) {}*/
	virtual void ContinueGlobalMouseMomentum() {}
	void SetCapture();
	void ReleaseCapture();

	CtrlFrame() {}
	virtual ~CtrlFrame() {}

private:
	CtrlFrame(const CtrlFrame&);
	void operator=(const CtrlFrame&);
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
	public GeomInteraction2D
{
	
public:
	RTTI_DECL1(Ctrl, GeomInteraction2D)
	
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

	Vector<CtrlFrame*> frames;
	Rect content_r;
	
	
	void Refresh0() {Refresh();}
	void Layout0() {Layout();}
	
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
	
	Size GetContentSize() const;
	void SetContentRect(const Rect& r);
	
	void Add(GeomInteraction2D& c);
	void Add(Ctrl& c);
	void AddFrame(CtrlFrame& c) {c.ctrl = this; frames.Add(&c); SetPendingRedraw();}
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
	
	Size GetSize() const {return GetFrameSize();}
	String Name() const;
	
	void DeepFrameLayout() override;
	void SetFrameBox(const Rect& r) override;
	void DeepMouseMoveInFrameContent(Point pt, dword keyflags) override;
	void MouseMoveInFrameContent(Point pt, dword keyflags) override;
	bool MouseEventInFrameCaptured(int mouse_code, const Point& pt, dword keyflags) override;
	void MouseEventInFrameContent(int mouse_code, const Point& pt, dword keyflags) override;
	void MouseLeaveFrame() override;
	Rect GetContentRect() const override;
	Point GetContentPoint(const Point& pt) override;
	bool MouseWheelInFrameContent(Point p, int zdelta, dword keyflags) override;
	void SetFocus() override;
	void DeepUnfocus() override;
	void PaintPreFrame(ProgPainter& pp) override;
	void PaintPostFrame(ProgPainter& pp) override;
	void PaintDebug(ProgPainter& pp) override;
	bool IsCtrl() const override;
	void Refresh() override;
	
	void SetRect(const Rect& r);
	void SetRect(int x, int y, int cx, int cy);
	void Update();
	
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




class BorderFrame : public CtrlFrame {
public:
	virtual void FrameLayout(Rect& r);
	virtual void FramePaint(Draw& w, const Rect& r);
	virtual void FrameAddSize(Size& sz);

protected:
	const ColorF *border;

public:
	BorderFrame(const ColorF *border) : border(border) {}
};



CtrlFrame& InsetFrame();

String GetKeyDesc(dword key);

Point GetMousePos();





END_UPP_NAMESPACE

#endif
