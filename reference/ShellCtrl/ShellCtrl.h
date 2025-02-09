#ifndef _ShellCtrl_ShellCtrl_h
#define _ShellCtrl_ShellCtrl_h

#include <EcsComplete/EcsComplete.h>
using namespace Upp;

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
	
	void Update();
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

#endif
