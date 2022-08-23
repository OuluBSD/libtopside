#include "Backend.h"

#define EMIT if (emitter) emitter->

NAMESPACE_TOPSIDE_BEGIN


SemanticNode::SemanticNode() {
	
}

SemanticNode& SemanticNode::Add(String name) {
	SemanticNode& s = sub.Add();
	s.SetOwner(this);
	s.name = name;
	return s;
}

SemanticNode* SemanticNode::Find(String name) {
	for (auto& s : sub)
		if (s.name == name)
			return &s;
	return 0;
}

String SemanticNode::GetTreeString(int indent) const {
	String s;
	s.Cat('\t', indent);
	s << ToString() << "\n";
	for (const SemanticNode& n : sub) {
		s << n.GetTreeString(indent+1);
	}
	return s;
}

String SemanticNode::GetCodeString(const CodeArgs& args) const {
	TODO
}

String SemanticNode::ToString() const {
	return name;
}














SemanticParser::SemanticParser() :
	ErrorSource("SemanticParser")
{
	
}

void SemanticParser::AddBuiltinType(String name) {
	SemanticNode& sn = root.Add(name);
	sn.src = CLSRC_BUILTIN;
}

void SemanticParser::InitDefault() {
	AddBuiltinType("void");
	AddBuiltinType("int");
	AddBuiltinType("long");
	AddBuiltinType("uint");
	AddBuiltinType("ulong");
	AddBuiltinType("float");
	AddBuiltinType("double");
	AddBuiltinType("byte");
	AddBuiltinType("char");
	AddBuiltinType("short");
	AddBuiltinType("ushort");
}

bool SemanticParser::ProcessEon(const TokenStructure& t) {
	root.Clear();
	path.Clear();
	
	InitDefault();
	
	path.Add(&t.root);
	
	return ParseNamespaceBlock();
}

