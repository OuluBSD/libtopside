#include "Complete.h"
using namespace UPP;
using namespace TS;


CONSOLE_APP_MAIN {
	SetCoutLog();
	
	Plan::Factory::Dump();
	Plan::Factory::ExportAll();
	
}
