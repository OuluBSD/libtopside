#include "Backend.h"


NAMESPACE_TOPSIDE_BEGIN



String Statement::GetTreeString(int indent) const {
	String s;
	s.Cat('\t', indent);
	s << ToString() << "\n";
	for (const Statement& o : stmts) {
		s << o.GetTreeString(indent+1);
	}
	if (expr)
		s << expr->GetTreeString(indent+1);
	return s;
}

String Statement::ToString() const {
	String s;
	s << "Statement";
	return s;
}

String Statement::GetCodeString(const CodeArgs& args) const {
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
