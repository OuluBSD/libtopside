#include "ShellCtrl.h"


NAMESPACE_UPP_BEGIN


ShellCtrl::ShellCtrl() {
	
}

ShellCtrl::~ShellCtrl() {
	if (Thread::IsShutdownThreads()) {
		SingleMachine::Static().Stop();
	}
}

void ShellCtrl::RealizeMachine() {
	Machine& mach = SingleMachine::Static();
	if (!mach.IsStarted()) {
		DefaultRunner(
			false, // don't start main loop, but poll machine manually
			"ShellCtrl Demo",
			"tests" DIR_SEPS "03o_uppctrl_video.eon"
			);
	}
}

void ShellCtrl::Start() {
	tc.Set(-1000/30, THISBACK(Update));
}

void ShellCtrl::Stop() {
	tc.Kill();
}

void ShellCtrl::PollMachine() {
	Machine& mach = SingleMachine::Static();
	if (mach.IsStarted() && !mach.HasFailed()) {
		double dt = ResetSeconds(ts);
		mach.Update(dt);
	}
}

void ShellCtrl::Update() {
	RealizeMachine();
	PollMachine();
	Refresh();
}

void ShellCtrl::Paint(Draw& d) {
	Size sz = GetSize();
	if (1) {
		#ifdef flagDEBUG
		d.DrawRect(sz, Color(Random(256), Random(256), Random(256)));
		#else
		d.DrawRect(sz, White());
		#endif
		return;
	}
	
	d.DrawRect(sz, White());
}



NAMESPACE_UPP_END

