#include "Internal.h"


NAMESPACE_UPP


AbsoluteWindow::AbsoluteWindow() : id(-1) {
	
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

