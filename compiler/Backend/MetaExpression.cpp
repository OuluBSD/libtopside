#include "Backend.h"

#if 0

NAMESPACE_TOPSIDE_BEGIN


MetaStatement::MetaStatement() {
	MetaExpression& me = mexpr.Create();
	me.SetOwner(this);
	
	
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
	
	if (!IsContained(args))
		return s;
	
	if (args.have_header) {
		s.Cat('\t', args.indent);
		
		if (!is_inline) {
			if (mexpr.IsEmpty()) {
				s << "// <empty MetaStatement>\n";
			}
			else {
				s << mexpr->GetCodeString(args);
				if (!hide_stmt)
					s << ";";
				s << "\n";
			}
		}
		else {
			if (mexpr.IsEmpty()) {
				s << "/*<empty MetaStatement>*/";
			}
			else {
				s << mexpr->GetCodeString(args);
			}
		}
	}
	
	if (args.have_impl) {
		
	}
	
	return s;
}





MetaExpression&	MetaExpression::AddSub() {
	MetaExpression& me = mexprs.Add();
	me.SetOwner(this);
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
	else if (type == ID)
		s << "(Id: " << str << ")";
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
	else if (type == ID) {
		if (str.IsEmpty())
			s << "/*<invalid empty id>*/";
		else
			s << str;
	}
	else if (type == STRING) {
		if (str.IsEmpty())
			s << "/*<invalid empty string>*/";
		else
			s << "\"" << str << "\"";
	}
	else if (type == DEFINE) {
		s << "#define " << str << " \\\n";
		for (MetaExpression& me : mexprs) {
			s.Cat('\t', args.indent+1);
			s << me.GetCodeString(args) << " \\\n";
		}
		s << "\n";
	}
	else {
		TODO
	}
	
	return s;
}


NAMESPACE_TOPSIDE_END

#endif
