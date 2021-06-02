#include "PortManager.h"


NAMESPACE_TOPSIDE_BEGIN


PortManager::PortManager() {
	
	
}


void PortManagerMain() {
	using namespace UPP;
	using namespace UPP;
	SetCoutLog();
	
	PortManager mgr;
	
	String ports_path = GetDataFile("ports.json");
	if (!FileExists) {
		LOG("Could not find ports.json");
		Exit(1);
	}
	
	
}


NAMESPACE_TOPSIDE_END


CONSOLE_APP_MAIN {TS::PortManagerMain();}

