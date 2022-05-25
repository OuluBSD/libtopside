#include "IGraphics.h"


NAMESPACE_PARALLEL_BEGIN


#if 0

NativeBufferRef CreateVertexBuffer(NativeDeviceRef device, const Pbr::PrimitiveBuilder& prim_builder)
{
    TODO
    
    /*
    // Create Vertex Buffer
    D3D11_BUFFER_DESC desc{};
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.ByteWidth = (uint32)(sizeof(decltype(prim_builder.vertices)::value_type) * prim_builder.vertices.GetCount());
    desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    D3D11_SUBRESOURCE_DATA init_data{};
    init_data.pSysMem = prim_builder.vertices.data();

    NativeBufferRef vertex_buffer;
    Pbr::Internal::ThrowIfFailed(device->CreateBuffer(&desc, &init_data, &vertex_buffer));
    return vertex_buffer;*/
}

NativeBufferRef CreateIndexBuffer(NativeDeviceRef device, const Pbr::PrimitiveBuilder& prim_builder)
{
    TODO
    
    // Create Index Buffer
    /*D3D11_BUFFER_DESC desc{};
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.ByteWidth = (uint32)(sizeof(decltype(prim_builder.indices)::value_type) * prim_builder.indices.GetCount());
    desc.BindFlags = D3D11_BIND_INDEX_BUFFER;

    D3D11_SUBRESOURCE_DATA init_data{};
    init_data.pSysMem = prim_builder.indices.data();

    NativeBufferRef index_buffer;
    Pbr::Internal::ThrowIfFailed(device->CreateBuffer(&desc, &init_data, &index_buffer));
    return index_buffer;*/
}

#endif


namespace Pbr {


template <class Gfx>
PrimitiveT<Gfx>::PrimitiveT(int idx_count, NativeBufferRef index_buffer, NativeBufferRef vertex_buffer, Shared<MaterialT<Gfx>> material)
    : idx_count(idx_count)
    , vertex_buffer(vertex_buffer)
    , index_buffer(index_buffer)
    , material(std::move(material))
{
	
}

template <class Gfx>
PrimitiveT<Gfx>::PrimitiveT(Resources const& pbr_res, const Pbr::PrimitiveBuilder& prim_builder, Shared<Pbr::MaterialT<Gfx>> material)
    : PrimitiveT(
        (uint32)prim_builder.indices.GetCount(),
        CreateIndexBuffer(pbr_res.GetDevice().Get(), prim_builder).Get(),
        CreateVertexBuffer(pbr_res.GetDevice().Get(), prim_builder).Get(),
        std::move(material))
{
	
}

template <class Gfx>
PrimitiveT<Gfx> PrimitiveT<Gfx>::Clone(Resources const& pbr_res) const
{
    return PrimitiveT(idx_count, index_buffer.Get(), vertex_buffer.Get(), material->Clone(pbr_res));
}

template <class Gfx>
void PrimitiveT<Gfx>::Render(NativeDeviceContextRef context) const
{
    TODO
    
    /*const int stride = sizeof(Pbr::Vertex);
    const int offset = 0;
    context->IASetVertexBuffers(0, 1, vertex_buffer.GetAddressOf(), &stride, &offset);
    context->IASetIndexBuffer(index_buffer.Get(), DXGI_FORMAT_R32_UINT, 0);
    context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    context->DrawIndexedInstanced(idx_count, 2, 0, 0, 0);*/
}


}


NAMESPACE_PARALLEL_END
