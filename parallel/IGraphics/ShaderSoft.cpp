#include "IGraphics.h"

NAMESPACE_PARALLEL_BEGIN





template <class Gfx>
SoftShaderT<Gfx>::SoftShaderT() {
	
}

template <class Gfx>
void SoftShaderT<Gfx>::Clear() {
	
}

template <class Gfx>
void SoftShaderT<Gfx>::SetSource(String s) {
	src = s;
}

/*template <class Gfx>
void SoftShaderT<Gfx>::SetTestShader(SoftShaderLibrary::FragmentShader fs) {
	this->fs = fs;
}*/

SOFTREND_EXCPLICIT_INITIALIZE_CLASS(SoftShaderT)


NAMESPACE_PARALLEL_END
