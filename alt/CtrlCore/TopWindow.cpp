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

int TopWindow::Run() {
	TODO
}

#if 0
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
	
	TODO // follow upp TopWindow better
	
	/*Machine& mach = GetActiveMachine();
	WindowSystemRef wins = mach.Get<WindowSystem>();
	WindowManager& mgr = wins->GetActiveScope();
	mgr.AddInterface(*this);*/
	
	#endif
}
#endif
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

TopWindow& TopWindow::Title(const WString& _title)
{
	if(title != _title) {
		title = _title;
		SyncTitle();
	}
	return *this;
}

TopWindow& TopWindow::Title(const char *s)
{
	return Title(String(s).ToWString());
}

TopWindow& TopWindow::Icon(const Image& m)
{
	if(!icon.IsSame(m)) {
		icon = m;
		SyncCaption();
	}
	return *this;
}

void TopWindow::ShutdownWindows()
{
	bool again = true;
	while(again) {
		Vector<Ctrl *> tc = GetTopCtrls();
		again = false;
		for(int i = 0; i < tc.GetCount(); i++) {
			TopWindow* w = CastPtr<TopWindow>(tc[i]);
			if(w && w->IsOpen() && w->IsEnabled()) {
				again = true;
				w->SetForeground();
				TODO
				/*w->ShutdownWindow();
				if(w && w->IsOpen())
					w->WhenClose();
				if(!w || !w->IsOpen())
					break;*/
			}
		}
	}
}


END_UPP_NAMESPACE
