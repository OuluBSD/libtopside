#include "Backend.h"

NAMESPACE_TOPSIDE_BEGIN


AstBuilder::AstBuilder() :
	ErrorSource("AstBuilder")
{
	
}

void AstBuilder::Clear() {
	spath.Clear();
	root.Clear();
	
	InitDefault();
}

bool AstBuilder::Execute(String high_script_content) {
    ArrayMap<String, HiValue> global;
    
    Clear();
    
	try {
		HighCall(global, "AddFile(file)", THISBACK(HiAddFile));
		HighCall(global, "PushFunction(loc, ret_type, name)", THISBACK(HiPushFunction));
		HighCall(global, "Parameter(loc, type, name)", THISBACK(HiParameter));
		HighCall(global, "PopFunctionDefinition(loc)", THISBACK(HiPopFunctionDefinition));
		HighCall(global, "PopFunction(loc)", THISBACK(HiPopFunction));
		HighCall(global, "PushStatementList(loc)", THISBACK(HiPushStatementList));
		HighCall(global, "PopStatementList(loc)", THISBACK(HiPopStatementList));
		HighCall(global, "PushStatement(loc, type)", THISBACK(HiPushStatement));
		HighCall(global, "PopStatement(loc)", THISBACK(HiPopStatement));
		HighCall(global, "PushStatementParameter(loc, param_type)", THISBACK(HiPushStatementParameter));
		HighCall(global, "PopStatementParameter(loc)", THISBACK(HiPopStatementParameter));
		HighCall(global, "DeclareVariable(loc, n, id)", THISBACK(HiDeclareVariable));
		HighCall(global, "Variable(loc, n, id)", THISBACK(HiVariable));
		HighCall(global, "PushRvalResolve(loc, id, t)", THISBACK(HiPushRvalResolve));
		HighCall(global, "PushRvalArgumentList(loc)", THISBACK(HiPushRvalArgumentList));
		HighCall(global, "Argument(loc)", THISBACK(HiArgument));
		HighCall(global, "PopExpr(loc)", THISBACK(HiPopExpr));
		HighCall(global, "PushRval(loc, n)", THISBACK(HiPushRval));
		//HighCall(global, "PushRvalCall(loc, n)", THISBACK(HiPushRvalCall));
		HighCall(global, "PushRvalConstruct(loc, n)", THISBACK(HiPushRvalConstruct));
		HighCall(global, "PushRvalConstant(loc, t)", THISBACK(HiPushRvalConstant));
		HighCall(global, "Expr1(loc, op)", THISBACK(HiExpr1));
		HighCall(global, "Expr2(loc, op)", THISBACK(HiExpr2));
		HighCall(global, "Expr3(loc, op)", THISBACK(HiExpr3));
	    StdLib(global);
	
        Scan(global, high_script_content, "parser");
        HiValue ret = TS::Execute(global, "main", INT_MAX);
        DUMP(ret);
    }
    catch(Exc e) {
        LOG("ERROR: " << e << "\n");
        return false;
    }
    return true;
}

void AstBuilder::PushFunction(const FileLocation& loc, AstNode& ret_type, const PathIdentifier& name) {
	AstNode& var = DeclareRelative(name);
	var.src = SEMT_FUNCTION_STATIC;
	var.type = &ret_type;
	
	PushScope(var);
	
}

void AstBuilder::Parameter(const FileLocation& loc, const PathIdentifier& type, const PathIdentifier& name) {
	
	AstNode* tn = FindTypeDeclaration(type);
	if (!tn) {
		DUMP(type);
		AddError(loc, "internal error");
		return;
	}
	
	DUMP(name);
	AstNode& var = DeclareRelative(name);
	var.src = SEMT_PARAMETER;
	var.type = tn;
	var.locked = true;
}

/*void AstBuilder::PushFunctionDefinition(const FileLocation& loc) {
	AstNode& n = GetTopNode();
	
	AstNode* def = n.Find(FN_BLOCK_NAME);
	if (def) {
		AddError(loc, "function is already defined");
		return;
	}
	
	def = &n.Add(FN_BLOCK_NAME);
	def->src = SEMT_STATEMENT_BLOCK;
	
	PushScope(*def);
}*/

void AstBuilder::PopFunctionDefinition(const FileLocation& loc) {
	PopScope();
}

void AstBuilder::PopFunction(const FileLocation& loc) {
	PopScope();
}

void AstBuilder::PushStatementList(const FileLocation& loc) {
	AstNode& n = GetTopNode();
	AstNode& stmt = n.Add();
	stmt.src = SEMT_STATEMENT_BLOCK;
	
	PushScope(stmt);
}

