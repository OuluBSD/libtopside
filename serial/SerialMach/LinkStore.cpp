#include "SerialMach.h"

NAMESPACE_SERIAL_BEGIN


#if 0
void LinkStore::Clone(Main& dst, const Main& src) {
	const LinkMap& src_comps = src.GetLinks();
	LinkMap& dst_comps = dst.GetLinks();
	
	LinkMap::Iterator iter = const_cast<LinkMap&>(src_comps).begin();
	for (; iter; ++iter) {
		LinkTypeCls comp_type = iter.key();
		LinkTypeCls cls; TODO
		
		Base* new_atom = CreateLink(cls);
		dst.InitializeLink(*new_atom);
		iter.value().CopyTo(new_atom);
		dst_comps.LinkMapBase::Add(comp_type, new_atom);
	}
}
#endif

void LinkStore::ReturnLink(Base* c) {
	ASSERT(c);
	LinkTypeCls type = c->GetLinkType();
	
	auto iter = LinkFactory::refurbishers.Find(type);
	if (iter)
		iter.Get()(c);
}

LinkBase* LinkStore::CreateLink(LinkTypeCls cls) {
	auto iter = LinkFactory::producers.Find(cls);
	ASSERT_(iter, "Invalid to create non-existant atom");
	
	LinkBase* obj = iter.value()();
	//obj->SetType(cls);
	return obj;
}

LinkBase* LinkStore::CreateLinkTypeCls(LinkTypeCls cls) {
	auto it = Factory::producers.Find(cls);
	if (!it) {
		auto new_fn = Serial::Factory::LinkDataMap().Get(cls).new_fn;
		std::function<LinkBase*()> p([new_fn] { return new_fn();});
		std::function<void(LinkBase*)> r([] (Base* b){ delete b;});
		Factory::producers.Add(cls) = p;
		Factory::refurbishers.Add(cls) = r;
	}
	
	return CreateLink(cls);
}


NAMESPACE_SERIAL_END
