#include "Animator.h"

NAMESPACE_TOPSIDE_BEGIN


EditorApp::EditorApp() {
	Title("Editor App");
	Sizeable().MaximizeBox().MinimizeBox();
	
	Rect r = GetRect();
	SetRect(RectC(r.left, r.top, 512, 512));
	
	Add(draw.SizePos());
	
	tc.Set(-1, THISBACK(ProcessScript));
	
	draw.SetProject(proj);
}

void EditorApp::ProcessScript() {
	proj.Update();
	draw.Refresh();
}


NAMESPACE_TOPSIDE_END
