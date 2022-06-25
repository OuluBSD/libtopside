#include "IGraphics.h"

NAMESPACE_PARALLEL_BEGIN


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
	
	mat4 ident = identity<mat4>();
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
	// copy texture ids
	static_assert(sizeof(tex_id) == sizeof(m.tex_id), "tex_id mismatch");
	memcpy(tex_id, m.tex_id, sizeof(tex_id));
	memcpy(tex_filter, m.tex_filter, sizeof(tex_filter));
}
	
template <class Gfx>
void DataObjectT<Gfx>::Paint(DataState& state) {
	if (!element_count)
		return;
	
	for(int i = 0; i < TEXTYPE_COUNT; i++) {
		int id = tex_id[i];
		int ch = TEXTYPE_OFFSET + i;
		Gfx::ActiveTexture(ch);
		if (id >= 0) {
			auto& tex = state.textures[id];
			Gfx::BindTextureRO(GVar::TEXTYPE_2D, tex);
		}
		else {
			Gfx::UnbindTexture(GVar::TEXTYPE_2D);
		}
		Gfx::DeactivateTexture();
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
DataStateT<Gfx>::DataStateT() {
	
}

template <class Gfx>
DataStateT<Gfx>::~DataStateT() {
	Free();
}

template <class Gfx>
void DataStateT<Gfx>::Free() {
	for (NativeColorBufferRef& t : textures)
		Gfx::DeleteTexture(t);
	textures.Clear();
}

template <class Gfx>
void DataStateT<Gfx>::Clear() {
	Free();
	objects.Clear();
}

template <class Gfx>
typename Gfx::DataObject& DataStateT<Gfx>::AddObject() {
	DataObject* p = new DataObject();
	p->SetState(this);
	objects.Add(p);
	p->id = objects.GetCount() - 1;
	RendVer1(OnRealizeObject, p->id);
	return *p;
}

template <class Gfx>
bool DataStateT<Gfx>::LoadModel(ModelLoader& l) {
	ASSERT(l.model);
	if (!l.model) return false;
	
	l.model->SetParent(&l);
    l.model->path = "";
    l.model->directory = "";
	
    ProcessNode(*l.model);
    
    return true;
}

template <class Gfx>
void DataStateT<Gfx>::ProcessNode(Model& model) {
	for (Mesh& mesh : model.meshes)
		ProcessMesh(mesh);
}

template <class Gfx>
void DataStateT<Gfx>::ProcessMesh(/*GfxDataObject& o, Model& mout,*/ Mesh& out) {
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
void DataStateT<Gfx>::Refresh(Model& m) {
	ProcessNode(m);
}

template <class Gfx>
bool DataStateT<Gfx>::LoadModel(ModelLoader& l, String path) {
	#ifdef flagASSIMP
	return LoadModelAssimp(l,  path);
	#endif
	return false;
}

#ifdef flagASSIMP
template <class Gfx>
bool DataStateT<Gfx>::LoadModelAssimp(ModelLoader& l, String path) {
	LOG("DataStateT::LoadModelAssimp: " << path);
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
	
    ProcessNode(*l.model, scene->mRootNode, scene);
    
    return true;
}

template <class Gfx>
bool DataStateT<Gfx>::LoadModelTextures(ModelLoader& l) {
	Model& m = *l.model;
	
	int prev_count = textures.GetCount();
	int count = m.textures.GetCount();
	textures.SetCount(count);
	for(int i = prev_count; i < count; i++) textures[i] = Null;
	
	for(int i = 0; i < m.textures.GetCount(); i++) {
		NativeColorBufferRef& buf = textures[i];
		ByteImage& tex = m.textures[i];
		
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
void DataStateT<Gfx>::ProcessNode(Model& model, aiNode *node, const aiScene *scene) {
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
void DataStateT<Gfx>::ProcessMesh(Model& mout, Mesh& out, aiMesh *mesh, const aiScene *scene) {
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
    if(mesh->mMaterialIndex >= 0) {
		aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
		
		for(int i = 1; i < TEXTYPE_COUNT; i++)
			LoadMaterialTextures(mout, out, material, i);
    }
	
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
void DataStateT<Gfx>::RefreshTexture(Model& model) {
	for (Mesh& mesh : model.meshes)
		RefreshTexture(mesh);
}

template <class Gfx>
void DataStateT<Gfx>::RefreshTexture(Mesh& out) {
	ASSERT(out.accel);
	if (!out.accel) return;
	DataObjectT<Gfx>* o = CastPtr<DataObjectT<Gfx>>(out.accel);
	ASSERT(o);
	if (!o) return;
	
	o->RefreshTexture(out);
}

template <class Gfx>
void DataStateT<Gfx>::LoadMaterialTextures(Model& mout, Mesh& out, aiMaterial *mat, int type) {
	for(unsigned int i = 0; i < mat->GetTextureCount((aiTextureType) type); i++) {
        if (out.tex_id[type] >= 0) {
            LOG("warning: ModelLoader: multiple textures per mesh: " << mout.path);
            break;
        }
        aiString str;
        mat->GetTexture((aiTextureType) type, i, &str);
        
        String path = AppendFileName(mout.directory, str.C_Str());
        mout.AddTextureFile(out, (TexType) type, path);
    }
}
#endif


//GFX_EXCPLICIT_INITIALIZE_CLASS(VertexShaderArgsT)
//GFX_EXCPLICIT_INITIALIZE_CLASS(FragmentShaderArgsT)
GFX3D_EXCPLICIT_INITIALIZE_CLASS(DataObjectT)
GFX3D_EXCPLICIT_INITIALIZE_CLASS(DataStateT)

NAMESPACE_PARALLEL_END
