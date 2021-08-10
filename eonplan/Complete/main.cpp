#include "Complete.h"
using namespace UPP;
using namespace TS;


CONSOLE_APP_MAIN {
	SetCoutLog();
	
	
	Machine1<TestAudioChain>			mach;
	mach.Init();
	mach.Dump();
	
	
}
