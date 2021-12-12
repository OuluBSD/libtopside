#include "SoftRend.h"

NAMESPACE_TOPSIDE_BEGIN


SoftProgram::SoftProgram() {
	
}

void SoftProgram::Clear() {
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
	
	TODO
	
}


NAMESPACE_TOPSIDE_END
