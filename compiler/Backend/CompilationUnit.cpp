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

bool CompilationUnit::Activate(TypeExpr& te) {
	String id = te.ToString();
	int i = gtypes.Find(id);
	if (i >= 0) {
		te.global_ptr = &gtypes[i];
		return true;
	}
	
	te.global_ptr = &gtypes.Add(id, te);
	return true;
}

String CompilationUnit::GetTreeString(int indent) const {
	String s;
	s.Cat('\t', indent);
	s << ToString() << "\n";
	for (const Namespace& ns : namespaces.GetValues()) {
		s << ns.GetTreeString(indent+1);
	}
	return s;
}

String CompilationUnit::ToString() const {
	String s;
	s << "CompilationUnit";
	return s;
}

String CompilationUnit::GetCodeString(const CodeArgs& args) const {
	String s;
	
	for (const Namespace& ns : namespaces.GetValues()) {
		s << ns.GetCodeString(args);
	}
	
	return s;
}

NAMESPACE_TOPSIDE_END
