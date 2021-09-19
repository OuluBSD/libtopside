#include "AtomDebug.h"

NAMESPACE_SERIAL_BEGIN


MachineVerifier::MachineVerifier() {
	Clear();
}

void MachineVerifier::Attach(Machine& mach) {
	this->mach = &mach;
	
	mach.WhenEnterUpdate << THISBACK(OnEnterUpdate);
	mach.WhenEnterSystemUpdate << THISBACK(OnEnterSystemUpdate);
	
	mach.WhenLeaveUpdate << THISBACK(OnLeaveUpdate);
	mach.WhenLeaveSystemUpdate << THISBACK(OnLeaveSystemUpdate);
	
}

void MachineVerifier::Clear() {
	mach = 0;
	ext_sys = 0;
	SetDefaultExpected();
}

void MachineVerifier::MayLeaveTop() {
	Scope& cur = stack.Top();
	cur.MayLeave(true);
}

void MachineVerifier::SetDefaultExpected() {
	stack.Clear();
	Scope& scope = stack.Add();
	scope.type = ROOT;
	scope.AddEnter(UPDATE);
}

VerifierSystem& MachineVerifier::AddSystem(TypeCls t, SerialTypeCls et) {
	VerifierSystem& sys = this->sys.Add();
	sys.type = t;
	sys.ecs_type = et;
	return sys;
}

bool MachineVerifier::Scope::CanEnter(Type t) const {
	bool found = false;
	for (const ExpectedAction& a : enter) {
		if (a.type == t) {
			found = true;
			break;
		}
	}
	return found;
}

void MachineVerifier::Enter(Type t) {
	ASSERT(!stack.IsEmpty());
	Scope& scope = stack.Top();
	if (!scope.CanEnter(t))
		Panic("MachineVerifier enter failed: not allowed");
	
	Scope& cur = stack.Add();
	cur.type = t;
}

void MachineVerifier::Leave(Type t) {
	ASSERT(!stack.IsEmpty());
	Scope& scope = stack.Top();
	if (!scope.may_leave)
		Panic("MachineVerifier leave failed: scope is not allowed to leave here");
	if (scope.type != t)
		Panic("MachineVerifier leave failed: unexpected scope type");
	
	stack.SetCount(stack.GetCount()-1);
	
	if (stack.IsEmpty())
		SetDefaultExpected();
}

void MachineVerifier::OnEnterUpdate() {
	RTLOG("MachineVerifier::OnEnterUpdate");
	Enter(UPDATE);
	
	Scope& cur = stack.Top();
	cur.MayLeave(true);
	cur.AddEnter(SYSTEM_UPDATE);
	
}

void MachineVerifier::OnEnterSystemUpdate(SystemBase& base) {
	RTLOG("MachineVerifier::OnEnterSystemUpdate " << HexStr((void*)&base));
	Enter(SYSTEM_UPDATE);
	
	Scope& cur = stack.Top();
	cur.MayLeave(true);
	cur.AddEnter(EXTCOMP_FORWARD);
	cur.AddEnter(ONCE_FORWARD);
		
	if (!ext_sys && (ext_sys = CastPtr<AtomSystem>(&base))) {
		ext_sys->WhenEnterOnceForward << THISBACK(OnEnterOnceForward);
		ext_sys->WhenEnterAtomForward << THISBACK(OnEnterAtomForward);
		ext_sys->WhenEnterFwdScopeForward << THISBACK(OnEnterFwdScopeForward);
		
		ext_sys->WhenLeaveOnceForward << THISBACK(OnLeaveOnceForward);
		ext_sys->WhenLeaveAtomForward << THISBACK(OnLeaveAtomForward);
		ext_sys->WhenLeaveFwdScopeForward << THISBACK(OnLeaveFwdScopeForward);
	}
	
	
}

void MachineVerifier::OnEnterOnceForward(PacketForwarder* fwd) {
	RTLOG("MachineVerifier::OnEnterOnceForward " << HexStr((void*)fwd));
	Enter(ONCE_FORWARD);
	
	Scope& cur = stack.Top();
	//cur.MayLeave(true);
	cur.AddEnter(FWDSCOPE_FORWARD);
	
}

void MachineVerifier::OnEnterAtomForward(AtomBase* c) {
	RTLOG("MachineVerifier::OnEnterAtomForward " << HexStr((void*)c));
	Enter(EXTCOMP_FORWARD);
	
	Scope& cur = stack.Top();
	//cur.MayLeave(true);
	cur.AddEnter(FWDSCOPE_FORWARD);
	
}

