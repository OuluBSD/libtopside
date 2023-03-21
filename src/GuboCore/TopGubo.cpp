#include "GuboCore.h"
#include <GuboCore/GuboCore.h>


NAMESPACE_TOPSIDE_BEGIN


TopGubo::TopGubo() {
	SetFrameBox(CubfC(0,0,0,320,240,240));
	CreateGeom3DComponent();
	
}

void TopGubo::FocusEvent() {
	
	TODO
	
}


/*Surface* TopGubo::GetSurface() {
	return this;
}*/

void TopGubo::RunInMachine() {
	Run();
}

int TopGubo::Run() {
	TODO
}

void TopGubo::UpdateFromTransform3D() {
	TODO
	#if 0
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
	#endif
}

void TopGubo::OpenMain() {
	
}

NAMESPACE_TOPSIDE_END

