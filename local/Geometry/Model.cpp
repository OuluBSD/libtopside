#include "Geometry.h"

#if 0

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

void ModelMesh::Refresh(FramebufferState& s, GfxDataObject& o) {
	for (Mesh& m : meshes) {
		Refresh(s, o, m);
	}
}

void ModelMesh::Refresh(FramebufferState& s, GfxDataObject& o, Mesh& mesh) {
	int tex_i = 0;
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	for(int i = 0; i < TEXTYPE_COUNT; i++) {
		int tex_id = mesh.tex_id[i];
	    if (tex_id >= 0) {
	        Texture& tex = textures[tex_id];
	        if (tex.compression != Texture::COMP_NONE) {
	            TODO
	        }
	        o.MakeTexture(tex_id, tex.width, tex.height, tex.pitch, tex.stride, tex.data);
	        
	        /*glActiveTexture(GL_TEXTURE0 + tex_i); // activate proper texture unit before binding
	        // retrieve texture number (the N in diffuse_textureN)
	        String key;
	        if (i == TEXTYPE_DIFFUSE)
	            key = "material.texture_diffuse" + IntStr(diffuseNr++);
	        else if (i == TEXTYPE_SPECULAR)
	            key = "material.texture_specular" + IntStr(specularNr++);
	        
	        s.SetInt(key, tex_i);
	        
	        ASSERT(tex.tex_id >= 0);
	        glBindTexture(GL_TEXTURE_2D, tex.tex_id);
	        
	        tex_i++;*/
	    }
	}
    
    
    /*if (!mesh.is_colored_only)
	    s.SetBool("is_colored_only", false);
    else {
        vec4 v4 = MakeVec4(mesh.material.ambient, 1);
        s.SetBool("is_colored_only", true);
        s.SetVec4("in_color", v4);
    }*/
	
	//Dump();
	
}







ModelLoader::ModelLoader() {
	
}

bool ModelLoader::LoadModel(FramebufferState& s, GfxDataObject& o, String path) {
	model.Clear();
	
	if (0)
		;
	#ifdef flagASSIMP
	else if (LoadModelAssimp(o, path))
		;
	#endif
	else
		return false;
	
	model->Refresh(s, o);
	
	return true;
}


#ifdef flagASSIMP

bool ModelLoader::LoadModelAssimp(GfxDataObject& o, String path)
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

void ModelLoader::ProcessNode(GfxDataObject& o, aiNode *node, const aiScene *scene)
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

void ModelLoader::ProcessMesh(GfxDataObject& o, ModelMesh& mout, Mesh& out, aiMesh *mesh, const aiScene *scene)
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

	out.Refresh(o);
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

#endif
