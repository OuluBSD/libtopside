#ifndef _ShellCtrl_ShellCtrl_h
#define _ShellCtrl_ShellCtrl_h

#include <EcsComplete/EcsComplete.h>
using namespace Upp;

NAMESPACE_UPP_BEGIN


/*
ShellCtrl
- attaches to Ctrl-based screen in IScreen
- connects to the default audio port

*/

class ShellCtrl : public Ctrl {
	TimeCallback tc;
	
	void Update();
public:
	typedef ShellCtrl CLASSNAME;
	ShellCtrl();
	
	void Start();
	void Stop();
	
};


NAMESPACE_UPP_END

#endif
