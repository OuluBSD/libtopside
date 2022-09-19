#include "Backend.h"

NAMESPACE_TOPSIDE_BEGIN


AstRunner::AstRunner() :
	ErrorSource("AstRunner")
{
	
}

bool AstRunner::Execute(AstNode& n) {
	
	if (!Visit(n))
		return false;
	
	return true;
}

String AstRunner::GetTreeString(int indent) const {
	return root.GetTreeString(indent);
}

String AstRunner::GetCodeString(const CodeArgs& args) const {
	return root.GetCodeString(args);
}

String AstRunner::ToString() const {
	return root.ToString();
}

AstNode& AstRunner::GetRoot() {
	return root;
}

AstNode* AstRunner::Merge(AstNode& n) {
	AstNode& owner = *spath.Top().n;
	
	if (n.name.GetCount()) {
		AstNode* prev = owner.Find(n.name);
		if (prev) {
			if (!IsMergeable(*prev, n)) {
				AddError(n.loc, "cannot merge " + GetSemanticTypeString(n.src) + " to " + GetSemanticTypeString(prev->src));
				return 0;
			}
			return prev;
		}
	}
	else {
		AstNode* prev = owner.Find(n.src);
		if (prev) {
			if (!IsMergeable(*prev, n)) {
				AddError(n.loc, "cannot merge " + GetSemanticTypeString(n.src) + " to " + GetSemanticTypeString(prev->src));
				return 0;
			}
			return prev;
		}
	}
	
	AstNode& d = owner.Add(n.loc);
	d.CopyFrom(n);
	Bind(n, d);
	
	return &d;
}

bool AstRunner::VisitMetaFor(AstNode& n) {
	ASSERT(n.src == SEMT_STATEMENT && n.stmt == STMT_META_FOR);
	
	AstNode* block = 0;
	AstNode* for_cond = 0;
	AstNode* for_post = 0;
	AstNode* for_range = 0;
	
	for (AstNode& s : n.sub) {
		if (s.src == SEMT_CTOR) {
			if (!VisitMetaCtor(s))
				return false;
		}
		else if (s.src == SEMT_STATEMENT && s.stmt == STMT_META_FOR_COND) {
			for_cond = &s;
		}
		else if (s.src == SEMT_STATEMENT && s.stmt == STMT_META_FOR_POST) {
			for_post = &s;
		}
		else if (s.src == SEMT_STATEMENT &&  s.stmt == STMT_META_FOR_RANGE) {
			for_range = &s;
		}
		else if (s.src == SEMT_RVAL) {
			// pass
		}
		else if (s.src == SEMT_STATEMENT_BLOCK) {
			block = &s;
		}
		else TODO
	}
	
	if (!block) {
		AddError(n.loc, "no statement-block in meta-for loop");
		return false;
	}
	
	if (for_range) {
		TODO
	}
	else {
		if (!for_cond || !for_post) {
			AddError(n.loc, "internal error: no for-cond or for-post statement");
			return false;
		}
		
		
		
		Object cond_val, post_val;
		int dbg_i = 0;
		while (1) {
			
			if (!Evaluate(*for_cond, cond_val))
				return false;
			
			bool b = false;
			dword type = cond_val.GetType();
			if (type == BOOL_V)
				b = cond_val.Get<bool>();
			else if (type == INT_V || type == INT64_V)
				b = cond_val.ToInt();
			else if (type == DOUBLE_V)
				b = cond_val.ToDouble();
			
			if (!b)
				break;
			
			for (AstNode& s : block->sub) {
				if (!Visit(s))
					return false;
			}
			
			if (!Evaluate(*for_post, post_val))
				return false;
			
			dbg_i++;
		}
		//DUMP(dbg_i);
	}
	
	return true;
}

