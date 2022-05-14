#include <EcsLocal/EcsLocal.h>


NAMESPACE_UPP


TopWindow::TopWindow() : id(-1) {
	using namespace Ecs;
	Engine& eng = GetActiveEngine();
	
	EntityStoreRef ents = eng.Get<EntityStore>();
	EntityRef e = ents->GetRoot()->Create<Window2D>();
	Ref<CoreWindow> win = e->Get<CoreWindow>();
	ASSERT(win);
	win->tw = this;
	
}

void TopWindow::Init(TS::Ecs::CoreWindow* cw, int id) {
	this->cw = cw;
	this->id = id;
	
	if (title.IsEmpty())
		title = wm->GetTitle(id);
	else
		wm->SetTitle(id, title);
}

void TopWindow::Title(const String& title) {
	this->title = title;
	if (wm)
		wm->SetTitle(id, title);
}

void TopWindow::SetFrameRect(const Rect& r) {
	Ctrl::SetFrameRect(r);
	cw->SetFrameRect(r);
}

int TopWindow::Run(bool appmodal) {
	DebugMainLoop();
	return 0;
}

TopWindow& TopWindow::Sizeable(bool b) {
	TODO
}

TopWindow& TopWindow::MaximizeBox(bool b) {
	TODO
}

TopWindow& TopWindow::MinimizeBox(bool b) {
	TODO
}


END_UPP_NAMESPACE
