#include "Geometry.h"


NAMESPACE_TOPSIDE_BEGIN


ModelNode::ModelNode() {
	local_transform = Identity<mat4>();
	modify_count = 0;
}

ModelNode::ModelNode(const ModelNode& n) {
	modify_count = 0;
	*this = n;
}




bool Model::AddTextureFile(int mesh_i, TexType type, String path) {
	if (mesh_i < 0 || mesh_i >= meshes.GetCount())
		return false;
	return AddTextureFile(meshes[mesh_i], type, path);
}

bool Model::AddTextureFile(Mesh& mesh, TexType type, String path){
	if (FileExists(path)) {
        Image src = StreamRaster::LoadFileAny(path);
        return SetTexture(mesh, type, src, path);
    }
	return false;
}

bool Model::SetTexture(Mesh& mesh, TexType type, Image img, String path) {
	if (IsPositive(img.GetSize())) {
		if (mesh.material < 0) {
			Material& mat = AddMaterial();
			mesh.material = mat.id;
		}
		Material& mat = materials.Get(mesh.material);
		ASSERT(mat.id >= 0);
		int tex_id = GetAddTexture(img, path);
        mat.tex_id[type] = tex_id;
        mat.tex_filter[type] = 1; // LINEAR
        return true;
    }
    return false;
}

bool Model::LoadCubemapFile(Mesh& mesh, TexType type, String path) {
	ASSERT(type >= TEXTYPE_CUBE_DIFFUSE);
	
	if (path.IsEmpty())
		return false;
	Index<String> ext_list; ext_list << "" << ".png" << ".jpg";
	Index<String> dir_list; dir_list << "" << "imgs" << "imgs/skybox";
	String abs_path;
	for(int j = 0; j < ext_list.GetCount(); j++) {
		for(int k = 0; k < dir_list.GetCount(); k++) {
			String s = RealizeShareFile(AppendFileName(dir_list[k], path + ext_list[j]));
			if (FileExists(s)) {
				abs_path = s;
				break;
			}
		}
		if (!abs_path.IsEmpty()) break;
	}

	if (!FileExists(abs_path)) {
		LOG("Model::LoadCubemapFile: error: file does not exist: " << abs_path);
		return false;
	}
	
	int cubetex_id = GetAddCubeTexture(abs_path);
	CubeTexture& cubetex = cube_textures.Get(cubetex_id);
	cubetex.img[0] = StreamRaster::LoadFileAny(abs_path);
	
	String ext = GetFileExt(abs_path);
	String base = abs_path.Left(abs_path.GetCount() - ext.GetCount());
	
	for(int i = 1; i < 6; i++) {
		String side_path = base + "_" + IntStr(i) + ext;
		if (!FileExists(side_path)) {
			LOG("Model::LoadCubemapFile: error: file does not exist: " << side_path);
			return false;
		}
		
		cubetex.img[i] = StreamRaster::LoadFileAny(side_path);
	}
	
	for(int i = 0; i < 6; i++) {
		if (cubetex.img[i].IsEmpty()) {
			LOG("Model::LoadCubemapFile: error: cube side " << i << " image is empty");
			return false;
		}
	}
	
	if (mesh.material < 0) {
		Material& mat = AddMaterial();
		mesh.material = mat.id;
	}
	Material& mat = materials.Get(mesh.material);
	ASSERT(mat.id >= 0);
    mat.tex_id[type] = cubetex_id;
    mat.tex_filter[type] = 1; // LINEAR
    return true;
}

void Model::MakeModel(Shape2DWrapper& shape) {
	ASSERT(shape.shape);
	if (shape.shape) {
		MAKE_STATIC_LOCAL(Vector<tri3>, faces);
		shape.shape->GetFaces(faces);
		
	}
}

void Model::ReverseFaces() {
	for (Mesh& m : meshes)
		m.ReverseFaces();
}

void Model::GetGfxMeshes(Vector<GfxMesh*>& meshes) {
	for (Mesh& m : this->meshes)
		if (m.accel)
			meshes.Add(m.accel);
}

Mesh& Model::AddMesh() {
	Mesh& m = meshes.Add();
	m.owner = this;
	return m;
}

