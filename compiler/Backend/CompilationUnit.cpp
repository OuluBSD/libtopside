#include "Backend.h"


NAMESPACE_TOPSIDE_BEGIN

CompilationUnit::CompilationUnit() {
	
}

Namespace& CompilationUnit::GetAddNamespace(String name) {
	int i = namespaces.Find(name);
	if (i >= 0)
		return namespaces[i];
	Namespace& o = namespaces.Add(name);
	o.SetParent(this);
	o.name = name;
	return o;
}

NAMESPACE_TOPSIDE_END
