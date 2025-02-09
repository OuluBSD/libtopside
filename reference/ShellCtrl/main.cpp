#include "ShellCtrl.h"

#ifdef flagMAIN
using namespace Upp;

class TestApp : public TopWindow {
	ShellCtrl sc;
	
public:
	typedef TestApp CLASSNAME;
	TestApp() {
		Title("TestApp");
		Sizeable().MaximizeBox(1).MinimizeBox(1);
		Maximize();
		Add(sc.SizePos());
		sc.Start();
	}
	
};

GUI_APP_MAIN
{
	if (0) {
		TestApp app;
		app.Run();
	}
	else {
		VideoPlayerApp app;
		app.Run();
	}
	SingleMachine::Static().Stop();
}

#endif
