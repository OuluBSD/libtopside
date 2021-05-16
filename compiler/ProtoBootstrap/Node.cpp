#include "Bootstrap.h"


NAMESPACE_TOPSIDE_BEGIN
	

String NodeTreeStringSimple(const Node& n, int depth, String tab) {
	if (depth >= 100) return "";
	
	String s;
	for(int i = 0; i < depth; i++)
		s.Cat(tab);
	
	s << n.GetTypeString();
	int block = n.GetBlock();
	if (block >= 0)
		s << "(b" << block << ")";
	s << "(" << GetFileName(n.GetTokenFile()) << ":" << n.GetTokenLine() << ":" << n.GetTokenCol() << "): ";
	if (n.GetTokenType())
		s << "(" << n.GetTokenType() << ") ";
	
	String tk_str = n.GetTokenString();
	if (tk_str.IsEmpty())
		tk_str.Cat(n.GetTokenType());
	s << tk_str;
	
	
	const NodeData* d = n.GetData();
	if (d) {
		for(int i = 0; i < d->GetAttrCount(); i++)
			s << " " <<d->GetAttrKey(i) << "=\"" << d->GetAttr(i) << "\"";
	}
	s << "\n";
	
	for(int i = 0; i < n.GetCount(); i++)
		s << NodeTreeStringSimple(n.At(i), depth+1, tab);
	
	return s;
}


NAMESPACE_TOPSIDE_END
