#include "IGraphics.h"

NAMESPACE_PARALLEL_BEGIN


template <class Gfx>
MaterialT<Gfx>::MaterialT() {
	for(int i = 0; i < TEXTYPE_COUNT; i++) {
		tex_id[i] = -1;
		tex_filter[i] = GVar::DEFAULT_FILTER;
	}
}





template <class Gfx>
DataObjectT<Gfx>::DataObjectT() {
	vao = 0;
	vbo = 0;
	ebo = 0;
}

template <class Gfx>
DataObjectT<Gfx>::~DataObjectT() {
	Free();
}

template <class Gfx>
void DataObjectT<Gfx>::Free() {
	if (vbo) {
		Gfx::DeleteVertexBuffer(vbo);
		Gfx::DeleteElementBuffer(ebo);
		Gfx::DeleteVertexArray(vao);
		vbo = 0;
		ebo = 0;
		vao = 0;
	}
}

template <class Gfx>
void DataObjectT<Gfx>::Refresh(Mesh& m) {
	//Free();
	src = &m;
	
	mat4 ident = Identity<mat4>();
	scale = ident;
	model = ident;
	proj_override = ident;
	view_override = ident;
	use_quad = m.use_quad;
	
	// Create objects
	if (!vbo) {
		Gfx::GenVertexArray(vao);
		Gfx::GenVertexBuffer(vbo);
		Gfx::GenElementBuffer(ebo);
	}
	
	if (!m.vertices.IsEmpty() &&
		!m.indices.IsEmpty()) {
		
		// Set vertex array object data
		Gfx::BindVertexArray(vao);
		Gfx::BindVertexBuffer(vbo);
		Gfx::VertexBufferData(m.vertices);
	
		// Set element buffer object data
		Gfx::BindElementBuffer(ebo);
		Gfx::ElementBufferData(m.indices);
		element_count = m.indices.GetCount();
	
		Gfx::SetupVertexStructure();
		
		Gfx::UnbindVertexBuffer();
		Gfx::UnbindElementBuffer();
		Gfx::UnbindVertexArray();
	}
	
}

template <class Gfx>
void DataObjectT<Gfx>::RefreshTexture(Mesh& m) {
	material = m.material;
}
	
template <class Gfx>
void DataObjectT<Gfx>::Paint(ModelState& state) {
	if (!element_count)
		return;
	
	if (material >= 0) {
		MaterialT<Gfx>& mat = state.materials.Get(material);
		
		for(int i = 0; i < TEXTYPE_CUBE_DIFFUSE; i++) {
			int id = mat.tex_id[i];
			int ch = TEXTYPE_OFFSET + i;
			Gfx::ActiveTexture(ch);
			if (id >= 0) {
				auto& tex = state.textures.Get(id);
				Gfx::BindTextureRO(GVar::TEXMODE_2D, tex);
			}
			else {
				Gfx::UnbindTexture(GVar::TEXMODE_2D);
			}
			Gfx::DeactivateTexture();
		}
		for(int i = TEXTYPE_CUBE_DIFFUSE; i < TEXTYPE_COUNT; i++) {
			int id = mat.tex_id[i];
			int ch = TEXTYPE_OFFSET + i;
			Gfx::ActiveTexture(ch);
			if (id >= 0) {
				auto& tex = state.cube_textures.Get(id);
				Gfx::BindTextureRO(GVar::TEXMODE_CUBE_MAP, tex);
			}
			else {
				Gfx::UnbindTexture(GVar::TEXMODE_CUBE_MAP);
			}
			Gfx::DeactivateTexture();
		}
	}
	
	// bind vbos for vertex array and index array
	Gfx::BindVertexArray(vao);
	Gfx::BindVertexBuffer(vbo);
	Gfx::BindElementBuffer(ebo);
	Gfx::ActivateVertexStructure();
	
	// draw 6 faces using offset of index array
	Gfx::DrawVertexElements(element_count, use_quad);
	
	Gfx::DeactivateVertexStructure();
	
	// bind with 0, so, switch back to normal pointer operation
	Gfx::UnbindVertexBuffer();
	Gfx::UnbindElementBuffer();
	Gfx::UnbindVertexArray();
}










template <class Gfx>
ModelStateT<Gfx>::ModelStateT() {
	
}

template <class Gfx>
ModelStateT<Gfx>::~ModelStateT() {
	Free();
}

