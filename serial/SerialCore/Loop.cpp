#include "SerialCore.h"


NAMESPACE_SERIAL_BEGIN


Loop::Loop() {
	DBG_CONSTRUCT
}

Loop::~Loop() {
	DBG_DESTRUCT
}

Loop* Loop::GetParent() const {
	return static_cast<Loop*>(RefScopeParent<LoopParent>::GetParentUnsafe().b);
}

/*void Loop::ClearInterfaces() {
	for (auto iter = links.rbegin(); iter; --iter)
		iter()->ClearSinkSource();
}*/

/*void Loop::CopyTo(Loop& l) const {
	l.AppendCopy(*this);
}*/

void Loop::AppendCopy(const Loop& l) {
	TODO
}

/*void Loop::VisitSinks(RuntimeVisitor& vis) {
	for(LinkBaseRef& c : links)
		c->VisitSink(vis);
}

void Loop::VisitSources(RuntimeVisitor& vis){
	for(LinkBaseRef& c : links)
		c->VisitSource(vis);
}*/

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

void Loop::Clear() {
	// useless ClearInterfacesDeep();
	UnrefDeep();
	UnlinkDeep();
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

/*void Loop::ClearAtomsDeep() {
	for (LoopRef& p : loops)
		p->ClearAtomsDeep();
	
	AtomStoreRef sys = GetMachine().Get<AtomStore>();
	for (auto it = links.rbegin(); it != links.rend(); --it) {
		sys->ReturnAtom(links.Detach(it));
	}
	
}*/

void Loop::ClearDeep() {
	for (LoopRef& p : loops)
		p->ClearDeep();
	loops.Clear();
	
	links.Clear();
}

/*LoopRef Loop::GetAddEmpty(String name) {
	LoopRef l = FindLoopByName(name);
	if (l)
		return l;
	l = CreateEmpty();
	l->SetName(name);
	return l;
}*/

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
	
	s << ".." << (name.IsEmpty() ? "unnamed" : "\"" + name + "\"") << "[" << (int)id << "]\n";
	
	for (LinkBaseRef& l : links)
		s << l->ToString();
	
	for (LoopRef& l : loops)
		s << l->GetTreeString(indent+1);
	
	return s;
}

/*bool Loop::MakeLink(AtomBaseRef src_atom, AtomBaseRef dst_atom, ValDevCls iface) {
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
		ExchangePointRef ep = MetaDirectoryBase::Add(expt_type);
		RTLOG("Loop::Link(...): created " << ep->GetDynamicName() << " at " << HexStr(&ep->GetRTTI()));
		src->Link(ep, sink, src_cookie, sink_cookie);
		ep->Init(this);
		ep->Set(src, sink, src_cookie, sink_cookie);
		src_atom->SetPrimarySink(dst_atom);
		dst_atom->SetPrimarySource(src_atom);
		return true;
	}
	return false;
}*/

/*EnvStateRef Loop::FindNearestState(String name) {
	Loop* l = this;
	while (l) {
		EnvStateRef e = l->FindState(name);
		if (e)
			return e;
		l = l->GetParent();
	}
	return EnvStateRef();
}*/

String Loop::GetDeepName() const {
	String s = name;
	Loop* l = GetParent();
	while (l) {
		s = l->name + "." + s;
		l = l->GetParent();
	}
	return s;
}

LoopId Loop::GetNextId() {
	static Atomic next_id;
	return ++next_id;
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
