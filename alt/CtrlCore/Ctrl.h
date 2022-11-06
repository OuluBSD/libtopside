#ifndef _CtrlCoreAlt_Ctrl_h_
#define _CtrlCoreAlt_Ctrl_h_

namespace TS { namespace Ecs {

class Windows;
class WindowManager;
class CoreWindow;
class VirtualGui;
class WindowSystem;
class DefaultGuiAppComponent;

}}


NAMESPACE_UPP

class Ctrl;

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
	void SetWithMouse(CtrlFrame* c);
	
public:
	RTTI_DECL0(CtrlFrame)
	
	virtual void FrameLayout(Rect& r) = 0;
	virtual void FrameAddSize(Size& sz) = 0;
	virtual void FramePaint(Draw& w, const Rect& r);
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
	virtual void MouseWheel(Point p, int zdelta, dword keyflags) {}
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
	int l = 0, r = 0, t = 0, b = 0, w = 0, h = 0;
	Byte vtype = 0, htype = 0;
};

class TopWindow;
//class CoreWindow;

class Ctrl :
	public Pte<Ctrl>,
	public VirtualCtrl
{
	
public:
	RTTI_DECL1(Ctrl, VirtualCtrl)
	
protected:
	
	
	
	
	static  int       LoopLevel;
	static  Ctrl     *LoopCtrl;
	static  int64     EventLoopNo;
	static  bool      do_debug_draw;
	
	Ctrl* GetCaptured();
	Ctrl* GetWithMouse();
	void SetCaptured(Ctrl* c);
	void SetWithMouse(Ctrl* c);
	CtrlFrame* GetFrameCaptured();
	CtrlFrame* GetFrameWithMouse();
	void SetFrameCaptured(CtrlFrame* c);
	void SetFrameWithMouse(CtrlFrame* c);
	
	
	
	bool         inloop:1;
	bool         ignore_mouse:1;
	bool         hidden:1;
	bool         want_focus:1;
	bool         has_focus:1;
	bool         has_focus_deep:1;
	bool         has_mouse:1;
	bool         has_mouse_deep:1;
	bool         pending_fx_redraw:1;
	bool         pending_redraw:1;
	bool         pending_layout:1;
	bool         modify:1;
	
	Ctrl* parent = NULL;
	Vector<Ctrl*> children;
	Vector<CtrlFrame*> frames;
	LogPos pos;
	Rect frame_r, content_r;
	DrawCommand cmd_begin, cmd_frame, cmd_pre, cmd_post, cmd_end;
	
	virtual bool Redraw(bool only_pending);
	void DeepMouseLeave();
	void Refresh0() {Refresh();}
	void Layout0() {Layout();}
	
public:
	friend class TS::Ecs::DefaultGuiAppComponent;
	
	bool DeepKey(dword key, int count);
	bool DeepMouseMove(const Point& pt, dword keyflags);
	bool DeepMouse(int mouse_code, const Point& pt, dword keyflags);
	bool DeepMouseWheel(const Point& pt, int zdelta, dword keyflags);
	
protected:
	friend class TS::Ecs::VirtualGui;
	friend class TS::Ecs::WindowSystem;
	friend class TopWindow;
	
	void SetFrameRect0(const Rect& r) {this->frame_r = r;}
	
public:
	typedef Ctrl CLASSNAME;
	Ctrl();
	virtual ~Ctrl() {}
	
	static void SetDebugDraw(bool b=true) {do_debug_draw = b;}
	static void CloseTopCtrls();
	static bool ProcessEvent(bool *quit = NULL);
	static bool ProcessEvents(bool *quit = NULL);
	static bool  ReleaseCtrlCapture();
	static Ctrl *GetCaptureCtrl();
	static Image OverrideCursor(const Image& m);
	static Image DefaultCursor();
	
	//void EventLoop(Ctrl *ctrl);
	
	DrawCommand& GetCommandBegin() {return cmd_begin;}
	DrawCommand& GetCommandEnd() {return cmd_end;}
	
	void Add(Ctrl& c);
	void AddFrame(CtrlFrame& c) {c.ctrl = this; frames.Add(&c); SetPendingRedraw();}
	void AddChild(Ctrl* c);
	Ctrl* GetLastChild();
	Ctrl* GetIndexChild(int i) {return children[i];}
	void RemoveChild(Ctrl* c);
	void DeepLayout();
	int GetChildCount() const {return children.GetCount();}
	
	Ctrl* GetParent();
	TopWindow* GetTopWindow();
	int GetCount() const {return children.GetCount();}
	Ctrl* operator[](int i) {return children[i];}
	
	Rect GetFrameRect() const {return frame_r;}
	Rect GetContentRect() const {return content_r;}
	Rect GetRect() const {return GetFrameRect();}
	Rect GetWorkArea() const;
	Size GetFrameSize() const {return frame_r.GetSize();}
	Size GetContentSize() const {return content_r.GetSize();}
	bool IsShown() const;
	bool HasFocus() const {return has_focus;}
	bool HasFocusDeep() const {return has_focus_deep;}
	bool HasMouse() const {return has_mouse;}
	bool HasMouseDeep() const {return has_mouse_deep;}
	bool IsPendingLayout() const {return pending_layout;}
	const LogPos& GetLogPos() const {return pos;}
	Size GetSize() const {return GetContentSize();}
	
	virtual void SetFrameRect(const Rect& r);
	void SetFrameRect(int x, int y, int w, int h) {SetFrameRect(Rect(x, y, x+w, y+h));}
	void SetRect(const Rect& r) {SetFrameRect(r);}
	void SetContentRect(const Rect& r) {content_r = r;}
	void SetPendingLayout() {pending_layout = true;}
	void SetPendingRedraw() {pending_redraw = true;}
	void SetPendingRedrawDeep();
	void SetPendingEffectRedraw() {pending_fx_redraw = true;}
	void SetFocus();
	void WantFocus(bool b=true) {want_focus = b;}
	void IgnoreMouse(bool b=true) {ignore_mouse = b;}
	
	void Show(bool b=true);
	void Hide() {Show(false);}
	void Refresh();
	void PostCallback(Callback cb);
	void PostRefresh();
	void PostLayoutCallback();
	void SetCapture();
	void ReleaseCapture();
	void DeepUnfocus();
	
	Ctrl& SizePos() {return HSizePos().VSizePos();}
	Ctrl& HSizePos(int l=0, int r=0);
	Ctrl& VSizePos(int t=0, int b=0);
	Ctrl& BottomPos(int i, int size);
	Ctrl& TopPos(int i, int size);
	Ctrl& LeftPos(int i, int size);
	Ctrl& RightPos(int i, int size);
	
	virtual void Activate() {}
	virtual void Deactivate() {}
	virtual Image FrameMouseEvent(int event, Point p, int zdelta, dword keyflags) {return DefaultImages::Arrow;}
	virtual Image MouseEvent(int event, Point p, int zdelta, dword keyflags) {return DefaultImages::Arrow;}
	virtual void MouseEnter(Point frame_p, dword keyflags) {if (do_debug_draw) Refresh();}
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
	virtual void MouseLeave() {if (do_debug_draw) Refresh();}
	virtual void PadTouch(int controller, Pointf p) {}
	virtual void PadUntouch(int controller) {}
	virtual Image CursorImage(Point p, dword keyflags) {return DefaultImages::Arrow;}
	virtual bool Key(dword key, int count) {return false;}
	virtual void Paint(Draw& d) {}
	virtual void Layout() {}
	virtual void PostLayout() {}
	virtual void GotFocus() {}
	virtual void LostFocus() {}
	virtual void ChildGotFocus() {}
	virtual void ChildLostFocus() {}
	virtual void Updated() {}
	virtual bool IsModified() const;
	virtual void SetModify();
	virtual void ClearModify();
	void    Update();
	
	virtual Size   GetMinSize() const {return Size(0,0);}
	virtual String GetDesc() const {return String();}
	virtual void   FrameLayout(Rect& r) {}
	virtual void   FrameAddSize(Size& sz) {}
	virtual bool   HotKey(dword key) {return false;}
	virtual int    OverPaint() const {return 0;}
	
	Callback WhenAction;
	
	
	
	Ctrl& operator <<= (Callback cb) {WhenAction = cb; return *this;}
	
	
	
	
	
	
	
	
	
	#include GUIPLATFORM_CTRL_DECLS_INCLUDE
	
	
	
	
};

class EmptySpaceCtrl : public Ctrl {
	RTTI_DECL1(EmptySpaceCtrl, Ctrl)
	
};




class Screen : public Ctrl {
	
	
public:
	RTTI_DECL1(Screen, Ctrl)
	virtual ~Screen() {}
	
	virtual bool Init() = 0;
	virtual void AddWindow(Ecs::CoreWindow&) = 0;
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
