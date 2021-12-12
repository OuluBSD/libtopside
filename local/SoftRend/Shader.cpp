#include "SoftRend.h"

NAMESPACE_TOPSIDE_BEGIN


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

void SoftShader::SetVar(int idx, int i) {
	
}

void SoftShader::SetVar(int idx, float f) {
	
}

void SoftShader::SetVar(int idx, float f0, float f1) {
	
}

void SoftShader::SetVar(int idx, float f0, float f1, float f2) {
	
}

void SoftShader::SetVar(int idx, float f0, float f1, float f2, float f3) {
	
}



NAMESPACE_TOPSIDE_END
