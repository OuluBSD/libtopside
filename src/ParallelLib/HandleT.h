#ifndef _ParallelLib_HandleT_h_
#define _ParallelLib_HandleT_h_

NAMESPACE_PARALLEL_BEGIN


template <class Dim> class HandleSystemT;
template <class Dim> class ScopeT;

template <class Dim>
class HandleT :
	public Dim::Interface,
	public Dim::Interaction
{
	
public:
	using Base = HandleT<Dim>;
	using Handle = HandleT<Dim>;
	using Scope = ScopeT<Dim>;
	using HandleSystem = HandleSystemT<Dim>;
	using Space = typename Dim::Space;
	using Interface = typename Dim::Interface;
	using InterfaceProxy = typename Dim::InterfaceProxy;
	using Interaction = typename Dim::Interaction;
	using Container = typename Dim::Container;
	using ContainerFrame = typename Dim::ContainerFrame;
	using TopContainer = typename Dim::TopContainer;
	
public:
	
	
protected:
	bool maximized;
	
	void SetContent(Scope* s, int id);
	
public:
	RTTI_DECL2(Base, Interface, Interaction)
	typedef HandleT<Dim> CLASSNAME;
	HandleT();
	
	void SetInterface(typename Dim::InterfaceProxy& iface);
	
	void						Title(const String& title) override;
	Interface&					Sizeable(bool b=true) override;
	Interface&					MaximizeBox(bool b=true) override;
	Interface&					MinimizeBox(bool b=true) override;
	int							Run(bool appmodal=false) override;
	String						GetTitle() const override;
	void						SetPendingPartialRedraw() override;
	
	TopContainer*				GetTopContainer();
	
	void SetMaximized(bool b=true);
	void Clear();
	Point GetGlobalMouse();
	void StoreRect();
	void LoadRect();
	void SetStoredRect(Rect r);
	int GetId() const;
	Rect GetStoredRect() const;
	Interface* GetAbsolute();
	bool IsMaximized() const;
	bool IsActive() const;
	void MoveWindow(Point pt);
	void Maximize();
	void Restore();
	void Minimize();
	void FocusEvent() override;
	void ToggleMaximized();
	bool IsPendingPartialRedraw() const;
	void Wait();
	Scope* GetScope() const;
	
};


NAMESPACE_PARALLEL_END

#endif
