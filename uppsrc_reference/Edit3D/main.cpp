#include "Edit3D.h"

#ifdef flagMAIN


GUI_APP_MAIN {
	using namespace TS;
	using namespace UPP;
	//TS::ChFlatDarkSkin();
	//TS::ChDarkSkin();
	TS::ChGraySkin();
	//TS::ChStdSkin();
	
	SetCoutLog();
	
	DaemonBase::Register<EditClientService>("EditClient");
	
	CommandLineArguments cmd;
	DaemonBase daemon;
	
	cmd.AddArg('v', "Verbose", false);
	cmd.AddArg('t', "Load test project", false);
	cmd.AddArg('n', "Pointcloud directory", true, "directory");
	cmd.AddArg('c', "Connect to a server", true, "address");
	cmd.AddArg('p', "Port", true, "integer");
	cmd.AddArg('g', "Debug-mode", false);
	if (!cmd.Parse()) {
		cmd.PrintHelp();
		return;
	}
	
	enum {
		EMPTY,
		POINTCLOUD,
		PROJECT0,
		REMOTE,
		REMOTE_DEBUG,
	};
	int mode = EMPTY;
	
	String pointcloud_dir;
	
	if (cmd.IsArg('c')) {
		daemon.Add("EditClient");
		daemon.Add("EnetClient");
		EnetServiceClient::addr_arg = cmd.GetArg('c');
		if (cmd.IsArg('p')) {
			EnetServiceClient::port_arg = StrInt(cmd.GetArg('p'));
			LOG("Connecting to port " << (int)EnetServiceClient::port_arg);
		}
		EnetServiceClient::SetVerbose(cmd.IsArg('v'));
		if (cmd.IsArg('g'))
			mode = REMOTE_DEBUG;
		else
			mode = REMOTE;
		
		if (!daemon.Init())
			return;
	}
	else if (cmd.IsArg('n')) {
		pointcloud_dir = cmd.GetArg('n');
		mode = POINTCLOUD;
	}
	else if (cmd.IsArg('t')) {
		mode = PROJECT0;
	}
	
	
	daemon.RunInThread();
	
	Edit3D app;
	
	
	if (mode == REMOTE_DEBUG)
		app.LoadRemote(daemon.FindServiceT<EditClientService>(), true);
	else if (mode == REMOTE)
		app.LoadRemote(daemon.FindServiceT<EditClientService>(), false);
	else if (mode == POINTCLOUD)
		app.LoadWmrStereoPointcloud(pointcloud_dir);
	else if (mode == PROJECT0)
		app.LoadTestProject(0);
	
	app.Run();
	
	daemon.Stop();
	daemon.Deinit();
}

#endif
