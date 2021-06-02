#include <TrustLib/TrustLib.h>


void GraphTest();
void AppleSeedTest();
void TrustNetTest();

CONSOLE_APP_MAIN {
	using namespace UPP;
	using namespace TS;
	
	SetCoutLog();
	
	
	GraphTest();
	AppleSeedTest();
	TrustNetTest();
}

