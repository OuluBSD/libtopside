#ifndef _Editor_DebuggerCtrl_h_
#define _Editor_DebuggerCtrl_h_

#include <CtrlLib/CtrlLib.h>
using namespace Upp;


class DebuggerCtrl : public ParentCtrl {
	TabCtrl tabs;
	
	
public:
	DebuggerCtrl();
	
	void RefreshDisassembly();
};

#endif
