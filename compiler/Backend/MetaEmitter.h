#ifndef _Backend_MetaEmitter_h_
#define _Backend_MetaEmitter_h_

NAMESPACE_TOPSIDE_BEGIN


class HighScriptEmitter : public SemanticParser {
	String code, main;
	int indent = 0;
	bool dbg_indent = 0;
	Index<String> files;
	
	void Log(String s);
	void Enter();
	void Leave();
	
	String LocArg(const FileLocation& loc);
public:
	typedef HighScriptEmitter CLASSNAME;
	HighScriptEmitter();
	
	static String GetPartStringArray(const PathIdentifier& name);
	
	void Finish();
	void SetDebugIndent(bool b=true) {dbg_indent = b;}
	String GetResult() const {return code;}
	String GetTabString() const;
	
	#include "ParserOverrides.inl"
	
};

NAMESPACE_TOPSIDE_END

#endif
