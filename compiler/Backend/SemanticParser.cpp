#include "Backend.h"

//#define EMIT if (emitter) emitter->
#define EMIT

NAMESPACE_TOPSIDE_BEGIN


SemanticParser::SemanticParser() :
	ErrorSource("SemanticParser")
{
	
}

bool SemanticParser::ProcessEon(const TokenStructure& t) {
	root.Clear();
	path.Clear();
	
	InitDefault();
	
	path.Add(&t.root);
	
	bool succ = ParseNamespaceBlock();
	
	spath.Clear();
	path.Clear();
	
	return succ;
}

bool SemanticParser::ParseNamespaceBlock() {
	ASSERT(!path.IsEmpty());
	
	const TokenNode& owner = *path.Top();
	const TokenNode*& cur = path.Add();
	
	for (const TokenNode& tns : owner.sub) {
		cur = &tns;
		if (!ParseDeclaration())
			return false;
	}
	
	path.Remove(path.GetCount()-1);
	
	return true;
}

SemanticParser::Iterator& SemanticParser::AddIterator(const TokenNode& n) {
	Iterator& i = iters.Add();
	i.iter = i.begin = n.begin;
	i.end = n.end;
	i.node = &n;
	return i;
}

SemanticParser::Iterator& SemanticParser::TopIterator() {
	ASSERT(!iters.IsEmpty());
	return iters.Top();
}

const SemanticParser::Iterator& SemanticParser::TopIterator() const {
	ASSERT(!iters.IsEmpty());
	return iters.Top();
}

void SemanticParser::PopIterator() {
	ASSERT(!iters.IsEmpty());
	iters.Remove(iters.GetCount()-1);
}

bool SemanticParser::ParseDeclaration() {
	AddIterator(*path.Top());
	
	if (!IsLineEnd()) {
		if (IsId("def")) {
			TODO
		}
		else if (IsId("machine")) {
			if (!ParseMachine())
				return false;
		}
		else if (IsId("chain")) {
			if (!ParseChain())
				return false;
		}
		else if (IsId("loop") || IsId("driver")) {
			if (!ParseLoop())
				return false;
		}
		else if (IsId("world")) {
			if (!ParseWorld())
				return false;
		}
		else {
			bool succ = ParseDeclExpr(true);
			PopIterator();
			return succ;
		}
	}
	
	PopIterator();
	return true;
}

/*bool SemanticParser::ParseTypedDeclaration(AstNode& ret_type) {
	Iterator& iter = TopIterator();
	const TokenNode& cur = *path.Top();
	ASSERT(iter.Check(cur));
	
	PathIdentifier name;
	if (!ParsePathIdentifier(name))
		return false;
	
	//DUMP(name);
	
	
	if (iter) {
		
		if (Char('(')) {
			return ParseFunction(ret_type, name);
		}
		else {
			TODO
		}
		
	}
	
	
	TODO
	
	
}

bool SemanticParser::ParseTypedMetaDeclaration(AstNode& ret_type) {
	Iterator& iter = TopIterator();
	const TokenNode& cur = *path.Top();
	ASSERT(iter.Check(cur));
	
	PathIdentifier name;
	if (!ParsePathIdentifier(name))
		return false;
	
	//DUMP(name);
	
	
	if (iter) {
		
		if (Char('(')) {
			return ParseMetaFunction(ret_type, name);
		}
		else {
			AstNode& var = DeclareRelative(name);
			ASSERT(var.IsPartially(SEMT_UNDEFINED));
			var.src = SEMT_VARIABLE;
			var.type = tn;
			
			EMIT DeclareVariable(first.begin->loc, *tn, name);
			if (Char('=')) {
				iter++;
				if (!Cond(true))
					return false;
			}
		}
	}
	
	return true;
}*/

bool SemanticParser::ParseFunction(AstNode& ret_type, const PathIdentifier& name) {
	Iterator& iter = TopIterator();
	const TokenNode& cur = *path.Top();
	ASSERT(iter.Check(cur));
	ASSERT(iter->IsType('('));
	
	AstNode& var = DeclareRelative(name);
	var.src = SEMT_FUNCTION_STATIC;
	var.type = &ret_type;
	
	PushScope(var);
	
	EMIT PushFunction(name.begin->loc, ret_type, name);
	
	if (!PassToken('(')) return false;
	
	int i = 0;
	while (iter && !iter->IsType(')')) {
		if (i && !PassToken(','))
			return false;
		
		if (!ParseParameter())
			return false;
		
		i++;
	}
	
	if (!PassToken(')')) return false;
	
	
	if (!iter && cur.sub.GetCount()) {
		//EMIT PushFunctionDefinition(cur.sub[0].begin->loc);
		
		if (!ParseStatementList())
			return false;
		
		//EMIT PopFunctionDefinition(cur.sub.Top().end->loc);
	}
	
	EMIT PopFunction(cur.end->loc);
	
	PopScope();
	
	return true;
}

bool SemanticParser::ParseMetaFunction(AstNode& ret_type, const PathIdentifier& name) {
	Iterator& iter = TopIterator();
	const TokenNode& cur = *path.Top();
	ASSERT(iter.Check(cur));
	ASSERT(iter->IsType('('));
	
	AstNode& var = DeclareRelative(name);
	var.src = SEMT_META_FUNCTION_STATIC;
	var.type = &ret_type;
	
	PushScope(var);
	
	EMIT PushMetaFunction(name.begin->loc, ret_type, name);
	
	if (!PassToken('(')) return false;
	
	int i = 0;
	while (iter && !iter->IsType(')')) {
		if (i && !PassToken(','))
			return false;
		
		if (!ParseMetaParameter())
			return false;
		
		i++;
	}
	
	if (!PassToken(')')) return false;
	
	
	if (!iter && cur.sub.GetCount()) {
		//EMIT PushFunctionDefinition(cur.sub[0].begin->loc);
		
		if (ret_type.name == "machstmt") {
			if (!ParseMachineStatementList())
				return false;
		}
		else if (ret_type.name == "chainstmt") {
			if (!ParseChainStatementList())
				return false;
		}
		else if (ret_type.name == "loopstmt") {
			if (!ParseLoopStatementList())
				return false;
		}
		else if (ret_type.name == "atomstmt") {
			if (!ParseAtomStatementList())
				return false;
		}
		else if (ret_type.name == "worldstmt") {
			if (!ParseWorldStatementList())
				return false;
		}
		else if (ret_type.name == "systemstmt") {
			if (!ParseSystemStatementList())
				return false;
		}
		else if (ret_type.name == "poolstmt") {
			if (!ParsePoolStatementList())
				return false;
		}
		else if (ret_type.name == "entitystmt") {
			if (!ParseEntityStatementList())
				return false;
		}
		else if (ret_type.name == "compstmt") {
			if (!ParseComponentStatementList())
				return false;
		}
		else if (!ParseStatementList())
			return false;
		
		//EMIT PopFunctionDefinition(cur.sub.Top().end->loc);
	}
	
	EMIT PopMetaFunction(cur.end->loc);
	
	PopScope();
	
	return true;
}

bool SemanticParser::ParseAtomStatementList() {
	bool succ = true;
	
	const TokenNode& tk_owner = *path.Top();
	AstNode& ast_owner = *spath.Top().n;
	
	AstNode& block = ast_owner.Add();
	block.src = SEMT_STATEMENT_BLOCK;
	PushScope(block);
	
	EMIT PushStatementList(tk_owner.end->loc);
	
	allow_expr_unresolved = true;
	
	const TokenNode*& sub = path.Add();
	for (const TokenNode& s : tk_owner.sub) {
		sub = &s;
		//DUMP(s)
		AddIterator(s);
		
		Iterator& iter = TopIterator();
		if (!iter)
			continue;
		
		if (IsId("meta")) {
			if (!ParseMeta()) {
				succ = false;
				break;
			}
		}
		else if (!ParseAtomExpressionStatement()) {
			succ = false;
			break;
		}
		
		PopIterator();
	}
	path.Remove(path.GetCount()-1);
	
	allow_expr_unresolved = false;
	if (!succ)
		PopIterator();
	
	PopScope();
	EMIT PopStatementList(tk_owner.end->loc);
	
	return succ;
}

