#ifndef _ShellCtrl_ShellCtrl_h
#define _ShellCtrl_ShellCtrl_h

#include <EcsComplete/EcsComplete.h>
#include <IScreen/IScreen.h>
using namespace Upp;

#define LAYOUTFILE <ShellCtrl/ShellCtrl.lay>
#include <CtrlCore/lay.h>


NAMESPACE_UPP_BEGIN

#if !defined flagSCREEN || !defined flagFFMPEG || !defined flagOGL || (!defined flagPORTAUDIO && !defined flagBUILTIN_PORTAUDIO )
	#error ShellCtrl requires following flags: SCREEN FFMPEG OGL PORTAUDIO (or BUILTIN_PORTAUDIO)
#endif

/*
ShellCtrl
- attaches to Ctrl-based screen in IScreen
- connects to the default audio port

*/

class ShellCtrl : public Ctrl {
	TimeCallback tc;
	TimeStop ts;
	bool found = false;
	RefT_Atom<Parallel::UppCtrlSinkDevice> sink;
	Image img;
	
	void Update();
	void OnFrame();
public:
	typedef ShellCtrl CLASSNAME;
	ShellCtrl();
	~ShellCtrl();
	
	void PollMachine();
	void RealizeMachine();
	void Start();
	void Stop();
	void Paint(Draw& d) override;
	
};


NAMESPACE_UPP_END

#include "VideoPlayer.h"

#endif
