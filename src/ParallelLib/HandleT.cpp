#include "ParallelLib.h"


NAMESPACE_TOPSIDE_BEGIN

void DebugMainLoop();

NAMESPACE_TOPSIDE_END



NAMESPACE_PARALLEL_BEGIN


template <class Dim>
HandleT<Dim>::HandleT () {
	this->SetDimensions(Dim::GetDefaultHandleDimensions());
	
}

template <class Dim>
typename Dim::TopContainer* HandleT<Dim>::GetTopContainer() {
	TODO
}

template <class Dim>
void HandleT<Dim>::SetInterface(InterfaceProxy& iface) {
	iface.SetTarget(*this);
	// --> GetLinkedProxy()
}

template <class Dim>
void HandleT<Dim>::Title(const String& title) {
	TODO
}

template <class Dim>
typename Dim::Interface& HandleT<Dim>::Sizeable(bool b) {
	TODO
}

template <class Dim>
typename Dim::Interface& HandleT<Dim>::MaximizeBox(bool b) {
	TODO
}

template <class Dim>
typename Dim::Interface& HandleT<Dim>::MinimizeBox(bool b) {
	TODO
}

template <class Dim>
int HandleT<Dim>::Run(bool appmodal) {
	DebugMainLoop();
	return 0;
}

template <class Dim>
String HandleT<Dim>::GetTitle() const {
	TODO
}

template <class Dim>
void HandleT<Dim>::SetPendingPartialRedraw() {
	TODO
}


HANDLETYPE_EXCPLICIT_INITIALIZE_CLASS(HandleT)

NAMESPACE_PARALLEL_END