bool SemanticParser::ParseAtomExpressionStatement() {
	const TokenNode& cur = CurrentNode();
	Iterator& iter = TopIterator();
	
	EMIT PushStatement(iter->loc, STMT_EXPR);
	
	bool succ = Assign(false);
	
	EMIT PopExpr(iter->loc);
	
	EMIT PopStatement(iter->loc);
	
	return succ;
}

bool SemanticParser::ParseStatementList() {
	bool succ = true;
	
	const TokenNode& tk_owner = *path.Top();
	AstNode& ast_owner = *spath.Top().n;
	
	AstNode& block = ast_owner.Add();
	block.src = SEMT_STATEMENT_BLOCK;
	PushScope(block);
	
	EMIT PushStatementList(tk_owner.end->loc);
	
	const TokenNode*& sub = path.Add();
	for (const TokenNode& s : tk_owner.sub) {
		sub = &s;
		//DUMP(s)
		AddIterator(s);
		
		Iterator& iter = TopIterator();
		if (!iter)
			continue;
		
		if (IsId("meta")) {
			if (!ParseMeta())
				return false;
		}
		else if (IsId("loop") || IsId("driver")) {
			if (!ParseLoop())
				return false;
		}
		else if (IsId("chain")) {
			if (!ParseChain())
				return false;
		}
		else if (IsId("machine")) {
			if (!ParseMachine())
				return false;
		}
		else if (!ParseStatement()) {
			succ = false;
			PopIterator();
			break;
		}
		
		PopIterator();
	}
	path.Remove(path.GetCount()-1);
	
	PopScope();
	EMIT PopStatementList(tk_owner.end->loc);
	
	return succ;
}

bool SemanticParser::ParseStatement() {
	const TokenNode& cur = CurrentNode();
	Iterator& iter = TopIterator();
	
	//DUMP(cur)
	
	if (IsId("meta")) {
		return ParseMetaStatement();
	}
	else if (Id("if")) {
		EMIT PushStatement(iter->loc, STMT_IF);
		
		if (!ParseExpression(false)) return false;
		if (!ParseStatementBlock()) return false;
		if (Id("else")) {
			EMIT PushStatement(iter->loc, STMT_ELSE);
			
			if (!ParseStatementBlock()) return false;
			
			EMIT PopStatement(iter->loc);
		}
		
		EMIT PopStatement(iter->loc);
	}
	else if (Id("do")) {
		EMIT PushStatement(iter->loc, STMT_DOWHILE);
		
		if (!ParseStatementBlock()) return false;
		if (!PassId("while")) return false;
		if (!ParseExpression(false)) return false;
		if (!PassToken(';')) return false;
		
		EMIT PopStatement(iter->loc);
	}
	else if (Id("while")) {
		EMIT PushStatement(iter->loc, STMT_WHILE);
		
		if (!ParseExpression(false)) return false;
		if (!ParseStatementBlock()) return false;
		
		EMIT PopStatement(iter->loc);
	}
	else if (Id("for")) {
		EMIT PushStatement(iter->loc, STMT_FOR);
		
		if (!IsToken(',')) {
			//EMIT PushStatementParameter(iter->loc, STMTP_FOR_DECL);
			if (!ParseDeclExpr(false)) return false;
		}
		if (Id("in") || Char(':')) {
			//EMIT PushStatementParameter(iter->loc, STMTP_FOR_COLLECTION);
			EMIT PushStatement(iter->loc, STMT_FOR_RANGE);
			if (!ParseExpression(false)) return false;
			EMIT PopStatement(iter->loc);
		}
		else {
			if (!PassToken(',')) return false;
			if (!IsToken(',')) {
				//EMIT PushStatementParameter(iter->loc, STMTP_WHILE_COND);
				EMIT PushStatement(iter->loc, STMT_FOR_COND);
				if (!ParseExpression(false)) return false;
				EMIT PopStatement(iter->loc);
			}
			if (!PassToken(',')) return false;
			if (iter) {
				//EMIT PushStatementParameter(iter->loc, STMTP_FOR_POST);
				EMIT PushStatement(iter->loc, STMT_FOR_POST);
				if (!ParseExpression(false)) return false;
				EMIT PopStatement(iter->loc);
			}
		}
		
		//EMIT PushStatementList(iter->loc);
		if (!ParseStatementBlock()) return false;
		//EMIT PopStatementList(iter->loc);
		
		EMIT PopStatement(iter->loc);
	}
	else if (Id("break")) {
		EMIT PushStatement(iter->loc, STMT_BREAK);
		EMIT PopStatement(iter->loc);
	}
	else if (Id("continue")) {
		EMIT PushStatement(iter->loc, STMT_CONTINUE);
		EMIT PopStatement(iter->loc);
	}
	else if (Id("case")) {
		AddError(iter->loc, "misplaced 'case'");
		return false;
	}
	else if (Id("default")) {
		AddError(iter->loc, "misplaced 'default'");
		return false;
	}
	else if (Id("else")) {
		AddError(iter->loc, "misplaced 'else'");
		return false;
	}
	else if (Id("return")) {
		EMIT PushStatement(iter->loc, STMT_RETURN);
		
		if (iter) {
			if (!ParseExpression(false)) return false;
		}
		
		EMIT PopStatement(iter->loc);
	}
	else if (Id("switch")) {
		EMIT PushStatement(iter->loc, STMT_SWITCH);
		
		if (!ParseExpression(false)) return false;
		
		if (!ParseSwitchBlock()) return false;
		
		EMIT PopStatement(iter->loc);
	}
	else if (Id("log")) {
		Token tk;
		tk.type = TK_ID;
		tk.str_value = "LOG";
		
		PathIdentifier id;
		id.begin = &tk;
		id.end = &tk;
		id.part_count = 1;
		id.parts[0] = &tk;
		
		EMIT PushStatement(iter->loc, STMT_EXPR);
		EMIT PushRvalResolve(iter->loc, id, SEMT_FUNCTION_BUILTIN);
		EMIT PushRvalArgumentList(iter->loc);
		
		if (!Assign(false)) return false;
		EMIT Argument(iter->loc);
		
		while (Char(',')) {
			if (!Assign(false)) return false;
			EMIT Argument(iter->loc);
		}
		
		EMIT Expr2(iter->loc, OP_CALL);
		EMIT PopExpr(iter->loc);
		EMIT PopStatement(iter->loc);
	}
	else if (cur.begin == cur.end && cur.sub.GetCount()) {
		EMIT PushStatement(iter->loc, STMT_BLOCK);
		
		if (!ParseStatementBlock()) return false;
		
		EMIT PopStatement(iter->loc);
	}
	else if (cur.begin == cur.end) {
		// empty statement
	}
	else {
		AstNode& stmt = spath.Top().n->Add();
		stmt.src = SEMT_STATEMENT;
		PushScope(stmt);
		EMIT PushStatement(iter->loc, STMT_EXPR);
		
		if (!ParseExpression(false)) return false;
		
		PopScope();
		EMIT PopStatement(iter->loc);
	}
	
	return true;
}

