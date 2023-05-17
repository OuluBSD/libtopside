#include "Local.h"

NAMESPACE_TOPSIDE_BEGIN


static void DaemonBase_signal_handler(int sig)
{
	#ifdef flagMSC
	TODO
	#else
	signal(sig, SIG_IGN);
	#endif
	
	Cout() << "DaemonBase - stopping\n";

	DaemonBase::Latest()->SetNotRunning();
}




DaemonService* DaemonService::FindService(String name) const {
	return base->FindService(name);
}


DaemonBase::DaemonBase() {
	Latest() = this;
}

bool DaemonBase::Init() {
	#ifdef flagMSC
	TODO
	#else
	signal(SIGINT, DaemonBase_signal_handler);
	#endif
	
	if (requested_services.IsEmpty()) {
		LOG("DaemonBase::Init: error: no requested service");
		return false;
	}
	
	for (String svc : requested_services) {
		int i  = NewFnArray().Find(svc);
		if (i < 0) {
			LOG("DaemonBase::Init: error: no service named '" << svc << "' registered");
			return false;
		}
		DaemonService& ds = services.Add(svc, NewFnArray()[i]());
		ds.base = this;
	}
	
	for(int i = 0; i < services.GetCount(); i++) {
		String name = services.GetKey(i);
		DaemonService& svc = services[i];
		if (!svc.Init(name)) {
			LOG("DaemonBase::Init: error: init failed for service named '" << name << "'");
			return false;
		}
	}
	
	running = true;
	return true;
}

void DaemonBase::Run() {
	TimeStop ts;
	while (running && (!timeout || ts.Seconds() < timeout)) {
		Update();
		Sleep(10);
	}
}

void DaemonBase::Update() {
	for (DaemonService& s : services.GetValues())
		s.Update();
}

void DaemonBase::SetNotRunning() {
	running = false;
}

void DaemonBase::Stop() {
	for(int i = 0; i < services.GetCount(); i++) {
		String name = services.GetKey(i);
		DaemonService& svc = services[i];
		svc.Stop();
	}
	
	
	running = false;
}

void DaemonBase::Deinit() {
	for(int i = 0; i < services.GetCount(); i++) {
		String name = services.GetKey(i);
		LOG("DaemonBase::Deinit: " << name);
		DaemonService& svc = services[i];
		svc.Deinit();
	}
	services.Clear();
}

void DaemonBase::DefaultProcedure() {
	if (!Init())
		return;
	
	Run();
	if (running)
		Stop();
	Deinit();
}

DaemonService* DaemonBase::FindService(String name) {
	int i = services.Find(name);
	if (i < 0)
		return 0;
	return &services[i];
}

void DaemonBase::Add(String svc_name) {
	ASSERT(!svc_name.IsEmpty());
	requested_services.FindAdd(svc_name);
}







#ifdef flagGLIB2
bool Glib2Daemon::Init() {
	if (!DaemonBase::Init())
		return false;
	
	loop = g_main_loop_new(NULL, TRUE);
	if (!loop)
		return false;
	
	return true;
}

void Glib2Daemon::Run() {
	g_main_loop_run(loop);
	
	DaemonBase::Run();
}

void Glib2Daemon::Stop() {
	DaemonBase::Stop();
	
	g_main_loop_quit(loop);
}

void Glib2Daemon::Deinit() {
	DaemonBase::Deinit();
	
	g_main_loop_unref(loop);
}
#endif


NAMESPACE_TOPSIDE_END
