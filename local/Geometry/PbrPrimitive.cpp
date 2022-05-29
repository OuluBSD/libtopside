#include "Geometry.h"


NAMESPACE_TOPSIDE_BEGIN


#if 0

DataBuffer CreateVertexBuffer(NativeDeviceRef device, const Pbr::PrimitiveBuilder& prim_builder)
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

    DataBuffer vertex_buffer;
    Pbr::Internal::ThrowIfFailed(device->CreateBuffer(&desc, &init_data, &vertex_buffer));
    return vertex_buffer;*/
}

DataBuffer CreateIndexBuffer(NativeDeviceRef device, const Pbr::PrimitiveBuilder& prim_builder)
{
    TODO
    
    // Create Index Buffer
    /*D3D11_BUFFER_DESC desc{};
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.ByteWidth = (uint32)(sizeof(decltype(prim_builder.indices)::value_type) * prim_builder.indices.GetCount());
    desc.BindFlags = D3D11_BIND_INDEX_BUFFER;

    D3D11_SUBRESOURCE_DATA init_data{};
    init_data.pSysMem = prim_builder.indices.data();

    DataBuffer index_buffer;
    Pbr::Internal::ThrowIfFailed(device->CreateBuffer(&desc, &init_data, &index_buffer));
    return index_buffer;*/
}

#endif


namespace Pbr {



Primitive::~Primitive() {
	ClearMaterial();
}

void Primitive::ClearMaterial() {
	if (material) {
		material->DecRef();
		material = 0;
	}
}

void Primitive::SetMaterial(Material& mat) {
	ClearMaterial();
	material = &mat;
	mat.IncRef();
}

/*Primitive::Set(int idx_count, DataBuffer& index_buffer, DataBuffer& vertex_buffer, Shared<Material> material)
    : idx_count(idx_count)
    , vertex_buffer(vertex_buffer)
    , index_buffer(index_buffer)
    , material(std::move(material))
{
	
}


Primitive::Set(Resources const& pbr_res, const Pbr::PrimitiveBuilder& prim_builder, Shared<Pbr::Material> material)
    : Primitive(
        (uint32)prim_builder.indices.GetCount(),
        CreateIndexBuffer(pbr_res.GetDevice().Get(), prim_builder).Get(),
        CreateVertexBuffer(pbr_res.GetDevice().Get(), prim_builder).Get(),
        std::move(material))
{
	
}*/



void Primitive::Copy(Resources const& pbr_res, Primitive& dst) const
{
	dst.indices <<= indices;
	dst.vertices <<= vertices;
	dst.material = material;
}

void Primitive::Render(GfxContext& context) const
{
    TODO
    
    /*const int stride = sizeof(Pbr::Vertex);
    const int offset = 0;
    context->IASetVertexBuffers(0, 1, vertex_buffer.GetAddressOf(), &stride, &offset);
    context->IASetIndexBuffer(index_buffer.Get(), DXGI_FORMAT_R32_UINT, 0);
    context->IASetPrimitiveopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    context->DrawIndexedInstanced(idx_count, 2, 0, 0, 0);*/
}


}


NAMESPACE_TOPSIDE_END
