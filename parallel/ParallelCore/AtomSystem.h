#ifndef _SerialCore_AtomSystem_h_
#define _SerialCore_AtomSystem_h_

NAMESPACE_PARALLEL_BEGIN


class AtomSystem :
	public System<AtomSystem>
{
	LinkedList<AtomBaseRef> updated;
	Mutex lock;
	
public:
	SYS_RTTI(AtomSystem)
	SYS_CTOR(AtomSystem);
	SYS_DEF_VISIT
	
	void AddOnce(PacketForwarder& fwd, RealtimeSourceConfig& cfg);
	
	
	static inline Callback& WhenUninit() {static Callback cb; return cb;}
	static ParallelTypeCls::Type GetSerialType() {return ParallelTypeCls::ATOM_SYSTEM;}
	
protected:
	
    bool Initialize() override;
    void Start() override;
    void Update(double dt) override;
    void Stop() override;
    void Uninitialize() override;
    
    void ForwardLinks(double dt, const char* id, LinkedList<AtomBaseRef>& atoms);
    
    
public:
	
    void AddUpdated(AtomBaseRef p);
    void RemoveUpdated(AtomBaseRef p);
	
	
};


NAMESPACE_PARALLEL_END

#endif
