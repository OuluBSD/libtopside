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

void HighScriptEmitter::PushFunction(const FileLocation& loc, AstNode& ret_type, const PathIdentifier& name) {
	Log("PushFunction: " + name.ToString() + ", returns " + ret_type.ToString());
	
	main << DBG_INDENT "PushFunction(" << LocArg(loc) << ", " << ret_type.GetPartStringArray() << ", " << GetPartStringArray(name) << ");\n";
	
	Enter();
}

void HighScriptEmitter::PushMetaFunction(const FileLocation& loc, AstNode& ret_type, const PathIdentifier& name) {
	Log("PushMetaFunction: " + name.ToString() + ", returns " + ret_type.ToString());
	
	main << DBG_INDENT "PushMetaFunction(" << LocArg(loc) << ", " << ret_type.GetPartStringArray() << ", " << GetPartStringArray(name) << ");\n";
	
	Enter();
}

void HighScriptEmitter::Parameter(const FileLocation& loc, const PathIdentifier& type, const PathIdentifier& name) {
	Log("Parameter: " + name.ToString() + ", type " + type.ToString());
	
	main << DBG_INDENT "Parameter(" << LocArg(loc) << ", " << GetPartStringArray(type) << ", " << GetPartStringArray(name) << ");\n";
}

void HighScriptEmitter::MetaParameter(const FileLocation& loc, const PathIdentifier& type, const PathIdentifier& name) {
	Log("MetaParameter: " + name.ToString() + ", type " + type.ToString());
	
	main << DBG_INDENT "MetaParameter(" << LocArg(loc) << ", " << GetPartStringArray(type) << ", " << GetPartStringArray(name) << ");\n";
}

/*void HighScriptEmitter::PushFunctionDefinition(const FileLocation& loc) {
	Log("FunctionDefinition:");
	
	main << DBG_INDENT "PushFunctionDefinition(" << LocArg(loc) << ");\n";
	
	Enter();
}*/

void HighScriptEmitter::PopFunctionDefinition(const FileLocation& loc) {
	Leave();
	//Log("PopFunctionDefinition:");
	
	main << DBG_INDENT "PopFunctionDefinition(" << LocArg(loc) << ");\n";
}

void HighScriptEmitter::PopFunction(const FileLocation& loc) {
	Leave();
	
	main << DBG_INDENT "PopFunction(" << LocArg(loc) << ");\n";
}

void HighScriptEmitter::PopMetaFunction(const FileLocation& loc) {
	Leave();
	
	main << DBG_INDENT "PopMetaFunction(" << LocArg(loc) << ");\n";
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
	
	//main << DBG_INDENT "PushStatement(" << LocArg(loc) << ", \"" << GetStmtTypeString(type) << "\");\n";
	main << DBG_INDENT "PushStatement(" << LocArg(loc) << ", " << IntStr((int)type) << "); // " << GetStmtTypeString(type) << "\n";
	
	Enter();
}

void HighScriptEmitter::PopStatement(const FileLocation& loc) {
	Leave();
	
	main << DBG_INDENT "PopStatement(" << LocArg(loc) << ");\n";
}

void HighScriptEmitter::PushStatementParameter(const FileLocation& loc, StmtParamType t) {
	Log("PushStatementParameter: " + GetStmtParamTypeString(t));
	
	main << DBG_INDENT "PushStatementParameter(" << LocArg(loc) << ", \"" << GetStmtParamTypeString(t) << "\");\n";
}

void HighScriptEmitter::PopStatementParameter(const FileLocation& loc) {
	Log("PopStatementParameter");
	
	main << DBG_INDENT "PopStatementParameter(" << LocArg(loc) << ");\n";
}

void HighScriptEmitter::DeclareVariable(const FileLocation& loc, AstNode& n, const PathIdentifier& id) {
	Log("DeclareVariable: " + n.ToString() + ", " + id.ToString());
	
	main << DBG_INDENT "DeclareVariable(" << LocArg(loc) << ", " << n.GetPartStringArray() << ", " << GetPartStringArray(id) << ");\n";
}

void HighScriptEmitter::DeclareMetaVariable(const FileLocation& loc, AstNode& n, const PathIdentifier& id) {
	Log("DeclareMetaVariable: " + n.ToString() + ", " + id.ToString());
	
	main << DBG_INDENT "DeclareMetaVariable(" << LocArg(loc) << ", " << n.GetPartStringArray() << ", " << GetPartStringArray(id) << ");\n";
}

