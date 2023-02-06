#include "Backend.h"

NAMESPACE_TOPSIDE_BEGIN


AstRunner::AstRunner() :
	ErrorSource("AstRunner")
{
	
}

bool AstRunner::Execute(const AstNode& n) {
	
	InitDefault(false);
	
	AstNode& root = GetRoot();
	
	for (const AstNode& s : n.sub) {
		if (s.src == SEMT_BUILTIN || s.src == SEMT_META_BUILTIN) {
			AstNode* local = root.Find(s.name, s.src);
			if (local)
				local->prev = &s;
		}
	}
	
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

AstNode* AstRunner::Merge(const AstNode& n) {
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
	d.CopyFrom(this, n);
	
	return &d;
}

AstNode* AstRunner::VisitMetaFor(const AstNode& n) {
	ASSERT(n.src == SEMT_STATEMENT && n.stmt == STMT_META_FOR);
	
	const AstNode* block = 0;
	const AstNode* for_cond = 0;
	const AstNode* for_post = 0;
	const AstNode* for_range = 0;
	
	AstNode* closest_type = GetClosestType();
	
	AstNode* d = AddDuplicate(n);
	if (!d) return 0;
	
	PushScope(*d, true);
	
	for (const AstNode& s : n.sub) {
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
				return 0;
		}
		else TODO
	}
	
	if (!block) {
		AddError(n.loc, "no statement-block in meta-for loop");
		return 0;
	}
	
	AstNode* dup_block = 0;
	
	if (for_range) {
		TODO
	}
	else {
		if (!for_cond || !for_post) {
			AddError(n.loc, "internal error: no for-cond or for-post statement");
			return 0;
		}
		
		
		int dbg_i = 0;
		while (1) {
			AstNode* cond_val = Evaluate(*for_cond);
			if (!cond_val)
				return 0;
			
			bool b = cond_val->obj.ToBool();
			if (!b)
				break;
			
			CHECK_SPATH_BEGIN
			dup_block = AddDuplicate(*block);
			if (!dup_block) return 0;
			PushScope(*dup_block);
			dup_block->i64 = 1; // skip indent
			
			for (const AstNode& s : block->sub) {
				if (!Visit(s))
					return 0;
				if (IsRvalReturn(s.src))
					PopScope();
			}
			
			PopScope(); // dup_block
			CHECK_SPATH_END
			
			AstNode* post_val = Evaluate(*for_post);
			if (!post_val)
				return 0;
			
			dbg_i++;
		}
	}
	
	PopScope(); // d
	
	SetMetaBlockType(*d, 0, closest_type);
	
	return builtin_void;
}

AstNode* AstRunner::VisitMetaIf(const AstNode& n) {
	ASSERT(n.src == SEMT_STATEMENT && n.stmt == STMT_META_IF);
	
	AstNode* d = AddDuplicate(n); // these can't be merge becaues of re-use
	d->src = SEMT_RVAL;
	if (!d)
		return 0;
	
	const AstNode* cond = n.Find(SEMT_EXPR);
	if (!cond) {
		AddError(n.loc, "internal error: expression not found");
		return 0;
	}
	
	AstNode* closest_type = GetClosestType();
	AstNode& owner_block = GetBlock();
	const AstNode* block = n.Find(SEMT_STATEMENT_BLOCK);
	if (!block) {
		AddError(n.loc, "internal error: block not found");
		return 0;
	}
	
	AstNode* else_ = n.ctx_next;
	ASSERT(!else_ || (else_->src == SEMT_STATEMENT && else_->stmt == STMT_META_ELSE));
	
	AstNode* cond_val = Evaluate(*cond);
	if (!cond_val)
		return 0;
	
	d->type = closest_type;
	PushScope(*d, true);
	
	AstNode* dup_block;
	bool b = cond_val->obj.ToBool();
	if (b) {
		block->locked = true;
		
		dup_block = AddDuplicate(*block);
		if (!dup_block) return 0;
		dup_block->type = closest_type;
		PushScope(*dup_block, true);
		if (!VisitStatementBlock(*block, false))
			return 0;
		PopScope();
	}
	else if (else_) {
		block = else_->Find(SEMT_STATEMENT_BLOCK);
		if (!block) {
			AddError(else_->loc, "internal error: block not found");
			return 0;
		}
		
		block->locked = true;
		
		dup_block = AddDuplicate(*block);
		if (!dup_block) return 0;
		dup_block->type = closest_type;
		PushScope(*dup_block, true);
		if (!VisitStatementBlock(*block, false))
			return 0;
		PopScope();
	}
	
	PopScope();
	
	SetMetaBlockType(*d, dup_block, closest_type);
	
	return d;
}

