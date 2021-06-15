#include "Clang.h"

NAMESPACE_TRANSLATION
	
Range::Range() {
	
}

Range::Range(CXSourceRange range) : range(range) {
	
}

	
Location Range::Begin() {
	return clang_getRangeStart(range);
}

Location Range::End()  {
	return clang_getRangeEnd(range);
}

END_NAMESPACE_TRANSLATION
