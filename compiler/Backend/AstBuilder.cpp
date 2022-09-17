#include "Backend.h"


NAMESPACE_TOPSIDE_BEGIN



/*void SemanticParser::Clear() {
	spath.Clear();
	root.Clear();
	fail = false;
	
	InitDefault();
}

void SemanticParser::AddError(const FileLocation& loc, String msg) {
	ErrorSource::AddError(loc, msg);
	flag.SetNotRunning();
	fail = true;
}*/

void SemanticParser::PushClass(const FileLocation& loc, const PathIdentifier& name) {
	AstNode& var = DeclareRelative(name);
	var.src = SEMT_CLASS;
	
	PushScope(var);
	
}

void SemanticParser::PopClass(const FileLocation& loc) {
	PopScope();
}

void SemanticParser::PushFunction(const FileLocation& loc, AstNode& ret_type, const PathIdentifier& name) {
	AstNode& var = DeclareRelative(name);
	var.src = SEMT_FUNCTION_STATIC;
	var.type = &ret_type;
	
	PushScope(var);
	
}

void SemanticParser::PushMetaFunction(const FileLocation& loc, AstNode& ret_type, const PathIdentifier& name) {
	AstNode& var = DeclareRelative(name);
	var.src = SEMT_META_FUNCTION_STATIC;
	var.type = &ret_type;
	
	PushScope(var);
	
}

