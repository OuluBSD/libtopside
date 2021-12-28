#include "Physics.h"

NAMESPACE_TOPSIDE_BEGIN


template <class Fys>
typename Fys::System* NodeT<Fys>::GetSystem() {
	NodeT* n = this;
	while (n->owner)
		n = n->owner;
	return CastPtr<System>(n);
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
typename Fys::NativeWorld& NodeT<Fys>::GetWorld() {
	return GetSystem()->GetWorld();
}

template <class Fys>
typename Fys::NativeSpace& NodeT<Fys>::GetWorldSpace() {
	return GetSystem()->GetSpace();
}


FYS_EXCPLICIT_INITIALIZE_CLASS(NodeT)

NAMESPACE_TOPSIDE_END
