#include "SoftRend.h"

NAMESPACE_PARALLEL_BEGIN


template <class B>
SoftCompilerT<B>::SoftCompilerT() {
	
}

template <class B>
bool SoftCompilerT<B>::Compile(SoftShader& s) {
	LOG("SoftCompiler::Compile: warning: TODO");
	
	return true;
}


SOFTREND_EXCPLICIT_INITIALIZE_CLASS(SoftCompilerT)


NAMESPACE_PARALLEL_END