bool SemanticParser::ParseMetaStatement(bool skip_meta_keywords) {
	const TokenNode& cur = CurrentNode();
	Iterator& iter = TopIterator();
	
	//DUMP(cur)
	if (!skip_meta_keywords && !PassId("meta"))
		return false;
	
	if (Id("if")) {
		EMIT PushStatement(iter->loc, STMT_META_IF);
		
		if (!ParseExpression(true)) return false;
		if (!ParseStatementBlock()) return false;
		if (Id("else")) {
			EMIT PushStatement(iter->loc, STMT_META_ELSE);
			
			if (!ParseStatementBlock()) return false;
			
			EMIT PopStatement(iter->loc);
		}
		
		EMIT PopStatement(iter->loc);
	}
	else if (Id("do")) {
		EMIT PushStatement(iter->loc, STMT_META_DOWHILE);
		
		if (!ParseStatementBlock()) return false;
		if (!PassId("while")) return false;
		if (!ParseExpression(true)) return false;
		if (!PassToken(';')) return false;
		
		EMIT PopStatement(iter->loc);
	}
	else if (Id("while")) {
		EMIT PushStatement(iter->loc, STMT_META_WHILE);
		
		if (!ParseExpression(true)) return false;
		if (!ParseStatementBlock()) return false;
		
		EMIT PopStatement(iter->loc);
	}
	else if (Id("for")) {
		EMIT PushStatement(iter->loc, STMT_META_FOR);
		
		if (!IsToken(',')) {
			//EMIT PushStatementParameter(iter->loc, STMTP_FOR_DECL);
			if (!ParseMetaDeclExpr(false)) return false;
		}
		if (Id("in") || Char(':')) {
			//EMIT PushStatementParameter(iter->loc, STMTP_FOR_COLLECTION);
			EMIT PushStatement(iter->loc, STMT_META_FOR_RANGE);
			if (!ParseExpression(true)) return false;
			EMIT PopStatement(iter->loc);
		}
		else {
			if (!PassToken(',')) return false;
			if (!IsToken(',')) {
				//EMIT PushStatementParameter(iter->loc, STMTP_WHILE_COND);
				EMIT PushStatement(iter->loc, STMT_META_FOR_COND);
				if (!ParseExpression(true)) return false;
				EMIT PopStatement(iter->loc);
			}
			if (!PassToken(',')) return false;
			if (iter) {
				//EMIT PushStatementParameter(iter->loc, STMTP_FOR_POST);
				EMIT PushStatement(iter->loc, STMT_META_FOR_POST);
				if (!ParseExpression(true)) return false;
				EMIT PopStatement(iter->loc);
			}
		}
		
		//EMIT PushStatementList(iter->loc);
		if (!ParseStatementBlock()) return false;
		//EMIT PopStatementList(iter->loc);
		
		EMIT PopStatement(iter->loc);
	}
	else if (Id("break")) {
		EMIT PushStatement(iter->loc, STMT_META_BREAK);
		EMIT PopStatement(iter->loc);
	}
	else if (Id("continue")) {
		EMIT PushStatement(iter->loc, STMT_META_CONTINUE);
		EMIT PopStatement(iter->loc);
	}
	else if (Id("case")) {
		AddError(iter->loc, "misplaced 'case'");
		return false;
	}
	else if (Id("default")) {
		AddError(iter->loc, "misplaced 'default'");
		return false;
	}
	else if (Id("else")) {
		AddError(iter->loc, "misplaced 'else'");
		return false;
	}
	else if (Id("return")) {
		EMIT PushStatement(iter->loc, STMT_META_RETURN);
		
		if (iter) {
			if (!ParseExpression(true)) return false;
		}
		
		EMIT PopStatement(iter->loc);
	}
	else if (Id("switch")) {
		EMIT PushStatement(iter->loc, STMT_META_SWITCH);
		
		if (!ParseExpression(true)) return false;
		
		if (!ParseSwitchBlock()) return false;
		
		EMIT PopStatement(iter->loc);
	}
	else if (cur.begin == cur.end && cur.sub.GetCount()) {
		EMIT PushStatement(iter->loc, STMT_BLOCK);
		
		if (!ParseStatementBlock()) return false;
		
		EMIT PopStatement(iter->loc);
	}
	else if (cur.begin == cur.end) {
		// empty statement
	}
	else {
		AstNode& stmt = spath.Top().n->Add();
		stmt.src = SEMT_META_STATEMENT;
		PushScope(stmt);
		EMIT PushStatement(iter->loc, STMT_META_EXPR);
		
		if (!ParseExpression(true)) return false;
		
		PopScope();
		EMIT PopStatement(iter->loc);
	}
	
	return true;
}

bool SemanticParser::ParseParameter() {
	Iterator& iter = TopIterator();
	const TokenNode& cur = *path.Top();
	ASSERT(iter.Check(cur));
	
	PathIdentifier type;
	if (!ParsePathIdentifier(type))
		return false;
	
	if (!iter) {
		AddError(iter->loc, "unexpeced end of parameter");
		return false;
	}
	
	AstNode* tn = FindDeclaration(type);
	if (!tn || !IsTypedNode(tn->src)) {
		AddError(iter->loc, "could not find type '" + type.ToString() + "'");
		return false;
	}
	
	PathIdentifier name;
	if (!iter->IsType(',')) {
		if (!ParsePathIdentifier(name))
			return false;
	}
	
	AstNode& pn = DeclareRelative(name);
	if (!pn.IsPartially(SEMT_UNDEFINED)) {
		AddError(iter->loc, "variable '" + name.ToString() + "' already declared");
		return false;
	}
	pn.src = SEMT_PARAMETER;
	pn.type = tn;
	
	EMIT Parameter(type.begin->loc, type, name);
	
	return true;
}

bool SemanticParser::ParseMetaParameter() {
	Iterator& iter = TopIterator();
	const TokenNode& cur = *path.Top();
	ASSERT(iter.Check(cur));
	
	PathIdentifier type;
	if (!ParsePathIdentifier(type))
		return false;
	
	if (!iter) {
		AddError(iter->loc, "unexpeced end of parameter");
		return false;
	}
	
	AstNode* tn = FindDeclaration(type, SEMT_META_ANY);
	if (!tn || !IsMetaTypedNode(tn->src)) {
		AddError(iter->loc, "could not find meta-type '" + type.ToString() + "'");
		return false;
	}
	
	PathIdentifier name;
	if (!iter->IsType(',')) {
		if (!ParsePathIdentifier(name))
			return false;
	}
	
	AstNode& pn = DeclareRelative(name);
	if (!pn.IsPartially(SEMT_UNDEFINED)) {
		AddError(iter->loc, "variable '" + name.ToString() + "' already declared");
		return false;
	}
	pn.src = SEMT_META_PARAMETER;
	pn.type = tn;
	
	EMIT MetaParameter(type.begin->loc, type, name);
	
	return true;
}

bool SemanticParser::ParsePathIdentifier(PathIdentifier& id) {
	Iterator& iter = TopIterator();
	id.begin = iter;
	id.part_count = 0;
	const Token* end = iter.end;
	
	bool expect_dot = false;
	
	memset(id.is_meta, 0, sizeof(id.is_meta));
	
	while (iter) {
		if (expect_dot) {
			if (!iter->IsType('.')) {
				end = iter;
				break;
			}
			expect_dot = false;
		}
		else {
			if (iter->IsType(TK_ID) && iter->str_value == "meta") {
				TODO
			}
			else if (iter->IsType(TK_ID) || iter->IsType(TK_INTEGER)) {
				id.parts[id.part_count++] = iter;
				expect_dot = true;
			}
			else if (iter->IsType('$')) {
				id.is_meta[id.part_count] = true;
			}
			else {
				TODO
			}
		}
		iter++;
	}
	
	id.end = end;
	
	return id.part_count > 0;
}

bool SemanticParser::ParseCallArguments() {
	Iterator& iter = TopIterator();
	
	if (!PassToken('('))
		return false;
	
	EMIT PushCall(iter->loc);
	
	int i = 0;
	while (!TryToken(')')) {
		if (i > 0 && !PassToken(','))
			return false;
		if (!Assign(false))
			return false;
		EMIT PopExprCallArgument(iter->loc, i);
		i++;
	}
	
	EMIT PopCall(iter->loc);
	
	return true;
}


bool SemanticParser::ParseClass() {
	const TokenNode& cur = *path.Top();
	DUMP(cur);
	TODO
}

bool SemanticParser::ParseStatementBlock() {
	return ParseStatementList();
}

bool SemanticParser::ParseDeclExpr(bool must_decl) {
	const TokenNode& cur = *path.Top();
	Iterator& iter = TopIterator();
	//DUMP(cur);
	
	PathIdentifier first;
	if (!ParsePathIdentifier(first))
		return false;
	
	AstNode* tn = FindDeclaration(first);
	AstNode* var = 0;
	PathIdentifier name;
	
	if (tn && tn->IsPartially(SEMT_TYPE)) {
		if (!ParsePathIdentifier(name))
			return false;
		
		var = &Declare(GetBlock(), name);
		ASSERT(var->IsPartially(SEMT_UNDEFINED));
		var->src = SEMT_VARIABLE;
		var->type = tn;
		
		
		if (IsChar('(')) {
			//EMIT PushFunction(first.begin->loc, *tn, name);
			
			ASSERT(var);
			if (!ParseFunction(*tn, name))
				return false;
			
			return true;
		}
		else {
			/*if (cur.sub.GetCount()) {
				DUMP(cur.GetTreeString());
				AddError(iter->loc, "expected ()");
				return false;
			}*/
			
			EMIT DeclareVariable(first.begin->loc, *tn, name);
			
		}
		
	}
	else if (!tn || must_decl) {
		if (must_decl)
			AddError(iter->loc, "could not resolve '" + first.ToString() + "'");
		return false;
	}
	else {
		var = tn;
		ASSERT(var->name.GetCount());
	}
	
	if (Char('=')) {
		EMIT PushStatement(iter->loc, STMT_CTOR);
		EMIT PushRval(iter->loc, *var);
		
		//NO: Expression leaf pushes: EMIT PushExprScope();
		if (!Cond(false)) return false;
		EMIT Expr2(iter->loc, OP_ASSIGN);
		
		EMIT PopExpr(iter->loc);
		EMIT PopStatement(iter->loc);
	}
	else if (IsChar('(')) {
		TODO // subscript op
	}
	ASSERT(!IsChar('('));
	
	return true;
}

