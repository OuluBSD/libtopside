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
void SoftProgramT<Gfx>::Begin() {
	objs.SetCount(0);
}

template <class Gfx>
void SoftProgramT<Gfx>::BeginObject() {
	obj_i = objs.GetCount();
	objs.Add().Zero();
}

template <class Gfx>
void SoftProgramT<Gfx>::EndObject() {
	obj_i = -1;
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
		case GVar::VAR_NONE:
		case GVar::VAR_DIFFUSE:
		case GVar::VAR_SPECULAR:
		case GVar::VAR_AMBIENT:
		case GVar::VAR_EMISSIVE:
		case GVar::VAR_HEIGHT:
		case GVar::VAR_NORMALS:
		case GVar::VAR_SHININESS:
		case GVar::VAR_OPACITY:
		case GVar::VAR_DISPLACEMENT:
		case GVar::VAR_LIGHTMAP:
		case GVar::VAR_REFLECTION:
		case GVar::VAR_UNKNOWN:
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
		case GVar::VAR_COMPAT_CHANNELRESOLUTION:	return sizeof(GenericShaderArgs::iChannelResolution[0]);
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
	
	ASSERT(obj_i >= 0);
	if (obj_i < 0) return;
	auto& fargs = objs[obj_i].fargs;
	
	if (idx == GVar::VAR_NONE) {fargs.iNone = j; return;}
	if (idx == GVar::VAR_DIFFUSE) {fargs.iDiffuse = j; return;}
	if (idx == GVar::VAR_SPECULAR) {fargs.iSpecular = j; return;}
	if (idx == GVar::VAR_AMBIENT) {fargs.iAmbient = j; return;}
	if (idx == GVar::VAR_EMISSIVE) {fargs.iEmissive = j; return;}
	if (idx == GVar::VAR_HEIGHT) {fargs.iHeight = j; return;}
	if (idx == GVar::VAR_NORMALS) {fargs.iNormals = j; return;}
	if (idx == GVar::VAR_SHININESS) {fargs.iShininess = j; return;}
	if (idx == GVar::VAR_OPACITY) {fargs.iOpacity = j; return;}
	if (idx == GVar::VAR_DISPLACEMENT) {fargs.iDisplacement = j; return;}
	if (idx == GVar::VAR_LIGHTMAP) {fargs.iLightmap = j; return;}
	if (idx == GVar::VAR_REFLECTION) {fargs.iReflection = j; return;}
	if (idx == GVar::VAR_UNKNOWN) {fargs.iUnknown = j; return;}
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
		//case GVar::VAR_COMPAT_CHANNELRESOLUTION: args.iChannelResolution0 = vec3(f0,f1,f2); return;
		default: break;
	}
	ASSERT(obj_i >= 0);
	if (obj_i < 0) return;
	auto& fargs = objs[obj_i].fargs;
	switch (idx) {
		case GVar::VAR_LIGHTDIR: fargs.light_dir = vec3(f0,f1,f2); return;
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
	ASSERT(obj_i >= 0);
	if (obj_i < 0) return;
	auto& vargs = objs[obj_i].vargs;
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

template <class Gfx>
void SoftProgramT<Gfx>::SetVarArray(int i, int arr_size, int count, float* f) {
	/*ASSERT(obj_i >= 0);
	if (obj_i < 0) return;
	auto& vargs = objs[obj_i].vargs;*/
	int idx = uniforms.GetKey(i);
	
	if (arr_size == 3) {
		if (idx == GL::VAR_COMPAT_CHANNELRESOLUTION) {
			ASSERT(count == 4);
			for(int i = 0; i < 4; i++) {
				args.iChannelResolution[i] = vec3(f[0], f[1], f[2]);
				f += 3;
			}
		}
		else TODO
	}
	else TODO
}

template <class Gfx>
void SoftProgramT<Gfx>::BindTexture(int tex, const ByteImage* buf) {
	ASSERT(tex >= 0 && tex < CHANNEL_COUNT);
	if (tex < 0)
		return;
	
	if (tex < TEXTYPE_COUNT && obj_i >= 0) {
		auto& fargs = objs[obj_i].fargs;
		fargs.color_buf[tex] = buf;
	}
	else if (tex < CHANNEL_COUNT) {
		args.color_buf[tex] = buf;
	}
}


SOFTREND_EXCPLICIT_INITIALIZE_CLASS(SoftProgramT)


NAMESPACE_PARALLEL_END
