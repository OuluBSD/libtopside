#include "Meta.h"

NAMESPACE_OULU_BEGIN


CompilationUnit::CompilationUnit() {
	token.WhenMessage << Proxy(WhenMessage);
	parser.WhenMessage << Proxy(WhenMessage);
	comp.WhenMessage << Proxy(WhenMessage);
	
	
}

bool CompilationUnit::CompileString(String mach, String path, String code) {
	
	if (!token.Process(code, path))
		return false;
	//token.Dump();
	
	
	if (!parser.Init(mach))
		return false;
	
	if (!parser.Process(token))
		return false;
	parser.Dump();
	
	
	if (!comp.Init(mach))
		return false;
	
	if (!comp.Process(parser))
		return false;
	
	return true;
}


NAMESPACE_OULU_END
