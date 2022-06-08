#include "EcsLib.h"


NAMESPACE_ECS_BEGIN

#if 0

/*void PrimitiveShape::SetShape(ShapeId type, const vec2& ax_vec) {
	shape.Create(type, ax_vec);
	
	model = new Model();
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
	loaded = 0;
	
	RenderingSystemRef rend = this->GetEngine().Get<RenderingSystem>();
	rend->RemoveModel(AsRefT());
	
}

bool ModelComponent::Arg(String key, Object value) {
	
	if (key == "builtin") {
		Vector<String> parts = Split((String)value, ",");
		if (parts.IsEmpty()) return false;
		String name = parts[0];
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
			float rad = 1 < parts.GetCount() ? StrDbl(parts[1]) : 1.0;
			float len = 2 < parts.GetCount() ? StrDbl(parts[2]) : 0.2;
			vec3 pos(0,0,0);
			mb.AddCylinder(pos, rad, len);
		}
		else {
			LOG("ModelComponent::Arg: error: invalid model name '" + name + "'");
			return false;
		}
		loader = mb;
	}
	else if (key == "x") {offset[0] = value.ToDouble(); RefreshExtModel();}
	else if (key == "y") {offset[1] = value.ToDouble(); RefreshExtModel();}
	else if (key == "z") {offset[2] = value.ToDouble(); RefreshExtModel();}
	else if (key == "cx") {scale[0] = value.ToDouble(); RefreshExtModel();}
	else if (key == "cy") {scale[1] = value.ToDouble(); RefreshExtModel();}
	else if (key == "cz") {scale[2] = value.ToDouble(); RefreshExtModel();}
	else if (key == "pitch") {pitch = DEG2RAD(value.ToDouble()); RefreshExtModel();}
	else if (key == "yaw") {yaw = DEG2RAD(value.ToDouble()); RefreshExtModel();}
	else if (key == "roll") {roll = DEG2RAD(value.ToDouble()); RefreshExtModel();}
	else return false;
	
	return true;
}

void ModelComponent::MakeCylinder(const vec3& pos, float radius, float length) {
	ModelBuilder mb;
	mb.AddCylinder(pos, radius, length);
	loader = mb;
}

void ModelComponent::RefreshExtModel() {
	have_ext_model = true;
	mat4 rotate = YawPitchRoll(pitch, yaw, roll);
	mat4 tran = translate(offset);
	mat4 scale = TS::scale(this->scale);
	this->ext_model = rotate * tran * scale;
}

void ModelComponent::SetRotation(float pitch, float yaw, float roll) {
	this->pitch = pitch;
	this->yaw = yaw;
	this->roll = roll;
	RefreshExtModel();
}

void ModelComponent::SetTranslation(const vec3& v) {
	this->offset = v;
	RefreshExtModel();
}

void ModelComponent::SetScale(const vec3& v) {
	this->scale = v;
	RefreshExtModel();
}

bool ModelComponent::Load(GfxDataState& state) {
	
	if (!loaded) {
		if (!loader && !prefab_name.IsEmpty()) {
			String path = KnownModelNames::GetPath(prefab_name);
			if (!state.LoadModel(loader, path))
				return false;
		}
		else if (loader) {
			if (!state.LoadModel(loader)) {
				LOG("ModelComponent::Load: error: model loading failed");
				return false;
			}
		}
		else {
			LOG("ModelComponent::Load: error: nothing to load");
			return false;
		}
		loaded = true;
	}
	else if (model_changed) {
		Ref<Model> m = loader.GetModel();
		if (m) {
			//state.ProcessNode(*m);
			state.Refresh(*m);
		}
	}
	
	model_changed = false;
	
	mat4 model;
	TransformRef trans = GetEntity()->Find<Transform>();
	if (trans) {
		mat4 pos = translate(trans->position);
		mat4 rot = rotate(trans->orientation);
		mat4 sz = TS::scale(trans->size);
		/*if (have_ext_model) {
			pos *= translate(offset);
			rot *= YawPitchRoll(pitch, yaw, roll);
			sz  *= TS::scale(this->scale);
		}*/
		model = pos * rot * sz;
	}
	else if (have_ext_model)
		model = ext_model;
	else
		model = identity<mat4>();
	
	if (have_ext_model)
		model *= ext_model;
		
	Ref<Model> mesh = loader.GetModel();
	if (!mesh)
		return false;
	
	bool is_visible = IsEnabled();
	
	static thread_local Vector<GfxMesh*> meshes;
	meshes.SetCount(0);
	mesh->GetGfxMeshes(meshes);
	for (GfxMesh* m : meshes) {
		GfxDataObject* obj = CastPtr<GfxDataObject>(m);
		if (!obj)
			continue;
		
		obj->is_visible = is_visible;
		obj->model = model;
		obj->color = color;
	}
	
	return true;
}

void ModelComponent::SetPrefabModel(String prefab) {
	prefab_name = prefab;
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

