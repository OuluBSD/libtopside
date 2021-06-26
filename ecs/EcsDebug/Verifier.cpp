#include "EcsDebug.h"

NAMESPACE_ECS_BEGIN


MachineVerifier::MachineVerifier() {
	
}

void MachineVerifier::Attach(Machine& mach) {
	this->mach = &mach;
	
	mach.WhenUpdate << THISBACK(OnUpdate);
	mach.WhenSystemUpdate << THISBACK(OnSystemUpdate);
	
}

void MachineVerifier::Clear() {
	mach = 0;
	ext_sys = 0;
}

VerifierSystem& MachineVerifier::AddSystem(TypeCls t, EcsTypeCls et) {
	VerifierSystem& sys = this->sys.Add();
	sys.type = t;
	sys.ecs_type = et;
	return sys;
}

void MachineVerifier::OnUpdate() {
	RTLOG("MachineVerifier::OnUpdate");
	
	
}

void MachineVerifier::OnSystemUpdate(SystemBase& base) {
	RTLOG("MachineVerifier::OnSystemUpdate " << HexStr((void*)&base));
	
	if (!ext_sys && (ext_sys = CastPtr<ExtSystem>(&base))) {
		ext_sys->WhenOnceForward << THISBACK(OnOnceForward);
		ext_sys->WhenExtComponentForward << THISBACK(OnExtComponentForward);
		ext_sys->WhenFwdScopeForward << THISBACK(OnFwdScopeForward);
	}
	
	
}

void MachineVerifier::OnOnceForward(PacketForwarder* fwd) {
	RTLOG("MachineVerifier::OnOnceForward " << HexStr((void*)fwd));
	
}

void MachineVerifier::OnExtComponentForward(ExtComponent* c) {
	RTLOG("MachineVerifier::OnExtComponentForward " << HexStr((void*)c));
	
}

void MachineVerifier::OnFwdScopeForward(FwdScope& f) {
	RTLOG("MachineVerifier::OnFwdScopeForward " << HexStr((void*)&f));
	
	ExtComponent* c = CastPtr<ExtComponent>(f.GetCurrent());
	if (c && !c->WhenStorePacket) {
		c->WhenStorePacket << THISBACK(OnStorePacket);
		c->WhenCreatedEmptyPacket << THISBACK(OnCreatedEmptyPacket);
	}
	
	
}

void MachineVerifier::OnStorePacket(ComponentExtBase& b, Packet& p) {
	RTLOG("MachineVerifier::OnStorePacket " << HexStr((void*)&b) << ", " << HexStr((void*)&*p));
	
}

void MachineVerifier::OnCreatedEmptyPacket(Packet& p) {
	RTLOG("MachineVerifier::OnCreatedEmptyPacket " << HexStr((void*)&*p));
	
}













void VerifierExtComponent::SetSourceFormat(Format fmt) {
	src_fmt = fmt;
}

void VerifierExtComponent::SetSinkFormat(Format fmt) {
	sink_fmt = fmt;
}

void VerifierExtComponent::LinkTo(VerifierExtComponent& comp) {
	ASSERT(!src);
	src = &comp;
}









VerifierExtComponent& VerifierEntity::AddExtComponentWith(EcsTypeCls t) {
	VerifierExtComponent& e = ext.Add();
	e.type = t;
	return e;
}




NAMESPACE_ECS_END
