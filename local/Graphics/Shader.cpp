#include "Graphics.h"

NAMESPACE_TOPSIDE_BEGIN


void Shader::PushMultiplyMat4(String key, const mat4& mat) {
	mat4& next = stack.Add();
	mat4& prev = stack[stack.GetCount()-2];
	next = prev * mat;
}

void Shader::PopMat4() {
	stack.SetCount(stack.GetCount()-1);
}

void Shader::SetStackMat4(const mat4& mat) {
	stack.SetCount(1);
	stack[0] = mat;
}



Shader* Shader::NewDefault() {
	AppFlags& f = GetAppFlags();
	
	switch (f.gfx) {
		case AppFlags::GFX_SW:		return new CpuShader();
#ifdef flagGUI
		case AppFlags::GFX_OPENGL:	return new OpenGLShader();
		case AppFlags::GFX_DX12:
		case AppFlags::GFX_VULKAN:
		case AppFlags::GFX_METAL:
#endif
		default:
		break;
	}
	
	return 0;
}

NAMESPACE_TOPSIDE_END
