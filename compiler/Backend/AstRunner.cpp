#include "Backend.h"

NAMESPACE_TOPSIDE_BEGIN


AstRunner::AstRunner() :
	ErrorSource("AstRunner")
{
	
}

bool AstRunner::Execute(AstNode& n) {
	meta_builtin_expr = n.Find("expr", SEMT_META_BUILTIN);
	
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
	AstNode& owner = GetNonLockedOwner();
	
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
		if (s.src == SEMT_STATEMENT && s.stmt == STMT_META_FOR_COND) {
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
		else if (s.src == SEMT_STATEMENT) {
			if (!Visit(s))
				return false;
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
			
			bool b = cond_val.ToBool();
			if (!b)
				break;
			
			for (AstNode& s : block->sub) {
				if (!Visit(s))
					return false;
			}
			
			if (!Evaluate(*for_post, post_val))
				return false;
			
			dbg_i++;
			//ASSERT(dbg_i < 100);
			if (dbg_i >= 10)
				break;
		}
		//DUMP(dbg_i);
	}
	
	return true;
}

bool AstRunner::VisitMetaIf(AstNode& n) {
	ASSERT(n.src == SEMT_STATEMENT && n.stmt == STMT_META_IF);
	
	AstNode* d = AddDuplicate(n); // these can't be merge becaues of re-use
	if (!d)
		return false;
	
	AstNode* cond = n.Find(SEMT_EXPR);
	if (!cond) {
		AddError(n.loc, "internal error: expression not found");
		return false;
	}
	
	AstNode* closest_type = GetClosestType();
	AstNode& owner_block = GetBlock();
	AstNode* block = n.Find(SEMT_STATEMENT_BLOCK);
	if (!block) {
		AddError(n.loc, "internal error: block not found");
		return false;
	}
	
	AstNode* else_ = n.ctx_next;
	ASSERT(!else_ || (else_->src == SEMT_STATEMENT && else_->stmt == STMT_META_ELSE));
	
	Object cond_val;
	if (!Evaluate(*cond, cond_val))
		return false;
	
	d->type = closest_type;
	PushScope(*d, true);
	
	bool b = cond_val.ToBool();
	if (b) {
		block->locked = true;
		block->type = closest_type;
		PushScope(*block, true);
		if (!VisitStatementBlock(*block, false))
			return false;
		PopScope();
	}
	else if (else_) {
		block = else_->Find(SEMT_STATEMENT_BLOCK);
		if (!block) {
			AddError(else_->loc, "internal error: block not found");
			return false;
		}
		
		block->locked = true;
		block->type = closest_type;
		PushScope(*block, true);
		if (!VisitStatementBlock(*block, false))
			return false;
		PopScope();
	}
	
	PopScope();
	
	//d->rval = block->rval;
	ASSERT(d->rval);
	ASSERT(d->rval != d);
	
	return true;
}

