#include "EcsLib.h"


NAMESPACE_OULU_BEGIN


void PrimitiveShape::SetShape(ShapeId type, const vec2& ax_vec) {
	shape.Create(type, ax_vec);
	
	model = new Model();
	model->MakeModel(shape);
}

void PrimitiveShape::Signal() {
	for(InterfaceBase* conn: GetConnections()) {
		ModelSource* in = (ModelSource*)conn;
		/*Ref<PipelineData> pdata = in->GetData();
		if (pdata) {
			pdata->PutModel(model, true);
		}*/
		TODO
	}
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
	Entity& e = GetEntity();
	RendModel& m = models.Add();
	m.a = GetModel();
	m.b.a = e.Find<Transform>();
	m.b.b = e.Find<Renderable>();
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





void ModelDispatch(ComponentBase& b) {
	Ref<Connector> conn = b.GetEntity().Find<Connector>();
	if (conn) {
		conn->SignalModelSink();
	}
	else {
		LOG("error: ModelComponent::Dispatch: Connector not found");
	}
}

NAMESPACE_OULU_END

