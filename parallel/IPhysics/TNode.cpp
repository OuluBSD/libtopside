#include "IPhysics.h"

NAMESPACE_PARALLEL_BEGIN


template <class Fys>
typename Fys::System* NodeT<Fys>::GetSystem() {
	NodeT* n = this;
	while (n->owner)
		n = n->owner;
	return CastPtr<System>(n);
}

template <class Fys>
SystemT<Fys>* NodeT<Fys>::GetSystemT() {
	NodeT* n = this;
	while (n->owner)
		n = n->owner;
	return CastPtr<SystemT>(n);
}

template <class Fys>
typename Fys::Space* NodeT<Fys>::GetSpace() {
	NodeT* n = this;
	while (n) {
		Space* s = CastPtr<Space>(n);
		if (s)
			return s;
		n = n->owner;
	}
	return NULL;
}

template <class Fys>
typename Fys::NativeWorld& NodeT<Fys>::GetNativeWorld() {
	auto sys = GetSystemT();
	ASSERT(sys);
	return sys->GetWorld();
}

template <class Fys>
typename Fys::NativeSpace& NodeT<Fys>::GetNativeWorldSpace(bool dbg_chk) {
	auto sys = GetSystemT();
	ASSERT(sys);
	return sys->GetSpace().GetNative(dbg_chk);
}


FYS_EXCPLICIT_INITIALIZE_CLASS(NodeT)

NAMESPACE_PARALLEL_END
