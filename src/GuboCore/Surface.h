#ifndef _GuboCore_Surface_h_
#define _GuboCore_Surface_h_


NAMESPACE_TOPSIDE_BEGIN
class Absolute2D;
NAMESPACE_TOPSIDE_END



NAMESPACE_TOPSIDE_BEGIN

class Surface;

class SurfaceFrame :
	public GeomInteraction2D
{
	
protected:
	friend class Surface;
	
	Surface* ctrl = NULL;
	bool has_mouse = false;
	
	SurfaceFrame* GetCaptured();
	SurfaceFrame* GetWithMouse();
	void SetCaptured(SurfaceFrame* c);
	void SetWithMouse(SurfaceFrame* c);
	
public:
	RTTI_DECL1(SurfaceFrame, GeomInteraction2D)
	
	virtual void FramePaint(Draw& w, const Rect& r) {}
	/*virtual void FrameLayout(Rect& r) = 0;
	virtual void FrameAddSize(Size& sz) = 0;
	virtual void FrameAdd(Surface& parent);
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

	SurfaceFrame() {}
	virtual ~SurfaceFrame() {}

private:
	SurfaceFrame(const SurfaceFrame&);
	void operator=(const SurfaceFrame&);
};


#if IS_UPP_CORE
using KeyInfo = ::UPP::KeyInfo;
#endif




class TopSurface;

class Surface :
	public Pte<Surface>,
	public GeomInteraction2D
{
	
public:
	RTTI_DECL1(Surface, GeomInteraction2D)
	
protected:
	static  int       LoopLevel;
	static  Surface     *LoopSurface;
	static  int64     EventLoopNo;
	
	Surface* GetCaptured();
	Surface* GetWithMouse();
	void SetCaptured(Surface* c);
	void SetWithMouse(Surface* c);
	SurfaceFrame* GetFrameCaptured();
	SurfaceFrame* GetFrameWithMouse();
	void SetFrameCaptured(SurfaceFrame* c);
	void SetFrameWithMouse(SurfaceFrame* c);
	
	
	bool         inloop:1;
	
	Vector<SurfaceFrame*> frames;
	Rect content_r;
	
	
	void Refresh0() {Refresh();}
	void Layout0() {Layout();}
	
	
public:
	typedef Surface CLASSNAME;
	Surface();
	virtual ~Surface() {}
	
	static void SetDebugDraw(bool b=true) {do_debug_draw = b;}
	static bool ProcessEvent(bool *quit = NULL);
	static bool ProcessEvents(double dt, bool *quit = NULL);
	static bool ReleaseSurfaceCapture();
	static Surface *GetCaptureSurface();
	
	//static oid EventLoop(Surface *ctrl);
	
	Size GetContentSize() const;
	void SetContentRect(const Rect& r);
	
	void Add(GeomInteraction2D& c);
	void Add(Surface& c);
	void AddFrame(SurfaceFrame& c) {c.ctrl = this; frames.Add(&c); SetPendingRedraw();}
	void AddChild(Surface* c);
	Surface* GetLastChild();
	Surface* GetIndexChild(int i);
	void RemoveChild(Surface* c);
	int GetChildCount() const;
	
	Surface* GetParent();
	TopSurface* GetTopSurface();
	
	Rect GetWorkArea() const;
	Size GetSize() const {return GetFrameSize();}
	
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
	bool IsSurface() const override;
	void Refresh() override;
	Surface* GetSurface() override {return this;}
	
	void SetRect(const Rect& r);
	void Update();
	
	virtual int    OverPaint() const {return 0;}
	
	Callback WhenAction;
	
	
	Surface& operator <<= (Callback cb) {WhenAction = cb; return *this;}
	
	
public:
	static void EventLoopIteration(void*);
	static void TimerProc(double dt);
	static void Invalidate();
	static void EventLoop();
	static void PaintAll(bool b);
	static void InitFB();
	static void ExitFB();
	static void SetDesktopSize(Size sz);
	
};

class EmptySpaceSurface : public Surface {
	RTTI_DECL1(EmptySpaceSurface, Surface)
	
};



class ParentSurface : public Surface {
	
public:
	RTTI_DECL1(ParentSurface, Surface)
	
	
	
	
};






NAMESPACE_TOPSIDE_END

#endif
