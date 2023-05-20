#ifndef _Geometry_Model_h_
#define _Geometry_Model_h_

NAMESPACE_TOPSIDE_BEGIN

class ModelLoader;


struct ModelNode : Moveable<ModelNode>
{
	ModelNode();
	ModelNode(const ModelNode& n);
	
    hash_t GetHashValue() const {
        CombineHash c;
        c.Put(name.GetHashValue());
        c.Put(index);
        c.Put(parent_node_index);
        c.Put(local_transform.GetHashValue());
        return c;
    }
    void Etherize(Ether& e);
    
    void Set(const mat4& local_transform, String name, NodeIndex index, NodeIndex parent_node_index) {
        this->name = name;
        this->index = index;
        this->parent_node_index = parent_node_index;
        modify_count = 0;
        SetTransform(local_transform);
    }

    // Set the local transform for this node.
    void SetTransform(const mat4& transform) {
        StoreMatrix(&local_transform, transform);
        ++modify_count;
    }

    // Get the local transform for this node.
    const mat4& GetTransform() const {
        return local_transform;
    }

	void operator=(const ModelNode& n) {
		name = n.name;
		index = n.index;
		parent_node_index = n.parent_node_index;
		modify_count = (int)n.modify_count;
		local_transform = n.local_transform;
	}
	
public:
    String			name;
    NodeIndex		index;
    NodeIndex		parent_node_index;
	
	static const int RootIdx = 0;
	
private:
    friend class Model;
    friend class MeshFactory;
    friend class ModelBuilder;
    
    mat4			local_transform;
    
    
    Atomic			modify_count;
};



class Model :
	public RefScopeEnabler<Model,ModelLoader>,
	RTTIBase
{
	
public:
	struct Texture {
		ByteImage img;
		String path;
		
	    hash_t GetHashValue() const {
	        CombineHash c;
	        c.Put(img.GetHashValue());
	        c.Put(path.GetHashValue());
	        return c;
	    }
		void Etherize(Ether& e);
	};
	
	struct CubeTexture {
		ByteImage img[6];
		String path;
		
	    hash_t GetHashValue() const {
	        CombineHash c;
	        for(int i = 0; i < 6; i++)
				c.Put(img[i].GetHashValue());
	        c.Put(path.GetHashValue());
	        return c;
	    }
		void Etherize(Ether& e);
	};
	
public:
	Array<Mesh> meshes;
	Vector<ModelNode> nodes;
	ArrayMap<int, Material> materials;
	ArrayMap<int, Texture> textures;
	ArrayMap<int, CubeTexture> cube_textures;
    String path;
    String directory;
    
    
public:
	RTTI_DECL_R0(Model)
	Model() {}
	Model(const Model& m) {*this = m;}
    
    void Clear() {
		meshes.Clear();
		nodes.Clear();
		materials.Clear();
		textures.Clear();
		path.Clear();
		directory.Clear();
	}
	
    hash_t GetHashValue() const {
        CombineHash ch;
        for (auto& v : meshes) ch.Put(v.GetHashValue());
        for (auto& v : nodes) ch.Put(v.GetHashValue());
        for(int i = 0; i < materials.GetCount(); i++) {
			ch.Put(materials.GetKey(i));
			ch.Put(materials[i].GetHashValue());
        }
        for(int i = 0; i < textures.GetCount(); i++) {
			ch.Put(textures.GetKey(i));
			ch.Put(textures[i].GetHashValue());
        }
        for(int i = 0; i < cube_textures.GetCount(); i++) {
			ch.Put(cube_textures.GetKey(i));
			ch.Put(cube_textures[i].GetHashValue());
        }
        ch.Put(path.GetHashValue());
        ch.Put(directory.GetHashValue());
        return ch;
    }
    void Visit(RuntimeVisitor& vis) {/*vis | meshes | textures;*/}
    
	void operator=(const Model& src) {
        meshes <<= src.meshes;
        nodes <<= src.nodes;
        materials <<= src.materials;
        textures <<= src.textures;
        path = src.path;
        directory = src.directory;
	}
	
	const Array<Mesh>& GetMeshes() const {return meshes;}
	bool AddTextureFile(int mesh_i, TexType type, String path);
	bool AddTextureFile(Mesh& mesh, TexType type, String path);
	bool SetTexture(Mesh& mesh, TexType type, Image img, String path);
	bool LoadCubemapFile(Mesh& mesh, TexType type, String path);
	
	void MakeModel(Shape2DWrapper& shape);
    void Etherize(Ether& e);
    void Dump();
    void ReverseFaces();
    Mesh& AddMesh();
    Material& AddMaterial();
    Material& RealizeMaterial(Mesh& m);
    ModelNode& AddNode(String name="", NodeIndex parent=-1);
    Optional<NodeIndex> FindFirstNode(String name, Optional<NodeIndex> const& parent_node_index = {});
    mat4 GetNodeWorldTransform(NodeIndex node_idx) const;
    const ModelNode& GetNode(NodeIndex node_idx) const;
    int GetMeshCount() const {return meshes.GetCount();}
    Mesh& GetMesh(int i) {return meshes[i];}
    int AddTexture(const Image& img, String path);
    int GetAddTexture(const Image& img, String path);
    int FindTexture(String path);
    int AddCubeTexture(String path);
	int GetAddCubeTexture(String path);

    bool IsEmpty() const {return meshes.IsEmpty();}
    operator bool() const {return !IsEmpty();}
    
};

using ModelRef = Ref<Model, RefParent1<ModelLoader>>;


class ModelBuilder;


class ModelLoader :
	public RefScopeEnabler<ModelLoader,RefRoot>
{
	
public:
	RTTI_DECL_R0(ModelLoader)
	ModelLoader();
	
	void Clear();
    void Set(const Model& m);
    void Attach(Model* m);
    void operator=(const Model& m);
    void operator=(ModelBuilder& mb);
	operator bool() const;
    void Visit(RuntimeVisitor& vis);
	bool LoadModel(String path);
	
	Model& Create();
	Model& Realize();
	Ref<Model> GetModel();
	
	
public:
	One<Model> model;
    
    
protected:
	#ifdef flagASSIMP
	bool LoadModelAssimp(String path);
    void ProcessMaterials(Model& model, const aiScene *scene);
    void ProcessNode(Model& model, aiNode *node, const aiScene *scene);
    void ProcessMesh(Model& mout, Mesh& out, aiMesh *mesh, const aiScene *scene);
    void ProcessMaterial(Model& mout, TS::Material& m, const aiMaterial *mat);
	#endif
	
    
};


NAMESPACE_TOPSIDE_END

#endif
