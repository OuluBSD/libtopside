#include "IGraphics.h"

#if 0

NAMESPACE_TOPSIDE_BEGIN

void CpuDataObject::Paint() {
	TODO
}

void CpuDataObject::MakeTexture(int tex_id, int w, int h, int pitch, int stride, const Vector<byte>& data) {
	TODO
}
/*
void CpuDataObject::Set(const mat4& model, const mat4& scale, const mat4* proj, const mat4* view) {
	TODO
}

void CpuDataObject::SetModel(const mat4& m) {
	TODO
}

void CpuDataObject::SetScale(const mat4& m) {
	TODO
}

void CpuDataObject::SetProjection(const mat4& m) {
	TODO
}

void CpuDataObject::SetView(const mat4& m) {
	TODO
}*/




GfxDataObject& CpuFramebufferState::CreateObject() {
	CpuDataObject& o = objects.Add(new CpuDataObject(*this));
	o.id = objects.GetCount() - 1;
	RendVer1(OnRealizeObject, o.id);
	return o;
}


GfxDataObject* CpuShader::CreateObject() {
	return &state->CreateObject();
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




void Mesh::RefreshSw(GfxDataObject& o) {
	CpuDataObject* fbo = CastPtr<CpuDataObject>(&o);
	ASSERT(fbo);
	if (fbo)
		RefreshSw(*fbo);
}

void Mesh::RefreshSw(CpuDataObject& o) {
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
	for(int i = 0; i < GVar::SHADERTYPE_COUNT; i++) {
		if (state.stages[i])
			stages[i] = CastPtr<CpuShader>(state.stages[i]);
	}
}

void CpuShaderPipeline::Clear() {
	state = 0;
	for(int i = 0; i < GVar::SHADERTYPE_COUNT; i++)
		stages[i] = 0;
}



NAMESPACE_TOPSIDE_END

#endif
