#include <Graphics/Graphics.h>

NAMESPACE_TOPSIDE_BEGIN


SoftProgram::SoftProgram() {
	
}

void SoftProgram::Clear() {
	ASSERT(shaders.IsEmpty());
	inited = false;
}

bool SoftProgram::Create() {
	
	
	inited = true;
	return true;
}

bool SoftProgram::LinkProgram() {
	
	
	return true;
}

void SoftProgram::SetParameter(GVar::ParamType type, int i) {
	TODO
}

int SoftProgram::GetParamInt(GVar::ProgParamType type) {
	if (type == GVar::ACTIVE_UNIFORMS)
		return Shaders::UNIFORM_COUNT + uniforms.GetCount();
	
	TODO
	
}

int SoftProgram::GetVarSize(int idx) const {
	switch (idx) {
		case Shaders::IVIEW:		return sizeof(GenericVertexShaderArgs::view);
		case Shaders::ILIGHTDIR:	return sizeof(GenericFragmentShaderArgs::light_dir);
		/*case Shaders::IPROJ:		return sizeof(GenericVertexShaderArgs::proj);
		case Shaders::ISCALE:		return sizeof(GenericVertexShaderArgs::scale);
		case Shaders::IMODEL:		return sizeof(GenericVertexShaderArgs::model);*/
		case Shaders::IRESOLUTION:	return sizeof(GenericShaderArgs::iResolution);
		case Shaders::ITIME:		return sizeof(GenericShaderArgs::iTime);
		default: break;
	}
	
	TODO
	
}

int SoftProgram::GetVarType(int idx) const {
	return 1;
}

String SoftProgram::GetVar(int idx) const {
	if (idx < 0) return "";
	if (idx < Shaders::UNIFORM_COUNT) return Shaders::GetUniformName(idx);
	if (idx > Shaders::UNIFORM_COUNT + uniforms.GetCount()) return "";
	
	TODO
	
}

void SoftProgram::Attach(SoftShader& s) {
	ASSERT(s.prog == 0);
	s.prog = this;
	shaders.Add(&s);
}

void SoftProgram::SetVar(int idx, int i) {
	TODO
}

void SoftProgram::SetVar(int idx, float f) {
	switch (idx) {
		case Shaders::ITIME: args.iTime = f; return;
		default: break;
	}
	ASSERT(0);
}

void SoftProgram::SetVar(int idx, float f0, float f1) {
	TODO
}

void SoftProgram::SetVar(int idx, float f0, float f1, float f2) {
	switch (idx) {
		case Shaders::IRESOLUTION: args.iResolution = vec3(f0,f1,f2); return;
		case Shaders::ILIGHTDIR: fargs.light_dir = vec3(f0,f1,f2); return;
		default: break;
	}
	ASSERT(0);
}

void SoftProgram::SetVar(int idx, float f0, float f1, float f2, float f3) {
	TODO
}

void SoftProgram::SetVar(int idx, const mat4& mat) {
	switch (idx) {
		case Shaders::IVIEW:		vargs.view = mat; return;
		/*case Shaders::IPROJ:		vargs.proj = mat; return;
		case Shaders::ISCALE:		vargs.scale = mat; return;
		case Shaders::IMODEL:		vargs.model = mat; return;*/
		default: break;
	}
	ASSERT(0);
}


NAMESPACE_TOPSIDE_END
