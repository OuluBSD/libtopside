#include "ParallelCore.h"


NAMESPACE_PARALLEL_BEGIN

// incomplete Script::Plan dtor in header
AtomBase::CustomerData::CustomerData() : cfg(gen) {}
AtomBase::CustomerData::~CustomerData() {}


AtomBase::AtomBase() {
	DBG_CONSTRUCT
}

AtomBase::~AtomBase() {
	DBG_DESTRUCT
}

Machine& AtomBase::GetMachine() {
	return GetParent().GetMachine();
}

void AtomBase::UninitializeDeep() {
	Uninitialize();
	ClearSinkSource();
	UninitializeAtom();
}

SpaceRef AtomBase::GetSpace() {
	return GetParent().AsRefT();
}

Space& AtomBase::GetParent() {
	return *((SP*)this)->GetParent().AsStatic<Space>();
}

String AtomBase::ToString() const {
	return GetDynamicName();
}

void AtomBase::SetInterface(const IfaceConnTuple& iface) {
	this->iface = iface;
}

const IfaceConnTuple& AtomBase::GetInterface() const {
	return iface;
}

void AtomBase::AddAtomToUpdateList() {
	AtomBase::GetMachine().template Get<AtomSystem>()->AddUpdated(AtomBase::AsRefT());
}

void AtomBase::RemoveAtomFromUpdateList() {
	AtomBase::GetMachine().template Get<AtomSystem>()->RemoveUpdated(AtomBase::AsRefT());
}








void AtomMap::Dump() {
	auto iter = AtomMapBase::begin();
	for(int i = 0; iter; ++iter, ++i) {
		LOG(i << ": " <<
			iter.value().GetDynamicName() << ": \"" <<
			iter.value().ToString() << "\"");
	}
}

void AtomMap::ReturnAtom(AtomStore& s, AtomBase* c) {
	s.ReturnAtom(c);
}




NAMESPACE_PARALLEL_END

