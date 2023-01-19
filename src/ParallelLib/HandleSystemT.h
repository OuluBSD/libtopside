#ifndef _ParallelLib_HandleSystemT_h_
#define _ParallelLib_HandleSystemT_h_

NAMESPACE_PARALLEL_BEGIN


template <class Dim>
class HandleSystemT : public Parallel::System<HandleSystemT<Dim>> {
	
public:
	using Base = HandleSystemT<Dim>;
	using Scope = ScopeT<Dim>;
	using Handle = HandleT<Dim>;
	using HandleSystem = HandleSystemT<Dim>;
	using Space = typename Dim::Space;
	using Interface = typename Dim::Interface;
	using InterfaceProxy = typename Dim::InterfaceProxy;
	using Interaction = typename Dim::Interaction;
	using Container = typename Dim::Container;
	using ContainerFrame = typename Dim::ContainerFrame;
	using TopContainer = typename Dim::TopContainer;
	using Event = typename Dim::Event;
	
private:
	Array<Scope> scopes;
	int active_pos = -1;
	bool close_machine_when_empty = false;
	
	Array<TopContainer> owned_wins;
	Mutex lock;
	
protected:
    bool Initialize() override;
    void Start() override;
    void Update(double dt) override;
    void Stop() override;
    void Uninitialize() override;
    
public:
    typedef HandleSystemT<Dim> CLASSNAME;
	HandleSystemT(Machine& m);
	
	SYS_RTTI(HandleSystemT)
	SYS_DEF_VISIT
	
	
	Scope& AddScope();
	void Close();
	void CloseContainer(TopContainer* tc);
	void SetCloseMachineWhenEmpty(bool b=true) {close_machine_when_empty = b;}
	
	void RealizeScope();
	Scope& GetActiveScope();
	Scope& GetScope(int i);
	
	int GetScopeCount() const {return scopes.GetCount();}
	int GetScreenCount() const {return GetScopeCount();}
	
};

using GuboSystem = HandleSystemT<Ctx3D>;
using WindowSystem = HandleSystemT<Ctx2D>;
using GuboSystemRef = Ref<GuboSystem>;
using WindowSystemRef = Ref<WindowSystem>;

NAMESPACE_PARALLEL_END

#endif
