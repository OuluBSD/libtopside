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
	
	//simple_shader.Load(FindLocalFile("shaders" DIR_SEPS "model_loading.vs"), FindLocalFile("shaders" DIR_SEPS "model_loading.fs"));
	
	/*Ref<DisplaySystem> rend = GetEngine().TryGet<DisplaySystem>();
	if (!rend) {
		LOG("WindowSystem::Initialize: error: couldn't find RenderingSystem");
		return false;
	}
	SetDesktopSize(rend->GetVirtualScreenSize());*/
	
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
	
	/*ASSERT(VirtualGui3DPtr);
	if (VirtualGui3DPtr)
		VirtualGui3DPtr->Render(closed);*/
}

void WindowSystem::Stop() {
	::UPP::Ctrl::CloseTopCtrls();
}

void WindowSystem::Uninitialize() {
	
	//Close();
	
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
	TODO
}

void WindowSystemScreen::CloseWindow(CoreWindow& cw) {
	TODO
	/*EntityRef ent = GetPool()->FindEntity<CoreWindow>(&cw);
	if (ent) {
		ent->Destroy();
	}*/
}


NAMESPACE_ECS_END

#endif
