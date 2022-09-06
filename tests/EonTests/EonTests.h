#ifndef _EonTests_EonTests_h_
#define _EonTests_EonTests_h_

#include <Local/Local.h>
#include <High/High.h>
#include <Backend/Backend.h>
using namespace TS;


struct Tester : Compiler {
	
	
	typedef Tester CLASSNAME;
	
	void OnProcMsg(ProcMsg msg);
	
};

#endif
