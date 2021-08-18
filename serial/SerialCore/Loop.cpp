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

Loop* Loop::GetParent() const {
	return RefScopeParent<LoopParent>::GetParent().b;
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

LoopRef Loop::Clone() const {
	LoopRef l = CreateEmpty();
	l->AppendCopy(*this);
	GetMachine().Get<LoopStore>()->Clone(*l, *this);
	return l;
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

LoopRef Loop::CreateEmpty() const {
	TODO
	/*Entity& e = objects.Add();
	e.SetParent(this);
	e.SetId(GetNextId());
	Initialize(e);
	return e;*/
}

void Loop::Clear() {
	// useless ClearInterfacesDeep();
	/*UnrefDeep();
	UnlinkDeep();
	UninitializeComponentsDeep();
	ClearComponentsDeep();
	ClearDeep();*/
	TODO
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
