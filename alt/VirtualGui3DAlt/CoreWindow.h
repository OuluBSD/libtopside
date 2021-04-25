#ifndef _CtrlCore_CoreWindow_h_
#define _CtrlCore_CoreWindow_h_

NAMESPACE_OULU_BEGIN


struct WindowsImg {
	static Image& close();
	static Image& maximize();
	static Image& minimize();
	static Image& nwse();
	static Image& nesw();
	static Image& ns();
	static Image& ew();
};

class Windows;

class WindowDecoration : public Ctrl {
	CoreWindow* win = NULL;
	String label;
	bool left_down;
	Point left_down_pt;
	
public:
	typedef WindowDecoration CLASSNAME;
	WindowDecoration(CoreWindow*);
	
	virtual void Paint(Draw& draw);
	
	void SetLabel(String str) {label = str;}
	
	String GetLabel() const {return label;}
	
	virtual void LeftDown(Point p, dword keyflags);
	virtual void LeftDouble(Point p, dword keyflags);
	virtual void LeftUp(Point p, dword keyflags);
	virtual void MouseMove(Point p, dword keyflags);
	virtual void RightDown(Point p, dword keyflags);
	
	void LocalMenu(Bar& bar);
	
	
};



class CoreWindow : public Ctrl, public Component<CoreWindow> {
	struct ResizeFrame : public CtrlFrame {
		CoreWindow* win = NULL;
		Size sz;
		int frame_width = 8;
		int corner_width = 24;
		bool is_active = false;
		bool is_resizing = false;
		Point resize_start_pt;
		Rect resize_start_r;
		int resize_area = 0;
		Point resize_diff;
		bool used_momentum = false;
		
		enum {CENTER, TL, TR, BL, BR, TOP, BOTTOM, LEFT, RIGHT};
		int GetArea(Point pt);
		void SetActive(bool b) {frame_width = b ? 8 : 0;}
		virtual void FrameLayout(Rect& r);
		virtual void FramePaint(Draw& w, const Rect& r);
		virtual void FrameAddSize(Size& sz);
		virtual void MouseEnter(Point frame_p, dword keyflags);
		virtual void MouseMove(Point frame_p, dword keyflags);
		virtual void MouseLeave();
		virtual void LeftDown(Point p, dword keyflags);
		virtual void LeftUp(Point p, dword keyflags);
		virtual void ContinueGlobalMouseMomentum();
		void DoResize();
	};
	
	One<Shader> shader;
	
	One<TopWindow> tw;
	void (CoreWindow::*reset_fn)();
	Windows* wins = NULL;
	
	Vector<mat4> offset;
	DrawCommand cmd_screen_begin, cmd_screen_end;
	//Framebuffer fb;
	ResizeFrame resize_frame;
	WindowDecoration decor;
	Button minimize, maximize, close;
	Rect stored_rect;
	//Point global_mouse;
	//bool is_global_mouse_override = false;
	int id = -1;
	bool pending_partial_redraw = false;
	
protected:
	friend class Windows;
	friend class SDL2;
	
	
	void SetContent(Windows* wins, int id);
	
	bool maximized;
	
	void SetMaximized(bool b=true);
	
	void DrawLine(DrawCommand& cmd);
	void DrawImage(DrawCommand& cmd);
	void DrawRect(DrawCommand& cmd);
	void DrawTriangles(DrawCommand& cmd);
	void DrawPolyline(DrawCommand& cmd);
	void DrawPolygon(DrawCommand& cmd);
	void DrawOffset(DrawCommand& cmd);
	void DrawEnd(DrawCommand& cmd);
	
public:
	Weak<Transform>    transform;
	Weak<Transform2D>  transform2d;
	
public:
	typedef CoreWindow CLASSNAME;
	CoreWindow();
	CoreWindow(const CoreWindow& cw) : stored_rect(0,0,0,0), decor(this) {*this = cw;}
	
