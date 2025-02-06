#include "EmuCtrl.h"

#ifdef flagUSEMALLOC
namespace Upp {
bool NoMemoryLeaksCheck;
}
#endif

GUI_APP_MAIN {
	SetupEmu();
	
	EmuApp app;
	
	app.Start();
	
	CloseEmu();
}
