#ifndef _SerialCore_AtomSystem_h_
#define _SerialCore_AtomSystem_h_

NAMESPACE_SERIAL_BEGIN


class AtomSystem :
	public System<AtomSystem>
{
	struct Once {
		PacketForwarder*		fwd;
		RealtimeSourceConfig*	cfg;
	};
	LinkedList<Once> once_cbs;
	LinkedList<AtomBaseRef> customers;
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
	static SerialTypeCls::Type GetSerialType() {return SerialTypeCls::ATOM_SYSTEM;}
	
protected:
	
    bool Initialize() override;
    void Start() override;
    void Update(double dt) override;
    void Stop() override;
    void Uninitialize() override;
    
public:
	
    void Add(AtomBaseRef p);
    void Remove(AtomBaseRef p);
	
	
};


NAMESPACE_SERIAL_END

#endif
