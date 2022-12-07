#ifndef _CtrlCoreAlt_Ctrl_h_
#define _CtrlCoreAlt_Ctrl_h_


NAMESPACE_UPP
class Absolute2D;
END_UPP_NAMESPACE


namespace TS { namespace Ecs {

class Windows;
class WindowManager;
class Geom2DComponent;
class VirtualGui;
//class WindowSystem;
class DefaultGuiAppComponent;

}}


NAMESPACE_UPP

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
	void SetWithMouse(CtrlFrame* c);
	
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
	
	
	bool         inloop:1;
	
	Vector<CtrlFrame*> frames;
	Rect content_r;
	
	
	void Refresh0() {Refresh();}
	void Layout0() {Layout();}
	
public:
	friend class TS::Ecs::DefaultGuiAppComponent;
	
	
protected:
	friend class TS::Ecs::VirtualGui;
	//friend class TS::Ecs::WindowSystem;
	friend class TopWindow;
	
	
public:
	typedef Ctrl CLASSNAME;
	Ctrl();
	virtual ~Ctrl() {}
	
	static void SetDebugDraw(bool b=true) {do_debug_draw = b;}
	static bool ProcessEvent(bool *quit = NULL);
	static bool ProcessEvents(double dt, bool *quit = NULL);
	static bool ReleaseCtrlCapture();
	static Ctrl *GetCaptureCtrl();
	
	//vstatic oid EventLoop(Ctrl *ctrl);
	static void EventLoopIteration(double dt, bool* quit);
	
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
	
	Ctrl* GetParent();
	Ctrl* GetTopCtrl();
	TopWindow* GetTopWindow();
	
	Rect GetWorkArea() const;
	Size GetSize() const {return GetFrameSize();}
	
	void DeepFrameLayout() override;
	void SetFrameRect(const Rect& r) override;
	void DeepMouseMoveInFrame(Point pt, dword keyflags) override;
	bool MouseMoveInFrame(Point pt, dword keyflags) override;
	bool MouseEventInFrameCaptured(int mouse_code, const Point& pt, dword keyflags) override;
	bool MouseEventInFrame(int mouse_code, const Point& pt, dword keyflags) override;
	void MouseLeaveFrame() override;
	Rect GetContentRect() const override;
	Point GetContentPoint(const Point& pt) override;
	bool MouseWheelInFrame(Point p, int zdelta, dword keyflags) override;
	void SetFocus() override;
	void DeepUnfocus() override;
	void PaintPreFrame(ProgPainter& pp) override;
	void PaintPostFrame(ProgPainter& pp) override;
	void PaintDebug(ProgPainter& pp) override;
	bool IsCtrl() const override;
	void Refresh() override;
	
	void SetRect(const Rect& r);
	void SetPendingRedrawDeep();
	void Update();
	
	virtual int    OverPaint() const {return 0;}
	
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
	
public:
	//static void InitFB();
	//static void ExitFB();
	//static void SetDesktopSize(Size sz);
	static void Invalidate();
	
	Absolute2D* GetAbsolute2D();
	
	
	
};

class EmptySpaceCtrl : public Ctrl {
	RTTI_DECL1(EmptySpaceCtrl, Ctrl)
	
};




class Workspace2D : public GeomInteraction2D {
	
	
public:
	RTTI_DECL1(Workspace2D, GeomInteraction2D)
	virtual ~Workspace2D() {}
	
	virtual bool Init() = 0;
	virtual void AddWindow(Ecs::Geom2DComponent&) = 0;
	virtual bool Poll(CtrlEvent& e) = 0;
	virtual void Render() = 0;
	virtual void Shutdown() = 0;
	virtual bool ProcessCloseQueue() = 0;
	
};


class ParentCtrl : public Ctrl {
	
public:
	RTTI_DECL1(ParentCtrl, Ctrl)
	
	
	
	
};






END_UPP_NAMESPACE

#endif
