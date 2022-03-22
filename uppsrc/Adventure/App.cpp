#include "Adventure.h"

namespace Adventure {






ProgramApp::ProgramApp() {
	Title("Program App");
	Sizeable().MaximizeBox().MinimizeBox();
	
	Rect r = GetRect();
	SetRect(RectC(r.left, r.top, 512, 512));
	
	Add(draw.SizePos());
	
	tc.Set(-1, THISBACK(ProcessScript));
	
	draw.SetProgram(prog);
}

void ProgramApp::ProcessScript() {
	prog.Update();
	draw.Refresh();
}






}
