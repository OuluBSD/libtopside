#include "Backend.h"

NAMESPACE_TOPSIDE_BEGIN


Compiler::Compiler() {
	t.WhenMessage << THISBACK(OnProcMsg);
	ts.WhenMessage << THISBACK(OnProcMsg);
	sp.WhenMessage << THISBACK(OnProcMsg);
	ex.WhenMessage << THISBACK(OnProcMsg);
	
}

bool Compiler::CompileEonFile(String filepath, ProgLang lang, String& output) {
	output.Clear();
	
	ProcMsg m;
	if (!FileExists(filepath)) {
		m.msg = "file does not exist: " + filepath;
		m.severity = PROCMSG_ERROR;
		OnProcMsg(m);
		return false;
	}
	
	String content = LoadFile(filepath);
	if (content.IsEmpty()) {
		m.msg = "got empty file from: " + filepath;
		m.severity = PROCMSG_ERROR;
		OnProcMsg(m);
		return false;
	}
	
	bool verbose = true;
	
	#define TEST(x) if (!(x)) {return false;}
	
	// Tokenize eon
	TEST(Tokenize(filepath, content, true))
	if (verbose) t.Dump();
	
	// Parse error handling structure (for multiple error messages per single try)
	TEST(ParseStructure())
	
	// Semantically parse
	TEST(Parse())
	if (verbose) {LOG(sp.GetRoot().GetTreeString(0));}
	
	// Run meta
	TEST(RunMeta())
	if (verbose) {LOG(ar.GetRoot().GetTreeString(0));}
	
	if (lang == LANG_HIGH) {
		// Export High script
		TEST(ExportHigh())
	}
	else if (lang == LANG_CPP) {
		TEST(ExportCpp());
	}
	else {
		TODO
	}
		
	
	
	output = ex.GetResult();
	if (verbose) {LOG(output);}
	
	return true;
}

bool Compiler::Tokenize(String filepath, String content, bool pythonic) {
	this->filepath = filepath;
	this->content = content;
	
	//t.WhenMessage = callback(OnMessage);
	t.SkipNewLines(!pythonic);
	t.SkipComments();
	if (!t.Process(content, filepath))
		return false;
	t.CombineTokens();
	if (pythonic)
		t.NewlineToEndStatement();
	
	return true;
}

bool Compiler::ParseStructure() {
	ts.WhenMessage = THISBACK(OnProcMsg);
	if (!ts.ProcessEon(t)) {
		return false;
	}
	LOG(ts.GetTreeString());
	return true;
}

bool Compiler::Parse() {
	sp.WhenMessage = THISBACK(OnProcMsg);
	if (!sp.ProcessEon(ts)) {
		return false;
	}
	LOG(sp.GetTreeString());
	
	return true;
}

bool Compiler::RunMeta() {
	ar.WhenMessage = THISBACK(OnProcMsg);
	if (!ar.Execute(sp.GetRoot()))
		return false;
	
	return true;
}

bool Compiler::ExportHigh() {
	InitHighExporter(ex.lang);
	
	ex.WhenMessage = THISBACK(OnProcMsg);
	if (!ex.Process(ar.GetRoot()))
		return false;
	
	return true;
}

bool Compiler::ExportCpp() {
	InitCppExporter(ex.lang);
	
	ex.WhenMessage = THISBACK(OnProcMsg);
	if (!ex.Process(ar.GetRoot()))
		return false;
	
	return true;
}

void Compiler::OnProcMsg(ProcMsg msg) {
	LOG(msg.ToString());
}


NAMESPACE_TOPSIDE_END
