#ifndef _ParallelMach_Machine_h_
#define _ParallelMach_Machine_h_

NAMESPACE_PARALLEL_BEGIN
using namespace Serial;



class SystemBase : public MetaSystemBase {
public:
	RTTI_DECL1(SystemBase, MetaSystemBase)
	
    SystemBase();
    virtual ~SystemBase();

    virtual TypeCls GetType() const = 0;
	virtual void Visit(RuntimeVisitor& vis) = 0;
	
	Machine& GetMachine() const {return *GetParent().AsStatic<Machine>();}
protected:
    friend Machine;

    virtual bool Initialize() {return true;}
    virtual void Start() {}
    virtual void Update(double /*dt*/) {}
    virtual void Stop() {}
    virtual void Uninitialize() {}

	
};

template<typename T>
using IsSystem = std::is_base_of<SystemBase, T>;


template<typename T>
class System :
	public SystemBase
{
	using SystemT = System<T>;
public:
	RTTI_DECL1(SystemT, SystemBase)
    using SystemBase::SystemBase;
	
	System() {};
    TypeCls GetType() const override {return AsTypeCls<T>();}
    void Visit(RuntimeVisitor& vis) override {vis.VisitThisPure<SystemBase>(this);}
    
};


#define SYS_RTTI(x)  RTTI_DECL1(x, System<x>)
#define SYS_CTOR(x) \
	typedef x CLASSNAME; \
	x(Machine& m) : SP(m) {}
#define SYS_CTOR_(x) \
	typedef x CLASSNAME; \
	x(Machine& m) : SP(m)
#define SYS_DEF_VISIT void Visit(RuntimeVisitor& vis) override {vis.VisitThis<System<CLASSNAME>>(this);}
#define SYS_DEF_VISIT_(x) void Visit(RuntimeVisitor& vis) override {x; vis.VisitThis<System<CLASSNAME>>(this);}
#define SYS_DEF_VISIT_H void Visit(RuntimeVisitor& vis) override;
#define SYS_DEF_VISIT_I(cls, x) void cls::Visit(RuntimeVisitor& vis) {x; vis.VisitThis<System<CLASSNAME>>(this);}

class Machine :
	public MetaMachineBase
{
	int64 ticks = 0;
	Index<String> last_warnings;
	double warning_age;
	
public:
	RTTI_DECL1(Machine, MetaMachineBase)
	int64 GetTicks() const {return ticks;}
	
	
    template<typename SystemT>
    Ref<SystemT> Get() {
        auto system = Find<SystemT>();
        ASSERT(system);
        return system;
    }

    template<typename SystemT>
    SystemT* GetPtr() {
        SystemCollection::PtrIterator it = FindSystemPtr(AsTypeCls<SystemT>());
        return CastPtr<SystemT>(&*it);
    }

    template<typename SystemT>
    Ref<SystemT> Find()
    {
        CXX2A_STATIC_ASSERT(IsSystem<SystemT>::value, "T should derive from System");
        
        SystemCollection::Iterator it = FindSystem(AsTypeCls<SystemT>());
        return it ? it->AsRef<SystemT>() : Ref<SystemT>();
    }

    template<typename SystemT, typename... Args>
    Ref<SystemT> Add(Args&&... args)
    {
        CXX2A_STATIC_ASSERT(IsSystem<SystemT>::value, "T should derive from System");
		
		SystemT* syst = new SystemT(*this, args...);
        Add(AsTypeCls<SystemT>(), syst);
        return syst->AsRefT();
    }
    

    template<typename SystemT, typename... Args>
    Ref<SystemT> FindAdd(Args&&... args)
    {
		Ref<SystemT> ret = Find<SystemT>();
		if (ret)
			return ret;
		
		return Add<SystemT>(args...);
    }
    
    template<typename SystemT>
    void Remove()
    {
        CXX2A_STATIC_ASSERT(IsSystem<SystemT>::value, "T should derive from System");

        ASSERT(is_initialized && is_started);
        Remove(AsTypeCls<SystemT>());
    }

    Machine();
    virtual ~Machine();

    bool HasStarted() const;

    bool Start();
    void Update(double dt);
    void Stop();
    void Suspend();
    void Resume();
    void DieFast() {Start(); Update(0); Stop();}
	void Clear() {ticks=0; is_started=0; is_initialized=0; is_suspended=0; is_running=0; systems.Clear();}
	
    bool IsStarted() const {return is_started;}
    bool IsRunning() const {return is_running;}
	void SetNotRunning() {is_running = false;}
	void Visit(RuntimeVisitor& vis);
	void WarnDeveloper(String msg);
	
	MachineVerifier*	GetMachineVerifier() const {return mver;}
	
	Callback WhenEnterUpdate;
	Callback1<SystemBase&> WhenEnterSystemUpdate;
	
	Callback WhenLeaveUpdate;
	Callback WhenLeaveSystemUpdate;
	
	static Callback WhenInitialize;
	static Callback WhenUserProgram;
	static Callback WhenPostInitialize;
	static Callback WhenPreFirstUpdate;
	
private:
    using SystemCollection = RefTypeMapIndirect<SystemBase> ;
    SystemCollection systems;

    bool is_started = false;
    bool is_initialized = false;
    bool is_suspended = false;
    bool is_running = false;
    
    SystemCollection::Iterator FindSystem(TypeCls type_id) {return systems.Find(type_id);}
    SystemCollection::PtrIterator FindSystemPtr(TypeCls type_id) {return systems.FindPtr(type_id);}
    void Add(TypeCls type_id, SystemBase* system);
    void Remove(TypeCls typeId);
    
    
protected:
	friend class Serial::MachineVerifier;
	
    MachineVerifier* mver = 0;
    
    
};


Machine& GetActiveMachine();
void SetActiveMachine(Machine& m);
void ClearActiveMachine();


NAMESPACE_PARALLEL_END



NAMESPACE_TOPSIDE_BEGIN


class SingleMachine {
	
protected:
	Parallel::Machine mach;
	
	bool Open(void(*arg_fn)());
	void Close();
	
public:
	SingleMachine()		{Parallel::SetActiveMachine(mach);}
	~SingleMachine()	{Parallel::ClearActiveMachine();}
	
	void Run(void(*fn)(), void(*arg_fn)());
	
	bool Start() {return Open(0);}
	void Stop() {Close();}
};


NAMESPACE_TOPSIDE_END

#endif
