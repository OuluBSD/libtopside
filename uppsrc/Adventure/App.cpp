#include "Adventure.h"

namespace Adventure {






ProgramApp::ProgramApp() {
	Title("Program App");
	Sizeable().MaximizeBox().MinimizeBox();
	
	Add(draw.SizePos());
	
	tc.Set(-10, THISBACK(ProcessScript));
	
}

void ProgramApp::ProcessScript() {
	
	
	
	Sleep(1);
}







void ProgramDraw::Paint(Draw& w) {
	Size sz = GetSize();
	
	w.DrawRect(sz, White());
	
	
}

}
