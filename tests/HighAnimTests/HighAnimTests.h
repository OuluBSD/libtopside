#ifndef _HighAnimTests_HighAnimTests_h_
#define _HighAnimTests_HighAnimTests_h_

#include <HighLib/HighLib.h>
using namespace UPP;
using namespace TS;


class TestApp : public TopWindow {
	TimeCallback tc;
	int mode = -1;
	
	HiAnimContext ctx;
	
public:
	typedef TestApp CLASSNAME;
	TestApp();
	
	void Paint(Draw& d);
	
	void Clear();
	void MakeNext();
	void Make1();
	void Make2();
	
	void Iterate();
	
};


#endif
