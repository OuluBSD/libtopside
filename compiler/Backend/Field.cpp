#include "Backend.h"

#if 0

NAMESPACE_TOPSIDE_BEGIN



String Field::GetTreeString(int indent) const {
	String s;
	s.Cat('\t', indent);
	s << ToString() << "\n";
	if (ctor)
		s << ctor->GetTreeString(indent+1);
	return s;
}

String Field::ToString() const {
	String s;
	s << name << ": Field";
	return s;
}

String Field::GetCodeString(const CodeArgs& args) const {
	if (!IsContained(args))
		return String();
	
	String s;
	
	if (args.have_header) {
		s.Cat('\t', args.indent);
		if (cls)
			s << cls->GetTypeString();
		s << " " << name << ";\n";
		
		// todo: if static const -> expr
	}
	
	if (args.have_impl) {
		
		TODO
		
	}
	
	return s;
}

NAMESPACE_TOPSIDE_END

#endif
