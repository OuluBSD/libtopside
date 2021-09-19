#include "Internal.h"


NAMESPACE_SERIAL_BEGIN


Loop::Loop() {
	DBG_CONSTRUCT
}

Loop::~Loop() {
	DBG_DESTRUCT
}

LoopId Loop::GetNextId() {
	static Atomic next_id;
	return ++next_id;
}

Loop* Loop::GetParent() const {
	return RefScopeParent<LoopParent>::GetParentUnsafe().b;
}

Machine& Loop::GetMachine() const {
	if (machine)
		return *machine;
	const Loop* l = this;
	int levels = 0;
	while (l && levels++ < 1000) {
		const LoopParent& par = l->RefScopeParent<LoopParent>::GetParent();
		if (par.a) {
			machine = &par.a->GetMachine();
			ASSERT(machine);
			return *machine;
		}
		ASSERT(l != par.b);
		l = par.b;
	}
	THROW(Exc("Machine ptr not found"));
}

void Loop::OnChange() {
	changed = GetMachine().GetTicks();
}

AtomBaseRef Loop::GetTypeCls(AtomTypeCls atom_type) {
	for (AtomBaseRef& comp : atoms) {
		AtomTypeCls type = comp->GetType();
		ASSERT(type.IsValid());
		if (type == atom_type)
			return comp;
	}
	return AtomBaseRef();
}

AtomBaseRef Loop::GetAddTypeCls(AtomTypeCls cls) {
	AtomBaseRef cb = FindTypeCls(cls);
	return cb ? cb : AddPtr(GetMachine().Get<AtomStore>()->CreateAtomTypeCls(cls));
}

AtomBaseRef Loop::FindTypeCls(AtomTypeCls atom_type) {
	for (AtomBaseRef& comp : atoms) {
		AtomTypeCls type = comp->GetType();
		if (type == atom_type)
			return comp;
	}
	return AtomBaseRef();
}

AtomBaseRef Loop::AddPtr(AtomBase* comp) {
	comp->SetParent(this);
	atoms.AddBase(comp);
	InitializeAtom(*comp);
	return AtomBaseRef(this, comp);
}

void Loop::InitializeAtoms() {
	for(auto& comp : atoms.GetValues())
		InitializeAtom(*comp);
}

void Loop::InitializeAtom(AtomBase& comp) {
	comp.SetParent(this);
	//comp.Initialize();
}

void Loop::UninitializeAtoms() {
	auto& atoms = this->atoms.GetValues();
	int dbg_i = 0;
	for (auto it = atoms.rbegin(); it != atoms.rend(); --it) {
		it().AltUninitialize();
		it().Uninitialize();
		dbg_i++;
	}
}

void Loop::ClearAtoms() {
	AtomStoreRef sys = GetMachine().Get<AtomStore>();
	for (auto iter = atoms.rbegin(); iter; --iter)
		sys->ReturnAtom(atoms.Detach(iter));
	ASSERT(atoms.IsEmpty());
}

void Loop::ClearInterfaces() {
	for (auto iter = atoms.rbegin(); iter; --iter)
		iter().ClearSinkSource();
}

void Loop::CopyTo(Loop& l) const {
	l.AppendCopy(*this);
}

void Loop::AppendCopy(const Loop& l) {
	TODO
}

/*void Loop::Destroy() {
	Destroyable::Destroy();
	
	for (auto& component : atoms.GetValues()) {
		component->Destroy();
	}
}*/

/*void Loop::SetEnabled(bool enable) {
	Enableable::SetEnabled(enable);
	
	for (auto& component : atoms.GetValues()) {
		component->SetEnabled(enable);
	}
}*/

void Loop::VisitSinks(RuntimeVisitor& vis) {
	for(AtomBaseRef& c : atoms)
		c->VisitSink(vis);
}

void Loop::VisitSources(RuntimeVisitor& vis){
	for(AtomBaseRef& c : atoms)
		c->VisitSource(vis);
}

int Loop::GetLoopDepth() const {
	int d = 0;
	const Loop* p = this;
	while (1) {
		p = p->GetParent();
		if (!p) break;
		++d;
	}
	return d;
}

bool Loop::HasLoopParent(LoopRef pool) const {
	const Loop* p = this;
	while (p) {
		if (p == &*pool)
			return true;
		p = p->GetParent();
	}
	return false;
}

void Loop::Initialize(Loop& l, String prefab) {
	uint64 ticks = GetMachine().GetTicks();
	l.SetPrefab(prefab);
	l.SetCreated(ticks);
	l.SetChanged(ticks);
	
}

LoopRef Loop::CreateEmpty() {
	Loop& l = loops.Add();
	l.SetParent(this);
	l.SetId(GetNextId());
	Initialize(l);
	return l;
}

