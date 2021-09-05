#include "Backend.h"


NAMESPACE_TOPSIDE_BEGIN



ClassDecl::ClassDecl() {
	
}

String ClassDecl::GetTreeString(int indent) const {
	String s;
	s.Cat('\t', indent);
	if (!cls)
		s << "<empty ClassDecl>\n";
	else
		s << cls->GetName() << "\n";
	return s;
}

String ClassDecl::GetCodeString(const CodeArgs& args) const {
	String s;
	if (!cls)
		return s;
	s.Cat('\t', args.indent);
	s << cls->GetClassKey() << " ";
	s << cls->GetName() << ";\n";
	return s;
}

String ClassDecl::ToString() const {
	String s;
	if (!cls)
		s << "<empty ClassDecl>\n";
	else
		s << cls->GetName() << ": Class";
	return s;
}







ClassPathScope::ClassPathScope() {
	
}

ClassDecl& ClassPathScope::GetAddClassDecl(String key) {
	int i = cdecls.Find(key);
	if (i >= 0)
		return cdecls[i];
	
	ClassDecl& cd = cdecls.Add(key);
	cd.SetParent(this);
	cd.SetName(key);
	return cd;
}






String TemplateClass::GetTreeString(int indent) const {
	
	return "TemplateClass";
}

String TemplateClass::GetCodeString(const CodeArgs& args) const {
	
	return "TemplateClass";
}

String TemplateClass::ToString() const {
	
	return "TemplateClass";
}




Class::Class() {
	
}


bool Class::Inherit(Class& cls) {
	VectorFindAdd(inherited, &cls);
	return true;
}

Field& Class::GetAddField(String name) {
	int i = fields.Find(name);
	if (i >= 0) return fields[i];
	Field& f = fields.Add(name);
	f.name = name;
	f.SetParent(this);
	return f;
}

MStmt& Class::GetAddMetaStatement(String name) {
	int i = mstmts.Find(name);
	if (i >= 0) return mstmts[i];
	MStmt& f = mstmts.Add(name);
	//f.SetName(name);
	f.SetParent(this);
	return f;
	/*MStmt& ms = mstmts.Add();
	ms.SetParent(this);
	return ms;*/
}

FunctionIdScope& Class::GetAddFunctionIdScope(String name) {
	int i = funcids.Find(name);
	if (i >= 0) return funcids[i];
	FunctionIdScope& f = funcids.Add(name);
	f.SetName(name);
	f.SetParent(this);
	return f;
}

String Class::GetTreeString(int indent) const {
	String s;
	s.Cat('\t', indent);
	s << ToString() << "\n";
	for (const MetaStatement& o : mstmts.GetValues()) {
		s << o.GetTreeString(indent+1);
	}
	for (const Class& o : classes.GetValues()) {
		s << o.GetTreeString(indent+1);
	}
	for (const Field& o : fields.GetValues()) {
		s << o.GetTreeString(indent+1);
	}
	for (const FunctionIdScope& o : funcids.GetValues()) {
		s << o.GetTreeString(indent+1);
	}
	return s;
}

String Class::ToString() const {
	String s;
	s << name << ": Class";
	return s;
}

String Class::GetCodeString(const CodeArgs& args) const {
	if (GetHint(HINT_HIDDEN) == "true")
		return String();
	
	String s;
	
	if (IsFwdContained(args)) {
		s.Cat('\t', args.indent);
		s << GetClassKey() << " " << name << ";\n\n";
	}
	
	if (!IsContained(args))
		return s;
	
	if (args.have_header) {
		s.Cat('\t', args.indent);
		s << GetClassKey() << " " << name << " ";
		if (inherited.GetCount()) {
			s << ": ";
			for(int i = 0; i < inherited.GetCount(); i++) {
				if (i) s << ", ";
				Class* c = inherited[i];
				s << "public " << c->name;
			}
			s << " ";
		}
		s << "{\n";
		
		CodeAccess acc = ACC_PRIVATE;
		CodeArgs subargs = args;
		subargs.indent++;
		
		for (const MetaStatement& o : mstmts.GetValues()) {
			CHK_ACCESS
			s << o.GetCodeString(subargs);
		}
		for (const Class& o : classes.GetValues()) {
			CHK_ACCESS
			s << o.GetCodeString(subargs);
		}
		for (const Field& o : fields.GetValues()) {
			CHK_ACCESS
			s << o.GetCodeString(subargs);
		}
		for (const FunctionIdScope& o : funcids.GetValues()) {
			s << o.GetCodeString(subargs, acc);
		}
		
		s.Cat('\t', args.indent);
		s.Cat('\n');
		s.Cat('\t', args.indent);
		s << "};\n\n";
	}
	
	if (args.have_impl) {
		CodeArgs subargs = args;
		
		for (const MetaStatement& o : mstmts.GetValues()) {
			s << o.GetCodeString(subargs);
		}
		for (const Class& o : classes.GetValues()) {
			s << o.GetCodeString(subargs);
		}
		for (const Field& o : fields.GetValues()) {
			s << o.GetCodeString(subargs);
		}
		for (const FunctionIdScope& o : funcids.GetValues()) {
			s << o.GetCodeString(subargs);
		}
		
	}
	
	return s;
}

String Class::GetClassPath() const {
	Class* par = GetSubParent();
	String name = GetName();
	if (par)
		return par->GetClassPath() + "::" + name;
	else
		return name;
}


NAMESPACE_TOPSIDE_END