void MachineVerifier::OnEnterFwdScopeForward(FwdScope& f) {
	RTLOG("MachineVerifier::OnEnterFwdScopeForward " << HexStr((void*)&f));
	Enter(FWDSCOPE_FORWARD);
	
	Scope& cur = stack.Top();
	//cur.MayLeave(true);
	cur.AddEnter(CREATE_EMPTY_PACKET);
	cur.AddEnter(STORE_PACKET);
	cur.AddEnter(VALEXPT_FWD);
	
	cur_pk.Clear();
	c = 0;
	vep = 0;
	if ((c = CastPtr<AtomBase>(f.GetCurrent()))) {
		if (!c->WhenEnterStorePacket) {
			c->WhenEnterStorePacket << THISBACK(OnEnterStorePacket);
			c->WhenEnterCreatedEmptyPacket << THISBACK(OnEnterCreatedEmptyPacket);
			
			c->WhenLeaveStorePacket << THISBACK(OnLeaveStorePacket);
			c->WhenLeaveCreatedEmptyPacket << THISBACK(OnLeaveCreatedEmptyPacket);
		}
	}
	else if ((vep = CastPtr<DefaultExchangePoint>(f.GetCurrent()))) {
		if (!vep->WhenEnterValExPtForward) {
			vep->WhenEnterValExPtForward << THISBACK(OnEnterValExPtForward);
			
			vep->WhenLeaveValExPtForward << THISBACK(OnLeaveValExPtForward);
		}
	}
	else TODO;
	
}

void MachineVerifier::OnEnterStorePacket(AtomBase& b, Packet& p) {
	RTLOG("MachineVerifier::OnEnterStorePacket " << HexStr((void*)&b) << ", " << HexStr((void*)&*p));
	Enter(STORE_PACKET);
	
}

void MachineVerifier::OnEnterCreatedEmptyPacket(Packet& p) {
	RTLOG("MachineVerifier::OnEnterCreatedEmptyPacket " << HexStr((void*)&*p));
	Enter(CREATE_EMPTY_PACKET);
	
	MayLeaveTop();
}

void MachineVerifier::OnEnterValExPtForward(DefaultExchangePoint& p) {
	RTLOG("MachineVerifier::OnEnterValExPtForward");
	Enter(VALEXPT_FWD);
	
	MayLeaveTop();
}



void MachineVerifier::OnLeaveUpdate() {
	RTLOG("MachineVerifier::OnLeaveUpdate");
	Leave(UPDATE);
	
}

void MachineVerifier::OnLeaveSystemUpdate() {
	RTLOG("MachineVerifier::OnLeaveSystemUpdate");
	Leave(SYSTEM_UPDATE);
	
}

void MachineVerifier::OnLeaveOnceForward() {
	RTLOG("MachineVerifier::OnLeaveOnceForward");
	Leave(ONCE_FORWARD);
	
}

void MachineVerifier::OnLeaveAtomForward() {
	RTLOG("MachineVerifier::OnLeaveAtomForward");
	Leave(EXTCOMP_FORWARD);
	
}

void MachineVerifier::OnLeaveFwdScopeForward() {
	RTLOG("MachineVerifier::OnLeaveFwdScopeForward");
	
	if (cur_pk.bytes) {
		RTLOG("Sent: " << cur_pk.count << " packets, " << cur_pk.bytes << " bytes, " << cur_pk.ch_samples << " ch-samples");
		/*if (c) {
			Format fmt = c->GetSourceValue().GetFormat();
			RTLOG("Sending format: " << fmt.ToString());
			
			if (fmt.IsAudio()) {
				AudioFormat& afmt = fmt;
				int sample_rate = afmt.GetSampleRate();
				int min_ch_samples = fmt.GetMinBufSamples();
				int max_ch_samples = min_ch_samples + sample_rate;
				RTLOG("Testing: " << min_ch_samples << " <= " << cur_pk.ch_samples << " < " << max_ch_samples);
				if (cur_pk.ch_samples < min_ch_samples || cur_pk.ch_samples >= max_ch_samples)
					Panic("Invalid sample count sent");
			}
			else if (fmt.vd.val.type == ValCls::RECEIPT) {
				
			}
			else TODO
		}*/
	}
	
	MayLeaveTop();
	
	Leave(FWDSCOPE_FORWARD);
	
	MayLeaveTop();
}

void MachineVerifier::OnLeaveStorePacket(Packet& p) {
	RTLOG("MachineVerifier::OnLeaveStorePacket");
	auto fmt = p->GetFormat();
	if (p->Data().GetCount() &&
		fmt.IsValid()) {
		MayLeaveTop();
	}
	
	Leave(STORE_PACKET);
	
	
	cur_pk.Add(p);
}

void MachineVerifier::PacketData::Add(Packet& p) {
	if (p->IsBuffered()) {
		ch_samples += p->GetSizeChannelSamples();
	}
	bytes += p->Data().GetCount();
	count++;
}

void MachineVerifier::OnLeaveCreatedEmptyPacket() {
	RTLOG("MachineVerifier::OnLeaveCreatedEmptyPacket");
	Leave(CREATE_EMPTY_PACKET);
	
	MayLeaveTop();
}

void MachineVerifier::OnLeaveValExPtForward() {
	RTLOG("MachineVerifier::OnLeaveValExPtForward");
	Leave(VALEXPT_FWD);
	
	MayLeaveTop();
}













void VerifierAtom::SetSourceFormat(Format fmt) {
	src_fmt = fmt;
}

void VerifierAtom::SetSinkFormat(Format fmt) {
	sink_fmt = fmt;
}

void VerifierAtom::LinkTo(VerifierAtom& comp) {
	ASSERT(!src);
	src = &comp;
}









VerifierAtom& VerifierEntity::AddAtomWith(SerialTypeCls t) {
	VerifierAtom& e = ext.Add();
	e.type = t;
	return e;
}

NAMESPACE_SERIAL_END
