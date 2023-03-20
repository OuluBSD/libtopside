#include "GuboCore.h"


NAMESPACE_TOPSIDE_BEGIN


TopSurface::TopSurface() {
	SetFrameRect(RectC(0,0,320,240));
	CreateGeom2DComponent();
	
}

/*Surface* TopSurface::GetSurface() {
	return this;
}*/

void TopSurface::OpenMain() {
	CreateGeom2DComponent();
}

void TopSurface::Run() {
	TODO
}

void TopSurface::RunInMachine() {
	Run();
}

void TopSurface::FocusEvent() {
	TODO
}

#if 0
void TopSurface::UpdateFromTransform2D() {
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


NAMESPACE_TOPSIDE_END