bool SemanticParser::ParseMetaDeclExpr(bool must_decl) {
	const TokenNode& cur = *path.Top();
	Iterator& iter = TopIterator();
	//DUMP(cur);
	
	PathIdentifier first;
	if (!ParsePathIdentifier(first))
		return false;
	
	AstNode* tn = FindDeclaration(first, SEMT_META_ANY);
	AstNode* var = 0;
	PathIdentifier name;
	
	if (tn && tn->IsPartially(SEMT_META_TYPE)) {
		if (!ParsePathIdentifier(name))
			return false;
		
		//DUMP(name);
		var = &DeclareRelative(name);
		ASSERT(var->IsPartially(SEMT_UNDEFINED));
		var->src = SEMT_META_VARIABLE;
		var->type = tn;
		
		EMIT DeclareMetaVariable(first.begin->loc, *tn, name);
	}
	else if (!tn || must_decl) {
		if (must_decl)
			AddError(iter->loc, "could not resolve '" + first.ToString() + "'");
		return false;
	}
	else {
		var = tn;
		ASSERT(var->name.GetCount());
	}
	
	if (Char('=')) {
		EMIT PushStatement(iter->loc, STMT_CTOR);
		EMIT PushRval(iter->loc, *var);
		
		//NO: Expression leaf pushes: EMIT PushExprScope();
		if (!Cond(true)) return false;
		EMIT Expr2(iter->loc, OP_ASSIGN);
		
		EMIT PopExpr(iter->loc);
		EMIT PopStatement(iter->loc);
	}
	else if (IsChar('(')) {
		if (!tn) {
			TODO // subscript op
		}
		else {
			ASSERT(var);
			if (!ParseMetaFunction(*tn, name))
				return false;
		}
	}
	
	return true;
}

bool SemanticParser::ParseSwitchBlock() {
	TODO
}

bool SemanticParser::ParseExpression(bool m) {
	Iterator& iter = TopIterator();
	bool succ = Assign(m);
	
	EMIT PopExpr(iter->loc);
	
	return succ;
}

bool SemanticParser::Subscript(bool m) {
	Iterator& iter = TopIterator();
	
	for(;;) {
		if(Char('[')) {
			if(Char(']')) {
				TODO // Emit
			}
			else {
				if(!IsChar(',') && !IsChar(':')) {
					if (!Assign(m))
						return false;
				}
				
				if(Char(',')) {
					if(!IsChar(']')) {
						if (!Assign(m))
							return false;
					}
					TODO // Emit
				}
				else
				if(Char(':')) {
					if(!IsChar(']')) {
						if (!Assign(m))
							return false;
					}
					TODO // Emit
				}
				else {
					TODO // Emit
				}
				PassChar(']');
			}
		}
		else
		if(Char('.')) {
			TODO
			//id = ReadId();
		}
		else
		if(Char('(')) {
			
			EMIT PushRvalArgumentList(iter->loc);
			
			if (!Char(')')) do {
				if (!Assign(m))
					return false;
				EMIT Argument(iter->loc);
				if(Char(')')) break;
				if (!PassChar(','))
					return false;
			} while (1);
			
			EMIT Expr2(iter->loc, OP_CALL);
			
			if(/*!IsToken(TK_INEQ) &&*/ Char('!')) {
				Term(m);
			}
			
		}
		else
			return true;
	}
	return true;
}

bool SemanticParser::Term(bool meta) {
	Iterator& iter = TopIterator();
	
	if(iter->IsType(TK_HEX)) {
		EMIT PushRvalConstant(iter->loc, iter);
		iter++;
		return true;
	}
	/*if(iter->IsType(TK_BINARY)) {
		TODO // Emit
		return true;
	}*/
	if(iter->IsType(TK_FLOAT) || iter->IsType(TK_DOUBLE)) {
		EMIT PushRvalConstant(iter->loc, iter);
		iter++;
		return true;
	}
	if(iter->IsType(TK_OCT)) {
		EMIT PushRvalConstant(iter->loc, iter);
		iter++;
		return true;
	}
	if(iter->IsType(TK_INTEGER)) {
		// TODO: int64 !
		EMIT PushRvalConstant(iter->loc, iter);
		iter++;
		return true;
	}
	if(iter->IsType(TK_STRING)) {
		EMIT PushRvalConstant(iter->loc, iter);
		iter++;
		return true;
	}
	if(iter->IsType(TK_CHAR)) {
		/*WString s = FromUtf8(ReadString('\'', true));
		if(s.GetLength() != 1) {
			AddError(iter->loc, "invalid character literal");
			return false;
		}*/
		EMIT PushRvalConstant(iter->loc, iter);
		iter++;
		return true;
	}
	if(iter->IsType(TK_ID) && (iter->str_value == "true" || iter->str_value == "false")) {
		EMIT PushRvalConstant(iter->loc, iter);
		iter++;
		return true;
	}
	if(Char('@')) {
		TODO // Emit
		if (!Subscript(meta))
			return false;
		return true;
	}
	if(Id("void")) {
		TODO // Emit
		return true;
	}
	/*if(Char(TK_INDENT)) {
		TODO // Emit
		if(!Char(TK_DEDENT)) {
			for(;;) {
				TODO // should be Assign, not ParseExpression
				if (!ParseExpression(meta))
					return false;
				PassChar(':');
				if (!ParseExpression(meta))
					return false;
				if(Char(TK_DEDENT))
					break;
				PassChar(',');
			}
		}
		if (!Subscript(meta))
			return false;
		return true;
	}*/
	if(Char('[')) {
		if(!Char(']')) {
			for(;;) {
				if (!Assign(meta))
					return false;
				if(Char(']'))
					break;
				PassChar(',');
				TODO // Emit
			}
		}
		if (!Subscript(meta))
			return false;
		return true;
	}
	if(Char('(')) {
		if (!Assign(meta))
			return false;
		PassChar(')');
		if (!Subscript(meta))
			return false;
		return true;
	}
	
	if (!iter) {
		AddError(iter->loc, "unexpected end-of-expression");
		return false;
	}
	
	bool  _global = false;
	if(Char('.')) {
		TODO // Emit
	}
	else
	if(Char(':'))
		_global = true;
	if(iter->IsType(TK_ID) || iter->IsType('$')) {
		PathIdentifier id;
		if (!ParsePathIdentifier(id))
			return false;
		
		if (id.HasMeta())
			meta = true;
		
		AstNode* nn = FindDeclaration(id, meta ? SEMT_META_ANY : SEMT_NULL);
		if (!nn) {
			if (allow_expr_unresolved) {
				EMIT PushRvalUnresolved(id.begin->loc, id, meta ? SEMT_META_ANY : SEMT_NULL);
				return Subscript(meta);
			}
			else {
				AddError(iter->loc, "could not find '" + id.ToString() + "'");
				return false;
			}
		}
		
		if (!_global && Char('(')) {
			
			if (nn->IsPartially(meta ? SEMT_META_FUNCTION : SEMT_FUNCTION)) {
				//EMIT PushRvalCall(id.begin->loc, *nn);
				EMIT PushRvalResolve(id.begin->loc, id, meta ? SEMT_META_FUNCTION : SEMT_FUNCTION);
			}
			else if (IsTypedNode(nn->src)) {
				//EMIT PushRvalConstruct(id.begin->loc, *nn);
				EMIT PushRvalResolve(id.begin->loc, id, meta ? SEMT_META_TYPE : SEMT_TYPE);
			}
			else {
				AddError(iter->loc, "can't call or construct '" + id.ToString() + "'");
				return false;
			}
			
			EMIT PushRvalArgumentList(iter->loc);
			
			if (!Char(')')) do {
				if (!Assign(meta))
					return false;
				EMIT Argument(iter->loc);
				if(Char(')')) break;
				if (!PassChar(','))
					return false;
			} while (1);
			
			EMIT Expr2(iter->loc, OP_CALL);
		}
		else {
			//DUMP(id);
			
			if (nn->IsPartially(meta ? SEMT_META_FIELD : SEMT_FIELD)) {
				EMIT PushRval(id.begin->loc, *nn);
			}
			else if (nn->IsPartially(meta ? SEMT_META_TYPE : SEMT_TYPE)) {
				const AstNode& owner = *spath.Top().n;
				if (owner.src == SEMT_STATEMENT && owner.sub.IsEmpty()) {
					PathIdentifier name;
					const FileLocation& loc = iter->loc;
					if (!ParsePathIdentifier(name)) {
						AddError(loc, "could not parse name");
						return false;
					}
					
					AstNode& block = GetBlock();
					AstNode& var = Declare(block, name);
					ASSERT(var.IsPartially(SEMT_UNDEFINED));
					var.src = SEMT_VARIABLE;
					var.type = nn;
					
					// Variable declaration statement
					EMIT DeclareVariable(iter->loc, *nn, name);
					EMIT PushRval(id.begin->loc, var);
				}
				else {
					TODO // probably user error --> AddError
				}
			}
			else if (allow_expr_unresolved) {
				EMIT PushRvalUnresolved(id.begin->loc, id, meta ? SEMT_META_ANY : SEMT_NULL);
			}
			else {
				TODO
			}
		}
		
		
		return Subscript(meta);
	}
	else {
		AddError(iter->loc, "invalid expression");
		return false;
	}
	
	return true;
}

