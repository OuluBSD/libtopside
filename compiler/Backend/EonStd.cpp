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

AstNode* EonStd::AddBuiltinType(String name) {
	AstNode& root = GetRoot();
	AstNode& sn = root.Add(FileLocation(), name);
	sn.src = SEMT_BUILTIN;
	return &sn;
}

AstNode* EonStd::AddMetaBuiltinType(String name) {
	AstNode& root = GetRoot();
	AstNode& sn = root.Add(FileLocation(), name);
	sn.src = SEMT_META_BUILTIN;
	return &sn;
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
	return s;
}

void EonStd::InitDefault(bool add_root) {
	builtin_void =			AddBuiltinType("void");
	builtin_int =			AddBuiltinType("int");
	builtin_long =			AddBuiltinType("long");
	builtin_uint =			AddBuiltinType("uint");
	builtin_ulong =			AddBuiltinType("ulong");
	builtin_float =			AddBuiltinType("float");
	builtin_double =		AddBuiltinType("double");
	builtin_byte =			AddBuiltinType("byte");
	builtin_char =			AddBuiltinType("char");
	builtin_short =			AddBuiltinType("short");
	builtin_ushort =		AddBuiltinType("ushort");
	builtin_cstring =		AddBuiltinType("cstring");
	
	meta_builtin_void =			AddMetaBuiltinType("void");
	meta_builtin_int =			AddMetaBuiltinType("int");
	meta_builtin_double =		AddMetaBuiltinType("double");
	meta_builtin_cstring =		AddMetaBuiltinType("cstring");
	meta_builtin_stmt =			AddMetaBuiltinType("stmt");
	
	meta_builtin_machstmt =		AddMetaBuiltinType("machstmt");
	meta_builtin_chainstmt =	AddMetaBuiltinType("chainstmt");
	meta_builtin_loopstmt =		AddMetaBuiltinType("loopstmt");
	
	meta_builtin_atomstmt =		AddMetaBuiltinType("atomstmt");
	meta_builtin_worldstmt =	AddMetaBuiltinType("worldstmt");
	meta_builtin_systemstmt =	AddMetaBuiltinType("systemstmt");
	meta_builtin_poolstmt =		AddMetaBuiltinType("poolstmt");
	meta_builtin_entitystmt =	AddMetaBuiltinType("entitystmt");
	meta_builtin_compstmt =		AddMetaBuiltinType("compstmt");
	meta_builtin_params =		AddMetaBuiltinType("params");
	meta_builtin_expr =			AddMetaBuiltinType("expr");
	
	
	{
		AstNode& logger = GetRoot().Add(FileLocation(), "LOG");
		logger.src = SEMT_FUNCTION_BUILTIN;
	}
	
	GetRoot().src = SEMT_ROOT;
	
	if (add_root)
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

AstNode* EonStd::FindDeclaration(const Vector<String>& id, SemanticType accepts) {
	if (id.IsEmpty())
		return 0;
	
	for (int i = spath.GetCount()-1; i >= 0; i--) {
		Scope& s = spath[i];
			
		AstNode* n = GetDeclaration(s.n, id, accepts);
		if (n)
			return n;
	}
	return 0;
}

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
			else if (t->IsType('#')) {
				next = cur;
				// pass, next = &cur->GetAdd(SEMT_TYPE_POINTER);
			}
			else if (t->IsType('&')) {
				next = cur;
				// pass, next = &cur->GetAdd(SEMT_TYPE_LREF);
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
	
	if (id.head_count > 0 && id.tail_count > 0) {
		return 0;
	}
	
	if (cur && id.head_count > 0) {
		TODO
	}
	else if (cur && id.tail_count > 0) {
		if (cur->IsPartially(SEMT_TYPE)) {
			for(int i = 0; i < id.tail_count; i++) {
				switch (id.tail[i]) {
				case PathIdentifier::PTR:
					cur = &cur->GetAdd(id.end->loc, SEMT_TYPE_POINTER);
					break;
				
				case PathIdentifier::LREF:
					cur = &cur->GetAdd(id.end->loc, SEMT_TYPE_LREF);
					break;
				
				default:
					return 0;
				}
			}
		}
		else {
			TODO
		}
	}
	
	SemanticType a = id.is_meta[id.part_count-1] ? SEMT_META_ANY : accepts;
	
	if (cur && accepts == SEMT_NULL || cur->IsPartially(a))
		return cur;
	
	return 0;
}

AstNode* EonStd::GetDeclaration(AstNode* owner, const Vector<String>& id, SemanticType accepts) {
	AstNode* cur = owner;
	AstNode* next = 0;
	AstNode* prev = 0;
	
	for(int i = 0; i < id.GetCount(); i++) {
		bool last = i == id.GetCount()-1;
		next = 0;
		String name = id[i];
		for (int tries = 0; tries < 100; tries++) {
			SemanticType a = last ? accepts : SEMT_NULL;
			next = cur->Find(name, a);
			
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
	
	SemanticType a = accepts;
	
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
					cur = &cur->Add(t->loc, id, max(0, cur->sub.GetCount()-2));
			}
			else cur = &cur->GetAdd(t->loc, id);
			if (cur->src == SEMT_NULL)
				cur->src = SEMT_IDPART;
		}
		else {
			TODO
		}
	}
	
	return *cur;
}

