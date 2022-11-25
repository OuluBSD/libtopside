#include "VirtualGui3D01.h"


NAMESPACE_TOPSIDE_BEGIN


CoreWindowTesterApp::CoreWindowTesterApp(int test_idx) : test_idx(test_idx) {
	
}

void CoreWindowTesterApp::Run() {
	switch (test_idx) {
		case 0: Test_WindowOpenClose(); break;
		default: ASSERT_(0, "invalid test index");
	}
}

void CoreWindowTesterApp::Test_WindowOpenClose() {
	
}






VirtualGuiTesterApp::VirtualGuiTesterApp(int test_idx) : test_idx(test_idx) {
	
	
	tc.Set(-1000, THISBACK(TimedToggle));
}

void VirtualGuiTesterApp::TimedToggle() {
	
	Refresh();
}

void VirtualGuiTesterApp::Paint(Draw& d) {
	Rect r = GetSize();
	
}

void VirtualGuiTesterApp::LeftDown(Point p, dword keyflags) {
	
}

void VirtualGuiTesterApp::RightDown(Point p, dword keyflags) {
	
}

bool VirtualGuiTesterApp::Key(dword key, int count) {
	
	return false;
}

void VirtualGuiTesterApp::MouseMove(Point p, dword keyflags) {
	
}

void VirtualGuiTesterApp::MouseWheel(Point p, int zdelta, dword keyflags) {
	
}


NAMESPACE_TOPSIDE_END


GUI_APP_MAIN {
	int idx = 0;
	const auto& cmd = CommandLine();
	if (!cmd.IsEmpty())
		idx = ScanInt(cmd[0]);
	
	CoreWindowTesterApp(0).Run();
}
