#include "EcsLib.h"

#if HAVE_WINDOWSYSTEM


NAMESPACE_OULU_BEGIN




bool WindowSystem::Initialize() {
	Size sz = VirtualGui3DAltPtr->GetSize();
	SetFrameRect0(RectC(0, 0, sz.cx, sz.cy));
	Ctrl::SetContentRect(RectC(0, 0, sz.cx, sz.cy));
	//simple_shader.Load(FindLocalFile("shaders" DIR_SEPS "model_loading.vs"), FindLocalFile("shaders" DIR_SEPS "model_loading.fs"));
	
	Ref<RenderingSystem> rend = GetMachine().TryGet<RenderingSystem>();
	if (!rend) {
		LOG("WindowSystem::Initialize: error: couldn't find RenderingSystem");
		return false;
	}
	SetDesktopSize(rend->GetVirtualScreenSize());
	
	return true;
}

void WindowSystem::Start() {
	
	ents = GetMachine().Get<EntityStore>();
	
}

void WindowSystem::Update(double dt) {
	bool closed = ProcessCloseQueue();
	
	TODO
	//Render(closed);
}

void WindowSystem::Stop() {
	::UPP::Ctrl::CloseTopCtrls();
}

void WindowSystem::Uninitialize() {
	
	//Close();
	
}

void WindowSystem::CloseWindow(CoreWindow& cw) {
	EntityRef ent = GetPool()->FindEntity<CoreWindow>(&cw);
	if (ent) {
		ent->Destroy();
	}
}

void WindowSystem::Invalidate() {
	TODO
}

void WindowSystem::SetDesktopSize(Size sz) {
	TODO
}


NAMESPACE_OULU_END

#endif
