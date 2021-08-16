#include "Backend.h"


NAMESPACE_TOPSIDE_BEGIN



String Function::GetTreeString(int indent) const {
	String s;
	s.Cat('\t', indent);
	s << ToString() << "\n";
	if (impl)
		s << impl->GetTreeString(indent+1);
	return s;
}

String Function::ToString() const {
	String s;
	s << name << ": Function";
	return s;
}

String Function::GetCodeString(const CodeArgs& args) const {
	if (!IsContained(args))
		return String();
	
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
