#include "SerialScript.h"

#ifdef flagMAIN

NAMESPACE_TOPSIDE_BEGIN

bool SingleMachine::Open(void(*arg_fn)()) {return false;}
void SingleMachine::Close() {}
	

bool TestEonTest(String s) {
	DUMP(s);
	
	Compiler c;
	String high;
	bool succ = c.CompileEonFileToHigh(s, high);
	
	c.t.Dump();
	LOG(c.sp.GetResult());
	if (!succ)
		return false;
	
	LOG(c.ab.root.GetTreeString(0));
	LOG(high);
	
	return true;
}

void TestEonTests() {
	String dir = ShareDirFile("eon" DIR_SEPS "tests");
	Index<String> files;
	
	FindFile ff;
	if (ff.Search(dir + DIR_SEPS + "*.eon")) do {
		files.Add(ff.GetPath());
	}
	while (ff.Next());
	
	SortIndex(files, StdLess<String>());
	DUMPC(files);
	
	for (String file : files) {
		LOG("Testing: " << GetFileName(file));
		
		//if (file != "/home/sblo/libtopside/share/eon/tests/00a_audio_gen.eon") continue;
		
		if (!TestEonTest(file)) {
			LOG("Failed: " << GetFileName(file));
			break;
		}
	}
}

NAMESPACE_TOPSIDE_END


CONSOLE_APP_MAIN {
	TS::TestEonTests();
}


#endif
