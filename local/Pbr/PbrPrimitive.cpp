#include "Pbr.h"


NAMESPACE_TOPSIDE_BEGIN


ComPtr<ID3D11Buffer> CreateVertexBuffer(ID3D11Device* device, const Pbr::PrimitiveBuilder& prim_builder)
{
    // Create Vertex Buffer
    D3D11_BUFFER_DESC desc{};
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.ByteWidth = (uint32)(sizeof(decltype(prim_builder.vertices)::value_type) * prim_builder.vertices.size());
    desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    D3D11_SUBRESOURCE_DATA init_data{};
    init_data.pSysMem = prim_builder.vertices.data();

    ComPtr<ID3D11Buffer> vertex_buffer;
    Pbr::Internal::ThrowIfFailed(device->CreateBuffer(&desc, &init_data, &vertex_buffer));
    return vertex_buffer;
}

ComPtr<ID3D11Buffer> CreateIndexBuffer(ID3D11Device* device, const Pbr::PrimitiveBuilder& prim_builder)
{
    // Create Index Buffer
    D3D11_BUFFER_DESC desc{};
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.ByteWidth = (uint32)(sizeof(decltype(prim_builder.indices)::value_type) * prim_builder.indices.size());
    desc.BindFlags = D3D11_BIND_INDEX_BUFFER;

    D3D11_SUBRESOURCE_DATA init_data{};
    init_data.pSysMem = prim_builder.indices.data();

    ComPtr<ID3D11Buffer> index_buffer;
    Pbr::Internal::ThrowIfFailed(device->CreateBuffer(&desc, &init_data, &index_buffer));
    return index_buffer;
}

}


namespace Pbr {


Primitive::Primitive(UINT idx_count, ID3D11Buffer* index_buffer, ID3D11Buffer* vertex_buffer, Shared<Material> material)
    : idx_count(idx_count)
    , vertex_buffer(vertex_buffer)
    , index_buffer(index_buffer)
    , material(std::move(material))
{
	
}

Primitive::Primitive(Pbr::Resources const& pbr_res, const Pbr::PrimitiveBuilder& prim_builder, Shared<Pbr::Material> material)
    : Primitive(
        (uint32)prim_builder.indices.size(),
        CreateIndexBuffer(pbr_res.GetDevice().Get(), prim_builder).Get(),
        CreateVertexBuffer(pbr_res.GetDevice().Get(), prim_builder).Get(),
        std::move(material))
{
	
}

Primitive Primitive::Clone(Pbr::Resources const& pbr_res) const
{
    return Primitive(idx_count, index_buffer.Get(), vertex_buffer.Get(), material->Clone(pbr_res));
}

void Primitive::Render(ID3D11DeviceContext3* context) const
{
    const UINT stride = sizeof(Pbr::Vertex);
    const UINT offset = 0;
    context->IASetVertexBuffers(0, 1, vertex_buffer.GetAddressOf(), &stride, &offset);
    context->IASetIndexBuffer(index_buffer.Get(), DXGI_FORMAT_R32_UINT, 0);
    context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    context->DrawIndexedInstanced(idx_count, 2, 0, 0, 0);
}


}


NAMESPACE_TOPSIDE_END
