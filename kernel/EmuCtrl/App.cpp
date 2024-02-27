#include "EmuCtrl.h"


EmuApp::EmuApp() {
	Add(log.SizePos());
	
}

void EmuApp::Init() {
	ASSERT(global);
	Monitor& mon = global->monitor;
	
	#define LINK(x) mon.On##x << THISBACK(x);
	LINK(MoveCursor)
	LINK(Scroll)
	LINK(Put)
	LINK(Clear)
	LINK(Write)
	LINK(WriteDec)
	LINK(WriteHexPtr)
	LINK(WriteHexInt)
	LINK(NewLine)
	#undef LINK
	
}

void EmuApp::Data() {
	Monitor& mon = global->monitor;
	
	
	
}

void EmuApp::Start() {
	running = 1;
	stopped = 0;
	
	Thread::Start(THISBACK(EmuProcess));
	Sleep(100); // give some time for booting
	
	TopWindow::Run();
	
	running = 0;
	while (!stopped) Sleep(1);
}

void EmuApp::EmuProcess() {
	multiboot mboot;
	
	mboot.OnMonitorCreate << THISBACK(Init);
	
	int ret = multiboot_main(&mboot);
	
	stopped = 1;
	running = 0;
}

void EmuApp::RefreshOutput() {
	log.SetData(output);
	log.SetCursor(log.GetLength());
}

void EmuApp::MoveCursor() {
	
}

void EmuApp::Scroll() {
	
}

void EmuApp::Put(char c) {
	
}

void EmuApp::Clear() {
	
}

void EmuApp::Write(const char *c) {
	output << String(c).ToWString();
	PostCallback(THISBACK(RefreshOutput));
}

void EmuApp::WriteDec(int i) {
	
}

void EmuApp::WriteHexPtr(void* p) {
	
}

void EmuApp::WriteHexInt(size_t i) {
	
}

void EmuApp::NewLine() {
	
}

