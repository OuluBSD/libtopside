#include "Backend.h"


NAMESPACE_TOPSIDE_BEGIN


void SemanticParser::PushWorld(const FileLocation& loc, const PathIdentifier& name) {
	AstNode& mach = DeclareRelative(name);
	mach.src = SEMT_WORLD;
	PushScope(mach);
}

void SemanticParser::PopWorld(const FileLocation& loc) {
	PopScope();
}

AstNode* SemanticParser::PushClass(const FileLocation& loc, const PathIdentifier& name) {
	AstNode& var = DeclareRelative(name);
	var.src = SEMT_CLASS;
	
	PushScope(var);
	
	return &var;
}

void SemanticParser::PopClass(const FileLocation& loc) {
	PopScope();
}

AstNode* SemanticParser::PushFunction(const FileLocation& loc, AstNode& ret_type, const PathIdentifier& name) {
	AstNode& var = DeclareRelative(name);
	var.src = SEMT_FUNCTION_STATIC;
	var.type = &ret_type;
	
	PushScope(var);
	
	return &var;
}

AstNode* SemanticParser::PushMetaFunction(const FileLocation& loc, AstNode& ret_type, const PathIdentifier& name) {
	AstNode& var = DeclareRelative(name);
	var.src = SEMT_META_FUNCTION_STATIC;
	var.type = &ret_type;
	
	PushScope(var);
	
	return &var;
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
	AstNode* tn = FindDeclaration(type, SEMT_META_TYPE);
	if (!tn) {
		AddError(loc, "internal error");
		return;
	}
	
	AstNode& var = DeclareRelative(name);
	var.src = SEMT_META_PARAMETER;
	var.type = tn;
	var.locked = true;
}

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

AstNode* SemanticParser::PushStatement(const FileLocation& loc, StmtType type) {
	AstNode& n = GetTopNode();
	AstNode& stmt = n.Add(loc);
	stmt.src = SEMT_STATEMENT;
	stmt.stmt = type;
	
	PushScope(stmt);
	
	return &stmt;
}

void SemanticParser::PopStatement(const FileLocation& loc, AstNode* rval) {
	AstNode& n = GetTopNode();
	ASSERT(!n.rval || n.rval == rval || !rval);
	ASSERT(rval != &n);
	if (!rval && n.rval)
		; // pass
	else
		n.rval = rval;
	
	PopScope();
}

AstNode* SemanticParser::PushConstructor(const FileLocation& loc, bool meta, AstNode& type, AstNode* var) {
	AstNode& n = GetTopNode();
	AstNode& stmt = n.Add(loc);
	stmt.src = meta ? SEMT_META_CTOR : SEMT_CTOR;
	stmt.type = &type;
	stmt.rval = var;
	
	ASSERT(var->ctx_next == 0);
	var->ctx_next = &stmt;
	
	PushScope(stmt);
	
	return &stmt;
}

void SemanticParser::PopConstructor(const FileLocation& loc) {
	AstNode& ctor = GetTopNode();
	PopScope();
	AstNode& owner = GetTopNode();
	if (owner.src == SEMT_STATEMENT) {
		ASSERT(!owner.locked);
		owner.stmt = STMT_CTOR;
		owner.rval = &ctor;
	}
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
	ASSERT(!var.name.IsEmpty());
	
	return &var;
}

void SemanticParser::DeclareMetaVariable(const FileLocation& loc, AstNode& type, const PathIdentifier& name) {
	AstNode& block = GetBlock();
	AstNode& var = Declare(block, name);
	var.src = SEMT_META_VARIABLE;
	var.type = &type;
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
	
	AstNode* d = FindDeclaration(id, t);
	if (!d) {
		AddError(loc, "could not find declaration '" + id.ToString() + "'");
		return;
	}
	r.rval = d;
	r.id = id;
	ASSERT(&r != d);
	
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

AstNode* SemanticParser::PushRvalArgumentList(const FileLocation& loc) {
	AstNode& n = GetTopNode();
	AstNode& r = n.Add(loc);
	r.src = SEMT_ARGUMENT_LIST;
	
	PushScopeRVal(r);
	
	return &r;
}

void SemanticParser::Argument(const FileLocation& loc) {
	int c = spath.GetCount();
	ASSERT(c > 2);
	AstNode& owner = *spath[c-2].n;
	AstNode& a = *spath[c-1].n;
	ASSERT(owner.src == SEMT_ARGUMENT_LIST);
	AstNode& arg = owner.Add(loc);
	arg.src = SEMT_ARGUMENT;
	arg.rval = &a;
	ASSERT(arg.rval);
	PopScope();
}

AstNode* SemanticParser::ArraySize(const FileLocation& loc) {
	int c = spath.GetCount();
	ASSERT(c > 2);
	AstNode& owner = *spath[c-2].n;
	AstNode& a = *spath[c-1].n;
	ASSERT(owner.src == SEMT_CTOR);
	AstNode& arg = owner.Add(loc);
	arg.src = SEMT_ARRAYSIZE;
	arg.rval = &a;
	PopScope();
	return &arg;
}

AstNode* SemanticParser::PopExpr(const FileLocation& loc) {
	return PopScope();
}

void SemanticParser::PushRval(const FileLocation& loc, AstNode& n) {
	AstNode& t = GetTopNode();
	AstNode& r = t.Add(loc);
	r.src = SEMT_RVAL;
	r.rval = &n;
	
	PushScopeRVal(r);
}

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
	PushScopeRVal(n);
}

