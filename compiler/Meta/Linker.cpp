#include "Meta.h"

NAMESPACE_OULU_BEGIN


Linker::Linker() : ErrorSource("Linker") {
	
}

void Linker::Add(const CompilationUnit& unit) {
	ASSERT(obj == NULL);
	obj = &unit.GetObject();
	
	
}

bool Linker::Link() {
	
	return true;
}


NAMESPACE_OULU_END
