#include "AtomDebug.h"


#if 0
	#define MVER_LOG(x) RTLOG(x)
#else
	#define MVER_LOG(x)
#endif


NAMESPACE_SERIAL_BEGIN


MachineVerifier* __latest_mver;


#define MACHVER_FWD_FN(x) \
	void MachineVerifier_OnEnter##x(size_t call_id) { \
		if (__latest_mver) \
			__latest_mver->OnEnter##x(call_id); \
	} \
	 \
	void MachineVerifier_OnLeave##x(size_t call_id) { \
		if (__latest_mver) \
			__latest_mver->OnLeave##x(call_id); \
	} \

MACHVER_FWDFN_LIST
#undef MACHVER_FWD_FN

void MachineVerifier_OnLoopLoader_Status(ScriptLoopLoader* ll) {
	if (__latest_mver)
		__latest_mver->OnLoopLoader_Status(ll);
}

void MachineVerifier_OnLoopLoader_RealizeAtoms(ScriptLoopLoader* ll) {
	if (__latest_mver)
		__latest_mver->OnLoopLoader_RealizeAtoms(ll);
}

void MachineVerifier_OnLoopLoader_AtomLinked(ScriptLoopLoader* ll) {
	if (__latest_mver)
		__latest_mver->OnLoopLoader_AtomLinked(ll);
}

void MachineVerifier_OnLoopLoader_SearchNewSegment(ScriptLoopLoader* ll) {
	if (__latest_mver)
		__latest_mver->OnLoopLoader_SearchNewSegment(ll);
}




MachineVerifier::MachineVerifier() {
	ASSERT(!__latest_mver);
	__latest_mver = this;
	
	Clear();
}

void MachineVerifier::Attach(Machine& mach) {
	this->mach = &mach;
	mach.mver = this;
	
	mach.WhenEnterUpdate << THISBACK(OnEnterUpdate);
	mach.WhenEnterSystemUpdate << THISBACK(OnEnterSystemUpdate);
	
	mach.WhenLeaveUpdate << THISBACK(OnLeaveUpdate);
	mach.WhenLeaveSystemUpdate << THISBACK(OnLeaveSystemUpdate);
	
}

void MachineVerifier::Attach(ScriptLoader& sl) {
	sl.WhenEnterScriptLoad << THISBACK(OnEnterScriptLoad);
	sl.WhenLeaveScriptLoad << THISBACK(OnLeaveScriptLoad);
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
	if (!Thread::IsMain()) return;
	ASSERT(!stack.IsEmpty());
	Scope& scope = stack.Top();
	if (!scope.CanEnter(t))
		Panic("MachineVerifier enter failed: not allowed");
	
	Scope& cur = stack.Add();
	cur.type = t;
}

void MachineVerifier::Leave(Type t) {
	if (!Thread::IsMain()) return;
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
	if (!Thread::IsMain()) return;
	
	MVER_LOG("MachineVerifier::OnEnterUpdate");
	Enter(UPDATE);
	
	Scope& cur = stack.Top();
	cur.MayLeave(true);
	cur.AddEnter(SYSTEM_UPDATE);
	
}

void MachineVerifier::OnEnterSystemUpdate(SystemBase& base) {
	if (!Thread::IsMain()) return;
	
	MVER_LOG("MachineVerifier::OnEnterSystemUpdate " << HexStr((void*)&base));
	Enter(SYSTEM_UPDATE);
	
	Scope& cur = stack.Top();
	cur.MayLeave(true);
	cur.AddEnter(EXTCOMP_FORWARD);
	cur.AddEnter(ONCE_FORWARD);
	cur.AddEnter(SCRIPT_LOAD);
		
	if (!ext_sys && (ext_sys = CastPtr<AtomSystem>(&base))) {
		ext_sys->WhenEnterOnceForward << THISBACK(OnEnterOnceForward);
		ext_sys->WhenEnterAtomForward << THISBACK(OnEnterAtomForward);
		ext_sys->WhenEnterFwdScopeForward << THISBACK(OnEnterFwdScopeForward);
		
		ext_sys->WhenLeaveOnceForward << THISBACK(OnLeaveOnceForward);
		ext_sys->WhenLeaveAtomForward << THISBACK(OnLeaveAtomForward);
		ext_sys->WhenLeaveFwdScopeForward << THISBACK(OnLeaveFwdScopeForward);
	}
	
	
}

void MachineVerifier::OnEnterScriptLoad(SystemBase& base) {
	if (!Thread::IsMain()) return;
	
	MVER_LOG("MachineVerifier::OnEnterScriptLoad");
	
	Enter(SCRIPT_LOAD);
	
	Scope& cur = stack.Top();
	cur.AddEnter(LOOPLOADER_FORWARD_BEGINNING);
	cur.MayLeave(true); // because of errors
}