bool SemanticParser::Unary(bool m) {
	const Token& tk = TopIterator();
	
	if(TryToken(TK_INC)) {
		if (!Unary(m)) return false;
		EMIT Expr1(tk.loc, OP_INC);
	}
	else
	if(TryToken(TK_DEC)) {
		if (!Unary(m)) return false;
		EMIT Expr1(tk.loc, OP_DEC);
	}
	else
	if(Char('-')) {
		if (!Unary(m)) return false;
		EMIT Expr1(tk.loc, OP_NEGATIVE);
	}
	else
	if(Char('+')) {
		if (!Unary(m)) return false;
		EMIT Expr1(tk.loc, OP_POSITIVE);
	}
	else
	if(Char('!')) {
		if (!Unary(m)) return false;
		EMIT Expr1(tk.loc, OP_NOT);
	}
	else
	if(Char('~')) {
		if (!Unary(m)) return false;
		EMIT Expr1(tk.loc, OP_NEGATE);
	}
	else
		if (!Term(m)) return false;

	if(TryToken(TK_INC)) {
		EMIT Expr1(tk.loc, OP_POSTINC);
	}
	if(TryToken(TK_DEC)) {
		EMIT Expr1(tk.loc, OP_POSTDEC);
	}
	
	return true;
}

bool SemanticParser::Mul(bool m) {
	if (!Unary(m)) return false;
	for(;;) {
		const Token& tk = TopIterator();
		
		if(/*!IsToken(TK_MULASS) &&*/ Char('*')) {
			if (!Unary(m)) return false;
			EMIT Expr2(tk.loc, OP_MUL);
		}
		else
		if(/*!IsToken(TK_DIVASS) &&*/ Char('/')) {
			if (!Unary(m)) return false;
			EMIT Expr2(tk.loc, OP_DIV);
		}
		else
		if(/*!IsToken(TK_MODASS) &&*/ Char('%')) {
			if (!Unary(m)) return false;
			EMIT Expr2(tk.loc, OP_MOD);
		}
		else
			break;
	}
	
	return true;
}

bool SemanticParser::Add(bool m) {
	if (!Mul(m)) return false;
	
	for(;;) {
		const Token& tk = TopIterator();
		
		if(/*!IsChar2('+', '=') &&*/ Char('+')) {
			if (!Mul(m)) return false;
			EMIT Expr2(tk.loc, OP_ADD);
		}
		else
		if(/*!IsChar2('-', '=') &&*/ Char('-')) {
			if (!Mul(m)) return false;
			EMIT Expr2(tk.loc, OP_SUB);
		}
		else
			break;
	}
	return true;
}

bool SemanticParser::Shift(bool m) {
	if (!Add(m)) return false;
	for(;;) {
		const Token& tk = TopIterator();
		
		if(TryToken(TK_LSHIFT)) {
			if (!Add(m)) return false;
			EMIT Expr2(tk.loc, OP_LSH);
		}
		else
		if(TryToken(TK_RSHIFT)) {
			if (!Add(m)) return false;
			EMIT Expr2(tk.loc, OP_RSH);
		}
		else
			break;
	}
	return true;
}

bool SemanticParser::DoCompare(bool m, const FileLocation& loc, OpType op) {
	if (!Shift(m)) return false;
	EMIT Expr2(loc, op);
	return true;
}

bool SemanticParser::Compare(bool m) {
	if (!Shift(m)) return false;
	for(;;) {
		const Token& tk = TopIterator();
		
		if (TryToken(TK_GREQ)) {
			if (!DoCompare(m, tk.loc, OP_GREQ)) return false;
		}
		else if (TryToken(TK_LSEQ)) {
			if (!DoCompare(m, tk.loc, OP_LSEQ)) return false;
		}
		else if (Char('>')) {
			if (!DoCompare(m, tk.loc, OP_GREATER)) return false;
		}
		else if (Char('<')) {
			if (!DoCompare(m, tk.loc, OP_LESS)) return false;
		}
		else
			break;
	}
	return true;
}

bool SemanticParser::Equal(bool m) {
	if (!Compare(m)) return false;
	for(;;) {
		const Token& tk = TopIterator();
		
		if(TryToken(TK_EQ)) {
			if (!Compare(m)) return false;
			EMIT Expr2(tk.loc, OP_EQ);
		}
		else
		if(TryToken(TK_INEQ)) {
			if (!Compare(m)) return false;
			EMIT Expr2(tk.loc, OP_INEQ);
		}
		else
			break;
	}
	return true;
}

bool SemanticParser::BinAnd(bool m) {
	if (!Equal(m)) return false;
	while(/*!IsChar2('&', '&') &&*/ Char('&')) {
		const Token& tk = TopIterator().iter[-1];
		
		if (!Equal(m)) return false;
		EMIT Expr2(tk.loc, OP_BWAND);
	}
	return true;
}

bool SemanticParser::BinXor(bool m) {
	if (!BinAnd(m)) return false;
	while(Char('^')) {
		const Token& tk = TopIterator().iter[-1];
		
		if (!BinAnd(m)) return false;
		EMIT Expr2(tk.loc, OP_BWXOR);
	}
	return true;
}

bool SemanticParser::BinOr(bool m) {
	if (!BinXor(m)) return false;
	while(/*!IsChar2('|', '|') &&*/ Char('|')) {
		const Token& tk = TopIterator().iter[-1];
		
		if (!BinXor(m)) return false;
		EMIT Expr2(tk.loc, OP_BWOR);
	}
	return true;
}

bool SemanticParser::And(bool m) {
	if (!BinOr(m)) return false;
	if(TryToken(TK_LOGAND)) {
		while(TryToken(TK_LOGAND)) {
			const Token& tk = TopIterator().iter[-1];
			
			if (!BinOr(m)) return false;
			EMIT Expr2(tk.loc, OP_AND);
		}
	}
	return true;
}

bool SemanticParser::Or(bool m) {
	if (!And(m)) return false;
	if(TryToken(TK_LOGOR)) {
		while(TryToken(TK_LOGOR)) {
			const Token& tk = TopIterator().iter[-1];
			
			if (!And(m)) return false;
			EMIT Expr2(tk.loc, OP_OR);
		}
	}
	return true;
}

bool SemanticParser::Cond(bool m) {
	if (!Or(m)) return false;
	if(Char('?')) {
		const Token& tk = TopIterator().iter[-1];
		
		if (!Cond(m)) return false;
		PassChar(':');
		if (!Cond(m)) return false;
		EMIT Expr3(tk.loc, OP_COND);
	}
	return true;
}

bool SemanticParser::Assign(bool m) {
	if (!Cond(m)) return false;
	return AssignPost(m);
}

