#include <EcsLocal/EcsLocal.h>


NAMESPACE_UPP


TopWindow::TopWindow() : id(-1) {
	
	CreateCoreWindow();
	
	
}

void TopWindow::CreateCoreWindow() {
	using namespace Ecs;
	
	Windows* windows = Ctrl::GetWindows();
	ASSERT(windows);
	if (!windows)
		return;
	
	RTLOG("TopWindow::CreateCoreWindow");
	Engine& eng = GetActiveEngine();
	EntityStoreRef ents = eng.Get<EntityStore>();
	EntityRef e = ents->GetRoot()->Create<Window2D>();
	Ref<CoreWindow> cw = e->Get<CoreWindow>();
	ASSERT(cw);
	cw->tw = this;
	
	this->cw = &*cw;
	
	windows->AddWindow(*cw);
	
	UpdateFromTransform2D();
	
}

void TopWindow::UpdateFromTransform2D() {
	using namespace Ecs;
	ASSERT(cw);
	if (!cw) return;
	
	EntityRef e = this->cw->GetEntity();
	Ref<Transform2D> tr = e->Find<Transform2D>();
	ASSERT(tr);
	if (!tr) return;
	
	Transform2D& t = *tr;
	CoreWindow& cw = *this->cw;
	
	Rect r = cw.GetFrameRect();
	Size t_size = ToSize(t.size);
	Point t_pos = ToPoint(t.position);
	if (r.Width()  != t_size.cx ||
		r.Height() != t_size.cy ||
		r.left     != t_pos.x ||
		r.top      != t_pos.y) {
		r.left = t_pos.x;
		r.top = t_pos.y;
		r.right = r.left + t_size.cx;
		r.bottom = r.top + t_size.cy;
		cw.SetFrameRect0(r);
	}
	
	if (cw.IsPendingLayout()) {
		cw.DeepLayout();
		cw.SetPendingEffectRedraw();
	}
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
