#ifndef _GuboCore_Gubo_h_
#define _GuboCore_Gubo_h_


NAMESPACE_TOPSIDE_BEGIN


class Gubo :
	public Pte<Gubo>,
	public GeomInteraction3D
{
	
public:
	RTTI_DECL1(Gubo, GeomInteraction3D)
	
protected:
	static  int       LoopLevel;
	static  Gubo     *LoopGubo;
	static  int64     EventLoopNo;
	
	Gubo* GetCaptured();
	Gubo* GetWithMouse();
	void SetCaptured(Gubo* c);
	void SetWithMouse(Gubo* c);
	GuboFrame* GetFrameCaptured();
	GuboFrame* GetFrameWithMouse();
	void SetFrameCaptured(GuboFrame* c);
	void SetFrameWithMouse(GuboFrame* c);
	
	
	bool         inloop:1;
	
	Vector<GuboFrame*> frames;
	Cubf content_r;
	
	
	void Refresh0() {Refresh();}
	
public:
	//friend class TS::Ecs::DefaultGuboAppComponent;
	
	
protected:
	//friend class TS::Ecs::VirtualGubo;
	//friend class TS::Ecs::WindowSystem;
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
	
	Volf GetContentVolf() const;
	void SetContentCubf(const Cubf& r);
	
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
	TopWindow* GetTopWindow();
	
	Cubf GetWorkArea() const;
	Volf GetVolf() const {return GetFrameVolf();}
	
	void DeepFrameLayout() override;
	void SetFrameBox(const Cubf& r) override;
	void DeepMouseMoveInFrameContent(Point pt, dword keyflags) override;
	void MouseMoveInFrameContent(Point pt, dword keyflags) override;
	bool MouseEventInFrameCaptured(int mouse_code, const Point& pt, dword keyflags) override;
	void MouseEventInFrameContent(int mouse_code, const Point& pt, dword keyflags) override;
	void MouseLeaveFrame() override;
	Cubf GetContentCubf() const override;
	Point GetContentPoint(const Point& pt) override;
	bool MouseWheelInFrameContent(Point p, int zdelta, dword keyflags) override;
	void SetFocus() override;
	void DeepUnfocus() override;
	void PaintPreFrame(ProgPainter& pp) override;
	void PaintPostFrame(ProgPainter& pp) override;
	void PaintDebug(ProgPainter& pp) override;
	bool IsGubo() const override;
	void Refresh() override;
	
	void SetCubf(const Cubf& r);
	void Update();
	
	virtual int    OverPaint() const {return 0;}
	
	Callback WhenAction;
	
	
	Gubo& operator <<= (Callback cb) {WhenAction = cb; return *this;}
	
	
public:
	Absolute3D* aw = 0;
	
	//static bool           invalid;
	//static uint32 prev_ticks;
	
	static void TimerProc(double dt);
	//static void GuboSleep(int ms);
	//static void DoPaint();
	//static void PaintScene(SystemDraw& draw);
	
public:
	//static void InitFB();
	//static void ExitFB();
	//static void SetDesktopVolf(Volf sz);
	static void Invalidate();
	
	Absolute3DInterface* GetAbsolute3D();
	
	
};


NAMESPACE_TOPSIDE_END


#endif