bool SemanticParser::AssignPost(bool m) {
	const Token& tk = TopIterator();
	if(Char('=')) {
		if (!Assign(m)) return false;
		EMIT Expr2(tk.loc, OP_ASSIGN);
	}
	else
	if(TryToken(TK_ADDASS)) {
		if (!Cond(m)) return false;
		EMIT Expr2(tk.loc, OP_ADDASS);
	}
	else
	if(TryToken(TK_SUBASS)) {
		if (!Cond(m)) return false;
		EMIT Expr2(tk.loc, OP_SUBASS);
	}
	else
	if(TryToken(TK_MULASS)) {
		if (!Cond(m)) return false;
		EMIT Expr2(tk.loc, OP_MULASS);
	}
	else
	if(TryToken(TK_DIVASS)) {
		if (!Cond(m)) return false;
		EMIT Expr2(tk.loc, OP_DIVASS);
	}
	else
	if(TryToken(TK_MODASS)) {
		if (!Cond(m)) return false;
		EMIT Expr2(tk.loc, OP_MODASS);
	}
	return true;
}

bool SemanticParser::IsToken(int tk_type) const {
	const Iterator& iter = TopIterator();
	if (!iter) return false;
	return iter->IsType(tk_type);
}

/*bool SemanticParser::IsChar2(int a, int b) const {
	const Iterator& iter = TopIterator();
	if (!iter) return false;
	if (iter.iter + 1 == iter.end) return false;
	return iter.iter[0].IsType(a) && iter.iter[1].IsType(b);
}

bool SemanticParser::Char2(int a, int b) {
	Iterator& iter = TopIterator();
	if (!IsChar2(a,b)) return false;
	iter.iter += 2;
	return true;
}*/

bool SemanticParser::TryToken(int tk_type) {
	Iterator& iter = TopIterator();
	if (!iter || !iter->IsType(tk_type))
		return false;
	iter++;
	return true;
}

bool SemanticParser::PassToken(int tk_type) {
	Iterator& iter = TopIterator();
	if (!iter) {
		AddError(iter->loc, "expected '" + Token::GetTypeStringStatic(tk_type) + "' but got EOL");
		return false;
	}
	if (!iter->IsType(tk_type)) {
		AddError(iter->loc, "expected '" + Token::GetTypeStringStatic(tk_type) + "' but got '" + iter->GetTypeString() + "'");
		return false;
	}
	iter++;
	return true;
}

bool SemanticParser::Id(const char* s) {
	Iterator& iter = TopIterator();
	if (iter->IsType(TK_ID) && iter->str_value == s) {
		iter++;
		return true;
	}
	return false;
}

bool SemanticParser::IsId(const char* s) const {
	const Iterator& iter = TopIterator();
	return iter && iter->IsType(TK_ID) && iter->str_value == s;
}

bool SemanticParser::PassId(const char* s) {
	Iterator& iter = TopIterator();
	if (!iter) {
		AddError(iter->loc, "expected '" + String(s) + "' but got EOL");
		return false;
	}
	if (!Id(s)) {
		AddError(iter->loc, "expected '" + String(s) + "'");
		return false;
	}
	return true;
}

AstNode* SemanticParser::ParseAndFindDeclaration() {
	PathIdentifier id;
	if (!ParsePathIdentifier(id))
		return 0;
	
	AstNode* n = FindDeclaration(id);
	if (!n)
		AddError(TopIterator()->loc, "could not resolve '" + id.ToString() + "'");
	return n;
}

AstNode* SemanticParser::ParseAndFindMetaDeclaration() {
	PathIdentifier id;
	if (!ParsePathIdentifier(id))
		return 0;
	
	AstNode* n = FindDeclaration(id, SEMT_META_ANY);
	if (!n)
		AddError(TopIterator()->loc, "could not resolve '" + id.ToString() + "'");
	return n;
}

String SemanticParser::GetTreeString(int indent) const {
	return root.GetTreeString(indent);
}

String SemanticParser::GetCodeString(const CodeArgs& args) const {
	return root.GetCodeString(args);
}

String SemanticParser::ToString() const {
	return root.ToString();
}

String SemanticParser::GetPath(const AstNode& n) const {
	thread_local static Vector<const AstNode*> tmp;
	AstNode* cur = spath.Top().n;
	
	tmp.SetCount(0);
	const AstNode* iter = &n;
	while (iter && iter != cur) {
		tmp.Add(iter);
		iter = iter->GetSubOwner();
	}
	
	String s;
	for (int i = tmp.GetCount()-1, j = 0; i >= 0; i--, j++) {
		if (j) s.Cat('.');
		s.Cat(tmp[i]->GetName());
	}
	return s;
}

bool SemanticParser::ParseWorld() {
	Iterator& iter = TopIterator();
	if (!PassId("world"))
		return false;
	
	PathIdentifier id;
	if (!ParsePathIdentifier(id)) {
		AddError(iter->loc, "invalid world id");
		return false;
	}
	
	Iterator& owner_iter = TopIterator();
	AstNode& owner = GetTopNode();
	if (owner_iter.node->sub.GetCount()) {
		AstNode& mach = Declare(owner, id);
		mach.src = SEMT_WORLD;
		PushScope(mach);
		if (!ParseWorldStatementList())
			return false;
		PopScope();
	}
	else {
		TODO // declaration-only
	}
	
	return true;
}

bool SemanticParser::ParseSystem() {
	Iterator& iter = TopIterator();
	if (!PassId("system"))
		return false;
	
	PathIdentifier id;
	if (!ParsePathIdentifier(id)) {
		AddError(iter->loc, "invalid system id");
		return false;
	}
	
	Iterator& owner_iter = TopIterator();
	AstNode& owner = GetTopNode();
	AstNode& mach = Declare(owner, id);
	mach.src = SEMT_SYSTEM;
	
	PushScope(mach);
	
	EMIT PushSystem(iter.begin->loc, id);
	
	if (owner_iter.node->sub.GetCount()) {
		if (!ParseSystemStatementList())
			return false;
		
	}
	
	EMIT PopSystem(iter.begin->loc);
	
	PopScope();
	
	return true;
}

bool SemanticParser::ParsePool() {
	Iterator& iter = TopIterator();
	if (!PassId("pool"))
		return false;
	
	PathIdentifier id;
	if (!ParsePathIdentifier(id)) {
		AddError(iter->loc, "invalid pool id");
		return false;
	}
	
	AstNode& owner = GetTopNode();
	AstNode& pool = Declare(owner, id);
	pool.src = SEMT_POOL;
	
	PushScope(pool);
	
	EMIT PushPool(iter.begin->loc, id);
	
	Iterator& owner_iter = TopIterator();
	if (owner_iter.node->sub.GetCount()) {
		if (!ParsePoolStatementList())
			return false;
	}
	
	EMIT PopPool(iter.begin->loc);
	
	PopScope();
	
	return true;
}

bool SemanticParser::ParseEntity() {
	Iterator& iter = TopIterator();
	if (!PassId("entity"))
		return false;
	
	PathIdentifier id;
	if (!ParsePathIdentifier(id)) {
		AddError(iter->loc, "invalid entity id");
		return false;
	}
	
	AstNode& owner = GetTopNode();
	AstNode& ent = Declare(owner, id);
	ent.src = SEMT_ENTITY;
	
	PushScope(ent);
	
	EMIT PushEntity(iter.begin->loc, id);
	
	Iterator& owner_iter = TopIterator();
	if (owner_iter.node->sub.GetCount()) {
		if (!ParseEntityStatementList())
			return false;
	}
	
	EMIT PopEntity(iter.begin->loc);
	
	PopScope();
	
	return true;
}

bool SemanticParser::ParseComponent() {
	Iterator& iter = TopIterator();
	if (!PassId("comp"))
		return false;
	
	PathIdentifier id;
	if (!ParsePathIdentifier(id)) {
		AddError(iter->loc, "invalid component id");
		return false;
	}
	
	AstNode& owner = GetTopNode();
	AstNode& comp = Declare(owner, id);
	comp.src = SEMT_COMPONENT;
	
	PushScope(comp);
	
	EMIT PushComponent(iter.begin->loc, id);
	
	Iterator& owner_iter = TopIterator();
	if (owner_iter.node->sub.GetCount()) {
		if (!ParseComponentStatementList())
			return false;
	}
	
	EMIT PopComponent(iter.begin->loc);
	
	PopScope();
	
	return true;
}


