#include "Animator.h"

NAMESPACE_TOPSIDE_BEGIN


EditorDraw::EditorDraw() {
	
}
	
void EditorDraw::Paint(Draw& d) {
	Size sz = GetSize();
	ImageDraw id(sz);
	id.DrawRect(sz, White());
	
	
	proj->ctx.p.Paint(d);
	
	
	Image img;
	d.DrawImage(0,0,img);
}

void EditorDraw::SetProject(Project& p) {
	proj = &p;
}


NAMESPACE_TOPSIDE_END