template <class Gfx>
void ModelStateT<Gfx>::Free() {
	for (NativeColorBufferRef& t : textures.GetValues())
		Gfx::DeleteTexture(t);
	textures.Clear();
	
	for (NativeColorBufferRef& t : cube_textures.GetValues())
		Gfx::DeleteTexture(t);
	cube_textures.Clear();
}

template <class Gfx>
void ModelStateT<Gfx>::Clear() {
	Free();
	objects.Clear();
	materials.Clear();
	env_material = -1;
	env_material_model = -1;
	prog = -1;
}

template <class Gfx>
int ModelStateT<Gfx>::GetMaterialKey(int i) const {
	return materials.GetKey(i);
}

template <class Gfx>
typename Gfx::DataObject& ModelStateT<Gfx>::AddObject() {
	DataObject* p = new DataObject();
	p->SetState(this);
	objects.Add(p);
	p->id = objects.GetCount() - 1;
	return *p;
}

template <class Gfx>
MaterialT<Gfx>& ModelStateT<Gfx>::GetAddMaterial(int material_id) {
	int i = materials.Find(material_id);
	if (i >= 0)
		return materials[i];
	MaterialT<Gfx>& m = materials.Add(material_id);
	m.id = material_id;
	return m;
}

template <class Gfx>
MaterialT<Gfx>& ModelStateT<Gfx>::AddMaterial() {
	int material_id = materials.IsEmpty() ? 0 : materials.Top().id + 1;
	MaterialT<Gfx>& m = materials.Add(material_id);
	m.id = material_id;
	return m;
}

template <class Gfx>
bool ModelStateT<Gfx>::SetProgram(String name) {
	int id = owner->dictionary.Find(name);
	if (id < 0)
		return false;
	this->prog = id;
	return true;
}

template <class Gfx>
bool ModelStateT<Gfx>::LoadModel(ModelLoader& l) {
	ASSERT(l.model);
	if (!l.model) return false;
	
	l.model->SetParent(&l);
    l.model->path = "";
    l.model->directory = "";
	
    ProcessNode(*l.model);
    ProcessMaterials(*l.model);
    LoadModelTextures(*l.model);
    
    return true;
}

template <class Gfx>
bool ModelStateT<Gfx>::LoadModel(Model& m) {
    ProcessNode(m);
    ProcessMaterials(m);
    LoadModelTextures(m);
    
    return true;
}

template <class Gfx>
void ModelStateT<Gfx>::ProcessNode(Model& model) {
	for (Mesh& mesh : model.meshes)
		ProcessMesh(mesh);
}

template <class Gfx>
void ModelStateT<Gfx>::ProcessMesh(Mesh& out) {
	for (DataObject& obj : objects) {
		if (obj.src == &out) {
			obj.Refresh(out);
			return;
		}
	}
	DataObject& obj = AddObject();
	obj.Refresh(out);
}

template <class Gfx>
void ModelStateT<Gfx>::Refresh(Model& m) {
	ProcessNode(m);
}

template <class Gfx>
bool ModelStateT<Gfx>::LoadModelTextures(Model& m) {
	Free();
	
	for(int i = 0; i < m.textures.GetCount(); i++) {
		int id = m.textures.GetKey(i);
		NativeColorBufferRef& buf = textures.GetAdd(id);
		ByteImage& tex = m.textures[i].img;
		
		if (buf || tex.IsEmpty())
			continue;
		
		if (tex.channels < 3)
			tex.ToGrayscaleRGB();
		
		Gfx::GenTexture(buf);
		ASSERT(buf);
		
		Gfx::ActiveTexture(CHANNEL_NONE);
		Gfx::BindTextureRW(GVar::TEXMODE_2D, buf);
		//not here, requires framebuffer: Gfx::TexParameteri(GVar::TEXMODE_2D, GVar::FILTER_LINEAR, GVar::WRAP_REPEAT);
		Gfx::TexImage2D(tex);
		Gfx::GenerateMipmap(GVar::TEXMODE_2D);
		Gfx::UnbindTexture(GVar::TEXMODE_2D);
		Gfx::DeactivateTexture();
	}
	
	for(int i = 0; i < m.cube_textures.GetCount(); i++) {
		int id = m.cube_textures.GetKey(i);
		NativeColorBufferRef& buf = cube_textures.GetAdd(id);
		if (buf)
			continue;
		
		Gfx::GenTexture(buf);
		ASSERT(buf);
		Gfx::ActiveTexture(CHANNEL_NONE);
		Gfx::BindTextureRW(GVar::TEXMODE_CUBE_MAP, buf);
		for(int j = 0; j < 6; j++) {
			GVar::TextureMode tex_type = (GVar::TextureMode)(GVar::TEXMODE_CUBE_MAP_SIDE_0 + j);
			
			ByteImage& tex = m.cube_textures[i].img[j];
			if (tex.IsEmpty())
				continue;
				
			if (tex.channels < 3)
				tex.ToGrayscaleRGB();
			
			Gfx::SetTexture(
					tex_type,
					tex.sz,
					GVar::Sample::SAMPLE_U8,
					tex.channels,
					tex.Begin());
		}
		Gfx::GenerateMipmap(GVar::TEXMODE_CUBE_MAP);
		Gfx::UnbindTexture(GVar::TEXMODE_CUBE_MAP);
		Gfx::DeactivateTexture();
	}
	
	
    RefreshTexture(m);
	
	return true;
}