void AstBuilder::PopStatementList(const FileLocation& loc) {
	PopScope();
}

void AstBuilder::PushStatement(const FileLocation& loc, StmtType type) {
	AstNode& n = GetTopNode();
	AstNode& stmt = n.Add();
	stmt.src = SEMT_STATEMENT;
	stmt.stmt = type;
	
	PushScope(stmt);
}

void AstBuilder::PopStatement(const FileLocation& loc) {
	PopScope();
}

void AstBuilder::PushStatementParameter(const FileLocation& loc, StmtParamType t) {
	String ts = GetStmtParamTypeString(t);
	
	AstNode& n = GetTopNode();
	AstNode& param = n.Add(ts);
	PushScope(param);
}

void AstBuilder::PopStatementParameter(const FileLocation& loc) {
	PopScope();
}

void AstBuilder::DeclareVariable(const FileLocation& loc, AstNode& type, const PathIdentifier& name) {
	AstNode& block = GetBlock();
	AstNode& var = Declare(block, name);
	var.src = SEMT_VARIABLE;
	var.type = &type;
	//DUMP(var.GetPath());
	ASSERT(!var.name.IsEmpty());
	
}

void AstBuilder::Variable(const FileLocation& loc, const AstNode& n, const PathIdentifier& id) {
	TODO
}

void AstBuilder::PushRvalResolve(const FileLocation& loc, const PathIdentifier& id, SemanticType t) {
	AstNode& n = GetTopNode();
	AstNode& r = n.Add();
	r.src = SEMT_RESOLVE;
	r.filter = t;
	/*ASSERT(id.part_count);
	for(int i = 0; i < id.part_count; i++)
		r.path.Add(id.parts[i]->str_value);*/
	DUMP(id);
	AstNode* d = FindDeclaration(id, t);
	if (!d) {
		AddError(loc, "could not find declaration '" + id.ToString() + "'");
		return;
	}
	r.link[0] = d;
	
	PushScopeRVal(*d);
}

void AstBuilder::PushRvalArgumentList(const FileLocation& loc) {
	AstNode& n = GetTopNode();
	AstNode& r = n.Add();
	r.src = SEMT_ARGUMENT_LIST;
	
	PushScopeRVal(r);
}

void AstBuilder::Argument(const FileLocation& loc) {
	int c = spath.GetCount();
	ASSERT(c > 2);
	AstNode& owner = *spath[c-2].n;
	AstNode& a = *spath[c-1].n;
	ASSERT(owner.src == SEMT_ARGUMENT_LIST);
	AstNode& arg = owner.Add();
	arg.src = SEMT_ARGUMENT;
	arg.link[0] = &a;
	PopScope();
}

/*void AstBuilder::PopExprScopeToCtor(const FileLocation& loc) {
	PopScope();
}*/

void AstBuilder::PopExpr(const FileLocation& loc) {
	PopScope();
}

void AstBuilder::PushRval(const FileLocation& loc, AstNode& n) {
	PushScopeRVal(n);
}

/*void AstBuilder::PushRvalCall(const FileLocation& loc, AstNode& n) {
	PushScopeRVal(n);
}*/

void AstBuilder::PushRvalConstruct(const FileLocation& loc, AstNode& n) {
	TODO
}

void AstBuilder::PushRvalConstant(const FileLocation& loc, const Token& t) {
	TODO
}

void AstBuilder::PushRvalConstant(const FileLocation& loc, int32 v) {
	AstNode& n = GetTopNode().Add();
	n.src = SEMT_CONSTANT;
	n.con = CONST_INT32;
	n.i64 = v;
	PushScope(n);
}

void AstBuilder::PushRvalConstant(const FileLocation& loc, int64 v) {
	AstNode& n = GetTopNode().Add();
	n.src = SEMT_CONSTANT;
	n.con = CONST_INT64;
	n.i64 = v;
	PushScope(n);
}

void AstBuilder::PushRvalConstant(const FileLocation& loc, double v) {
	AstNode& n = GetTopNode().Add();
	n.src = SEMT_CONSTANT;
	n.con = CONST_DOUBLE;
	n.dbl = v;
	PushScope(n);
}

void AstBuilder::PushRvalConstant(const FileLocation& loc, String v) {
	AstNode& n = GetTopNode().Add();
	n.src = SEMT_CONSTANT;
	n.con = CONST_STRING;
	n.str = v;
	PushScope(n);
}

void AstBuilder::Expr1(const FileLocation& loc, OpType op) {
	int c = spath.GetCount();
	ASSERT(c >= 2);
	AstNode* arg0 = spath[c-1].n;
	
	AstNode& owner = *spath[c-2].n;
	AstNode& expr = owner.Add();
	expr.src = SEMT_EXPR;
	expr.op = op;
	expr.link[0] = arg0;
	
	spath[c-1].n = &expr;
}