void MachineVerifier::OnEnterTerminalTest(size_t call_id) {
	if (!Thread::IsMain()) return;
	
	MVER_LOG("MachineVerifier::OnEnterTerminalTest " << HexStr(call_id));
	Enter(TERMINAL_TEST);
	
	Scope& cur = stack.Top();
	cur.MayLeave(true);
}

void MachineVerifier::OnEnterSearchNewSegment(size_t call_id) {
	if (!Thread::IsMain()) return;
	
	MVER_LOG("MachineVerifier::OnEnterSearchNewSegment " << HexStr(call_id));
	Enter(LOOPLOADER_SEARCH_NEW_SEGMENT);
	
	Scope& cur = stack.Top();
	cur.AddEnter(TERMINAL_TEST);
}

void MachineVerifier::OnEnterScriptLoopLoaderForwardBeginning(size_t call_id) {
	if (!Thread::IsMain()) return;
	
	MVER_LOG("MachineVerifier::OnEnterScriptLoopLoaderForwardBeginning " << HexStr(call_id));
	Enter(LOOPLOADER_FORWARD_BEGINNING);
	
	Scope& cur = stack.Top();
	cur.AddEnter(LOOPLOADER_SEARCH_NEW_SEGMENT);
}

void MachineVerifier::OnEnterScriptLoopLoaderForwardRetry(size_t call_id) {
	
	MVER_LOG("MachineVerifier::OnEnterScriptLoopLoaderForwardRetry " << HexStr(call_id));
	Enter(LOOPLOADER_FORWARD_RETRY);
	
	Scope& cur = stack.Top();
	cur.AddEnter(LOOPLOADER_SEARCH_NEW_SEGMENT);
	cur.AddEnter(LOOPLOADER_FORWARD_SIDES);
}

void MachineVerifier::OnEnterScriptLoopLoaderForwardSides(size_t call_id) {
	
	MVER_LOG("MachineVerifier::OnEnterScriptLoopLoaderForwardSides " << HexStr(call_id));
	Enter(LOOPLOADER_FORWARD_SIDES);
}

void MachineVerifier::OnEnterOnceForward(PacketForwarder* fwd) {
	if (!Thread::IsMain()) return;
	
	MVER_LOG("MachineVerifier::OnEnterOnceForward " << HexStr((void*)fwd));
	Enter(ONCE_FORWARD);
	
	Scope& cur = stack.Top();
	cur.AddEnter(FWDSCOPE_FORWARD);
	
}

void MachineVerifier::OnEnterAtomForward(AtomBase* c) {
	if (!Thread::IsMain()) return;
	
	MVER_LOG("MachineVerifier::OnEnterAtomForward " << HexStr((void*)c));
	Enter(EXTCOMP_FORWARD);
	
	Scope& cur = stack.Top();
	cur.AddEnter(FWDSCOPE_FORWARD);
	
}

