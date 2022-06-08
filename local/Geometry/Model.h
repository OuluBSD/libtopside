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




class ModelMesh :
	public RefScopeEnabler<ModelMesh,ModelLoader>,
	RTTIBase
{
	
public:
	Array<Mesh> meshes;
	Array<ByteImage> textures;
	Array<Material> materials;
    String path;
    String directory;
    
    
    
	RTTI_DECL_R0(ModelMesh)
	ModelMesh() {}
	ModelMesh(const ModelMesh& m) {*this = m;}
    
    void Clear() {
		meshes.Clear();
		textures.Clear();
	}
	
    void Visit(RuntimeVisitor& vis) {/*vis | meshes | textures;*/}
    
	void operator=(const ModelMesh& src) {
        textures <<= src.textures;
        meshes <<= src.meshes;
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
    Optional<NodeIndex> FindFirstNode(String name);
    mat4 GetNodeWorldTransform(NodeIndex node_idx) const;
    const ModelNode& GetNode(NodeIndex node_idx) const;
    
    bool IsEmpty() const {return meshes.IsEmpty();}
    operator bool() const {return !IsEmpty();}
    
};

using ModelMeshRef = Ref<ModelMesh, RefParent1<ModelLoader>>;


class ModelBuilder;


class ModelLoader :
	public RefScopeEnabler<ModelLoader,RefRoot>
{
	
public:
	RTTI_DECL_R0(ModelLoader)
	ModelLoader();
	
	void Clear() {model.Clear();}
    void Set(const ModelMesh& m) {model = new ModelMesh(m); model->SetParent(this);}
    void operator=(const ModelMesh& m) {Set(m);}
    void operator=(ModelBuilder& mb);
	operator bool() const {return !model.IsEmpty();}
    void Visit(RuntimeVisitor& vis) {if (model) vis % *model;}
	
	Ref<ModelMesh> GetModel() {return model ? model->AsRefT() : Null;}
	
	
public:
	One<ModelMesh> model;
    
    
    
};


NAMESPACE_TOPSIDE_END

#endif