void AstBuilder::Expr2(const FileLocation& loc, OpType op) {
	int c = spath.GetCount();
	ASSERT(c >= 3);
	AstNode* arg0 = spath[c-2].n;
	AstNode* arg1 = spath[c-1].n;
	
	AstNode& owner = *spath[c-3].n;
	AstNode& expr = owner.Add();
	expr.src = SEMT_EXPR;
	expr.op = op;
	expr.link[0] = arg0;
	expr.link[1] = arg1;
	
	spath.SetCount(c-1);
	spath[c-2].n = &expr;
}

void AstBuilder::Expr3(const FileLocation& loc, OpType op) {
	int c = spath.GetCount();
	ASSERT(c >= 4);
	AstNode* arg0 = spath[c-3].n;
	AstNode* arg1 = spath[c-2].n;
	AstNode* arg2 = spath[c-1].n;
	
	AstNode& owner = *spath[c-4].n;
	AstNode& expr = owner.Add();
	expr.src = SEMT_EXPR;
	expr.op = op;
	expr.link[0] = arg0;
	expr.link[1] = arg1;
	expr.link[2] = arg2;
	
	spath.SetCount(c-2);
	spath[c-3].n = &expr;
}





void AstBuilder::LoadLocation(const HiValue& v, FileLocation& loc) {
	int f = v[0];
	loc.line = v[1];
	loc.col = v[2];
	loc.file = f >= 0 && f < files.GetCount() ? files[f] : String();
}

void AstBuilder::LoadPath(const FileLocation& loc, const HiValue& v, PathIdentifier& id, Vector<Token>& tokens) {
	id.part_count = v.GetCount();
	int c = id.part_count * 2 - 1;
	ASSERT(c > 0);
	tokens.SetCount(c);
	for(int i = 0, j = 0; i < c; i++) {
		Token& t = tokens[i];
		t.loc = loc;
		if (i % 2 == 0) {
			const HiValue& v0 = v.ArrayGet(j);
			id.parts[j] = &t;
			t.type = TK_ID;
			t.str_value = (String)v0;
			j++;
		}
		else {
			t.type = '.';
		}
	}
	id.begin = tokens.Begin();
	id.end = tokens.End();
}

void AstBuilder::HiAddFile(HiEscape& e) {
	String file = e[0];
	files.Add(file);
}

void AstBuilder::HiPushFunction(HiEscape& e) {
	FileLocation loc;
	LoadLocation(e[0], loc);
	
	PathIdentifier type, name;
	LoadPath(loc, e[1], type, tokens[0]);
	LoadPath(loc, e[2], name, tokens[1]);
	
	//DUMP(loc); DUMP(name); DUMP(type);
	
	AstNode* tn = FindTypeDeclaration(type);
	if (!tn) {
		DUMP(type);
		AddError(loc, "type '" + type.ToString() + "' not found");
		return;
	}
	
	PushFunction(loc, *tn, name);
}

void AstBuilder::HiParameter(HiEscape& e) {
	FileLocation loc;
	LoadLocation(e[0], loc);
	
	PathIdentifier type, name;
	LoadPath(loc, e[1], type, tokens[0]);
	LoadPath(loc, e[2], name, tokens[1]);
	
	Parameter(loc, type, name);
}

/*void AstBuilder::HiPushFunctionDefinition(HiEscape& e) {
	FileLocation loc;
	LoadLocation(e[0], loc);
	
	PushFunctionDefinition(loc);
}*/

void AstBuilder::HiPopFunctionDefinition(HiEscape& e) {
	FileLocation loc;
	LoadLocation(e[0], loc);
	
	PopFunctionDefinition(loc);
}

void AstBuilder::HiPopFunction(HiEscape& e) {
	FileLocation loc;
	LoadLocation(e[0], loc);
	
	PopFunction(loc);
}

void AstBuilder::HiPushStatementList(HiEscape& e) {
	FileLocation loc;
	LoadLocation(e[0], loc);
	
	PushStatementList(loc);
}

void AstBuilder::HiPopStatementList(HiEscape& e) {
	FileLocation loc;
	LoadLocation(e[0], loc);
	
	PopStatementList(loc);
}

void AstBuilder::HiPushStatement(HiEscape& e) {
	FileLocation loc;
	LoadLocation(e[0], loc);
	
	StmtType t = (StmtType)(int)e[1];
	PushStatement(loc, t);
}

