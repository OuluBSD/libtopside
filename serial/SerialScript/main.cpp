#include "SerialScript.h"

#ifdef flagMAIN

NAMESPACE_TOPSIDE_BEGIN

bool SingleMachine::Open(void(*arg_fn)()) {return false;}
void SingleMachine::Close() {}
	

bool TestEonTest(String s, ProgLang tgt) {
	DUMP(s);
	
	Compiler c;
	String code;
	bool succ = c.CompileEonFile(s, tgt, code);
	
	c.t.Dump();
	if (!succ)
		return false;
	
	LOG(c.sp.root.GetTreeString(0));
	LOG(code);
	
	return true;
}

void TestEonTests(String dir_title) {
	String dir = ShareDirFile("eon" DIR_SEPS + dir_title);
	Index<String> files;
	
	FindFile ff;
	if (ff.Search(dir + DIR_SEPS + "*.eon")) do {
		files.Add(ff.GetPath());
	}
	while (ff.Next());
	
	SortIndex(files, StdLess<String>());
	DUMPC(files);
	
	int i = -1;
	for (String file : files) {
		String fname = GetFileName(file);
		
		if (fname.Find("meta") != 0) continue;
		
		LOG("Testing " << i << ": " << fname);
		i++;
		if (i != 2) continue;
		//if (file != "/home/sblo/libtopside/share/eon/tests/02h_daw_core.eon") continue;
		
		if (!TestEonTest(file, LANG_CPP)) {
			LOG("Failed: " << fname);
			break;
		}
		
	}
}

NAMESPACE_TOPSIDE_END


CONSOLE_APP_MAIN {
	TS::TestEonTests("lang");
	//TS::TestEonTests("tests");
}


#endif
