#include "ShellCtrl.h"

#ifdef flagMAIN
using namespace Upp;

class TestApp : public TopWindow {
	ShellCtrl sc;
	
public:
	typedef TestApp CLASSNAME;
	TestApp() {
		Title("TestApp");
		Add(sc.SizePos());
		sc.Start();
	}
	
};

GUI_APP_MAIN
{
	TestApp app;
	app.Run();
}

#endif
