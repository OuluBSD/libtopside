#ifndef _Geometry_Model_h_
#define _Geometry_Model_h_

NAMESPACE_TOPSIDE_BEGIN

class ModelLoader;
struct GfxShader;
struct CpuDataObject;
/*#if HAVE_OPENGL
struct OglDataObject;
class OglShader;
#endif*/


//struct FramebufferState;


class Mesh : public BoundingBox, Moveable<Mesh> {
	
public:
    Vector<Vertex> vertices;
    Vector<uint32> indices;
    //Vector<vec2> tex_coords;
	Material material;
	int tex_id[TEXTYPE_COUNT];
	bool is_colored_only = false;
	bool is_lines = false;
	
	
	Mesh() {Clear();}
	Mesh(const Mesh& m) {*this = m;}
	
	void Clear();
	//void Set(GfxDataObject& o, const Vector<Vertex>& Vertices, const Vector<uint32>& indices);
    bool AddTextureFilePath(String key, String path);
	void operator=(const Mesh& src) {
        Clear();
        BoundingBox::operator=(src);
        vertices <<= src.vertices;
        indices <<= src.indices;
        //tex_coords <<= src.tex_coords;
        material = src.material;
        for(int i = 0; i < TEXTYPE_COUNT; i++)
            tex_id[i] = src.tex_id[i];
        is_colored_only = src.is_colored_only;
        is_lines = src.is_lines;
        //Refresh();
    }
    
    /*void Refresh(GfxDataObject& o);
    void RefreshOgl(GfxDataObject& o);
    void RefreshSw(GfxDataObject& o);
    void RefreshSw(CpuDataObject& o);
#if HAVE_OPENGL
    void RefreshOgl(OglDataObject& o);
#endif*/
    
    void SetMaterial(const Material& m) {material = m;}
    void SetCount(int vertex_count, int triangle_count) {
        vertices.SetCount(vertex_count);
        indices.SetCount(3 * triangle_count);
        //tex_coords.SetCount(3 * triangle_count);
    }
    void SetVertCoord(int i, vec3 v) {vertices[i].position = v.Embed();}
    void SetVertNormal(int i, vec3 v) {vertices[i].normal = v;}
    void SetVertTangent(int i, vec3 v) {}//vertices[i].tangent = v;}
    //void SetTexCoord(int i, vec2 v) {tex_coords[i] = v;}
    void SetTriangleIndices(int i, const ivec3& v) {
        ASSERT(v[0] >= 0 && v[0] < vertices.GetCount());
        ASSERT(v[1] >= 0 && v[1] < vertices.GetCount());
        ASSERT(v[2] >= 0 && v[2] < vertices.GetCount());
        indices[3 * i + 0] = v[0];
        indices[3 * i + 1] = v[1];
        indices[3 * i + 2] = v[2];
    }
    
    int GetTriangleCount() const {return indices.GetCount() / 3;}
    vec3 GetVertCoord(int i) const {return vertices[i].position.Splice();}
    vec3 GetVertNormal(int i) const {return vertices[i].normal;}
    vec2 GetTexCoord(int i) const {return vertices[i].tex_coord;}
    ivec3 GetTriangleIndices(int i) const {
        ivec3 v;
        v[0] = indices[i * 3 + 0];
        v[1] = indices[i * 3 + 1];
        v[2] = indices[i * 3 + 2];
        return v;
    }
    void UpdateBoundingBox();
    void UpdateNormalsAndTangents();
    void CenterAxis(BoundingBox::Align align = BoundingBox::ALIGN_CENTER);
    void SetAxis(vec3 axis);
    void TransformVertices(mat4 transform);
    void Dump(int indent=0);
    
    
};


class ModelMesh :
	public RefScopeEnabler<ModelMesh,ModelLoader>,
	RTTIBase
{
	
public:
	Vector<Mesh> meshes;
	Vector<Texture> textures;
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
	
	const Vector<Mesh>& GetMeshes() const {return meshes;}
	bool AddTextureFile(int mesh_i, TexType type, String path);
	bool AddTextureFile(Mesh& mesh, TexType type, String path);
	bool SetTexture(Mesh& mesh, TexType type, Image img);
	
	void MakeModel(Shape2DWrapper& shape);
	//void Refresh(GfxDataState& s, GfxDataObject& o);
    //void Refresh(GfxDataState& s, GfxDataObject& o, Mesh& m);
    void Dump();
    
};

using ModelMeshRef = Ref<ModelMesh, RefParent1<ModelLoader>>;


class ModelLoader :
	public RefScopeEnabler<ModelLoader,RefRoot>
{
	
public:
	RTTI_DECL_R0(ModelLoader)
	ModelLoader();
	
	void Clear() {model.Clear();}
    void Set(const ModelMesh& m) {model = new ModelMesh(m); model->SetParent(this);}
    void operator=(const ModelMesh& m) {Set(m);}
	operator bool() const {return !model.IsEmpty();}
    void Visit(RuntimeVisitor& vis) {if (model) vis % *model;}
	
	Ref<ModelMesh> GetModel() {return model ? model->AsRefT() : Null;}
	
	
public:
	One<ModelMesh> model;
    
    
    
};


NAMESPACE_TOPSIDE_END

#endif
