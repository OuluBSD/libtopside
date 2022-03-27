#ifndef _SerialMach_LinkSystem_h_
#define _SerialMach_LinkSystem_h_

NAMESPACE_SERIAL_BEGIN


class LinkSystem :
	public System<LinkSystem>
{
	struct Once {
		PacketForwarder*		fwd;
		RealtimeSourceConfig*	cfg;
	};
	LinkedList<Once> once_cbs;
	LinkedList<LinkBaseRef> customers, drivers, pollers;
	Mutex lock;
	
public:
	SYS_RTTI(LinkSystem)
	SYS_CTOR(LinkSystem);
	SYS_DEF_VISIT_H
	
	void AddOnce(PacketForwarder& fwd, RealtimeSourceConfig& cfg);
	
	Callback1<PacketForwarder*>				WhenEnterOnceForward;
	Callback1<LinkBase*>					WhenEnterLinkForward;
	Callback1<FwdScope&>					WhenEnterFwdScopeForward;
	
	Callback								WhenLeaveOnceForward;
	Callback								WhenLeaveLinkForward;
	Callback								WhenLeaveFwdScopeForward;
	
	
	static inline Callback& WhenUninit() {static Callback cb; return cb;}
	static ParallelTypeCls::Type GetSerialType() {return ParallelTypeCls::LOOP_SYSTEM;}
	
protected:
	
    bool Initialize() override;
    void Start() override;
    void Update(double dt) override;
    void Stop() override;
    void Uninitialize() override;
    
    void ForwardLinks(double dt, const char* id, LinkedList<LinkBaseRef>& links);
    
    
public:
    void AddCustomer(LinkBaseRef p);
    void AddDriver(LinkBaseRef p);
    void AddPolling(LinkBaseRef p);
    void RemoveCustomer(LinkBaseRef p);
    void RemoveDriver(LinkBaseRef p);
    void RemovePolling(LinkBaseRef p);
    
    String GetDebugPacketString(LinkBaseRef& c, RealtimeSourceConfig* cfg);
    
};


NAMESPACE_SERIAL_END

#endif
