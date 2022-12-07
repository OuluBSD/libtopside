#ifndef _CuboidTests_CuboidTests_h_
#define _CuboidTests_CuboidTests_h_

#include <Complete/Complete.h>
#include <DesktopSuite/DesktopSuite.h>
#include <EcsVirtualGui/EcsVirtualGui.h>
using namespace UPP;


class GuboTester : public TopGubo {
	TimeStop ts;
	float phase_seconds = 3.0;
	
public:
	typedef GuboTester CLASSNAME;
	GuboTester();
	
	
	void Paint(Draw& d) override;
	
	
};

#endif
