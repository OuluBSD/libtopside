#include "Backend.h"

NAMESPACE_TOPSIDE_BEGIN


MetaStatement::MetaStatement() {
	MetaExpression& me = mexpr.Create();
	me.SetParent(this);
	
	
}

String MetaStatement::GetTreeString(int indent) const {
	String s;
	s.Cat('\t', indent);
	s << ToString() << "\n";
	/*for (const Class& o : classes.GetValues()) {
		s << o.GetTreeString(indent+1);
	}
	for (const Field& o : fields.GetValues()) {
		s << o.GetTreeString(indent+1);
	}*/
	return s;
}

String MetaStatement::ToString() const {
	String s;
	s << "MetaStatement";
	return s;
}

String MetaStatement::GetCodeString(const CodeArgs& args) const {
	if (GetHint(HINT_HIDDEN) == "true")
		return String();
	
	String s;
	s.Cat('\t', args.indent);
	
	if (mexpr.IsEmpty()) {
		s << "// <empty MetaStatement>\n";
	}
	else {
		s << mexpr->GetCodeString(args) << ";\n";
	}
	
	return s;
}





MetaExpression&	MetaExpression::AddSub() {
	MetaExpression& me = mexprs.Add();
	me.SetParent(this);
	return me;
}

String MetaExpression::GetTreeString(int indent) const {
	String s;
	s.Cat('\t', indent);
	s << ToString() << "\n";
	/*for (const Class& o : classes.GetValues()) {
		s << o.GetTreeString(indent+1);
	}
	for (const Field& o : fields.GetValues()) {
		s << o.GetTreeString(indent+1);
	}*/
	return s;
}

String MetaExpression::ToString() const {
	String s;
	s << "MetaExpression";
	
	if (type == CALL)
		s << "(Call)";
	else if (type == STRING)
		s << "(String: " << str << ")";
	
	return s;
}

String MetaExpression::GetCodeString(const CodeArgs& args) const {
	if (GetHint(HINT_HIDDEN) == "true")
		return String();
	
	String s;
	
	if (type == INVALID) {
		s << "/*<invalid MetaExpression>*/";
	}
	else if (type == CALL) {
		s << str << "(";
		int i = 0;
		for (MetaExpression& me : mexprs) {
			if (i++ > 0) s << ", ";
			s << me.GetCodeString(args);
		}
		s << ")";
	}
	else if (type == STRING) {
		if (str.IsEmpty())
			s << "/*<invalid empty string>*/";
		else
			s << str;
	}
	else {
		TODO
	}
	
	return s;
}


NAMESPACE_TOPSIDE_END