bool SemanticParser::ParseNamespaceBlock() {
	ASSERT(!path.IsEmpty());
	
	const TokenNode& owner = *path.Top();
	const TokenNode*& cur = path.Add();
	
	for (const TokenNode& tns : owner.sub) {
		cur = &tns;
		if (!ParseDeclaration())
			break;
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
				TODO
			}
			else if (id == "chain") {
				TODO
			}
			else if (id == "loop") {
				TODO
			}
			else {
				// Find previously declared type
				SemanticNode* decl = FindDeclaration();
				
				if (!decl) {
					AddError(cur.begin->loc, "could not resolve");
					PopIterator();
					return false;
				}
				
				if (IsTrivialObjectType(decl->src)) {
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

bool SemanticParser::ParseTypedDeclaration(SemanticNode& ret_type) {
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

bool SemanticParser::ParseFunction(SemanticNode& ret_type, const PathIdentifier& name) {
	Iterator& iter = TopIterator();
	const TokenNode& cur = *path.Top();
	ASSERT(iter.Check(cur));
	ASSERT(iter->IsType('('));
	
	EMIT PushFunction(ret_type, name);
	
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
		EMIT PushFunctionDefinition();
		
		if (!ParseStatementList())
			return false;
		
		EMIT PopFunctionDefinition();
	}
	
	EMIT PopFunction();
	
	return true;
}

bool SemanticParser::ParseStatementList() {
	bool succ = true;
	
	EMIT PushStatementList();
	
	const TokenNode& owner = *path.Top();
	const TokenNode*& sub = path.Add();
	for (const TokenNode& s : owner.sub) {
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
	
	EMIT PopStatementList();
	
	return succ;
}

bool SemanticParser::ParseStatement() {
	const TokenNode& cur = CurrentNode();
	Iterator& iter = TopIterator();
	
	//DUMP(cur)
	
	if (Id("if")) {
		EMIT PushStatement(STMT_IF);
		
		if (!ParseConditional()) return false;
		// Emit
		if (!ParseStatementBlock()) return false;
		if (Id("else")) {
			EMIT PushStatement(STMT_ELSE);
			
			if (!ParseStatementBlock()) return false;
			
			EMIT PopStatement();
		}
		
		EMIT PopStatement();
	}
	else if (Id("do")) {
		EMIT PushStatement(STMT_DOWHILE);
		
		if (!ParseStatementBlock()) return false;
		if (!PassId("while")) return false;
		if (!ParseExpression()) return false;
		// Emit
		if (!PassToken(';')) return false;
		
		EMIT PopStatement();
	}
	else if (Id("while")) {
		EMIT PushStatement(STMT_WHILE);
		
		if (!ParseConditional()) return false;
		if (!ParseStatementBlock()) return false;
		
		EMIT PopStatement();
	}
	else if (Id("for")) {
		EMIT PushStatement(STMT_FOR);
		
		if (!IsToken(',')) {
			if (!ParseDeclExpr()) return false;
		}
		if (Id("in") || Char(':')) {
			if (!ParseExpression()) return false;
		}
		else {
			if (!PassToken(',')) return false;
			if (!IsToken(',')) {
				if (!ParseExpression()) return false;
			}
			if (!PassToken(',')) return false;
			if (iter) {
				if (!ParseExpression()) return false;
			}
		}
		
		if (!ParseStatementBlock()) return false;
		
		EMIT PopStatement();
	}
	else if (Id("break")) {
		EMIT PushStatement(STMT_BREAK);
		EMIT PopStatement();
	}
	else if (Id("continue")) {
		EMIT PushStatement(STMT_CONTINUE);
		EMIT PopStatement();
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
		EMIT PushStatement(STMT_RETURN);
		
		if (iter) {
			if (!ParseExpression()) return false;
		}
		
		EMIT PopStatement();
	}
	else if (Id("switch")) {
		EMIT PushStatement(STMT_SWITCH);
		
		if (!ParseExpression()) return false;
		
		if (!ParseSwitchBlock()) return false;
		
		EMIT PopStatement();
	}
	else if (Id("log")) {
		EMIT PushStatement(STMT_LOG);
		
		if (!ParseExpression()) return false;
		
		while (Char(',')) {
			if (!ParseExpression()) return false;
		}
		
		EMIT PopStatement();
	}
	else if (cur.begin == cur.end && cur.sub.GetCount()) {
		EMIT PushStatement(STMT_BLOCK);
		
		if (!ParseStatementBlock()) return false;
		
		EMIT PopStatement();
	}
	else if (cur.begin == cur.end) {
		// empty statement
	}
	else {
		AddError(cur.begin->loc, "unexpected token in statement");
		return false;
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
	
	PathIdentifier name;
	if (!iter->IsType(',')) {
		if (!ParsePathIdentifier(name))
			return false;
	}
	
	EMIT Parameter(type, name);
	
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
	//DUMP(cur);
	
	PathIdentifier first;
	if (!ParsePathIdentifier(first))
		return false;
	
	SemanticNode* type = FindDeclaration(first);
	
	if (type) {
		PathIdentifier name;
		if (!ParsePathIdentifier(name))
			return false;
		
	}
	
	if (IsChar('=')) {
		if (!Assign())
			return false;
	}
	
	return true;
}

bool SemanticParser::ParseSwitchBlock() {
	TODO
}

bool SemanticParser::ParseExpression() {
	return Assign();
}

bool SemanticParser::Subscript() {
	for(;;) {
		if(Char('[')) {
			if(Char(']')) {
				// Emit
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
					// Emit
				}
				else
				if(Char(':')) {
					if(!IsChar(']')) {
							if (!ParseExpression())
						return false;
					}
					// Emit
				}
				else {
					// Emit
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
			if(!IsChar2('!', '=') && Char('!')) {
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
		// Emit
		iter++;
		return true;
	}
	/*if(iter->IsType(TK_BINARY)) {
		// Emit
		return true;
	}*/
	if(iter->IsType(TK_FLOAT) || iter->IsType(TK_DOUBLE)) {
		// Emit
		iter++;
		return true;
	}
	if(iter->IsType(TK_OCT)) {
		// Emit
		iter++;
		return true;
	}
	if(iter->IsType(TK_INTEGER)) {
		// TODO: int64 !
		// Emit
		iter++;
		return true;
	}
	if(iter->IsType(TK_STRING)) {
		// Emit
		iter++;
		return true;
	}
	if(iter->IsType(TK_CHAR)) {
		/*WString s = FromUtf8(ReadString('\'', true));
		if(s.GetLength() != 1) {
			AddError(iter->loc, "invalid character literal");
			return false;
		}*/
		// Emit
		iter++;
		return true;
	}
	if(Char('@')) {
		// Emit
		Subscript();
		return true;
	}
	if(Id("void")) {
		// Emit
		return true;
	}
	if(Char(TK_INDENT)) {
		// Emit
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
		// Emit
	}
	else
	if(Char(':'))
		_global = true;
	if(iter->IsType(TK_ID)) {
		PathIdentifier id;
		if (!ParsePathIdentifier(id))
			return false;
		
		/*if(id.part_count == "self") {
			// Emit
		}
		else*/
		{
			if (!_global && Char('(')) {
				
				int i = 0;
				while (!Char(')')) {
					if (i) {
						if (!PassChar(','))
							return false;
					}
					if (!ParseExpression())
						return false;
					i++;
				}
				
			}
			
			// Emit id
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
	if(Char2('+', '+')) {
		if (!Unary()) return false;
	}
	else
	if(Char2('-', '-')) {
		if (!Unary()) return false;
	}
	else
	if(Char('-')) {
		if (!Unary()) return false;
	}
	else
	if(Char('+')) {
		if (!Unary()) return false;
	}
	else
	if(Char('!')) {
		if (!Unary()) return false;
	}
	else
	if(Char('~')) {
		if (!Unary()) return false;
	}
	else
		if (!Term()) return false;

	if(Char2('+', '+')) {
		TODO
	}
	if(Char2('-', '-')) {
		TODO
	}
	
	return true;
}

bool SemanticParser::Mul() {
	if (!Unary()) return false;
	for(;;) {
		if(!IsChar2('*', '=') && Char('*')) {
			if (!Unary()) return false;
		}
		else
		if(!IsChar2('/', '=') && Char('/')) {
			if (!Unary()) return false;
		}
		else
		if(!IsChar2('%', '=') && Char('%')) {
			if (!Unary()) return false;
		}
		else
			break;
	}
	
	return true;
}

bool SemanticParser::Add() {
	if (!Mul()) return false;
	for(;;) {
		if(!IsChar2('+', '=') && Char('+')) {
			if (!Mul()) return false;
		}
		else
		if(!IsChar2('-', '=') && Char('-')) {
			if (!Mul()) return false;
		}
		else
			break;
	}
	return true;
}

bool SemanticParser::Shift() {
	if (!Add()) return false;
	for(;;) {
		if(Char2('<', '<')) {
			if (!Add()) return false;
		}
		else
		if(Char2('>', '>')) {
			if (!Add()) return false;
		}
		else
			break;
	}
	return true;
}

bool SemanticParser::DoCompare(const char *op) {
	if (!Shift()) return false;
	// Emit
	return true;
}

bool SemanticParser::Compare() {
	if (!Shift()) return false;
	for(;;) {
		if (Char2('>', '=')) {
			if (!DoCompare(">=")) return false;
		}
		else if (Char2('<', '=')) {
			if (!DoCompare("<=")) return false;
		}
		else if (Char('>')) {
			if (!DoCompare(">")) return false;
		}
		else if (Char('<')) {
			if (!DoCompare("<")) return false;
		}
		else
			break;
	}
	return true;
}

bool SemanticParser::Equal() {
	if (!Compare()) return false;
	for(;;) {
		if(Char2('=', '=')) {
			if (!Compare()) return false;
		}
		else
		if(Char2('!', '=')) {
			if (!Compare()) return false;
		}
		else
			break;
	}
	return true;
}

bool SemanticParser::BinAnd() {
	if (!Equal()) return false;
	while(!IsChar2('&', '&') && Char('&')) {
		if (!Equal()) return false;
	}
	return true;
}

bool SemanticParser::BinXor() {
	if (!BinAnd()) return false;
	while(Char('^')) {
		if (!BinAnd()) return false;
	}
	return true;
}

bool SemanticParser::BinOr() {
	if (!BinXor()) return false;
	while(!IsChar2('|', '|') && Char('|')) {
		if (!BinXor()) return false;
	}
	return true;
}

bool SemanticParser::And() {
	if (!BinOr()) return false;
	if(IsChar2('&', '&')) {
		while(Char2('&', '&')) {
			if (!BinOr()) return false;
		}
	}
	return true;
}

bool SemanticParser::Or() {
	if (!And()) return false;
	if(IsChar2('|', '|')) {
		while(Char2('|', '|')) {
			if (!And()) return false;
		}
	}
	return true;
}

bool SemanticParser::Cond() {
	if (!Or()) return false;
	if(Char('?')) {
		if (!Cond()) return false;
		PassChar(':');
		if (!Cond()) return false;
	}
	return true;
}

bool SemanticParser::Assign() {
	if (!Cond()) return false;
	if(Char('=')) {
		if (!Assign()) return false;
	}
	else
	if(Char2('+', '=')) {
		if (!Cond()) return false;
	}
	else
	if(Char2('-', '=')) {
		if (!Cond()) return false;
	}
	else
	if(Char2('*', '=')) {
		if (!Cond()) return false;
	}
	else
	if(Char2('/', '=')) {
		if (!Cond()) return false;
	}
	else
	if(Char2('%', '=')) {
		if (!Cond()) return false;
	}
	return true;
}

bool SemanticParser::IsToken(int tk_type) const {
	const Iterator& iter = TopIterator();
	if (!iter) return false;
	return iter->IsType(tk_type);
}

bool SemanticParser::IsChar2(int a, int b) const {
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
}

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

SemanticNode* SemanticParser::FindDeclaration() {
	PathIdentifier id;
	if (!ParsePathIdentifier(id))
		return 0;
	
	return FindDeclaration(id);
}

SemanticNode* SemanticParser::FindDeclaration(const PathIdentifier& id) {
	SemanticNode* cur = &root;
	for(int i = 0; i < id.part_count; i++) {
		const Token* t = id.parts[i];
		if (t->IsType(TK_ID) || t->IsType(TK_INTEGER)) {
			cur = cur->Find(t->str_value);
		}
		else {
			TODO
		}
		if (!cur)
			break;
	}
	
	return cur;
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



NAMESPACE_TOPSIDE_END

#undef EMIT
