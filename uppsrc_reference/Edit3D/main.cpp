#include "Edit3D.h"

#ifdef flagMAIN

GUI_APP_MAIN {
	using namespace TS;
	using namespace UPP;
	Edit3D app;
	
	const auto& c = CommandLine();
	if (!c.IsEmpty() && DirectoryExists(c[0]))
		app.LoadWmrStereoPointcloud(c[0]);
	else
		app.LoadTestProject(0);
	
	app.Run();
	
	
}

#endif
