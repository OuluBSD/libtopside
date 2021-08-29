#ifndef _SerialCore_AtomSystem_h_
#define _SerialCore_AtomSystem_h_

NAMESPACE_SERIAL_BEGIN


class AtomSystem : public System<AtomSystem> {
	
	
public:
	SYS_RTTI(AtomSystem)
    SYS_CTOR(AtomSystem)
	SYS_DEF_VISIT
	
	
	Callback1<PacketForwarder*>				WhenEnterOnceForward;
	Callback1<AtomSystem*>					WhenEnterAtomForward;
	Callback1<FwdScope&>					WhenEnterFwdScopeForward;
	
	Callback								WhenLeaveOnceForward;
	Callback								WhenLeaveAtomForward;
	Callback								WhenLeaveFwdScopeForward;
	
	
	
	static SerialTypeCls::Type GetSerialType() {return SerialTypeCls::ATOM_SYSTEM;}
	
	
};


NAMESPACE_SERIAL_END

#endif
