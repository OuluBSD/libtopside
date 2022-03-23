#include "Internal.h"

NAMESPACE_PARALLEL_BEGIN

#if 0
void AtomStore::Clone(Main& dst, const Main& src) {
	const AtomMap& src_comps = src.GetAtoms();
	AtomMap& dst_comps = dst.GetAtoms();
	
	AtomMap::Iterator iter = const_cast<AtomMap&>(src_comps).begin();
	for (; iter; ++iter) {
		AtomTypeCls comp_type = iter.key();
		AtomTypeCls cls; TODO
		
		Base* new_atom = CreateAtom(cls);
		dst.InitializeAtom(*new_atom);
		iter.value().CopyTo(new_atom);
		dst_comps.AtomMapBase::Add(comp_type, new_atom);
	}
}
#endif

void AtomStore::ReturnAtom(Base* c) {
	ASSERT(c);
	AtomTypeCls type = c->GetType();
	
	auto iter = AtomFactory::refurbishers.Find(type);
	if (iter)
		iter.Get()(c);
}

AtomBase* AtomStore::CreateAtom(AtomTypeCls cls) {
	auto iter = AtomFactory::producers.Find(cls);
	ASSERT_(iter, "Invalid to create non-existant atom");
	
	AtomBase* obj = iter.value()();
	//obj->SetType(cls);
	return obj;
}

AtomBase* AtomStore::CreateAtomTypeCls(AtomTypeCls cls) {
	auto it = Factory::producers.Find(cls);
	if (!it) {
		auto new_fn = Serial::Factory::AtomDataMap().Get(cls).new_fn;
		std::function<AtomBase*()> p([new_fn] { return new_fn();});
		std::function<void(AtomBase*)> r([] (Base* b){ delete b;});
		Factory::producers.Add(cls) = p;
		Factory::refurbishers.Add(cls) = r;
	}
	
	return CreateAtom(cls);
}


NAMESPACE_PARALLEL_END
