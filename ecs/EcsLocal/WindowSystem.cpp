#include "EcsLocal.h"

#if HAVE_WINDOWSYSTEM

NAMESPACE_ECS_BEGIN


bool WindowSystem::Initialize() {
	WindowSystemScreen& win = wm.AddScreen<WindowSystemScreen>();
	win.sys = this;
	
	Ctrl::SetWindows(&win);
	
	
	Size sz = VirtualGui3DPtr->GetSize();
	
	win.SetFrameRect0(RectC(0, 0, sz.cx, sz.cy));
	win.Ctrl::SetContentRect(RectC(0, 0, sz.cx, sz.cy));
	
	return true;
}

void WindowSystem::Start() {
	
	ents = GetEngine().Get<EntityStore>();
	
}

void WindowSystem::Update(double dt) {
	bool closed = false;
	
	for (Windows& w : wm.screens) {
		closed = w.ProcessCloseQueue() || closed;
	}
	
}

void WindowSystem::Stop() {
	::UPP::Ctrl::CloseTopCtrls();
}

void WindowSystem::Uninitialize() {
	
}

void WindowSystem::Invalidate() {
	TODO
}

void WindowSystem::SetDesktopSize(Size sz) {
	vdesktop_sz = sz;
}



bool WindowSystemScreen::Init() {
	return true;
}

void WindowSystemScreen::Render() {
	TODO
}

void WindowSystemScreen::Shutdown() {
	CloseAll();
}

void WindowSystemScreen::CloseWindow(CoreWindow& cw) {
	TODO
}


NAMESPACE_ECS_END

#endif