void AstBuilder::HiPopStatement(HiEscape& e) {
	FileLocation loc;
	LoadLocation(e[0], loc);
	
	PopStatement(loc);
}

void AstBuilder::HiPushStatementParameter(HiEscape& e) {
	FileLocation loc;
	LoadLocation(e[0], loc);
	StmtParamType t = (StmtParamType)(int)e[1];
	
	PushStatementParameter(loc, t);
}

void AstBuilder::HiPopStatementParameter(HiEscape& e) {
	FileLocation loc;
	LoadLocation(e[0], loc);
	
	PopStatementParameter(loc);
}

void AstBuilder::HiDeclareVariable(HiEscape& e) {
	FileLocation loc;
	LoadLocation(e[0], loc);
	
	PathIdentifier type, name;
	LoadPath(loc, e[1], type, tokens[0]);
	LoadPath(loc, e[2], name, tokens[1]);
	
	//DUMP(type)
	AstNode* tn = FindTypeDeclaration(type);
	if (!tn) {
		DUMP(type);
		AddError(loc, "type '" + type.ToString() + "' not found");
		return;
	}
	
	DeclareVariable(loc, *tn, name);
}

void AstBuilder::HiVariable(HiEscape& e) {
	TODO
}

void AstBuilder::HiPushRvalResolve(HiEscape& e) {
	FileLocation loc;
	LoadLocation(e[0], loc);
	
	PathIdentifier name;
	LoadPath(loc, e[1], name, tokens[0]);
	
	SemanticType t = (SemanticType)(int)e[2];
	
	PushRvalResolve(loc, name, t);
}

void AstBuilder::HiPushRvalArgumentList(HiEscape& e) {
	FileLocation loc;
	LoadLocation(e[0], loc);
	
	PushRvalArgumentList(loc);
}

void AstBuilder::HiArgument(HiEscape& e) {
	FileLocation loc;
	LoadLocation(e[0], loc);
	
	Argument(loc);
}

/*void AstBuilder::HiPopExprScopeToCtor(HiEscape& e) {
	FileLocation loc;
	LoadLocation(e[0], loc);
	
	PopExprScopeToCtor(loc);
}*/

void AstBuilder::HiPopExpr(HiEscape& e) {
	FileLocation loc;
	LoadLocation(e[0], loc);
	
	PopExpr(loc);
}

void AstBuilder::HiPushRval(HiEscape& e) {
	FileLocation loc;
	LoadLocation(e[0], loc);
	
	PathIdentifier name;
	LoadPath(loc, e[1], name, tokens[0]);
	
	AstNode* nn = FindDeclaration(name, SEMT_FIELD);
	if (!nn) {
		DUMP(GetPathString());
		DUMP(name);
		LOG(GetRoot().GetTreeString());
		AddError(loc, "'" + name.ToString() + "' not found");
		TODO
		return;
	}
	
	PushRval(loc, *nn);
}

/*void AstBuilder::HiPushRvalCall(HiEscape& e) {
	FileLocation loc;
	LoadLocation(e[0], loc);
	
	PathIdentifier name;
	LoadPath(loc, e[1], name, tokens[0]);
	
	AstNode* fn = FindDeclaration(name, SEMT_FUNCTION);
	if (!fn) {
		AddError(loc, "function '" + name.ToString() + "' not found");
		return;
	}
	
	PushRvalCall(loc, *fn);
}*/

void AstBuilder::HiPushRvalConstruct(HiEscape& e) {
	TODO
}

void AstBuilder::HiPushRvalConstant(HiEscape& e) {
	FileLocation loc;
	LoadLocation(e[0], loc);
	
	HiValue& v = e[1];
	if (v.IsInt())
		PushRvalConstant(loc, v.GetInt());
	else if (v.IsInt64())
		PushRvalConstant(loc, v.GetInt64());
	else if (v.IsNumber())
		PushRvalConstant(loc, v.GetNumber());
	else
		PushRvalConstant(loc, (String)v);
	
}

void AstBuilder::HiExpr1(HiEscape& e) {
	FileLocation loc;
	LoadLocation(e[0], loc);
	OpType op = (OpType)(int)e[1];
	
	Expr1(loc, op);
}

void AstBuilder::HiExpr2(HiEscape& e) {
	FileLocation loc;
	LoadLocation(e[0], loc);
	OpType op = (OpType)(int)e[1];
	
	Expr2(loc, op);
}

void AstBuilder::HiExpr3(HiEscape& e) {
	FileLocation loc;
	LoadLocation(e[0], loc);
	OpType op = (OpType)(int)e[1];
	
	Expr3(loc, op);
}




NAMESPACE_TOPSIDE_END
