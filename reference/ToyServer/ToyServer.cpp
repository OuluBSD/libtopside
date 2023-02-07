#include <ToyHub/ToyHub.h>

#if IS_TS_CORE
	#error ToyServer requires Skylark currently, which depends on U++ Core.
#endif


using namespace UPP;
using namespace TS::ToyHub;

// Local server URL: 127.0.0.1:8001
CONSOLE_APP_MAIN
{
#ifdef _DEBUG
	StdLogSetup(LOG_FILE|LOG_COUT);
	Ini::skylark_log = true;
#endif
	
	RunToyHub();
}

