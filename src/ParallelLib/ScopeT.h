#ifndef _ParallelLib_ScopeT_h_
#define _ParallelLib_ScopeT_h_

NAMESPACE_PARALLEL_BEGIN


template <class Dim>
class HandleSystemT;


template <class Dim>
class ScopeT :
	public RefScopeEnabler<ScopeT<Dim>, RefParent1<HandleSystemT<Dim>>>,
	public Dim::Space
{
	
public:
	using Base = ScopeT<Dim>;
	using Handle = HandleT<Dim>;
	using Space = typename Dim::Space;
	using Interface = typename Dim::Interface;
	using InterfaceProxy = typename Dim::InterfaceProxy;
	
private:
	Array<Handle> handles;
	
public:
	RTTI_DECL1(Base, Space)
	typedef ScopeT<Dim> CLASSNAME;
	ScopeT();
	
	
	bool Init() override;
	void AddInterface(InterfaceProxy&) override;
	bool Poll(typename Dim::Event& e) override;
	void Render() override;
	void Shutdown() override;
	bool ProcessCloseQueue() override;
	
};

using GuboManager = ScopeT<Ctx3D>;
using WindowManager = ScopeT<Ctx2D>;
using GuboManagerRef = Ref<GuboManager>;
using WindowManagerRef = Ref<WindowManager>;

NAMESPACE_PARALLEL_END

#endif
