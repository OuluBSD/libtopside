#ifndef _EcsMech_Machine_h_
#define _EcsMech_Machine_h_


NAMESPACE_TOPSIDE_BEGIN

class Machine;


class SystemBase : public RefScopeEnabler<SystemBase,Machine> {
public:
	RTTI_DECL_R0(SystemBase)
	using RScope = RefScopeEnabler<SystemBase,Machine>;
	
    SystemBase();
    virtual ~SystemBase();

    virtual TypeCls GetType() const = 0;
	virtual void Visit(RuntimeVisitor& vis) = 0;
	
	Machine& GetMachine() const {return RScope::GetParent();}
protected:
    friend Machine;

    virtual bool Initialize() {return true;}
    virtual void Start() {}
    virtual void Update(double /*dt*/) {}
    virtual void Stop() {}
    virtual void Uninitialize() {}

	
};


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
    
};

#define SYS_RTTI(x)  RTTI_DECL1(x, System<x>)
#define SYS_CTOR(x) x(Machine& m) : RefScopeParent<RefParent1<Machine>>(m) {}
#define SYS_CTOR_(x) x(Machine& m) : RefScopeParent<RefParent1<Machine>>(m)

class Machine :
	public RefScopeEnabler<Machine,RefRoot>
{
	int64 ticks = 0;
	
public:
	RTTI_DECL_R0(Machine)
	int64 GetTicks() const {return ticks;}
	
	
    template<typename SystemT>
    Ref<SystemT> Get() {
        auto system = TryGet<SystemT>();
        ASSERT(system);
        return system;
    }

    template<typename SystemT>
    Ref<SystemT> TryGet()
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
        return syst->template AsRef<SystemT>();
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
	
    bool IsRunning() const {return is_running;}
	void SetNotRunning() {is_running = false;}
	void Visit(RuntimeVisitor& vis);
	
	
	static Callback WhenInitialize;
	static Callback WhenPreUpdate;
	
private:
    using SystemCollection = RefTypeMapIndirect<SystemBase> ;
    SystemCollection systems;

    bool is_started = false;
    bool is_initialized = false;
    bool is_suspended = false;
    bool is_running = false;
    
    SystemCollection::Iterator FindSystem(TypeCls type_id) {return systems.Find(type_id);}
    void Add(TypeCls type_id, SystemBase* system);
    void Remove(TypeCls typeId);
};


Machine& GetActiveMachine();
void SetActiveMachine(Machine& m);
void ClearActiveMachine();


class SingleMachine {
	Machine mach;
	
	bool Open(bool gui);
	void Close();
	
public:
	SingleMachine() {SetActiveMachine(mach);}
	~SingleMachine() {ClearActiveMachine();}
	
	void Run(bool gui, void(*fn)());
	
};



NAMESPACE_TOPSIDE_END


#endif
