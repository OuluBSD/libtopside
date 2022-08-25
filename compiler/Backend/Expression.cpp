#include "Backend.h"

#if 0

NAMESPACE_TOPSIDE_BEGIN



String Expression::GetTreeString(int indent) const {
	String s;
	s.Cat('\t', indent);
	s << ToString() << "\n";
	for (const Expression& o : exprs) {
		s << o.GetTreeString(indent+1);
	}
	return s;
}

String Expression::ToString() const {
	String s;
	s << "Expression";
	return s;
}

String Expression::GetCodeString(const CodeArgs& args) const {
	//if (!IsContained(args))
	//	return String();
	
	String s;
	
	if (type == ID) {
		s << str;
	}
	else if (type == PARENT) {
		for (Expression& e : exprs) {
			s << e.GetCodeString(args);
		}
	}
	else if (type == ID) {
		s << str;
	}
	else if (type == ID_TMPL) {
		s << str << "<";
		int i = 0;
		for (Expression& e : exprs) {
			if (i++ > 0)
				s << ", ";
			s << e.GetCodeString(args);
		}
		s << ">";
	}
	else if (type == RETURN) {
		s << "return ";
		int i = 0;
		for (Expression& e : exprs) {
			if (i++ > 0)
				s << ", ";
			s << e.GetCodeString(args);
		}
	}
	else if (type == META_CALL) {
		s << str << "(";
		int i = 0;
		for (Expression& e : exprs) {
			if (i++ > 0)
				s << ", ";
			s << e.GetCodeString(args);
		}
		s << ")";
	}
	else if (type == CALL) {
		s << str << "(";
		int i = 0;
		for (Expression& e : exprs) {
			if (i++ > 0)
				s << ", ";
			s << e.GetCodeString(args);
		}
		s << ")";
	}
	else if (type == OBJ_METHOD) {
		s << "." << str << "(";
		int i = 0;
		for (Expression& e : exprs) {
			if (i++ > 0)
				s << ", ";
			s << e.GetCodeString(args);
		}
		s << ")";
	}
	else if (type == OBJ_FIELD) {
		s << "." << str;
	}
	else if (type == OBJ_METHOD_TMPL) {
		s << "." << str;
		if (exprs.GetCount() >= 1) {
			s << "<";
			const Expression& tmpl_args = exprs[0];
			int i = 0;
			for (Expression& e : tmpl_args.exprs) {
				if (i++ > 0)
					s << ", ";
				s << e.GetCodeString(args);
			}
			s << ">";
		}
		s << "(";
		if (exprs.GetCount() >= 2) {
			const Expression& call_params = exprs[1];
			int i = 0;
			for (Expression& e : call_params.exprs) {
				if (i++ > 0)
					s << ", ";
				s << e.GetCodeString(args);
			}
		}
		s << ")";
	}
	else {
		TODO
	}
	
	
	return s;
}

NAMESPACE_TOPSIDE_END

#endif
