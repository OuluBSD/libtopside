#ifndef _SerialCore_AtomSystem_h_
#define _SerialCore_AtomSystem_h_

NAMESPACE_PARALLEL_BEGIN


class AtomSystem :
	public System<AtomSystem>
{
	struct Once {
		PacketForwarder*		fwd;
		RealtimeSourceConfig*	cfg;
	};
	LinkedList<Once> once_cbs;
	LinkedList<AtomBaseRef> customers, drivers, pollers, updated;
	Mutex lock;
	
public:
	SYS_RTTI(AtomSystem)
	SYS_CTOR(AtomSystem);
	SYS_DEF_VISIT_H
	
	void AddOnce(PacketForwarder& fwd, RealtimeSourceConfig& cfg);
	
	
	Callback1<PacketForwarder*>				WhenEnterOnceForward;
	Callback1<AtomBase*>					WhenEnterAtomForward;
	Callback1<FwdScope&>					WhenEnterFwdScopeForward;
	
	Callback								WhenLeaveOnceForward;
	Callback								WhenLeaveAtomForward;
	Callback								WhenLeaveFwdScopeForward;
	
	
	static inline Callback& WhenUninit() {static Callback cb; return cb;}
	static ParallelTypeCls::Type GetSerialType() {return ParallelTypeCls::ATOM_SYSTEM;}
	
protected:
	
    bool Initialize() override;
    void Start() override;
    void Update(double dt) override;
    void Stop() override;
    void Uninitialize() override;
    
    void ForwardAtoms(double dt, const char* id, LinkedList<AtomBaseRef>& atoms);
    
    String GetDebugPacketString(AtomBaseRef& c, RealtimeSourceConfig* cfg);
    
public:
	
    void AddCustomer(AtomBaseRef p);
    void AddDriver(AtomBaseRef p);
    void AddPolling(AtomBaseRef p);
    void AddUpdated(AtomBaseRef p);
    void RemoveCustomer(AtomBaseRef p);
    void RemoveDriver(AtomBaseRef p);
    void RemovePolling(AtomBaseRef p);
    void RemoveUpdated(AtomBaseRef p);
	
	
};


NAMESPACE_PARALLEL_END

#endif
