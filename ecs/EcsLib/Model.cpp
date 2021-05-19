#include "EcsLib.h"


NAMESPACE_TOPSIDE_BEGIN


void PrimitiveShape::SetShape(ShapeId type, const vec2& ax_vec) {
	shape.Create(type, ax_vec);
	
	model = new Model();
	model->MakeModel(shape);
}










bool ModelComponent::LoadModel(String path) {
	loader.Clear();
	return loader.LoadModel(path);
}

bool ModelComponent::AddTextureFile(int mesh_i, TexType type, String path) {
	if (loader.model)
		return loader.model->AddTextureFile(mesh_i, type, path);
	return false;
}

void ModelComponent::GetModels(VectorRendModel& models) {
	EntityRef e = GetEntity();
	RendModel& m = models.Add();
	m.a = GetModel();
	m.b.a = e->Find<Transform>();
	m.b.b = e->Find<Renderable>();
}

#if 0
void ModelComponent::Signal() {
	if (loader.model) {
		bool can_pick = GetConnections().GetCount() == 1;
		
		for(InterfaceBase* conn: GetConnections()) {
			ModelSource* in = (ModelSource*)conn;
			TODO
			/*Ref<PipelineData> pdata = in->GetData();
			if (pdata) {
				pdata->PutModel(loader.model, can_pick);
			}*/
		}
		
		loader.model.Clear();
	}
}
#endif







NAMESPACE_TOPSIDE_END

