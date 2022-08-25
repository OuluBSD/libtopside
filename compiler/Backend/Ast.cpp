#include "Backend.h"

NAMESPACE_TOPSIDE_BEGIN


AstNode::AstNode() {
	
}

AstNode& AstNode::Add(String name) {
	AstNode& s = sub.Add();
	s.SetOwner(this);
	s.name = name;
	return s;
}

AstNode& AstNode::GetAdd(String name) {
	AstNode* p = Find(name);
	if (p)
		return *p;
	else
		return Add(name);
}

AstNode* AstNode::Find(String name) {
	for (auto& s : sub)
		if (s.name == name)
			return &s;
	return 0;
}

String AstNode::GetTreeString(int indent) const {
	String s;
	s.Cat('\t', indent);
	s << ToString() << "\n";
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
