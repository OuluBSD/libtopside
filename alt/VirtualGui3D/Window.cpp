#include "Internal.h"


NAMESPACE_UPP


AbsoluteWindow::AbsoluteWindow() : id(-1) {
	
	
	CreateCoreWindow();
	
	
}

void AbsoluteWindow::CreateCoreWindow() {
	using namespace Ecs;
	
	Windows* windows = this->GetWindows();
	ASSERT(windows);
	if (!windows)
		return;
	
	RTLOG("AbsoluteWindow::CreateCoreWindow");
	Engine& eng = GetActiveEngine();
	EntityStoreRef ents = eng.Get<EntityStore>();
	EntityRef e = ents->GetRoot()->Create<Window2D>();
	Ref<CoreWindow> cw = e->Get<CoreWindow>();
	ASSERT(cw);
	cw->aw = this;
	
	this->cw = &*cw;
	
	windows->AddWindow(*cw);
	
	UpdateFromTransform2D();
	
}

void AbsoluteWindow::UpdateFromTransform2D() {
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
		cw.SetGeomRect(r);
	}
	
	if (cw.IsPendingLayout()) {
		cw.DeepLayout();
		cw.SetPendingEffectRedraw();
	}
}

void AbsoluteWindow::Init(TS::Ecs::CoreWindow* cw, int id) {
	this->cw = cw;
	this->id = id;
	
	TS::Ecs::Windows* wins = GetWindows();
	TS::Ecs::WindowManager* wm = GetWindowManager();
	String title = GetTitle();
	if (title.IsEmpty())
		title = wins->GetTitle(id);
	else
		wins->SetTitle(id, title);
}

TS::Ecs::WindowManager* AbsoluteWindow::GetWindowManager() const {
	auto* win = GetWindow();
	ASSERT(win);
	if (!win) return 0;
	
	auto* wins = win->GetWindows();
	ASSERT(wins);
	if (!wins) return 0;
	
	TS::Ecs::WindowManager* wm = wins->GetWindowManager();
	ASSERT(wm);
	return wm;
}

void AbsoluteWindow::Title(const String& title) {
	TS::Ecs::Windows* wins = GetWindows();
	ASSERT(wins);
	if (wins)
		wins->SetTitle(id, title);
}

int AbsoluteWindow::Run(bool appmodal) {
	DebugMainLoop();
	return 0;
}

AbsoluteWindowInterface& AbsoluteWindow::Sizeable(bool b) {
	TODO
}

AbsoluteWindowInterface& AbsoluteWindow::MaximizeBox(bool b) {
	TODO
}

AbsoluteWindowInterface& AbsoluteWindow::MinimizeBox(bool b) {
	TODO
}

String AbsoluteWindow::GetTitle() const {
	TODO
}

TS::Ecs::Windows* AbsoluteWindow::GetWindows() {
	return cw ? cw->GetWindows() : 0;
}

Image AbsoluteWindow::DefaultCursor() {
	LOG("TODO AbsoluteWindow::DefaultCursor");
	return Image();
}

Image AbsoluteWindow::OverrideCursor(const Image& m) {
	LOG("TODO AbsoluteWindow::OverrideCursor");
	return Image();
}

Ecs::CoreWindow* AbsoluteWindow::GetWindow() {
	return cw;
}


END_UPP_NAMESPACE

