#include "Backend.h"

NAMESPACE_TOPSIDE_BEGIN


String EonStd::GetPathString() const {
	String s;
	for (const Scope& scope : spath) {
		if (!s.IsEmpty())
			s.Cat('.');
		s << scope.n->GetName();
	}
	return s;
}

void EonStd::AddBuiltinType(String name) {
	AstNode& root = GetRoot();
	AstNode& sn = root.Add(name);
	sn.src = SEMT_BUILTIN;
}

void EonStd::AddMetaBuiltinType(String name) {
	AstNode& root = GetRoot();
	AstNode& sn = root.Add(name);
	sn.src = SEMT_META_BUILTIN;
}

String EonStd::GetRelativePartStringArray(const AstNode& n) const {
	ASSERT(!spath.IsEmpty());
	AstNode* top = spath.Top().n;
	AstNode* root = spath[0].n;
	ASSERT(top != &n);
	
	const AstNode* nodes[PathIdentifier::MAX_PARTS];
	int node_count = 0;
	const AstNode* iter = &n;
	while (iter && iter != top && iter != root) {
		bool found = false;
		for (const Scope& s : spath) {
			if (s.n == iter) {
				found = true;
				break;
			}
		}
		if (found)
			break;
		
		if (iter->IsPartially(SEMT_PATH) || iter->IsPartially(SEMT_META_PATH))
			nodes[node_count++] = iter;
		iter = iter->GetSubOwner();
	}
	
	String s = "[";
	for(int i = 0; i < node_count; i++) {
		if (i) s.Cat(',');
		s.Cat('\"');
		const AstNode& node = *nodes[node_count-1-i];
		if (node.IsPartially(SEMT_META_ANY))
			s.Cat('$');
		const String& n = node.name;
		ASSERT(n.GetCount());
		s.Cat(n);
		s.Cat('\"');
	}
	s.Cat(']');
	//DUMP(s)
	return s;
}

void EonStd::InitDefault() {
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
	AddBuiltinType("cstring");
	
	AddMetaBuiltinType("void");
	AddMetaBuiltinType("int");
	AddMetaBuiltinType("double");
	AddMetaBuiltinType("cstring");
	AddMetaBuiltinType("stmt");
	
	AddMetaBuiltinType("machstmt");
	AddMetaBuiltinType("chainstmt");
	AddMetaBuiltinType("loopstmt");
	
	AddMetaBuiltinType("atomstmt");
	AddMetaBuiltinType("worldstmt");
	AddMetaBuiltinType("systemstmt");
	AddMetaBuiltinType("poolstmt");
	AddMetaBuiltinType("entitystmt");
	AddMetaBuiltinType("compstmt");
	AddMetaBuiltinType("params");
	
	{
		AstNode& logger = GetRoot().Add("LOG");
		logger.src = SEMT_FUNCTION_BUILTIN;
	}
	
	GetRoot().src = SEMT_ROOT;
	
	spath.Add().Set(&GetRoot(),true);
}

bool EonStd::ForwardUserspace(AstNode*& n) {
	if (!n) return false;
	
	if (n->IsPartially(SEMT_FUNCTION)) {
		n = n->Find(SEMT_STATEMENT_BLOCK);
		return n != NULL;
	}
	if (n->IsPartially(SEMT_STATEMENT)) {
		switch (n->stmt) {
			case STMT_FOR:
			case STMT_IF:
			case STMT_ELSE:
				n = n->Find(SEMT_STATEMENT_BLOCK);
				break;
			
			case STMT_FOR_COND:
			case STMT_FOR_POST:
			case STMT_FOR_RANGE:
			case STMT_BLOCK:
			case STMT_RETURN:
				return false;
				
			case STMT_DOWHILE:
			case STMT_WHILE:
			case STMT_BREAK:
			case STMT_CONTINUE:
			case STMT_CASE:
			case STMT_DEFAULT:
			case STMT_SWITCH:
				TODO
				
			default:
			case STMT_NULL:
				break;
		}
	}
	return false;
}

AstNode* EonStd::FindDeclaration(const PathIdentifier& id, SemanticType accepts) {
	if (id.part_count == 0)
		return 0;
	
	for (int i = spath.GetCount()-1; i >= 0; i--) {
		Scope& s = spath[i];
			
		AstNode* n = GetDeclaration(s.n, id, accepts);
		if (n)
			return n;
	}
	return 0;
}