void HighScriptEmitter::Variable(const FileLocation& loc, const AstNode& n, const PathIdentifier& id) {
	Log("Variable: " + n.ToString() + ", " + id.ToString());
	
	main << DBG_INDENT "Variable(" << LocArg(loc) << ", " << n.GetPartStringArray() << ", " << GetPartStringArray(id) << ");\n";
}

void HighScriptEmitter::PushRvalResolve(const FileLocation& loc, const PathIdentifier& id, SemanticType t) {
	Log("PushRvalResolve: " + id.ToString() + " " + GetSemanticTypeString(t));
	
	main << DBG_INDENT "PushRvalResolve(" << LocArg(loc) << ", " << GetPartStringArray(id) << ", " << IntStr((int)t) << ");\n";
}

void HighScriptEmitter::PushRvalUnresolved(const FileLocation& loc, const PathIdentifier& id, SemanticType t) {
	Log("PushRvalUnresolved: " + id.ToString() + " " + GetSemanticTypeString(t));
	
	main << DBG_INDENT "PushRvalUnresolved(" << LocArg(loc) << ", " << GetPartStringArray(id) << ", " << IntStr((int)t) << ");\n";
}

void HighScriptEmitter::PushRvalArgumentList(const FileLocation& loc) {
	Log("PushRvalArgumentList");
	
	main << DBG_INDENT "PushRvalArgumentList(" << LocArg(loc) << ");\n";
}

void HighScriptEmitter::Argument(const FileLocation& loc) {
	Log("Argument");
	
	main << DBG_INDENT "Argument(" << LocArg(loc) << ");\n";
}

/*void HighScriptEmitter::PushExprScope() {
	Enter();
}*/

/*void HighScriptEmitter::PopExprScopeToCtor(const FileLocation& loc) {
	Leave();
	
	main << DBG_INDENT "PopExprScopeToCtor(" << LocArg(loc) << ");\n";
}*/

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

void HighScriptEmitter::PushRval(const FileLocation& loc, AstNode& n) {
	Log("PushRval: " + n.ToString());
	
	main << DBG_INDENT "PushRval(" << LocArg(loc) << ", " << GetRelativePartStringArray(n) << ");\n";
	
	Enter();
}

/*void HighScriptEmitter::PushRvalCall(const FileLocation& loc, AstNode& n) {
	Log("PushRvalCall: " + n.ToString());
	
	main << DBG_INDENT "PushRvalCall(" << LocArg(loc) << ", " << GetRelativePartStringArray(n) << ");\n";
	
	Enter();
}*/

void HighScriptEmitter::PushRvalConstruct(const FileLocation& loc, AstNode& n) {
	Log("PushRvalConstruct: " + n.ToString());
	
	main << DBG_INDENT "PushRvalConstruct(" << LocArg(loc) << ", " << GetRelativePartStringArray(n) << ");\n";
	
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
	
	main << DBG_INDENT "Expr1(" << LocArg(loc) << ", " << IntStr((int)op) << "); // " << GetOpString(op) << "\n";
	
	//Enter();
}

void HighScriptEmitter::Expr2(const FileLocation& loc, OpType op) {
	//Leave();
	Leave();
	Log("Expr2: " + GetOpString(op));
	
	main << DBG_INDENT "Expr2(" << LocArg(loc) << ", " << IntStr((int)op) << "); // " << GetOpString(op) << "\n";
	
	//Enter();
}

void HighScriptEmitter::Expr3(const FileLocation& loc, OpType op) {
	//Leave();
	Leave();
	Leave();
	Log("Expr3: " + GetOpString(op));
	
	main << DBG_INDENT "Expr3(" << LocArg(loc) << ", " << IntStr((int)op) << "); // " << GetOpString(op) << "\n";
	
	//Enter();
}

void HighScriptEmitter::PushSystem(const FileLocation& loc, const PathIdentifier& id) {
	main << DBG_INDENT "PushSystem(" << LocArg(loc) << ", " << GetPartStringArray(id) << ");\n";
	
	Enter();
}

void HighScriptEmitter::PopSystem(const FileLocation& loc) {
	Leave();
	
	main << DBG_INDENT "PopSystem(" << LocArg(loc) << ");\n";
}

void HighScriptEmitter::PushPool(const FileLocation& loc, const PathIdentifier& id) {
	main << DBG_INDENT "PushSystem(" << LocArg(loc) << ", " << GetPartStringArray(id) << ");\n";
	
	Enter();
}

