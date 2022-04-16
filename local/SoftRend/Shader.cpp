#include "SoftRend.h"

NAMESPACE_PARALLEL_BEGIN





template <class B>
SoftShaderT<B>::SoftShaderT() {
	
}

template <class B>
void SoftShaderT<B>::Clear() {
	inited = false;
}

template <class B>
bool SoftShaderT<B>::Create(GVar::ShaderType t) {
	Clear();
	
	type = t;
	
	
	inited = true;
	return true;
}

template <class B>
void SoftShaderT<B>::SetSource(String s) {
	src = s;
}

/*template <class B>
void SoftShaderT<B>::SetTestShader(SoftShaderLibrary::FragmentShader fs) {
	this->fs = fs;
}*/

SOFTREND_EXCPLICIT_INITIALIZE_CLASS(SoftShaderT)


NAMESPACE_PARALLEL_END
