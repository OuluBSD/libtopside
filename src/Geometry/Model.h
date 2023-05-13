#ifndef _Geometry_Model_h_
#define _Geometry_Model_h_

NAMESPACE_TOPSIDE_BEGIN

class ModelLoader;


struct ModelNode : Moveable<ModelNode>
{
	ModelNode();
	ModelNode(const ModelNode& n);
	
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
	};
	
	struct CubeTexture {
		ByteImage img[6];
		String path;
	};
	
	Array<Mesh> meshes;
	Vector<ModelNode> nodes;
	ArrayMap<int, Material> materials;
	ArrayMap<int, Texture> textures;
	ArrayMap<int, CubeTexture> cube_textures;
    String path;
    String directory;
    
    
    
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
	//void Refresh(GfxDataState& s, GfxDataObject& o);
    //void Refresh(GfxDataState& s, GfxDataObject& o, Mesh& m);
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
