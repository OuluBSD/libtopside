#ifndef _GuiTests_GuiTests_h_
#define _GuiTests_GuiTests_h_

#include <Complete/Complete.h>
#include <DesktopSuite/DesktopSuite.h>
using namespace UPP;


class GuiTester : public TopWindow {
	TimeStop ts;
	float phase_seconds = 3.0;
	
public:
	typedef GuiTester CLASSNAME;
	GuiTester();
	
	
	void Paint(Draw& d) override;
	
	
};

#endif
