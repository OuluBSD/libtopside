#include "ParallelCore.h"

NAMESPACE_PARALLEL_BEGIN



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
		auto new_fn = Parallel::Factory::AtomDataMap().Get(cls).new_fn;
		std::function<AtomBase*()> p([new_fn] { return new_fn();});
		std::function<void(AtomBase*)> r([] (Base* b){ delete b;});
		Factory::producers.Add(cls) = p;
		Factory::refurbishers.Add(cls) = r;
	}
	
	return CreateAtom(cls);
}


NAMESPACE_PARALLEL_END
