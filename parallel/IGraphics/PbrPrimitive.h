#pragma once


NAMESPACE_PARALLEL_BEGIN


namespace Pbr {

// A primitive holds a vertex buffer, index buffer, and a pointer to a PBR material.
template <class Gfx>
struct PrimitiveT
{
    using Collection = Vector<PrimitiveT>;
	using NativeBufferRef = typename Gfx::NativeBufferRef;
	using NativeDeviceContextRef = typename Gfx::NativeDeviceContextRef;
	using Resources = ResourcesT<Gfx>;
	using Model = ModelT<Gfx>;
	using Material = MaterialT<Gfx>;
	
    PrimitiveT() = delete;
    PrimitiveT(int idx_count, NativeBufferRef index_buffer, NativeBufferRef vertex_buffer, Shared<Material> material);
    PrimitiveT(Resources const& pbr_res, const Pbr::PrimitiveBuilder& prim_builder, Shared<Material> material);
	
    // Get the material for the primitive.
    Shared<Material>& GetMaterial() { return material; }
    const Shared<Material>& GetMaterial() const { return material; }
	
//protected:
    void Render(NativeDeviceContextRef context) const;
    PrimitiveT Clone(const Resources& pbr_res) const;
	
private:
    int					idx_count;
    NativeBufferRef		index_buffer;
    NativeBufferRef		vertex_buffer;
    Shared<Material>	material;
    
    
};

}


NAMESPACE_PARALLEL_END
