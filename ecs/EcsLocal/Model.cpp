#include "EcsLocal.h"


NAMESPACE_ECS_BEGIN

#if 0

/*void PrimitiveShape::SetShape(ShapeId type, const vec2& ax_vec) {
	shape.Create(type, ax_vec);
	
	model = new ModelMesh();
	model->MakeModel(shape);
}*/










/*bool ModelComponent::LoadModel(String path) {
	loader.Clear();
	return loader.LoadModel(path);
}*/

bool ModelComponent::AddTextureFile(int mesh_i, TexType type, String path) {
	if (loader)
		return loader.GetModel()->AddTextureFile(mesh_i, type, path);
	return false;
}

void ModelComponent::GetModels(VectorRendModel& models) {
	EntityRef e = GetEntity();
	RendModel& m = models.Add();
	m.a = GetModel();
	m.b.a = e->Find<Transform>();
	m.b.b = e->Find<Renderable>();
}

#endif

/*void ModelComponent::LoadModel(CpuDataState& state) {
	auto& o = cpu_obj ? *cpu_obj : state.AddObject();
	cpu_obj = cpu_obj ? cpu_obj : &o;
	if (!state.LoadModel(loader, o))
		Panic("Couldn't load model: ModelComponent");
	if (!state.LoadModelTextures(loader, o))
		Panic("Couldn't load model textures: ModelComponent");
}

void ModelComponent::LoadModel(OglDataState& state) {
	auto& o = ogl_obj ? *ogl_obj : state.AddObject();
	ogl_obj = ogl_obj ? ogl_obj : &o;
	if (!state.LoadModel(loader, o))
		Panic("Couldn't load model: ModelComponent");
	if (!state.LoadModelTextures(loader, o))
		Panic("Couldn't load model textures: ModelComponent");
}*/

/*void ModelComponent::RefreshModel(CpuDataState& state) {
	ASSERT(cpu_obj);
	TODO
}

void ModelComponent::RefreshModel(OglDataState& state) {
	ASSERT(ogl_obj);
	TODO
}*/





NAMESPACE_ECS_END

