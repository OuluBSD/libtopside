#include "SerialCore.h"

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

String Loop::GetTreeString(int indent) {
	String s;
	
	s.Cat('\t', indent);
	
	s << (name.IsEmpty() ? "unnamed" : "\"" + name + "\"") << ": " << prefab << "\n";
	
	for (AtomBaseRef& c : atoms) {
		s.Cat('\t', indent+1);
		s << c->ToString();
		s.Cat('\n');
	}
	
	return s;
}

void Loop::OnChange() {
	changed = GetMachine().GetTicks();
}

AtomBaseRef Loop::GetTypeCls(TypeAtomCls atom_type) {
	for (AtomBaseRef& comp : atoms) {
		TypeAtomCls type = comp->GetType();
		ASSERT(type.IsValid());
		if (type == atom_type)
			return comp;
	}
	return AtomBaseRef();
}

AtomBaseRef Loop::GetAddTypeCls(TypeAtomCls cls) {
	AtomBaseRef cb = FindTypeCls(cls);
	return cb ? cb : AddPtr(GetMachine().Get<AtomStore>()->CreateAtomTypeCls(cls));
}

AtomBaseRef Loop::FindTypeCls(TypeAtomCls atom_type) {
	for (AtomBaseRef& comp : atoms) {
		TypeAtomCls type = comp->GetType();
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
	comp.Initialize();
}

void Loop::UninitializeAtoms() {
	auto& atoms = this->atoms.GetValues();
	int dbg_i = 0;
	for (auto it = atoms.rbegin(); it != atoms.rend(); --it) {
		it().UninitializeWithExt();
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

LoopRef Loop::Clone() const {
	LoopRef ent = GetPool().Clone(*this);
	ent->InitializeAtoms();
	return ent;
}

void Loop::Destroy() {
	Destroyable::Destroy();
	
	for (auto& component : atoms.GetValues()) {
		component->Destroy();
	}
}

void Loop::SetEnabled(bool enable) {
	Enableable::SetEnabled(enable);
	
	for (auto& component : atoms.GetValues()) {
		component->SetEnabled(enable);
	}
}

Machine& Loop::GetMachine() {
	return GetPool().GetMachine();
}

const Machine& Loop::GetMachine() const {
	return GetPool().GetMachine();
}

Pool& Loop::GetPool() const {
	Pool* p = RefScopeParent<LoopParent>::GetParent().o;
	ASSERT(p);
	return *p;
}

void Loop::VisitSinks(RuntimeVisitor& vis) {
	for(AtomBaseRef& c : atoms)
		c->VisitSink(vis);
}

void Loop::VisitSources(RuntimeVisitor& vis){
	for(AtomBaseRef& c : atoms)
		c->VisitSource(vis);
}

int Loop::GetPoolDepth() const {
	int d = 0;
	Pool* p = &GetPool();
	while (1) {
		p = p->GetParent();
		if (!p) break;
		++d;
	}
	return d;
}

bool Loop::HasPoolParent(PoolRef pool) const {
	Pool* p = &GetPool();
	while (p) {
		if (p == &*pool)
			return true;
		p = p->GetParent();
	}
	return false;
}






bool LoopHashVisitor::OnEntry(const RTTI& type, TypeCls derived, const char* derived_name, void* mem, LockedScopeRefCounter* ref) {
	if (derived == AsTypeCls<Loop>()) {
		Loop& e = *(Loop*)mem;
		ch.Put(1);
		ch.Put(e.GetId());
	}
	else if (derived == AsTypeCls<Pool>()) {
		Pool& p = *(Pool*)mem;
		ch.Put(2);
		ch.Put(p.GetId());
	}
	return true;
}

NAMESPACE_SERIAL_END
