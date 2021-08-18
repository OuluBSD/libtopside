#include "SerialCore.h"

NAMESPACE_SERIAL_BEGIN


void AtomStore::Clone(Main& dst, const Main& src) {
	const AtomMap& src_comps = src.GetAtoms();
	AtomMap& dst_comps = dst.GetAtoms();
	
	AtomMap::Iterator iter = const_cast<AtomMap&>(src_comps).begin();
	for (; iter; ++iter) {
		TypeAtomCls comp_type = iter.key();
		TypeAtomCls cls; TODO
		
		Base* new_atom = CreateAtom(cls);
		dst.InitializeAtom(*new_atom);
		iter.value().CopyTo(new_atom);
		dst_comps.AtomMapBase::Add(comp_type, new_atom);
	}
}

void AtomStore::ReturnAtom(Base* c) {
	ASSERT(c);
	TypeAtomCls type = c->GetType();
	
	auto iter = SerialFactory::refurbishers.Find(type.side);
	if (iter)
		iter.Get()(c);
}

AtomBase* AtomStore::CreateAtom(TypeAtomCls cls) {
	auto iter = SerialFactory::producers.Find(cls.side);
	ASSERT_(iter, "Invalid to create non-existant atom");
	
	AtomBase* obj = iter.value()();
	obj->SetType(cls);
	return obj;
}

AtomBase* AtomStore::CreateAtomTypeCls(TypeAtomCls cls) {
	auto it = Factory::producers.Find(cls.side);
	if (!it) {
		auto new_fn = Serial::Factory::AtomDataMap().Get(cls).new_fn;
		std::function<AtomBase*()> p([new_fn] { return new_fn();});
		std::function<void(AtomBase*)> r([] (Base* b){ delete b;});
		Factory::producers.Add(cls.side) = p;
		Factory::refurbishers.Add(cls.side) = r;
	}
	
	return CreateAtom(cls);
}


NAMESPACE_SERIAL_END
