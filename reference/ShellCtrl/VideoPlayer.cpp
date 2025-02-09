#include "ShellCtrl.h"


NAMESPACE_UPP_BEGIN


VideoPlayerCtrl::VideoPlayerCtrl() {
	CtrlLayout(*this);
	this->hsplit.Horz(shell, playlist);
	this->hsplit.SetPos(7500);
	
	CtrlLayout(playlist);
	
}

VideoPlayerCtrl::~VideoPlayerCtrl() {
	
}





VideoPlayerApp::VideoPlayerApp() {
	Title("VideoPlayer");
	Sizeable().MaximizeBox().MinimizeBox();
	Maximize();
	
	Add(player.SizePos());
	AddFrame(menu);
	AddFrame(status);
	
	player.fullscreen.WhenAction = [this] {
		this->FullScreen(!this->IsFullScreen());
	};
}



NAMESPACE_UPP_END
