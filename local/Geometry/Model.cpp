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

#if 0

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
	        
	        glActiveTexture(GL_TEXTURE0 + tex_i); // activate proper texture unit before binding
	        // retrieve texture number (the N in diffuse_textureN)
	        String key;
	        if (i == TEXTYPE_DIFFUSE)
	            key = "material.texture_diffuse" + IntStr(diffuseNr++);
	        else if (i == TEXTYPE_SPECULAR)
	            key = "material.texture_specular" + IntStr(specularNr++);
	        
	        s.SetInt(key, tex_i);
	        
	        ASSERT(tex.tex_id >= 0);
	        glBindTexture(GL_TEXTURE_2D, tex.tex_id);
	        
	        tex_i++;
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

#endif






ModelLoader::ModelLoader() {
	
}


#if 0

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

#endif

void ModelLoader::operator=(ModelBuilder& mb) {
	model = mb.Detach();
}




NAMESPACE_TOPSIDE_END

