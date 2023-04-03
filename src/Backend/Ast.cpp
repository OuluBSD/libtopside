#include "Backend.h"

NAMESPACE_TOPSIDE_BEGIN

Endpoint::Endpoint() : n(0) {
	
}

Endpoint::Endpoint(AstNode& n) : n(&n), rel_loc(n.loc) {
	
}

Endpoint::Endpoint(AstNode* n) : n(n) {
	if (n)
		rel_loc = n->loc;
}

void Endpoint::operator=(const Endpoint& ep) {
	n = ep.n;
	rel_loc = ep.rel_loc;
}

String Endpoint::ToString() const {
	String s;
	if (n)
		s << GetSemanticTypeString(n->src) << ", " << n->GetPath() << ", " << rel_loc.ToString();
	return s;
}





AstNode::AstNode() {
	
}

void AstNode::CopyFrom(EonStd* e, const AstNode& n) {
	sub.Clear();
	
	name = n.name;
	src = n.src;
	stmt = n.stmt;
	op = n.op;
	con = n.con;
	filter = n.filter;
	i64 = n.i64;
	str = n.str;
	loc = n.loc;
	
	prev = &n;
	
	if (e) {
		type = n.type ? e->FindStackWithPrev(n.type) : 0;
		rval = n.rval ? e->FindStackWithPrev(n.rval) : 0;
		ctx_next = n.ctx_next ? e->FindStackWithPrev(n.ctx_next) : 0;
		ASSERT(type != this);
		ASSERT(rval != this);
		ASSERT(ctx_next != this);
	
		for(int i = 0; i < AstNode::ARG_COUNT; i++) {
			arg[i] = n.arg[i] ? e->FindStackWithPrev(n.arg[i]) : 0;
			ASSERT(arg[i] != this);
		}
	}
	
}

void AstNode::CopyFromObject(const FileLocation& loc, const Object& o) {
	sub.Clear();
	name.Clear();
	src = SEMT_CONSTANT;
	stmt = STMT_NULL;
	op = OP_NULL;
	filter = SEMT_NULL;
	i64 = 0;
	str.Clear();
	this->loc = loc;
	
	dword type = o.GetType();
	ASSERT(type);
	
	if (type == BOOL_V) {
		i64 = o.ToInt();
		con = CONST_BOOL;
	}
	else if (type == INT_V) {
		i64 = o.ToInt();
		con = CONST_INT32;
	}
	else if (type == INT64_V) {
		i64 = o.ToInt();
		con = CONST_INT64;
	}
	else if (type == STRING_V) {
		str = o.ToString();
		con = CONST_STRING;
	}
	else if (type == DOUBLE_V) {
		dbl = o.ToDouble();
		con = CONST_DOUBLE;
	}
	else TODO
}

void AstNode::CopyToObject(Object& n) const {
	if (src == SEMT_CONSTANT) {
		switch (con) {
			case CONST_BOOL: n = (bool)i64; break;
			case CONST_INT32: n = (int32)i64; break;
			case CONST_INT64: n = (int64)i64; break;
			case CONST_STRING: n = str; break;
			case CONST_DOUBLE: n = dbl; break;
			default: TODO break;
		}
	}
	else TODO
}

AstNode& AstNode::Add(const FileLocation& loc, String name, int idx) {
	ASSERT(!locked);
	AstNode& s =
		idx >= 0 ? sub.Insert(idx) : sub.Add();
	s.SetOwner(this);
	s.name = name;
	s.loc = loc;
	return s;
}

AstNode& AstNode::GetAdd(const FileLocation& loc, String name) {
	ASSERT(name.GetCount());
	AstNode* p = Find(name);
	if (p)
		return *p;
	else
		return Add(loc, name);
}

AstNode& AstNode::GetAdd(const FileLocation& loc, SemanticType accepts) {
	ASSERT(name.GetCount());
	for (AstNode& s : sub) {
		if (s.IsPartially(accepts))
			return s;
	}
	AstNode& s = Add(loc);
	s.src = accepts;
	if (accepts == SEMT_TYPE_POINTER)
		s.name = "#";
	else if (accepts == SEMT_TYPE_LREF)
		s.name = "&";
	
	return s;
}

AstNode* AstNode::Find(String name, SemanticType accepts) {
	ASSERT(name.GetCount());
	for (auto& s : sub)
		if (s.name == name && (accepts == SEMT_NULL || s.IsPartially(accepts)))
			return &s;
	return 0;
}

const AstNode* AstNode::Find(String name, SemanticType accepts) const {
	ASSERT(name.GetCount());
	for (auto& s : sub)
		if (s.name == name && (accepts == SEMT_NULL || s.IsPartially(accepts)))
			return &s;
	return 0;
}

AstNode* AstNode::Find(SemanticType t) {
	for (auto& s : sub)
		if (s.src == t)
			return &s;
	return 0;
}

AstNode* AstNode::FindPartial(SemanticType t) {
	for (auto& s : sub)
		if ((int64)s.src & (int64)t)
			return &s;
	return 0;
}

const AstNode* AstNode::Find(SemanticType t) const {
	for (auto& s : sub)
		if (s.src == t)
			return &s;
	return 0;
}

AstNode* AstNode::FindWithPrevDeep(const AstNode* prev) {
	if (this->prev == prev)
		return this;
	for (AstNode& s : sub) {
		if (s.prev == prev)
			return &s;
	}
	for (AstNode& s : sub) {
		AstNode* r = s.FindWithPrevDeep(prev);
		if (r)
			return r;
	}
	return 0;
}

