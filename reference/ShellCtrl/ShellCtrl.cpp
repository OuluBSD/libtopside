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
	
}



NAMESPACE_UPP_END

