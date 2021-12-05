#include "Graphics.h"

NAMESPACE_TOPSIDE_BEGIN

void CpuFramebufferObject::Paint() {
	TODO
}

void CpuFramebufferObject::MakeTexture(int tex_id, int w, int h, int pitch, int stride, const Vector<byte>& data) {
	TODO
}
/*
void CpuFramebufferObject::Set(const mat4& model, const mat4& scale, const mat4* proj, const mat4* view) {
	TODO
}

void CpuFramebufferObject::SetModel(const mat4& m) {
	TODO
}

void CpuFramebufferObject::SetScale(const mat4& m) {
	TODO
}

void CpuFramebufferObject::SetProjection(const mat4& m) {
	TODO
}

void CpuFramebufferObject::SetView(const mat4& m) {
	TODO
}*/




FramebufferObject& CpuFramebufferState::NewObject() {
	CpuFramebufferObject& o = objects.Add(new CpuFramebufferObject(*this));
	o.id = objects.GetCount() - 1;
	RendVer1(OnRealizeObject, o.id);
	return o;
}


FramebufferObject* CpuShader::CreateObject() {
	return &state->NewObject();
}

/*
bool CpuShader::Load(String vertex_path, String fragment_path, String geometry_path) {
	TODO
}

void CpuShader::Refresh(ModelMesh& model) {
	TODO
}

void CpuShader::Refresh(ModelMesh& model, Mesh& mesh) {
	TODO
}

void CpuShader::Use() {
	TODO
}

void CpuShader::SetBool(const String &name, bool value) const {
	
}

void CpuShader::SetInt(const String &name, int value) const {
	
}

void CpuShader::SetFloat(const String &name, float value) const {
	
}

void CpuShader::SetVec2(const String &name, const vec2 &value) const {
	
}

void CpuShader::SetVec3(const String &name, const vec3 &value) const {
	
}

void CpuShader::SetVec4(const String &name, const vec4 &value) const {
	
}

void CpuShader::SetMat2(const String &name, const mat2 &mat) const {
	
}

void CpuShader::SetMat3(const String &name, const mat3 &mat) const {
	
}

void CpuShader::SetMat4(const String &name, const mat4 &mat) const {
	
}
*/




void Mesh::RefreshSw(FramebufferObject& o) {
	CpuFramebufferObject* fbo = CastPtr<CpuFramebufferObject>(&o);
	ASSERT(fbo);
	if (fbo)
		RefreshSw(*fbo);
}

void Mesh::RefreshSw(CpuFramebufferObject& o) {
	// pass?
}






CpuShaderPipeline::CpuShaderPipeline() {
	Clear();
}

void CpuShaderPipeline::LoadState(CpuFramebufferState& state) {
	Clear();
	
	this->state = &state;
	AppendState(state);
}

void CpuShaderPipeline::AppendState(CpuFramebufferState& state) {
	for(int i = 0; i < ShaderVar::PROG_COUNT; i++) {
		if (state.stages[i])
			stages[i] = CastPtr<CpuShader>(state.stages[i]);
	}
}

void CpuShaderPipeline::Clear() {
	state = 0;
	for(int i = 0; i < ShaderVar::PROG_COUNT; i++)
		stages[i] = 0;
}



NAMESPACE_TOPSIDE_END
