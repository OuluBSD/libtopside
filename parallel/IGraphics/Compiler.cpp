#include "IGraphics.h"

NAMESPACE_PARALLEL_BEGIN


template <class Gfx>
SoftCompilerT<Gfx>::SoftCompilerT() {
	
}

template <class Gfx>
bool SoftCompilerT<Gfx>::Compile(SoftShader& s) {
	LOG("SoftCompiler::Compile: warning: TODO");
	
	return true;
}


SOFTREND_EXCPLICIT_INITIALIZE_CLASS(SoftCompilerT)


NAMESPACE_PARALLEL_END
