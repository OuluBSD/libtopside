#ifndef _ShellCtrl_VideoPlayer_h_
#define _ShellCtrl_VideoPlayer_h_

NAMESPACE_UPP_BEGIN


class VideoPlayerCtrl : public WithVideoPlayerLayout<Ctrl> {
	ShellCtrl shell;
	WithPlaylistLayout<Ctrl> playlist;
	
public:
	typedef VideoPlayerCtrl CLASSNAME;
	VideoPlayerCtrl();
	~VideoPlayerCtrl();
	
};


class VideoPlayerApp : public TopWindow {
	VideoPlayerCtrl player;
	MenuBar menu;
	StatusBar status;
	
public:
	typedef VideoPlayerApp CLASSNAME;
	VideoPlayerApp();
	
};

NAMESPACE_UPP_END

#endif