AstNode* AstRunner::MergeStatement(AstNode& n) {
	AstNode& owner = *spath.Top().n;
	AstNode* d = 0;
	
	ASSERT(n.src == SEMT_STATEMENT);
	if (n.src != SEMT_STATEMENT) return 0;
	
	switch (n.stmt) {
	case STMT_RETURN:
		d = &owner.Add(n.loc);
		d->CopyFrom(n);
		Bind(n, *d);
		if (n.sub.GetCount()) {
			PushScope(*d);
			for (int i = n.sub.GetCount()-1; i >= 0; i--) {
				AstNode& s = n.sub[i];
				if (s.src == SEMT_EXPR) {
					if (!Visit(s))
						return 0;
					for(int j = 1; j < s.i64; j++)
						PopScope(); // expr rval
					break;
				}
			}
			PopScope();
		}
		return d;
		
	case STMT_EXPR:
		d = &owner.Add(n.loc);
		d->CopyFrom(n);
		Bind(n, *d);
		PushScope(*d);
		ASSERT(n.sub.GetCount());
		for (int i = n.sub.GetCount()-1; i >= 0; i--) {
			AstNode& s = n.sub[i];
			if (s.src == SEMT_EXPR || s.src == SEMT_CTOR) {
				if (!Visit(s))
					return 0;
				PopScope(); // expr rval
				break;
			}
		}
		PopScope();
		return d;
		
	case STMT_META_FOR:
		break;
	
	case STMT_NULL:
	case STMT_IF:
	case STMT_ELSE:
	case STMT_DOWHILE:
	case STMT_WHILE:
	case STMT_FOR:
	case STMT_FOR_COND:
	case STMT_FOR_POST:
	case STMT_FOR_RANGE:
	case STMT_BREAK:
	case STMT_CONTINUE:
	case STMT_CASE:
	case STMT_DEFAULT:
	case STMT_SWITCH:
	case STMT_BLOCK:
	default:
		TODO
		break;
		
	}
	
	AddError(n.loc, "internal error");
	return 0;
}

bool AstRunner::IsMergeable(AstNode& prev, AstNode& to_merge) const {
	if (to_merge.src != prev.src)
		return false;
	
	return true;
}

void AstRunner::PushRuntimeScope(Object& o) {
	rpath.Add(&o);
}

void AstRunner::AddRuntimeScope(const FileLocation& loc, String name) {
	Object& o = *rpath.Top();
	ObjectMap* map = o.TryGetMap();
	if (!map) {
		AddError(loc, "internal error: can't add without object map");
		return;
	}
	
	Object& s = map->Add(name);
	rpath.Add(&s);
	s.Create<ObjectArrayMapComb>();
	
}

void AstRunner::PopRuntimeScope() {
	rpath.SetCount(rpath.GetCount()-1);
}

