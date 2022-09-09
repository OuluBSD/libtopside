#ifndef _Backend_Compiler_h_
#define _Backend_Compiler_h_

NAMESPACE_TOPSIDE_BEGIN


struct Compiler {
	String filepath, content;
	
	Tokenizer t;
	TokenStructure ts;
	HighScriptEmitter sp;
	AstBuilder ab;
	AstExporter ex;
	
	
public:
	typedef Compiler CLASSNAME;
	Compiler();
	
	bool CompileEonFile(String filepath, ProgLang lang, String& output);
	
public:
	bool Tokenize(String filepath, String content, bool pythonic=false);
	bool ParseStructure();
	bool Parse();
	bool RunMeta();
	bool ExportHigh();
	bool ExportCpp();
	
	void OnProcMsg(ProcMsg msg);
	
	
};

NAMESPACE_TOPSIDE_END

#endif
