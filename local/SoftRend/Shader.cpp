#include "SoftRend.h"

NAMESPACE_TOPSIDE_BEGIN


VectorMap<String, SoftShaderLibrary::FragmentShader> SoftShaderLibrary::frag_shaders;




SoftShader::SoftShader() {
	
}

void SoftShader::Clear() {
	inited = false;
}

bool SoftShader::Create(GVar::ShaderType t) {
	Clear();
	
	type = t;
	
	
	inited = true;
	return true;
}

void SoftShader::SetSource(String s) {
	src = s;
}

void SoftShader::SetTestShader(SoftShaderLibrary::FragmentShader fs) {
	this->fs = fs;
}


NAMESPACE_TOPSIDE_END