void HighScriptEmitter::PopPool(const FileLocation& loc) {
	Leave();
	
	main << DBG_INDENT "PopPool(" << LocArg(loc) << ");\n";
}

void HighScriptEmitter::PushEntity(const FileLocation& loc, const PathIdentifier& id) {
	main << DBG_INDENT "PushEntity(" << LocArg(loc) << ", " << GetPartStringArray(id) << ");\n";
	
	Enter();
}

void HighScriptEmitter::PopEntity(const FileLocation& loc) {
	Leave();
	
	main << DBG_INDENT "PopEntity(" << LocArg(loc) << ");\n";
}

void HighScriptEmitter::PushComponent(const FileLocation& loc, const PathIdentifier& id) {
	main << DBG_INDENT "PushComponent(" << LocArg(loc) << ", " << GetPartStringArray(id) << ");\n";
	
	Enter();
}

void HighScriptEmitter::PopComponent(const FileLocation& loc) {
	Leave();
	
	main << DBG_INDENT "PopComponent(" << LocArg(loc) << ");\n";
}

void HighScriptEmitter::PushMachine(const FileLocation& loc, const PathIdentifier& id) {
	main << DBG_INDENT "PushMachine(" << LocArg(loc) << ", " << GetPartStringArray(id) << ");\n";
	
	Enter();
}

void HighScriptEmitter::PopMachine(const FileLocation& loc) {
	Leave();
	
	main << DBG_INDENT "PopMachine(" << LocArg(loc) << ");\n";
}

void HighScriptEmitter::PushChain(const FileLocation& loc, const PathIdentifier& id) {
	main << DBG_INDENT "PushChain(" << LocArg(loc) << ", " << GetPartStringArray(id) << ");\n";
	
	Enter();
}

void HighScriptEmitter::PopChain(const FileLocation& loc) {
	Leave();
	
	main << DBG_INDENT "PopChain(" << LocArg(loc) << ");\n";
}

void HighScriptEmitter::PushLoop(const FileLocation& loc, const PathIdentifier& id) {
	main << DBG_INDENT "PushLoop(" << LocArg(loc) << ", " << GetPartStringArray(id) << ");\n";
	
	Enter();
}

void HighScriptEmitter::PopLoop(const FileLocation& loc) {
	Leave();
	
	main << DBG_INDENT "PopLoop(" << LocArg(loc) << ");\n";
}

void HighScriptEmitter::PushAtom(const FileLocation& loc, const PathIdentifier& id) {
	main << DBG_INDENT "PushAtom(" << LocArg(loc) << ", " << GetPartStringArray(id) << ");\n";
	
	Enter();
}

void HighScriptEmitter::PopAtom(const FileLocation& loc) {
	Leave();
	
	main << DBG_INDENT "PopAtom(" << LocArg(loc) << ");\n";
}

void HighScriptEmitter::PushAtomConnector(const FileLocation& loc, int part) {
	main << DBG_INDENT "PushAtomConnector(" << LocArg(loc) << ", " << IntStr(part) << ");\n";
	
	Enter();
}

void HighScriptEmitter::PopAtomConnector(const FileLocation& loc) {
	Leave();
	
	main << DBG_INDENT "PopAtomConnector(" << LocArg(loc) << ");\n";
}

void HighScriptEmitter::PushState(const FileLocation& loc, const PathIdentifier& id) {
	main << DBG_INDENT "PushState(" << LocArg(loc) << ", " << GetPartStringArray(id) << ");\n";
	
	Enter();
}

void HighScriptEmitter::PopState(const FileLocation& loc) {
	Leave();
	
	main << DBG_INDENT "PopState(" << LocArg(loc) << ");\n";
}

void HighScriptEmitter::PushCall(const FileLocation& loc) {
	main << DBG_INDENT "PushCall(" << LocArg(loc) << ");\n";
	
	Enter();
}

void HighScriptEmitter::PopCall(const FileLocation& loc) {
	Leave();
	
	main << DBG_INDENT "PopCall(" << LocArg(loc) << ");\n";
}

void HighScriptEmitter::PopExprCallArgument(const FileLocation& loc, int arg_i) {
	main << DBG_INDENT "PopExprCallArgument(" << LocArg(loc) << ", " << IntStr(arg_i) << ");\n";
	
	Enter();
}



NAMESPACE_TOPSIDE_END
