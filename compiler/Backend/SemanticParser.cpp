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
	const TokenNode& cur = *path.Top();
	Iterator& iter = AddIterator(cur);
	
	//DUMP(cur);
	
	if (iter) {
		
		if (iter->IsType(TK_ID)) {
			const String& id = iter->str_value;
			//DUMP(id);
			
			if (id == "def") {
				TODO
			}
			else if (id == "machine") {
				if (!ParseMachine())
					return false;
			}
			else if (id == "chain") {
				if (!ParseChain())
					return false;
			}
			else if (id == "loop") {
				if (!ParseLoop())
					return false;
			}
			else {
				// Find previously declared type
				AstNode* decl = ParseAndFindDeclaration();
				
				if (!decl) {
					AddError(cur.begin->loc, "could not resolve");
					PopIterator();
					return false;
				}
				
				if (IsTypedNode(decl->src)) {
					bool succ = ParseTypedDeclaration(*decl);
					PopIterator();
					return succ;
				}
				else {
					TODO
				}
			}
		}
		else {
			DUMP(cur);
			TODO
		}
		
	}
	
	PopIterator();
	return true;
}

bool SemanticParser::ParseTypedDeclaration(AstNode& ret_type) {
	Iterator& iter = TopIterator();
	const TokenNode& cur = *path.Top();
	ASSERT(iter.Check(cur));
	
	PathIdentifier id;
	if (!ParsePathIdentifier(id))
		return false;
	
	//DUMP(id);
	
	
	if (iter) {
		
		if (iter->IsType('(')) {
			return ParseFunction(ret_type, id);
		}
		else {
			TODO
		}
		
	}
	
	
	TODO
	
	
}

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
		
		if (!ParseStatement()) {
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
	
	if (Id("if")) {
		EMIT PushStatement(iter->loc, STMT_IF);
		
		if (!ParseConditional()) return false;
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
		if (!ParseExpression()) return false;
		if (!PassToken(';')) return false;
		
		EMIT PopStatement(iter->loc);
	}
	else if (Id("while")) {
		EMIT PushStatement(iter->loc, STMT_WHILE);
		
		if (!ParseConditional()) return false;
		if (!ParseStatementBlock()) return false;
		
		EMIT PopStatement(iter->loc);
	}
	else if (Id("for")) {
		EMIT PushStatement(iter->loc, STMT_FOR);
		
		if (!IsToken(',')) {
			//EMIT PushStatementParameter(iter->loc, STMTP_FOR_DECL);
			if (!ParseDeclExpr()) return false;
		}
		if (Id("in") || Char(':')) {
			//EMIT PushStatementParameter(iter->loc, STMTP_FOR_COLLECTION);
			EMIT PushStatement(iter->loc, STMT_FOR_RANGE);
			if (!ParseExpression()) return false;
			EMIT PopStatement(iter->loc);
		}
		else {
			if (!PassToken(',')) return false;
			if (!IsToken(',')) {
				//EMIT PushStatementParameter(iter->loc, STMTP_WHILE_COND);
				EMIT PushStatement(iter->loc, STMT_FOR_COND);
				if (!ParseExpression()) return false;
				EMIT PopStatement(iter->loc);
			}
			if (!PassToken(',')) return false;
			if (iter) {
				//EMIT PushStatementParameter(iter->loc, STMTP_FOR_POST);
				EMIT PushStatement(iter->loc, STMT_FOR_POST);
				if (!ParseExpression()) return false;
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
			if (!ParseExpression()) return false;
		}
		
		EMIT PopStatement(iter->loc);
	}
	else if (Id("switch")) {
		EMIT PushStatement(iter->loc, STMT_SWITCH);
		
		if (!ParseExpression()) return false;
		
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
		
		if (!Assign()) return false;
		EMIT Argument(iter->loc);
		
		while (Char(',')) {
			if (!Assign()) return false;
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
		
		if (!ParseExpression()) return false;
		
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

bool SemanticParser::ParsePathIdentifier(PathIdentifier& id) {
	Iterator& iter = TopIterator();
	id.begin = iter;
	id.part_count = 0;
	const Token* end = iter.end;
	
	bool expect_dot = false;
	
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
			else {
				TODO
			}
		}
		iter++;
	}
	
	id.end = end;
	
	return id.part_count > 0;
}

bool SemanticParser::ParseConditional() {
	
	if (!ParseExpression())
		return false;
	
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

bool SemanticParser::ParseDeclExpr() {
	const TokenNode& cur = *path.Top();
	Iterator& iter = TopIterator();
	//DUMP(cur);
	
	PathIdentifier first;
	if (!ParsePathIdentifier(first))
		return false;
	
	AstNode* tn = FindDeclaration(first);
	AstNode* var = 0;
	
	if (tn && tn->IsPartially(SEMT_TYPE)) {
		PathIdentifier name;
		if (!ParsePathIdentifier(name))
			return false;
		
		var = &DeclareRelative(name);
		ASSERT(var->IsPartially(SEMT_UNDEFINED));
		var->src = SEMT_VARIABLE;
		var->type = tn;
		
		EMIT DeclareVariable(first.begin->loc, *tn, name);
	}
	else {
		var = tn;
		ASSERT(var->name.GetCount());
	}
	
	if (Char('=')) {
		EMIT PushStatement(iter->loc, STMT_CTOR);
		EMIT PushRval(iter->loc, *var);
		
		//NO: Expression leaf pushes: EMIT PushExprScope();
		if (!Cond()) return false;
		EMIT Expr2(iter->loc, OP_ASSIGN);
		
		EMIT PopExpr(iter->loc);
		EMIT PopStatement(iter->loc);
	}
	else if (IsChar('(')) {
		TODO
	}
	
	return true;
}

bool SemanticParser::ParseSwitchBlock() {
	TODO
}

bool SemanticParser::ParseExpression() {
	Iterator& iter = TopIterator();
	bool succ = Assign();
	
	EMIT PopExpr(iter->loc);
	
	return succ;
}

bool SemanticParser::Subscript() {
	for(;;) {
		if(Char('[')) {
			if(Char(']')) {
				TODO // Emit
			}
			else {
				if(!IsChar(',') && !IsChar(':')) {
					if (!ParseExpression())
						return false;
				}
				
				if(Char(',')) {
					if(!IsChar(']')) {
						if (!ParseExpression())
							return false;
					}
					TODO // Emit
				}
				else
				if(Char(':')) {
					if(!IsChar(']')) {
							if (!ParseExpression())
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
			if(!Char(')')) {
				for(;;) {
					if (!ParseExpression())
						return false;
					if(Char(')')) break;
					PassChar(',');
				}
			}
			if(/*!IsToken(TK_INEQ) &&*/ Char('!')) {
				Term();
			}
			
		}
		else
			return true;
	}
	return true;
}

bool SemanticParser::Term() {
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
	if(Char('@')) {
		TODO // Emit
		Subscript();
		return true;
	}
	if(Id("void")) {
		TODO // Emit
		return true;
	}
	if(Char(TK_INDENT)) {
		TODO // Emit
		if(!Char(TK_DEDENT)) {
			for(;;) {
				if (!ParseExpression())
					return false;
				PassChar(':');
				if (!ParseExpression())
					return false;
				if(Char(TK_DEDENT))
					break;
				PassChar(',');
			}
		}
		Subscript();
		return true;
	}
	if(Char('[')) {
		if(!Char(']')) {
			for(;;) {
				if (!ParseExpression())
					return false;
				if(Char(']'))
					break;
				PassChar(',');
			}
		}
		Subscript();
		return true;
	}
	if(Char('(')) {
		if (!ParseExpression()) return false;
		PassChar(')');
		Subscript();
		return true;
	}
	
	bool  _global = false;
	if(Char('.')) {
		TODO // Emit
	}
	else
	if(Char(':'))
		_global = true;
	if(iter->IsType(TK_ID)) {
		PathIdentifier id;
		if (!ParsePathIdentifier(id))
			return false;
		
		AstNode* nn = FindDeclaration(id);
		if (!nn) {
			AddError(iter->loc, "could not find '" + id.ToString() + "'");
			return false;
		}
		
		if (!_global && Char('(')) {
			
			if (nn->IsPartially(SEMT_FUNCTION)) {
				//EMIT PushRvalCall(id.begin->loc, *nn);
				EMIT PushRvalResolve(iter->loc, id, SEMT_FUNCTION);
			}
			else if (IsTypedNode(nn->src)) {
				//EMIT PushRvalConstruct(id.begin->loc, *nn);
				EMIT PushRvalResolve(iter->loc, id, SEMT_TYPE);
			}
			else {
				AddError(iter->loc, "can't call or construct '" + id.ToString() + "'");
				return false;
			}
			
			EMIT PushRvalArgumentList(iter->loc);
			
			int i = 0;
			while (!Char(')')) {
				if (i) {
					if (!PassChar(','))
						return false;
				}
				if (!Assign())
					return false;
				EMIT Argument(iter->loc);
				i++;
			}
			
			EMIT Expr2(iter->loc, OP_CALL);
		}
		else {
			//DUMP(id);
			
			if (nn->IsPartially(SEMT_FIELD)) {
				EMIT PushRval(id.begin->loc, *nn);
			}
			else if (nn->IsPartially(SEMT_TYPE)) {
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
					
					// Variable declaration statement
					EMIT DeclareVariable(iter->loc, *nn, name);
					EMIT PushRval(id.begin->loc, var);
				}
				else {
					TODO // probably user error --> AddError
				}
			}
			else {
				TODO
			}
		}
		
		
		return Subscript();
	}
	else {
		AddError(iter->loc, "invalid expression");
		return false;
	}
	
	return true;
}

bool SemanticParser::Unary() {
	const Token& tk = TopIterator();
	
	if(TryToken(TK_INC)) {
		if (!Unary()) return false;
		EMIT Expr1(tk.loc, OP_INC);
	}
	else
	if(TryToken(TK_DEC)) {
		if (!Unary()) return false;
		EMIT Expr1(tk.loc, OP_DEC);
	}
	else
	if(Char('-')) {
		if (!Unary()) return false;
		EMIT Expr1(tk.loc, OP_NEGATIVE);
	}
	else
	if(Char('+')) {
		if (!Unary()) return false;
		EMIT Expr1(tk.loc, OP_POSITIVE);
	}
	else
	if(Char('!')) {
		if (!Unary()) return false;
		EMIT Expr1(tk.loc, OP_NOT);
	}
	else
	if(Char('~')) {
		if (!Unary()) return false;
		EMIT Expr1(tk.loc, OP_NEGATE);
	}
	else
		if (!Term()) return false;

	if(TryToken(TK_INC)) {
		EMIT Expr1(tk.loc, OP_POSTINC);
	}
	if(TryToken(TK_DEC)) {
		EMIT Expr1(tk.loc, OP_POSTDEC);
	}
	
	return true;
}

bool SemanticParser::Mul() {
	if (!Unary()) return false;
	for(;;) {
		const Token& tk = TopIterator();
		
		if(/*!IsToken(TK_MULASS) &&*/ Char('*')) {
			if (!Unary()) return false;
			EMIT Expr2(tk.loc, OP_MUL);
		}
		else
		if(/*!IsToken(TK_DIVASS) &&*/ Char('/')) {
			if (!Unary()) return false;
			EMIT Expr2(tk.loc, OP_DIV);
		}
		else
		if(/*!IsToken(TK_MODASS) &&*/ Char('%')) {
			if (!Unary()) return false;
			EMIT Expr2(tk.loc, OP_MOD);
		}
		else
			break;
	}
	
	return true;
}

bool SemanticParser::Add() {
	if (!Mul()) return false;
	
	for(;;) {
		const Token& tk = TopIterator();
		
		if(/*!IsChar2('+', '=') &&*/ Char('+')) {
			if (!Mul()) return false;
			EMIT Expr2(tk.loc, OP_ADD);
		}
		else
		if(/*!IsChar2('-', '=') &&*/ Char('-')) {
			if (!Mul()) return false;
			EMIT Expr2(tk.loc, OP_SUB);
		}
		else
			break;
	}
	return true;
}

bool SemanticParser::Shift() {
	if (!Add()) return false;
	for(;;) {
		const Token& tk = TopIterator();
		
		if(TryToken(TK_LSHIFT)) {
			if (!Add()) return false;
			EMIT Expr2(tk.loc, OP_LSH);
		}
		else
		if(TryToken(TK_RSHIFT)) {
			if (!Add()) return false;
			EMIT Expr2(tk.loc, OP_RSH);
		}
		else
			break;
	}
	return true;
}

bool SemanticParser::DoCompare(const FileLocation& loc, OpType op) {
	if (!Shift()) return false;
	EMIT Expr2(loc, op);
	return true;
}

bool SemanticParser::Compare() {
	if (!Shift()) return false;
	for(;;) {
		const Token& tk = TopIterator();
		
		if (TryToken(TK_GREQ)) {
			if (!DoCompare(tk.loc, OP_GREQ)) return false;
		}
		else if (TryToken(TK_LSEQ)) {
			if (!DoCompare(tk.loc, OP_LSEQ)) return false;
		}
		else if (Char('>')) {
			if (!DoCompare(tk.loc, OP_GREATER)) return false;
		}
		else if (Char('<')) {
			if (!DoCompare(tk.loc, OP_LESS)) return false;
		}
		else
			break;
	}
	return true;
}

bool SemanticParser::Equal() {
	if (!Compare()) return false;
	for(;;) {
		const Token& tk = TopIterator();
		
		if(TryToken(TK_EQ)) {
			if (!Compare()) return false;
			EMIT Expr2(tk.loc, OP_EQ);
		}
		else
		if(TryToken(TK_INEQ)) {
			if (!Compare()) return false;
			EMIT Expr2(tk.loc, OP_INEQ);
		}
		else
			break;
	}
	return true;
}

bool SemanticParser::BinAnd() {
	if (!Equal()) return false;
	while(/*!IsChar2('&', '&') &&*/ Char('&')) {
		const Token& tk = TopIterator().iter[-1];
		
		if (!Equal()) return false;
		EMIT Expr2(tk.loc, OP_BWAND);
	}
	return true;
}

bool SemanticParser::BinXor() {
	if (!BinAnd()) return false;
	while(Char('^')) {
		const Token& tk = TopIterator().iter[-1];
		
		if (!BinAnd()) return false;
		EMIT Expr2(tk.loc, OP_BWXOR);
	}
	return true;
}

bool SemanticParser::BinOr() {
	if (!BinXor()) return false;
	while(/*!IsChar2('|', '|') &&*/ Char('|')) {
		const Token& tk = TopIterator().iter[-1];
		
		if (!BinXor()) return false;
		EMIT Expr2(tk.loc, OP_BWOR);
	}
	return true;
}

bool SemanticParser::And() {
	if (!BinOr()) return false;
	if(TryToken(TK_LOGAND)) {
		while(TryToken(TK_LOGAND)) {
			const Token& tk = TopIterator().iter[-1];
			
			if (!BinOr()) return false;
			EMIT Expr2(tk.loc, OP_AND);
		}
	}
	return true;
}

bool SemanticParser::Or() {
	if (!And()) return false;
	if(TryToken(TK_LOGOR)) {
		while(TryToken(TK_LOGOR)) {
			const Token& tk = TopIterator().iter[-1];
			
			if (!And()) return false;
			EMIT Expr2(tk.loc, OP_OR);
		}
	}
	return true;
}

bool SemanticParser::Cond() {
	if (!Or()) return false;
	if(Char('?')) {
		const Token& tk = TopIterator().iter[-1];
		
		if (!Cond()) return false;
		PassChar(':');
		if (!Cond()) return false;
		EMIT Expr3(tk.loc, OP_COND);
	}
	return true;
}

bool SemanticParser::Assign() {
	if (!Cond()) return false;
	const Token& tk = TopIterator();
		
	if(Char('=')) {
		if (!Assign()) return false;
		EMIT Expr2(tk.loc, OP_ASSIGN);
	}
	else
	if(TryToken(TK_ADDASS)) {
		if (!Cond()) return false;
		EMIT Expr2(tk.loc, OP_ADDASS);
	}
	else
	if(TryToken(TK_SUBASS)) {
		if (!Cond()) return false;
		EMIT Expr2(tk.loc, OP_SUBASS);
	}
	else
	if(TryToken(TK_MULASS)) {
		if (!Cond()) return false;
		EMIT Expr2(tk.loc, OP_MULASS);
	}
	else
	if(TryToken(TK_DIVASS)) {
		if (!Cond()) return false;
		EMIT Expr2(tk.loc, OP_DIVASS);
	}
	else
	if(TryToken(TK_MODASS)) {
		if (!Cond()) return false;
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
	if (!iter->IsType(tk_type))
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
	
	return FindDeclaration(id);
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
	
	Iterator& owner_iter = TopIterator();
	AstNode& owner = GetTopNode();
	if (owner_iter.node->sub.GetCount()) {
		AstNode& mach = Declare(owner, id);
		mach.src = SEMT_MACHINE;
		PushScope(mach);
		if (!ParseMachineDefinition())
			return false;
		PopScope();
	}
	else {
		TODO // machine declaration-only
	}
	
	return true;
}

bool SemanticParser::ParseMachineDefinition() {
	const TokenNode& owner = *path.Top();
	const TokenNode*& cur = path.Add();
	
	for(const TokenNode& tns : owner.sub) {
		cur = &tns;
		if (!ParseMachineStatement())
			return false;
	}
	
	path.Remove(path.GetCount()-1);
	
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
			else if (id == "loop") {
				if (!ParseLoop())
					return false;
			}
			else if (id == "meta") {
				if (!ParseMeta())
					return false;
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
	
	PopIterator();
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
	
	Iterator& owner_iter = TopIterator();
	AstNode& owner = GetTopNode();
	if (owner_iter.node->sub.GetCount()) {
		AstNode& chain = Declare(owner, id);
		chain.src = SEMT_CHAIN;
		PushScope(chain);
		if (!ParseChainDefinition())
			return false;
		PopScope();
	}
	else {
		TODO // chain declaration-only
	}
	
	return true;
}

bool SemanticParser::ParseChainDefinition() {
	const TokenNode& owner = *path.Top();
	const TokenNode*& cur = path.Add();
	
	for(const TokenNode& tns : owner.sub) {
		cur = &tns;
		if (!ParseChainStatement())
			return false;
	}
	
	path.Remove(path.GetCount()-1);
	
	return true;
}

bool SemanticParser::ParseChainStatement() {
	const TokenNode& cur = *path.Top();
	Iterator& iter = AddIterator(cur);
	
	if (iter) {
		
		if (iter->IsType(TK_ID)) {
			const String& id = iter->str_value;
			//DUMP(id);
			
			if (id == "loop") {
				if (!ParseLoop())
					return false;
			}
			else if (id == "state") {
				if (!ParseState())
					return false;
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
	
	PopIterator();
	return true;
}

bool SemanticParser::ParseLoop() {
	Iterator& iter = TopIterator();
	if (iter->str_value != "loop") {
		AddError(iter->loc, "expected 'loop'");
		return false;
	}
	iter++;
	
	PathIdentifier id;
	if (!ParsePathIdentifier(id)) {
		AddError(iter->loc, "invalid loop id");
		return false;
	}
	
	Iterator& owner_iter = TopIterator();
	AstNode& owner = GetTopNode();
	if (owner_iter.node->sub.GetCount()) {
		AstNode& loop = Declare(owner, id);
		loop.src = SEMT_LOOP;
		PushScope(loop);
		if (!ParseLoopDefinition())
			return false;
		PopScope();
	}
	else {
		TODO // loop declaration-only
	}
	
	return true;
}

bool SemanticParser::ParseLoopDefinition() {
	const TokenNode& owner = *path.Top();
	const TokenNode*& cur = path.Add();
	
	for(const TokenNode& tns : owner.sub) {
		cur = &tns;
		if (!ParseLoopStatement())
			return false;
	}
	
	path.Remove(path.GetCount()-1);
	
	return true;
}

bool SemanticParser::ParseLoopStatement() {
	const TokenNode& cur = *path.Top();
	Iterator& iter = AddIterator(cur);
	
	if (iter) {
		
		if (iter->IsType(TK_ID)) {
			
			PathIdentifier id;
			if (!ParsePathIdentifier(id)) {
				AddError(iter->loc, "id parsing failed");
				return false;
			}
			
			if (iter->IsType('[')) {
				if (!ParseAtom(id))
					return false;
			}
			
			/*if (id == "") {
				TODO
			}
			else {
				TODO
				AddError(cur.begin->loc, "invalid machine statement");
				PopIterator();
				return false;
			}*/
		}
		else {
			DUMP(cur);
			TODO
		}
		
	}
	
	PopIterator();
	return true;
}

bool SemanticParser::ParseAtom(PathIdentifier& id) {
	Iterator& iter = TopIterator();
	
	AstNode& owner = GetTopNode();
	AstNode& atom = Declare(owner, id);
	PushScope(atom);
	
	if (!IsLineEnd()) {
		if (TryToken('[')) {
			
			if (!TryToken(']')) {
				AstNode& src_cond = atom.Add("src");
				PushScope(src_cond);
				if (!Cond())
					return false;
				PopScope();
				
				if (!PassToken(']'))
					return false;
			}
			if (TryToken('[') && !TryToken(']')) {
				AstNode& sink_cond = atom.Add("sink");
				PushScope(sink_cond);
				if (!Cond())
					return false;
				PopScope();
				
				if (!PassToken(']'))
					return false;
			}
		}
		else {
			AddError(iter->loc, "unexpected token");
			return false;
		}
	}
	
	if (iter.node->sub.GetCount()) {
		TODO
	}
	
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
	
	
	return true;
}

bool SemanticParser::ParseMeta() {
	Iterator& iter = TopIterator();
	
	if (!PassId("meta"))
		return false;
	
	if (IsId("stmt")) {
		TODO
		
	}
	else if (IsId("params")) {
		TODO
		
	}
	else if (IsId("def")) {
		TODO
		
	}
	else if (IsId("for")) {
		TODO
		
	}
	else {
		PathIdentifier id;
		if (!ParsePathIdentifier(id)) {
			AddError(iter->loc, "id parsing failed");
			return false;
		}
		
		
		if (IsToken('(')) {
			TODO
		}
		else if (IsToken(TK_ID)) {
			TODO // find type
		}
		else {
			TODO // meta expression statement
		}
	}
	
	return true;
}


NAMESPACE_TOPSIDE_END

#undef EMIT
