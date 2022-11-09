#ifndef _Geometry_Mesh_h_
#define _Geometry_Mesh_h_

NAMESPACE_TOPSIDE_BEGIN


class Model;


struct GfxMesh : RTTIBase {
	RTTI_DECL0(GfxMesh)
};

class Mesh : public BoundingBox, Moveable<Mesh> {
	
public:
	Model* owner = 0;
    Vector<Vertex> vertices;
    Vector<uint32> indices;
    //Vector<vec2> tex_coords;
    VectorMap<String, NodeIndex> named_vertices;
	int material = -1;
	bool disable_textures = false;
	bool wireframe_only = false;
	//GfxMesh* accel = 0;
	
	
public:
	Mesh() {Clear();}
	Mesh(const Mesh& m) {*this = m;}
	
	void Clear();
	void ReverseFaces();
	//void Set(GfxDataObject& o, const Vector<Vertex>& Vertices, const Vector<uint32>& indices);
    bool AddTextureFilePath(String key, String path);
	void operator=(const Mesh& src) {
        Clear();
        BoundingBox::operator=(src);
        vertices <<= src.vertices;
        indices <<= src.indices;
        named_vertices <<= src.named_vertices;
        material = src.material;
        disable_textures = src.disable_textures;
        wireframe_only = src.wireframe_only;
    }
    
    
    void SetMaterial(Material& m) {ASSERT(m.owner == owner && m.id >= 0); material = m.id;}
    void SetCount(int vertex_count, int triangle_count) {
        vertices.SetCount(vertex_count);
        indices.SetCount(3 * triangle_count);
    }
    void SetVertCoord(int i, vec3 v) {vertices[i].position = v.Embed();}
    void SetVertNormal(int i, vec3 v) {vertices[i].normal = v;}
    void SetVertTangent(int i, vec3 v) {vertices[i].tangent = v.Embed();}
    void SetTexCoord(int i, vec2 v) {vertices[i].tex_coord = v;}
    void SetTriangleIndices(int i, const ivec3& v) {
        ASSERT(v[0] >= 0 && v[0] < vertices.GetCount());
        ASSERT(v[1] >= 0 && v[1] < vertices.GetCount());
        ASSERT(v[2] >= 0 && v[2] < vertices.GetCount());
        indices[3 * i + 0] = v[0];
        indices[3 * i + 1] = v[1];
        indices[3 * i + 2] = v[2];
    }
    void SetNodeIndex(int i, NodeIndex idx) {vertices[i].mdl_transform_idx = idx;}
    
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
    void CenterAnchor(BoundingBox::Align align = BoundingBox::ALIGN_CENTER);
    void SetAnchor(vec3 pos);
    void TransformVertices(mat4 transform);
    void Dump(int indent=0);
    
    
};


NAMESPACE_TOPSIDE_END

#endif
