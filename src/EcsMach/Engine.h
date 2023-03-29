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
    SystemBase(Engine& e);
    virtual ~SystemBase();

    virtual TypeCls GetType() const = 0;
	virtual void Visit(RuntimeVisitor& vis) = 0;
    virtual bool Arg(String key, Object value) {return true;}
	
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
	System(Engine& e) : SystemBase(e) {};
    TypeCls GetType() const override {return AsTypeCls<T>();}
    void Visit(RuntimeVisitor& vis) override {vis.VisitThisPure<SystemBase>(this);}
    
};

#define SYS_RTTI(x)  RTTI_DECL1(x, System<x>)
#define ECS_SYS_CTOR(x) \
	typedef x CLASSNAME; \
	x(Engine& m) : SP(m) {}
#define ECS_SYS_CTOR_DERIVED(x, derived_from) \
	typedef x CLASSNAME; \
	x(Engine& m) : derived_from(m) {}
#define SYS_DEF_VISIT void Visit(RuntimeVisitor& vis) override {vis.VisitThis<Ecs::System<CLASSNAME>>(this);}
#define SYS_DEF_VISIT_DERIVED(x) void Visit(RuntimeVisitor& vis) override {vis.VisitThis<x>(this);}
#define SYS_DEF_VISIT_(x) void Visit(RuntimeVisitor& vis) override {x; vis.VisitThis<Ecs::System<CLASSNAME>>(this);}

struct ComponentBaseUpdater {
	
	virtual void Update(double dt) {Panic("unimplemented");}
	
};


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
        if (it)
            return it->AsRef<SystemT>();
        
        return Ref<SystemT>();
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
	
	void AddToUpdateList(ComponentBaseUpdater* c);
	void RemoveFromUpdateList(ComponentBaseUpdater* c);
	
	Ref<SystemBase> Add(TypeCls type, bool startup=true);
	Ref<SystemBase> GetAdd(String id, bool startup=true);
    
	Callback WhenEnterUpdate;
	Callback1<SystemBase&> WhenEnterSystemUpdate;
	
	Callback WhenLeaveUpdate;
	Callback WhenLeaveSystemUpdate;
	
	static Callback WhenGuiProgram;
	static Callback WhenInitialize;
	static Callback WhenPreFirstUpdate;
	
	Serial::EntitySystem& GetEntitySystem() {ASSERT(sys); return *sys;}
	Serial::Machine& GetMachine() {return sys->GetMachine();}
	
protected:
	friend class Serial::EntitySystem;
	
	Serial::EntitySystem* sys = 0;
	
private:
    using SystemCollection = RefTypeMapIndirect<SystemBase> ;
    SystemCollection systems;
	
	bool is_started = false;
    bool is_initialized = false;
    bool is_suspended = false;
    bool is_running = false;
    bool is_looping_systems = false;
    
    SystemCollection::Iterator FindSystem(TypeCls type_id) {return systems.Find(type_id);}
    void Add(TypeCls type_id, SystemBase* system, bool startup=true);
    void Remove(TypeCls typeId);
    
    Vector<ComponentBaseUpdater*> update_list;
    
    
private:
	typedef SystemBase* (*NewSystemFn)(Ecs::Engine&);
    static VectorMap<String, TypeCls>& EonToType() {static VectorMap<String, TypeCls> m; return m;}
    static VectorMap<TypeCls, NewSystemFn>& TypeNewFn() {static VectorMap<TypeCls, NewSystemFn> m; return m;}
	
	template <class T>
	static SystemBase* NewSystem(Ecs::Engine& e) {return new T(e);}
	
public:
	
	template <class T>
	static void Register(String id) {
		//String id = T::GetEonId();
		ASSERT(id.GetCount() > 0);
		TypeCls type = T::TypeIdClass();
		ASSERT(EonToType().Find(id) < 0);
		EonToType().Add(id, type);
		ASSERT(TypeNewFn().Find(type) < 0);
		TypeNewFn().Add(type, &NewSystem<T>);
	}
	
    void SystemStartup(TypeCls type_id, SystemBase* system);
    
};


Engine& GetActiveEngine();
void SetActiveEngine(Engine& e);
void ClearActiveEngine();



NAMESPACE_ECS_END


NAMESPACE_SERIAL_BEGIN


void MachineEcsInit();


NAMESPACE_SERIAL_END


#endif
