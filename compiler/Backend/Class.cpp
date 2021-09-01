#include "Backend.h"


NAMESPACE_TOPSIDE_BEGIN

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

String Class::GetTreeString(int indent) const {
	String s;
	s.Cat('\t', indent);
	s << ToString() << "\n";
	for (const Class& o : classes.GetValues()) {
		s << o.GetTreeString(indent+1);
	}
	for (const Field& o : fields.GetValues()) {
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
		s << "class " << name << ";\n\n";
	}
	
	if (!IsContained(args))
		return s;
	
	if (args.have_header) {
		s.Cat('\t', args.indent);
		s << "class " << name << " ";
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
		
		for (const Class& o : classes.GetValues()) {
			if (o.access != acc) {
				s.Cat('\t', args.indent);
				GetAccessString(o.access);
				acc = o.access;
			}
			s << o.GetCodeString(subargs);
		}
		for (const Field& o : fields.GetValues()) {
			if (o.access != acc) {
				s.Cat('\t', args.indent);
				GetAccessString(o.access);
				acc = o.access;
			}
			s << o.GetCodeString(subargs);
		}
		
		s.Cat('\t', args.indent);
		s.Cat('\n');
		s.Cat('\t', args.indent);
		s << "};\n\n";
	}
	else if (args.have_impl) {
		
		
		
	}
	
	return s;
}

NAMESPACE_TOPSIDE_END
