#include "IGraphics.h"
//#include <Graphics/Graphics.h>

NAMESPACE_PARALLEL_BEGIN


template <class Gfx>
SoftProgramT<Gfx>::SoftProgramT() {
	
}

template <class Gfx>
void SoftProgramT<Gfx>::Clear() {
	ASSERT(shaders.IsEmpty());
	inited = false;
}

template <class Gfx>
bool SoftProgramT<Gfx>::Create() {
	
	
	inited = true;
	return true;
}

template <class Gfx>
bool SoftProgramT<Gfx>::LinkProgram() {
	
	
	return true;
}

template <class Gfx>
void SoftProgramT<Gfx>::SetParameter(GVar::ParamType type, int i) {
	if (type == GVar::PROGRAM_SEPARABLE) {
		// pass
	}
	else {
		TODO
	}
}

template <class Gfx>
int SoftProgramT<Gfx>::GetParamInt(GVar::ProgParamType type) {
	if (type == GVar::ACTIVE_UNIFORMS)
		return Shaders::UNIFORM_COUNT + uniforms.GetCount();
	
	TODO
	
}

template <class Gfx>
int SoftProgramT<Gfx>::GetVarSize(int idx) const {
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

template <class Gfx>
int SoftProgramT<Gfx>::GetVarType(int idx) const {
	return 1;
}

template <class Gfx>
String SoftProgramT<Gfx>::GetVar(int idx) const {
	if (idx < 0) return "";
	if (idx < Shaders::UNIFORM_COUNT) return Shaders::GetUniformName(idx);
	if (idx > Shaders::UNIFORM_COUNT + uniforms.GetCount()) return "";
	
	TODO
	
}

template <class Gfx>
void SoftProgramT<Gfx>::Attach(SoftShader& s) {
	ASSERT(s.GetSoftProgram() == 0);
	s.SetSoftProgram(this);
	shaders.Add(&s);
}

template <class Gfx>
void SoftProgramT<Gfx>::SetVar(int idx, int i) {
	TODO
}

template <class Gfx>
void SoftProgramT<Gfx>::SetVar(int idx, float f) {
	switch (idx) {
		case Shaders::ITIME: args.iTime = f; return;
		default: break;
	}
	ASSERT(0);
}

template <class Gfx>
void SoftProgramT<Gfx>::SetVar(int idx, float f0, float f1) {
	TODO
}

template <class Gfx>
void SoftProgramT<Gfx>::SetVar(int idx, float f0, float f1, float f2) {
	switch (idx) {
		case Shaders::IRESOLUTION: args.iResolution = vec3(f0,f1,f2); return;
		case Shaders::ILIGHTDIR: fargs.light_dir = vec3(f0,f1,f2); return;
		default: break;
	}
	ASSERT(0);
}

template <class Gfx>
void SoftProgramT<Gfx>::SetVar(int idx, float f0, float f1, float f2, float f3) {
	TODO
}

template <class Gfx>
void SoftProgramT<Gfx>::SetVar(int idx, const mat4& mat) {
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


NAMESPACE_PARALLEL_END
