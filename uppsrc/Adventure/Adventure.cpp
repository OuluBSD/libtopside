#include "Adventure.h"

GUI_APP_MAIN {
	using namespace Adventure;
	
	ProgramApp a;
	if (a.Init())
		a.Run();
	
}
