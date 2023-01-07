#include "ParallelLib.h"

NAMESPACE_PARALLEL_BEGIN


template <class Dim>
HandleSystemT<Dim>::HandleSystemT(Machine& m) :
	RefScopeEnabler<MetaSystemBase, MetaMachineBase>::SP(m) {
	
}

template <class Dim>
bool HandleSystemT<Dim>::Initialize() {
	
	return true;
}

template <class Dim>
void HandleSystemT<Dim>::Start() {
	
}

template <class Dim>
void HandleSystemT<Dim>::Update(double dt) {
	TODO
}

template <class Dim>
void HandleSystemT<Dim>::Stop() {
	
}

template <class Dim>
void HandleSystemT<Dim>::Uninitialize() {
	
}

template <class Dim>
void HandleSystemT<Dim>::RealizeScope() {
	if (scopes.IsEmpty()) {
		Scope& s = scopes.Add();
		active_scope = 0;
	}
}

template <class Dim>
ScopeT<Dim>& HandleSystemT<Dim>::GetActiveScope() {
	RealizeScope();
	
	if (active_scope < 0 || active_scope >= scopes.GetCount())
		active_scope = 0;
	return scopes[active_scope];
}


HANDLETYPE_EXCPLICIT_INITIALIZE_CLASS(HandleSystemT)


NAMESPACE_PARALLEL_END