template <class Gfx>
void ModelStateT<Gfx>::ProcessMaterials(Model& model) {
	
	for(int i = 0; i < model.materials.GetCount(); i++) {
		TS::Material& mat = model.materials[i];
		ASSERT(mat.id >= 0);
		MaterialT<Gfx>& gfx_mat = materials.GetAdd(mat.id);
		gfx_mat.id = mat.id;
		for(int j = 0; j < TEXTYPE_COUNT; j++) {
			gfx_mat.tex_id[j] = mat.tex_id[j];
			gfx_mat.tex_filter[j] = mat.tex_filter[j];
			ASSERT(gfx_mat.tex_id[j] < 0 || gfx_mat.tex_filter[j] >= 0);
		}
	}
}

template <class Gfx>
void ModelStateT<Gfx>::RefreshTexture(Model& model) {
	for (Mesh& mesh : model.meshes)
		RefreshTexture(mesh);
}

template <class Gfx>
void ModelStateT<Gfx>::RefreshTexture(Mesh& out) {
	for (DataObject& obj : objects) {
		if (obj.src == &out) {
			obj.RefreshTexture(out);
			return;
		}
	}
}











template <class Gfx>
DataStateT<Gfx>::DataStateT() {
	
}

template <class Gfx>
DataStateT<Gfx>::~DataStateT() {
	Clear();
}

template <class Gfx>
GfxModelState& DataStateT<Gfx>::RealizeModel(hash_t link) {
	int i = models.Find(link);
	if (i < 0) {
		ModelState& ms = models.Add(link);
		ms.owner = this;
		ms.id = link;
		return ms;
	}
	else return models[i];
}

template <class Gfx>
ModelStateT<Gfx>& DataStateT<Gfx>::AddModelT() {
	int id = models.IsEmpty() ? 0 : models.Top().id + 1;
	ModelState& ms = models.Add(id);
	ms.owner = this;
	ms.id = id;
	return ms;
}

template <class Gfx>
GfxModelState& DataStateT<Gfx>::GetModel(int i) {
	return models.Get(i);
}

template <class Gfx>
PipelineStateT<Gfx>& DataStateT<Gfx>::GetAddPipeline(String name) {
	int id = dictionary.FindAdd(name);
	int i = pipelines.Find(id);
	if (i >= 0)
		return pipelines[i];
	PipelineStateT<Gfx>& ps = pipelines.Add(id);
	ps.owner = this;
	ps.name = name;
	return ps;
}

template <class Gfx>
PipelineStateT<Gfx>* DataStateT<Gfx>::FindPipeline(String name) {
	int id = dictionary.Find(name);
	if (id < 0)
		return 0;
	int i = pipelines.Find(id);
	if (i < 0)
		return 0;
	return &pipelines[i];
}

template <class Gfx>
void DataStateT<Gfx>::Clear() {
	models.Clear();
	pipelines.Clear();
}




//GFX_EXCPLICIT_INITIALIZE_CLASS(VertexShaderArgsT)
//GFX_EXCPLICIT_INITIALIZE_CLASS(FragmentShaderArgsT)
GFX3D_EXCPLICIT_INITIALIZE_CLASS(DataObjectT)
GFX3D_EXCPLICIT_INITIALIZE_CLASS(ModelStateT)
GFX3D_EXCPLICIT_INITIALIZE_CLASS(DataStateT)

NAMESPACE_PARALLEL_END