bool AstRunner::Visit(AstNode& n) {
	AstNode* s;

	switch (n.src) {
	case SEMT_ROOT:
		ASSERT(spath.IsEmpty());
		ASSERT(rpath.IsEmpty());
		runtime.Create<ObjectArrayMapComb>();
		PushRuntimeScope(runtime);
		GetRoot().src = SEMT_ROOT;
		Bind(n, GetRoot());
		PushScope(GetRoot());
		for (AstNode& s : n.sub) {
			if (s.src == SEMT_RVAL)
				continue;
			if (!Visit(s))
				return false;
		}
		PopScope();
		PopRuntimeScope();
		//ASSERT(spath.IsEmpty());
		break;
	
	case SEMT_BUILTIN:
	case SEMT_FUNCTION_BUILTIN:
		if (!Merge(n))
			return false;
		break;
	
	case SEMT_META_BUILTIN:
		break;
	
	case SEMT_META_VARIABLE:
		DeclareMetaVariable(n);
		break;
	
	case SEMT_FUNCTION_STATIC:
	case SEMT_STATEMENT_BLOCK:
	case SEMT_VARIABLE:
		s = Merge(n);
		if (!s)
			return false;
		AddRuntimeScope(n.loc, n.name);
		if (!n.sub.IsEmpty()) {
			PushScope(*s);
			for (AstNode& s : n.sub) {
				if (!Visit(s))
					return false;
			}
			PopScope();
		}
		PopRuntimeScope();
		break;
		
	case SEMT_EXPR:
		s = Merge(n);
		if (!s)
			return false;
		//AddRuntimeScope(n.loc, n.name);
		//PushScope(*s);
		for(int i = 0; i < n.i64; i++) {
			AstNode& l = *n.link[i];
			if (!Visit(l))
				return false;
			s->link[i] = l.next;
		}
		//PopScope();
		//PopRuntimeScope();
		for(int i = 1; i < n.i64; i++) {
			PopScope();
		}
		spath.Top().n = s;
		break;
		
	case SEMT_ARGUMENT_LIST:
	case SEMT_ARGUMENT:
		if (n.src == SEMT_ARGUMENT)
			PopScope();
		s = Merge(n);
		if (!s)
			return false;
		if (!n.sub.IsEmpty()) {
			PushScope(*s);
			for (AstNode& s : n.sub) {
				if (!Visit(s))
					return false;
			}
			PopScope();
		}
		break;
		
	case SEMT_CTOR:
		if (n.type && n.type->IsPartially(SEMT_META_TYPE))
			return VisitMetaCtor(n);
		s = AddDuplicate(n);
		if (!s)
			return false;
		AddRuntimeScope(n.loc, n.name);
		PushScope(*s);
		for (AstNode& s : n.sub) {
			if (!Visit(s))
				return false;
		}
		PopScope();
		PopRuntimeScope();
		PushScopeRVal(*s);
		break;
		
	case SEMT_STATEMENT:
		switch (n.stmt) {
			case STMT_META_FOR: return VisitMetaFor(n);
			default: break;
		}
		s = MergeStatement(n);
		if (!s)
			return false;
		break;
	
	case SEMT_RVAL:
		ASSERT(n.link[0]);
		if (n.link[0]->IsPartially(SEMT_META_FIELD)) {
			if (!VisitMetaRVal(n))
				return false;
		}
		else {
			s = AddDuplicate(n);
			if (!s)
				return false;
			PushScopeRVal(*s);
			/*
			expr link is used instead of this:
			if (n.sub.GetCount()) {
				for (AstNode& s : n.sub) {
					if (!Visit(s))
						return false;
				}
			}*/
		}
		break;
		
	case SEMT_CONSTANT:
		s = AddDuplicate(n);
		if (!s)
			return false;
		PushScopeRVal(*s);
		break;
	
	case SEMT_IDPART:
	case SEMT_PARAMETER:
	case SEMT_RESOLVE:
	case SEMT_NULL:
	case SEMT_NAMESPACE:
	case SEMT_TYPEDEF:
	case SEMT_CLASS_DECL:
	case SEMT_CLASS:
	case SEMT_CLASS_TEMPLATE:
	case SEMT_FUNCTION_METHOD:
	case SEMT_ARRAYSIZE:
	default:
		TODO
	}
	
	
	return true;
}

AstNode* AstRunner::AddDuplicate(AstNode& n) {
	AstNode& owner = *spath.Top().n;
	AstNode& d = owner.Add(n.loc);
	d.CopyFrom(n);
	Bind(n, d);
	return &d;
}

bool AstRunner::VisitMetaRVal(AstNode& n) {
	if (!n.link[0] || !n.link[0]->IsPartially(SEMT_META_FIELD)) {ASSERT(0); return false;}
	
	AstNode& ref = *n.link[0];
	
	if (ref.src == SEMT_META_VARIABLE) {
		ASSERT(ref.next_obj);
		if (!ref.next_obj) return false;
		
		AstNode& owner = *spath.Top().n;
		AstNode& d = owner.Add(n.loc);
		d.CopyFromObject(n.loc, *ref.next_obj);
		Bind(n, d);
		
		PushScopeRVal(d);
	}
	else TODO;
	
	return true;
}

bool AstRunner::VisitMetaCtor(AstNode& n) {
	ASSERT(n.type && n.type->IsPartially(SEMT_META_TYPE));
	ASSERT(n.link[0]);
	
	AstNode& var = *n.link[0];
	AstNode* args = n.Find(SEMT_ARGUMENT_LIST);
	if (!args) {
		TODO
	}
	
	ASSERT(var.next_obj);
	Object& o = *var.next_obj;
	
	int arg_count = 0;
	AstNode* arg = 0;
	for (AstNode& s : args->sub) {
		if (s.src == SEMT_ARGUMENT) {
			arg = &s;
			arg_count++;
		}
	}
	
	if (arg_count == 1) {
		ASSERT(arg->link[0]);
		AstNode& argvar = *arg->link[0];
		
		if (argvar.src == SEMT_CONSTANT) {
			argvar.CopyToObject(o);
		}
		else TODO
	}
	else {
		TODO
	}
	
	return true;
}

