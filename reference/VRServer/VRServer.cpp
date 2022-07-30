#include "VRServer.h"



CONSOLE_APP_MAIN {
	SetCoutLog();
	
	Glib2Daemon daemon;
	
	daemon.Add("TcpServer");
	daemon.Add("LocalVR");
	daemon.Add("LocalVRDebug");
	daemon.Add("LocalHMD");
	//daemon.Add("WmrFusion");
	
	daemon.DefaultProcedure();
	
}
