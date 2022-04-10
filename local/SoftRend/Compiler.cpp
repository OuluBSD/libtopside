#include "SoftRend.h"

NAMESPACE_TOPSIDE_BEGIN


template <class B>
SoftCompilerT<B>::SoftCompilerT() {
	
}

template <class B>
bool SoftCompilerT<B>::Compile(SoftShader& s) {
	LOG("SoftCompiler::Compile: warning: TODO");
	
	return true;
}


SOFTREND_EXCPLICIT_INITIALIZE_CLASS(SoftCompilerT)


NAMESPACE_TOPSIDE_END
