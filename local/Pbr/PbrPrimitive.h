#pragma once


NAMESPACE_TOPSIDE_BEGIN


namespace Pbr {

// A primitive holds a vertex buffer, index buffer, and a pointer to a PBR material.
struct Primitive
{
    using Collection = Vector<Primitive>;

    Primitive() = delete;
    Primitive(int idx_count, ID3D11Buffer* index_buffer, ID3D11Buffer* vertex_buffer, Shared<Material> material);
    Primitive(Pbr::Resources const& pbr_res, const Pbr::PrimitiveBuilder& prim_builder, Shared<Material> material);

    // Get the material for the primitive.
    Shared<Material>& GetMaterial() { return material; }
    const Shared<Material>& GetMaterial() const { return material; }

protected:
    friend struct Model;
    void Render(ID3D11DeviceContext3* context) const;
    Primitive Clone(Pbr::Resources const& pbr_res) const;

private:
    int idx_count;
    ComPtr<ID3D11Buffer> index_buffer;
    ComPtr<ID3D11Buffer> vertex_buffer;
    Shared<Material> material;
};

}


NAMESPACE_TOPSIDE_END
