#pragma once


NAMESPACE_TOPSIDE_BEGIN


namespace Pbr {

// A primitive holds a vertex buffer, index buffer, and a pointer to a PBR material.

struct Primitive
{
    /*using Collection = Vector<Primitive>;
	using NativeBufferRef = typename Gfx::NativeBufferRef;
	using GfxContext& = typename Gfx::GfxContext&;
	using Resources = Resources;
	using Model = Model;
	using Material = Material;*/
	
	Primitive() {}
	~Primitive();
    /*Primitive() = delete;
    Primitive(int idx_count, DataBuffer& index_buffer, DataBuffer& vertex_buffer, Shared<Material> material);
    Primitive(Resources const& pbr_res, const Pbr::PrimitiveBuilder& prim_builder, Shared<Material> material);*/
    
    //void Set(int idx_count, DataBuffer& index_buffer, DataBuffer& vertex_buffer);
    //void Set(const Resources& pbr_res, const Pbr::PrimitiveBuilder& prim_builder);
	
    // Get the material for the primitive.
    Material& GetMaterial() { ASSERT(material); return *material; }
    const Material& GetMaterial() const { ASSERT(material); return *material; }
    
    void SetMaterial(Material& mat);
	void ClearMaterial();
	
//protected:
    void Render(GfxContext& context) const;
    void Copy(const Resources& pbr_res, Primitive& dst) const;
	
    
public:
    Vector<Pbr::Vertex>		vertices;
    Vector<uint32>			indices;
    Material*				material = 0;
    
    
};

}


NAMESPACE_TOPSIDE_END
