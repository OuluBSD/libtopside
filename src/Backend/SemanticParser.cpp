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
		CHECK_SPATH_BEGIN
		
		cur = &tns;
		if (!ParseDeclaration())
			return false;
		
		CHECK_SPATH_END
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
	
	int cookie = 0;
	if (!IsLineEnd()) {
		CHECK_SPATH_BEGIN
		
		if (IsId("def")) {
			if (!ParseClass())
				return false;
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
		else if (IsId("meta")) {
			if (!ParseMeta(cookie))
				return false;
		}
		else {
			bool prev;
			{
				Scope& t = spath.Top();
				prev = t.must_declare;
				t.must_declare = true;
			}
			
			if (!ParseExpression(false))
				return false;
			
			{
				Scope& t = spath.Top();
				t.must_declare = prev;
			}
		}
		
		CHECK_SPATH_END
	}
	
	PopIterator();
	return true;
}

bool SemanticParser::ParseFunction(AstNode& ret_type, const PathIdentifier& name) {
	Iterator& iter = TopIterator();
	const TokenNode& cur = *path.Top();
	ASSERT(iter.Check(cur));
	ASSERT(iter->IsType('('));
	
	AstNode* var = EMIT PushFunction(name.begin->loc, ret_type, name);
	if (!var) return false;
	
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
		
		if (!ParseStatementList())
			return false;
		
	}
	
	EMIT PopFunction(cur.end->loc);
	
	EMIT PushRval(iter->loc, *var);
	
	return true;
}

bool SemanticParser::ParseMetaFunction(AstNode& ret_type, const PathIdentifier& name) {
	Iterator& iter = TopIterator();
	const TokenNode& cur = *path.Top();
	ASSERT(iter.Check(cur));
	ASSERT(iter->IsType('('));
	
	AstNode* var = EMIT PushMetaFunction(name.begin->loc, ret_type, name);
	if (!var) return false;
	
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
		else if (ret_type.name == "expr") {
			if (!ParseExpressionList())
				return false;
		}
		else if (!ParseStatementList())
			return false;
		
	}
	
	EMIT PopMetaFunction(cur.end->loc);
	
	EMIT PushRval(iter->loc, *var);
	
	return true;
}

