#include "EcsLib.h"


NAMESPACE_ECS_BEGIN


void ModelComponent::Initialize() {
	color = one<vec4>();
	prefab_name.Clear();
	offset = zero<vec3>();
	scale = one<vec3>();
	pitch = 0;
	yaw = 0;
	roll = 0;
	ext_model = Identity<mat4>();
	have_ext_model = false;
	model_changed = false;
	
	RenderingSystemRef rend = this->GetEngine().Get<RenderingSystem>();
	rend->AddModel(AsRefT());
	
}

void ModelComponent::Uninitialize() {
	Clear();
	
	RenderingSystemRef rend = this->GetEngine().Get<RenderingSystem>();
	rend->RemoveModel(AsRefT());
	
}

void ModelComponent::SetEnabled(bool enable) {
	if (!enable && always_enabled) {
		enable = true;
	}
	Enableable::SetEnabled(enable);
}

bool ModelComponent::Arg(String key, Object value) {
	
	if (key == "builtin") {
		Vector<String> parts = Split(value.ToString(), ",");
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
			float rad = 1 < parts.GetCount() ? (float)StrDbl(parts[1]) : 1.0f;
			float len = 2 < parts.GetCount() ? (float)StrDbl(parts[2]) : 0.2f;
			vec3 pos(0,0,0);
			mb.AddCylinder(pos, rad, len);
		}
		else if (name == "skybox") {
			load_skybox = true;
			return true;
		}
		else {
			LOG("ModelComponent::Arg: error: invalid model name '" + name + "'");
			return false;
		}
		model_changed = true;
		loader = mb;
		model = loader.GetModel();
	}
	else if (key == "skybox.diffuse") {
		skybox_diffuse = value;
	}
	else if (key == "skybox.irradiance") {
		skybox_irradiance = value;
	}
	else if (key == "texture") {
		Ref<Model> mdl = loader.GetModel();
		if (mdl && mdl->GetMeshCount()) {
			String path = RealizeShareFile(value);
			Image img = StreamRaster::LoadFileAny(path);
			if (img) {
				Mesh& m = mdl->meshes[0];
				mdl->SetTexture(m, TEXTYPE_DIFFUSE, img, path);
			}
		}
	}
	else if (key == "path") {
		String path = RealizeShareFile(value);
		if (!loader.LoadModel(path)) {
			LOG("ModelComponent::Arg: error: loading model file failed: " << path);
			return false;
		}
		model_changed = true;
		model = loader.GetModel();
		return true;
	}
	else if (key == "x") {offset[0] = value.ToFloat(); RefreshExtModel();}
	else if (key == "y") {offset[1] = value.ToFloat(); RefreshExtModel();}
	else if (key == "z") {offset[2] = value.ToFloat(); RefreshExtModel();}
	else if (key == "cx") {scale[0] = value.ToFloat(); RefreshExtModel();}
	else if (key == "cy") {scale[1] = value.ToFloat(); RefreshExtModel();}
	else if (key == "cz") {scale[2] = value.ToFloat(); RefreshExtModel();}
	else if (key == "pitch") {pitch = DEG2RADf(value.ToFloat()); RefreshExtModel();}
	else if (key == "yaw") {yaw = DEG2RADf(value.ToFloat()); RefreshExtModel();}
	else if (key == "roll") {roll = DEG2RADf(value.ToFloat()); RefreshExtModel();}
	else if (key == "always.enabled") {always_enabled = value.ToString() == "true";}
	else {
		LOG("ModelComponent::Arg: error: invalid key '" << key << "'");
		return false;
	}
	
	return true;
}

void ModelComponent::Create() {
	loader.Create();
	model = loader.GetModel();
	model_changed = true;
}

void ModelComponent::MakeBall(const vec3& pos, float radius) {
	ASSERT(!model);
	ModelBuilder mb;
	mb.AddSphere(pos, radius);
	model_changed = true;
	loader = mb;
	model = loader.GetModel();
}

void ModelComponent::MakeCylinder(const vec3& pos, float radius, float length) {
	ASSERT(!model);
	ModelBuilder mb;
	mb.AddCylinder(pos, radius, length);
	model_changed = true;
	loader = mb;
	model = loader.GetModel();
}

void ModelComponent::RefreshExtModel() {
	if (dbg) {
		LOG("debug");
	}
	have_ext_model = true;
	mat4 rotate = AxesMat(yaw, pitch, roll);
	mat4 tran = Translate(offset);
	mat4 scale = TS::Scale(this->scale);
	this->ext_model = rotate * tran * scale;
}

