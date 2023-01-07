#include "ParallelLib.h"

NAMESPACE_PARALLEL_BEGIN


template <class Dim>
ScopeT<Dim>::ScopeT() {
	
}

template <class Dim>
bool ScopeT<Dim>::Init() {
	TODO
}

template <class Dim>
void ScopeT<Dim>::AddInterface(InterfaceProxy& iface) {
	Handle& h = handles.Add();
	h.SetInterface(iface);
}

template <class Dim>
bool ScopeT<Dim>::Poll(typename Dim::Event& e) {
	TODO
}

template <class Dim>
void ScopeT<Dim>::Render() {
	TODO
}

template <class Dim>
void ScopeT<Dim>::Shutdown() {
	TODO
}

template <class Dim>
bool ScopeT<Dim>::ProcessCloseQueue() {
	TODO
}


HANDLETYPE_EXCPLICIT_INITIALIZE_CLASS(ScopeT)


NAMESPACE_PARALLEL_END
