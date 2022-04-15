#include "SoftRend.h"

NAMESPACE_PARALLEL_BEGIN


//VectorMap<String, SoftShaderLibrary::FragmentShader> SoftShaderLibrary::frag_shaders;
template <class Backend>
	VectorMap<String, typename SoftShaderLibraryT<Backend>::ShaderFactory>
		SoftShaderLibraryT<Backend>::shader_classes[GVar::SHADERTYPE_COUNT];

template <class Backend>
	VectorMap<String, typename SoftShaderLibraryT<Backend>::ShaderFactory>&
		SoftShaderLibraryT<Backend>::GetMap(int i) {
	ASSERT(i >= 0 && i < GVar::SHADERTYPE_COUNT);
	return shader_classes[i];
}



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

SOFTREND_EXCPLICIT_INITIALIZE_CLASS(SoftShaderLibraryT)
SOFTREND_EXCPLICIT_INITIALIZE_CLASS(SoftShaderT)


NAMESPACE_PARALLEL_END
