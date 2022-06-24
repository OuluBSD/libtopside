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
	if (type == GVar::ACTIVE_UNIFORMS) {
		for (SoftShader* s : shaders) {
			auto& sb = s->Get();
			for (dword d : sb.used_uniforms)
				uniforms.GetAdd(d);
		}
		return uniforms.GetCount();
	}
	
	TODO
	return 0;
}

template <class Gfx>
int SoftProgramT<Gfx>::GetVarSize(int i) const {
	int idx = uniforms.GetKey(i);
	
	switch (idx) {
		case GVar::VAR_VIEW:				return sizeof(GenericVertexShaderArgs::view);
		case GVar::VAR_LIGHTDIR:			return sizeof(GenericFragmentShaderArgs::light_dir);
		/*case Shaders::IPROJ:				return sizeof(GenericVertexShaderArgs::proj);
		case Shaders::ISCALE:				return sizeof(GenericVertexShaderArgs::scale);*/
		case GVar::VAR_MODEL:				return sizeof(GenericVertexShaderArgs::model);
		case GVar::VAR_COMPAT_RESOLUTION:	return sizeof(GenericShaderArgs::iResolution);
		case GVar::VAR_COMPAT_TIME:			return sizeof(GenericShaderArgs::iTime);
		case GVar::VAR_COMPAT_CHANNEL0:
		case GVar::VAR_COMPAT_CHANNEL1:
		case GVar::VAR_COMPAT_CHANNEL2:
		case GVar::VAR_COMPAT_CHANNEL3:
		case GVar::VAR_BUFFERSTAGE0_COLOR:
		case GVar::VAR_BUFFERSTAGE1_COLOR:
		case GVar::VAR_BUFFERSTAGE2_COLOR:
		case GVar::VAR_BUFFERSTAGE3_COLOR:
		case GVar::VAR_BUFFERSTAGE4_COLOR:
											return sizeof(void*);
		case GVar::VAR_COMPAT_CHANNELRESOLUTION:	return sizeof(GenericShaderArgs::iChannelResolution0);
		default: break;
	}
	
	TODO
	
}

template <class Gfx>
int SoftProgramT<Gfx>::GetVarType(int i) const {
	int idx = uniforms.GetKey(i);
	return 1;
}

template <class Gfx>
String SoftProgramT<Gfx>::GetVar(int i) const {
	int idx = uniforms.GetKey(i);
	if (idx < 0)
		return "";
	if (idx < GVar::VAR_COUNT)
		return GVar::names[idx];
		
	TODO
	
}


template <class Gfx>
void SoftProgramT<Gfx>::Attach(SoftShader& s) {
	ASSERT(s.GetSoftProgram() == 0);
	s.SetSoftProgram(this);
	shaders.Add(&s);
}

template <class Gfx>
void SoftProgramT<Gfx>::SetVar(int i, int j) {
	int idx = uniforms.GetKey(i);
	if (idx == GVar::VAR_COMPAT_CHANNEL0) {args.iChannel0 = j; return;}
	if (idx == GVar::VAR_COMPAT_CHANNEL1) {args.iChannel1 = j; return;}
	if (idx == GVar::VAR_COMPAT_CHANNEL2) {args.iChannel2 = j; return;}
	if (idx == GVar::VAR_COMPAT_CHANNEL3) {args.iChannel3 = j; return;}
	if (idx == GVar::VAR_BUFFERSTAGE0_COLOR) {args.iStageColor0 = j; return;}
	if (idx == GVar::VAR_BUFFERSTAGE1_COLOR) {args.iStageColor1 = j; return;}
	if (idx == GVar::VAR_BUFFERSTAGE2_COLOR) {args.iStageColor2 = j; return;}
	if (idx == GVar::VAR_BUFFERSTAGE3_COLOR) {args.iStageColor3 = j; return;}
	if (idx == GVar::VAR_BUFFERSTAGE4_COLOR) {args.iStageColor4 = j; return;}
	TODO
}

template <class Gfx>
void SoftProgramT<Gfx>::SetVar(int i, float f) {
	int idx = uniforms.GetKey(i);
	switch (idx) {
		case GVar::VAR_COMPAT_TIME: args.iTime = f; return;
		default: break;
	}
	ASSERT(0);
}

template <class Gfx>
void SoftProgramT<Gfx>::SetVar(int i, float f0, float f1) {
	int idx = uniforms.GetKey(i);
	TODO
}

template <class Gfx>
void SoftProgramT<Gfx>::SetVar(int i, float f0, float f1, float f2) {
	int idx = uniforms.GetKey(i);
	switch (idx) {
		case GVar::VAR_COMPAT_RESOLUTION: args.iResolution = vec3(f0,f1,f2); return;
		case GVar::VAR_LIGHTDIR: fargs.light_dir = vec3(f0,f1,f2); return;
		case GVar::VAR_COMPAT_CHANNELRESOLUTION: args.iChannelResolution0 = vec3(f0,f1,f2); return;
		default: break;
	}
	ASSERT(0);
}

template <class Gfx>
void SoftProgramT<Gfx>::SetVar(int i, float f0, float f1, float f2, float f3) {
	int idx = uniforms.GetKey(i);
	TODO
}

template <class Gfx>
void SoftProgramT<Gfx>::SetVar(int i, const mat4& mat) {
	int idx = uniforms.GetKey(i);
	switch (idx) {
		case GVar::VAR_VIEW:		vargs.view = mat; return;
		/*case Shaders::IPROJ:		vargs.proj = mat; return;
		case Shaders::ISCALE:		vargs.scale = mat; return;*/
		case GVar::VAR_MODEL:		vargs.model = mat; return;
		default: break;
	}
	ASSERT(0);
}


SOFTREND_EXCPLICIT_INITIALIZE_CLASS(SoftProgramT)


NAMESPACE_PARALLEL_END
