#include "Meta.h"

using namespace Topside;
using namespace Upp;

CONSOLE_APP_MAIN {
	
	SimpleProgramProcess proc0;
	proc0.Process("Mark1", GetDataFile("meta2.vm1"), GetDataFile("aexp_vm2.meta2"), GetDataFile("aexp.vm1"), GetDataFile("aexp_dbg.log"));
	proc0.DumpMessages();
	
	
	SimpleProgramProcess proc1;
	proc1.Process("Mark1", GetDataFile("aexp.vm1"), GetDataFile("simple1.aexp"), GetDataFile("simple1.txt"));
	proc1.DumpMessages();
	
}