bool SemanticParser::ParseMachine() {
	Iterator& iter = TopIterator();
	if (iter->str_value != "machine") {
		AddError(iter->loc, "expected 'machine'");
		return false;
	}
	iter++;
	
	PathIdentifier id;
	if (!ParsePathIdentifier(id)) {
		AddError(iter->loc, "invalid machine id");
		return false;
	}
	
	AstNode& owner = GetTopNode();
	AstNode& mach = Declare(owner, id);
	mach.src = SEMT_MACHINE;
	
	PushScope(mach);
	
	EMIT PushMachine(iter.begin->loc, id);
	
	Iterator& owner_iter = TopIterator();
	if (owner_iter.node->sub.GetCount()) {
		if (!ParseMachineStatementList())
			return false;
	}
	
	EMIT PopMachine(iter.begin->loc);
	
	PopScope();
	
	return true;
}

bool SemanticParser::ParseChain() {
	Iterator& iter = TopIterator();
	if (iter->str_value != "chain") {
		AddError(iter->loc, "expected 'chain'");
		return false;
	}
	iter++;
	
	PathIdentifier id;
	if (!ParsePathIdentifier(id)) {
		AddError(iter->loc, "invalid chain id");
		return false;
	}
	
	AstNode& owner = GetTopNode();
	AstNode& chain = Declare(owner, id);
	chain.src = SEMT_CHAIN;
	
	PushScope(chain);
	
	EMIT PushChain(iter.begin->loc, id);
	
	Iterator& owner_iter = TopIterator();
	if (owner_iter.node->sub.GetCount()) {
		if (!ParseChainStatementList())
			return false;
	}
	
	EMIT PopChain(iter.begin->loc);
	
	PopScope();
	
	return true;
}

bool SemanticParser::ParseLoop() {
	Iterator& iter = TopIterator();
	
	bool is_driver = false;
	
	if (IsId("driver")) {
		is_driver = true;
		iter++;
	}
	else if (!PassId("loop"))
		return false;
	
	PathIdentifier id;
	if (!ParsePathIdentifier(id)) {
		AddError(iter->loc, "invalid loop id");
		return false;
	}
	
	AstNode& owner = GetTopNode();
	AstNode& loop = Declare(owner, id);
	loop.src = SEMT_LOOP;
	
	PushScope(loop);
	
	EMIT PushLoop(iter.begin->loc, id);
	
	Iterator& owner_iter = TopIterator();
	if (owner_iter.node->sub.GetCount()) {
		if (!ParseLoopStatementList())
			return false;
	}
	else {
		loop.src = SEMT_LOOP_DECL;
	}
	
	EMIT PopLoop(iter.begin->loc);
	
	PopScope();
	
	return true;
}

bool SemanticParser::ParseAtom(PathIdentifier& id) {
	Iterator& iter = TopIterator();
	
	AstNode& owner = GetTopNode();
	AstNode& atom = Declare(owner, id);
	
	PushScope(atom);
	
	EMIT PushAtom(iter.begin->loc, id);
	
	if (!IsLineEnd()) {
		if (TryToken('[')) {
			int c = 0;
			while (!TryToken(']')) {
				if (c == 0)
					EMIT PushAtomConnector(iter->loc, 0);
				
				AstNode& src_cond = atom.Add("src");
				PushScope(src_cond);
				allow_expr_unresolved = true;
				bool succ = Cond(false);
				allow_expr_unresolved = false;
				if (!succ)
					return false;
				PopScope();
				
				
				TryToken(',');
				c++;
			}
			if (c > 0)
				EMIT PopAtomConnector(iter->loc);
			
			if (TryToken('[')) {
				int c = 0;
				while (!TryToken(']')) {
					if (c == 0)
						EMIT PushAtomConnector(iter->loc, 1);
					
					AstNode& sink_cond = atom.Add("sink");
					PushScope(sink_cond);
					allow_expr_unresolved = true;
					bool succ = Cond(false);
					allow_expr_unresolved = false;
					if (!succ)
						return false;
					PopScope();
					
					TryToken(',');
					c++;
				}
				
				if (c > 0)
					EMIT PopAtomConnector(iter->loc);
			}
		}
		else {
			AddError(iter->loc, "unexpected token");
			return false;
		}
	}
	
	if (iter.node->sub.GetCount()) {
		
		if (!ParseAtomStatementList())
			return false;
		
	}
	
	EMIT PopAtom(iter.begin->loc);
	
	PopScope();
	
	return true;
}

bool SemanticParser::ParseState() {
	Iterator& iter = TopIterator();
	
	if (!PassId("state"))
		return false;
	
	PathIdentifier id;
	if (!ParsePathIdentifier(id)) {
		AddError(iter->loc, "id parsing failed");
		return false;
	}
	
	AstNode& owner = GetTopNode();
	AstNode& state = Declare(owner, id);
	
	EMIT PushState(iter->loc, id);
	EMIT PopState(iter->loc);
	
	return true;
}

bool SemanticParser::ParseMachineStatementList() {
	Iterator& iter = TopIterator();
	const TokenNode& owner = *path.Top();
	const TokenNode*& cur = path.Add();
	
	EMIT PushStatementList(iter->loc);
	
	for(const TokenNode& tns : owner.sub) {
		cur = &tns;
		if (!ParseMachineStatement())
			return false;
	}
	
	path.Remove(path.GetCount()-1);
	
	EMIT PopStatementList(iter->loc);
	
	return true;
}

bool SemanticParser::ParseMachineStatement() {
	const TokenNode& cur = *path.Top();
	Iterator& iter = AddIterator(cur);
	
	if (iter) {
		
		if (iter->IsType(TK_ID)) {
			const String& id = iter->str_value;
			//DUMP(id);
			
			if (id == "chain") {
				if (!ParseChain())
					return false;
			}
			else if (id == "loop" || id == "driver") {
				if (!ParseLoop())
					return false;
			}
			else if (id == "meta") {
				if (!ParseMeta())
					return false;
			}
			else if (id == "pass") {
				// pass
				iter++;
			}
			else {
				AddError(cur.begin->loc, "invalid machine statement");
				PopIterator();
				return false;
			}
		}
		else {
			DUMP(cur);
			TODO
		}
		
	}
	
	if (iter) {
		AddError(iter->loc, "expected end-of-statement");
		return false;
	}
	
	PopIterator();
	return true;
}

bool SemanticParser::ParseChainStatementList() {
	const TokenNode& owner = *path.Top();
	const TokenNode*& cur = path.Add();
	
	EMIT PushStatementList(owner.begin->loc);
	
	for(const TokenNode& tns : owner.sub) {
		cur = &tns;
		if (!ParseChainStatement())
			return false;
	}
	
	path.Remove(path.GetCount()-1);
	
	EMIT PopStatementList(owner.end->loc);
	
	return true;
}

bool SemanticParser::ParseChainStatement() {
	const TokenNode& cur = *path.Top();
	Iterator& iter = AddIterator(cur);
	
	if (iter) {
		
		if (iter->IsType(TK_ID)) {
			const String& id = iter->str_value;
			//DUMP(id);
			
			if (id == "loop" || id == "driver") {
				if (!ParseLoop())
					return false;
			}
			else if (id == "state") {
				if (!ParseState())
					return false;
			}
			else if (id == "meta") {
				if (!ParseMeta())
					return false;
			}
			else if (id == "pass") {
				// pass
				iter++;
			}
			else {
				AddError(cur.begin->loc, "invalid chain statement");
				PopIterator();
				return false;
			}
		}
		else {
			DUMP(cur);
			TODO
		}
		
	}
	
	if (iter) {
		AddError(iter->loc, "expected end-of-statement");
		return false;
	}
	
	PopIterator();
	return true;
}

bool SemanticParser::ParseLoopStatementList() {
	const TokenNode& owner = *path.Top();
	const TokenNode*& cur = path.Add();
	
	EMIT PushStatementList(owner.begin->loc);
	
	for(const TokenNode& tns : owner.sub) {
		cur = &tns;
		if (!ParseLoopStatement())
			return false;
	}
	
	path.Remove(path.GetCount()-1);
	
	EMIT PopStatementList(owner.end->loc);
	
	return true;
}

