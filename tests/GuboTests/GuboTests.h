#ifndef _GuboTests_GuboTests_h_
#define _GuboTests_GuboTests_h_

#include <Complete/Complete.h>
#include <DesktopSuite/DesktopSuite.h>
using namespace UPP;


class GuboTester : public TopGubo {
	TimeStop ts;
	float phase_seconds = 3.0;
	
public:
	typedef GuboTester CLASSNAME;
	GuboTester();
	
	
	void Paint(Draw3D& d) override;
	
	
};

#endif
