#include <ToyHub/ToyHub.h>

#ifndef UPP_VERSION
	#error ToyServer requires Skylark currently, which depends on U++ Core.
#endif


using namespace Upp;
using namespace Topside::ToyHub;

// Local server URL: 127.0.0.1:8001
CONSOLE_APP_MAIN
{
#ifdef _DEBUG
	StdLogSetup(LOG_FILE|LOG_COUT);
	Ini::skylark_log = true;
#endif
	
	RunToyHub();
}

