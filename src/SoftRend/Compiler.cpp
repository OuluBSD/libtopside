#include "SoftRend.h"

NAMESPACE_TOPSIDE_BEGIN



SoftCompiler::SoftCompiler() {
	
}


bool SoftCompiler::Compile(SoftShader& s) {
	LOG("SoftCompiler::Compile: warning: software shaders are not currently compiled");
	
	return true;
}



NAMESPACE_TOPSIDE_END
