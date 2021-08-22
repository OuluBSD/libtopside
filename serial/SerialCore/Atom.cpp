#include "SerialCore.h"

NAMESPACE_SERIAL_BEGIN


AtomBase::AtomBase() {
	DBG_CONSTRUCT
}

AtomBase::~AtomBase() {
	DBG_DESTRUCT
}

Machine& AtomBase::GetMachine() {
	return GetParent()->GetMachine();
}

void AtomBase::UninitializeWithExt() {
	ClearExtension();
	Uninitialize();
	ClearSinkSource();
}

LoopRef AtomBase::GetLoop() {
	return GetParent()->AsRefT();
}

String AtomBase::ToString() const {
	return GetDynamicName();
}

AtomBaseRef AtomBase::SetAtomTypeCls(TypeAtomCls ext) {
	TypeAtomCls atom = GetType();
	const auto& cd = Serial::Factory::AtomDataMap().Get(atom);
	TODO
	#if 0
	for (const auto& e : cd.ext.GetValues()) {
		if (e.cls == ext) {
			AtomBase* b = e.new_fn();
			if (SetExtension(b))
				return GetExtension();
			break;
		}
	}
	#endif
	return AtomBaseRef();
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




NAMESPACE_SERIAL_END
