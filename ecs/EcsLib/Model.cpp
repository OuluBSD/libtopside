#include "EcsLib.h"


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

void ModelComponent::Initialize() {
	
	RenderingSystemRef rend = this->GetEngine().Get<RenderingSystem>();
	rend->AddModel(AsRefT());
	
}

void ModelComponent::Uninitialize() {
	obj = 0;
	
	RenderingSystemRef rend = this->GetEngine().Get<RenderingSystem>();
	rend->RemoveModel(AsRefT());
	
}

bool ModelComponent::Arg(String key, Object value) {
	
	if (key == "builtin") {
		String name = value;
		ModelBuilder mb;
		if (name == "plane") {
			vec3 pos(-5,0,-5);
			vec2 size(10,10);
			mb.AddPlane(pos, size);
		}
		else if (name == "box") {
			vec3 pos(0,0,0);
			vec3 dim(2,2,2);
			mb.AddBox(pos, dim, true);
		}
		else if (name == "sphere") {
			vec3 pos(0,0,0);
			mb.AddSphere(pos, 2, 3, 3);
		}
		else if (name == "cylinder") {
			vec3 pos(0,0,0);
			mb.AddCylinder(pos, 2, 2);
		}
		else {
			LOG("ModelComponent::Arg: error: invalid model name '" + name + "'");
			return false;
		}
		loader = mb;
	}
	else return false;
	
	return true;
}

bool ModelComponent::Load(GfxDataState& state) {
	if (!obj) {
		obj = &state.CreateObject();
		if (!state.LoadModel(loader, *obj)) {
			LOG("ModelComponent::Load: error: model loading failed");
			return false;
		}
	}
	
	TransformRef trans = GetEntity()->Find<Transform>();
	if (trans) {
		mat4 pos = translate(trans->position);
		mat4 rot = rotate(trans->orientation);
		mat4 sz = scale(trans->size);
		obj->model = pos * rot * sz;
	}
	
	return true;
}

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