void Loop::Clear() {
	// useless ClearInterfacesDeep();
	UnrefDeep();
	UnlinkDeep();
	UninitializeAtomsDeep();
	ClearAtomsDeep();
	ClearDeep();
}

void Loop::UnrefDeep() {
	RefClearVisitor vis;
	vis.Visit(*this);
}

void Loop::UnlinkDeep() {
	for (auto it = loops.rbegin(); it != loops.rend(); --it) {
		it().UnlinkDeep();
	}
	
	UnlinkExchangePoints();
	
	/*for (auto it = comps.rbegin(); it != comps.rend(); --it) {
		it().UnlinkAll();
	}*/
}

void Loop::UnlinkExchangePoints() {
	for (ExchangePointRef& pt : pts) {
		pt->Source()	->ClearLink();
		pt->Sink()		->ClearLink();
		pt->Clear();
	}
	pts.Clear();
}

void Loop::UninitializeAtomsDeep() {
	for (LoopRef& p : loops)
		p->UninitializeAtomsDeep();
	
	for (auto it = atoms.rbegin(); it != atoms.rend(); --it) {
		it().UninitializeDeep();
	}
	
	/*for (auto it = comps.rbegin(); it != comps.rend(); --it) {
		it().UninitializeWithExt();
	}*/
}

void Loop::ClearAtomsDeep() {
	for (LoopRef& p : loops)
		p->ClearAtomsDeep();
	
	AtomStoreRef sys = GetMachine().Get<AtomStore>();
	for (auto it = atoms.rbegin(); it != atoms.rend(); --it) {
		sys->ReturnAtom(atoms.Detach(it));
	}
	
}

void Loop::ClearDeep() {
	for (LoopRef& p : loops)
		p->ClearDeep();
	loops.Clear();
	
	atoms.Clear();
}

LoopRef Loop::GetAddEmpty(String name) {
	LoopRef l = FindLoopByName(name);
	if (l)
		return l;
	l = CreateEmpty();
	l->SetName(name);
	return l;
}

LoopRef Loop::FindLoopByName(String name) {
	for (LoopRef object : loops)
		if (object->GetName() == name)
			return object;
	return LoopRef();
}

void Loop::Dump() {
	LOG(GetTreeString());
}

String Loop::GetTreeString(int indent) {
	String s;
	
	String pre;
	pre.Cat('\t', indent);
	
	s << ".." << (name.IsEmpty() ? "unnamed" : "\"" + name + "\"") << "[" << id << "]\n";
	
	for (AtomBaseRef& a : atoms)
		s << a->ToString();
	
	for (LoopRef& l : loops)
		s << l->GetTreeString(indent+1);
	
	return s;
}

bool Loop::Link(AtomBaseRef src_atom, AtomBaseRef dst_atom, ValDevCls iface) {
	ASSERT(iface.IsValid());
	InterfaceSourceRef src = src_atom->GetSource();
	InterfaceSinkRef sink = dst_atom->GetSink();
	ASSERT(src && sink);
	if (!src || !sink)
		return false;
	
	ASSERT(src	->AsAtomBase()->GetLoop()->HasLoopParent(AsRefT()));
	ASSERT(sink	->AsAtomBase()->GetLoop()->HasLoopParent(AsRefT()));
	CookieRef src_cookie, sink_cookie;
	
	if (src->Accept(sink, src_cookie, sink_cookie)) {
		auto& sdmap = Serial::Factory::IfaceLinkDataMap();
		int i = sdmap.Find(iface);
		if (i < 0) {
			LOG("error: no exchange-point class set for type " + iface.ToString());
			ASSERT(0);
			return false;
		}
		const auto& src_d = sdmap[i];
		if (src_d.vd != iface) {
			ASSERT(0);
			LOG("internal error: unexpected sink class type");
			return false;
		}
		
		TypeCls expt_type = src_d.cls;
		ASSERT(expt_type);
		ExchangePointRef ep = MetaExchangePoint::Add(expt_type);
		RTLOG("Loop::Link(...): created " << ep->GetDynamicName() << " at " << HexStr(&ep->GetRTTI()));
		src->Link(ep, sink, src_cookie, sink_cookie);
		ep->Init(this);
		ep->Set(src, sink, src_cookie, sink_cookie);
		return true;
	}
	return false;
}




bool LoopHashVisitor::OnEntry(const RTTI& type, TypeCls derived, const char* derived_name, void* mem, LockedScopeRefCounter* ref) {
	if (derived == AsTypeCls<Loop>()) {
		Loop& e = *(Loop*)mem;
		ch.Put(1);
		ch.Put(e.GetId());
	}
	else if (derived == AsTypeCls<Loop>()) {
		Loop& p = *(Loop*)mem;
		ch.Put(2);
		ch.Put(p.GetId());
	}
	return true;
}

NAMESPACE_SERIAL_END
