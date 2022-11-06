#include "EcsLib.h"
#include <EcsLocal/EcsLocal.h>
#include <EcsVirtualGui/EcsVirtualGui.h>

NAMESPACE_ECS_BEGIN


#ifdef flagGUI

DefaultGuiAppComponent::DefaultGuiAppComponent() {
	prev_mouse = Point(0,0);
	
}

void DefaultGuiAppComponent::Visit(RuntimeVisitor& vis) {
	/*if (test) vis % *test;*/
	vis & wins & cw;
}

void DefaultGuiAppComponent::Initialize() {
	AddToUpdateList();
	Serial::EcsVideoBase::AddBinder(this);
	Serial::EventStateBase::AddBinder(this);
	
	cw = GetEntity()->Find<CoreWindow>();
	trans2 = GetEntity()->Find<Transform2D>();
}

void DefaultGuiAppComponent::Uninitialize() {
	RemoveFromUpdateList();
	Serial::EcsVideoBase::RemoveBinder(this);
	Serial::EventStateBase::RemoveBinder(this);
}

void DefaultGuiAppComponent::Update(double dt) {
	
}

void DefaultGuiAppComponent::StateStartup(GfxDataState& state) {
	Engine& eng = GetActiveEngine();
	EntityStoreRef ents = eng.Get<EntityStore>();
	RenderingSystemRef rend = eng.Get<RenderingSystem>();
	PoolRef models = ents->GetRoot()->GetAddPool("models");
	
	TODO
}

void DefaultGuiAppComponent::Dispatch(const CtrlEvent& e) {
	if (cw && trans2) {
		Point cw_pos(trans2->position[0], trans2->position[1]);
		Point win_pt = e.pt - cw_pos;
		if (e.type == EVENT_WINDOW_RESIZE) {
			
		}
		else if (e.type == EVENT_MOUSEMOVE) {
			cw->DeepMouseMove(e.pt, e.value);
		}
		else if (e.type == EVENT_MOUSEWHEEL) {
			cw->DeepMouseWheel(e.pt, e.n, e.value);
		}
		else if (e.type == EVENT_KEYDOWN || e.type == EVENT_KEYUP) {
			cw->DeepKey(e.value, e.n);
		}
		else if (e.type == EVENT_MOUSE_EVENT) {
			cw->DeepMouse(e.n, e.pt, e.value);
		}
		else {
			LOG("TODO DefaultGuiAppComponent::Dispatch " << e.ToString());
		}
	}
}

bool DefaultGuiAppComponent::Render(Draw& d) {
	
	ProgDraw* pd = CastPtr<ProgDraw>(&d);
	ASSERT(pd);
	if (!pd) {
		return false;
	}
	
	return true;
	
}

void DefaultGuiAppComponent::DrawObj(GfxStateDraw& fb, bool use_texture) {
	
	TODO
}

bool DefaultGuiAppComponent::Arg(const String& key, const String& value) {
	
	return true;
}

#endif


NAMESPACE_ECS_END
