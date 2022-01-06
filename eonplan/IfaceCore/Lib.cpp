#include "IfaceCore.h"

NAMESPACE_PLAN_BEGIN

	
void IfaceLib::Dump() {
	for (Package* p : Packages())
		p->Dump();
}

void IfaceLib::Export(CompilationUnit& cu) {
	for (Package* p : Packages())
		p->Export(cu);
}

void IfaceLib::Export() {
	for (Package* p : Packages())
		p->Export();
}


NAMESPACE_PLAN_END
