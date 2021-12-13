#include "SoftRend.h"

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
	
}

int SoftProgram::GetParamInt(GVar::ProgParamType type) {
	if (type == GVar::ACTIVE_UNIFORMS)
		return uniforms.GetCount();
	
	TODO
	
}

int SoftProgram::GetVarSize(int idx) const {
	
	TODO
	
}

int SoftProgram::GetVarType(int idx) const {
	
	TODO
	
}

String SoftProgram::GetVar(int idx) const {
	
	TODO
	
}

void SoftProgram::Attach(SoftShader& s) {
	ASSERT(s.prog == 0);
	s.prog = this;
	shaders.Add(&s);
}


NAMESPACE_TOPSIDE_END
