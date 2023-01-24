#include "ParallelLib.h"


NAMESPACE_TOPSIDE_BEGIN

void DebugMainLoop();

NAMESPACE_TOPSIDE_END



NAMESPACE_PARALLEL_BEGIN


template <class Dim>
HandleT<Dim>::HandleT() :
	decor(this)
{
	maximized = false;
	id = -1;
	
	this->Add(decor);
	
	this->SetFrameBox(Dim::GetDefaultHandleDimensions());
	
}

template <class Dim>
typename Dim::TopContainer* HandleT<Dim>::GetTopContainer() {
	auto* proxy = this->GetLinkedProxy();
	if (!proxy)
		return 0;
	return CastPtr<typename Dim::TopContainer>(proxy);
}

template <class Dim>
void HandleT<Dim>::SetInterface(InterfaceProxy& iface) {
	iface.SetTarget(*this);
	// --> GetLinkedProxy()
}

template <class Dim>
void HandleT<Dim>::Layout() {
	TODO
}

template <class Dim>
void HandleT<Dim>::Title(const String& title) {
	LOG("TODO");
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
	return title;
}

template <class Dim>
void HandleT<Dim>::SetPendingPartialRedraw() {
	pending_partial_redraw = true;
}

template <class Dim>
GeomInteraction* HandleT<Dim>::GetDynamicallyLinked() const {
	auto* abs_proxy = this->GetLinkedProxy();
	if (abs_proxy)
		return abs_proxy->GetInteraction();
	return 0;
}

template <class Dim>
ScopeT<Dim>& HandleT<Dim>::GetScope() const {
	ScopeT<Dim>* owner = this->GetParent().Get();
	ASSERT(owner);
	return *owner;
}

template <class Dim>
HandleSystemT<Dim>& HandleT<Dim>::GetHandleSystem() const {
	ScopeT<Dim>* owner0 = this->GetParent().Get();
	ASSERT(owner0);
	HandleSystemT<Dim>* owner1 = owner0->GetParent().Get();
	ASSERT(owner1);
	return *owner1;
}

template <class Dim>
void HandleT<Dim>::Close() {
	Scope& scope = GetScope();
	scope.QueueCloseHandle(id);
}

template <class Dim>
void HandleT<Dim>::Maximize() {
	Scope& scope = GetScope();
	scope.FocusHandlePos(id);
	scope.MaximizeHandle(id);
	maximized = true;
}

template <class Dim>
void HandleT<Dim>::Minimize() {
	Scope& scope = GetScope();
	scope.MinimizeHandle(id);
}

template <class Dim>
void HandleT<Dim>::CloseOthers() {
	Scope& scope = GetScope();
	scope.CloseOthers(id);
}

template <class Dim>
void HandleT<Dim>::SetMaximized(bool b) {
	maximized = b;
}

template <class Dim>
bool HandleT<Dim>::IsMaximized() const {
	return maximized;
}

template <class Dim>
void HandleT<Dim>::StoreRect() {
	stored_box = this->GetFrameBox();
}

template <class Dim>
void HandleT<Dim>::LoadRect() {
	ASSERT(stored_box.bottom && stored_box.right);
	SetFrameBox(stored_box);
}

template <class Dim>
void HandleT<Dim>::SetFrameBox(const Box& b) {
	TopContainer* tc = GetTopContainer();
	if (tc)
		tc->SetFrameBox(b);
}

template <class Dim>
bool HandleT<Dim>::IsPendingPartialRedraw() const {
	return pending_partial_redraw;
}















template <class Dim>
GeomDecorationT<Dim>::GeomDecorationT(Handle* h) {
	TODO
}

template <class Dim>
void GeomDecorationT<Dim>::Paint(DrawT& draw) {
	TODO
}

template <class Dim>
void GeomDecorationT<Dim>::LeftDown(Pt p, dword keyflags) {
	TODO
}

template <class Dim>
void GeomDecorationT<Dim>::LeftDouble(Pt p, dword keyflags) {
	TODO
}

template <class Dim>
void GeomDecorationT<Dim>::LeftUp(Pt p, dword keyflags) {
	TODO
}

template <class Dim>
void GeomDecorationT<Dim>::MouseMove(Pt p, dword keyflags) {
	TODO
}

template <class Dim>
void GeomDecorationT<Dim>::RightDown(Pt p, dword keyflags) {
	TODO
}

template <class Dim>
void GeomDecorationT<Dim>::LocalMenu(Bar& bar) {
	TODO
}


HANDLETYPE_EXCPLICIT_INITIALIZE_CLASS(HandleT)
HANDLETYPE_EXCPLICIT_INITIALIZE_CLASS(GeomDecorationT)

NAMESPACE_PARALLEL_END