void AstNode::FindAll(Vector<Endpoint>& ptrs, SemanticType accepts, const FileLocation* rel_loc) {
	if (IsPartially(accepts)) {
		Endpoint& p = ptrs.Add();
		p.n = this;
		if (rel_loc)
			p.rel_loc = *rel_loc;
		else
			p.rel_loc = loc;
	}
	for (AstNode& s : sub) {
		if (s.src == SEMT_SYMBOLIC_LINK && !rel_loc)
			s.FindAll(ptrs, accepts, &loc);
		else
			s.FindAll(ptrs, accepts, rel_loc);
	}
}

void AstNode::FindAllStmt(Vector<Endpoint>& ptrs, StmtType accepts, const FileLocation* rel_loc) {
	if (src == SEMT_STATEMENT && stmt == accepts) {
		Endpoint& p = ptrs.Add();
		p.n = this;
		if (rel_loc)
			p.rel_loc = *rel_loc;
		else
			p.rel_loc = loc;
	}
	for (AstNode& s : sub) {
		if (s.src == SEMT_SYMBOLIC_LINK && !rel_loc)
			s.FindAllStmt(ptrs, accepts, &loc);
		else
			s.FindAllStmt(ptrs, accepts, rel_loc);
	}
}

void AstNode::FindAllNonIdEndpoints(Vector<Endpoint>& ptrs, SemanticType accepts, const FileLocation* rel_loc) {
	for (AstNode& s : sub) {
		if (s.src == SEMT_SYMBOLIC_LINK && !rel_loc)
			s.FindAllNonIdEndpoints0(ptrs, accepts, &loc);
		else
			s.FindAllNonIdEndpoints0(ptrs, accepts, rel_loc);
	}
	if (sub.IsEmpty() && src != SEMT_IDPART) {
		Endpoint& p = ptrs.Add();
		p.n = this;
		if (rel_loc)
			p.rel_loc = *rel_loc;
		else
			p.rel_loc = loc;
	}
}

void AstNode::FindAllNonIdEndpoints0(Vector<Endpoint>& ptrs, SemanticType accepts, const FileLocation* rel_loc) {
	if (src == SEMT_IDPART) {
		for (AstNode& s : sub) {
			if (s.src == SEMT_SYMBOLIC_LINK && !rel_loc)
				s.FindAllNonIdEndpoints0(ptrs, accepts, &loc);
			else
				s.FindAllNonIdEndpoints0(ptrs, accepts, rel_loc);
		}
	}
	else if (accepts == SEMT_NULL || IsPartially(accepts)) {
		Endpoint& p = ptrs.Add();
		p.n = this;
		if (rel_loc)
			p.rel_loc = *rel_loc;
		else
			p.rel_loc = loc;
	}
}

String AstNode::GetConstantString() const {
	String s = GetConstString(con) + ": ";
	switch (con) {
		case CONST_NULL:	s += "null"; break;
		case CONST_INT32:	s += IntStr((int)i64); break;
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
	else if (src == SEMT_OBJECT)
		s << "object(" << obj.ToString() << ")\n";
	else if (src == SEMT_UNRESOLVED)
		s << "unresolved(" << str << ")\n";
	else if (src == SEMT_CONSTANT)
		s << "const(" << GetConstantString() << ")\n";
	else if (src == SEMT_STATEMENT)
		s << "stmt(" << GetStmtTypeString(stmt) << ")\n";
	else if (op != OP_NULL)
		s << "op(" << GetOpString(op) << ")\n";
	else if (filter != SEMT_NULL)
		s << "filter(" << GetSemanticTypeString(filter) << ")\n";
	else if (src == SEMT_RVAL && rval)
		s << rval->GetName() << "\n";
	else
		s << "\n";
	
	for (const AstNode& n : sub) {
		s << n.GetTreeString(indent+1);
	}
	return s;
}

String AstNode::GetTreeString(int indent, bool links) const {
	String s = GetTreeString(indent);
	if (!links) return s;
	for(int i = 0; i < ARG_COUNT; i++) {
		if (arg[i]) {
			s.Cat('\t', indent+1);
			s << "arg:\n";
			s << arg[i]->GetTreeString(indent+2);
		}
	}
	if (rval) {
		s.Cat('\t', indent+1);
		s << "rval:\n";
		s << rval->GetTreeString(indent+2);
	}
	if (ctx_next) {
		s.Cat('\t', indent+1);
		s << "ctx_next:\n";
		s << ctx_next->GetTreeString(indent+2);
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
		if (cur->IsPartially((SemanticType)(
				SEMT_PATH | SEMT_TYPE | SEMT_FIELD | SEMT_META_TYPE | SEMT_META_FIELD)))
			path[count++] = cur;
		cur = cur->GetSubOwner();
	}
	
	String s;
	s.Cat('[');
	for(int i = count-1, j = 0; i >= 0; i--, j++) {
		if (j) s += ", \"";
		else s.Cat('\"');
		s.Cat(path[i]->GetName());
		s.Cat('\"');
	}
	s.Cat(']');
	return s;
}



Object EvaluateAstNodeObject(AstNode& n) {
	Object o;
	if (n.src == SEMT_EXPR) {
		switch (n.op) {
			
		case OP_POSITIVE:
			o = EvaluateAstNodeObject(*n.arg[0]);
			break;
			
		case OP_NEGATIVE:
			o = EvaluateAstNodeObject(*n.arg[0]);
			o = Object(-1) * o;
			break;
			
		default:
			TODO
		}
	}
	else if (n.src == SEMT_CONSTANT) {
		n.CopyToObject(o);
	}
	else TODO
	return o;
}

NAMESPACE_TOPSIDE_END