Material& Model::AddMaterial() {
	int id = materials.IsEmpty() ? 0 : materials.Top().id + 1;
	Material& m = materials.Add(id);
	m.owner = this;
	m.id = id;
	return m;
}

ModelNode& Model::AddNode(String name, NodeIndex parent) {
	ModelNode& n = nodes.Add();
	n.name = name;
	n.index = nodes.GetCount()-1;
	n.parent_node_index = parent;
	return n;
}

Optional<NodeIndex> Model::FindFirstNode(String name, Optional<NodeIndex> const& parent_node_index) {
	// Children are guaranteed to come after their parents, so start looking after the parent index if one is provided.
    const NodeIndex start_index = parent_node_index ? parent_node_index.value() + 1 : ModelNode::RootIdx;
    for (const ModelNode& node : nodes) {
        if ((!parent_node_index || node.parent_node_index == parent_node_index.value()) &&
            node.name == name) {
            return node.index;
        }
    }

    return {};
}

mat4 Model::GetNodeWorldTransform(NodeIndex node_idx) const {
    const ModelNode& node = GetNode(node_idx);
	
    // Compute the transform recursively.
    const mat4 parent_transform =
		node.index == ModelNode::RootIdx ?
			Identity<mat4>() :
			GetNodeWorldTransform(node.parent_node_index);
	
    return MultiplyMatrix(node.GetTransform(), parent_transform);
}

const ModelNode& Model::GetNode(NodeIndex node_idx) const {
	return nodes[node_idx];
}

void Model::Dump() {
	for(int i = 0; i < meshes.GetCount(); i++) {
		LOG("Mesh " << i << ":");
		meshes[i].Dump(1);
	}
	LOG("Textures:");
	for(int i = 0; i < textures.GetCount(); i++) {
		Size sz = textures[i].img.GetSize();
		LOG("\t" << i << ": " << textures[i].path << ": " << (int)sz.cx << "x" << (int)sz.cy);
	}
}

int Model::AddTexture(const Image& img, String path) {
	int id = textures.IsEmpty() ? 0 : textures.GetKey(textures.GetCount()-1) + 1;
	Texture& t = textures.Add(id);
	t.img.Set(img);
	t.path = path;
	return id;
}

int Model::GetAddTexture(const Image& img, String path) {
	int i = FindTexture(path);
	if (i >= 0)
		return i;
	if (img.IsEmpty())
		return -1;
	return AddTexture(img, path);
}

int Model::AddCubeTexture(String path) {
	int id = cube_textures.IsEmpty() ? 0 : cube_textures.GetKey(textures.GetCount()-1) + 1;
	CubeTexture& t = cube_textures.Add(id);
	t.path = path;
	return id;
}

int Model::GetAddCubeTexture(String path) {
	int i = FindTexture(path);
	if (i >= 0)
		return i;
	return AddCubeTexture(path);
}

int Model::FindTexture(String path) {
	for(int i = 0; i < textures.GetCount(); i++) {
		Texture& tex = textures[i];
		if (tex.path == path)
			return textures.GetKey(i);
	}
	return -1;
}


#if 0

void Model::Refresh(FramebufferState& s, GfxDataObject& o) {
	for (Mesh& m : meshes) {
		Refresh(s, o, m);
	}
}

void Model::Refresh(FramebufferState& s, GfxDataObject& o, Mesh& mesh) {
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
    
    
    /*if (!mesh.disable_textures)
	    s.SetBool("disable_textures", false);
    else {
        vec4 v4 = MakeVec4(mesh.material.ambient, 1);
        s.SetBool("disable_textures", true);
        s.SetVec4("in_color", v4);
    }*/
	
	//Dump();
	
}

#endif






ModelLoader::ModelLoader() {
	
}

void ModelLoader::Clear() {
	model.Clear();
}

void ModelLoader::Set(const Model& m) {
	model = new Model(m);
	model->SetParent(this);
}

void ModelLoader::operator=(const Model & m) {
	Set(m);
}

ModelLoader::operator bool() const {
	return !model.IsEmpty();
}

void ModelLoader::Visit(RuntimeVisitor& vis) {
	if (model)
		vis % *model;
}

void ModelLoader::Create() {
	model.Create();
	model->SetParent(this);
}

Ref<Model> ModelLoader::GetModel() {
	return model ? model->AsRefT() : Null;
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

