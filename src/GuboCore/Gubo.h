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
	static  bool      do_debug_draw;
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
	Cubf content;
	
	
	void Refresh0() {Refresh();}
	
public:
	//friend class TS::Ecs::DefaultGuboAppComponent;
	
	
protected:
	//friend class TS::Ecs::VirtualGubo;
	//friend class TS::Ecs::WindowSystem;
	friend class TopSurface;
	
	
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
	void AddFrame(GuboFrame& c) {c.gubo = this; frames.Add(&c); SetPendingRedraw();}
	void AddChild(Gubo* c);
	Gubo* GetLastChild();
	Gubo* GetIndexChild(int i);
	void RemoveChild(Gubo* c);
	int GetChildCount() const;
	
	Gubo* GetParent();
	Gubo* GetTopGubo();
	TopSurface* GetTopSurface();
	
	Cubf GetWorkArea() const;
	Volf GetSize() const {return GetFrameSize();}
	Volf GetContentSize() const;
	
	void DeepFrameLayout() override;
	void SetFrameBox(const Cubf& r) override;
	void DeepMouseMoveInFrameContent(Point3f pt, dword keyflags) override;
	void MouseMoveInFrameContent(Point3f pt, dword keyflags) override;
	bool MouseEventInFrameCaptured(int mouse_code, const Point3f& pt, dword keyflags) override;
	void MouseEventInFrameContent(int mouse_code, const Point3f& pt, dword keyflags) override;
	void MouseLeaveFrame() override;
	Cubf GetContentBox() const override;
	Point3f GetContentPoint(const Point3f& pt) override;
	bool MouseWheelInFrameContent(Point3f p, int zdelta, dword keyflags) override;
	void SetFocus() override;
	void DeepUnfocus() override;
	void PaintPreFrame(ProgPainter3& pp) override;
	void PaintPostFrame(ProgPainter3& pp) override;
	void PaintDebug(ProgPainter3& pp) override;
	bool IsGubo() const;
	void Refresh() override;
	Gubo* GetGubo() override {return this;}
	
	void SetCubf(const Cubf& r);
	void SetContentBox(const Cubf& r);
	void Update();
	
	virtual int    OverPaint() const {return 0;}
	
	Callback WhenAction;
	
	Gubo& operator <<= (Callback cb) {WhenAction = cb; return *this;}
	
};


NAMESPACE_TOPSIDE_END


#endif
