#ifndef _EonTests_EonTests_h_
#define _EonTests_EonTests_h_

#include <Local/Local.h>
#include <High/High.h>
#include <Backend/Backend.h>
using namespace TS;


struct Tester {
	String filepath, content;
	Tokenizer t;
	TokenStructure ts;
	SemanticParser sp;
	HighScriptEmitter emitter;
	AstBuilder ab;
	
	
	typedef Tester CLASSNAME;
	bool Tokenize(String filepath, String content);
	bool ParseStructure();
	bool Parse();
	bool RunMeta();
	
	void OnProcMsg(ProcMsg msg);
	
};

#endif
