#include "EcsLib.h"
#include <EcsLocal/EcsLocal.h>


NAMESPACE_ECS_BEGIN


#ifdef flagGUI

DefaultGuiAppComponent::DefaultGuiAppComponent() {
	prev_mouse = Point(0,0);
	
}

void DefaultGuiAppComponent::Visit(RuntimeVisitor& vis) {
	vis.VisitThis<ComponentT>(this);
	/*if (test) vis % *test;*/
	
	//vis & wins;
	//vis & cw;
	
	vis & trans;
	vis & trans2;
}

void DefaultGuiAppComponent::Etherize(Ether& e) {
	e % prev_mouse;
	
	EtherizeRef(e, cw);
	EtherizeRef(e, trans);
	EtherizeRef(e, trans2);
}

void DefaultGuiAppComponent::Initialize() {
	AddToUpdateList();
	Serial::HandleVideoBase::AddBinder(this);
	Serial::EventStateBase::AddBinder(this);
	
	cw = GetEntity()->Find<Geom2DComponent>();
	trans2 = GetEntity()->Find<Transform2D>();
}

void DefaultGuiAppComponent::Uninitialize() {
	//wins.Clear();
	cw.Clear();
	trans.Clear();
	trans2.Clear();
	
	RemoveFromUpdateList();
	Serial::HandleVideoBase::RemoveBinder(this);
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
	TODO
	#if 0
	if (cw && trans2) {
		Ctrl* ctrl = cw->GetWindowCtrl();
		if (!ctrl)
			return;
		Point cw_pos(trans2->position[0], trans2->position[1]);
		Point win_pt = e.pt - cw_pos;
		if (e.type == EVENT_WINDOW_RESIZE) {
			
		}
		else if (e.type == EVENT_MOUSEMOVE) {
			ctrl->DeepMouseMove(e.pt, e.value);
		}
		else if (e.type == EVENT_MOUSEWHEEL) {
			ctrl->DeepMouseWheel(e.pt, e.n, e.value);
		}
		else if (e.type == EVENT_KEYDOWN || e.type == EVENT_KEYUP) {
			ctrl->DeepKey(e.value, e.n);
		}
		else if (e.type == EVENT_MOUSE_EVENT) {
			ctrl->DeepMouse(e.n, e.pt, e.value);
		}
		else {
			LOG("TODO DefaultGuiAppComponent::Dispatch " << e.ToString());
		}
	}
	#endif
}

bool DefaultGuiAppComponent::Render(Draw& d) {
	ASSERT_(0, "DefaultGuiAppComponent cannot be used with draw (yet)");
	return false;
}

bool DefaultGuiAppComponent::RenderProg(DrawCommand*& begin, DrawCommand*& end) {
	TODO
	#if 0
	Ctrl* ctrl = cw->GetWindowCtrl();
	begin = &ctrl->GetCommandBegin();
	end = &ctrl->GetCommandEnd();
	
	return begin != NULL;
	#endif
}

void DefaultGuiAppComponent::DrawObj(GfxStateDraw& fb, bool use_texture) {
	
	TODO
}

bool DefaultGuiAppComponent::Arg(const String& key, const String& value) {
	
	return true;
}

#endif


NAMESPACE_ECS_END
