#include "Backend.h"

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

bool SemanticParser::ParseDeclaration() {
	const TokenNode& cur = *path.Top();
	const Token* iter = cur.begin;
	const Token* end = cur.end;
	
	//DUMP(cur);
	
	if (iter != end) {
		
		if (iter->IsType(TK_ID)) {
			const String& id = iter->str_value;
			DUMP(id);
			
			if (id == "def") {
				
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
				SemanticNode* decl = FindDeclaration(iter, end);
				
				if (!decl) {
					AddError(cur.begin->loc, "could not resolve");
					return false;
				}
				
				if (IsTrivialObjectType(decl->src)) {
					return ParseTypedDeclaration(*decl, iter);
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
	
	return true;
}

bool SemanticParser::ParseTypedDeclaration(SemanticNode& ret_type, const Token*& iter) {
	const TokenNode& cur = *path.Top();
	ASSERT(iter >= cur.begin && iter <= cur.end);
	
	PathIdentifier id;
	if (!ParsePathIdentifier(id, iter, cur.end))
		return false;
	
	DUMP(id);
	
	
	if (iter != cur.end) {
		
		if (iter->IsType('(')) {
			return ParseFunction(ret_type, id, iter);
		}
		else {
			TODO
		}
		
	}
	
	
	TODO
	
	
}

bool SemanticParser::ParseFunction(SemanticNode& ret_type, const PathIdentifier& name, const Token*& iter) {
	const TokenNode& cur = *path.Top();
	ASSERT(iter->IsType('('));
	
	if (!PassToken(iter, '(')) return false;
	
	Array<SemanticNode> params;
	int i = 0;
	while (iter != cur.end && !iter->IsType(')')) {
		if (i && !PassToken(iter, ','))
			return false;
		
		SemanticNode& param = params.Add();
		if (!ParseParameter(param, iter))
			return false;
		
		i++;
	}
	
	if (!PassToken(iter, ')')) return false;
	
	
	if (PassToken(iter, ':')) {
		if (!ParseStatementList())
			return false;
	}
	else {
		
		// Emit function declaration
		
	}
	
	
	return true;
}

bool SemanticParser::ParseStatementList() {
	bool succ = true;
	
	const TokenNode& owner = *path.Top();
	const TokenNode*& sub = path.Add();
	for (const TokenNode& s : owner.sub) {
		sub = &s;
		
		if (!ParseStatement()) {
			succ = false;
			break;
		}
	}
	path.Remove(path.GetCount()-1);
	
	return succ;
}

bool SemanticParser::ParseStatement() {
	const TokenNode& cur = CurrentNode();
	
	//DUMP(cur)
	
	if (Id("if")) {
		
	}
	else if (Id("do")) {
		
	}
	else if (Id("while")) {
		
	}
	else if (Id("for")) {
		
	}
	else if (Id("break")) {
		
	}
	else if (Id("continue")) {
		
	}
	else if (Id("case")) {
		
	}
	else if (Id("default")) {
		
	}
	else if (Id("else")) {
		
	}
	else if (Id("return")) {
		
	}
	else if (Id("switch")) {
		
	}
	else if (cur.begin == cur.end && cur.sub.GetCount()) {
		
	}
	else if (cur.begin == cur.end) {
		// empty statement
	}
	else {
		AddError(cur.begin->loc, "unexpected token in statement");
		return false;
	}
	
	TODO
	return true;
}

bool SemanticParser::ParseParameter(SemanticNode& ret_type, const Token*& iter) {
	const TokenNode& cur = *path.Top();
	
	PathIdentifier type;
	if (!ParsePathIdentifier(type, iter, cur.end))
		return false;
	
	if (iter == cur.end) {
		AddError(iter->loc, "unexpeced end of parameter");
		return false;
	}
	
	PathIdentifier name;
	if (!iter->IsType(',')) {
		if (!ParsePathIdentifier(name, iter, cur.end))
			return false;
	}
	
	//DUMP(type); DUMP(name);
	
	
	// Emit resolve type
	// Emit reserve name
	// (push to statement stack)
	
	return true;
}

bool SemanticParser::PassToken(const Token*& iter, int tk_type) {
	if (!iter->IsType(tk_type)) {
		AddError(iter->loc, "expected '" + Token::GetTypeStringStatic(tk_type) + "' but got '" + iter->GetTypeString() + "'");
		return false;
	}
	iter++;
	return true;
}

bool SemanticParser::ParsePathIdentifier(PathIdentifier& id, const Token*& iter, const Token* end) {
	id.begin = iter;
	id.part_count = 0;
	
	bool expect_dot = false;
	
	while (iter != end) {
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

bool SemanticParser::ParseClass() {
	const TokenNode& cur = *path.Top();
	DUMP(cur);
	TODO
}

SemanticNode* SemanticParser::FindDeclaration(const Token*& iter, const Token* end) {
	PathIdentifier id;
	if (!ParsePathIdentifier(id, iter, end))
		return 0;
	
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
	TODO
}

String SemanticParser::GetCodeString(const CodeArgs& args) const {
	TODO
}

String SemanticParser::ToString() const {
	TODO
}



NAMESPACE_TOPSIDE_END
