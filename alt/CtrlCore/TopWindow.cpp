#include "CtrlCore.h"
#include <ParallelLib/ParallelLib.h>


NAMESPACE_UPP


TopWindow::TopWindow() {
	SetFrameRect(RectC(0,0,320,240));
	CreateGeom2DComponent();
	
}

/*Ctrl* TopWindow::GetCtrl() {
	return this;
}*/

void TopWindow::RunInMachine() {
	Run();
}

void TopWindow::CreateGeom2DComponent() {
	using namespace Ecs;
	using namespace Parallel;
	
	#if 0
	RTLOG("TopWindow::CreateGeom2DComponent");
	Ecs::Engine& eng = GetActiveEngine();
	WindowSystemRef wins = eng.Get<WindowSystem>();
	EntityStoreRef ents = eng.Get<EntityStore>();
	EntityRef e = ents->GetRoot()->Create<Window2D>();
	Ref<Geom2DComponent> cw = e->Get<Geom2DComponent>();
	ASSERT(cw);
	SetTarget(cw);
	
	WindowSystemScreen* active_screen = wins->GetActiveScreen();
	active_screen->AddWindow(*cw);
	
	//UpdateFromTransform2D();
	
	#else
	
	Machine& mach = GetActiveMachine();
	WindowSystemRef wins = mach.Get<WindowSystem>();
	WindowManager& mgr = wins->GetActiveScope();
	mgr.AddInterface(*this);
	
	#endif
}

#if 0
void TopWindow::UpdateFromTransform2D() {
	using namespace Ecs;
	ASSERT(cw);
	if (!cw) return;
	
	EntityRef e = this->cw->GetEntity();
	Ref<Transform2D> tr = e->Find<Transform2D>();
	ASSERT(tr);
	if (!tr) return;
	
	Transform2D& t = *tr;
	Geom2DComponent& cw = *this->cw;
	
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
#endif


END_UPP_NAMESPACE