AstNode* AstRunner::MergeStatement(AstNode& n) {
	AstNode& owner = GetNonLockedOwner();
	AstNode* d = 0;
	AstNode* block = 0;
	
	ASSERT(n.src == SEMT_STATEMENT);
	if (n.src != SEMT_STATEMENT) return 0;
	
	switch (n.stmt) {
	case STMT_RETURN:
		return VisitReturn(n);
		
	case STMT_EXPR:
		d = AddDuplicate(n);
		PushScope(*d, true);
		ASSERT(n.sub.GetCount());
		ASSERT(n.rval);
		if (n.rval) {
			AstNode& s = *n.rval;
			if (!Visit(s))
				return 0;
			if (IsRvalReturn(s.src))
				PopScope(); // expr rval
			//d->rval = s.next->rval;
		}
		PopScope();
		d->CopyPrevNextLinks();
		return d;
		
	case STMT_META_FOR:
	case STMT_META_IF:
	case STMT_META_ELSE:
		break;
	
	case STMT_IF:
		d = &owner.Add(n.loc);
		d->CopyFrom(n);
		Bind(n, *d);
		if (n.sub.GetCount()) {
			PushScope(*d);
			for (AstNode& s : n.sub) {
				if (!Visit(s))
					return 0;
				if (IsRvalReturn(s.src))
					PopScope();
			}
			PopScope();
		}
		return d;
	
	case STMT_CTOR:
		d = AddDuplicate(n);
		if (!d)
			return 0;
		PushScope(*d);
		ASSERT(n.sub.GetCount());
		ASSERT(n.rval);
		if (n.rval) {
			AstNode& s = *n.rval;
			if (!Visit(s))
				return 0;
			if (IsRvalReturn(s.src))
				PopScope(); // expr rval
		}
		PopScope();
		d->CopyPrevNextLinks();
		ASSERT(d->rval || n.rval->type->IsPartially(SEMT_META_ANY));
		return d;
		
	case STMT_NULL:
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

ObjectMap* AstRunner::GetRuntimeScope(const FileLocation& loc) {
	Object& o = *rpath.Top();
	ObjectMap* map = o.TryGetMap();
	if (!map) {
		AddError(loc, "internal error: can't add without object map");
		return 0;
	}
	return map;
}

void AstRunner::AddRuntimeScope(const FileLocation& loc, String name) {
	Object* s = CreateRuntimeField(loc, name);
	if (!s) return;
	
	rpath.Add(s);
	s->Create<ObjectArrayMapComb>();
}

Object* AstRunner::CreateRuntimeField(const FileLocation& loc, String name) {
	ObjectMap* map = GetRuntimeScope(loc);
	if (!map) return 0;
	
	if (name.IsEmpty()) {
		AddError(loc, "internal error: empty name");
		return 0;
	}
	
	Object& s = map->Add(name);
	return &s;
}

void AstRunner::PopRuntimeScope() {
	rpath.SetCount(rpath.GetCount()-1);
}

bool AstRunner::Visit(AstNode& n) {
	AstNode* s;
	Object* o;
	int pop_count;
	CHECK_SPATH_INIT
	
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
			if (IsRvalReturn(s.src))
				PopScope();
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
	
	case SEMT_META_CTOR:
		if (!VisitMetaCtor(n))
			return false;
		break;
		
	case SEMT_META_FUNCTION_STATIC:
		return VisitMetaStaticFunction(n);
		
	case SEMT_META_PARAMETER:
		s = AddDuplicate(n);
		if (!s)
			return false;
		AddRuntimeScope(n.loc, n.name);
		if (!n.sub.IsEmpty()) {
			PushScope(*s);
			for (AstNode& s : n.sub) {
				if (s.src == SEMT_RVAL)
					continue;
				if (!Visit(s))
					return false;
				if (IsRvalReturn(s.src))
					PopScope();
			}
			PopScope();
		}
		PopRuntimeScope();
		break;
		
	
	case SEMT_FUNCTION_STATIC:
	case SEMT_VARIABLE:
		s = Merge(n);
		if (!s)
			return false;
		AddRuntimeScope(n.loc, n.name);
		if (!n.sub.IsEmpty()) {
			PushScope(*s);
			for (AstNode& s : n.sub) {
				if (s.src == SEMT_RVAL)
					continue;
				if (!Visit(s))
					return false;
				if (IsRvalReturn(s.src))
					PopScope();
			}
			PopScope();
		}
		PopRuntimeScope();
		break;
		
	case SEMT_STATEMENT_BLOCK:
		s = Merge(n);
		if (!s)
			return false;
		if (!n.sub.IsEmpty()) {
			PushScope(*s);
			/*for (AstNode& s : n.sub) {
				if (s.src == SEMT_RVAL)
					continue;
				if (!Visit(s))
					return false;
				if (IsRvalReturn(s.src))
					PopScope();
			}*/
			if (!VisitStatementBlock(n, false))
				return false;
			PopScope();
		}
		break;
		
	case SEMT_EXPR:
		s = AddDuplicate(n);
		if (!s)
			return false;
		//AddRuntimeScope(n.loc, n.name);AddDuplicate
		//PushScope(*s);
		CHECK_SPATH_BEGIN_1
		pop_count = 0;
		for(int i = 0; i < n.i64; i++) {
			AstNode& l = *n.arg[i];
			if (!Visit(l))
				return false;
			if (IsRvalReturn(l.src))
				pop_count++;
			s->arg[i] = l.next;
		}
		//PopScope();
		//PopRuntimeScope();
		for(int i = 1; i < pop_count; i++) {
			PopScope();
		}
		ASSERT(pop_count >= 1);
		spath.Top().n = s;
		
		CHECK_SPATH_END
		
		if (s->op == OP_CALL && s->arg[0] && s->arg[0]->src == SEMT_META_RVAL && s->arg[1]) {
			if (!VisitMetaCall(*s, *s->arg[0], *s->arg[1]))
				return false;
		}
		else if (s->arg[0] && s->arg[0]->src == SEMT_META_RVAL)
			TODO
		break;
		
	case SEMT_ARGUMENT_LIST:
		s = Merge(n);
		if (!s)
			return false;
		if (!n.sub.IsEmpty()) {
			
			PushScope(*s);
			
			CHECK_SPATH_BEGIN
			
			for (AstNode& s : n.sub) {
				if (s.src == SEMT_ARGUMENT || s.IsPartially(SEMT_META_ANY)) {
					if (!Visit(s))
						return false;
					if (IsRvalReturn(s.src))
						PopScope();
					
					CHECK_SPATH_END
				}
			}
			
			CHECK_SPATH_END
			
			PopScope();
			
		}
		PushScopeRVal(*s);
		break;
		
	case SEMT_ARGUMENT:
		s = AddDuplicate(n);
		if (!s)
			return false;
		ASSERT(n.rval);
		if (n.rval) {
			PushScope(*s);
			/*for (AstNode& s : n.sub) {
				if (!Visit(s))
					return false;
			}*/
			if (!Visit(*n.rval))
				return false;
			if (IsRvalReturn(n.rval->src))
				PopScope();
			s->CopyPrevNextLinks();
			PopScope();
		}
		break;
		
	case SEMT_CTOR:
		if (n.type && n.type->IsPartially(SEMT_META_TYPE))
			return VisitMetaCtor(n);
		s = AddDuplicate(n);
		if (!s)
			return false;
		ASSERT(n.arg[0]);
		if (n.arg[0]) {
			AddRuntimeScope(n.loc, n.rval ? n.rval->name : n.type->name);
			PushScope(*s);
			if (!Visit(*n.arg[0]))
				return false;
			if (IsRvalReturn(n.arg[0]->src))
				PopScope();
			PopScope();
			PopRuntimeScope();
		}
		s->CopyPrevNextLinks();
		PushScopeRVal(*s);
		ASSERT(s->arg[0]);
		break;
		
	case SEMT_STATEMENT:
		switch (n.stmt) {
			case STMT_META_FOR: return VisitMetaFor(n);
			case STMT_META_IF: return VisitMetaIf(n);
			case STMT_META_ELSE: return true;
			default: break;
		}
		s = MergeStatement(n);
		if (!s)
			return false;
		break;
	
	case SEMT_RVAL:
		ASSERT(n.rval);
		if (n.rval->IsPartially(SEMT_META_FIELD)) {
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
	
	case SEMT_PARAMETER:
		s = AddDuplicate(n);
		o = CreateRuntimeField(n.loc, n.name);
		if (!o) return false;
		break;
	
	case SEMT_RESOLVE:
		return VisitResolve(n);
	
	case SEMT_IDPART:
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
	AstNode& owner = GetNonLockedOwner();
	AstNode& d = owner.Add(n.loc);
	d.CopyFrom(n);
	Bind(n, d);
	return &d;
}

bool AstRunner::VisitMetaRVal(AstNode& n) {
	if (!n.rval || !n.rval->IsPartially(SEMT_META_FIELD)) {ASSERT(0); return false;}
	
	AstNode& ref = *n.rval;
	
	if (ref.src == SEMT_META_VARIABLE || ref.src == SEMT_META_PARAMETER) {
		ASSERT(ref.next_obj);
		if (!ref.next_obj) {
			AddError(n.loc, "internal error: no object");
			return false;
		}
		
		AstNode& owner = GetNonLockedOwner();
		AstNode& d = owner.Add(n.loc);
		d.CopyFromObject(n.loc, *ref.next_obj);
		Bind(n, d);
		
		PushScopeRVal(d);
	}
	else TODO;
	
	return true;
}

bool AstRunner::VisitMetaCtor(AstNode& n) {
	ASSERT(n.src == SEMT_META_CTOR);
	ASSERT(n.type && n.type->IsPartially(SEMT_META_TYPE));
	ASSERT(n.rval);
	
	AstNode& var = *n.rval;
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
		ASSERT(arg->rval);
		AstNode& argvar = *arg->rval;
		
		if (argvar.src == SEMT_CONSTANT) {
			argvar.CopyToObject(o);
		}
		else if (argvar.src == SEMT_EXPR) {
			if (!Evaluate(argvar, o))
				return false;
		}
		else TODO
	}
	else {
		TODO
	}
	
	return true;
}

bool AstRunner::VisitMetaStaticFunction(AstNode& n) {
	ASSERT(n.src == SEMT_META_FUNCTION_STATIC);
	
	Object* o = CreateRuntimeField(n.loc, n.name);
	if (!o)
		return false;
	
	AstNode* d = Merge(n);
	if (!d)
		return false;
	
	/* This is done while calling the meta function
	PushScope(*d);
	for (AstNode& s : n.sub) {
		if (!Visit(s))
			return false;
	}
	PopScope();*/
	
	return true;
}

bool AstRunner::VisitResolve(AstNode& n) {
	ASSERT(n.src == SEMT_RESOLVE);
	ASSERT(n.filter != SEMT_NULL);
	ASSERT(!n.id.IsEmpty());
	
	AstNode* decl = FindDeclaration(n.id, n.filter);
	if (!decl) {
		AddError(n.loc, "couldn't find declaration '" + n.id.ToString() + "'");
		return false;
	}
	
	if (decl->src == SEMT_META_FUNCTION_STATIC) {
		AstNode& rval = GetTopNode().Add(n.loc);
		rval.src = SEMT_META_RVAL;
		rval.rval = decl;
		Bind(n, rval);
		PushScopeRVal(rval);
		return true;
	}
	else TODO
}

bool AstRunner::VisitStatementBlock(AstNode& n, bool req_rval) {
	AstNode& block = GetBlock();
	AstNode& owner = GetNonLockedOwner();
	ASSERT(block.src == SEMT_STATEMENT_BLOCK);
	ASSERT(&n != &block);
	int dbg_count = 0;
	
	//ASSERT(n.next == &block);
	//LOG(n.GetTreeString(0));
	
	if (!n.sub.IsEmpty()) {
		//PushScope(*n.next);
		int dbg_i = 0;
		for (AstNode& s : n.sub) {
			int prev_count = block.sub.GetCount();
			CHECK_SPATH_BEGIN
			
			if (!Visit(s))
				return false;
			
			if (s.next && s.next->rval) {
				AstNode& r = *s.next->rval;
				if (block.type == meta_builtin_expr) {
					if (IsRvalReturn(r.src)) {
						owner.rval = &r;
						//LOG(r.GetTreeString(0, true));
						ASSERT(&owner != owner.rval);
					}
				}
			}
			
			if (IsRvalReturn(s.src)) {
				PopScope();
			}
			
			bool added = block.sub.GetCount() > prev_count;
			if (added) dbg_count++;
			
			if (s.src == SEMT_STATEMENT && s.stmt == STMT_RETURN) {ASSERT(added);}
			
			ASSERT(&GetBlock() == &block);
			CHECK_SPATH_END
			
			//DUMP(added);
			//ASSERT(spath.Top().n == &block);
			//ASSERT(block.sub.GetCount() == dbg_i+1);
			
			dbg_i++;
		}
		//PopScope();
	}
	
	//LOG(n.next->GetTreeString(0));
	//ASSERT(n.next->sub.GetCount() == n.sub.GetCount());
	
	if (req_rval && !owner.rval) {
		AddError(n.loc, "internal error: no rval");
		return false;
	}
	return true;
}

AstNode* AstRunner::VisitReturn(AstNode& n) {
	AstNode& block = GetBlock();
	ASSERT(spath.Top().n == &block);
	int c = block.sub.GetCount();
	
	AstNode* d = AddDuplicate(n);
	if (n.sub.GetCount()) {
		CHECK_SPATH_BEGIN
		
		PushScope(*d);
		if (n.rval) {
			if (!Visit(*n.rval))
				return 0;
			if (IsRvalReturn(n.rval->src))
				PopScope();
		}
		PopScope();
		
		CHECK_SPATH_END
	}
	d->CopyPrevNextLinks();
	
	ASSERT(block.sub.GetCount() > c);
	block.rval = d->rval;
	ASSERT(block.rval != &block);
	return d;
}

bool AstRunner::VisitMetaCall(AstNode& d, AstNode& rval, AstNode& args) {
	if (rval.src == SEMT_META_RVAL && args.src == SEMT_ARGUMENT_LIST) {
		//AstNode& ret = GetTopNode().Add(d.loc);
		
		AstNode& fn = *rval.rval->prev;
		AstNode& ret_type = *fn.type;
		ASSERT(fn.src == SEMT_META_FUNCTION_STATIC);
		fn.locked = true;
		PushScope(fn, true);
		
		Object o;
		ObjectMap& map = o.CreateMap();
		
		PushScope(d, true);
		d.type = fn.type;
		
		Vector<AstNode*> arg_ptrs;
		Vector<AstNode*> param_ptrs;
		
		for (AstNode& arg : args.sub) {
			if (arg.src != SEMT_ARGUMENT) continue;
			arg_ptrs.Add(&arg);
		}
		for (AstNode& param : fn.sub) {
			if (param.src != SEMT_META_PARAMETER) continue;
			param_ptrs.Add(&param);
		}
		if (arg_ptrs.GetCount() != param_ptrs.GetCount()) {
			AddError(args.loc, "got '" + IntStr(arg_ptrs.GetCount()) + "' arguments, but expected '" + IntStr(param_ptrs.GetCount()) + "'");
			return false;
		}
		
		for(int i = 0; i < arg_ptrs.GetCount(); i++) {
			AstNode& arg = *arg_ptrs[i];
			AstNode& param = *param_ptrs[i];
			
			ASSERT(param.name.GetCount());
			Object& ao = map.Add(param.name);
			if (!arg.rval) {
				AddError(arg.loc, "internal error: expected argument expression");
				return false;
			}
			AstNode& aexpr = *arg.rval;
			if (!Evaluate(aexpr, ao))
				return false;
			
			param.next_obj = &ao;
		}
		
		AstNode* block = fn.Find(SEMT_STATEMENT_BLOCK);
		if (!block) {
			AddError(fn.loc, "internal error: function has no statement block");
			return false;
		}
		
		AstNode* dup_block = AddDuplicate(*block);
		
		block->locked = true;
		dup_block->type = fn.type;
		PushScope(*dup_block, true);
		
		PushRuntimeScope(o);
		if (!VisitStatementBlock(*block, true))
			return false;
		PopRuntimeScope();
		
		PopScope(); // block
		PopScope(); // ret
		PopScope(); // fn
		
		for (AstNode* param : param_ptrs) param->next_obj = 0;
		
		
		// Override meta-node type and link function return value
		if (spath.Top().n != &d) {
			AddError(d.loc, "internal error: stack did not unwind properly");
			return false;
		}
		
		//d.link[0] = &ret;
		SemanticType filter = SEMT_NULL;
		if (fn.type) {
			if (&ret_type == meta_builtin_expr) {
				d.src = SEMT_RVAL;
				d.rval = dup_block->rval;
				ASSERT(d.rval);
				//LOG(d.rval->GetTreeString(0, true));
				/*if (block->rval) {
					d.rval = block->rval;
					//LOG(d.rval->GetTreeString(0, true));
					ASSERT(d.rval != &d);
				}
				else
					filter = SEMT_WITH_RVAL_RET;*/
			}
			else TODO
		}
		else TODO;
		//if (filter != SEMT_NULL)
		//	d.link[0] = d.FindPartial(filter);
	}
	else TODO
	
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
				else TODO
			}
		}
		else {
			TODO
		}
	}
	else if (n.src == SEMT_EXPR) {
		if (n.op == OP_POSTINC || n.op == OP_POSTDEC) {
			if (n.arg[0] && n.arg[0]->src == SEMT_RVAL) {
				Object* v = 0;
				if (n.arg[0]->next_obj)
					v = n.arg[0]->next_obj;
				else if (n.arg[0]->rval && n.arg[0]->rval->next_obj)
					v = n.arg[0]->rval->next_obj;
				if (v) {
					o = *v;
					*v = v->ToInt() + (int64)(n.op == OP_POSTINC ? 1 : -1);
					return true;
				}
				else TODO
			}
		}
		
		Object a[AstNode::ARG_COUNT];
		
		ASSERT(n.i64 > 0);
		for(int i = 0; i < n.i64; i++) {
			if (!n.arg[i]) {
				AddError(n.loc, "expression failed");
				return false;
			}
			if (!Evaluate(*n.arg[i], a[i]))
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
		ASSERT(n.rval);
		if (!n.rval || !n.rval->next_obj) {
			AddError(n.loc, "internal error: incomplete rval");
			return false;
		}
		
		Object& v = *n.rval->next_obj;
		o = v;
	}
	else TODO
	
	return true;
}


NAMESPACE_TOPSIDE_END
