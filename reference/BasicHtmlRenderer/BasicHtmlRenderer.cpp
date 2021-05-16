#include <LayoutCtrl/LayoutCtrl.h>
using namespace Upp;


GUI_APP_MAIN {
	Topside::Layout::Client c;
	
	String path;
	const auto& cmds = CommandLine();
	if (cmds.GetCount())
		path = cmds[0];
	else
		path = "file://" + GetDataFile("1.html");
	
	c.SetAddress(path);
	c.Run();
}
