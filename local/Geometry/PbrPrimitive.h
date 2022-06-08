#if 0
#pragma once


NAMESPACE_TOPSIDE_BEGIN


namespace Pbr {

// A primitive holds a vertex buffer, index buffer, and a pointer to a PBR material.

struct Mesh
{
    /*using Collection = Vector<Mesh>;
	using NativeBufferRef = typename Gfx::NativeBufferRef;
	using GfxContext& = typename Gfx::GfxContext&;
	using Resources = Resources;
	using Model = Model;
	using Material = Material;*/
	
	Mesh() {}
	~Mesh();
    /*Mesh() = delete;
    Mesh(int idx_count, DataBuffer& index_buffer, DataBuffer& vertex_buffer, Shared<Material> material);
    Mesh(Resources const& pbr_res, const Pbr::MeshBuilder& prim_builder, Shared<Material> material);*/
    
    //void Set(int idx_count, DataBuffer& index_buffer, DataBuffer& vertex_buffer);
    //void Set(const Resources& pbr_res, const Pbr::MeshBuilder& prim_builder);
	
    // Get the material for the primitive.
    Material& GetMaterial() { ASSERT(material); return *material; }
    const Material& GetMaterial() const { ASSERT(material); return *material; }
    
    void SetMaterial(Material& mat);
	void ClearMaterial();
	
//protected:
    void Render(GfxContext& context) const;
    void Copy(const Resources& pbr_res, Mesh& dst) const;
	
    
public:
    Vector<Pbr::Vertex>		vertices;
    Vector<uint32>			indices;
    Material*				material = 0;
    
    
};

}


NAMESPACE_TOPSIDE_END

#endif
