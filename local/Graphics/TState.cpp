#include "Graphics.h"

NAMESPACE_TOPSIDE_BEGIN


template <class Gfx>
DataObjectT<Gfx>::DataObjectT() {
	vao = Null;
	vbo = Null;
	ebo = Null;
}

template <class Gfx>
DataObjectT<Gfx>::~DataObjectT() {
	FreeOgl();
}

template <class Gfx>
void DataObjectT<Gfx>::Refresh(Mesh& m) {
	ASSERT(!vao && !vbo && !ebo);

	// Create objects
	Gfx::GenVertexArray(vao);
	Gfx::GenVertexBuffer(vbo);
	Gfx::GenElementBuffer(ebo);

	// Set vertex array object data
	Gfx::BindVertexArray(vao);
	Gfx::BindVertexBuffer(vbo);
	Gfx::VertexBufferData(m.vertices);

	// Set element buffer object data
	Gfx::BindElementBuffer(ebo);
	Gfx::ElementBufferData(m.indices);
	element_count = m.indices.GetCount();

	Gfx::SetupVertexStructure();
	
	Gfx::UnbindVertexArray();
}

template <class Gfx>
void DataObjectT<Gfx>::Paint() {
	ASSERT(element_count > 0)
	if (!element_count)
		return;
	
	// bind vbos for vertex array and index array
	Gfx::BindVertexArray(vao);
	Gfx::GenElementBuffer(ebo);
	Gfx::ActivateVertexStructure();
	
	// draw 6 faces using offset of index array
	Gfx::DrawVertexElements(element_count);
	
	Gfx::DeactivateVertexStructure();
	
	// bind with 0, so, switch back to normal pointer operation
	Gfx::UnbindVertexArray();
}






template <class Gfx>
DataStateT<Gfx>::DataStateT() {
	
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
bool DataStateT<Gfx>::LoadModel(ModelLoader& l, String path) {
	return LoadModelAssimp(l, AddObject(), path);
}

#ifdef flagASSIMP
template <class Gfx>
bool DataStateT<Gfx>::LoadModelAssimp(ModelLoader& l, DataObject& o, String path) {
	LOG("DataStateT::LoadModelAssimp: " << path);
    Assimp::Importer import_;
    const aiScene *scene = import_.ReadFile(path.Begin(), aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);
	
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        LOG("ERROR: assimp load failed: " << import_.GetErrorString());
        return false;
    }
	
	l.model = new ModelMesh();
	l.model->SetParent(&l);
    l.model->path = path;
    l.model->directory = GetFileDirectory(path);
	
    ProcessNode(o, *l.model, scene->mRootNode, scene);
    
    return true;
}

template <class Gfx>
void DataStateT<Gfx>::ProcessNode(GfxDataObject& o, ModelMesh& model, aiNode *node, const aiScene *scene) {
	// process all the node's meshes (if any)
    for(unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        ProcessMesh(o, model, model.meshes.Add(), mesh, scene);
    }
    // then do the same for each of its children
    for(unsigned int i = 0; i < node->mNumChildren; i++) {
        ProcessNode(o, model, node->mChildren[i], scene);
    }
}

template <class Gfx>
void DataStateT<Gfx>::ProcessMesh(GfxDataObject& o, ModelMesh& mout, Mesh& out, aiMesh *mesh, const aiScene *scene) {
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
    }
    
    // process indices
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

	o.Refresh(out);
}

template <class Gfx>
void DataStateT<Gfx>::LoadMaterialTextures(ModelMesh& mout, Mesh& out, aiMaterial *mat, int type) {
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


GFX_EXCPLICIT_INITIALIZE_CLASS(VertexShaderArgsT)
GFX_EXCPLICIT_INITIALIZE_CLASS(FragmentShaderArgsT)
GFX_EXCPLICIT_INITIALIZE_CLASS(DataObjectT)
GFX_EXCPLICIT_INITIALIZE_CLASS(DataStateT)

NAMESPACE_TOPSIDE_END
