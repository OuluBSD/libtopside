#include "Geometry.h"


NAMESPACE_TOPSIDE_BEGIN


bool ModelMesh::AddTextureFile(int mesh_i, TexType type, String path) {
	if (mesh_i < 0 || mesh_i >= meshes.GetCount())
		return false;
	return AddTextureFile(meshes[mesh_i], type, path);
}

bool ModelMesh::AddTextureFile(Mesh& mesh, TexType type, String path){
	if (FileExists(path)) {
        Image src = StreamRaster::LoadFileAny(path);
        return SetTexture(mesh, type, src);
    }
	return false;
}

bool ModelMesh::SetTexture(Mesh& mesh, TexType type, Image img) {
	if (IsPositive(img.GetSize())) {
        mesh.tex_id[type] = textures.GetCount();
        textures.Add().Set(img);
        return true;
    }
    return false;
}

void ModelMesh::MakeModel(Shape2DWrapper& shape) {
	ASSERT(shape.shape);
	if (shape.shape) {
		MAKE_STATIC_LOCAL(Vector<tri3>, faces);
		shape.shape->GetFaces(faces);
		
	}
}







ModelLoader::ModelLoader() {
	
}

bool ModelLoader::LoadModel(FramebufferObject& o, String path) {
	model.Clear();
	
	#ifdef flagASSIMP
	if (LoadModelAssimp(o, path))
		return true;
	#endif
	
	return false;
}


#ifdef flagASSIMP

bool ModelLoader::LoadModelAssimp(FramebufferObject& o, String path)
{
	LOG("Model::LoadModelAssimp: " << path);
    Assimp::Importer import;
    const aiScene *scene = import.ReadFile(path.Begin(), aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);
	
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        LOG("ERROR: assimp load failed: " << import.GetErrorString());
        return false;
    }
    this->path = path;
    this->directory = GetFileDirectory(path);
	
	model = new ModelMesh();
	model->SetParent(this);
	
    ProcessNode(o, scene->mRootNode, scene);
    
    return true;
}

void ModelLoader::ProcessNode(FramebufferObject& o, aiNode *node, const aiScene *scene)
{
    // process all the node's meshes (if any)
    for(unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        ProcessMesh(o, *model, model->meshes.Add(), mesh, scene);
    }
    // then do the same for each of its children
    for(unsigned int i = 0; i < node->mNumChildren; i++) {
        ProcessNode(o, node->mChildren[i], scene);
    }
}

void ModelLoader::ProcessMesh(FramebufferObject& o, ModelMesh& mout, Mesh& out, aiMesh *mesh, const aiScene *scene)
{
    out.vertices.SetCount(mesh->mNumVertices);
    out.tex_coords.SetCount(mesh->mNumVertices);
    for(unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex& vertex = out.vertices[i];
        vec2& tex_coord = out.tex_coords[i];
        
        // process vertex positions, normals and texture coordinates
        vertex.position[0] = mesh->mVertices[i][0];
		vertex.position[1] = mesh->mVertices[i][1];
		vertex.position[2] = mesh->mVertices[i][2];
		
		vertex.normal[0] = mesh->mNormals[i][0];
		vertex.normal[1] = mesh->mNormals[i][1];
		vertex.normal[2] = mesh->mNormals[i][2];
		
		// does the mesh contain texture coordinates?
		
		if(mesh->mTextureCoords[0]) {
		    tex_coord[0] = mesh->mTextureCoords[0][i][0];
		    tex_coord[1] = mesh->mTextureCoords[0][i][1];
		}
		else
		    tex_coord = vec2(0.0f, 0.0f);
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

	out.SetupAutomatic(o);
}

void ModelLoader::LoadMaterialTextures(ModelMesh& mout, Mesh& out, aiMaterial *mat, int type) {
    for(unsigned int i = 0; i < mat->GetTextureCount((aiTextureType) type); i++) {
        if (out.tex_id[type] >= 0) {
            LOG("warning: ModelLoader: multiple textures per mesh: " << path);
            break;
        }
        aiString str;
        mat->GetTexture((aiTextureType) type, i, &str);
        
        String path = AppendFileName(directory, str.C_Str());
        mout.AddTextureFile(out, (TexType) type, path);
    }
}

#endif



NAMESPACE_TOPSIDE_END
