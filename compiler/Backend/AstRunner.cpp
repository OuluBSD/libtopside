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
		PushScope(*d);
		for (AstNode& s : n.sub) {
			if (!Visit(s))
				return 0;
		}
		PopScope();
		return d;
		
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
	case STMT_EXPR:
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
		ASSERT(spath.IsEmpty());
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
		s = Merge(n);
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
		break;
		
	case SEMT_STATEMENT:
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
			if (!AddDuplicate(n))
				return false;
		}
		break;
	
	case SEMT_ARGUMENT_LIST:
	case SEMT_IDPART:
	case SEMT_PARAMETER:
	case SEMT_EXPR:
	case SEMT_CONSTANT:
	case SEMT_VARIABLE:
	case SEMT_ARGUMENT:
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


NAMESPACE_TOPSIDE_END
