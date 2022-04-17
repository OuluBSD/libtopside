#include "IGraphics.h"

NAMESPACE_PARALLEL_BEGIN





template <class Gfx>
SoftShaderT<Gfx>::SoftShaderT() {
	
}

template <class Gfx>
void SoftShaderT<Gfx>::Clear() {
	inited = false;
}

template <class Gfx>
bool SoftShaderT<Gfx>::Create(GVar::ShaderType t) {
	Clear();
	
	type = t;
	
	
	inited = true;
	return true;
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
