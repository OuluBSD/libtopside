#ifndef _GuboCore_HandleT_h_
#define _GuboCore_HandleT_h_

NAMESPACE_GUBO_BEGIN


struct WindowsImg {
	static Image& close();
	static Image& maximize();
	static Image& minimize();
	static Image& nwse();
	static Image& nesw();
	static Image& ns();
	static Image& ew();
};

template <class Dim> class HandleSystemT;
template <class Dim> class ScopeT;
template <class Dim> class HandleT;


template <class Dim>
class GeomDecorationT : public Dim::Interaction {
public:
	using Base = GeomDecorationT<Dim>;
	using GeomDecoration = GeomDecorationT<Dim>;
	using Handle = HandleT<Dim>;
	using HandleSystem = HandleSystemT<Dim>;
	using DrawT = typename Dim::DrawT;
	using Interaction = typename Dim::Interaction;
	using Container = typename Dim::Container;
	using ContainerFrame = typename Dim::ContainerFrame;
	using TopContainer = typename Dim::TopContainer;
	using Sz = typename Dim::Sz;
	using Pt = typename Dim::Pt;
	using Box = typename Dim::Box;
	using CmdDraw = typename Dim::CmdDraw;
	using CmdPainter = typename Dim::CmdPainter;
	
protected:
	Handle* handle = NULL;
	Button3 minimize, maximize, close;
	String label;
	bool left_down;
	Pt left_down_pt;
	
public:
	RTTI_DECL1(GeomDecoration, Interaction)
	typedef GeomDecorationT CLASSNAME;
	GeomDecorationT(Handle* h);
	
	void Paint(DrawT& draw) override;
	
	void SetLabel(String str) {label = str;}
	
	String GetLabel() const {return label;}
	
	void LeftDown(Pt p, dword keyflags) override;
	void LeftDouble(Pt p, dword keyflags) override;
	void LeftUp(Pt p, dword keyflags) override;
	void MouseMove(Pt p, dword keyflags) override;
	void RightDown(Pt p, dword keyflags) override;
	void MouseEnter(Pt frame_p, dword keyflags) override;
	void MouseLeave() override;
	
	void LocalMenu(Bar& bar);
	
	
};


template <class Dim>
class HandleT :
	public RefScopeEnabler<HandleT<Dim>, ScopeT<Dim>>,
	public Dim::Interaction
{
	
public:
	using Base = HandleT<Dim>;
	using Handle = HandleT<Dim>;
	using Scope = ScopeT<Dim>;
	using HandleSystem = HandleSystemT<Dim>;
	using GeomDecoration = GeomDecorationT<Dim>;
	using DrawT = typename Dim::DrawT;
	using Interaction = typename Dim::Interaction;
	using Container = typename Dim::Container;
	using ContainerFrame = typename Dim::ContainerFrame;
	using TopContainer = typename Dim::TopContainer;
	using Box = typename Dim::Box;
	using Sz = typename Dim::Sz;
	using Pt = typename Dim::Pt;
	
public:
	enum {CENTER, TL, TR, BL, BR, TOP, BOTTOM, LEFT, RIGHT};
	
protected:
	GeomDecoration decor;
	Box stored_box;
	bool maximized;
	bool pending_partial_redraw;
	bool cursor_overriden = false;
	bool is_resizing = false;
	bool used_momentum = false;
	int override_area = -1;
	int id;
	int resize_area = 0;
	Pt resize_start_pt;
	Pt resize_diff;
	Box resize_start_r;
	
public:
	RTTI_DECL1(Handle, Interaction)
	typedef HandleT<Dim> CLASSNAME;
	HandleT();
	
	void SetId(int id) {this->id = id;}
	//void SetInterface(typename Dim::InterfaceProxy& iface);
	
	void						Title(const String& title);
	HandleT&					Sizeable(bool b=true);
	HandleT&					MaximizeBox(bool b=true);
	HandleT&					MinimizeBox(bool b=true);
	int							Run(bool appmodal=false);
	String						GetTitle() const;
	void						SetPendingPartialRedraw();
	//GeomInteraction*			GetDynamicallyLinked() const override;
	Image						OverrideCursor(const Image& m);
	Image						DefaultCursor();
	
	void						Layout() override;
	void						Paint(DrawT& draw) override;
	void						SetFrameBox(const Box& r) override;
	bool						DeepMouseMove(const Pt& pt, dword keyflags) override;
	GeomInteraction*			GetProxy() const override;
	void						MouseMove(Pt p, dword keyflags) override;
	void						MouseLeave() override;
	void						DeepMouseLeave() override;
	void						LeftDown(Pt p, dword keyflags) override;
	void						LeftUp(Pt p, dword keyflags) override;
	
	
	void						CheckMouseBorder(const Pt& pt);
	TopContainer*				GetTopContainer();
	int							GetArea(const Pt& pt);
	
	void SetMaximized(bool b=true);
	//void Clear();
	void StoreRect();
	void LoadRect();
	//void SetStoredRect(Rect r);
	//int GetId() const;
	//Rect GetStoredRect() const;
	//Interface* GetAbsolute();
	bool IsMaximized() const;
	bool IsActive() const;
	void MoveHandle(Pt pt);
	void Close();
	void Maximize();
	void Restore();
	void Minimize();
	void CloseOthers();
	void CaptureResize(const Pt& p);
	void ReleaseResize();
	void FocusEvent() {TODO;}
	void ToggleMaximized();
	void ContinueGlobalMouseMomentum();
	void DoResize();
	bool IsPendingPartialRedraw() const;
	//void Wait();
	int GetFrameWidth() const;
	int GetCornerWidth() const;
	Scope& GetScope() const;
	HandleSystem& GetHandleSystem() const;
	
	Pt GetGlobalMouse() const;
	
};

using GuboHandle = HandleT<Ctx3D>;
using SurfaceHandle = HandleT<Ctx2D>;

NAMESPACE_GUBO_END

#endif
