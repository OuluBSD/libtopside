#ifndef _EcsLib_Geom2DComponent_h_
#define _EcsLib_Geom2DComponent_h_

#ifdef flagGUI

NAMESPACE_ECS_BEGIN


#if 0

class Windows;

class WindowDecoration : public GeomInteraction2D {
	Geom2DComponent* win = NULL;
	String label;
	bool left_down;
	Point left_down_pt;
	
public:
	RTTI_DECL1(WindowDecoration, GeomInteraction2D)
	typedef WindowDecoration CLASSNAME;
	WindowDecoration(Geom2DComponent*);
	
	virtual void Paint(Draw& draw) override;
	
	void SetLabel(String str) {label = str;}
	
	String GetLabel() const {return label;}
	
	virtual void LeftDown(Point p, dword keyflags) override;
	virtual void LeftDouble(Point p, dword keyflags) override;
	virtual void LeftUp(Point p, dword keyflags) override;
	virtual void MouseMove(Point p, dword keyflags) override;
	virtual void RightDown(Point p, dword keyflags) override;
	
	void LocalMenu(Bar& bar);
	
	
};

#endif

struct Geom2DComponentLink;

class Geom2DComponent :
	public GeomInteraction2D,
	/*public Absolute2D,*/
	public Component<Geom2DComponent>
{
	RTTI_COMP1(Geom2DComponent, GeomInteraction2D)
	
	#if 0
	struct ResizeFrame : public CtrlFrame {
		RTTI_DECL1(ResizeFrame, CtrlFrame)
	
		Geom2DComponent* win = NULL;
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
		virtual void FrameLayout(Rect& r) override;
		virtual void FramePaint(Draw& w, const Rect& r) override;
		virtual void FrameAddSize(Size& sz) override;
		virtual void MouseEnter(Point frame_p, dword keyflags) override;
		virtual void MouseMove(Point frame_p, dword keyflags) override;
		virtual void MouseLeave() override;
		virtual void LeftDown(Point p, dword keyflags) override;
		virtual void LeftUp(Point p, dword keyflags) override;
		virtual void ContinueGlobalMouseMomentum() override;
		void DoResize();
	};
	#endif
	
public:
	//One<Absolute2DInterface> owned_aw;
	//Absolute2DInterface* aw = 0;
	//Windows* wins = NULL;
	void (Geom2DComponent::*reset_fn)() = 0;
	Geom2DComponentLink* linked = NULL;
	TransformRef    transform;
	Transform2DRef  transform2d;
	
	//ResizeFrame resize_frame;
	//WindowDecoration decor;
	//Button minimize, maximize, close;
	Rect stored_rect;
	int id = -1;
	bool pending_partial_redraw = false;
	
protected:
	friend class Windows;
	friend class SDL2;
	
	bool maximized;
	
	//void SetContent(Windows* wins, int id);
	void SetMaximized(bool b=true);
	
public:
	typedef Geom2DComponent CLASSNAME;
	Geom2DComponent();
	Geom2DComponent(const Geom2DComponent& cw) : stored_rect(0,0,0,0)/*, decor(this)*/ {
		*this = cw;
	}
	void operator=(const Geom2DComponent& cw);
	
	#if 0
	template <class T>
	void ResetTopWindow() {
		Clear();
		T* t = new T();
		aw = static_cast<Absolute2DInterface*>(t);
	}
	template <class T>
	T& Create() {
		Clear();
		T* t = new T();
		owned_aw = static_cast<Absolute2DInterface*>(t);
		aw = &*owned_aw;
		reset_fn = &Geom2DComponent::ResetTopWindow<T>;
		return *t;
	}
	#endif
	
	void Clear();
	//void DeepLayout();
	Point GetGlobalMouse();
	//bool IsGlobalMouseOverridden() const {return pending_partial_redraw;}
	//void SetGlobalMouse(Point pt) {is_global_mouse_override = true; global_mouse = pt;}
	void Title(String label);
	void StoreRect();
	void LoadRect();
	void SetStoredRect(Rect r);
	void SetPendingPartialRedraw() override;
	
	//GLuint GetTexture() {return fb.GetTexture();}
	//const Framebuffer& GetFramebuffer() const {return fb;}
	int GetId() const;
	Rect GetStoredRect() const;
	//Absolute2DInterface* GetAbsolute2D();
	bool IsMaximized() const;
	bool IsActive() const;
	void MoveWindow(Point pt);
	void Maximize();
	void Restore();
	void Minimize();
	//void Close() override;
	//void FocusEvent() override;
	void ToggleMaximized();
	bool IsPendingPartialRedraw() const;
	void Wait();
	//Windows* GetWindows() const {return wins;}
	TopWindow* GetTopWindow() const;
	
	void Etherize(Ether& e) override;
	void Initialize() override;
	void Uninitialize() override;
	//String GetTitle() const override;
	void Layout() override;
	//bool IsGeomDrawBegin() override;
	//void SetFrameRect(const Rect& r) override;
	bool Redraw(bool only_pending) override;
	void LeftDown(Point p, dword keyflags) override;
	void ChildGotFocus() override;
	void Paint(Draw& id) override;
	
	COMP_DEF_VISIT
	
	virtual void ChildMouseEvent(Ctrl *child, int event, Point p, int zdelta, dword keyflags);
};

using Geom2DComponentRef = Ref<Geom2DComponent>;


struct Geom2DComponentLink : public Component<Geom2DComponentLink> {
	RTTI_COMP1(Geom2DComponentLink, ComponentT)
	COPY_PANIC(Geom2DComponentLink)
	COMP_DEF_VISIT
	
	
	Geom2DComponent* linked = 0;
	
	
	void Etherize(Ether& e) override;
	void Initialize() override;
	void Uninitialize() override;
	
	void Link(Geom2DComponent* cw);
	void Unlink(Geom2DComponent* cw);
	void Unlink();
	Geom2DComponent& GetWindow() const;
	
};

using Geom2DComponentLinkRef = Ref<Geom2DComponentLink>;


struct Window2D :
	EntityPrefab<
		Geom2DComponent,
		Transform2D,
		DefaultGuiAppComponent
	> {
    static Components Make(Entity& e)
    {
        auto components = EntityPrefab::Make(e);
		
		components.Get<Geom2DComponentRef>()->transform2d = components.Get<Transform2DRef>();
		
		components.Get<Transform2DRef>()->position = vec2(0, 1);
		components.Get<Transform2DRef>()->size = vec2(320, 240);
		
        return components;
    }
};


// Window3D needs to be linked to Window2D
struct Window3D :
	EntityPrefab<
		Geom2DComponentLink,
		Transform,
		ModelComponent
	> {
    static Components Make(Entity& e)
    {
        auto components = EntityPrefab::Make(e);
		
		Geom2DComponentLinkRef win = components.Get<Geom2DComponentLinkRef>();
		
		#if 0
		ModelComponentRef mdl = components.Get<ModelComponentRef>();
		mdl->Arg("builtin", "box");
		#endif
		
		TransformRef trans = components.Get<TransformRef>();
		trans->data.position = vec3(0, 2, 0);
		
        return components;
    }
};


NAMESPACE_ECS_END

#endif
#endif
