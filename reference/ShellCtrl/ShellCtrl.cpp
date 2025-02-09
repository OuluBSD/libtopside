#include "ShellCtrl.h"


NAMESPACE_UPP_BEGIN

void ScrUppCtrl_SetCallback(Parallel::ScrUppCtrl::NativeSinkDevice* dev, Callback cb);
Parallel::Packet ScrUppCtrl_GetLastFrame(Parallel::ScrUppCtrl::NativeSinkDevice* dev);


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
		SetShellMode(SHELLMODE_INTERPRETER);
		DefaultRunner(
			false, // don't start main loop, but poll machine manually
			"ShellCtrl Demo",
			"tests" DIR_SEPS "03o_uppctrl_video.eon"
			);
	}
	if (mach.IsStarted() && !mach.HasFailed() && !found) {
		LoopStoreRef ls = mach.Find<LoopStore>();
		if (ls) {
			LoopRef root = ls->GetRoot();
			LOG(root->GetTreeString());
			auto* space = root->GetSpace();
			if (space) {
				LOG(space->GetTreeString());
			}
			LoopRef l = root->Get("upp.app.program.video");
			if (l) {
				auto* space = l->GetSpace();
				if (space) {
					auto atom = space->FindTypeClsSub(SubAtomCls::UPP_CTRL_VIDEO_ATOM_PIPE);
					if (atom) {
						this->sink = atom->AsRefT<UppCtrlSinkDevice>();
						ScrUppCtrl_SetCallback(this->sink->dev, THISBACK(OnFrame));
						found = true;
					}
				}
			}
		}
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

void ShellCtrl::OnFrame() {
	Packet in = ScrUppCtrl_GetLastFrame(sink->dev);
	if (in) {
		auto fmt = in->GetFormat();
		//LOG(fmt.ToString());
		if (fmt.vd == VD(CENTER, VIDEO)) {
			auto res = fmt.vid.GetSize();
			Size sz(res.cx, res.cy);
			ImageBuffer ib(sz);
			RGBA* it  = ib.Begin();
			RGBA* end = ib.End();
			if (fmt.vid.GetChannels() == 3) {
				const Vector<byte>& pixmap = in->Data();
				const byte* src = pixmap.Begin();
				while (it != end) {
					it->r = src[0];
					it->g = src[1];
					it->b = src[2];
					it->a = 255;
					it++;
					src += 3;
				}
			}
			else TODO
			this->img = ib;
		}
	}
}

void ShellCtrl::Paint(Draw& d) {
	Size sz = GetSize();
	if (!sink) {
		d.DrawRect(sz, GrayColor(128-16+Random(32)));
	}
	else {
		d.DrawImage(0,0,img);
	}
}



NAMESPACE_UPP_END