bool SemanticParser::ParseAtomStatementList() {
	bool succ = true;
	
	const TokenNode& tk_owner = *path.Top();
	
	EMIT PushStatementList(tk_owner.end->loc);
	
	allow_expr_unresolved = true;
	
	int cookie = 0;
	const TokenNode*& sub = path.Add();
	for (const TokenNode& s : tk_owner.sub) {
		sub = &s;
		AddIterator(s);
		
		Iterator& iter = TopIterator();
		if (!iter)
			continue;
		
		if (IsId("meta")) {
			if (!ParseMeta(cookie)) {
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
	
	EMIT PopStatementList(tk_owner.end->loc);
	
	return succ;
}

bool SemanticParser::ParseAtomExpressionStatement() {
	const TokenNode& cur = CurrentNode();
	Iterator& iter = TopIterator();
	
	EMIT PushStatement(iter->loc, STMT_EXPR);
	
	bool succ = Assign(false);
	
	AstNode* ret = EMIT PopExpr(iter->loc);
	
	EMIT PopStatement(iter->loc, ret);
	
	return succ;
}

bool SemanticParser::ParseStatementList() {
	bool succ = true;
	
	const TokenNode& tk_owner = *path.Top();
	
	EMIT PushStatementList(tk_owner.end->loc);
	
	int cookie = 0;
	const TokenNode*& sub = path.Add();
	for (const TokenNode& s : tk_owner.sub) {
		sub = &s;
		AddIterator(s);
		
		Iterator& iter = TopIterator();
		if (!iter)
			continue;
		
		CHECK_SPATH_BEGIN
		
		if (IsId("meta")) {
			if (!ParseMeta(cookie))
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
		
		CHECK_SPATH_END
		
		PopIterator();
	}
	path.Remove(path.GetCount()-1);
	
	EMIT PopStatementList(tk_owner.end->loc);
	
	return succ;
}

bool SemanticParser::ParseStatement() {
	const TokenNode& cur = CurrentNode();
	Iterator& iter = TopIterator();
	int cookie = 0;
	AstNode* link;
	
	if (IsId("meta")) {
		return ParseMetaStatement(cookie);
	}
	else if (Id("if")) {
		EMIT PushStatement(iter->loc, STMT_IF);
		
		if (!(link = ParseExpression(false))) return false;
		if (!ParseStatementBlock()) return false;
		
		EMIT PopStatement(iter->loc, link);
	}
	else if (IsId("else")) {
		AstNode& t = GetTopNode();
		if (t.sub.IsEmpty()) {
			AddError(iter->loc, "'else' without 'if'");
			return false;
		}
		AstNode& prev = t.sub.Top();
		if (prev.src != SEMT_STATEMENT || prev.stmt != STMT_IF) {
			AddError(iter->loc, "'else' without 'if'");
			return false;
		}
		
		PassId("else");
		
		AstNode* e = EMIT PushStatement(iter->loc, STMT_ELSE);
		if (!e) return false;
		
		ASSERT(!prev.ctx_next && !e->ctx_next);
		prev.ctx_next = e;
		e->ctx_next = &prev;
		
		if (!ParseStatementBlock()) return false;
		
		EMIT PopStatement(iter->loc, 0);
	}
	else if (Id("do")) {
		EMIT PushStatement(iter->loc, STMT_DOWHILE);
		
		if (!ParseStatementBlock()) return false;
		if (!PassId("while")) return false;
		if (!(link = ParseExpression(false))) return false;
		if (!PassToken(';')) return false;
		
		EMIT PopStatement(iter->loc, link);
	}
	else if (Id("while")) {
		EMIT PushStatement(iter->loc, STMT_WHILE);
		
		if (!(link = ParseExpression(false))) return false;
		if (!ParseStatementBlock()) return false;
		
		EMIT PopStatement(iter->loc, link);
	}
	else if (Id("for")) {
		EMIT PushStatement(iter->loc, STMT_FOR);
		
		if (!IsToken(',')) {
			if (!ParseExpression(false)) return false;
		}
		if (Id("in") || Char(':')) {
			EMIT PushStatement(iter->loc, STMT_FOR_RANGE);
			if (!ParseExpression(false)) return false;
			EMIT PopStatement(iter->loc, 0);
		}
		else {
			if (!PassToken(',')) return false;
			if (!IsToken(',')) {
				EMIT PushStatement(iter->loc, STMT_FOR_COND);
				if (!ParseExpression(false)) return false;
				EMIT PopStatement(iter->loc, 0);
			}
			if (!PassToken(',')) return false;
			if (iter) {
				EMIT PushStatement(iter->loc, STMT_FOR_POST);
				if (!ParseExpression(false)) return false;
				EMIT PopStatement(iter->loc, 0);
			}
		}
		
		if (!ParseStatementBlock()) return false;
		
		EMIT PopStatement(iter->loc, 0);
	}
	else if (Id("break")) {
		EMIT PushStatement(iter->loc, STMT_BREAK);
		EMIT PopStatement(iter->loc, 0);
	}
	else if (Id("continue")) {
		EMIT PushStatement(iter->loc, STMT_CONTINUE);
		EMIT PopStatement(iter->loc, 0);
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
		
		bool b;
		{
			Scope& s = spath.Top();
			b = s.no_declare;
			s.no_declare = true;
		}
		
		link = 0;
		if (iter) {
			if (!Assign(false)) return false;
			link = EMIT PopExpr(iter->loc);
		}
		
		{
			Scope& s = spath.Top();
			s.no_declare = b;
		}
		
		EMIT PopStatement(iter->loc, link);
	}
	else if (Id("switch")) {
		EMIT PushStatement(iter->loc, STMT_SWITCH);
		
		if (!(link = ParseExpression(false))) return false;
		
		if (!ParseSwitchBlock()) return false;
		
		EMIT PopStatement(iter->loc, link);
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
		AstNode* ret = EMIT PopExpr(iter->loc);
		EMIT PopStatement(iter->loc, ret);
	}
	else if (cur.begin == cur.end && cur.sub.GetCount()) {
		EMIT PushStatement(iter->loc, STMT_BLOCK);
		
		if (!ParseStatementBlock()) return false;
		
		EMIT PopStatement(iter->loc, 0);
	}
	else if (cur.begin == cur.end) {
		// empty statement
	}
	else {
		if (!ParseExpressionStatement())
			return false;
	}
	
	return true;
}

bool SemanticParser::ParseExpressionStatement() {
	Iterator& iter = TopIterator();
	
	CHECK_SPATH_BEGIN
	
	EMIT PushStatement(iter->loc, STMT_EXPR);
	
	AstNode* link;
	if (!(link = ParseExpression(false))) return false;
	
	if (link->rval && link->rval->src == SEMT_CTOR)
		link = 0;
	
	EMIT PopStatement(iter->loc, link);
	
	CHECK_SPATH_END
	return true;
}

bool SemanticParser::Id2(const char* a, const char* b) {
	Iterator& iter = TopIterator();
	if (iter.iter != iter.end && iter.iter+1 != iter.end &&
		iter.iter->type == TK_ID && iter.iter->str_value == "meta" &&
		iter.iter->type == TK_ID && iter.iter->str_value == "else") {
		iter.iter += 2;
		return true;
	}
	return false;
}

bool SemanticParser::ParseMetaStatement(int& cookie, bool skip_meta_keywords) {
	const TokenNode& cur = CurrentNode();
	Iterator& iter = TopIterator();
	
	if (!skip_meta_keywords && !PassId("meta"))
		return false;
	
	AstNode* link = 0;
	int prev_cookie = cookie;
	cookie = 0;
	
	if (Id("if")) {
		EMIT PushStatement(iter->loc, STMT_META_IF);
		
		if (!(link = ParseExpression(true))) return false;
		if (!ParseStatementBlock()) return false;
		
		EMIT PopStatement(iter->loc, link);
		
		cookie |= COOKIE_IF;
	}
	else if (prev_cookie & COOKIE_IF && Id("else")) {
		AstNode& t = GetTopNode();
		if (t.sub.IsEmpty()) {
			AddError(iter->loc, "'else' without 'if'");
			return false;
		}
		AstNode& prev = t.sub.Top();
		if (prev.src != SEMT_STATEMENT || prev.stmt != STMT_META_IF) {
			AddError(iter->loc, "'else' without 'if'");
			return false;
		}
		
		AstNode* e = EMIT PushStatement(iter->loc, STMT_META_ELSE);
		if (!e) return false;
		
		ASSERT(!prev.ctx_next && !e->ctx_next);
		prev.ctx_next = e;
		e->ctx_next = &prev;
		
		if (!ParseStatementBlock()) return false;
		
		EMIT PopStatement(iter->loc, 0);
	}
	else if (Id("do")) {
		EMIT PushStatement(iter->loc, STMT_META_DOWHILE);
		
		if (!ParseStatementBlock()) return false;
		if (!PassId("while")) return false;
		if (!(link = ParseExpression(true))) return false;
		if (!PassToken(';')) return false;
		
		EMIT PopStatement(iter->loc, link);
	}
	else if (Id("while")) {
		EMIT PushStatement(iter->loc, STMT_META_WHILE);
		
		if (!(link = ParseExpression(true))) return false;
		if (!ParseStatementBlock()) return false;
		
		EMIT PopStatement(iter->loc, link);
	}
	else if (Id("for")) {
		EMIT PushStatement(iter->loc, STMT_META_FOR);
		
		if (!IsToken(',')) {
			EMIT PushStatement(iter->loc, STMT_EXPR);
			AstNode* rval = EMIT ParseExpression(true);
			if (!rval) return false;
			EMIT PopStatement(iter->loc, 0);
		}
		if (Id("in") || Char(':')) {
			EMIT PushStatement(iter->loc, STMT_META_FOR_RANGE);
			AstNode* rval = EMIT ParseExpression(true);
			if (!rval) return false;
			EMIT PopStatement(iter->loc, 0);
		}
		else {
			if (!PassToken(',')) return false;
			if (!IsToken(',')) {
				EMIT PushStatement(iter->loc, STMT_META_FOR_COND);
				if (!ParseExpression(true)) return false;
				EMIT PopStatement(iter->loc, 0);
			}
			if (!PassToken(',')) return false;
			if (iter) {
				EMIT PushStatement(iter->loc, STMT_META_FOR_POST);
				if (!ParseExpression(true)) return false;
				EMIT PopStatement(iter->loc, 0);
			}
		}
		
		if (!ParseStatementBlock()) return false;
		
		EMIT PopStatement(iter->loc, 0);
	}
	else if (Id("break")) {
		EMIT PushStatement(iter->loc, STMT_META_BREAK);
		EMIT PopStatement(iter->loc, 0);
	}
	else if (Id("continue")) {
		EMIT PushStatement(iter->loc, STMT_META_CONTINUE);
		EMIT PopStatement(iter->loc, 0);
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
			if (!(link = ParseExpression(true))) return false;
		}
		
		EMIT PopStatement(iter->loc, link);
	}
	else if (Id("switch")) {
		EMIT PushStatement(iter->loc, STMT_META_SWITCH);
		
		if (!(link = ParseExpression(true))) return false;
		
		if (!ParseSwitchBlock()) return false;
		
		EMIT PopStatement(iter->loc, link);
	}
	else if (cur.begin == cur.end && cur.sub.GetCount()) {
		EMIT PushStatement(iter->loc, STMT_BLOCK);
		
		if (!ParseStatementBlock()) return false;
		
		EMIT PopStatement(iter->loc, 0);
	}
	else if (cur.begin == cur.end) {
		// empty statement
	}
	else {
		EMIT PushStatement(iter->loc, STMT_META_EXPR);
		
		if (!(link = ParseExpression(true))) return false;
		
		EMIT PopStatement(iter->loc, 0);
	}
	
	return true;
}

bool SemanticParser::ParseType(PathIdentifier& type, AstNode*& tn) {
	Iterator& iter = TopIterator();
	
	if (!ParsePathIdentifier(type, true, false))
		return false;
	
	if (!iter) {
		AddError(iter->loc, "unexpeced end of parameter");
		return false;
	}
	
	tn = FindDeclaration(type);
	if (!tn || !IsTypedNode(tn->src)) {
		AddError(iter->loc, "could not find type '" + type.ToString() + "'");
		return false;
	}
	
	if (TryToken('[')) {
		// TODO evaluate expression
		if (IsToken('$')) {
			TODO
		}
		else if (IsToken(TK_INTEGER)) {
			int i = StrInt(iter->str_value);
			AstNode& arr = tn->Add(iter->loc, IntStr(i));
			arr.src = SEMT_ARRAYSIZE;
			arr.i64 = i;
			tn = &arr;
			iter++;
		}
		else {
			AddError(iter->loc, "not supported (yet?)");
			return false;
		}
		
		if (!PassToken(']'))
			return false;
	}
	
	if (iter && (iter->type == '#' || iter->type == '&')) {
		ASSERT_(type.tail_count == 0, "TODO mixed pointers");
	}
	
	while (iter) {
		if (iter->type == '#') {
			tn = &tn->GetAdd(iter->loc, SEMT_TYPE_POINTER);
			type.tail[type.tail_count++] = PathIdentifier::PTR;
		}
		else if (iter->type == '&') {
			tn = &tn->GetAdd(iter->loc, SEMT_TYPE_LREF);
			type.tail[type.tail_count++] = PathIdentifier::LREF;
		}
		else break;
		iter++;
	}
	
	return true;
}

bool SemanticParser::ParseParameter() {
	Iterator& iter = TopIterator();
	const TokenNode& cur = *path.Top();
	ASSERT(iter.Check(cur));
	
	PathIdentifier type;
	AstNode* tn;
	if (!ParseType(type, tn))
		return false;
	
	PathIdentifier name;
	if (!iter->IsType(',')) {
		if (!ParsePathIdentifier(name, false, false))
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
	if (!ParsePathIdentifier(type, true, false))
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
		if (!ParsePathIdentifier(name, false, false))
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

bool SemanticParser::ParsePathIdentifier(PathIdentifier& id, bool declare, bool resolve) {
	Iterator& iter = TopIterator();
	id.Clear();
	id.begin = iter;
	
	const Token* end = iter.end;
	bool expect_dot = false;
	bool tail = false;
	
	if (resolve) {
		while (iter) {
			if (iter->IsType('#')) {
				if (id.head_count >= PathIdentifier::MAX_TAIL_COUNT) {
					AddError(iter->loc, "too many qualifiers");
					return false;
				}
				
				id.head[id.head_count++] = PathIdentifier::PTR;
			}
			else if (iter->IsType('&')) {
				if (id.head_count >= PathIdentifier::MAX_TAIL_COUNT) {
					AddError(iter->loc, "too many qualifiers");
					return false;
				}
				
				id.head[id.head_count++] = PathIdentifier::LREF;
			}
			else break;
			iter++;
		}
	}
	
	if (declare && iter && iter->IsType(TK_ID) && iter->str_value == "const") {
		id.is_const = true;
		iter++;
	}
	
	while (iter) {
		if (iter->IsType('#') || iter->IsType('&')) {
			if (declare && id.part_count > 0)
				tail = true;
			break;
		}
		else if (expect_dot) {
			if (!iter->IsType('.')) {
				end = iter;
				break;
			}
			expect_dot = false;
		}
		else {
			if (iter->IsType(TK_ID) && iter->str_value == "meta") {
				if (!id.part_count) {
					AddError(iter->loc, "unexpected 'meta' keyword");
					return false;
				}
				break;
			}
			else if (iter->IsType(TK_ID) || iter->IsType(TK_INTEGER)) {
				id.parts[id.part_count++] = iter;
				expect_dot = true;
			}
			else if (iter->IsType('$')) {
				id.is_meta[id.part_count] = true;
			}
			else {
				AddError(iter->loc, "unexpected token " + iter->GetTypeString());
				return false;
			}
		}
		iter++;
	}
	
	if (tail) {
		while (iter) {
			if (iter->IsType('#')) {
				if (id.tail_count >= PathIdentifier::MAX_TAIL_COUNT) {
					AddError(iter->loc, "too many qualifiers");
					return false;
				}
				
				id.tail[id.tail_count++] = PathIdentifier::PTR;
			}
			else if (iter->IsType('&')) {
				if (id.tail_count >= PathIdentifier::MAX_TAIL_COUNT) {
					AddError(iter->loc, "too many qualifiers");
					return false;
				}
				
				id.tail[id.tail_count++] = PathIdentifier::LREF;
			}
			else break;
			iter++;
		}
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
	Iterator& iter = TopIterator();
	const TokenNode& cur = *path.Top();
	
	if (!PassId("def"))
		return false;
	
	PathIdentifier name;
	if (!ParsePathIdentifier(name, false, false)) {
		AddError(iter->loc, "could not parse name");
		return false;
	}
	
	AstNode* var = EMIT PushClass(name.begin->loc, name);
	if (!var) return false;
	
	if (!iter && cur.sub.GetCount()) {
		
		if (!ParseStatementList())
			return false;
		
	}
	
	EMIT PopClass(cur.end->loc);
	
	EMIT PushRval(iter->loc, *var);
	
	return true;
}

bool SemanticParser::ParseStatementBlock() {
	if (!ParseStatementList())
		return false;
	
	return true;
}

bool SemanticParser::ParseDeclExpr(bool meta, const PathIdentifier& type_id, AstNode& tn) {
	const TokenNode& cur = *path.Top();
	Iterator& iter = TopIterator();
	
	PathIdentifier name;
	
	if (!ParsePathIdentifier(name, false, false)) {
		AddError(iter->loc, "could not parse name");
		return false;
	}
	
	if (IsChar('(') && cur.sub.GetCount()) {
		if (meta) {
			if (!ParseMetaFunction(tn, name))
				return false;
		}
		else {
			if (!ParseFunction(tn, name))
				return false;
		}
	}
	else {
		AstNode* var = EMIT DeclareVariable(type_id.begin->loc, tn, name);
		if (!var)
			return false;
		
		if (Char('[')) {
			AstNode* ctor = EMIT PushConstructor(iter->loc, meta, tn, var);
			
			if (!Cond(false)) return false;
			
			AstNode* arr = EMIT ArraySize(iter->loc);
			ctor->arg[0] = arr;
			
			if (!PassChar(']')) return false;
			
			if (Char('=')) {
				TODO
			}
			
			EMIT PopConstructor(iter->loc);
			
			EMIT PushRval(iter->loc, *ctor);
			return true;
		}
		else if (IsChar('(')) {
			AstNode* ctor = EMIT PushConstructor(iter->loc, meta, tn, var);
			if (!ctor) return false;
			
			AstNode* args = EMIT PushRvalArgumentList(iter->loc);
			ctor->arg[0] = args;
			
			if (!Char(')')) {
				if (!Cond(false)) return false;
				EMIT Argument(iter->loc);
				
				while (Char(',')) {
					if (!Cond(false)) return false;
					EMIT Argument(iter->loc);
				}
				
				if (!PassChar(')'))
					return false;
			}
			
			EMIT PopExpr(iter->loc);
			EMIT PopConstructor(iter->loc);
			
			EMIT PushRval(iter->loc, *ctor);
			return true;
		}
		else if (Char('=')) {
			AstNode* ctor = EMIT PushConstructor(iter->loc, meta, tn, var);
			if (!ctor) return false;
			
			AstNode* args = EMIT PushRvalArgumentList(iter->loc);
			ctor->arg[0] = args;
			
			//NO: Expression leaf pushes: EMIT PushExprScope();
			if (!Cond(false)) return false;
			EMIT Argument(iter->loc);
			
			EMIT PopExpr(iter->loc);
			EMIT PopConstructor(iter->loc);
			
			EMIT PushRval(iter->loc, *ctor);
			return true;
		}
		
		EMIT PushRval(iter->loc, *var);
	}
	
	
	return true;
}

bool SemanticParser::ParseSwitchBlock() {
	TODO
}

AstNode* SemanticParser::ParseExpression(bool m) {
	CHECK_SPATH_BEGIN1
	
	Iterator& iter = TopIterator();
	if (!Assign(m))
		return 0;
	
	CHECK_SPATH_END
	
	return EMIT PopExpr(iter->loc);
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
				
				if (!PassChar(']'))
					return false;
			}
			
			EMIT Expr2(iter->loc, OP_SUBSCRIPT);
			return true;
		}
		else
		if(Char('.')) {
			TODO
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
			
			if(Char('!')) {
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
		EMIT PushRvalConstant(iter->loc, HexInt(iter->str_value));
		iter++;
		return true;
	}
	
	if(iter->IsType(TK_FLOAT) || iter->IsType(TK_DOUBLE)) {
		EMIT PushRvalConstant(iter->loc, StrDbl(iter->str_value));
		iter++;
		return true;
	}
	if(iter->IsType(TK_OCT)) {
		EMIT PushRvalConstant(iter->loc, OctInt(iter->str_value));
		iter++;
		return true;
	}
	if(iter->IsType(TK_INTEGER)) {
		// TODO: int64 !
		EMIT PushRvalConstant(iter->loc, StrInt(iter->str_value));
		iter++;
		return true;
	}
	if(iter->IsType(TK_STRING)) {
		EMIT PushRvalConstant(iter->loc, iter->str_value);
		iter++;
		return true;
	}
	if(iter->IsType(TK_CHAR)) {
		TODO
		EMIT PushRvalConstant(iter->loc, iter->str_value);
		iter++;
		return true;
	}
	if(iter->IsType(TK_ID) && (iter->str_value == "true" || iter->str_value == "false")) {
		EMIT PushRvalConstant(iter->loc, iter->str_value == "true");
		iter++;
		return true;
	}
	if(Char('@')) {
		TODO // Emit
		if (!Subscript(meta))
			return false;
		return true;
	}
	
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
		bool typename_ = iter->str_value == "typename";
		if (typename_)
			iter++;
		
		PathIdentifier id;
		if (!ParsePathIdentifier(id, true, true))
			return false;
		
		
		AstNode* nn = 0;
		bool partial_meta = id.HasPartialMeta();
		// e.g. "a.$i"
		if (partial_meta) {
			nn = EMIT PartialMetaResolve(id.begin->loc, id, typename_ ? SEMT_META_TYPE : SEMT_META_FIELD);
			ASSERT(nn);
		}
		else {
			if (id.HasMeta())
				meta = true;
			
			if (typename_) {
				nn = FindDeclaration(id, meta ? SEMT_META_TYPE : SEMT_TYPE);
				if (!nn) {
					AddError(iter->loc, "could not find type '" + id.ToString() + "'");
					return false;
				}
			}
			else {
				nn = FindDeclaration(id, meta ? SEMT_META_ANY : SEMT_NULL);
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
			}
		}
		
		if (!_global && Char('(')) {
			EMIT PushRval(id.begin->loc, *nn);
			
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
			if (nn->IsPartially((SemanticType)(SEMT_META_FIELD | SEMT_FIELD)) ||
				(partial_meta && !typename_)) {
				EMIT PushRval(id.begin->loc, *nn);
			}
			else if (nn->IsPartially((SemanticType)(SEMT_META_TYPE | SEMT_TYPE)) ||
				(partial_meta && typename_)) {
				if (!ParseDeclExpr(meta, id, *nn))
					return false;
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
		
		if(Char('*')) {
			if (!Unary(m)) return false;
			EMIT Expr2(tk.loc, OP_MUL);
		}
		else
		if(Char('/')) {
			if (!Unary(m)) return false;
			EMIT Expr2(tk.loc, OP_DIV);
		}
		else
		if(Char('%')) {
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
		
		if(Char('+')) {
			if (!Mul(m)) return false;
			EMIT Expr2(tk.loc, OP_ADD);
		}
		else
		if(Char('-')) {
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
	while(Char('&')) {
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
	while(Char('|')) {
		const Token& tk = TopIterator().iter[-1];
		
		if (!BinXor(m)) return false;
		EMIT Expr2(tk.loc, OP_BWOR);
	}
	return true;
}

bool SemanticParser::And(bool m) {
	if (!BinOr(m)) return false;
	if(IsToken(TK_LOGAND)) {
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
	if(IsToken(TK_LOGOR)) {
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
		AddError(iter->loc, "expected '" + Token::GetTextValueStatic(tk_type, "") + "' but got EOL");
		return false;
	}
	if (!iter->IsType(tk_type)) {
		AddError(iter->loc, "expected '" + Token::GetTextValueStatic(tk_type, "") + "' but got '" + iter->GetTypeString() + "'");
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
	if (!ParsePathIdentifier(id, false, true))
		return 0;
	
	AstNode* n = FindDeclaration(id);
	if (!n)
		AddError(TopIterator()->loc, "could not resolve '" + id.ToString() + "'");
	return n;
}

AstNode* SemanticParser::ParseAndFindMetaDeclaration() {
	PathIdentifier id;
	if (!ParsePathIdentifier(id, false, true))
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
	if (!ParsePathIdentifier(id, false, false)) {
		AddError(iter->loc, "invalid world id");
		return false;
	}
	
	Iterator& owner_iter = TopIterator();
	AstNode& owner = GetTopNode();
	if (owner_iter.node->sub.GetCount()) {
		EMIT PushWorld(iter->loc, id);
		
		if (!ParseWorldStatementList())
			return false;
		
		EMIT PopWorld(iter->loc);
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
	if (!ParsePathIdentifier(id, false, false)) {
		AddError(iter->loc, "invalid system id");
		return false;
	}
	
	Iterator& owner_iter = TopIterator();
	
	EMIT PushSystem(iter.begin->loc, id);
	
	if (owner_iter.node->sub.GetCount()) {
		if (!ParseSystemStatementList())
			return false;
	}
	
	EMIT PopSystem(iter.begin->loc);
	
	return true;
}

bool SemanticParser::ParsePool() {
	Iterator& iter = TopIterator();
	if (!PassId("pool"))
		return false;
	
	PathIdentifier id;
	if (!ParsePathIdentifier(id, false, false)) {
		AddError(iter->loc, "invalid pool id");
		return false;
	}
	
	EMIT PushPool(iter.begin->loc, id);
	
	Iterator& owner_iter = TopIterator();
	if (owner_iter.node->sub.GetCount()) {
		if (!ParsePoolStatementList())
			return false;
	}
	
	EMIT PopPool(iter.begin->loc);
	
	return true;
}

bool SemanticParser::ParseEntity() {
	Iterator& iter = TopIterator();
	if (!PassId("entity"))
		return false;
	
	PathIdentifier id;
	if (!ParsePathIdentifier(id, false, false)) {
		AddError(iter->loc, "invalid entity id");
		return false;
	}
	
	EMIT PushEntity(iter.begin->loc, id);
	
	Iterator& owner_iter = TopIterator();
	if (owner_iter.node->sub.GetCount()) {
		if (!ParseEntityStatementList())
			return false;
	}
	
	EMIT PopEntity(iter.begin->loc);
	
	return true;
}

bool SemanticParser::ParseComponent() {
	Iterator& iter = TopIterator();
	if (!PassId("comp"))
		return false;
	
	PathIdentifier id;
	if (!ParsePathIdentifier(id, false, false)) {
		AddError(iter->loc, "invalid component id");
		return false;
	}
	
	EMIT PushComponent(iter.begin->loc, id);
	
	Iterator& owner_iter = TopIterator();
	if (owner_iter.node->sub.GetCount()) {
		if (!ParseComponentStatementList())
			return false;
	}
	
	EMIT PopComponent(iter.begin->loc);
	
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
	if (!ParsePathIdentifier(id, false, false)) {
		AddError(iter->loc, "invalid machine id");
		return false;
	}
	
	EMIT PushMachine(iter.begin->loc, id);
	
	Iterator& owner_iter = TopIterator();
	if (owner_iter.node->sub.GetCount()) {
		if (!ParseMachineStatementList())
			return false;
	}
	
	EMIT PopMachine(iter.begin->loc);
	
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
	if (!ParsePathIdentifier(id, false, false)) {
		AddError(iter->loc, "invalid chain id");
		return false;
	}
	
	EMIT PushChain(iter.begin->loc, id);
	
	Iterator& owner_iter = TopIterator();
	if (owner_iter.node->sub.GetCount()) {
		if (!ParseChainStatementList())
			return false;
	}
	
	EMIT PopChain(iter.begin->loc);
	
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
	if (!ParsePathIdentifier(id, false, false)) {
		AddError(iter->loc, "invalid loop id");
		return false;
	}
	
	CHECK_SPATH_BEGIN
	AstNode* loop = EMIT PushLoop(iter.begin->loc, id);
	if (is_driver)
		loop->src = SEMT_DRIVER;
	
	Iterator& owner_iter = TopIterator();
	if (owner_iter.node->sub.GetCount()) {
		if (!ParseLoopStatementList())
			return false;
	}
	else {
		loop->src = SEMT_LOOP_DECL;
	}
	
	EMIT PopLoop(iter.begin->loc);
	CHECK_SPATH_END
	
	return true;
}

bool SemanticParser::ParseAtom(PathIdentifier& id) {
	Iterator& iter = TopIterator();
	
	CHECK_SPATH_BEGIN
	AstNode* atom = EMIT PushAtom(iter.begin->loc, id);
	if (!atom) return false;
	
	if (!IsLineEnd()) {
		if (TryToken('[')) {
			while (!TryToken(']')) {
				if (TryToken(',')) {
					AddEmptyAtomConnector(iter->loc, 0);
				}
				else {
					AstNode* conn = EMIT PushAtomConnector(iter->loc, 0);
					
					CHECK_SPATH_BEGIN
					allow_expr_unresolved = true;
					bool succ = Cond(false);
					AstNode* rval = PopExpr(iter->loc);
					allow_expr_unresolved = false;
					if (!succ)
						return false;
					CHECK_SPATH_END
					
					TryToken(',');
					
					EMIT PopAtomConnector(iter->loc);
				}
			}
			
			if (TryToken('[')) {
				while (!TryToken(']')) {
					if (TryToken(',')) {
						AddEmptyAtomConnector(iter->loc, 1);
					}
					else {
						AstNode* conn = EMIT PushAtomConnector(iter->loc, 1);
						
						CHECK_SPATH_BEGIN
						allow_expr_unresolved = true;
						bool succ = Cond(false);
						AstNode* rval = PopExpr(iter->loc);
						allow_expr_unresolved = false;
						if (!succ)
							return false;
						CHECK_SPATH_END
						
						TryToken(',');
						
						EMIT PopAtomConnector(iter->loc);
					}
				}
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
	CHECK_SPATH_END

	return true;
}

bool SemanticParser::ParseState() {
	Iterator& iter = TopIterator();
	
	if (!PassId("state"))
		return false;
	
	PathIdentifier id;
	if (!ParsePathIdentifier(id, false, false)) {
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
	int cookie = 0;
	
	EMIT PushStatementList(iter->loc);
	
	for(const TokenNode& tns : owner.sub) {
		cur = &tns;
		if (!ParseMachineStatement(cookie))
			return false;
	}
	
	path.Remove(path.GetCount()-1);
	
	EMIT PopStatementList(iter->loc);
	
	return true;
}

bool SemanticParser::ParseMachineStatement(int& cookie) {
	const TokenNode& cur = *path.Top();
	Iterator& iter = AddIterator(cur);
	
	if (iter) {
		
		if (iter->IsType(TK_ID)) {
			const String& id = iter->str_value;
			
			if (id == "chain") {
				if (!ParseChain())
					return false;
			}
			else if (id == "loop" || id == "driver") {
				if (!ParseLoop())
					return false;
			}
			else if (id == "meta") {
				if (!ParseMeta(cookie))
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
	int cookie = 0;
	
	EMIT PushStatementList(owner.begin->loc);
	
	for(const TokenNode& tns : owner.sub) {
		CHECK_SPATH_BEGIN
		
		cur = &tns;
		if (!ParseChainStatement(cookie))
			return false;
		
		CHECK_SPATH_END
	}
	
	path.Remove(path.GetCount()-1);
	
	EMIT PopStatementList(owner.end->loc);
	
	return true;
}

bool SemanticParser::ParseChainStatement(int& cookie) {
	const TokenNode& cur = *path.Top();
	Iterator& iter = AddIterator(cur);
	
	if (iter) {
		CHECK_SPATH_BEGIN
		
		if (iter->IsType(TK_ID)) {
			const String& id = iter->str_value;
			
			if (id == "loop" || id == "driver") {
				if (!ParseLoop())
					return false;
			}
			else if (id == "state") {
				if (!ParseState())
					return false;
			}
			else if (id == "meta") {
				if (!ParseMeta(cookie))
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
		
		CHECK_SPATH_END
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
	int cookie = 0;
	
	EMIT PushStatementList(owner.begin->loc);
	
	for(const TokenNode& tns : owner.sub) {
		CHECK_SPATH_BEGIN
		
		cur = &tns;
		if (!ParseLoopStatement(cookie))
			return false;
		
		CHECK_SPATH_END
	}
	
	path.Remove(path.GetCount()-1);
	
	EMIT PopStatementList(owner.end->loc);
	
	return true;
}

bool SemanticParser::ParseLoopStatement(int& cookie) {
	const TokenNode& cur = *path.Top();
	Iterator& iter = AddIterator(cur);
	
	if (iter) {
		
		if (IsId("meta")) {
			if (!ParseMeta(cookie))
				return false;
		}
		else if (Id("pass")) {
			// pass
		}
		else if (iter->IsType('$')) {
			if (!ParseExpressionStatement())
				return false;
		}
		else if (iter->IsType(TK_ID) || iter->IsType('$')) {
			PathIdentifier id;
			if (!ParsePathIdentifier(id, false, false)) {
				AddError(iter->loc, "id parsing failed");
				return false;
			}
			
			if (!iter || iter->IsType('[') || cur.sub.GetCount()) {
				if (!ParseAtom(id))
					return false;
			}
			else if (iter->IsType('=')) {
				CHECK_SPATH_BEGIN
				
				AstNode* var = EMIT DeclareVariable(iter->loc, *builtin_void, id);
				if (!var) return false;
				
				EMIT PushStatement(iter->loc, STMT_EXPR);
				
				EMIT PushRval(id.begin->loc, *var);
				
				if (!AssignPost(false))
					return false;
				
				AstNode* link = EMIT PopExpr(iter->loc);
				
				EMIT PopStatement(iter->loc, link);
				
				CHECK_SPATH_END
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

bool SemanticParser::ParseMeta(int& cookie) {
	
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
		return ParseMetaStatement(cookie, 1);
	}
	else {
		return ParseExpression(true);
	}
}

bool SemanticParser::ParseWorldStatementList() {
	Iterator& iter = TopIterator();
	const TokenNode& owner = *path.Top();
	const TokenNode*& cur = path.Add();
	int cookie = 0;
	
	EMIT PushStatementList(iter->loc);
	
	for(const TokenNode& tns : owner.sub) {
		CHECK_SPATH_BEGIN
		
		cur = &tns;
		if (!ParseWorldStatement(cookie))
			return false;
		
		CHECK_SPATH_END
	}
	
	path.Remove(path.GetCount()-1);
	
	EMIT PopStatementList(iter->loc);
	
	return true;
}

bool SemanticParser::ParseWorldStatement(int& cookie) {
	const TokenNode& cur = *path.Top();
	Iterator& iter = AddIterator(cur);
	
	if (iter) {
		
		if (IsId("meta")) {
			if (!ParseMeta(cookie))
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
	int cookie = 0;
	
	EMIT PushStatementList(iter->loc);
	
	for(const TokenNode& tns : owner.sub) {
		CHECK_SPATH_BEGIN
		
		cur = &tns;
		if (!ParseSystemStatement(cookie))
			return false;
		
		CHECK_SPATH_END
	}
	
	path.Remove(path.GetCount()-1);
	
	EMIT PopStatementList(iter->loc);
	
	return true;
}

bool SemanticParser::ParseSystemStatement(int& cookie) {
	const TokenNode& cur = *path.Top();
	Iterator& iter = AddIterator(cur);
	
	if (iter) {
		if (Id("pass")) {
			// pass
		}
		else if (IsId("meta")) {
			if (!ParseMeta(cookie))
				return false;
		}
		else if (iter->IsType(TK_ID)) {
			EMIT PushStatement(iter->loc, STMT_EXPR);
			
			allow_expr_unresolved = true;
			bool succ = Assign(false);
			allow_expr_unresolved = false;
			if (!succ)
				return false;
			
			AstNode* link = EMIT PopExpr(iter->loc);
			EMIT PopStatement(iter->loc, link);
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
	int cookie = 0;
	
	EMIT PushStatementList(iter->loc);
	
	for(const TokenNode& tns : owner.sub) {
		cur = &tns;
		if (!ParsePoolStatement(cookie))
			return false;
	}
	
	path.Remove(path.GetCount()-1);
	
	EMIT PopStatementList(iter->loc);
	
	return true;
}

bool SemanticParser::ParsePoolStatement(int& cookie) {
	const TokenNode& cur = *path.Top();
	Iterator& iter = AddIterator(cur);
	
	if (iter) {
		if (Id("pass")) {
			// pass
		}
		else if (IsId("meta")) {
			if (!ParseMeta(cookie))
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
	int cookie = 0;
	
	EMIT PushStatementList(iter->loc);
	
	for(const TokenNode& tns : owner.sub) {
		cur = &tns;
		if (!ParseEntityStatement(cookie))
			return false;
	}
	
	path.Remove(path.GetCount()-1);
	
	EMIT PopStatementList(iter->loc);
	
	return true;
}

bool SemanticParser::ParseEntityStatement(int& cookie) {
	const TokenNode& cur = *path.Top();
	Iterator& iter = AddIterator(cur);
	
	if (iter) {
		if (Id("pass")) {
			// pass
		}
		else if (IsId("meta")) {
			if (!ParseMeta(cookie))
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
	int cookie = 0;
	
	EMIT PushStatementList(iter->loc);
	
	for(const TokenNode& tns : owner.sub) {
		cur = &tns;
		if (!ParseComponentStatement(cookie))
			return false;
	}
	
	path.Remove(path.GetCount()-1);
	
	EMIT PopStatementList(iter->loc);
	
	return true;
}

bool SemanticParser::ParseComponentStatement(int& cookie) {
	const TokenNode& cur = *path.Top();
	Iterator& iter = AddIterator(cur);
	
	if (iter) {
		if (Id("pass")) {
			// pass
		}
		else if (IsId("meta")) {
			if (!ParseMeta(cookie))
				return false;
		}
		else if (IsToken(TK_ID)) {
			EMIT PushStatement(iter->loc, STMT_EXPR);
			
			allow_expr_unresolved = true;
			bool succ = Assign(false);
			allow_expr_unresolved = false;
			if (!succ)
				return false;
			
			AstNode* link = EMIT PopExpr(iter->loc);
			EMIT PopStatement(iter->loc, link);
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

bool SemanticParser::ParseExpressionList() {
	bool succ = true;
	
	const TokenNode& tk_owner = *path.Top();
	
	EMIT PushStatementList(tk_owner.end->loc);
	
	int expr_count = 0;
	
	int cookie = 0;
	const TokenNode*& sub = path.Add();
	for (const TokenNode& s : tk_owner.sub) {
		sub = &s;
		Iterator& iter = AddIterator(s);
		
		if (!iter)
			continue;
		
		if (IsId("meta")) {
			if (!ParseMeta(cookie))
				return false;
		}
		else {
			if (expr_count > 0) {
				AddError(iter->loc, "only single expression is allowed");
				succ = false;
			}
			
			AstNode* stmt = EMIT PushStatement(iter->loc, STMT_EXPR);
			AstNode* expr = ParseExpression(false);
			if (!expr) {
				succ = false;
				PopIterator();
				break;
			}
			expr_count++;
			
			EMIT PopStatement(iter->loc, expr);
		}
		
		PopIterator();
	}
	path.Remove(path.GetCount()-1);
	
	EMIT PopStatementList(tk_owner.end->loc);
	
	return succ;
}


NAMESPACE_TOPSIDE_END

#undef EMIT
