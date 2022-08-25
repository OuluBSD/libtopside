#include "Backend.h"

#if 0

NAMESPACE_TOPSIDE_BEGIN


CompilationUnit::CompilationUnit() {
	root.SetOwner(this);
}

void CompilationUnit::InitDefault() {
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
}

void CompilationUnit::AddBuiltinType(String name) {
	ASSERT(root.classes.Find(name) < 0);
	Class& c = root.classes.Add(name);
	c.name = name;
}

Namespace& CompilationUnit::GetAddNamespace(String name) {
	/*int i = namespaces.Find(name);
	if (i >= 0)
		return namespaces[i];
	Namespace& o = namespaces.Add(name);
	o.SetOwner(this);
	o.name = name;
	return o;*/
	return root.GetAddNamespace(name);
}

bool CompilationUnit::Activate(TypeExpr& te) {
	String id = te.ToString();
	int i = gtypes.Find(id);
	if (i >= 0) {
		te.global_ptr = &gtypes[i];
		return true;
	}
	for (TypeExpr& sub : te.sub) {
		if (!Activate(sub))
			return false;
	}
	te.global_ptr = &gtypes.Add(id, te);
	return true;
}

String CompilationUnit::GetTreeString(int indent) const {
	/*String s;
	s.Cat('\t', indent);
	s << ToString() << "\n";
	for (const Namespace& ns : namespaces.GetValues()) {
		s << ns.GetTreeString(indent+1);
	}
	return s;*/
	return root.GetTreeString(indent);
}

String CompilationUnit::ToString() const {
	String s;
	s << "CompilationUnit";
	return s;
}

String CompilationUnit::GetCodeString(const CodeArgs& args) const {
	String s;
	
	/*for (const Namespace& ns : namespaces.GetValues()) {
		s << ns.GetCodeString(args);
	}*/
	s << root.GetCodeString(args);
	
	return s;
}

Class* CompilationUnit::FindClass(const PathIdentifier& id, int i) {
	return root.FindClass(id, i);
}


NAMESPACE_TOPSIDE_END

#endif