/*AstNode* EonStd::FindTypeDeclaration(const PathIdentifier& id) {
	return FindDeclaration(id, SEMT_TYPE);
}*/

AstNode* EonStd::GetDeclaration(const PathIdentifier& id, SemanticType accepts) {
	if (id.part_count == 0 || spath.IsEmpty())
		return 0;
	
	Scope& s = spath[0];
	return GetDeclaration(s.n, id, accepts);
}

AstNode* EonStd::GetDeclaration(AstNode* owner, const PathIdentifier& id, SemanticType accepts) {
	AstNode* cur = owner;
	AstNode* next = 0;
	AstNode* prev = 0;
	for(int i = 0; i < id.part_count; i++) {
		bool last = i == id.part_count-1;
		next = 0;
		for (int tries = 0; tries < 100; tries++) {
			const Token* t = id.parts[i];
			if ((t->IsType(TK_ID) || t->IsType(TK_INTEGER)) && !t->str_value.IsEmpty()) {
				if (id.is_meta[i]) {
					SemanticType a = last ? (accepts & SEMT_META_ANY ? accepts : SEMT_META_ANY) : SEMT_META_ANY;
					next = cur->Find(t->str_value, a);
				}
				else {
					SemanticType a = last ? accepts : SEMT_NULL;
					next = cur->Find(t->str_value, a);
				}
			}
			else {
				TODO
			}
			
			if (!next) {
				if (ForwardUserspace(cur)) {
					ASSERT(cur);
					continue;
				}
				else
					return 0;
			}
			else break;
		}
		
		ASSERT(next);
		prev = cur;
		cur = next;
	}
	
	SemanticType a = id.is_meta[id.part_count-1] ? SEMT_META_ANY : accepts;
	
	if (cur && accepts == SEMT_NULL || cur->IsPartially(a))
		return cur;
	
	return 0;
}

AstNode& EonStd::Declare(AstNode& owner, const PathIdentifier& id, bool insert_before) {
	AstNode* cur = &owner;
	for(int i = 0; i < id.part_count; i++) {
		const Token* t = id.parts[i];
		if (t->IsType(TK_ID) || t->IsType(TK_INTEGER)) {
			String id = t->str_value;
			ASSERT(id.GetCount());
			if (insert_before) {
				AstNode* next = cur->Find(id);
				if (next)
					cur = next;
				else
					cur = &cur->Add(id, max(0, cur->sub.GetCount()-2));
			}
			else cur = &cur->GetAdd(id);
			if (cur->src == SEMT_NULL)
				cur->src = SEMT_IDPART;
		}
		else {
			TODO
		}
	}
	
	//LOG("Declared " << GetPath(*cur));
	
	return *cur;
}

AstNode& EonStd::DeclareRelative(const PathIdentifier& id) {
	ASSERT(id.part_count > 0);
	return Declare(*spath.Top().n, id);
}

AstNode& EonStd::GetBlock() {
	for(int i = spath.GetCount()-1; i >= 0; i--) {
		Scope& scope = spath[i];
		if (scope.n->IsPartially(SEMT_BLOCK))
			return *scope.n;
	}
	return GetRoot();
}

void EonStd::PushScope(AstNode& n) {
	ASSERT(!spath.IsEmpty());
	thread_local static Vector<AstNode*> tmp;
	AstNode* cur = spath.Top().n;
	
	tmp.SetCount(0);
	AstNode* iter = &n;
	while (iter && iter != cur) {
		tmp.Add(iter);
		iter = iter->GetSubOwner();
	}
	ASSERT(iter == cur);
	
	for (int i = tmp.GetCount()-1, j = 0; i >= 0; i--, j++) {
		Scope& s = spath.Add();
		s.n = tmp[i];
		s.pop_this = j == 0;
	}
}

// Returns links to variables in expression statements etc.
// The scope path is not continous, unlike with LVal.
// ~ The scope stack grows from left, and sometimes meet's it's end from the right side. ~
void EonStd::PushScopeRVal(AstNode& n) {
	Scope& s = spath.Add();
	s.n = &n;
	s.pop_this = true;
}

void EonStd::PopScope() {
	int rm_i = 0;
	for (int i = spath.GetCount()-1; i >= 0; i--) {
		Scope& s = spath[i];
		if (s.pop_this) {
			rm_i = i;
			break;
		}
	}
	int c = spath.GetCount() - rm_i;
	spath.Remove(rm_i, c);
	ASSERT(spath.GetCount() > 0);
}


NAMESPACE_TOPSIDE_END
