#include <TrustLib/TrustLib.h>


void GraphTest();
void AppleSeedTest();
void TrustNetTest();

CONSOLE_APP_MAIN {
	using namespace Upp;
	using namespace Oulu;
	
	SetCoutLog();
	
	
	GraphTest();
	AppleSeedTest();
	TrustNetTest();
}

