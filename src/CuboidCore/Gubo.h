#ifndef _GuboCore_Gubo_h_
#define _GuboCore_Gubo_h_


NAMESPACE_TOPSIDE_BEGIN


class Gubo;


class GuboFrame :
	public GeomInteraction3D
{
	
protected:
	friend class Gubo;
	
	Gubo* ctrl = NULL;
	bool has_mouse = false;
	
	GuboFrame* GetCaptured();
	GuboFrame* GetWithMouse();
	void SetCaptured(GuboFrame* c);
	void SetWithMouse(GuboFrame* c);
	
public:
	RTTI_DECL1(GuboFrame, GeomInteraction3D)
	
	virtual void FramePaint(Draw& w, const Rect& r) {}
	/*virtual void FrameLayout(Rect& r) = 0;
	virtual void FrameAddSize(Size& sz) = 0;
	virtual void FrameAdd(Gubo& parent);
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

	GuboFrame() {}
	virtual ~GuboFrame() {}

private:
	GuboFrame(const GuboFrame&);
	void operator=(const GuboFrame&);
};



class TopGubo;


// Gui Cuboid --> Gubo (based on Ctrl class, which is a gui class)
class Gubo :
	public Pte<Gubo>,
	public GeomInteraction3D
{
	
public:
	RTTI_DECL1(Gubo, GeomInteraction3D)
	
protected:
	static  int       LoopLevel;
	static  Gubo   *LoopGubo;
	static  int64     EventLoopNo;
	
	Gubo* GetCaptured();
	Gubo* GetWithMouse();
	void SetCaptured(Gubo* c);
	void SetWithMouse(Gubo* c);
	GuboFrame* GetFrameCaptured();
	GuboFrame* GetFrameWithMouse();
	void SetFrameCaptured(GuboFrame* c);
	void SetFrameWithMouse(GuboFrame* c);
	
	
	void* frame = 0;
	bool         inloop:1;
	
	Vector<GuboFrame*> frames;
	Vol content_r;
	
	
	void Refresh0() {Refresh();}
	void Layout0() {Layout();}
	
	
protected:
	friend class TopWindow;
	
	
public:
	typedef Gubo CLASSNAME;
	Gubo();
	virtual ~Gubo() {}
	
	static void SetDebugDraw(bool b=true) {do_debug_draw = b;}
	static bool ProcessEvent(bool *quit = NULL);
	static bool ProcessEvents(double dt, bool *quit = NULL);
	static bool ReleaseGuboCapture();
	static Gubo *GetCaptureGubo();
	
	//vstatic oid EventLoop(Gubo *ctrl);
	static void EventLoopIteration(double dt, bool* quit);
	
	Size GetContentSize() const;
	void SetContentRect(const Rect& r);
	template<class T> void SetTopFrame(T& tgf) {frame = &tgf;}
	
	void Add(GeomInteraction3D& c);
	void Add(Gubo& c);
	void AddFrame(GuboFrame& c) {c.ctrl = this; frames.Add(&c); SetPendingRedraw();}
	void AddChild(Gubo* c);
	Gubo* GetLastChild();
	Gubo* GetIndexChild(int i);
	void RemoveChild(Gubo* c);
	int GetChildCount() const;
	
	Gubo* GetParent();
	Gubo* GetTopGubo();
	
	/*
	Rect GetWorkArea() const;
	Size GetSize() const {return GetFrameSize();}
	
	void DeepFrameLayout() override;
	void SetFrameRect(const Rect& r) override;
	bool DeepMouseMoveInFrame(Point pt, dword keyflags) override;
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
	bool IsGubo() const override;
	void Refresh() override;
	
	void SetRect(const Rect& r);
	void SetPendingRedrawDeep();
	void Update();
	
	virtual int    OverPaint() const {return 0;}
	*/
	
	Callback WhenAction;
	
	
	Gubo& operator <<= (Callback cb) {WhenAction = cb; return *this;}
	
	
public:
	
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
	
	
};

class EmptySpaceGubo : public Gubo {
	RTTI_DECL1(EmptySpaceGubo, Gubo)
	
};



class ParentGubo : public Gubo {
	
public:
	RTTI_DECL1(ParentGubo, Gubo)
	
	
	
	
};


NAMESPACE_TOPSIDE_END


#endif
