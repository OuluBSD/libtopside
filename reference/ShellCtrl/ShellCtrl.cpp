#include "ShellCtrl.h"


NAMESPACE_UPP_BEGIN


ShellCtrl::ShellCtrl() {
	
}

void ShellCtrl::Start() {
	tc.Set(-1000/30, THISBACK(Update));
}

void ShellCtrl::Stop() {
	tc.Kill();
}

void ShellCtrl::Update() {
	Refresh();
}

void ShellCtrl::Paint(Draw& d) {
	Size sz = GetSize();
	#ifdef flagDEBUG
	d.DrawRect(sz, Color(Random(256), Random(256), Random(256)));
	#else
	d.DrawRect(sz, White());
	#endif
}



NAMESPACE_UPP_END