void SemanticParser::PushRvalConstant(const FileLocation& loc, int32 v) {
	AstNode& n = GetTopNode().Add(loc);
	n.src = SEMT_CONSTANT;
	n.con = CONST_INT32;
	n.i64 = v;
	PushScopeRVal(n);
}

void SemanticParser::PushRvalConstant(const FileLocation& loc, int64 v) {
	AstNode& n = GetTopNode().Add(loc);
	n.src = SEMT_CONSTANT;
	n.con = CONST_INT64;
	n.i64 = v;
	PushScopeRVal(n);
}

void SemanticParser::PushRvalConstant(const FileLocation& loc, double v) {
	AstNode& n = GetTopNode().Add(loc);
	n.src = SEMT_CONSTANT;
	n.con = CONST_DOUBLE;
	n.dbl = v;
	PushScopeRVal(n);
}

void SemanticParser::PushRvalConstant(const FileLocation& loc, String v) {
	AstNode& n = GetTopNode().Add(loc);
	n.src = SEMT_CONSTANT;
	n.con = CONST_STRING;
	n.str = v;
	PushScopeRVal(n);
}

void SemanticParser::Expr1(const FileLocation& loc, OpType op) {
	int c = spath.GetCount();
	ASSERT(c >= 2);
	AstNode* arg0 = spath[c-1].n;
	
	AstNode& owner = *spath[c-2].n;
	AstNode& expr = owner.Add(loc);
	expr.src = SEMT_EXPR;
	expr.op = op;
	expr.arg[0] = arg0;
	expr.i64 = 1;
	
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
	expr.arg[0] = arg0;
	expr.arg[1] = arg1;
	expr.i64 = 2;
	
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
	expr.arg[0] = arg0;
	expr.arg[1] = arg1;
	expr.arg[2] = arg2;
	expr.i64 = 3;
	
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

AstNode* SemanticParser::PushLoop(const FileLocation& loc, const PathIdentifier& id) {
	AstNode& var = DeclareRelative(id);
	var.src = SEMT_LOOP;
	
	PushScope(var);
	
	return &var;
}

void SemanticParser::PopLoop(const FileLocation& loc) {
	PopScope();
}

AstNode* SemanticParser::PushAtom(const FileLocation& loc, const PathIdentifier& id) {
	AstNode& var = DeclareRelative(id);
	var.src = SEMT_ATOM;
	
	PushScope(var);
	
	return &var;
}

void SemanticParser::PopAtom(const FileLocation& loc) {
	PopScope();
}

AstNode* SemanticParser::AddEmptyAtomConnector(const FileLocation& loc, int part) {
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
	var.i64 = part;
	
	return &var;
}

AstNode* SemanticParser::PushAtomConnector(const FileLocation& loc, int part) {
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
	var.i64 = part;
	
	PushScope(var);
	
	return &var;
}

void SemanticParser::PopAtomConnector(const FileLocation& loc) {
	PopScope();
}

void SemanticParser::PushState(const FileLocation& loc, const PathIdentifier& id) {
	AstNode& var = DeclareRelative(id);
	var.src = SEMT_STATE;
	
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
	var.i64 = 2;
	
	PushScope(var);
	
}

void SemanticParser::PopCall(const FileLocation& loc) {
	PopScope();
}

void SemanticParser::PopRvalLink(const FileLocation& loc) {
	int c = spath.GetCount();
	ASSERT(c >= 2);
	AstNode* arg0 = spath[c-1].n;
	
	AstNode& owner = *spath[c-2].n;
	owner.arg[0] = arg0;
	
	spath.SetCount(c-1);
}

void SemanticParser::PopExprCallArgument(const FileLocation& loc, int arg_i) {
	int c = spath.GetCount();
	ASSERT(c >= 2);
	AstNode* arg0 = spath[c-1].n;
	
	AstNode& owner = *spath[c-2].n;
	AstNode& expr = owner.Add(loc);
	expr.src = SEMT_CALL_ARG;
	expr.arg[0] = arg0;
	
	spath.SetCount(c-1);
}

AstNode* SemanticParser::PartialMetaResolve(const FileLocation& loc, const PathIdentifier& id, SemanticType t) {
	AstNode& n = GetTopNode().Add(loc);
	n.src = SEMT_META_RESOLVE;
	n.id = id;
	n.filter = t;
	return &n;
}




NAMESPACE_TOPSIDE_END

