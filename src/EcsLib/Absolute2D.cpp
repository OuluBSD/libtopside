#include "EcsLib.h"


NAMESPACE_UPP


Absolute2D::Absolute2D() : id(-1) {
	
}

void Absolute2D::Init(TS::Ecs::Geom2DComponent* cw, int id) {
	this->cw = cw;
	this->id = id;
	
	TODO
	#if 0
	TS::Ecs::Windows* wins = GetWindows();
	TS::Ecs::WindowManager* wm = GetWindowManager();
	String title = GetTitle();
	if (title.IsEmpty())
		title = wins->GetTitle(id);
	else
		wins->SetTitle(id, title);
	#endif
}

TS::Ecs::WindowManager* Absolute2D::GetWindowManager() const {
	auto* win = GetWindow();
	ASSERT(win);
	if (!win) return 0;
	
	TODO
	#if 0
	auto* wins = win->GetWindows();
	ASSERT(wins);
	if (!wins) return 0;
	
	TS::Ecs::WindowManager* wm = wins->GetWindowManager();
	ASSERT(wm);
	return wm;
	#endif
}

void Absolute2D::Title(const String& title) {
	TODO
	#if 0
	TS::Ecs::Windows* wins = GetWindows();
	ASSERT(wins);
	if (wins)
		wins->SetTitle(id, title);
	#endif
}

int Absolute2D::Run(bool appmodal) {
	DebugMainLoop();
	return 0;
}

Absolute2DInterface& Absolute2D::Sizeable(bool b) {
	TODO
}

Absolute2DInterface& Absolute2D::MaximizeBox(bool b) {
	TODO
}

Absolute2DInterface& Absolute2D::MinimizeBox(bool b) {
	TODO
}

String Absolute2D::GetTitle() const {
	TODO
}

TS::Ecs::Windows* Absolute2D::GetWindows() {
	return cw ? cw->GetWindows() : 0;
}

Image Absolute2D::DefaultCursor() {
	LOG("TODO Absolute2D::DefaultCursor");
	return Image();
}

Image Absolute2D::OverrideCursor(const Image& m) {
	LOG("TODO Absolute2D::OverrideCursor");
	return Image();
}

Ecs::Geom2DComponent* Absolute2D::GetWindow() {
	return cw;
}


END_UPP_NAMESPACE
