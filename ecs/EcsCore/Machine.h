#ifndef _EcsCore_Machine_h_
#define _EcsCore_Machine_h_


NAMESPACE_OULU_BEGIN

class Machine;


class SystemBase {
public:
    SystemBase(Machine& machine);
    virtual ~SystemBase() = default;

    virtual TypeId GetType() const = 0;

	Machine& GetMachine() const {return machine;}
protected:
    friend Machine;

    virtual bool Initialize() {return true;}
    virtual void Start() {}
    virtual void Update(float /*dt*/) {}
    virtual void Stop() {}
    virtual void Uninitialize() {}

    Machine& machine;
};


template<typename T>
class System : public SystemBase, public LockedScopeEnabler<T> {
public:
    using SystemBase::SystemBase;
	
	System(Machine& e) : SystemBase(e) {};
    TypeId GetType() const override {
        return typeid(T);
    }
};


class Machine {
	int64 ticks = 0;
	
public:
	int64 GetTicks() const {return ticks;}
	
	
    template<typename SystemT>
    Ref<SystemT> Get()
    {
        auto system = TryGet<SystemT>();
        ASSERT(system);
        return system;
    }

    template<typename SystemT>
    Ref<SystemT> TryGet();/*
    {
        CXX2A_STATIC_ASSERT(IsSystem<SystemT>::value, "T should derive from System");
        
        auto it = FindSystem(typeid(SystemT));
        return it == systems.end()
            ? Ref<SystemT>()
            : it->As<SystemT>();
    }*/

    template<typename SystemT, typename... Args>
    Ref<SystemT> Add(Args&&... args);/*
    {
        CXX2A_STATIC_ASSERT(IsSystem<SystemT>::value, "T should derive from System");
		
		SystemT* syst = new SystemT(*this, args...);
		Ref<SystemBase> s;
		s.WrapObject(syst);
		syst->InitWeak(s.As<SystemT>());
		Add(typeid(SystemT), s);
        //Add(typeid(SystemT), MakeRef<SystemT>(*this, std::forward<Args>(args)...));
        return s.As<SystemT>();
    }*/

    template<typename SystemT>
    void Remove()
    {
        CXX2A_STATIC_ASSERT(IsSystem<SystemT>::value, "T should derive from System");

        ASSERT(is_initialized && is_started);

        Remove(typeid(SystemT));
    }

    Machine();
    virtual ~Machine();

    bool HasStarted() const;

    bool Start();
    void Update(float dt);
    void Stop();
    void Suspend();
    void Resume();
    void DieFast() {Start(); Update(0); Stop();}
    
    bool IsRunning() const {return is_running;}
	void SetNotRunning() {is_running = false;}
	
	
	static Callback WhenStarting;
	
private:
    typedef RefLinkedList<SystemBase> SystemCollection;
    SystemCollection systems;

    bool is_started = false;
    bool is_initialized = false;
    bool is_suspended = false;
    bool is_running = false;
    
    SystemCollection::Iterator FindSystem(TypeId const& typeId);
    //void Add(TypeId const& typeId, Ref<SystemBase> system);
    void Remove(TypeId const& typeId);
};

inline Machine& GetMachine() {return Single<Machine>();}

NAMESPACE_OULU_END


#endif
