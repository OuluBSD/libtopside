#include "EonTests.h"




void Tester::OnProcMsg(ProcMsg msg) {
	LOG(msg.ToString());
}




CONSOLE_APP_MAIN {
	SetCoutLog();
	
	String dir = GetDataDirectory();
	Index<String> files;
	//GetDirectoryFiles(dir, files);
	files << GetDataFile("Test00.eon");
	
	bool fail = false;
	for (String file : files) {
		String ext = GetFileExt(file);
		if (ext != ".eon")
			continue;
		String content = LoadFile(file);
		if (content.IsEmpty()) {
			LOG("error: empty file: " << file);
			fail = true;
			break;
		}
		
		Tester t;
		
		#define TEST(x) if (!(x)) {LOG("error: test " #x " failed on file " << file); fail = true; break;}
		
		// Tokenize eon
		TEST(t.Tokenize(file, content, true))
		t.t.Dump();
		
		// Parse error handling structure (for multiple error messages per single try)
		TEST(t.ParseStructure())
		
		
		// Semantically parse & produce meta script
		TEST(t.Parse())
		LOG(t.sp.GetResult());
		
		
		// Run meta script (which makes program AST)
		TEST(t.RunMeta())
		LOG(t.ab.root.GetTreeString(0));
		
		
		// Export High script
		TEST(t.ExportHigh())
		LOG(t.ex.GetResult());
		
		
		// Load machine & ecs with High? (Export & dummy loader)
		// - pros: 1 to 1 c++ loader
		//		- export also c++ main function
		
		
	}
	
	if (!fail) {
		LOG("success! :)");
	}
	else {
		LOG("fail :(");
	}
	
}
