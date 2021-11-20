#ifndef _EcsMech_Engine_h_
#define _EcsMech_Engine_h_


NAMESPACE_ECS_BEGIN

class Engine;


class SystemBase :
	public RefScopeEnabler<SystemBase,Engine>
{
public:
	RTTI_DECL_R0(SystemBase)
	
    SystemBase();
    virtual ~SystemBase();

    virtual TypeCls GetType() const = 0;
	virtual void Visit(RuntimeVisitor& vis) = 0;
	
	Engine& GetEngine() const;
protected:
    friend Engine;

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
public:
	using SystemT = System<T>;
	RTTI_DECL1(SystemT, SystemBase)
    using SystemBase::SystemBase;
	
	System() {};
    TypeCls GetType() const override {return AsTypeCls<T>();}
    void Visit(RuntimeVisitor& vis) override {vis.VisitThisPure<SystemBase>(this);}
    
};

#define SYS_RTTI(x)  RTTI_DECL1(x, System<x>)
#define ECS_SYS_CTOR(x) \
	typedef x CLASSNAME; \
	x(Engine& m) : SP(m) {}
#define SYS_DEF_VISIT void Visit(RuntimeVisitor& vis) override {vis.VisitThis<System<CLASSNAME>>(this);}
#define SYS_DEF_VISIT_(x) void Visit(RuntimeVisitor& vis) override {x; vis.VisitThis<System<CLASSNAME>>(this);}

class Engine :
	public RefScopeEnabler<Engine,RefRoot>
{
	int64 ticks = 0;
	
public:
	RTTI_DECL_R0(Engine)
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

    template<typename SystemT, typename... Args>
    Ref<SystemT> GetAdd(Args&&... args) {
        SystemCollection::Iterator it = FindSystem(AsTypeCls<SystemT>());
        if (it)
            return it->AsRef<SystemT>();
        return Add<SystemT>(args...);
    }
    
    template<typename SystemT>
    void Remove()
    {
        CXX2A_STATIC_ASSERT(IsSystem<SystemT>::value, "T should derive from System");

        ASSERT(is_initialized && is_started);
        Remove(AsTypeCls<SystemT>());
    }

    Engine();
    virtual ~Engine();

    bool HasStarted() const;

    bool Start();
    void Update(double dt);
    void Stop();
    void Suspend();
    void Resume();
    void DieFast() {Start(); Update(0); Stop();}
	void Clear() {ticks=0; is_started=0; is_initialized=0; is_suspended=0; is_running=0; systems.Clear();}
	
    bool IsRunning() const {return is_running;}
	void SetNotRunning() {is_running = false;}
	void Visit(RuntimeVisitor& vis);
	
	
	Callback WhenEnterUpdate;
	Callback1<SystemBase&> WhenEnterSystemUpdate;
	
	Callback WhenLeaveUpdate;
	Callback WhenLeaveSystemUpdate;
	
	static Callback WhenGuiProgram;
	static Callback WhenInitialize;
	static Callback WhenPreFirstUpdate;
	
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


Engine& GetActiveEngine();
void SetActiveEngine(Engine& e);
void ClearActiveEngine();


class SingleEngine {
	Engine eng;
	
	bool Open(bool gui);
	void Close();
	
public:
	SingleEngine() {SetActiveEngine(eng);}
	~SingleEngine() {ClearActiveEngine();}
	
	void Run(bool gui, void(*fn)());
	
};


NAMESPACE_ECS_END


NAMESPACE_SERIAL_BEGIN


void MachineEcsInit();


NAMESPACE_SERIAL_END


#endif
