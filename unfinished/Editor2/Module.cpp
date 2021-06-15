#include "Clang.h"


NAMESPACE_TRANSLATION


Module::Module() {
	
}

Module::Module(CXModule module) : module(module) {
	
}

File Module::GetFile() {
	return clang_Module_getASTFile(module);
}


	
Module Module::GetParent() {
	return clang_Module_getParent(module);
}

String Module::GetName() {
	return clang_getCString(clang_Module_getName(module));
}

String Module::GetFullName() {
	return clang_getCString(clang_Module_getFullName(module));
}


int Module::GetTopLevelHeaderCount(Unit& unit) {
	return clang_Module_getNumTopLevelHeaders(unit.unit, module);
}

File Module::GetTopLevelHeader(Unit& unit, int i) {
	return clang_Module_getTopLevelHeader(unit.unit, module, i);
}


END_NAMESPACE_TRANSLATION
