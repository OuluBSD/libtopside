#include "Backend.h"

NAMESPACE_TOPSIDE_BEGIN


HighScriptEmitter::HighScriptEmitter() {
	
}

void HighScriptEmitter::Finish() {
	code.Clear();
	
	Vector<String> main_lines = Split(main, "\n");
	
	
	code << "init_files() {\n";
	for (String file : files)
		code << "\tAddFile(\"" << file << "\");\n";
	code << "}\n\n";
	
	
	code << "main() {\n";
	code << "\tinit_files();\n";
	
	for (String& line : main_lines) {
		code << "\t" << line << "\n";
	}
	code << "}\n\n";
}

void HighScriptEmitter::Log(String s) {
	LOG(GetTabString() + s);
}

String HighScriptEmitter::GetTabString() const {
	String tabs;
	tabs.Cat('\t', max(0, indent));
	return tabs;
}

void HighScriptEmitter::Enter() {
	++indent;
}

void HighScriptEmitter::Leave() {
	--indent;
}

String HighScriptEmitter::GetPartStringArray(const PathIdentifier& name) {
	String s = "[";
	for(int i = 0; i < name.part_count; i++) {
		if (i) s << ", ";
		s << "\"" << name.parts[i]->GetTextValue() << "\"";
	}
	s << "]";
	return s;
}

String HighScriptEmitter::LocArg(const FileLocation& loc) {
	String s;
	s += "[" + IntStr(files.FindAdd(loc.file)) + ", " + IntStr(loc.line) + ", " + IntStr(loc.col) + "]";
	return s;
}

#define DBG_INDENT (dbg_indent ? GetTabString() : String()) <<

void HighScriptEmitter::PushFunction(const FileLocation& loc, SemanticNode& ret_type, const PathIdentifier& name) {
	Log("PushFunction: " + name.ToString() + ", returns " + ret_type.ToString());
	
	main << DBG_INDENT "PushFunction(" << LocArg(loc) << ", " << ret_type.GetPartStringArray() << ", " << GetPartStringArray(name) << ");\n";
	
	Enter();
}

void HighScriptEmitter::Parameter(const FileLocation& loc, const PathIdentifier& type, const PathIdentifier& name) {
	Log("Parameter: " + name.ToString() + ", type " + type.ToString());
	
	main << DBG_INDENT "Parameter(" << LocArg(loc) << ", " << GetPartStringArray(type) << ", " << GetPartStringArray(name) << ");\n";
}

void HighScriptEmitter::PushFunctionDefinition(const FileLocation& loc) {
	Log("FunctionDefinition:");
	
	main << DBG_INDENT "FunctionDefinition(" << LocArg(loc) << ");\n";
	
	Enter();
}

void HighScriptEmitter::PopFunctionDefinition(const FileLocation& loc) {
	Leave();
	//Log("PopFunctionDefinition:");
	
	main << DBG_INDENT "PopFunctionDefinition(" << LocArg(loc) << ");\n";
}

void HighScriptEmitter::PopFunction(const FileLocation& loc) {
	Leave();
	
	main << DBG_INDENT "PopFunction(" << LocArg(loc) << ");\n";
}

void HighScriptEmitter::PushStatementList(const FileLocation& loc) {
	main << DBG_INDENT "PushStatementList(" << LocArg(loc) << ");\n";
	
	Enter();
}

void HighScriptEmitter::PopStatementList(const FileLocation& loc) {
	Leave();
	
	main << DBG_INDENT "PopStatementList(" << LocArg(loc) << ");\n";
}

void HighScriptEmitter::PushStatement(const FileLocation& loc, StmtType type) {
	Log("PushStatement: " + GetStmtTypeString(type));
	
	main << DBG_INDENT "PushStatement(" << LocArg(loc) << ", \"" << GetStmtTypeString(type) << "\");\n";
	
	Enter();
}

