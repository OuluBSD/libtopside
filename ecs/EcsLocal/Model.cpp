#include "EcsLocal.h"


NAMESPACE_ECS_BEGIN


/*void PrimitiveShape::SetShape(ShapeId type, const vec2& ax_vec) {
	shape.Create(type, ax_vec);
	
	model = new ModelMesh();
	model->MakeModel(shape);
}*/










bool ModelComponent::LoadModel(String path) {
	loader.Clear();
	return loader.LoadModel(path);
}

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





NAMESPACE_ECS_END

