#include "Grammar.h"



#ifndef flagBOOTSTRAP

NAMESPACE_OULU_BEGIN
namespace Ast {


Node::Node() {
	
}




NamedNode* Scope::FindInVisible(String id) {
	Scope* s = this;
	while (s) {
		NamedNode* n = s->FindInScope(id);
		if (n)
			return n;
		s = s->container;
	}
	return 0;
}

NamedNode* Scope::FindInScope(String id) {
	int i;
	i = fields.Find(id);
	if (i >= 0) return &fields[i];
	
	i = classes.Find(id);
	if (i >= 0) return &classes[i];
	
	i = funcs.Find(id);
	if (i >= 0) return &funcs[i];
	
	return 0;
}


}
NAMESPACE_OULU_END

#endif
