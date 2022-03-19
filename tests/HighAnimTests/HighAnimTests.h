#ifndef _HighAnimTests_HighAnimTests_h_
#define _HighAnimTests_HighAnimTests_h_

#include <HighAnim/HighAnim.h>
using namespace UPP;
using namespace TS;


class TestApp : public TopWindow {
	Animation	a;
	AnimPlayer	p;
	TimeCallback tc;
	int mode = -1;
	int op_limit = 1000000;
	
	ArrayMap<String, HiValue> global;
	One<Hi> vm;
	String code;
	
public:
	typedef TestApp CLASSNAME;
	TestApp();
	
	void Paint(Draw& d);
	
	void Clear();
	void MakeNext();
	void Make1();
	void Make2();
	
	void ContinueVm();
	void BeginVm();
	void Iterate();
	void HI_DrawText(HiEscape& e);
	
};


#endif
