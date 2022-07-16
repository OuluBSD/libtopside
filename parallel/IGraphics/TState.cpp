#include "IGraphics.h"

NAMESPACE_PARALLEL_BEGIN


template <class Gfx>
MaterialT<Gfx>::MaterialT() {
	for(int i = 0; i < TEXTYPE_COUNT; i++) {
		tex_id[i] = -1;
		tex_filter[i] = -1;
	}
}





template <class Gfx>
DataObjectT<Gfx>::DataObjectT() {
	vao = Null;
	vbo = Null;
	ebo = Null;
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
		vbo = Null;
		ebo = Null;
		vao = Null;
	}
}

template <class Gfx>
void DataObjectT<Gfx>::Refresh(Mesh& m) {
	//Free();
	
	mat4 ident = Identity<mat4>();
	scale = ident;
	model = ident;
	proj_override = ident;
	view_override = ident;
	
	// Create objects
	if (!vbo) {
		Gfx::GenVertexArray(vao);
		Gfx::GenVertexBuffer(vbo);
		Gfx::GenElementBuffer(ebo);
	}

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
		
		for(int i = 0; i < TEXTYPE_COUNT; i++) {
			int id = mat.tex_id[i];
			int ch = TEXTYPE_OFFSET + i;
			Gfx::ActiveTexture(ch);
			if (id >= 0) {
				auto& tex = state.textures.Get(id);
				Gfx::BindTextureRO(GVar::TEXTYPE_2D, tex);
			}
			else {
				Gfx::UnbindTexture(GVar::TEXTYPE_2D);
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
	Gfx::DrawVertexElements(element_count);
	
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
}

template <class Gfx>
void ModelStateT<Gfx>::Clear() {
	Free();
	objects.Clear();
}

template <class Gfx>
typename Gfx::DataObject& ModelStateT<Gfx>::AddObject() {
	DataObject* p = new DataObject();
	p->SetState(this);
	objects.Add(p);
	p->id = objects.GetCount() - 1;
	RendVer1(OnRealizeObject, p->id);
	return *p;
}

template <class Gfx>
MaterialT<Gfx>& ModelStateT<Gfx>::GetAddMaterial(int material_id) {
	return materials.GetAdd(material_id);
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
    
    return true;
}

template <class Gfx>
void ModelStateT<Gfx>::ProcessNode(Model& model) {
	for (Mesh& mesh : model.meshes)
		ProcessMesh(mesh);
}

template <class Gfx>
void ModelStateT<Gfx>::ProcessMesh(Mesh& out) {
	DataObject* obj = 0;
	if (!out.accel) {
		obj = &AddObject();
		out.accel = obj;
	}
	else {
		obj = CastPtr<DataObject>(out.accel);
		ASSERT_(obj, "Mesh is used in multiple gfx accelerators, which is not supported yet");
		if (!obj) return;
	}
	
	obj->Refresh(out);
}

template <class Gfx>
void ModelStateT<Gfx>::Refresh(Model& m) {
	ProcessNode(m);
}

template <class Gfx>
bool ModelStateT<Gfx>::LoadModel(ModelLoader& l, String path) {
	#ifdef flagASSIMP
	return LoadModelAssimp(l,  path);
	#endif
	return false;
}

#ifdef flagASSIMP
template <class Gfx>
bool ModelStateT<Gfx>::LoadModelAssimp(ModelLoader& l, String path) {
	LOG("ModelStateT::LoadModelAssimp: " << path);
    Assimp::Importer import_;
    const aiScene *scene = import_.ReadFile(path.Begin(), aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);
	
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        LOG("ERROR: assimp load failed: " << import_.GetErrorString());
        return false;
    }
	
	l.model = new Model();
	l.model->SetParent(&l);
    l.model->path = path;
    l.model->directory = GetFileDirectory(path);
	
    ProcessMaterials(*l.model, scene);
    ProcessNode(*l.model, scene->mRootNode, scene);
    
    return true;
}

template <class Gfx>
bool ModelStateT<Gfx>::LoadModelTextures(ModelLoader& l) {
	Model& m = *l.model;
	
	textures.Clear();
	
	for(int i = 0; i < m.textures.GetCount(); i++) {
		int id = m.textures.GetKey(i);
		NativeColorBufferRef& buf = textures.GetAdd(id);
		ByteImage& tex = m.textures[i].img;
		
		if (buf || tex.IsEmpty())
			continue;
		
		
		Gfx::GenTexture(buf);
		ASSERT(buf);
		
		Gfx::ActiveTexture(CHANNEL_NONE);
		Gfx::BindTextureRW(GVar::TEXTYPE_2D, buf);
		//not here, requires framebuffer: Gfx::TexParameteri(GVar::TEXTYPE_2D, GVar::FILTER_LINEAR, GVar::WRAP_REPEAT);
		Gfx::TexImage2D(tex);
		Gfx::UnbindTexture(GVar::TEXTYPE_2D);
		Gfx::GenerateMipmap(GVar::TEXTYPE_2D);
		Gfx::DeactivateTexture();
	}
	
    RefreshTexture(*l.model);
	
	return true;
}

template <class Gfx>
void ModelStateT<Gfx>::ProcessMaterials(Model& model, const aiScene *scene) {
	model.materials.Clear();
	for(int i = 0; i < scene->mNumMaterials; i++) {
		const aiMaterial* m = scene->mMaterials[i];
		ASSERT(m);
		TS::Material& mat = model.materials.Add(i);
		mat.id = i;
		ProcessMaterial(model, mat, m);
	}
	ProcessMaterials(model);
}

template <class Gfx>
void ModelStateT<Gfx>::ProcessMaterial(Model& model, TS::Material& m, const aiMaterial *mat) {
	for (int type = 0; type <= aiTextureType_UNKNOWN; type++) {
		int c = mat->GetTextureCount((aiTextureType) type);
		if (c > 1) {
			TODO
		}
		
		for(unsigned int i = 0; i < c; i++) {
			TexType textype = TEXTYPE_COUNT;
			switch (type) {
				#define TYPE(x) case aiTextureType_##x: textype = TEXTYPE_##x; break;
				TYPE(NONE)
				TYPE(DIFFUSE)
				TYPE(SPECULAR)
				TYPE(AMBIENT)
				TYPE(EMISSIVE)
				TYPE(HEIGHT)
				TYPE(NORMALS)
				TYPE(SHININESS)
				TYPE(OPACITY)
				TYPE(DISPLACEMENT)
				TYPE(LIGHTMAP)
				TYPE(REFLECTION)
				TYPE(UNKNOWN)
				#undef TYPE
			}
			if (textype == TEXTYPE_COUNT) continue;
			
	        if (m.tex_id[type] >= 0) {
	            LOG("warning: ModelLoader: multiple textures per mesh: " << model.path);
	            break;
	        }
	        aiString str;
	        str.Clear();
	        int r = mat->GetTexture((aiTextureType) type, i, &str);
	        
	        String path = AppendFileName(model.directory, str.C_Str());
	        Image img = StreamRaster::LoadFileAny(path);
	        m.tex_id[textype] = model.GetAddTexture(img, path);
	        m.tex_filter[textype] = 1;
	    }
	}
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
void ModelStateT<Gfx>::ProcessNode(Model& model, aiNode *node, const aiScene *scene) {
	// process all the node's meshes (if any)
    for(unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        ProcessMesh(model, model.meshes.Add(), mesh, scene);
    }
    // then do the same for each of its children
    for(unsigned int i = 0; i < node->mNumChildren; i++) {
        ProcessNode(model, node->mChildren[i], scene);
    }
}

template <class Gfx>
void ModelStateT<Gfx>::ProcessMesh(Model& model, Mesh& out, aiMesh *mesh, const aiScene *scene) {
	out.vertices.SetCount(mesh->mNumVertices);
	
    for(unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex& vertex = out.vertices[i];
        
        // process vertex positions, normals and texture coordinates
        vertex.position[0] = mesh->mVertices[i][0];
		vertex.position[1] = mesh->mVertices[i][1];
		vertex.position[2] = mesh->mVertices[i][2];
		
		vertex.normal[0] = mesh->mNormals[i][0];
		vertex.normal[1] = mesh->mNormals[i][1];
		vertex.normal[2] = mesh->mNormals[i][2];
		
		// does the mesh contain texture coordinates?
		
		if(mesh->mTextureCoords[0]) {
		    vertex.tex_coord[0] = mesh->mTextureCoords[0][i][0];
		    vertex.tex_coord[1] = mesh->mTextureCoords[0][i][1];
		}
		else
		    vertex.tex_coord = vec2(0.0f, 0.0f);
		
		ASSERT(vertex.tex_coord[0] >= 0.0f && vertex.tex_coord[0] <= 1.0f);
		ASSERT(vertex.tex_coord[1] >= 0.0f && vertex.tex_coord[1] <= 1.0f);
    }
    
    // process indices
    out.indices.SetCount(0);
    out.indices.Reserve(mesh->mNumFaces*3);
    for(unsigned int i = 0; i < mesh->mNumFaces; i++) {
	    aiFace face = mesh->mFaces[i];
	    for(unsigned int j = 0; j < face.mNumIndices; j++)
	        out.indices.Add(face.mIndices[j]);
	}
	
    // process material
    out.material = mesh->mMaterialIndex;
	
	GfxDataObject* o;
	if (!out.accel) {
		o = &CreateObject();
		out.accel = o;
	}
	else
		o = CastPtr<GfxDataObject>(out.accel);
	o->Refresh(out);
}

template <class Gfx>
void ModelStateT<Gfx>::RefreshTexture(Model& model) {
	for (Mesh& mesh : model.meshes)
		RefreshTexture(mesh);
}

template <class Gfx>
void ModelStateT<Gfx>::RefreshTexture(Mesh& out) {
	ASSERT(out.accel);
	if (!out.accel) return;
	DataObjectT<Gfx>* o = CastPtr<DataObjectT<Gfx>>(out.accel);
	ASSERT(o);
	if (!o) return;
	
	o->RefreshTexture(out);
}











template <class Gfx>
DataStateT<Gfx>::DataStateT() {
	
}

template <class Gfx>
DataStateT<Gfx>::~DataStateT() {
	Clear();
}

template <class Gfx>
ModelStateT<Gfx>& DataStateT<Gfx>::AddModelT() {
	int id = models.IsEmpty() ? 0 : models.Top().id + 1;
	ModelState& ms = models.Add(id);
	ms.id = id;
	return ms;
}

template <class Gfx>
GfxModelState& DataStateT<Gfx>::GetModel(int i) {
	return models.Get(i);
}

template <class Gfx>
PipelineStateT<Gfx>& DataStateT<Gfx>::GetAddPipeline(String name) {
	int i = pipelines.Find(name);
	if (i >= 0)
		return pipelines[i];
	PipelineStateT<Gfx>& ps = pipelines.Add(name);
	ps.owner = this;
	ps.name = name;
	return ps;
}

template <class Gfx>
void DataStateT<Gfx>::Clear() {
	models.Clear();
	pipelines.Clear();
}



#endif


//GFX_EXCPLICIT_INITIALIZE_CLASS(VertexShaderArgsT)
//GFX_EXCPLICIT_INITIALIZE_CLASS(FragmentShaderArgsT)
GFX3D_EXCPLICIT_INITIALIZE_CLASS(DataObjectT)
GFX3D_EXCPLICIT_INITIALIZE_CLASS(ModelStateT)
GFX3D_EXCPLICIT_INITIALIZE_CLASS(DataStateT)

NAMESPACE_PARALLEL_END
