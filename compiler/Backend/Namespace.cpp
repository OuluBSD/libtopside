#include "Backend.h"


NAMESPACE_TOPSIDE_BEGIN

Namespace::Namespace() {
	
}

Class& Namespace::GetAddClass(String name) {
	int i = classes.Find(name);
	if (i >= 0)
		return classes[i];
	Class& o = classes.Add(name);
	o.SetParent(this);
	o.name = name;
	return o;
}

Class& Namespace::GetAddTemplateClass(String name) {
	int i = classes.Find(name);
	if (i >= 0)
		return classes[i];
	Class& o = classes.Add(name);
	o.SetParent(this);
	o.is_template = true;
	o.name = name;
	return o;
}

Namespace& Namespace::GetAddNamespace(String name) {
	int i = namespaces.Find(name);
	if (i >= 0)
		return namespaces[i];
	Namespace& o = namespaces.Add(name);
	o.SetParent(this);
	o.name = name;
	return o;
}

String Namespace::GetTreeString(int indent) const {
	String s;
	s.Cat('\t', indent);
	s << ToString() << "\n";
	for (const Namespace& ns : namespaces.GetValues()) {
		s << ns.GetTreeString(indent+1);
	}
	for (const Class& c : classes.GetValues()) {
		s << c.GetTreeString(indent+1);
	}
	return s;
}

String Namespace::ToString() const {
	String s;
	s << name << ": Namespace";
	return s;
}

String Namespace::GetCodeString(const CodeArgs& args) const {
	String s;
	
	if (args.have_header) {
		s << "namespace " << name << " {\n\n";
		
		CodeArgs subargs = args;
		
		for (const Namespace& ns : namespaces.GetValues()) {
			s << ns.GetCodeString(subargs);
		}
		for (const Class& c : classes.GetValues()) {
			s << c.GetCodeString(subargs);
		}
		
		s << "}\n\n";
	}
	
	if (args.have_impl) {
		
		
		
	}
	
	return s;
}

NAMESPACE_TOPSIDE_END
