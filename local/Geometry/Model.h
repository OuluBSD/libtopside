#ifndef _Geometry_Model_h_
#define _Geometry_Model_h_

NAMESPACE_TOPSIDE_BEGIN

class ModelLoader;
//struct GfxShader;
//struct CpuDataObject;
/*#if HAVE_OPENGL
struct OglDataObject;
class OglShader;
#endif*/


//struct FramebufferState;




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
    friend struct Model;
    friend struct MeshFactory;
    friend struct ModelBuilder;
    
    mat4			local_transform;
    
    
    Atomic			modify_count;
};



class Model :
	public RefScopeEnabler<Model,ModelLoader>,
	RTTIBase
{
	
public:
	Array<Mesh> meshes;
	Vector<ModelNode> nodes;
	Array<ByteImage> textures;
	Array<Material> materials;
    String path;
    String directory;
    
    
    
	RTTI_DECL_R0(Model)
	Model() {}
	Model(const Model& m) {*this = m;}
    
    void Clear() {
		meshes.Clear();
		nodes.Clear();
		textures.Clear();
		materials.Clear();
		path.Clear();
		directory.Clear();
	}
	
    void Visit(RuntimeVisitor& vis) {/*vis | meshes | textures;*/}
    
	void operator=(const Model& src) {
        meshes <<= src.meshes;
        nodes <<= src.nodes;
        textures <<= src.textures;
        materials <<= src.materials;
        path = src.path;
        directory = src.directory;
	}
	
	const Array<Mesh>& GetMeshes() const {return meshes;}
	bool AddTextureFile(int mesh_i, TexType type, String path);
	bool AddTextureFile(Mesh& mesh, TexType type, String path);
	bool SetTexture(Mesh& mesh, TexType type, Image img);
	
	void MakeModel(Shape2DWrapper& shape);
	//void Refresh(GfxDataState& s, GfxDataObject& o);
    //void Refresh(GfxDataState& s, GfxDataObject& o, Mesh& m);
    void Dump();
    void ReverseFaces();
    void GetGfxMeshes(Vector<GfxMesh*>& meshes);
    Mesh& AddMesh();
    Material& AddMaterial();
    ModelNode& AddNode(String name="", NodeIndex parent=-1);
    Optional<NodeIndex> FindFirstNode(String name, Optional<NodeIndex> const& parent_node_index = {});
    mat4 GetNodeWorldTransform(NodeIndex node_idx) const;
    const ModelNode& GetNode(NodeIndex node_idx) const;
    int GetMeshCount() const {return meshes.GetCount();}
    Mesh& GetMesh(int i) {return meshes[i];}
    
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
	
	void Create();
	Ref<Model> GetModel();
	
	
public:
	One<Model> model;
    
    
    
};


NAMESPACE_TOPSIDE_END

#endif
