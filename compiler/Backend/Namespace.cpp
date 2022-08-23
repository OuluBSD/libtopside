#include "Backend.h"


NAMESPACE_TOPSIDE_BEGIN

Namespace::Namespace() {
	
}

Class& Namespace::GetAddClass(String name) {
	int i = classes.Find(name);
	if (i >= 0)
		return classes[i];
	Class& o = classes.Add(name);
	o.SetOwner(this);
	o.name = name;
	return o;
}

Class& Namespace::GetAddTemplateClass(String name) {
	int i = classes.Find(name);
	if (i >= 0)
		return classes[i];
	Class& o = classes.Add(name);
	o.SetOwner(this);
	o.is_template = true;
	o.name = name;
	return o;
}

Namespace& Namespace::GetAddNamespace(String name) {
	int i = namespaces.Find(name);
	if (i >= 0)
		return namespaces[i];
	Namespace& o = namespaces.Add(name);
	o.SetOwner(this);
	o.name = name;
	return o;
}

UsingStatement& Namespace::GetAddUsing(String name) {
	int i = using_stmts.Find(name);
	if (i >= 0)
		return using_stmts[i];
	UsingStatement& o = using_stmts.Add(name);
	o.SetOwner(this);
	o.name = name;
	return o;
}

MetaStatement& Namespace::GetAddMetaStatement(String name) {
	int i = mstmts.Find(name);
	if (i >= 0)
		return mstmts[i];
	MetaStatement& o = mstmts.Add(name);
	o.SetOwner(this);
	//o.name = name;
	return o;
	/*MetaStatement& ms = mstmts.Add();
	ms.SetOwner(this);
	return ms;*/
}

String Namespace::GetTreeString(int indent) const {
	String s;
	s.Cat('\t', indent);
	s << ToString() << "\n";
	for (const Namespace& o : namespaces.GetValues()) {
		s << o.GetTreeString(indent+1);
	}
	for (const Class& o : classes.GetValues()) {
		s << o.GetTreeString(indent+1);
	}
	for (const UsingStatement& o : using_stmts.GetValues()) {
		s << o.GetTreeString(indent+1);
	}
	for (const MetaStatement& o : mstmts.GetValues()) {
		s << o.GetTreeString(indent+1);
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
		String content;
		CodeArgs subargs = args;
		
		for (const Namespace& o : namespaces.GetValues()) {
			content << o.GetCodeString(subargs);
		}
		for (const Class& o : classes.GetValues()) {
			content << o.GetCodeString(subargs);
		}
		for (const UsingStatement& o : using_stmts.GetValues()) {
			content << o.GetCodeString(subargs);
		}
		for (const MetaStatement& o : mstmts.GetValues()) {
			content << o.GetCodeString(subargs);
		}
		
		if (!content.IsEmpty()) {
			s	<< "namespace " << name << " {\n\n"
				<< content
				<< "}\n\n";
		}
	}
	
	if (args.have_impl) {
		String content;
		CodeArgs subargs = args;
		
		for (const Namespace& o : namespaces.GetValues()) {
			content << o.GetCodeString(subargs);
		}
		for (const Class& o : classes.GetValues()) {
			content << o.GetCodeString(subargs);
		}
		for (const UsingStatement& o : using_stmts.GetValues()) {
			content << o.GetCodeString(subargs);
		}
		for (const MetaStatement& o : mstmts.GetValues()) {
			content << o.GetCodeString(subargs);
		}
		
		if (!content.IsEmpty()) {
			s	<< "namespace " << name << " {\n\n"
				<< content
				<< "}\n\n";
		}
	}
	
	return s;
}

NAMESPACE_TOPSIDE_END
