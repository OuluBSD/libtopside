#include "EcsVirtualGui.h"

NAMESPACE_ECS_BEGIN
using namespace TS;


#if 0
void VirtualGui::Render(bool do_render) {
	if (ents.IsEmpty())
		ents = rend->GetEngine().Get<EntityStore>();
	
	PoolRef root = ents->GetRoot();
	Vector<RTuple<EntityRef, Transform2DRef, CoreWindowRef>> wins = root->GetComponentsWithEntity<Transform2D, CoreWindow>();
	
	for(int i = 0; i < wins.GetCount(); i++) {
		RTuple<EntityRef, Transform2DRef, CoreWindowRef>& tuple = wins[i];
		Transform2D& t = *tuple.b.a;
		CoreWindow& cw = *tuple.b.b.a;
		
		if (cw.GetId() < 0)
			windows->AddWindow(cw);
		
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
			cw.SetGeomRect(r);
		}
		
		if (cw.IsPendingLayout()) {
			cw.DeepLayout();
			cw.SetPendingEffectRedraw();
		}
		
		do_render = cw.Redraw(true) || do_render;
	}
	
	Vector<RTuple<EntityRef, TransformRef, RenderableRef>> rends = root->GetComponentsWithEntity<Transform, Renderable>();
	if (rends.GetCount())
		do_render = true;
	
	if (do_render) {
		RenderFrame();
	}
	
}
#endif

void VirtualGui::RenderFrame() {
	TODO
	
	
}




void VirtualGui::RenderWindows() {
	
	glDisable(GL_DEPTH_TEST);
	
	Transform& t = *cam->Get<Transform>();
	Viewable& c = *cam->Get<Viewable>();
	
	TODO
}















NAMESPACE_ECS_END
