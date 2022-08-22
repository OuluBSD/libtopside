#include "EonTests.h"



bool Tester::Tokenize(String filepath, String content) {
	this->filepath = filepath;
	this->content = content;
	
	//t.WhenMessage = callback(OnMessage);
	t.SkipNewLines();
	t.SkipComments();
	if (!t.Process(content, filepath))
		return false;
	t.CombineTokens();
	if (1) // pythonic
		t.NewlineToEndStatement();
	t.Dump();
	
	return true;
}

bool Tester::ParseStructure() {
	ts.WhenMessage << THISBACK(OnProcMsg);
	if (!ts.ProcessEon(t)) {
		return false;
	}
	LOG(ts.GetTreeString());
	return true;
}

bool Tester::Parse() {
	sp.WhenMessage << THISBACK(OnProcMsg);
	if (!sp.ProcessEon(ts)) {
		return false;
	}
	LOG(sp.GetTreeString());
	return true;
}

void Tester::OnProcMsg(ProcMsg msg) {
	LOG(msg.ToString());
}




CONSOLE_APP_MAIN {
	SetCoutLog();
	
	String dir = GetDataDirectory();
	Index<String> files;
	//GetDirectoryFiles(dir, files);
	files << GetDataFile("Test0.eon");
	
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
		TEST(t.Tokenize(file, content))
		
		
		// Parse error handling structure (for multiple error messages per single try)
		TEST(t.ParseStructure())
		
		
		// Semantically parse & produce meta script
		TEST(t.Parse())
		
		
		// Run meta script (which makes program AST)
		
		
		// Export High script
		
		
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