void HighScriptEmitter::PopStatement(const FileLocation& loc) {
	Leave();
	
	main << DBG_INDENT "PopStatement(" << LocArg(loc) << ");\n";
}

void HighScriptEmitter::BindStatementParameter(const FileLocation& loc, StmtParamType t) {
	Log("BindStatementParameter: " + GetStmtParamTypeString(t));
	
	main << DBG_INDENT "BindStatementParameter(" << LocArg(loc) << ", \"" << GetStmtParamTypeString(t) << "\");\n";
}

void HighScriptEmitter::DeclareVariable(const FileLocation& loc, const SemanticNode& n, const PathIdentifier& id) {
	Log("DeclareVariable: " + n.ToString() + ", " + id.ToString());
	
	main << DBG_INDENT "PushFunction(" << LocArg(loc) << ", " << n.GetPartStringArray() << ", " << GetPartStringArray(id) << ");\n";
}

/*void HighScriptEmitter::PushExprScope() {
	Enter();
}*/

void HighScriptEmitter::PopExprScopeToCtor(const FileLocation& loc) {
	Leave();
	
	main << DBG_INDENT "PopExprScopeToCtor(" << LocArg(loc) << ");\n";
}

/*void HighScriptEmitter::PushCall(const PathIdentifier& id) {
	Log("PushCall: " + id.ToString());
	Enter();
}

void HighScriptEmitter::PopCall(){
	Leave();
}*/

/*void HighScriptEmitter::PushExprScopeRval() {
	Enter();
	
}
*/
void HighScriptEmitter::PopExpr(const FileLocation& loc) {
	Leave();
	
	main << DBG_INDENT "PopExpr(" << LocArg(loc) << ");\n";
}

void HighScriptEmitter::PushRval(const FileLocation& loc, const SemanticNode& n) {
	Log("PushRval: " + n.ToString());
	
	main << DBG_INDENT "PushRval(" << LocArg(loc) << ", " << n.GetPartStringArray() << ");\n";
	
	Enter();
}

void HighScriptEmitter::PushRvalCall(const FileLocation& loc, const SemanticNode& n) {
	Log("PushRvalCall: " + n.ToString());
	
	main << DBG_INDENT "PushRvalCall(" << LocArg(loc) << ", " << n.GetPartStringArray() << ");\n";
	
	Enter();
}

void HighScriptEmitter::PushRvalConstruct(const FileLocation& loc, const SemanticNode& n) {
	Log("PushRvalConstruct: " + n.ToString());
	
	main << DBG_INDENT "PushRvalConstruct(" << LocArg(loc) << ", " << n.GetPartStringArray() << ");\n";
	
	Enter();
}

void HighScriptEmitter::PushRvalConstant(const FileLocation& loc, const Token& t) {
	Log("PushRvalConstant: " + t.ToString());
	
	main << DBG_INDENT "PushRvalConstant(" << LocArg(loc) << ", " << t.GetTextValue() << ");\n";
	
	Enter();
}

void HighScriptEmitter::Expr1(const FileLocation& loc, OpType op) {
	//Leave();
	Log("Expr1: " + GetOpString(op));
	
	main << DBG_INDENT "Expr1(" << LocArg(loc) << ", \"" << GetOpString(op) << "\");\n";
	
	//Enter();
}

void HighScriptEmitter::Expr2(const FileLocation& loc, OpType op) {
	//Leave();
	Leave();
	Log("Expr2: " + GetOpString(op));
	
	main << DBG_INDENT "Expr2(" << LocArg(loc) << ", \"" << GetOpString(op) << "\");\n";
	
	//Enter();
}

void HighScriptEmitter::Expr3(const FileLocation& loc, OpType op) {
	//Leave();
	Leave();
	Leave();
	Log("Expr3: " + GetOpString(op));
	
	main << DBG_INDENT "Expr3(" << LocArg(loc) << ", \"" << GetOpString(op) << "\");\n";
	
	//Enter();
}

NAMESPACE_TOPSIDE_END
