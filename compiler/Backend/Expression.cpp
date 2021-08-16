#include "Backend.h"


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
	String s;
	
	if (args.have_header) {
		
		TODO
		
	}
	
	if (args.have_impl) {
		
		TODO
		
	}
	
	return s;
}

NAMESPACE_TOPSIDE_END
