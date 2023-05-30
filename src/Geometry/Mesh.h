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
    VectorMap<String, NodeIndex> named_vertices;
	int material = -1;
	bool disable_textures = false;
	bool wireframe_only = false;
	bool use_quad = false;
	
	
public:
	Mesh() {Clear();}
	Mesh(const Mesh& m) {*this = m;}
	
    hash_t GetHashValue() const {
        CombineHash c;
        for (auto& v : vertices) c.Put(v.GetHashValue());
        for (auto& v : indices) c.Put(v);
        for(int i = 0; i < named_vertices.GetCount(); i++) {
			c.Put(named_vertices.GetKey(i).GetHashValue());
			c.Put(named_vertices[i]);
        }
        c.Put(material);
        c.Put(disable_textures);
        c.Put(wireframe_only);
        c.Put(use_quad);
        return c;
    }
    void Etherize(Ether& e);
    
	void Clear();
	void ReverseFaces();
	
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
        use_quad = src.use_quad;
    }
    
    
    void SetMaterial(Material& m) {ASSERT(m.owner == owner && m.id >= 0); material = m.id;}
    void SetCountTriangles(int vertex_count, int triangle_count) {
        use_quad = false;
        vertices.SetCount(vertex_count);
        indices.SetCount(3 * triangle_count);
    }
    void SetCountQuads(int vertex_count, int quad_count) {
        use_quad = true;
        vertices.SetCount(vertex_count);
        indices.SetCount(4 * quad_count);
    }
    void SetVertCoord(int i, vec3 v) {vertices[i].position = v.Embed();}
    void SetVertNormal(int i, vec3 v) {vertices[i].normal = v;}
    void SetVertTangent(int i, vec3 v) {vertices[i].tangent = v.Embed();}
    void SetTexCoord(int i, vec2 v) {vertices[i].tex_coord = v;}
    void SetQuadIndices(int i, const ivec4& v) {
        ASSERT(use_quad);
        ASSERT(v[0] >= 0 && v[0] < vertices.GetCount());
        ASSERT(v[1] >= 0 && v[1] < vertices.GetCount());
        ASSERT(v[2] >= 0 && v[2] < vertices.GetCount());
        ASSERT(v[3] >= 0 && v[3] < vertices.GetCount());
        indices[4 * i + 0] = v[0];
        indices[4 * i + 1] = v[1];
        indices[4 * i + 2] = v[2];
        indices[4 * i + 3] = v[3];
    }
    void SetTriangleIndices(int i, const ivec3& v) {
        ASSERT(!use_quad);
        ASSERT(v[0] >= 0 && v[0] < vertices.GetCount());
        ASSERT(v[1] >= 0 && v[1] < vertices.GetCount());
        ASSERT(v[2] >= 0 && v[2] < vertices.GetCount());
        indices[3 * i + 0] = v[0];
        indices[3 * i + 1] = v[1];
        indices[3 * i + 2] = v[2];
    }
    void SetNodeIndex(int i, NodeIndex idx) {vertices[i].mdl_transform_idx = idx;}
    
    int GetTriangleCount() const {return indices.GetCount() / 3;}
    int GetQuadCount() const {return indices.GetCount() / 4;}
    vec3 GetVertCoord(int i) const {return vertices[i].position.Splice();}
    vec3 GetVertNormal(int i) const {return vertices[i].normal;}
    vec2 GetTexCoord(int i) const {return vertices[i].tex_coord;}
    ivec3 GetTriangleIndices(int i) const {
        ASSERT(!use_quad);
        ivec3 v;
        v[0] = indices[i * 3 + 0];
        v[1] = indices[i * 3 + 1];
        v[2] = indices[i * 3 + 2];
        return v;
    }
    ivec4 GetQuadIndices(int i) const {
        ASSERT(use_quad);
        ivec4 v;
        v[0] = indices[i * 4 + 0];
        v[1] = indices[i * 4 + 1];
        v[2] = indices[i * 4 + 2];
        v[3] = indices[i * 4 + 2];
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