void SemanticParser::Parameter(const FileLocation& loc, const PathIdentifier& type, const PathIdentifier& name) {
	
	AstNode* tn = FindDeclaration(type, SEMT_TYPE);
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

void SemanticParser::MetaParameter(const FileLocation& loc, const PathIdentifier& type, const PathIdentifier& name) {
	AstNode* tn = FindDeclaration(type, SEMT_TYPE);
	if (!tn) {
		AddError(loc, "internal error");
		return;
	}
	
	AstNode& var = DeclareRelative(name);
	var.src = SEMT_META_PARAMETER;
	var.type = tn;
	var.locked = true;
}

/*void SemanticParser::PushFunctionDefinition(const FileLocation& loc) {
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

void SemanticParser::PopFunctionDefinition(const FileLocation& loc) {
	PopScope();
}

void SemanticParser::PopFunction(const FileLocation& loc) {
	PopScope();
}

void SemanticParser::PopMetaFunction(const FileLocation& loc) {
	PopScope();
}

void SemanticParser::PushStatementList(const FileLocation& loc) {
	AstNode& n = GetTopNode();
	AstNode& stmt = n.Add(loc);
	stmt.src = SEMT_STATEMENT_BLOCK;
	
	PushScope(stmt);
}

void SemanticParser::PopStatementList(const FileLocation& loc) {
	PopScope();
}

void SemanticParser::PushStatement(const FileLocation& loc, StmtType type) {
	AstNode& n = GetTopNode();
	AstNode& stmt = n.Add(loc);
	stmt.src = SEMT_STATEMENT;
	stmt.stmt = type;
	
	PushScope(stmt);
}

void SemanticParser::PopStatement(const FileLocation& loc) {
	PopScope();
}

void SemanticParser::PushConstructor(const FileLocation& loc, AstNode& type, AstNode* var) {
	AstNode& n = GetTopNode();
	AstNode& stmt = n.Add(loc);
	stmt.src = SEMT_CTOR;
	stmt.type = &type;
	stmt.link[0] = var;
	
	ASSERT(var->link[0] == 0);
	var->link[0] = &stmt;
	
	PushScope(stmt);
}

void SemanticParser::PopConstructor(const FileLocation& loc) {
	PopScope();
}

void SemanticParser::PushStatementParameter(const FileLocation& loc, StmtParamType t) {
	String ts = GetStmtParamTypeString(t);
	
	AstNode& n = GetTopNode();
	AstNode& param = n.Add(loc, ts);
	PushScope(param);
}

void SemanticParser::PopStatementParameter(const FileLocation& loc) {
	PopScope();
}

AstNode* SemanticParser::DeclareVariable(const FileLocation& loc, AstNode& type, const PathIdentifier& name) {
	AstNode& block = GetBlock();
	AstNode& var = Declare(block, name, true);
	if (!var.IsPartially(SEMT_UNDEFINED)) {
		AddError(loc, "'" + name.ToString() + "' is already declared");
		return 0;
	}
	bool meta = type.IsPartially(SEMT_META_TYPE);
	var.src = meta ? SEMT_META_VARIABLE : SEMT_VARIABLE;
	var.type = &type;
	//DUMP(var.GetPath());
	ASSERT(!var.name.IsEmpty());
	
	return &var;
}

void SemanticParser::DeclareMetaVariable(const FileLocation& loc, AstNode& type, const PathIdentifier& name) {
	AstNode& block = GetBlock();
	AstNode& var = Declare(block, name);
	var.src = SEMT_META_VARIABLE;
	var.type = &type;
	//DUMP(var.GetPath());
	ASSERT(!var.name.IsEmpty());
	
}

void SemanticParser::Variable(const FileLocation& loc, const AstNode& n, const PathIdentifier& id) {
	TODO
}

void SemanticParser::PushRvalResolve(const FileLocation& loc, const PathIdentifier& id, SemanticType t) {
	AstNode& n = GetTopNode();
	AstNode& r = n.Add(loc);
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
	r.str = id.ToString();
	
	PushScopeRVal(r);
}

void SemanticParser::PushRvalUnresolved(const FileLocation& loc, const PathIdentifier& id, SemanticType t) {
	AstNode& n = GetTopNode();
	AstNode& r = n.Add(loc);
	r.src = SEMT_UNRESOLVED;
	r.filter = t;
	r.str = id.ToString();
	
	PushScopeRVal(r);
}

void SemanticParser::PushRvalArgumentList(const FileLocation& loc) {
	AstNode& n = GetTopNode();
	AstNode& r = n.Add(loc);
	r.src = SEMT_ARGUMENT_LIST;
	
	PushScopeRVal(r);
}

void SemanticParser::Argument(const FileLocation& loc) {
	int c = spath.GetCount();
	ASSERT(c > 2);
	AstNode& owner = *spath[c-2].n;
	AstNode& a = *spath[c-1].n;
	ASSERT(owner.src == SEMT_ARGUMENT_LIST);
	AstNode& arg = owner.Add(loc);
	arg.src = SEMT_ARGUMENT;
	arg.link[0] = &a;
	PopScope();
}

void SemanticParser::ArraySize(const FileLocation& loc) {
	int c = spath.GetCount();
	ASSERT(c > 2);
	AstNode& owner = *spath[c-2].n;
	AstNode& a = *spath[c-1].n;
	ASSERT(owner.src == SEMT_CTOR);
	AstNode& arg = owner.Add(loc);
	arg.src = SEMT_ARRAYSIZE;
	arg.link[0] = &a;
	PopScope();
}

/*void SemanticParser::PopExprScopeToCtor(const FileLocation& loc) {
	PopScope();
}*/

void SemanticParser::PopExpr(const FileLocation& loc) {
	PopScope();
}

void SemanticParser::PushRval(const FileLocation& loc, AstNode& n) {
	AstNode& t = GetTopNode();
	AstNode& r = t.Add(loc);
	r.src = SEMT_RVAL;
	r.link[0] = &n;
	
	PushScopeRVal(r);
}

/*void SemanticParser::PushRvalCall(const FileLocation& loc, AstNode& n) {
	PushScopeRVal(n);
}*/

void SemanticParser::PushRvalConstruct(const FileLocation& loc, AstNode& n) {
	TODO
}

void SemanticParser::PushRvalConstant(const FileLocation& loc, const Token& t) {
	TODO
}

void SemanticParser::PushRvalConstant(const FileLocation& loc, bool v) {
	AstNode& n = GetTopNode().Add(loc);
	n.src = SEMT_CONSTANT;
	n.con = CONST_BOOL;
	n.i64 = v;
	PushScope(n);
}

void SemanticParser::PushRvalConstant(const FileLocation& loc, int32 v) {
	AstNode& n = GetTopNode().Add(loc);
	n.src = SEMT_CONSTANT;
	n.con = CONST_INT32;
	n.i64 = v;
	PushScope(n);
}

void SemanticParser::PushRvalConstant(const FileLocation& loc, int64 v) {
	AstNode& n = GetTopNode().Add(loc);
	n.src = SEMT_CONSTANT;
	n.con = CONST_INT64;
	n.i64 = v;
	PushScope(n);
}

void SemanticParser::PushRvalConstant(const FileLocation& loc, double v) {
	AstNode& n = GetTopNode().Add(loc);
	n.src = SEMT_CONSTANT;
	n.con = CONST_DOUBLE;
	n.dbl = v;
	PushScope(n);
}

void SemanticParser::PushRvalConstant(const FileLocation& loc, String v) {
	AstNode& n = GetTopNode().Add(loc);
	n.src = SEMT_CONSTANT;
	n.con = CONST_STRING;
	n.str = v;
	PushScope(n);
}

void SemanticParser::Expr1(const FileLocation& loc, OpType op) {
	int c = spath.GetCount();
	ASSERT(c >= 2);
	AstNode* arg0 = spath[c-1].n;
	
	AstNode& owner = *spath[c-2].n;
	AstNode& expr = owner.Add(loc);
	expr.src = SEMT_EXPR;
	expr.op = op;
	expr.link[0] = arg0;
	
	spath[c-1].n = &expr;
}

void SemanticParser::Expr2(const FileLocation& loc, OpType op) {
	int c = spath.GetCount();
	ASSERT(c >= 3);
	AstNode* arg0 = spath[c-2].n;
	AstNode* arg1 = spath[c-1].n;
	
	AstNode& owner = *spath[c-3].n;
	AstNode& expr = owner.Add(loc);
	expr.src = SEMT_EXPR;
	expr.op = op;
	expr.link[0] = arg0;
	expr.link[1] = arg1;
	
	spath.SetCount(c-1);
	spath[c-2].n = &expr;
}

void SemanticParser::Expr3(const FileLocation& loc, OpType op) {
	int c = spath.GetCount();
	ASSERT(c >= 4);
	AstNode* arg0 = spath[c-3].n;
	AstNode* arg1 = spath[c-2].n;
	AstNode* arg2 = spath[c-1].n;
	
	AstNode& owner = *spath[c-4].n;
	AstNode& expr = owner.Add(loc);
	expr.src = SEMT_EXPR;
	expr.op = op;
	expr.link[0] = arg0;
	expr.link[1] = arg1;
	expr.link[2] = arg2;
	
	spath.SetCount(c-2);
	spath[c-3].n = &expr;
}

void SemanticParser::PushSystem(const FileLocation& loc, const PathIdentifier& id) {
	AstNode& var = DeclareRelative(id);
	var.src = SEMT_SYSTEM;
	
	PushScope(var);
	
}

void SemanticParser::PopSystem(const FileLocation& loc) {
	PopScope();
}

void SemanticParser::PushPool(const FileLocation& loc, const PathIdentifier& id) {
	AstNode& var = DeclareRelative(id);
	var.src = SEMT_POOL;
	
	PushScope(var);
	
}

void SemanticParser::PopPool(const FileLocation& loc) {
	PopScope();
}

void SemanticParser::PushEntity(const FileLocation& loc, const PathIdentifier& id) {
	AstNode& var = DeclareRelative(id);
	var.src = SEMT_ENTITY;
	
	PushScope(var);
	
}

void SemanticParser::PopEntity(const FileLocation& loc) {
	PopScope();
}

void SemanticParser::PushComponent(const FileLocation& loc, const PathIdentifier& id) {
	AstNode& var = DeclareRelative(id);
	var.src = SEMT_COMPONENT;
	
	PushScope(var);
	
}

void SemanticParser::PopComponent(const FileLocation& loc) {
	PopScope();
}

void SemanticParser::PushMachine(const FileLocation& loc, const PathIdentifier& id) {
	AstNode& var = DeclareRelative(id);
	var.src = SEMT_MACHINE;
	
	PushScope(var);
	
}

void SemanticParser::PopMachine(const FileLocation& loc) {
	PopScope();
}

void SemanticParser::PushChain(const FileLocation& loc, const PathIdentifier& id) {
	AstNode& var = DeclareRelative(id);
	var.src = SEMT_CHAIN;
	
	PushScope(var);
	
}

void SemanticParser::PopChain(const FileLocation& loc) {
	PopScope();
}

void SemanticParser::PushLoop(const FileLocation& loc, const PathIdentifier& id) {
	AstNode& var = DeclareRelative(id);
	var.src = SEMT_LOOP;
	
	PushScope(var);
	
}

void SemanticParser::PopLoop(const FileLocation& loc) {
	PopScope();
}

void SemanticParser::PushAtom(const FileLocation& loc, const PathIdentifier& id) {
	AstNode& var = DeclareRelative(id);
	var.src = SEMT_ATOM;
	
	PushScope(var);
	
}

void SemanticParser::PopAtom(const FileLocation& loc) {
	PopScope();
}

void SemanticParser::PushAtomConnector(const FileLocation& loc, int part) {
	int c = spath.GetCount();
	String str;
	switch (part) {
		case 0: str = "sink"; break;
		case 1: str = "src"; break;
		default: str = IntStr(part);
	}
	AstNode& owner = *spath[c-1].n;
	AstNode& var = owner.Add(loc, str);
	var.src = SEMT_STATEMENT;
	var.stmt = STMT_ATOM_CONNECTOR;
	
	PushScope(var);
	
}

void SemanticParser::PopAtomConnector(const FileLocation& loc) {
	PopScope();
}

void SemanticParser::PushState(const FileLocation& loc, const PathIdentifier& id) {
	AstNode& var = DeclareRelative(id);
	var.src = SEMT_STATEMENT;
	var.stmt = STMT_STATE;
	
	PushScope(var);
	
}

void SemanticParser::PopState(const FileLocation& loc) {
	PopScope();
}

void SemanticParser::PushCall(const FileLocation& loc) {
	int c = spath.GetCount();
	AstNode& owner = *spath[c-1].n;
	AstNode& var = owner.Add(loc);
	var.src = SEMT_EXPR;
	var.op = OP_CALL;
	
	PushScope(var);
	
}

void SemanticParser::PopCall(const FileLocation& loc) {
	PopScope();
}

void SemanticParser::PopExprCallArgument(const FileLocation& loc, int arg_i) {
	int c = spath.GetCount();
	ASSERT(c >= 2);
	AstNode* arg0 = spath[c-1].n;
	
	AstNode& owner = *spath[c-2].n;
	AstNode& expr = owner.Add(loc);
	expr.src = SEMT_CALL_ARG;
	expr.link[0] = arg0;
	
	spath.SetCount(c-1);
}








#if 0

void SemanticParser::LoadLocation(const HiValue& v, FileLocation& loc) {
	int f = v[0];
	loc.line = v[1];
	loc.col = v[2];
	loc.file = f >= 0 && f < files.GetCount() ? files[f] : String();
}

void SemanticParser::LoadPath(const FileLocation& loc, const HiValue& v, PathIdentifier& id, Vector<Token>& tokens) {
	id.Clear();
	id.part_count = v.GetCount();
	int c = id.part_count * 2 - 1;
	ASSERT(c > 0);
	tokens.Reserve(c);
	tokens.SetCount(0);
	bool head = false;
	for(int i = 0, j = 0, k = 0; i < id.part_count; i++) {
		const HiValue& v0 = v.ArrayGet(i);
		String str = (String)v0;
		int c = str.GetCount();
		if (!c) {
			ASSERT(0);
			continue;
		}
		int chr = str[0];
		if (c == 1 && (chr == '#' || chr == '&')) {
			Token& t = tokens.Add();
			t.loc = loc;
			t.type = chr;
			id.parts[k++] = &t;
			if (i == 0) head = true;
			if (head) {
				id.head[id.head_count++] = chr == '#' ? PathIdentifier::PTR : PathIdentifier::LREF;
			}
			else {
				id.tail[id.tail_count++] = chr == '#' ? PathIdentifier::PTR : PathIdentifier::LREF;
			}
		}
		else {
			if (j) {
				Token& t = tokens.Add();
				t.loc = loc;
				t.type = '.';
				//id.parts[k++] = &t;
			}
			Token& t = tokens.Add();
			t.loc = loc;
			t.type = TK_ID;
			t.str_value = str;
			if (chr == '$') {
				t.str_value = t.str_value.Mid(1);
				id.is_meta[k] = true;
			}
			j++;
			id.parts[k++] = &t;
		}
	}
	id.begin = tokens.Begin();
	id.end = tokens.End();
}


void SemanticParser::HiAddFile(HiEscape& e) {
	String file = e[0];
	files.Add(file);
}

void SemanticParser::HiPushClass(HiEscape& e) {
	FileLocation loc;
	LoadLocation(e[0], loc);
	
	PathIdentifier name;
	LoadPath(loc, e[1], name, tokens[0]);
	
	//DUMP(loc); DUMP(name); DUMP(type);
	
	PushClass(loc, name);
}

void SemanticParser::HiPopClass(HiEscape& e) {
	FileLocation loc;
	LoadLocation(e[0], loc);
	
	PopClass(loc);
}

void SemanticParser::HiPushFunction(HiEscape& e) {
	FileLocation loc;
	LoadLocation(e[0], loc);
	
	PathIdentifier type, name;
	LoadPath(loc, e[1], type, tokens[0]);
	LoadPath(loc, e[2], name, tokens[1]);
	
	//DUMP(loc); DUMP(name); DUMP(type);
	
	AstNode* tn = FindDeclaration(type, SEMT_TYPE);
	if (!tn) {
		DUMP(type);
		AddError(loc, "type '" + type.ToString() + "' not found");
		return;
	}
	
	PushFunction(loc, *tn, name);
}

void SemanticParser::HiPushMetaFunction(HiEscape& e) {
	FileLocation loc;
	LoadLocation(e[0], loc);
	
	PathIdentifier type, name;
	LoadPath(loc, e[1], type, tokens[0]);
	LoadPath(loc, e[2], name, tokens[1]);
	
	//DUMP(loc); DUMP(name); DUMP(type);
	
	AstNode* tn = FindDeclaration(type, SEMT_META_TYPE);
	if (!tn) {
		DUMP(type);
		AddError(loc, "type '" + type.ToString() + "' not found");
		return;
	}
	
	PushMetaFunction(loc, *tn, name);
}

void SemanticParser::HiParameter(HiEscape& e) {
	FileLocation loc;
	LoadLocation(e[0], loc);
	
	PathIdentifier type, name;
	LoadPath(loc, e[1], type, tokens[0]);
	LoadPath(loc, e[2], name, tokens[1]);
	
	Parameter(loc, type, name);
}

void SemanticParser::HiMetaParameter(HiEscape& e) {
	FileLocation loc;
	LoadLocation(e[0], loc);
	
	PathIdentifier type, name;
	LoadPath(loc, e[1], type, tokens[0]);
	LoadPath(loc, e[2], name, tokens[1]);
	
	MetaParameter(loc, type, name);
}

/*void SemanticParser::HiPushFunctionDefinition(HiEscape& e) {
	FileLocation loc;
	LoadLocation(e[0], loc);
	
	PushFunctionDefinition(loc);
}*/

void SemanticParser::HiPopFunctionDefinition(HiEscape& e) {
	FileLocation loc;
	LoadLocation(e[0], loc);
	
	PopFunctionDefinition(loc);
}

void SemanticParser::HiPopFunction(HiEscape& e) {
	FileLocation loc;
	LoadLocation(e[0], loc);
	
	PopFunction(loc);
}

void SemanticParser::HiPopMetaFunction(HiEscape& e) {
	FileLocation loc;
	LoadLocation(e[0], loc);
	
	PopFunction(loc);
}

void SemanticParser::HiPushStatementList(HiEscape& e) {
	FileLocation loc;
	LoadLocation(e[0], loc);
	
	PushStatementList(loc);
}

void SemanticParser::HiPopStatementList(HiEscape& e) {
	FileLocation loc;
	LoadLocation(e[0], loc);
	
	PopStatementList(loc);
}

void SemanticParser::HiPushStatement(HiEscape& e) {
	FileLocation loc;
	LoadLocation(e[0], loc);
	
	StmtType t = (StmtType)(int)e[1];
	PushStatement(loc, t);
}

void SemanticParser::HiPopStatement(HiEscape& e) {
	FileLocation loc;
	LoadLocation(e[0], loc);
	
	PopStatement(loc);
}

void SemanticParser::HiPushConstructor(HiEscape& e) {
	FileLocation loc;
	LoadLocation(e[0], loc);
	
	PathIdentifier type, name;
	LoadPath(loc, e[1], type, tokens[0]);
	
	AstNode* tn = FindDeclaration(type, SEMT_TYPE);
	if (!tn) {
		AddError(loc, "type '" + type.ToString() + "' not found");
		return;
	}
	
	AstNode* var = 0;
	
	HiValue arg2 = e[2];
	if (arg2.IsInt()) {
		// pass
	}
	else {
		LoadPath(loc, e[2], name, tokens[1]);
		var = FindDeclaration(name, SEMT_FIELD);
		if (!var) {
			AddError(loc, "variable '" + name.ToString() + "' not found");
			return;
		}
	}
	
	PushConstructor(loc, *tn, var);
}

void SemanticParser::HiPopConstructor(HiEscape& e) {
	FileLocation loc;
	LoadLocation(e[0], loc);
	
	PopConstructor(loc);
}

void SemanticParser::HiPushStatementParameter(HiEscape& e) {
	FileLocation loc;
	LoadLocation(e[0], loc);
	StmtParamType t = (StmtParamType)(int)e[1];
	
	PushStatementParameter(loc, t);
}

void SemanticParser::HiPopStatementParameter(HiEscape& e) {
	FileLocation loc;
	LoadLocation(e[0], loc);
	
	PopStatementParameter(loc);
}

void SemanticParser::HiDeclareVariable(HiEscape& e) {
	FileLocation loc;
	LoadLocation(e[0], loc);
	
	PathIdentifier type, name;
	LoadPath(loc, e[1], type, tokens[0]);
	LoadPath(loc, e[2], name, tokens[1]);
	
	//DUMP(type)
	AstNode* tn = FindDeclaration(type, SEMT_TYPE);
	if (!tn) {
		DUMP(type);
		AddError(loc, "type '" + type.ToString() + "' not found");
		return;
	}
	
	DeclareVariable(loc, *tn, name);
}

void SemanticParser::HiDeclareMetaVariable(HiEscape& e) {
	FileLocation loc;
	LoadLocation(e[0], loc);
	
	PathIdentifier type, name;
	LoadPath(loc, e[1], type, tokens[0]);
	LoadPath(loc, e[2], name, tokens[1]);
	
	//DUMP(type)
	AstNode* tn = FindDeclaration(type, SEMT_META_TYPE);
	if (!tn) {
		DUMP(type);
		AddError(loc, "type '" + type.ToString() + "' not found");
		return;
	}
	
	DeclareMetaVariable(loc, *tn, name);
}

void SemanticParser::HiVariable(HiEscape& e) {
	TODO
}

void SemanticParser::HiPushRvalResolve(HiEscape& e) {
	FileLocation loc;
	LoadLocation(e[0], loc);
	
	PathIdentifier name;
	LoadPath(loc, e[1], name, tokens[0]);
	
	SemanticType t = (SemanticType)(int)e[2];
	
	PushRvalResolve(loc, name, t);
}

void SemanticParser::HiPushRvalUnresolved(HiEscape& e) {
	FileLocation loc;
	LoadLocation(e[0], loc);
	
	PathIdentifier name;
	LoadPath(loc, e[1], name, tokens[0]);
	
	SemanticType t = (SemanticType)(int)e[2];
	
	PushRvalUnresolved(loc, name, t);
}

void SemanticParser::HiPushRvalArgumentList(HiEscape& e) {
	FileLocation loc;
	LoadLocation(e[0], loc);
	
	PushRvalArgumentList(loc);
}

void SemanticParser::HiArgument(HiEscape& e) {
	FileLocation loc;
	LoadLocation(e[0], loc);
	
	Argument(loc);
}

void SemanticParser::HiArraySize(HiEscape& e) {
	FileLocation loc;
	LoadLocation(e[0], loc);
	
	ArraySize(loc);
}

/*void SemanticParser::HiPopExprScopeToCtor(HiEscape& e) {
	FileLocation loc;
	LoadLocation(e[0], loc);
	
	PopExprScopeToCtor(loc);
}*/

void SemanticParser::HiPopExpr(HiEscape& e) {
	FileLocation loc;
	LoadLocation(e[0], loc);
	
	PopExpr(loc);
}

void SemanticParser::HiPushRval(HiEscape& e) {
	FileLocation loc;
	LoadLocation(e[0], loc);
	
	PathIdentifier name;
	LoadPath(loc, e[1], name, tokens[0]);
	
	AstNode* nn = FindDeclaration(name, (SemanticType)(SEMT_FIELD | SEMT_FUNCTION | SEMT_TYPE));
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

/*void SemanticParser::HiPushRvalCall(HiEscape& e) {
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

void SemanticParser::HiPushRvalConstruct(HiEscape& e) {
	TODO
}

void SemanticParser::HiPushRvalConstant(HiEscape& e) {
	FileLocation loc;
	LoadLocation(e[0], loc);
	
	HiValue& v = e[1];
	if (v.IsDouble())
		PushRvalConstant(loc, v.GetNumber());
	else if (v.IsInt())
		PushRvalConstant(loc, v.GetInt());
	else if (v.IsInt64())
		PushRvalConstant(loc, v.GetInt64());
	else
		PushRvalConstant(loc, (String)v);
	
}

void SemanticParser::HiExpr1(HiEscape& e) {
	FileLocation loc;
	LoadLocation(e[0], loc);
	OpType op = (OpType)(int)e[1];
	
	Expr1(loc, op);
}

void SemanticParser::HiExpr2(HiEscape& e) {
	FileLocation loc;
	LoadLocation(e[0], loc);
	OpType op = (OpType)(int)e[1];
	
	Expr2(loc, op);
}

void SemanticParser::HiExpr3(HiEscape& e) {
	FileLocation loc;
	LoadLocation(e[0], loc);
	OpType op = (OpType)(int)e[1];
	
	Expr3(loc, op);
}

void SemanticParser::HiPushSystem(HiEscape& e) {
	FileLocation loc;
	LoadLocation(e[0], loc);
	
	PathIdentifier name;
	LoadPath(loc, e[1], name, tokens[0]);
	
	PushSystem(loc, name);
}

void SemanticParser::HiPopSystem(HiEscape& e) {
	FileLocation loc;
	LoadLocation(e[0], loc);
	
	PopSystem(loc);
}

void SemanticParser::HiPushPool(HiEscape& e) {
	FileLocation loc;
	LoadLocation(e[0], loc);
	
	PathIdentifier name;
	LoadPath(loc, e[1], name, tokens[0]);
	
	PushPool(loc, name);
}

void SemanticParser::HiPopPool(HiEscape& e) {
	FileLocation loc;
	LoadLocation(e[0], loc);
	
	PopPool(loc);
}

void SemanticParser::HiPushEntity(HiEscape& e) {
	FileLocation loc;
	LoadLocation(e[0], loc);
	
	PathIdentifier name;
	LoadPath(loc, e[1], name, tokens[0]);
	
	PushEntity(loc, name);
}

void SemanticParser::HiPopEntity(HiEscape& e) {
	FileLocation loc;
	LoadLocation(e[0], loc);
	
	PopEntity(loc);
}

void SemanticParser::HiPushComponent(HiEscape& e) {
	FileLocation loc;
	LoadLocation(e[0], loc);
	
	PathIdentifier name;
	LoadPath(loc, e[1], name, tokens[0]);
	
	PushComponent(loc, name);
}

void SemanticParser::HiPopComponent(HiEscape& e) {
	FileLocation loc;
	LoadLocation(e[0], loc);
	
	PopComponent(loc);
}

void SemanticParser::HiPushMachine(HiEscape& e) {
	FileLocation loc;
	LoadLocation(e[0], loc);
	
	PathIdentifier name;
	LoadPath(loc, e[1], name, tokens[0]);
	
	PushMachine(loc, name);
}

void SemanticParser::HiPopMachine(HiEscape& e) {
	FileLocation loc;
	LoadLocation(e[0], loc);
	
	PopMachine(loc);
}

void SemanticParser::HiPushChain(HiEscape& e) {
	FileLocation loc;
	LoadLocation(e[0], loc);
	
	PathIdentifier name;
	LoadPath(loc, e[1], name, tokens[0]);
	
	PushChain(loc, name);
}

void SemanticParser::HiPopChain(HiEscape& e) {
	FileLocation loc;
	LoadLocation(e[0], loc);
	
	PopChain(loc);
}

void SemanticParser::HiPushLoop(HiEscape& e) {
	FileLocation loc;
	LoadLocation(e[0], loc);
	
	PathIdentifier name;
	LoadPath(loc, e[1], name, tokens[0]);
	
	PushLoop(loc, name);
}

void SemanticParser::HiPopLoop(HiEscape& e) {
	FileLocation loc;
	LoadLocation(e[0], loc);
	
	PopLoop(loc);
}

void SemanticParser::HiPushAtom(HiEscape& e) {
	FileLocation loc;
	LoadLocation(e[0], loc);
	
	PathIdentifier name;
	LoadPath(loc, e[1], name, tokens[0]);
	
	PushAtom(loc, name);
}

void SemanticParser::HiPopAtom(HiEscape& e) {
	FileLocation loc;
	LoadLocation(e[0], loc);
	
	PopAtom(loc);
}

void SemanticParser::HiPushAtomConnector(HiEscape& e) {
	FileLocation loc;
	LoadLocation(e[0], loc);
	
	int part = e[1];
	
	PushAtomConnector(loc, part);
}

void SemanticParser::HiPopAtomConnector(HiEscape& e) {
	FileLocation loc;
	LoadLocation(e[0], loc);
	
	PopAtomConnector(loc);
}

void SemanticParser::HiPushState(HiEscape& e) {
	FileLocation loc;
	LoadLocation(e[0], loc);
	
	PathIdentifier name;
	LoadPath(loc, e[1], name, tokens[0]);
	
	PushState(loc, name);
}

void SemanticParser::HiPopState(HiEscape& e) {
	FileLocation loc;
	LoadLocation(e[0], loc);
	
	PopState(loc);
}

void SemanticParser::HiPushCall(HiEscape& e) {
	FileLocation loc;
	LoadLocation(e[0], loc);
	
	PushCall(loc);
}

void SemanticParser::HiPopCall(HiEscape& e) {
	FileLocation loc;
	LoadLocation(e[0], loc);
	
	PopCall(loc);
}

void SemanticParser::HiPopExprCallArgument(HiEscape& e) {
	FileLocation loc;
	LoadLocation(e[0], loc);
	
	int arg_i = e[1];
	
	PopExprCallArgument(loc, arg_i);
}

#endif


NAMESPACE_TOPSIDE_END