AstNode& EonStd::DeclareRelative(const PathIdentifier& id) {
	ASSERT(id.part_count > 0);
	return Declare(*spath.Top().n, id);
}

AstNode* EonStd::GetClosestType(bool skip_locked) {
	for(int i = spath.GetCount()-1; i >= 0; i--) {
		Scope& scope = spath[i];
		if (skip_locked && scope.n->locked)
			continue;
		if (scope.n->IsPartially(SEMT_FUNCTION))
			return 0;
		if (scope.n->type)
			return scope.n->type;
	}
	return 0;
}
AstNode& EonStd::GetBlock() {
	for(int i = spath.GetCount()-1; i >= 0; i--) {
		Scope& scope = spath[i];
		if (scope.n->locked)
			continue;
		if (scope.n->IsPartially(SEMT_BLOCK))
			return *scope.n;
	}
	return GetRoot();
}


AstNode& EonStd::GetNonLockedOwner() {
	for(int i = spath.GetCount()-1; i >= 0; i--) {
		Scope& scope = spath[i];
		if (scope.n->locked)
			continue;
		return *scope.n;
	}
	return GetRoot();
}

void EonStd::PushScope(AstNode& n, bool non_continuous) {
	if (spath.IsEmpty() || non_continuous) {
		ASSERT(&n == &GetRoot() || non_continuous);
		Scope& s = spath.Add();
		s.n = &n;
		s.pop_this = true;
	}
	else {
		thread_local static Vector<AstNode*> tmp;
		AstNode* cur = spath.Top().n;
		
		tmp.SetCount(0);
		AstNode* iter = &n;
		int dbg_i = 0;
		while (iter && iter != cur) {
			tmp.Add(iter);
			iter = iter->GetSubOwner();
			dbg_i++;
		}
		ASSERT(iter == cur);
		
		for (int i = tmp.GetCount()-1, j = 0; i >= 0; i--, j++) {
			Scope& s = spath.Add();
			s.n = tmp[i];
			s.pop_this = j == 0;
		}
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

AstNode* EonStd::PopScope() {
	int rm_i = 0;
	for (int i = spath.GetCount()-1; i >= 0; i--) {
		Scope& s = spath[i];
		if (s.pop_this) {
			rm_i = i;
			break;
		}
	}
	int c = spath.GetCount() - rm_i;
	AstNode* ret = 0;
	if (c) ret = spath[rm_i].n;
	spath.Remove(rm_i, c);
	return ret;
}

String EonStd::GetTypeInitValueString(AstNode& n) const {
	if (n.src == SEMT_META_BUILTIN) {
		if (n.name == "int")
			return "0";
		TODO
	}
	else {
		TODO
	}
}

AstNode* EonStd::FindStackName(String name, SemanticType accepts) {
	for (int i = spath.GetCount()-1; i >= 0; i--) {
		Scope& s = spath[i];
		for (AstNode& ss : s.n->sub) {
			if (ss.name == name && (accepts == SEMT_NULL || ss.IsPartially(accepts)))
				return &ss;
		}
		if (s.n->name == name && (accepts == SEMT_NULL || s.n->IsPartially(accepts)))
			return s.n;
	}
	return 0;
}

AstNode* EonStd::FindStackObject(String name) {
	for (int i = spath.GetCount()-1; i >= 0; i--) {
		Scope& s = spath[i];
		for (AstNode& ss : s.n->sub) {
			if (ss.name == name)
				return &ss;
		}
		if (s.n->name == name)
			return s.n;
	}
	return 0;
}

AstNode* EonStd::FindStackWithPrev(const AstNode* prev) {
	for (int i = spath.GetCount()-1; i >= 0; i--) {
		Scope& s = spath[i];
		for (AstNode& ss : s.n->sub) {
			if (ss.prev == prev)
				return &ss;
		}
		if (s.n->prev == prev)
			return s.n;
	}
	return 0;
}

AstNode* EonStd::FindStackWithPrevDeep(const AstNode* prev) {
	for (int i = spath.GetCount()-1; i >= 0; i--) {
		Scope& s = spath[i];
		const AstNode* iter = prev;
		while (iter) {
			if (s.n->prev == iter) {
				return s.n->FindWithPrevDeep(prev);
			}
			iter = iter->GetSubOwner();
		}
	}
	if (!spath.IsEmpty())
		return spath[0].n->FindWithPrevDeep(prev);
	return 0;
}


NAMESPACE_TOPSIDE_END