	void operator=(const CoreWindow& cw) {
		Clear();
		reset_fn = cw.reset_fn;
		SetFrameRect(cw.frame_r);
		if (reset_fn)
			(*this.*reset_fn)();
	}
	
	template <class T>
	void ResetTopWindow() {
		Clear();
		T* t = new T();
		tw = static_cast<TopWindow*>(t);
	}
	template <class T>
	T& Create() {
		Clear();
		T* t = new T();
		tw = static_cast<TopWindow*>(t);
		reset_fn = &CoreWindow::ResetTopWindow<T>;
		return *t;
	}
	
	void Clear() {
		if (tw.IsEmpty()) return;
		RemoveChild(tw.Get());
		tw.Clear();
	}
	
	Point GetGlobalMouse();
	//bool IsGlobalMouseOverridden() const {return pending_partial_redraw;}
	//void SetGlobalMouse(Point pt) {is_global_mouse_override = true; global_mouse = pt;}
	void Title(String label) {decor.SetLabel(label);}
	void StoreRect() {stored_rect = GetFrameRect();}
	void LoadRect() {ASSERT(stored_rect.bottom && stored_rect.right); SetFrameRect(stored_rect);}
	void SetStoredRect(Rect r) {stored_rect = r;}
	void SetPendingPartialRedraw(bool b=true) {pending_partial_redraw = b;}
	
	//GLuint GetTexture() {return fb.GetTexture();}
	//const Framebuffer& GetFramebuffer() const {return fb;}
	int GetId() const {return id;}
	Rect GetStoredRect() const {return stored_rect;}
	String GetTitle() const {return decor.GetLabel();}
	TopWindow* GetTopWindow() {return tw.Get();}
	bool IsMaximized() const {return maximized;}
	bool IsActive() const;
	void MoveWindow(Point pt);
	void Maximize();
	void Restore();
	void Minimize();
	void Close();
	void FocusEvent();
	void ToggleMaximized() {if (IsMaximized()) Restore(); else Maximize();}
	bool IsPendingPartialRedraw() const {return pending_partial_redraw;}
	void Wait();
	
	void SetFrameRect(const Rect& r) override;
	bool Redraw(bool only_pending) override;
	void LeftDown(Point p, dword keyflags) override;
	void ChildGotFocus() override;
	virtual void ChildMouseEvent(Ctrl *child, int event, Point p, int zdelta, dword keyflags);
};




#ifdef flagOPENVR
template <class T>
struct Window : EntityPrefab<CoreWindow, Transform, VR_ScreenWindow> {
    static Components Make(Entity& e)
    {
        auto components = EntityPrefab::Make(e);
		
		//components.Get<CoreWindow>()->renderable = components.GetRef<Renderable>();
		components.Get<CoreWindow>()->transform = components.GetRef<Transform>();
		
		components.Get<Transform>().position = vec3(0, 0, -1);
		components.Get<Transform>().size = vec3(320, 240, 0);
		
        //components.Get<Renderable>()->ResetModel(KnownModelNames::UnitQuad);
        //components.Get<Renderable>()->color = Rgba(1.0, 1.0, 1.0, 1.0);
		
		components.Get<CoreWindow>()->Create<T>();
		
        return components;
    }
};
#endif



template <class T>
struct Window2D : EntityPrefab<CoreWindow, Transform2D> {
    static Components Make(Entity& e)
    {
        auto components = EntityPrefab::Make(e);
		
		//components.Get<CoreWindow>()->renderable2d = components.GetRef<Renderable2D>();
		components.Get<CoreWindow>()->transform2d = components.GetRef<Transform2D>();
		
		components.Get<Transform2D>()->position = vec2(0, 0);
		components.Get<Transform2D>()->size = vec2(320, 240);
		
		T& t = components.Get<CoreWindow>()->Create<T>();
		ASSERT(&t);
		
        return components;
    }
};


NAMESPACE_OULU_END

#endif