void ModelComponent::SetRotation(float yaw, float pitch, float roll) {
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

void ModelComponent::SetModel(ModelRef m) {
	model = m;
	loader.Clear();
	prefab_name.Clear();
	model_changed = true;
}

void ModelComponent::SetModelMatrix(const mat4& m) {
	if (dbg) {
		LOG("debug");
	}
	ext_model = m;
	have_ext_model = true;
}

void ModelComponent::Clear() {
	if (gfx_state && gfx_hash > 0) {
		gfx_state->GetModel(gfx_hash).Clear();
	}
	model.Clear();
	loader.Clear();
	model_changed = true;
	gfx_state = 0;
	gfx_hash = 0;
}

bool ModelComponent::Load(GfxDataState& state) {
	if (gfx_state) {
		// TODO if differs, reset gfx_hash etc.
		ASSERT(gfx_state == &state);
	}
	
	gfx_state = &state;
	
	
	// TODO merge dupliate ObjViewProgT<Gfx>::Render
	if (load_skybox) {
		load_skybox = false;
		
		GfxModelState& skybox = state.AddModel();
		gfx_hash = skybox.id;
		
		ASSERT(skybox.id >= 0);
		float skybox_sz = 1e8;
		Index<String> ext_list; ext_list << "" << ".png" << ".jpg";
		Index<String> dir_list; dir_list << "" << "imgs" << "imgs/skybox";
		ModelBuilder mb;
		Mesh& box_mesh = mb.AddBox(vec3(0), vec3(skybox_sz), true, true);
		Model& box = mb;
		
		if (!box.LoadCubemapFile(box_mesh, TEXTYPE_CUBE_DIFFUSE, skybox_diffuse)) {
			LOG("ModelComponent::Load: error: could not load skybox diffuse image '" << skybox_diffuse << "'");
			return false;
		}
		if (!box.LoadCubemapFile(box_mesh, TEXTYPE_CUBE_IRRADIANCE, skybox_irradiance)) {
			LOG("ModelComponent::Load: error: could not load skybox irradiance image '" << skybox_irradiance << "'");
			return false;
		}
		
		loader = mb;
		if (!skybox.LoadModel(loader)) {
			RTLOG("ModelComponent::Load: error: could not load skybox");
			return false;
		}
		
		skybox.env_material = skybox.GetMaterialKey(0);
		skybox.env_material_model = skybox.id;
		
		bool b = skybox.SetProgram("sky");
		ASSERT(b);
		
		if (state.env_material_model == 0)
			state.env_material_model = skybox.id;
		
		this->model = loader.GetModel();
		model_changed = false;
	}
	
	// If model is not loaded to the state
	if (gfx_hash == 0) {
		if (dbg) {
			LOG("debug");
		}
		
		if (model) {
			auto& mdl = state.AddModel();
			gfx_hash = mdl.id;
			mdl.LoadModel(*model);
		}
		else if (loader) {
			auto& mdl = state.AddModel();
			gfx_hash = mdl.id;
			if (!mdl.LoadModel(loader)) {
				LOG("ModelComponent::Load: error: model loading failed");
				return false;
			}
			model = loader.GetModel();
		}
		else if (!prefab_name.IsEmpty()) {
			String path = KnownModelNames::GetPath(prefab_name);
			auto& mdl = state.AddModel();
			gfx_hash = mdl.id;
			if (!loader.LoadModel(path))
				return false;
			if (!mdl.LoadModel(loader))
				return false;
			model = loader.GetModel();
		}
		else {
			return false;
		}
	}
	else if (model_changed) {
		if (dbg) {
			LOG("debug");
		}
		
		if (model) {
			state.RealizeModel(gfx_hash).Refresh(*model);
		}
		else {
			state.RealizeModel(gfx_hash).Clear();
		}
	}
	else {
		if (dbg) {
			LOG("debug");
		}
	}
	model_changed = false;
	
	
	mat4 model_mat;
	TransformRef trans = GetEntity()->Find<Transform>();
	if (trans) {
		mat4 pos = Translate(trans->data.position);
		mat4 rot = QuatMat(trans->data.orientation);
		mat4 sz = TS::Scale(trans->size);
		
		model_mat = pos * rot * sz;
		
		if (trans->verbose) {
			DUMP(trans->data.position);
		}
		
		if (have_ext_model)
			model_mat *= ext_model;
		
	}
	else if (have_ext_model)
		model_mat = ext_model;
	else
		model_mat = Identity<mat4>();
		
	if (!model)
		return false;
	
	bool is_visible = IsEnabled();
	
	static thread_local Vector<GfxMesh*> meshes;
	meshes.SetCount(0);
	auto& mdl_state = state.GetModel(gfx_hash);
	int obj_count = mdl_state.GetObjectCount();
	for(int i = 0; i < obj_count; i++) {
		GfxDataObject& obj = mdl_state.GetObject(i);
		obj.is_visible = is_visible;
		obj.model = model_mat;
		obj.color = color;
	}
	
	return true;
}

void ModelComponent::SetPrefabModel(String prefab) {
	prefab_name = prefab;
}


NAMESPACE_ECS_END

