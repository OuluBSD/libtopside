#ifndef _GuboCore_Gubo_h_
#define _GuboCore_Gubo_h_


NAMESPACE_TOPSIDE_BEGIN


class Gubo;


class GuboFrame :
	RTTIBase
{
public:
	RTTI_DECL0(GuboFrame)
	
	virtual void FrameLayout(Rect& r) = 0;
	virtual void FrameAddSize(Size& sz) = 0;
	virtual void FramePaint(Draw& w, const Rect& r);
	virtual void FrameAdd(Gubo& parent);
	virtual void FrameRemove();
	virtual int  OverPaint() const;

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
	RTTIBase
{
	
public:
	RTTI_DECL0(Gubo)
	
	static  bool do_debug_draw;
	
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
	
	
	void Refresh0() {TODO}
	void Layout0() {TODO}
	
	
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
	
	//void Add(GeomInteraction3D& c);
	void Add(Gubo& c);
	void AddFrame(GuboFrame& c);// {c.ctrl = this; frames.Add(&c); SetPendingRedraw();}
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
	
	
	Gubo* At(int i);
	
	bool Is3D() const;
	Gubo* Get3D();
	bool Redraw(bool only_pending);
	bool Dispatch(const CtrlEvent& e);
	void Refresh();
	
	virtual void Paint(Draw3& d) {}
	virtual void SetFrameBox(const Cubf& c);
	virtual Point3f GetContentPoint(const Point& pt);
	virtual Image FrameMouseEvent(int event, Point3f p, int zdelta, dword keyflags);
	virtual Image MouseEvent(int event, Point3f p, int zdelta, dword keyflags);
	virtual bool DeepMouseMoveInFrame(Point3f pt, dword keyflags);
	virtual bool DeepMouseMove(const Point3f& pt, dword keyflags);
	virtual bool MouseMoveInFrame(Point3f pt, dword keyflags);
	virtual bool MouseEventInFrameCaptured(int mouse_code, const Point& pt, dword keyflags);
	virtual bool MouseEventInFrame(int mouse_code, const Point& pt, dword keyflags);
	virtual bool MouseWheelInFrame(Point3f p, int zdelta, dword keyflags);
	virtual void MouseEnter(Point3f frame_p, dword keyflags);
	virtual void MouseMove(Point3f content_p, dword keyflags) {}
	virtual void LeftDown(Point3f p, dword keyflags) {}
	virtual void LeftDouble(Point3f p, dword keyflags) {}
	virtual void LeftTriple(Point3f p, dword keyflags) {}
	virtual void LeftDrag(Point3f p, dword keyflags) {}
	virtual void LeftHold(Point3f p, dword keyflags) {}
	virtual void LeftRepeat(Point3f p, dword keyflags) {}
	virtual void LeftUp(Point3f p, dword keyflags) {}
	virtual void RightDown(Point3f p, dword keyflags) {}
	virtual void RightDouble(Point3f p, dword keyflags) {}
	virtual void RightTriple(Point3f p, dword keyflags) {}
	virtual void RightDrag(Point3f p, dword keyflags) {}
	virtual void RightHold(Point3f p, dword keyflags) {}
	virtual void RightRepeat(Point3f p, dword keyflags) {}
	virtual void RightUp(Point3f p, dword keyflags) {}
	virtual void MiddleDown(Point3f p, dword keyflags) {}
	virtual void MiddleDouble(Point3f p, dword keyflags) {}
	virtual void MiddleTriple(Point3f p, dword keyflags) {}
	virtual void MiddleDrag(Point3f p, dword keyflags) {}
	virtual void MiddleHold(Point3f p, dword keyflags) {}
	virtual void MiddleRepeat(Point3f p, dword keyflags) {}
	virtual void MiddleUp(Point3f p, dword keyflags) {}
	virtual void MouseWheel(Point3f p, int zdelta, dword keyflags) {}
	virtual Image CursorImage(Point3f p, dword keyflags);
	virtual void PadTouch(int controller, Point3f p) {}
	
	virtual void   Close();
	virtual void   MouseLeave();
	virtual void   Layout();
	virtual void   CancelMode();
	
	bool    HasCapture() const;
	bool    HasMouse() const;
	
	Volf GetFrameSize() const;
	Cubf GetFrameBox() const;
	
	void StartDrag();
	
	bool ReleaseCapture();
	
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