bool SemanticParser::ParseLoopStatement() {
	const TokenNode& cur = *path.Top();
	Iterator& iter = AddIterator(cur);
	
	if (iter) {
		
		if (IsId("meta")) {
			if (!ParseMeta())
				return false;
		}
		else if (Id("pass")) {
			// pass
		}
		else if (iter->IsType(TK_ID) || iter->IsType('$')) {
			
			PathIdentifier id;
			if (!ParsePathIdentifier(id)) {
				AddError(iter->loc, "id parsing failed");
				return false;
			}
			
			if (!iter || iter->IsType('[') || cur.sub.GetCount()) {
				if (!ParseAtom(id))
					return false;
			}
			else if (iter->IsType('=')) {
				EMIT PushStatement(iter->loc, STMT_EXPR);
				
				if (!AssignPost(false))
					return false;
				
				EMIT PopStatement(iter->loc);
			}
			else if (IsToken('(')) {
				if (!ParseCallArguments())
					return false;
			}
			else {
				AddError(iter->loc, "invalid loop statement");
				return false;
			}
		}
		else {
			AddError(iter->loc, "invalid statement");
			return false;
		}
	}
	
	if (iter) {
		AddError(iter->loc, "expected end-of-statement");
		return false;
	}
	
	PopIterator();
	return true;
}

bool SemanticParser::ParseMeta() {
	
	if (!PassId("meta"))
		return false;
	
	if (IsId("def") ||
		IsId("if") ||
		IsId("do") ||
		IsId("while") ||
		IsId("for") ||
		IsId("break") ||
		IsId("continue") ||
		IsId("case") ||
		IsId("default") ||
		IsId("else") ||
		IsId("return") ||
		IsId("switch")
		) {
		return ParseMetaStatement(1);
	}
	else {
		return ParseMetaDeclExpr(false);
	}
	return true;
}

bool SemanticParser::ParseWorldStatementList() {
	Iterator& iter = TopIterator();
	const TokenNode& owner = *path.Top();
	const TokenNode*& cur = path.Add();
	
	EMIT PushStatementList(iter->loc);
	
	for(const TokenNode& tns : owner.sub) {
		cur = &tns;
		if (!ParseWorldStatement())
			return false;
	}
	
	path.Remove(path.GetCount()-1);
	
	EMIT PopStatementList(iter->loc);
	
	return true;
}

bool SemanticParser::ParseWorldStatement() {
	const TokenNode& cur = *path.Top();
	Iterator& iter = AddIterator(cur);
	
	if (iter) {
		
		if (IsId("meta")) {
			if (!ParseMeta())
				return false;
		}
		else if (Id("pass")) {
			// pass
		}
		else if (IsId("system")) {
			if (!ParseSystem())
				return false;
		}
		else if (IsId("pool")) {
			if (!ParsePool())
				return false;
		}
		else {
			AddError(iter->loc, "invalid statement");
			return false;
		}
	}
	
	if (iter) {
		AddError(iter->loc, "expected end-of-statement");
		return false;
	}
	
	PopIterator();
	return true;
}

bool SemanticParser::ParseSystemStatementList() {
	Iterator& iter = TopIterator();
	const TokenNode& owner = *path.Top();
	const TokenNode*& cur = path.Add();
	
	EMIT PushStatementList(iter->loc);
	
	for(const TokenNode& tns : owner.sub) {
		cur = &tns;
		if (!ParseSystemStatement())
			return false;
	}
	
	path.Remove(path.GetCount()-1);
	
	EMIT PopStatementList(iter->loc);
	
	return true;
}

bool SemanticParser::ParseSystemStatement() {
	const TokenNode& cur = *path.Top();
	Iterator& iter = AddIterator(cur);
	
	if (iter) {
		if (Id("pass")) {
			// pass
		}
		else if (IsId("meta")) {
			if (!ParseMeta())
				return false;
		}
		else if (iter->IsType(TK_ID)) {
			EMIT PushStatement(iter->loc, STMT_EXPR);
			
			allow_expr_unresolved = true;
			bool succ = Assign(false);
			allow_expr_unresolved = false;
			if (!succ)
				return false;
			
			EMIT PopStatement(iter->loc);
		}
		else {
			AddError(iter->loc, "invalid statement");
			return false;
		}
	}
	
	if (iter) {
		AddError(iter->loc, "expected end-of-statement");
		return false;
	}
	
	PopIterator();
	return true;
}

bool SemanticParser::ParsePoolStatementList() {
	Iterator& iter = TopIterator();
	const TokenNode& owner = *path.Top();
	const TokenNode*& cur = path.Add();
	
	EMIT PushStatementList(iter->loc);
	
	for(const TokenNode& tns : owner.sub) {
		cur = &tns;
		if (!ParsePoolStatement())
			return false;
	}
	
	path.Remove(path.GetCount()-1);
	
	EMIT PopStatementList(iter->loc);
	
	return true;
}

bool SemanticParser::ParsePoolStatement() {
	const TokenNode& cur = *path.Top();
	Iterator& iter = AddIterator(cur);
	
	if (iter) {
		if (Id("pass")) {
			// pass
		}
		else if (IsId("meta")) {
			if (!ParseMeta())
				return false;
		}
		else if (IsId("entity")) {
			if (!ParseEntity())
				return false;
		}
		else {
			AddError(iter->loc, "invalid statement");
			return false;
		}
	}
	
	if (iter) {
		AddError(iter->loc, "expected end-of-statement");
		return false;
	}
	
	PopIterator();
	return true;
}

bool SemanticParser::ParseEntityStatementList() {
	Iterator& iter = TopIterator();
	const TokenNode& owner = *path.Top();
	const TokenNode*& cur = path.Add();
	
	EMIT PushStatementList(iter->loc);
	
	for(const TokenNode& tns : owner.sub) {
		cur = &tns;
		if (!ParseEntityStatement())
			return false;
	}
	
	path.Remove(path.GetCount()-1);
	
	EMIT PopStatementList(iter->loc);
	
	return true;
}

bool SemanticParser::ParseEntityStatement() {
	const TokenNode& cur = *path.Top();
	Iterator& iter = AddIterator(cur);
	
	if (iter) {
		if (Id("pass")) {
			// pass
		}
		else if (IsId("meta")) {
			if (!ParseMeta())
				return false;
		}
		else if (IsId("comp")) {
			if (!ParseComponent())
				return false;
		}
		else {
			AddError(iter->loc, "invalid statement");
			return false;
		}
	}
	
	if (iter) {
		AddError(iter->loc, "expected end-of-statement");
		return false;
	}
	
	PopIterator();
	return true;
}

bool SemanticParser::ParseComponentStatementList() {
	Iterator& iter = TopIterator();
	const TokenNode& owner = *path.Top();
	const TokenNode*& cur = path.Add();
	
	EMIT PushStatementList(iter->loc);
	
	for(const TokenNode& tns : owner.sub) {
		cur = &tns;
		if (!ParseComponentStatement())
			return false;
	}
	
	path.Remove(path.GetCount()-1);
	
	EMIT PopStatementList(iter->loc);
	
	return true;
}

bool SemanticParser::ParseComponentStatement() {
	const TokenNode& cur = *path.Top();
	Iterator& iter = AddIterator(cur);
	
	if (iter) {
		if (Id("pass")) {
			// pass
		}
		else if (IsId("meta")) {
			if (!ParseMeta())
				return false;
		}
		else if (IsToken(TK_ID)) {
			EMIT PushStatement(iter->loc, STMT_EXPR);
			
			allow_expr_unresolved = true;
			bool succ = Assign(false);
			allow_expr_unresolved = false;
			if (!succ)
				return false;
			
			EMIT PopStatement(iter->loc);
		}
		else {
			AddError(iter->loc, "invalid statement");
			return false;
		}
	}
	
	if (iter) {
		AddError(iter->loc, "expected end-of-statement");
		return false;
	}
	
	PopIterator();
	return true;
}

/*bool SemanticParser::ParseMetaExpressionStatement() {
	Iterator& iter = TopIterator();
	
	AstNode* decl = ParseAndFindMetaDeclaration();
	
	if (!decl) {
		PopIterator();
		return false;
	}
	
	if (!IsMetaTypedNode(decl->src)) {
		if (!iter)
			return true;
		
		return AssignPost(true);
	}
	else {
		bool succ = ParseMetaDeclExprPost(decl, true);
		PopIterator();
		return succ;
	}
}*/

/*bool SemanticParser::IsMetaTypeQualifier() const {
	if (IsId("stmt") ||
		IsId("params"))
		return true;
	
	return false;
}*/




NAMESPACE_TOPSIDE_END

#undef EMIT
