#ifndef _ParallelLib_HandleSystemT_h_
#define _ParallelLib_HandleSystemT_h_

NAMESPACE_PARALLEL_BEGIN


template <class Dim>
class HandleSystemT : public Parallel::System<HandleSystemT<Dim>> {
	
public:
	using Scope = ScopeT<Dim>;
	using Handle = HandleT<Dim>;
	
private:
	Array<Scope> scopes;
	int active_scope = -1;
	
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
	
	
	void RealizeScope();
	Scope& GetActiveScope();
	
	int GetScopeCount() const {return scopes.GetCount();}
	int GetScreenCount() const {return GetScopeCount();}
	
};

using GuboSystem = HandleSystemT<Ctx3D>;
using WindowSystem = HandleSystemT<Ctx2D>;
using GuboSystemRef = Ref<GuboSystem>;
using WindowSystemRef = Ref<WindowSystem>;

NAMESPACE_PARALLEL_END

#endif
