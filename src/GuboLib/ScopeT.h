#ifndef _GuboCore_ScopeT_h_
#define _GuboCore_ScopeT_h_

NAMESPACE_GUBO_BEGIN

template <class Dim>
class ScopeT :
	public RefScopeEnabler<ScopeT<Dim>, HandleSystemT<Dim>>,
	public Dim::Container
{

public:
	using Base = ScopeT<Dim>;
	using Scope = ScopeT<Dim>;
	using Handle = HandleT<Dim>;
	using HandleSystem = HandleSystemT<Dim>;
	using Interaction = typename Dim::Interaction;
	using Container = typename Dim::Container;
	using ContainerFrame = typename Dim::ContainerFrame;
	using TopContainer = typename Dim::TopContainer;
	using Sz = typename Dim::Sz;
	using Pt = typename Dim::Pt;
	using Box = typename Dim::Box;
	using CmdDraw = typename Dim::CmdDraw;
	using CmdPainter = typename Dim::CmdPainter;
	using DrawT = typename Dim::DrawT;
	
	#if IS_UPP_CORE
	using UppTopSurface = SurfaceInterfaceGeom<UPP::TopSurface>;
	#endif
	
private:
	CmdDraw pd;
	Vector<int> close_handle_queue;
	ArrayMap<int, Handle> handles;
	
	#if IS_UPP_CORE
	Array<UppTopSurface> tws;
	#endif
	
	int handle_counter = 0;
	bool maximize_all;
	int active_pos, active_id;
	Interaction* captured = NULL;
	Interaction* with_mouse = NULL;
	Container* captured_ctrl = NULL;
	Container* with_mouse_ctrl = NULL;
	ContainerFrame* frame_with_mouse = NULL;
	ContainerFrame* frame_captured = NULL;
	bool do_render = false;
	int frame_width = 3;
	int corner_width = 10;
	Pt global_mouse;
	
public:
	void QueueCloseHandle(int handle_id) { close_handle_queue.Add(handle_id); }
	void MoveHandle(Pt pt, int handle_id);
	void FocusHandle(int handle_id);
	void FocusHandlePos(int win_pos);
	void MaximizeHandle(int handle_id);
	void MinimizeHandle(int handle_id);
	void RestoreHandle(int handle_id);
	void IsActiveHandle_(bool* result, int handle_id) { *result = handle_id == active_id; }
	bool IsActiveHandle(int handle_id) { return handle_id == active_id; }
	void SetHandleMaximized(Handle& h, bool b);
	void CloseHandle(int handle_id);

	void FocusPrevious();
	void SetTitle(int handle_id, String title);
	String GetTitle(int handle_id);
	void CloseOthers(int handle_id);

	void LoadDimsAll();
	void SetMaximizeAll(bool b = true) { maximize_all = b; }

	void SetCaptured(GeomInteraction* c) override;
	void SetWithMouse(GeomInteraction* c) override;
	
	void SetCaptured(Container* c);
	void SetWithMouse(Container* c);
	ContainerFrame* GetFrameCaptured() { return frame_captured; }
	ContainerFrame* GetFrameWithMouse() { return frame_with_mouse; }
	void SetFrameCaptured(ContainerFrame* c) { frame_captured = c; }
	void SetFrameWithMouse(ContainerFrame* c) { frame_with_mouse = c; }

public:
	RTTI_DECL_R1(Scope, Container)
	typedef ScopeT<Dim> CLASSNAME;
	ScopeT();

	bool Init();
	//void AddInterface(InterfaceProxy&);
	bool Poll(typename Dim::Event& e);
	void Render();
	void Shutdown();
	bool ProcessCloseQueue();
	bool IsGeomDrawBegin() const override;
	void Paint(DrawT& draw) override;
	bool MouseMoveInFrame(Pt pt, dword keyflags) override;
	bool DeepMouseMove(const Pt& pt, dword keyflags) override;
	
	#if IS_UPP_CORE
	void AddInterface(UPP::TopSurface&);
	#endif
	
	bool CheckRender();
	bool IsRender() const {return do_render;}
	
	hash_t GetHashValue() const { return (hash_t)(size_t)this; }
	HandleSystem* GetManager() const { return this->GetParentUnsafe().Get(); }
	Handle* GetHandle(TopContainer& ctrl);
	Handle* GetActiveHandle();
	int GetActiveHandlePos() { return active_pos; }
	int GetActiveHandleId() { return active_id; }
	int GetPosId(int handle_pos)
	{
		if(handle_pos >= 0 && handle_pos < handles.GetCount())
			return handles.GetKey(handle_pos);
		return -1;
	}
	int GetFrameWidth() const {return frame_width;}
	int GetCornerWidth() const {return corner_width;}
	Pt GetGlobalMouse() const {return global_mouse;}

	void FocusHandle(TopContainer* tc);
	void OrderTileHandles();
	void OrderTileHandlesVert();
	void CloseAll();
	void FocusEvent() {TODO}

	bool IsCaptureRoot() const override;
	Interaction* GetCaptured() const override { return captured; }
	Interaction* GetWithMouse() const override { return with_mouse; }
	bool Key(dword key, int count) override;
	// void LeftDown(Point p, dword keyflags) override;
	void Layout() override;
	void PostLayout() override;

	int GetCount() const { return handles.GetCount(); }
	Handle& operator[](int i) { return handles[i]; }
	Handle& Get(int i) { return handles[i]; }

	Interaction* GetLastSub();
	TopContainer* GetVisibleTopContainer();
	TopContainer& GetVisibleTopContainerRef() { return *GetVisibleTopContainer(); }
	
	CmdDraw& GetDraw() {return pd;}
	
	Callback WhenActiveHandleChanges, WhenHandleClose;
};

using GuboManager = ScopeT<Ctx3D>;
using SurfaceManager = ScopeT<Ctx2D>;
using GuboManagerRef = Ref<GuboManager>;
using SurfaceManagerRef = Ref<SurfaceManager>;


NAMESPACE_GUBO_END

#endif
