#include "Backend.h"

NAMESPACE_TOPSIDE_BEGIN


String MetaConditional::PreCodeString(const CodeArgs& args) const {
	String s;
	if (req_meta_defs.GetCount()) {
		s.Cat('\t', args.indent);
		s << "#if ";
		for(int i = 0; i < req_meta_defs.GetCount(); i++) {
			if (i) s << " && ";
			String def = req_meta_defs[i];
			s << "defined " << def;
		}
		s << "\n";
	}
	return s;
}

String MetaConditional::PostCodeString(const CodeArgs& args) const {
	String s;
	if (req_meta_defs.GetCount()) {
		s.Cat('\t', args.indent);
		s << "#endif\n";
	}
	return s;
}



String PathIdentifier::ToString() const {
	if (!begin || begin == end)
		return String();
	String s;
	const Token* iter = begin;
	while (iter != end) {
		//if (iter != begin) s.Cat('.');
		s.Cat(iter->GetTextValue());
		iter++;
	}
	return s;
}


NAMESPACE_TOPSIDE_END