bool AstRunner::DeclareMetaVariable(AstNode& n) {
	Object& owner = *rpath.Top();
	ObjectMap* map = owner.TryGetMap();
	if (!map) {
		AddError(n.loc, "internal error: declaring can be done to a map only");
		return false;
	}
	
	if (n.src == SEMT_META_VARIABLE) {
		ASSERT(n.name.GetCount());
		Object& o = map->Add(n.name);
		n.next_obj = &o;
	}
	else TODO;
	
	return true;
}

bool AstRunner::Evaluate(AstNode& n, Object& o) {
	
	if (n.src == SEMT_STATEMENT) {
		if (n.stmt == STMT_EXPR ||
			n.stmt == STMT_META_FOR_COND ||
			n.stmt == STMT_META_FOR_POST) {
			for (int i = n.sub.GetCount()-1; i >= 0; i--) {
				AstNode& e = n.sub[i];
				if (e.src == SEMT_EXPR) {
					return Evaluate(e, o);
				}
			}
		}
		else {
			TODO
		}
	}
	else if (n.src == SEMT_EXPR) {
		if (n.op == OP_POSTINC || n.op == OP_POSTDEC) {
			if (n.link[0] && n.link[0]->src == SEMT_RVAL) {
				Object* v = 0;
				if (n.link[0]->next_obj)
					v = n.link[0]->next_obj;
				else if (n.link[0]->link[0] && n.link[0]->link[0]->next_obj)
					v = n.link[0]->link[0]->next_obj;
				if (v) {
					o = *v;
					*v = v->ToInt() + (int64)(n.op == OP_POSTINC ? 1 : -1);
					return true;
				}
			}
		}
		
		Object a[AstNode::LINK_COUNT];
		
		ASSERT(n.i64 > 0);
		for(int i = 0; i < n.i64; i++) {
			if (!n.link[i]) {
				AddError(n.loc, "expression failed");
				return false;
			}
			if (!Evaluate(*n.link[i], a[i]))
				return false;
		}
		
		switch (n.op) {
			case OP_POSTINC:
			case OP_POSTDEC:
			case OP_POSITIVE:	o = a[0]; return true;
			case OP_NOT:		o = !a[0]; return true;
			case OP_NEGATIVE:	o = -a[0]; return true;
			case OP_GREATER:	o = a[0] > a[1]; return true;
			case OP_LESS:		o = a[0] < a[1]; return true;
			case OP_ADD:		o = a[0] + a[1]; return true;
			case OP_SUB:		o = a[0] - a[1]; return true;
			case OP_MUL:		o = a[0] * a[1]; return true;
			case OP_DIV:		o = a[0] / a[1]; return true;
			case OP_MOD:		o = a[0] % a[1]; return true;
			case OP_LSH:		o = a[0] << a[1]; return true;
			case OP_RSH:		o = a[0] >> a[1]; return true;
			
			case OP_NULL:
			case OP_INC:
			case OP_DEC:
			case OP_NEGATE:
			case OP_GREQ:
			case OP_LSEQ:
			case OP_EQ:
			case OP_INEQ:
			case OP_BWAND:
			case OP_BWXOR:
			case OP_BWOR:
			case OP_AND:
			case OP_OR:
			case OP_ASSIGN:
			case OP_ADDASS:
			case OP_SUBASS:
			case OP_MULASS:
			case OP_DIVASS:
			case OP_MODASS:
			case OP_COND:
			case OP_CALL:
			case OP_SUBSCRIPT:
			default:
				TODO
		}
	}
	else if (n.src == SEMT_CONSTANT) {
		n.CopyToObject(o);
	}
	else if (n.src == SEMT_RVAL) {
		ASSERT(n.link[0]);
		if (!n.link[0] || !n.link[0]->next_obj) {
			AddError(n.loc, "internal error: incomplete rval");
			return false;
		}
		
		Object& v = *n.link[0]->next_obj;
		o = v;
	}
	else TODO
	
	return true;
}


NAMESPACE_TOPSIDE_END