void MachineVerifier::OnEnterFwdScopeForward(FwdScope& f) {
	if (!Thread::IsMain()) return;
	
	MVER_LOG("MachineVerifier::OnEnterFwdScopeForward " << HexStr((void*)&f));
	Enter(FWDSCOPE_FORWARD);
	
	Scope& cur = stack.Top();
	cur.AddEnter(CREATE_EMPTY_PACKET);
	cur.AddEnter(PROCESS_PACKETS);
	cur.AddEnter(VALEXPT_FWD);
	
	cur_pk.Clear();
	c = 0;
	vep = 0;
	if ((c = CastPtr<AtomBase>(f.GetCurrent()))) {
		if (!c->WhenEnterProcessPackets) {
			c->WhenEnterProcessPackets << THISBACK(OnEnterProcessPackets);
			c->WhenLeaveProcessPackets << THISBACK(OnLeaveProcessPackets);
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

void MachineVerifier::OnEnterProcessPackets(AtomBase& b, PacketIO& p) {
	if (!Thread::IsMain()) return;
	
	MVER_LOG("MachineVerifier::OnEnterProcessPackets " << HexStr((void*)&b) << ", " << HexStr((void*)&*p.sink[0].p));
	Enter(PROCESS_PACKETS);
	
	// don't add this you dumb fuck: MayLeaveTop();
}

void MachineVerifier::OnEnterCreatedEmptyPacket(Packet& p) {
	if (!Thread::IsMain()) return;
	
	MVER_LOG("MachineVerifier::OnEnterCreatedEmptyPacket " << HexStr((void*)&*p));
	Enter(CREATE_EMPTY_PACKET);
	
	MayLeaveTop();
}

void MachineVerifier::OnEnterValExPtForward(DefaultExchangePoint& p) {
	if (!Thread::IsMain()) return;
	
	MVER_LOG("MachineVerifier::OnEnterValExPtForward");
	Enter(VALEXPT_FWD);
	
	MayLeaveTop();
}



void MachineVerifier::OnLeaveUpdate() {
	if (!Thread::IsMain()) return;
	
	MVER_LOG("MachineVerifier::OnLeaveUpdate");
	Leave(UPDATE);
	
}

void MachineVerifier::OnLeaveSystemUpdate() {
	if (!Thread::IsMain()) return;
	
	MVER_LOG("MachineVerifier::OnLeaveSystemUpdate");
	Leave(SYSTEM_UPDATE);
	
}

void MachineVerifier::OnLeaveOnceForward() {
	if (!Thread::IsMain()) return;
	
	MVER_LOG("MachineVerifier::OnLeaveOnceForward");
	Leave(ONCE_FORWARD);
	
}

void MachineVerifier::OnLeaveAtomForward() {
	if (!Thread::IsMain()) return;
	
	MVER_LOG("MachineVerifier::OnLeaveAtomForward");
	Leave(EXTCOMP_FORWARD);
	
}

void MachineVerifier::OnLeaveFwdScopeForward() {
	if (!Thread::IsMain()) return;
	
	MVER_LOG("MachineVerifier::OnLeaveFwdScopeForward");
	
	if (cur_pk.bytes) {
		MVER_LOG("Sent: " << cur_pk.count << " packets, " << cur_pk.bytes << " bytes, " << cur_pk.ch_samples << " ch-samples");
	}
	
	MayLeaveTop();
	
	Leave(FWDSCOPE_FORWARD);
	
	MayLeaveTop();
}

void MachineVerifier::OnLeaveProcessPackets(AtomBase& b, PacketIO& io) {
	if (!Thread::IsMain()) return;
	
	MVER_LOG("MachineVerifier::OnLeaveStorePacket");

	PacketIO::Source& prim_src = io.src[0];
	ASSERT_(prim_src.p, "primary packet must be forwarded always");
	
	Packet& prim_p = prim_src.p;
	auto fmt = prim_p->GetFormat();
	if (prim_p->Data().GetCount() &&
		fmt.IsValid()) {
		MayLeaveTop();
	}
	else {
		ASSERT_(0, "Packet is not valid");
	}
	
	Leave(PROCESS_PACKETS);
	
	if (prim_p)
		cur_pk.Add(prim_p);
}

void MachineVerifier::PacketData::Add(Packet& p) {
	if (p->IsBuffered()) {
		ch_samples += p->GetSizeChannelSamples();
	}
	bytes += p->Data().GetCount();
	count++;
}

void MachineVerifier::OnLeaveCreatedEmptyPacket() {
	if (!Thread::IsMain()) return;
	
	MVER_LOG("MachineVerifier::OnLeaveCreatedEmptyPacket");
	Leave(CREATE_EMPTY_PACKET);
	
	MayLeaveTop();
}

void MachineVerifier::OnLeaveValExPtForward() {
	if (!Thread::IsMain()) return;
	
	MVER_LOG("MachineVerifier::OnLeaveValExPtForward");
	Leave(VALEXPT_FWD);
	
	MayLeaveTop();
}

void MachineVerifier::OnLeaveScriptLoad() {
	if (!Thread::IsMain()) return;
	
	MVER_LOG("MachineVerifier::OnLeaveScriptLoad");
	Leave(SCRIPT_LOAD);
}

void MachineVerifier::OnLeaveTerminalTest(size_t call_id) {
	if (!Thread::IsMain()) return;
	
	MVER_LOG("MachineVerifier::OnLeaveTerminalTest");
	Leave(TERMINAL_TEST);
}

void MachineVerifier::OnLeaveSearchNewSegment(size_t call_id) {
	if (!Thread::IsMain()) return;
	
	MVER_LOG("MachineVerifier::OnLeaveSearchNewSegment");
	Leave(LOOPLOADER_SEARCH_NEW_SEGMENT);
	
	Scope& cur = stack.Top();
	cur.may_leave = true;
}

void MachineVerifier::OnLeaveScriptLoopLoaderForwardBeginning(size_t call_id) {
	if (!Thread::IsMain()) return;
	
	MVER_LOG("MachineVerifier::OnLeaveScriptLoopLoaderForwardBeginning");
	Leave(LOOPLOADER_FORWARD_BEGINNING);
	
	Scope& cur = stack.Top();
	cur.AddEnter(LOOPLOADER_FORWARD_RETRY);
	
	if (cur.type == SCRIPT_LOAD)
		cur.MayLeave(true);
}

void MachineVerifier::OnLeaveScriptLoopLoaderForwardRetry(size_t call_id) {
	if (!Thread::IsMain()) return;
	
	MVER_LOG("MachineVerifier::OnLeaveScriptLoopLoaderForwardRetry");
	Leave(LOOPLOADER_FORWARD_RETRY);
}

void MachineVerifier::OnLeaveScriptLoopLoaderForwardSides(size_t call_id) {
	if (!Thread::IsMain()) return;
	
	MVER_LOG("MachineVerifier::OnLeaveScriptLoopLoaderForwardSides");
	Leave(LOOPLOADER_FORWARD_SIDES);
}









void MachineVerifier::OnLoopLoader_Status(ScriptLoopLoader* ll) {
	LoopLoaderData& data = loop_loaders.GetAdd((size_t)ll);
	data.ll = ll;
	auto new_status = ll->GetStatus();
	MVER_LOG("MachineVerifier::OnLoopLoader_Status: set loop " << ll->def.id.ToString() << " " << HexStr(ll) << " status to " << GetScriptStatusString(new_status) << " (from " << GetScriptStatusString(data.status0) << ")");
	
	
	data.status1 = data.status0;
	data.status0 = new_status;
	
	
	Scope& cur = stack.Top();
	if (cur.type == LOOPLOADER_SEARCH_NEW_SEGMENT)
		cur.may_leave = true;
	
}

void MachineVerifier::UpdateLoopData(ScriptLoopLoader* ll) {
	int atom_count = ll->atom_links.GetCount();
	
	LoopLoaderData& data = loop_loaders.GetAdd((size_t)ll);
	int atoms_added = atom_count - data.atoms.GetCount();
	ASSERT(atom_count >= data.atoms.GetCount());
	data.atoms.SetCount(atom_count);
	
	if (atoms_added > 0 && !data.MayCreateAtoms())
		Panic("Loop may not create atoms");
	
	for(int i = 0; i < atom_count; i++) {
		const ScriptLoopLoader::AtomSideLinks& ll_atom = ll->atom_links[i];
		LoopAtomData& atom = data.atoms[i];
		
		atom.type = ll_atom.type;
		
		int src_side_count = ll_atom.src_side_conns.GetCount();
		int sink_side_count = ll_atom.sink_side_conns.GetCount();
		
		atom.src_sides.SetCount(src_side_count);
		atom.sink_sides.SetCount(sink_side_count);
		
		for(int j = 0; j < src_side_count; j++) {
			const ScriptLoopLoader::SideLink& ll_side = ll_atom.src_side_conns[j];
			LoopAtomSideData& side = atom.src_sides[j];
			
			ASSERT_(!(side.has_link && ll_side.link == NULL), "link disappeared");
			side.has_link = ll_side.link != NULL;
			side.is_required = ll_side.is_required;
			side.vd = ll_side.vd;
		}
		
		for(int j = 0; j < sink_side_count; j++) {
			const ScriptLoopLoader::SideLink& ll_side = ll_atom.sink_side_conns[j];
			LoopAtomSideData& side = atom.sink_sides[j];
			
			ASSERT_(!(side.has_link && ll_side.link == NULL), "link disappeared");
			side.has_link = ll_side.link != NULL;
			side.is_required = ll_side.is_required;
			side.vd = ll_side.vd;
		}
	}
}

void MachineVerifier::OnLoopLoader_RealizeAtoms(ScriptLoopLoader* ll) {
	LoopLoaderData& data = loop_loaders.GetAdd((size_t)ll);
	int prev_count = data.atoms.GetCount();
	
	UpdateLoopData(ll);
	
	int atoms_added = data.atoms.GetCount() - prev_count;
}

void MachineVerifier::OnLoopLoader_AtomLinked(ScriptLoopLoader* ll) {
	
	UpdateLoopData(ll);
	
	MVER_LOG("MachineVerifier::OnLoopLoader_AtomLinked: linked interface in loop " << HexStr(ll));
}

void MachineVerifier::OnLoopLoader_SearchNewSegment(ScriptLoopLoader* ll) {
	MVER_LOG("MachineVerifier::OnLoopLoader_SearchNewSegment");
	
	LoopLoaderData& data = loop_loaders.GetAdd((size_t)ll);
	if (!data.atoms.IsEmpty() && !data.MayCreateAtoms())
		Panic("Searching new segment is not allowed before last atom is fully-connected");
	
	
}

bool MachineVerifier::LoopLoaderData::MayCreateAtoms() const {
	if (atoms.IsEmpty())
		return true;
	
	const LoopAtomData& last_atom = atoms.Top();
	
	for (LoopAtomSideData& side : last_atom.sink_sides)
		if (!side.has_link && side.is_required)
			return false;
	
	for (LoopAtomSideData& side : last_atom.src_sides)
		if (!side.has_link && side.is_required)
			return false;
	
	return true;
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
