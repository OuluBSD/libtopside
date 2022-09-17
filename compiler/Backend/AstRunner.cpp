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

AstNode& AstRunner::AddDuplicate(AstNode& n) {
	AstNode& owner = *spath.Top().n;
	
	AstNode& d = owner.Add(n.loc);
	d.CopyFrom(n);
	Bind(n, d);
	
	return d;
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
		break;
	
	case SEMT_BUILTIN:
	case SEMT_FUNCTION_BUILTIN:
		AddDuplicate(n);
		break;
	
	case SEMT_META_BUILTIN:
		break;
	
	case SEMT_META_VARIABLE:
		DeclareMetaVariable(n);
		break;
	
	case SEMT_FUNCTION_STATIC:
		s = &AddDuplicate(n);
		ASSERT(n.name.GetCount());
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
		break;
	
	case SEMT_IDPART:
	case SEMT_STATEMENT_BLOCK:
	case SEMT_PARAMETER:
	case SEMT_STATEMENT:
	case SEMT_EXPR:
	case SEMT_CONSTANT:
	case SEMT_VARIABLE:
	case SEMT_ARGUMENT:
	case SEMT_RESOLVE:
	case SEMT_RVAL:
	case SEMT_NULL:
	case SEMT_NAMESPACE:
	case SEMT_TYPEDEF:
	case SEMT_CLASS_DECL:
	case SEMT_CLASS:
	case SEMT_CLASS_TEMPLATE:
	case SEMT_FUNCTION_METHOD:
	case SEMT_ARGUMENT_LIST:
	case SEMT_ARRAYSIZE:
	default:
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
