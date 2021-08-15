#include "Backend.h"


NAMESPACE_TOPSIDE_BEGIN

Class::Class() {
	
}

bool Class::Inherit(Class& cls) {
	VectorFindAdd(inherited, &cls);
	return true;
}

NAMESPACE_TOPSIDE_END