void AstRunner::SetMetaBlockType(AstNode& d, AstNode* dup_block, AstNode* closest_type) {
	if (dup_block)
		dup_block->i64 = 1; // skip indent
	
	if (!closest_type) {
		d.src = SEMT_STATEMENT_BLOCK;
		d.i64 = 1; // skip indent
	}
	else if (closest_type == this->meta_builtin_expr)
		d.rval = dup_block->rval;
	else if (closest_type->IsPartially(SEMT_META_BUILTIN))
		; // pass
	else
		TODO
}

AstNode* AstRunner::MergeStatement(const AstNode& n) {
	AstNode& owner = GetNonLockedOwner();
	AstNode* d = 0;
	AstNode* sd = 0;
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
		ASSERT(n.rval || n.sub.GetCount() == 1);
		if (n.rval) {
			const AstNode& s = *n.rval;
			sd = Visit(s);
			if (!sd)
				return 0;
			d->rval = sd;
			if (IsRvalReturn(s.src))
				PopScope(); // expr rval
		}
		else {
			const AstNode& s = n.sub[0];
			sd = Visit(s);
			if (!sd)
				return 0;
			d->rval = sd;
			if (IsRvalReturn(s.src))
				PopScope(); // expr rval
		}
		PopScope();
		return d;
		
	case STMT_META_FOR:
	case STMT_META_IF:
	case STMT_META_ELSE:
		break;
	
	case STMT_ATOM_CONNECTOR:
	case STMT_IF:
		d = AddDuplicate(n);
		d->CopyFrom(this, n);
		if (n.sub.GetCount()) {
			PushScope(*d);
			for (const AstNode& s : n.sub) {
				if (!Visit(s))
					return 0;
				if (IsRvalReturn(s.src))
					PopScope();
			}
			PopScope();
		}
		return d;
	
	case STMT_CTOR:
		if (n.rval && n.rval->IsPartially(SEMT_META_ANY))
			return VisitMetaCtor(*n.rval);
		d = AddDuplicate(n);
		if (!d)
			return 0;
		PushScope(*d);
		ASSERT(n.sub.GetCount());
		ASSERT(n.rval);
		if (n.rval) {
			AstNode& s = *n.rval;
			d->rval = Visit(s);
			if (!d->rval)
				return 0;
			if (IsRvalReturn(s.src))
				PopScope(); // expr rval
		}
		PopScope();
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

bool AstRunner::IsMergeable(const AstNode& prev, const AstNode& to_merge) const {
	if (to_merge.src != prev.src)
		return false;
	
	return true;
}

AstNode* AstRunner::Visit(const AstNode& n) {
	AstNode* d = 0;
	AstNode* sd = 0;
	AstNode* ad = 0;
	Object* o;
	int pop_count;
	CHECK_SPATH_INIT
	
	switch (n.src) {
	case SEMT_ROOT:
		ASSERT(spath.IsEmpty());
		d = &GetRoot();
		d->src = SEMT_ROOT;
		PushScope(*d);
		for (const AstNode& s : n.sub) {
			if (s.src == SEMT_RVAL)
				continue;
			sd = Visit(s);
			if (!sd)
				return 0;
			if (IsRvalReturn(s.src))
				PopScope();
		}
		PopScope();
		break;
		
	case SEMT_LOOP:
	case SEMT_CHAIN:
	case SEMT_ATOM:
	case SEMT_MACHINE:
	case SEMT_LOOP_DECL:
	case SEMT_WORLD:
	case SEMT_SYSTEM:
	case SEMT_POOL:
	case SEMT_DRIVER:
	case SEMT_STATE:
		d = Merge(n);
		PushScope(*d);
		for (const AstNode& s : n.sub) {
			sd = Visit(s);
			if (!sd)
				return 0;
			if (IsRvalReturn(s.src))
				PopScope();
		}
		PopScope();
		d->rval = builtin_void;
		break;
		
	case SEMT_ENTITY:
	case SEMT_COMPONENT:
		d = AddDuplicate(n);
		PushScope(*d);
		for (const AstNode& s : n.sub) {
			sd = Visit(s);
			if (!sd)
				return 0;
			if (IsRvalReturn(s.src))
				PopScope();
		}
		PopScope();
		d->rval = builtin_void;
		break;
		
	case SEMT_BUILTIN:
	case SEMT_FUNCTION_BUILTIN:
		d = Merge(n);
		break;
	
	case SEMT_META_BUILTIN:
		d = builtin_void;
		break;
	
	case SEMT_META_VARIABLE:
		d = DeclareMetaVariable(n);
		break;
		
	case SEMT_META_CTOR:
		d = VisitMetaCtor(n);
		break;
		
	case SEMT_META_FUNCTION_STATIC:
		d = VisitMetaStaticFunction(n);
		break;
		
	case SEMT_UNRESOLVED:
	case SEMT_META_PARAMETER:
		d = AddDuplicate(n);
		if (!d)
			return 0;
		if (!n.sub.IsEmpty()) {
			PushScope(*d);
			for (const AstNode& s : n.sub) {
				if (s.src == SEMT_RVAL)
					continue;
				sd = Visit(s);
				if (!sd)
					return 0;
				if (IsRvalReturn(s.src))
					PopScope();
			}
			PopScope();
		}
		break;
		
	
	case SEMT_FUNCTION_STATIC:
	case SEMT_VARIABLE:
		d = Merge(n);
		if (!d)
			return 0;
		if (!n.sub.IsEmpty()) {
			PushScope(*d);
			for (const AstNode& s : n.sub) {
				if (s.src == SEMT_RVAL)
					continue;
				sd = Visit(s);
				if (!sd)
					return 0;
				if (IsRvalReturn(s.src))
					PopScope();
			}
			PopScope();
		}
		break;
		
	case SEMT_STATEMENT_BLOCK:
		d = Merge(n);
		if (!d)
			return 0;
		if (!n.sub.IsEmpty()) {
			PushScope(*d);
			if (!VisitStatementBlock(n, false))
				return 0;
			PopScope();
		}
		break;
		
	case SEMT_IDPART:
		if (n.name.IsEmpty()) {
			AddError(n.loc, "internal error: no name");
			return 0;
		}
		d = GetTopNode().Find(n.name);
		if (!d)
			d = AddDuplicate(n);
		PushScope(*d);
		for (const AstNode& s : n.sub) {
			if (!Visit(s))
				return 0;
		}
		PopScope();
		d->rval = builtin_void;
		break;
		
	case SEMT_EXPR:
		d = AddDuplicate(n);
		if (!d)
			return 0;
		CHECK_SPATH_BEGIN_1
		pop_count = 0;
		for(int i = 0; i < n.i64; i++) {
			ASSERT(n.arg[i]);
			AstNode& a = *n.arg[i];
			AstNode* ad = Visit(a);
			if (!ad)
				return 0;
			if (IsRvalReturn(a.src))
				pop_count++;
			d->arg[i] = ad;
		}
		for(int i = 0; i < pop_count; i++) {
			PopScope();
		}
		PushScope(*d);
		CHECK_SPATH_END
		
		if (d->op == OP_CALL && d->arg[0] && d->arg[0]->src == SEMT_META_RVAL && d->arg[1]) {
			if (!VisitMetaCall(*d, *d->arg[0], *d->arg[1]))
				return 0;
		}
		else if (d->arg[0] && d->arg[0]->src == SEMT_META_RVAL)
			TODO
		break;
		
	case SEMT_ARGUMENT_LIST:
		d = Merge(n);
		if (!d)
			return 0;
		if (!n.sub.IsEmpty()) {
			PushScope(*d);
			
			CHECK_SPATH_BEGIN
			
			for (const AstNode& s : n.sub) {
				if (s.src == SEMT_ARGUMENT || s.IsPartially(SEMT_META_ANY)) {
					sd = Visit(s);
					if (!sd)
						return 0;
					if (IsRvalReturn(s.src))
						PopScope();
					
					CHECK_SPATH_END
				}
			}
			
			CHECK_SPATH_END
			
			PopScope();
		}
		PushScopeRVal(*d);
		break;
		
	case SEMT_ARGUMENT:
		d = AddDuplicate(n);
		if (!d)
			return 0;
		ASSERT(n.rval);
		if (n.rval) {
			PushScope(*d);
			d->rval = Visit(*n.rval);
			if (!d->rval)
				return 0;
			if (IsRvalReturn(n.rval->src))
				PopScope();
			PopScope();
		}
		break;
		
	case SEMT_CTOR:
		if (n.type && n.type->IsPartially(SEMT_META_TYPE))
			return VisitMetaCtor(n);
		d = AddDuplicate(n);
		if (!d)
			return 0;
		ASSERT(n.arg[0]);
		if (n.arg[0]) {
			PushScope(*d);
			ad = Visit(*n.arg[0]);
			if (!ad)
				return 0;
			d->arg[0] = ad;
			if (IsRvalReturn(n.arg[0]->src))
				PopScope();
			PopScope();
		}
		d->rval = FindStackWithPrevDeep(n.rval);
		PushScopeRVal(*d);
		ASSERT(d->arg[0]);
		ASSERT(d->rval);
		break;
		
	case SEMT_STATEMENT:
		switch (n.stmt) {
			case STMT_META_FOR: return VisitMetaFor(n);
			case STMT_META_IF: return VisitMetaIf(n);
			case STMT_META_ELSE: ASSERT_(0, "never call"); break;
			default: break;
		}
		d = MergeStatement(n);
		if (!d)
			return 0;
		break;
	
	case SEMT_RVAL:
		ASSERT(n.rval);
		if (n.rval->IsPartially(SEMT_META_FIELD)) {
			return VisitMetaRVal(n);
		}
		else {
			d = AddDuplicate(n);
			if (!d)
				return 0;
			if (n.rval) {
				AstNode* rval = n.rval;
				while (rval && (rval->src == SEMT_RVAL || rval->src == SEMT_META_CTOR))
					rval = rval->rval;
				if (!rval) {
					AddError(n.loc, "internal error: invalid rval");
					return 0;
				}
				
				if (rval->src == SEMT_META_RESOLVE) {
					d->rval = VisitMetaResolve(*rval);
				}
				else {
					d->rval = FindStackWithPrevDeep(rval);
				}
				ASSERT(d->rval); // todo crash here might mean succesfull merge (see same named variables)
				if (!d->rval) {
					AddError(n.loc, "internal error: incomplete rval");
					return 0;
				}
				
				if (d->rval->src != SEMT_IDPART && d->rval->IsPartially(SEMT_META_ANY))
					d->src = SEMT_META_RVAL;
			}
			else TODO
			PushScopeRVal(*d);
			
		}
		break;
		
	case SEMT_CONSTANT:
		d = AddDuplicate(n);
		if (!d)
			return 0;
		PushScopeRVal(*d);
		break;
	
	case SEMT_PARAMETER:
		d = &GetTopNode().Add(n.loc, n.name);
		d->CopyFrom(this, n);
		d->src = SEMT_OBJECT;
		break;
	
	case SEMT_RESOLVE:
		return VisitResolve(n);
	
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
	
	ASSERT(d);
	return d;
}

AstNode* AstRunner::AddDuplicate(const AstNode& n) {
	AstNode& owner = GetNonLockedOwner();
	AstNode& d = owner.Add(n.loc);
	d.CopyFrom(this, n);
	return &d;
}

AstNode* AstRunner::VisitMetaRVal(const AstNode& n) {
	if (!n.rval || !n.rval->IsPartially(SEMT_META_FIELD)) {ASSERT(0); return 0;}
	
	const AstNode& ref = *n.rval;
	
	if (ref.src == SEMT_META_VARIABLE || ref.src == SEMT_META_PARAMETER) {
		ASSERT(ref.name.GetCount());
		AstNode* o = FindStackWithPrev(&ref);
		ASSERT(o);
		while (o && o->src == SEMT_RVAL)
			o = o->rval;
		if (!o) {
			AddError(n.loc, "internal error: no object");
			return 0;
		}
		AstNode& owner = GetNonLockedOwner();
		AstNode& d = owner.Add(n.loc);
		
		if (o->src == SEMT_CONSTANT) {
			d.CopyFrom(this, *o);
		}
		else if (o->src == SEMT_OBJECT) {
			if (o->obj.IsVoid()) {
				AddError(o->loc, "meta-object is not initalized yet");
				return 0;
			}
			d.CopyFromObject(n.loc, o->obj);
		}
		else
			TODO;
		
		PushScopeRVal(d);
		
		return &d;
	}
	else TODO;
	
	return 0;
}

AstNode* AstRunner::VisitMetaCtor(const AstNode& n) {
	ASSERT(n.src == SEMT_META_CTOR);
	ASSERT(n.type && n.type->IsPartially(SEMT_META_TYPE));
	ASSERT(n.rval);
	
	AstNode& var = *n.rval;
	const AstNode* args = n.Find(SEMT_ARGUMENT_LIST);
	if (!args) {
		TODO
	}
	
	ASSERT(var.name.GetCount());
	
	AstNode* o = FindStackObject(var.name);
	
	{
		// Kinda hack: to allow finding node with ".prev == &n"
		AstNode* d = Merge(n);
		d->src = SEMT_RVAL;
		d->rval = o;
		d->name = var.name;
		ASSERT(o);
	}
	
	int arg_count = 0;
	const AstNode* arg = 0;
	for (const AstNode& s : args->sub) {
		if (s.src == SEMT_ARGUMENT) {
			arg = &s;
			arg_count++;
		}
	}
	
	if (arg_count == 1) {
		ASSERT(arg->rval);
		AstNode& argvar = *arg->rval;
		
		if (argvar.src == SEMT_CONSTANT) {
			argvar.CopyToObject(o->obj);
		}
		else if (argvar.src == SEMT_EXPR) {
			AstNode* argval = Evaluate(argvar);
			if (!argval)
				return 0;
			
			o->obj = argval->obj;
		}
		else TODO
	}
	else {
		TODO
	}
	
	return o;
}

AstNode* AstRunner::VisitMetaStaticFunction(const AstNode& n) {
	ASSERT(n.src == SEMT_META_FUNCTION_STATIC);
	
	AstNode* d = Merge(n);
	if (!d)
		return 0;
	
	return d;
}

AstNode* AstRunner::VisitResolve(const AstNode& n) {
	ASSERT(n.src == SEMT_RESOLVE);
	ASSERT(n.filter != SEMT_NULL);
	ASSERT(!n.id.IsEmpty());
	
	AstNode* decl = FindDeclaration(n.id, n.filter);
	if (!decl) {
		AddError(n.loc, "could not find declaration '" + n.id.ToString() + "'");
		return 0;
	}
	
	if (decl->src == SEMT_META_FUNCTION_STATIC) {
		AstNode& rval = GetTopNode().Add(n.loc);
		rval.CopyFrom(this, n);
		rval.src = SEMT_META_RVAL;
		rval.rval = decl;
		PushScopeRVal(rval);
		return &rval;
	}
	else TODO
}

bool AstRunner::VisitStatementBlock(const AstNode& n, bool req_rval) {
	AstNode& block = GetBlock();
	AstNode& owner = GetNonLockedOwner();
	ASSERT(block.src == SEMT_STATEMENT_BLOCK);
	ASSERT(&n != &block);
	int dbg_count = 0;
	
	if (!n.sub.IsEmpty()) {
		int dbg_i = 0;
		for (const AstNode& s : n.sub) {
			if (s.src == SEMT_STATEMENT && (s.stmt == STMT_ELSE || s.stmt == STMT_META_ELSE))
				continue;
			
			int prev_count = block.sub.GetCount();
			CHECK_SPATH_BEGIN
			
			AstNode* sd = Visit(s);
			if (!sd)
				return false;
			
			if (sd && sd->rval) {
				AstNode& r = *sd->rval;
				if (block.type == meta_builtin_expr) {
					if (IsRvalReturn(r.src)) {
						owner.rval = &r;
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
			
			dbg_i++;
		}
	}
	
	if (req_rval && !owner.rval) {
		AddError(n.loc, "internal error: no rval");
		return false;
	}
	return true;
}

AstNode* AstRunner::VisitReturn(const AstNode& n) {
	AstNode& block = GetBlock();
	ASSERT(spath.Top().n == &block);
	int c = block.sub.GetCount();
	
	AstNode* d = AddDuplicate(n);
	if (n.sub.GetCount()) {
		CHECK_SPATH_BEGIN
		
		PushScope(*d);
		if (n.rval) {
			d->rval = Visit(*n.rval);
			if (!d->rval)
				return 0;
			if (IsRvalReturn(n.rval->src))
				PopScope();
		}
		PopScope();
		
		CHECK_SPATH_END
	}
	
	ASSERT(block.sub.GetCount() > c);
	block.rval = d->rval;
	ASSERT(block.rval != &block);
	return d;
}

AstNode* AstRunner::VisitMetaResolve(const AstNode& n) {
	ASSERT(n.src == SEMT_META_RESOLVE);
	
	if (n.id.part_count == 0) {
		AddError(n.loc, "internal error: empty id");
		return 0;
	}
	
	Vector<String> parts;
	int part_i = 0;
	for (const Token* tk = n.id.begin ; tk != n.id.end; tk++) {
		if (tk->type == TK_ID) {
			if (n.id.is_meta[part_i]) {
				AstNode* a = FindStackName(tk->str_value, (SemanticType)(n.filter | SEMT_RVAL));
				while (a && a->src == SEMT_RVAL)
					a = a->rval;
				if (!a) {
					AddError(n.loc, "meta-field '" + tk->str_value + "' not found");
					return 0;
				}
				if (a->src == SEMT_OBJECT) {
					String s = a->obj.ToString();
					if (s.IsEmpty()) {
						AddError(n.loc, "meta-object '" + tk->str_value + "' gave empty string");
						return 0;
					}
					parts.Add(s);
				}
				else
					TODO
			}
			else {
				parts.Add(tk->str_value);
			}
			part_i++;
		}
	}
	
	
	AstNode* rval = FindDeclaration(parts);
	
	AstNode* d = AddDuplicate(n);
	d->src = SEMT_RVAL;
	d->rval = rval;
	
	return d;
}

bool AstRunner::VisitMetaCall(AstNode& d, AstNode& rval, AstNode& args) {
	if (rval.src == SEMT_META_RVAL && args.src == SEMT_ARGUMENT_LIST) {
		const AstNode& fn = *rval.rval->prev;
		AstNode& ret_type = *fn.type;
		ASSERT(fn.src == SEMT_META_FUNCTION_STATIC);
		fn.locked = true;
		
		bool req_rval = false;
		if (fn.type == meta_builtin_expr)
			req_rval = true;
		
		AstNode* call = AddDuplicate(fn);
		call->src = SEMT_STATEMENT_BLOCK;
		call->i64 = 1; // skip indent
		call->prev = 0; // to prevent wrong match
		PushScope(*call, true);
		
		Object o;
		ObjectMap& map = o.CreateMap();
		
		PushScope(d, true);
		d.type = FindStackWithPrev(fn.type);
		if (!d.type) {
			AddError(fn.type->loc, "internal error: type not found in new scope");
			return false;
		}
		
		Vector<AstNode*> arg_ptrs;
		Vector<const AstNode*> param_ptrs;
		
		for (AstNode& arg : args.sub) {
			if (arg.src != SEMT_ARGUMENT) continue;
			arg_ptrs.Add(&arg);
		}
		for (const AstNode& param : fn.sub) {
			if (param.src != SEMT_META_PARAMETER) continue;
			param_ptrs.Add(&param);
		}
		if (arg_ptrs.GetCount() != param_ptrs.GetCount()) {
			AddError(args.loc, "got '" + IntStr(arg_ptrs.GetCount()) + "' arguments, but expected '" + IntStr(param_ptrs.GetCount()) + "'");
			return false;
		}
		
		for(int i = 0; i < arg_ptrs.GetCount(); i++) {
			AstNode& arg = *arg_ptrs[i];
			const AstNode& param = *param_ptrs[i];
			
			ASSERT(param.name.GetCount());
			AstNode& ao = call->Add(param.loc, param.name);
			ao.CopyFrom(this, param);
			ao.src = SEMT_RVAL;
			
			if (!arg.rval) {
				AddError(arg.loc, "internal error: expected argument expression");
				return false;
			}
			AstNode& aexpr = *arg.rval;
			
			AstNode* aexpr_val = Evaluate(aexpr);
			if (!aexpr_val)
				return false;
			
			ao.rval = aexpr_val;
			ASSERT(ao.rval);
		}
		
		const AstNode* block = fn.Find(SEMT_STATEMENT_BLOCK);
		if (!block) {
			AddError(fn.loc, "internal error: function has no statement block");
			return false;
		}
		
		AstNode* dup_block = AddDuplicate(*block);
		
		block->locked = true;
		dup_block->type = d.type;
		PushScope(*dup_block, true);
		
		if (!VisitStatementBlock(*block, req_rval))
			return false;
		
		PopScope(); // block
		PopScope(); // ret
		PopScope(); // call
		
		// Override meta-node type and link function return value
		if (spath.Top().n != &d) {
			AddError(d.loc, "internal error: stack did not unwind properly");
			return false;
		}
		
		SemanticType filter = SEMT_NULL;
		if (d.type) {
			if (d.type == meta_builtin_expr) {
				d.src = SEMT_RVAL;
				d.rval = dup_block->rval;
				ASSERT(d.rval);
				
			}
			else if (d.type == meta_builtin_loopstmt) {
				d.src = SEMT_SYMBOLIC_LINK;
				d.rval = dup_block;
			}
			else if (!req_rval) {
				d.rval = builtin_void;
			}
			else TODO
		}
		else TODO;
	}
	else TODO
	
	return true;
}

AstNode* AstRunner::DeclareMetaVariable(const AstNode& n) {
	if (n.src == SEMT_META_VARIABLE) {
		ASSERT(n.name.GetCount());
		AstNode& block = GetBlock();
		if (block.Find(n.name, SEMT_OBJECT)) {
			AddError(n.loc, "meta-variable '" + n.name + "' have already been declared");
			return 0;
		}
		
		AstNode& d = block.Add(n.loc, n.name);
		d.CopyFrom(this, n);
		d.src = SEMT_OBJECT;
		return &d;
	}
	else TODO;
}

AstNode* AstRunner::Evaluate(const AstNode& n) {
	
	if (n.src == SEMT_STATEMENT) {
		if (n.stmt == STMT_EXPR ||
			n.stmt == STMT_META_FOR_COND ||
			n.stmt == STMT_META_FOR_POST) {
			for (int i = n.sub.GetCount()-1; i >= 0; i--) {
				const AstNode& e = n.sub[i];
				if (e.src == SEMT_EXPR) {
					return Evaluate(e);
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
			AstNode* a = n.arg[0];
			while (a && a->src == SEMT_RVAL) {
				a = a->rval;
			}
			if (a) {
				AstNode* o = FindStackWithPrev(a); // from previous phase to AstRunner phase
				if (o && o->src == SEMT_OBJECT) {
					AstNode* r = &GetTopNode().Add(n.loc);
					r->CopyFrom(this, n);
					r->src = SEMT_CONSTANT;
					r->CopyFromObject(n.loc, o->obj);
					
					o->obj = o->obj.ToInt() + (int64)(n.op == OP_POSTINC ? 1 : -1);
					
					return r;
				}
			}
		}
		
		AstNode* d = AddDuplicate(n);
		if (!d) return 0;
		d->src = SEMT_OBJECT;
		Object& o = d->obj;
		
		Object a[AstNode::ARG_COUNT];
		
		ASSERT(n.i64 > 0);
		for(int i = 0; i < n.i64; i++) {
			if (!n.arg[i]) {
				AddError(n.loc, "expression failed");
				return 0;
			}
			AstNode* r = Evaluate(*n.arg[i]);
			if (!r)
				return 0;
			d->arg[i] = r;
			
			if (r->src == SEMT_CONSTANT)
				r->CopyToObject(a[i]);
			else if (r->src == SEMT_OBJECT)
				a[i] = r->obj;
			else
				TODO
		}
		
		switch (n.op) {
			case OP_POSTINC:
			case OP_POSTDEC:
			case OP_POSITIVE:	o = a[0]; break;
			case OP_NOT:		o = !a[0]; break;
			case OP_NEGATIVE:	o = -a[0]; break;
			case OP_GREATER:	o = a[0] > a[1]; break;
			case OP_LESS:		o = a[0] < a[1]; break;
			case OP_ADD:		o = a[0] + a[1]; break;
			case OP_SUB:		o = a[0] - a[1]; break;
			case OP_MUL:		o = a[0] * a[1]; break;
			case OP_DIV:		o = a[0] / a[1]; break;
			case OP_LSH:		o = a[0] << a[1]; break;
			case OP_RSH:		o = a[0] >> a[1]; break;
			case OP_EQ:			o = a[0] == a[1]; break;
			case OP_INEQ:		o = a[0] != a[1]; break;
			case OP_AND:		o = a[0] && a[1]; break;
			case OP_OR:			o = a[0] || a[1]; break;
			case OP_GREQ:		o = a[0] >= a[1]; break;
			case OP_LSEQ:		o = a[0] <= a[1]; break;
			
			case OP_MOD:
			case OP_NULL:
			case OP_INC:
			case OP_DEC:
			case OP_NEGATE:
			case OP_BWAND:
			case OP_BWXOR:
			case OP_BWOR:
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
		
		return d;
	}
	else if (n.src == SEMT_CONSTANT) {
		AstNode* d = FindStackWithPrev(&n);
		if (d)
			return d;
		d = AddDuplicate(n);
		d->CopyFrom(this, n);
		return d;
	}
	else if (n.src == SEMT_RVAL) {
		ASSERT(n.rval);
		AstNode* rval = FindStackWithPrev(n.rval);
		while (rval && rval->src == SEMT_RVAL)
			rval = rval->rval;
		if (!rval) {
			AddError(n.loc, "internal error: incomplete rval");
			return 0;
		}
		else if (rval->src == SEMT_OBJECT) {
			return rval;
		}
		else if (rval->src == SEMT_CONSTANT) {
			return rval;
		}
		else TODO
	}
	else TODO
	
	return 0;
}


NAMESPACE_TOPSIDE_END
