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

void TestEonTests(String dir_title, String prefix="", int single=-1) {
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
		i++;
		String fname = GetFileName(file);
		
		if (prefix.GetCount() && fname.Find(prefix) != 0) continue;
		
		LOG("Testing " << i << ": " << fname);
		if (single >= 0 && i != single) continue;
		
		if (!TestEonTest(file, LANG_CPP)) {
			LOG("Failed: " << fname);
			break;
		}
		
	}
}

NAMESPACE_TOPSIDE_END


CONSOLE_APP_MAIN {
	//TS::TestEonTests("lang", "meta", 13);
	TS::TestEonTests("lang", "meta");
	//TS::TestEonTests("lang", "test");
	//TS::TestEonTests("tests", "", 65);
	TS::TestEonTests("tests");
}


#endif
