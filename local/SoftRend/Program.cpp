#include "SoftRend.h"
//#include <Graphics/Graphics.h>

NAMESPACE_TOPSIDE_BEGIN


template <class B>
SoftProgramT<B>::SoftProgramT() {
	
}

template <class B>
void SoftProgramT<B>::Clear() {
	ASSERT(shaders.IsEmpty());
	inited = false;
}

template <class B>
bool SoftProgramT<B>::Create() {
	
	
	inited = true;
	return true;
}

template <class B>
bool SoftProgramT<B>::LinkProgram() {
	
	
	return true;
}

template <class B>
void SoftProgramT<B>::SetParameter(GVar::ParamType type, int i) {
	TODO
}

template <class B>
int SoftProgramT<B>::GetParamInt(GVar::ProgParamType type) {
	if (type == GVar::ACTIVE_UNIFORMS)
		return Shaders::UNIFORM_COUNT + uniforms.GetCount();
	
	TODO
	
}

template <class B>
int SoftProgramT<B>::GetVarSize(int idx) const {
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

template <class B>
int SoftProgramT<B>::GetVarType(int idx) const {
	return 1;
}

template <class B>
String SoftProgramT<B>::GetVar(int idx) const {
	if (idx < 0) return "";
	if (idx < Shaders::UNIFORM_COUNT) return Shaders::GetUniformName(idx);
	if (idx > Shaders::UNIFORM_COUNT + uniforms.GetCount()) return "";
	
	TODO
	
}

template <class B>
void SoftProgramT<B>::Attach(SoftShader& s) {
	ASSERT(s.GetSoftProgram() == 0);
	s.SetSoftProgram(this);
	shaders.Add(&s);
}

template <class B>
void SoftProgramT<B>::SetVar(int idx, int i) {
	TODO
}

template <class B>
void SoftProgramT<B>::SetVar(int idx, float f) {
	switch (idx) {
		case Shaders::ITIME: args.iTime = f; return;
		default: break;
	}
	ASSERT(0);
}

template <class B>
void SoftProgramT<B>::SetVar(int idx, float f0, float f1) {
	TODO
}

template <class B>
void SoftProgramT<B>::SetVar(int idx, float f0, float f1, float f2) {
	switch (idx) {
		case Shaders::IRESOLUTION: args.iResolution = vec3(f0,f1,f2); return;
		case Shaders::ILIGHTDIR: fargs.light_dir = vec3(f0,f1,f2); return;
		default: break;
	}
	ASSERT(0);
}

template <class B>
void SoftProgramT<B>::SetVar(int idx, float f0, float f1, float f2, float f3) {
	TODO
}

template <class B>
void SoftProgramT<B>::SetVar(int idx, const mat4& mat) {
	switch (idx) {
		case Shaders::IVIEW:		vargs.view = mat; return;
		/*case Shaders::IPROJ:		vargs.proj = mat; return;
		case Shaders::ISCALE:		vargs.scale = mat; return;
		case Shaders::IMODEL:		vargs.model = mat; return;*/
		default: break;
	}
	ASSERT(0);
}


SOFTREND_EXCPLICIT_INITIALIZE_CLASS(SoftProgramT)


NAMESPACE_TOPSIDE_END
