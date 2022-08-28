#include "Backend.h"

NAMESPACE_TOPSIDE_BEGIN


AstNode::AstNode() {
	
}

AstNode& AstNode::Add(String name) {
	ASSERT(!locked);
	AstNode& s = sub.Add();
	s.SetOwner(this);
	s.name = name;
	return s;
}

AstNode& AstNode::GetAdd(String name) {
	ASSERT(name.GetCount());
	AstNode* p = Find(name);
	if (p)
		return *p;
	else
		return Add(name);
}

AstNode* AstNode::Find(String name) {
	ASSERT(name.GetCount());
	for (auto& s : sub)
		if (s.name == name)
			return &s;
	return 0;
}

const AstNode* AstNode::Find(String name) const {
	ASSERT(name.GetCount());
	for (auto& s : sub)
		if (s.name == name)
			return &s;
	return 0;
}

AstNode* AstNode::Find(SemanticType t) {
	for (auto& s : sub)
		if (s.src == t)
			return &s;
	return 0;
}

const AstNode* AstNode::Find(SemanticType t) const {
	for (auto& s : sub)
		if (s.src == t)
			return &s;
	return 0;
}

String AstNode::GetConstantString() const {
	String s = GetConstString(con) + ": ";
	switch (con) {
		case CONST_NULL:	s += "null"; break;
		case CONST_INT32:	s += IntStr(i64); break;
		case CONST_INT64:	s += IntStr64(i64); break;
		case CONST_DOUBLE:	s += DblStr(dbl); break;
		case CONST_STRING:	s += "\"" + str + "\""; break;
		default: break;
	}
	return s;
}

String AstNode::GetTreeString(int indent) const {
	String s;
	s.Cat('\t', indent);
	
	s << GetSemanticTypeString(src) << ": ";
	
	if (name.GetCount())
		s << name << "\n";
	else if (src == SEMT_CONSTANT)
		s << "const(" << GetConstantString() << ")\n";
	else if (src == SEMT_STATEMENT)
		s << "stmt(" << GetStmtTypeString(stmt) << ")\n";
	else if (op != OP_NULL)
		s << "op(" << GetOpString(op) << ")\n";
	else if (filter != SEMT_NULL)
		s << "filter(" << GetSemanticTypeString(filter) << ")\n";
	else
		s << "\n";
	
	//else if (src != SEMT_NULL)
	//	s << "src(" << GetSemanticTypeString(src) << ")\n";
	
	for (const AstNode& n : sub) {
		s << n.GetTreeString(indent+1);
	}
	return s;
}

String AstNode::GetCodeString(const CodeArgs& args) const {
	TODO
}

String AstNode::ToString() const {
	return name;
}

String AstNode::GetPath() const {
	static const int MAX_PATH_LEN = 32;
	const AstNode* path[MAX_PATH_LEN];
	const AstNode* cur = this;
	int count = 0;
	while (cur) {
		path[count] = cur;
		cur = cur->GetSubOwner();
		count++;
	}
	
	String s;
	for(int i = count-1, j = 0; i >= 0; i--, j++) {
		if (j) s += ".";
		s += path[i]->GetName();
	}
	return s;
}

String AstNode::GetPartStringArray() const {
	static const int MAX_PATH_LEN = 32;
	const AstNode* path[MAX_PATH_LEN];
	const AstNode* cur = this;
	int count = 0;
	while (cur) {
		path[count] = cur;
		cur = cur->GetSubOwner();
		count++;
	}
	
	String s;
	s.Cat('[');
	for(int i = count-2, j = 0; i >= 0; i--, j++) {
		if (j) s += ", \"";
		else s.Cat('\"');
		s.Cat(path[i]->GetName());
		s.Cat('\"');
	}
	s.Cat(']');
	return s;
}


NAMESPACE_TOPSIDE_END
