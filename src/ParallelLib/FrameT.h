#ifndef _ParallelLib_FrameT_h_
#define _ParallelLib_FrameT_h_

NAMESPACE_PARALLEL_BEGIN


template <class Dim> class HandleSystemT;
template <class Dim> class ScopeT;
template <class Dim> class HandleT;


template <class Dim>
class FrameT :
	public Dim::Container,
	RTTIBase
{
public:
	using Base = FrameT<Dim>;
	using Scope = ScopeT<Dim>;
	using GeomDecoration = FrameT<Dim>;
	using Handle = HandleT<Dim>;
	using HandleSystem = HandleSystemT<Dim>;
	using DrawT = typename Dim::DrawT;
	using Interaction = typename Dim::Interaction;
	using Container = typename Dim::Container;
	using ContainerFrame = typename Dim::ContainerFrame;
	using ContainerGeom = typename Dim::ContainerGeom;
	using TopContainer = typename Dim::TopContainer;
	using Sz = typename Dim::Sz;
	using Pt = typename Dim::Pt;
	using Box = typename Dim::Box;
	using CmdDraw = typename Dim::CmdDraw;
	using CmdPainter = typename Dim::CmdPainter;
	
protected:
	friend class HandleT<Dim>;
	friend class ::UPP::TopWindow;
	
	String  title;
	Button  minimize, maximize, close;
	Image   icon;
	Sz      minsize;
	bool    sizeable;
	Handle* handle = NULL;
	bool    maximized;
	Box     overlapped;
	bool    holding;
	TimeCallback hold;
	Pt      dir;
	Pt      startpos;
	Box     startrect;
	
	ContainerGeom geom;
	
	// deprecated
	#if 0
	bool left_down = false;
	Pt left_down_pt;
	#endif
	
public:
	#if IS_UPP_CORE
	RTTI_DECL0(GeomDecoration)
	#else
	RTTI_DECL1(GeomDecoration, Container)
	#endif
	
	typedef FrameT CLASSNAME;
	FrameT();
	
	void SetHandle(Handle* h);
	void SetTitle(String str) {title = str;}
	void SetClient(Box r);
	
	String GetTitle() const {return title;}
	Box GetClient() const;
	
	void GripResize();
	void Maximize();
	void Overlap();
	void ToggleMaximize();
	void SyncBox();
	void StartDrag();
	void Hold();
	
	bool IsMaximized() const                 { return maximized; }
	void Paint(DrawT& draw) override;
	void LeftDown(Pt p, dword keyflags) override;
	void LeftDouble(Pt p, dword keyflags) override;
	void LeftUp(Pt p, dword keyflags) override;
	void MouseMove(Pt p, dword keyflags) override;
	void RightDown(Pt p, dword keyflags) override;
	void MouseEnter(Pt frame_p, dword keyflags) override;
	void MouseLeave() override;
	void Layout() override;
	Image CursorImage(Pt p, dword) override;
	void CancelMode() override;
	
	void LocalMenu(Bar& bar);
	
	Scope& GetWorkArea();
	Box Margins() const;
	Box ComputeClient(Box r);
	Pt GetDragMode(Pt p);
	Image GetDragImage(Pt dir);
	
	Sz GetFrameSize() const;
	Box GetFrameBox() const;
	void SetFrameBox(Box b);
	TopContainer* GetTopContainer();
	Interaction& GetInteraction();
	Handle& GetHandle() const {return *handle;}
	
};


NAMESPACE_PARALLEL_END

#endif
