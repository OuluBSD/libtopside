#include "PlayEditor.h"

#ifdef flagMAIN
using namespace TS;

GUI_APP_MAIN {
	
	TS::PlayEditor e;
	
	if (CommandLine().GetCount() && !e.LoadFile(CommandLine()[0]))
		return;
	
	e.Run();
	
	e.SaveFile();
	
}

#endif
